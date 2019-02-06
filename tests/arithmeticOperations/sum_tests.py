#!/usr/bin/env python
import sys
sys.path.append('../wrappers/python')

import unittest
import ctypes

from abn_wrapper import ABN
from utilities import *

class Sum_tests(OperationTestCase):

    #Testframes
    def sum_testframe(self, a, b):
        a = self.abn.create_copy(a)
        b = self.abn.create_copy(b)
        c = self.abn.create(self.utilities.volume_of_test_numbers+1)
        self.abn.reset(c)
        self.abn.sum(c, a, b)
        a = self.utilities.abn_to_long(a)
        b = self.utilities.abn_to_long(b)
        c = self.utilities.abn_to_long(c)
        self.assertEqual(a+b, c)

    def test_summation(self):
        for i in range(0, len(self.numbers)):
            for j in range(0, len(self.numbers)):
                self.sum_testframe(self.numbers[i], self.numbers[j])