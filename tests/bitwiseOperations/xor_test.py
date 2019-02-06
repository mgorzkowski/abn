#!/usr/bin/env python
import sys
sys.path.append('../wrappers/python')

import unittest
import ctypes

from abn_wrapper import ABN
from utilities import *

class Xor_tests(OperationTestCase):

    #Testframe
    def xor_testframe(self, a, b):
        a = self.abn.create_copy(a)
        b = self.abn.create_copy(b)
        c = self.abn.create(self.utilities.volume_of_test_numbers)
        self.abn.reset(c)
        self.abn.bit_xor(c, b, a)
        pa = self.utilities.abn_to_long(a)
        pb = self.utilities.abn_to_long(b)
        pc = self.utilities.abn_to_long(c)
        self.assertEqual(pa ^ pb, pc)

    def test_bitwise_xor(self):
        for i in range(0, len(self.numbers)):
            for j in range(0, len(self.numbers)):
                self.xor_testframe(self.numbers[i], self.numbers[j])
