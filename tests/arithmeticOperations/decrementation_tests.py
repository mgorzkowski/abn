#!/usr/bin/env python
import sys
sys.path.append('../wrappers/python')

import unittest
import ctypes

from abn_wrapper import ABN
from utilities import Utilities

class Decrementation_tests(unittest.TestCase):

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
    def decrementation_testframe(self, a):
        a = self.abn.create_copy(a)
        b = self.utilities.abn_to_long(a)
        self.abn.dec(a)
        a = self.utilities.abn_to_long(a)
        b = self.utilities.normalize(b-1, self.utilities.get_default_bit_number())
        self.assertEqual(a, b)

    def test_decrementation(self):
        for i in range(0, len(self.numbers)):
            self.decrementation_testframe(self.numbers[i])