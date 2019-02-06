#!/usr/bin/env python
import sys
sys.path.append('../wrappers/python')

import unittest
import ctypes

from abn_wrapper import ABN
from utilities import *

class Add_tests(OperationTestCase):

    #Testframes
    def add_testframe(self, a, b):
        temp = self.abn.create_copy(a)
        a = self.abn.create(self.utilities.volume_of_test_numbers + 1)
        b = self.abn.create_copy(b)
        self.abn.copy(a, temp)
        pa = self.utilities.abn_to_long(a)
        self.abn.add(a, b)
        a = self.utilities.abn_to_long(a)
        b = self.utilities.abn_to_long(b)
        self.assertEqual(pa+b, a)

    def test_addition(self):
        for i in range(0, len(self.numbers)):
            for j in range(0, len(self.numbers)):
                self.add_testframe(self.numbers[i], self.numbers[j])