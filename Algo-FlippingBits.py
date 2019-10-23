#!/bin/python

import math
import os
import random
import re
import sys

def flippingBits(n):

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    q = int(raw_input())

    for q_itr in xrange(q):
        n = int(raw_input())

        result = flippingBits(n)

        fptr.write(str(result) + '\n')

    fptr.close()
