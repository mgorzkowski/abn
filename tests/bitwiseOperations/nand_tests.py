#!/usr/bin/env python
import sys
sys.path.append('../wrappers/python')

import unittest
import ctypes

from abn_wrapper import ABN
from utilities import *

class Nand_tests(OperationTestCase):

    #Testframe
    def nand_testframe(self, a, b):
        a = self.abn.create_copy(a)
        b = self.abn.create_copy(b)
        c = self.abn.create(self.utilities.volume_of_test_numbers)
        self.abn.reset(c)
        self.abn.bit_nand(c, b, a)
        pa = self.utilities.abn_to_long(a)
        pb = self.utilities.abn_to_long(b)
        pc = self.utilities.abn_to_long(c)
        self.assertEqual(self.utilities.bit_not(pa & pb), pc)

    def test_bitwise_nand(self):
        for i in range(0, len(self.numbers)):
            for j in range(0, len(self.numbers)):
                self.nand_testframe(self.numbers[i], self.numbers[j])

