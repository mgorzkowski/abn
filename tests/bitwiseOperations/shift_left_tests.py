#!/usr/bin/env python
import sys
sys.path.append('../wrappers/python')

import unittest
import ctypes

from abn_wrapper import ABN
from utilities import *

class Shift_left_tests(OperationTestCase):

    #Testframe
    def shift_left_testframe(self, a, shift):
        a = self.abn.create_copy(a)
        b = self.abn.create_copy(a)
        self.abn.shift_left(a, shift)
        pa = self.utilities.abn_to_long(a)
        pb = self.utilities.abn_to_long(b)
        self.assertEqual(pa, self.utilities.normalize(pb<<shift, self.utilities.get_default_bit_number()))


    def test_bitwise_shift_left(self):
        for i in range(0, len(self.numbers)):
            for j in range(0, self.utilities.get_default_bit_number()):
                self.shift_left_testframe(self.numbers[i], j)
