#! /usr/bin/env python3

import argparse
import os
import re
import matplotlib.pyplot as plt

parser = argparse.ArgumentParser(description='compute delta')
parser.add_argument('input_dirs', nargs='+')
args = parser.parse_args()

class Utilization:
    def __init__(self, iteration):
        self.iter = iteration
        self.utils = [0 for _ in range(9)]

    def __repr__(self):
        return str(self.iter) + '\n' \
            + '  ' + str(self.utils)
    
    def divide(self, other):
        return [round(self.utils[i] / 1,4) for i in range(9)]


def parse_file(file: str) -> Utilization:
    utilization = Utilization(file[-5])
    with open(file) as f:
        while True:
            line = f.readline()
            if not line:
                break

            if line.startswith('layer '):
                words = line.split()
                if len(words) == 4:
                    continue
                utilization.utils[int(words[1])] = float(words[4])
    
    return utilization


if __name__ == '__main__':
    for input_dir in args.input_dirs:
        files = os.listdir(input_dir)
        result_files = [f for f in files if f.endswith('.txt')]
        result_files.sort()
        result_utils  = [parse_file(os.path.join(input_dir, f)) for f in result_files]
        for result_util in result_utils:
            print(result_util.divide(result_utils[0]))
        

        
            