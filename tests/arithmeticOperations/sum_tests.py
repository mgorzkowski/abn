#!/usr/bin/env python
import sys
sys.path.append('../wrappers/python')

import unittest
import ctypes

from abn_wrapper import ABN
from utilities import Utilities

class Sum_tests(unittest.TestCase):

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
    def sum_testframe(self, a, b):
        a = self.abn.create_copy(a)
        b = self.abn.create_copy(b)
        c = self.abn.create(self.utilities.volume_of_test_numbers+1)
        self.abn.reset(c)
        self.abn.sum(c, a, b)
        a = self.utilities.abn_to_long(a)
        b = self.utilities.abn_to_long(b)
        c = self.utilities.abn_to_long(c)
        self.assertEqual(a+b, c)

    def test_summation(self):
        for i in range(0, len(self.numbers)):
            for j in range(0, len(self.numbers)):
                self.sum_testframe(self.numbers[i], self.numbers[j])