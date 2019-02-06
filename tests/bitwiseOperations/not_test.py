#!/usr/bin/env python
import sys
sys.path.append('../wrappers/python')

import unittest
import ctypes

from abn_wrapper import ABN
from utilities import *

class Not_tests(OperationTestCase):

    #Testframe
    def not_testframe(self, a):
        a = self.abn.create_copy(a)
        b = self.abn.create_copy(a)
        self.abn.bit_not(b)
        pa = self.utilities.abn_to_long(a)
        pb = self.utilities.abn_to_long(b)
        self.assertEqual(self.utilities.bit_not(pa), pb)

    def test_bitwise_not(self):
        for i in range(0, len(self.numbers)):
            self.not_testframe(self.numbers[i])