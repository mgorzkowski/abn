#!/usr/bin/env python
import sys
sys.path.append('..')

import traceback
from ctypes import *
from abn_wrapper import ABN

def example_func(abn):
    number = abn.create(c_uint(4))
    abn.reset(number)
    print abn.to_string(number)
    abn.inc(number)
    print abn.to_string(number)
    abn.set_byte(number, 0xFF, 0)
    print abn.to_string(number)
    abn.inc(number)
    print abn.to_string(number)

if __name__ == '__main__':
    try:
        abn = ABN('../../../bin/shared/libabn.so')
        example_func(abn)
    except:
        print traceback.format_exc()
