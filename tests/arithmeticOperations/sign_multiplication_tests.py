#!/usr/bin/env python
import sys
sys.path.append('../wrappers/python')

import unittest
import ctypes

from abn_wrapper import ABN
from utilities import *

class Sign_multiplication_tests(OperationTestCase):

    #testframes
    def sign_multiplication_testframe(self, a, b):
        a = self.abn.create_copy(a)
        b = self.abn.create_copy(b)
        c = self.abn.create(2*self.utilities.volume_of_test_numbers)
        self.abn.reset(c)
        self.abn.smul(c, a, b)
        a = self.utilities.abn_to_signed_long(a, self.utilities.get_default_bit_number())
        b = self.utilities.abn_to_signed_long(b, self.utilities.get_default_bit_number())
        c = self.utilities.abn_to_signed_long(c, 2*self.utilities.get_default_bit_number())
        temp = self.utilities.normalize(a*b, 2*self.utilities.get_default_bit_number())
        c = self.utilities.normalize(c, 2*self.utilities.get_default_bit_number())
        self.assertEqual(temp, c)

    def test_sign_multipication(self):
        for i in range(0, len(self.numbers)):
            for j in range(0, len(self.numbers)):
                self.sign_multiplication_testframe(self.numbers[i], self.numbers[j])