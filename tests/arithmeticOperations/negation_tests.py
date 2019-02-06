#!/usr/bin/env python
import sys
sys.path.append('../wrappers/python')

import unittest
import ctypes

from abn_wrapper import ABN
from utilities import *

class Negation_tests(OperationTestCase):

    #Testframes
    def negation_testframe(self, a):
        a = self.abn.create_copy(a)
        pa = - self.utilities.abn_to_signed_long(a, self.utilities.get_default_bit_number())
        self.abn.neg(a)
        a = self.utilities.abn_to_signed_long(a, self.utilities.get_default_bit_number())
        if pa == 1<<(self.utilities.get_default_bit_number() - 1):
            pass
        else:
            self.assertEqual(a, pa)

    def test_negation(self):
        for i in range(0, len(self.numbers)):
            self.negation_testframe(self.numbers[i])