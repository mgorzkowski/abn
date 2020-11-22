#!/usr/bin/env python
import sys
sys.path.append('../wrappers/python')

import unittest
import ctypes

from abn_wrapper import ABN
from utilities import *

class Rotate_left_tests(OperationTestCase):

    #Testframe
    def rotate_left_testframe(self, a, shift):
        a = self.abn.create_copy(a)
        b = self.abn.create_copy(a)
        self.abn.rotate_left(a, shift)
        pa = self.utilities.abn_to_long(a)
        pb = self.utilities.abn_to_long(b)
        pb = self.utilities.normalize(pb<<shift, self.utilities.get_default_bit_number()) + self.utilities.normalize(pb>>(self.utilities.get_default_bit_number() - shift), self.utilities.get_default_bit_number())
        self.assertEqual(pa, pb)

    def test_bitwise_rotate_left(self):
        for i in range(0, len(self.numbers)):
            for j in range(0, self.utilities.get_default_bit_number()):
                self.rotate_left_testframe(self.numbers[i], j)
