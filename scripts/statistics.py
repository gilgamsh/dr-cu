#! /usr/bin/env python3

import argparse
import os
import re
import matplotlib.pyplot as plt

parser = argparse.ArgumentParser(description='compute delta')
parser.add_argument('input_dirs', nargs='+')
args = parser.parse_args()


class Box:
    def __init__(self, layer, xl, yl, xh, yh, info):
        self.layer = layer
        self.xl = xl
        self.yl = yl
        self.xh = xh
        self.yh = yh
        self.info = info

    def width(self):
        return self.xh - self.xl

    def height(self):
        return self.yh - self.yl

    def center_x(self):
        return (self.xl + self.xh) / 2

    def center_y(self):
        return (self.yl + self.yh) / 2

    def center(self):
        return (self.center_x(), self.center_y())

    def __str__(self):
        return f'Box({self.layer}, {self.xl}, {self.yl}, {self.xh}, {self.yh}, {self.info})'

    def __repr__(self):
        return self.__str__() + '\n'


def parse_geo_file(file: str) -> list[Box]:
    boxes = []
    with open(file) as f:
        while True:
            line = f.readline()
            if not line:
                break
            if line.startswith('Obs: '):
                words = line.split()
                box = Box(int(words[1]), int(words[2]), int(words[3]),
                          int(words[4]), int(words[5]), words[6])
                boxes.append(box)
    return boxes


def parse_input_lef(file: str, layer: int) -> int:
    dbu = 0
    with open(file) as f:
        while True:
            line = f.readline()
            if not line:
                break

            if line.startswith('UNITS'):
                line = f.readline()
                words = line.split()
                dbu = int(words[2])
                continue
            if line.startswith('LAYER'):
                words = line.split()
                _layer = words[1]
                if _layer != f'Metal{layer}' and _layer != f'metal{layer}':
                    continue
                while True:
                    line = f.readline().strip()
                    if not line:
                        break
                    if line.startswith('WIDTH'):
                        words = line.split()
                        width = float(words[1])
                        return int(width * dbu)


def parse_input_def(file: str, layer: int) -> tuple[set[int], set[int]]:
    xtracks = set()  # type: set[int]
    ytracks = set()  # type: set[int]
    xstep = 0
    ystep = 0
    with open(file) as f:
        while True:
            line = f.readline()
            if not line:
                break
            if line.startswith('TRACKS'):
                words = line.split()
                start = int(words[2])
                step = int(words[6])
                num = int(words[4])
                _layer = int(words[8][-1])

                if _layer != layer:
                    continue

                if words[1] == 'X':
                    xstep = step
                    for i in range(num):
                        xtracks.add(start + i * step)
                elif words[1] == 'Y':
                    ystep = step
                    for i in range(num):
                        ytracks.add(start + i * step)
    return xtracks, ytracks


def analysis_boxes(boxes: list[Box], layer: int, xtracks: set[int], ytracks: set[int], width: int):
    layer -= 1
    num_on_tracks = 0
    num_on_tracks_x = 0
    num_on_tracks_y = 0
    num_boxes = 0
    boxes = [box for box in boxes if box.layer == layer]

    num_boxes = len(boxes)
    for box in boxes:
        if box.center_x() in xtracks and box.width() == width:
            num_on_tracks_x += 1
        if box.center_y() in ytracks and box.height() == width:
            num_on_tracks_y += 1
        if box.center_x() in xtracks and box.center_y() in ytracks:
            num_on_tracks += 1

    return num_boxes, num_on_tracks, num_on_tracks_x, num_on_tracks_y


if __name__ == '__main__':
    for input_dir in args.input_dirs:
        files = os.listdir(input_dir)
        input_lef = [f for f in files if f.endswith('.input.lef')]
        input_def = [f for f in files if f.endswith('.input.def')]
        geo_files = [f for f in files if f.endswith('.stat')]
        geo_files.sort()
        for file in geo_files:
            for layer in range(1, 10):
                width = parse_input_lef(os.path.join(
                    input_dir, input_lef[0]), layer)

                xtracks, ytracks = parse_input_def(
                    os.path.join(input_dir, input_def[0]), layer)
                boxes = parse_geo_file(os.path.join(input_dir, file))
                num_boxes, num_on_tracks, num_on_tracks_x, num_on_tracks_y = analysis_boxes(
                    boxes, layer, xtracks, ytracks, width)
                print(f'{file} {layer} {num_boxes} {num_on_tracks} {num_on_tracks_x} {num_on_tracks_y}: the percentage of boxes on tracks is {max(num_on_tracks_x,num_on_tracks_y) / max(num_boxes,0.0001) * 100:.2f}%')
