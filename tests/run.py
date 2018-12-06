#!/usr/bin/env python
import traceback

from abn_wrapper import *

def example_func():
    try:
        abn = ABN('../bin/libabn.so')
    except:
        raise Exception('Your libabn.so does not exist or is corrupted')

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
