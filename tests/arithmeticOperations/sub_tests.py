#!/usr/bin/env python
import sys
sys.path.append('../wrappers/python')

import unittest
import ctypes

from abn_wrapper import ABN
from utilities import *

class Sub_tests(OperationTestCase):

    #Testframes
    def sub_testframe(self, a, b):
        temp = self.abn.create_copy(a)
        a = self.abn.create(self.utilities.volume_of_test_numbers)
        b = self.abn.create_copy(b)
        self.abn.copy(a, temp)
        pa = self.utilities.abn_to_long(a)
        self.abn.sub(a, b)
        a = self.utilities.abn_to_long(a)
        b = self.utilities.abn_to_long(b)
        self.assertEqual(self.utilities.normalize(pa-b, self.utilities.get_default_bit_number()), a)

    def test_subtraction(self):
        for i in range(0, len(self.numbers)):
            for j in range(0, len(self.numbers)):
                self.sub_testframe(self.numbers[i], self.numbers[j])
