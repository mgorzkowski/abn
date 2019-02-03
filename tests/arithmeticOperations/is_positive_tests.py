#!/usr/bin/env python
import sys
sys.path.append('../wrappers/python')

import unittest
import ctypes

from abn_wrapper import ABN
from utilities import Utilities

class Is_positive_tests(unittest.TestCase):

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
    def is_positive_testframe(self, a):
        a = self.abn.create_copy(a)
        result = self.abn.is_positive(a)
        a = self.utilities.abn_to_signed_long(a, self.utilities.get_default_bit_number())
        self.assertEqual(result, a>=0)

    def test_is_positive(self):
        for i in range(0, len(self.numbers)):
            self.is_positive_testframe(self.numbers[i])
