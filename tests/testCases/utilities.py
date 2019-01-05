import sys
sys.path.append('../wrappers')

import unittest
import traceback
import ctypes

from abn_wrapper import ABN

abn = ABN('../bin/libabn.so')
# zmienic na test_number_volume
volume_of_test_numbers = 4
amount_of_test_numbers = 4
test_numbers = []

def abn_to_long(a):
    return int('0x' + abn.to_string(a), base=16)

def hex_to_long(a):
    if not '0x' in a:
        a = '0x' + a
    return int(a, base=16)

def shex(a):
    base = 1 << (8 * abn.size_of_abn_unit * volume_of_test_numbers)
    if a >= base/2:
        a = base - a
    return hex(a);

def get_test_numbers():
    test_numbers = []
    for n in range(1, amount_of_test_numbers):
        temp = abn.create(volume_of_test_numbers)
        abn.reset(temp)
        for i in range(0, abn.size_of_abn_unit*volume_of_test_numbers):
            abn.set_byte(temp, (n+1)*1835*(i+1)%256, i)
        test_numbers.append(temp)
    return test_numbers

def free_test_numbers(number_list):
    for i in range(1, len(number_list)):
        abn.free(number_list[i])
    test_numbers = None

