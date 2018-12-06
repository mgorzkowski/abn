#!/usr/bin/env python
import sys
sys.path.append('../../wrappers')

import traceback
from ctypes import *
from abn_wrapper import ABN

def example_func():
    try:
        abn = ABN('../../bin/libabn.so')
    except:
        print traceback.format_exc()
        raise Exception('Your libabn.so is corrupted or does not exist')

    number = abn.create(c_uint(int(4)))
    abn.reset(number)
    print abn.to_string(number)
    abn.inc(number)
    print abn.to_string(number)
    abn.set_byte(number, 255, 0)
    print abn.to_string(number)
    abn.inc(number)
    print abn.to_string(number)

if __name__ == '__main__':
    try:
        example_func()
    except:
        print traceback.format_exc()
