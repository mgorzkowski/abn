#!/usr/bin/env python
import sys
sys.path.append('../wrappers/python')

import unittest
import ctypes

from abn_wrapper import ABN
from utilities import *

class Multiplication_by_unit_tests(OperationTestCase):

    #Testframes
    def multiplication_by_unit_testframe(self, a, value):
        a = self.abn.create_copy(a)
        b = self.abn.create_copy(a)
        self.abn.reset(b)
        self.abn.mulu(b, a, value)
        a = self.utilities.abn_to_long(a)
        b = self.utilities.abn_to_long(b)
        self.assertEqual(b, self.utilities.normalize(a*value, self.utilities.get_default_bit_number()))

    def test_multiplication_by_unit(self):
        for i in range(0, len(self.numbers)):
            for j in [0, 1, 2, (1<<(self.abn.size_of_abn_unit*8))-2, (1<<(self.abn.size_of_abn_unit*8))-1]:
                self.multiplication_by_unit_testframe(self.numbers[i], j)
