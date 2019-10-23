#!/bin/python

import math
import os
import random
import re
import sys

def hurdleRace(k, height):

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    nk = raw_input().split()

    n = int(nk[0])

    k = int(nk[1])

    height = map(int, raw_input().rstrip().split())

    result = hurdleRace(k, height)

    fptr.write(str(result) + '\n')

    fptr.close()
