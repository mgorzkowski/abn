#!/usr/bin/env python
import sys
sys.path.append('../wrappers/python')

import unittest
import ctypes

from abn_wrapper import ABN
from utilities import Utilities

class Shift_right_tests(unittest.TestCase):

    def setUp(self):
        try:
            self.abn = ABN('../bin/shared/libabn.so')
        except:
            print "Cannot load share object. Make sure that libabn.so exists in the porper place and API is the same"
            sys.exit(-1)
        self.utilities = Utilities(self.abn)
        self.numbers = tuple(self.utilities.get_test_numbers())

    def tearDown(self):
        self.utilities.free_test_numbers(self.numbers)

    #Testframe
    def shift_right_testframe(self, a, shift):
        a = self.abn.create_copy(a)
        b = self.abn.create_copy(a)
        self.abn.shift_right(a, shift)
        pa = self.utilities.abn_to_long(a)
        pb = self.utilities.abn_to_long(b)
        self.assertEqual(pa, self.utilities.normalize(pb>>shift, self.utilities.get_default_bit_number()))

    def test_bitwise_shift_right(self):
        for i in range(0, len(self.numbers)):
            for j in range(0, self.utilities.get_default_bit_number()):
                self.shift_right_testframe(self.numbers[i], j)
