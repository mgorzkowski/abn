#!/usr/bin/env python
import sys
sys.path.append('../wrappers/python')

import unittest
import ctypes

from abn_wrapper import ABN
from utilities import *

class Sub_unit_tests(OperationTestCase):

    #Testframes
    def sub_unit_testframe(self, a, b):
        temp = self.abn.create_copy(a)
        a = self.abn.create(self.utilities.volume_of_test_numbers)
        self.abn.copy(a, temp)
        pa = self.utilities.abn_to_long(a)
        self.abn.subu(a, b)
        a = self.utilities.abn_to_long(a)
        self.assertEqual(self.utilities.normalize(pa-b, self.utilities.get_default_bit_number()), a)

    def test_unit_subtraction(self):
        for i in range(0, len(self.numbers)):
            for j in [0, 1, 2, (1<<(self.abn.size_of_abn_unit*8))-2, (1<<(self.abn.size_of_abn_unit*8))-1]:
                self.sub_unit_testframe(self.numbers[i], j)

    