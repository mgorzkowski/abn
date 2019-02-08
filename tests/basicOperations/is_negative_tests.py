#!/usr/bin/env python
import sys
sys.path.append('../wrappers/python')

import unittest
import ctypes

from abn_wrapper import ABN
from utilities import *

class Is_negative_tests(OperationTestCase):

    #Testframes
    def is_negative_testframe(self, a):
        a = self.abn.create_copy(a)
        result = self.abn.is_negative(a)
        a = self.utilities.abn_to_signed_long(a, self.utilities.get_default_bit_number())
        self.assertEqual(result, a<0)

    def test_is_negative(self):
        for i in range(0, len(self.numbers)):
            self.is_negative_testframe(self.numbers[i])