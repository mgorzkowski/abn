#!/usr/bin/env python
import sys
sys.path.append('../wrappers/python')

import unittest
import ctypes

from abn_wrapper import ABN
from utilities import Utilities

class Add_tests(unittest.TestCase):

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
    def add_testframe(self, a, b):
        temp = self.abn.create_copy(a)
        a = self.abn.create(self.utilities.volume_of_test_numbers + 1)
        b = self.abn.create_copy(b)
        self.abn.copy(a, temp)
        pa = self.utilities.abn_to_long(a)
        self.abn.add(a, b)
        a = self.utilities.abn_to_long(a)
        b = self.utilities.abn_to_long(b)
        self.assertEqual(pa+b, a)

    def test_addition(self):
        for i in range(0, len(self.numbers)):
            for j in range(0, len(self.numbers)):
                self.add_testframe(self.numbers[i], self.numbers[j])