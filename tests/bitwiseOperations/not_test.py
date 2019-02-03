#!/usr/bin/env python
import sys
sys.path.append('../wrappers/python')

import unittest
import ctypes

from abn_wrapper import ABN
from utilities import Utilities

class Not_tests(unittest.TestCase):

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