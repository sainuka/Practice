#!/bin/python

import math
import os
import random
import re
import sys


def designerPdfViewer(h, word):

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    h = map(int, raw_input().rstrip().split())

    word = raw_input()

    result = designerPdfViewer(h, word)

    fptr.write(str(result) + '\n')

    fptr.close()
