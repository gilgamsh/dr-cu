#! /usr/bin/env python3

import argparse
import os
import re
import matplotlib.pyplot as plt

parser = argparse.ArgumentParser(description='Draw Net in Grid')
parser.add_argument('input_file_names', nargs='+')
parser.add_argument('-d', '--m1_direction', default='horizontal')
args = parser.parse_args()

class Box:
    def __init__(self, layer, lx, hx, ly, hy):
        self.layer = int(layer)
        self.lx = int(lx)
        self.hx = int(hx)
        self.ly = int(ly)
        self.hy = int(hy)

        self.lx, self.hx = min(self.lx, self.hx), max(self.lx, self.hx)
        self.ly, self.hy = min(self.ly, self.hy), max(self.ly, self.hy)
        self.hx += 1
        self.hy += 1

    def __repr__(self):
        return 'box(l={}, x=({}, {}), y=({}, {}))'.format(self.layer, self.lx, self.hx, self.ly, self.hy)

    def w(self):
        return self.hx - self.lx

    def h(self):
        return self.hy - self.ly

def parse_files(file):
    boxes = dict()
    layer_size = dict()

    with open(file) as f:
        while True:
            line = f.readline()
            if not line:
                break

            if line.startswith('layer '):
                words = line.split()
                if len(words) == 4:
                    layer ,x, y = words[1:]
                    layer_size[layer] = (int(x), int(y))

            if line.startswith('nets:'):
                while True:
                    line = f.readline()
                    if not line:
                        break
                    if line.startswith('net '):
                        continue

                    words = line.split()
                    alayer, ax, ay, blayer, bx, by = words

                    if alayer == blayer:
                        box = Box(alayer, ax, bx, ay, by)
                        if box.layer not in boxes:
                            boxes[box.layer] = []
                        boxes[box.layer].append(box)
    
    return layer_size, boxes
  


    
    
                


if __name__ == '__main__':
    for file in args.input_file_names:
        layer_size,boxes = parse_files(file)
        def plot_boxes(boxes, layer, color):
            for box in boxes:
                if box.layer == layer:
                    plt.gca().add_patch(plt.Rectangle((box.lx, box.ly), box.w(), box.h(), color=color, fill=False))
                
