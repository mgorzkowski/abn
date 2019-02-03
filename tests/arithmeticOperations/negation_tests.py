#!/usr/bin/env python
import sys
sys.path.append('../wrappers/python')

import unittest
import ctypes

from abn_wrapper import ABN
from utilities import Utilities

class Negation_tests(unittest.TestCase):

    def setUp(self):
        try:
            self.abn = ABN('../bin/shared/libabn.so')
        except:
            print "Cannot load share object. Make sure that libabn.so exists in the porper place and API is the same"
            sys.exit(-1)
        self.utilities = Utilities(self.abn)
        self.numbers = tuple(self.utilities.get_test_numbers())

    def tearDown(self):
        self.utilities.free_test_numbers(self.numbers)

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