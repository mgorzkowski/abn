#!/usr/bin/env python
import sys
sys.path.append('../wrappers/python')

import unittest
import ctypes

from abn_wrapper import ABN
from utilities import Utilities

class Add_unit_tests(unittest.TestCase):

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
    def add_unit_testframe(self, a, b):
        temp = self.abn.create_copy(a)
        a = self.abn.create(self.utilities.volume_of_test_numbers + 1)
        self.abn.copy(a, temp)
        pa = self.utilities.abn_to_long(a)
        self.abn.adu(a, b)
        a = self.utilities.abn_to_long(a)
        self.assertEqual(pa+b, a)

    def test_unit_addition(self):
        for i in range(0, len(self.numbers)):
            for j in [0, 1, 2, (1<<self.abn.size_of_abn_unit)-2, (1<<self.abn.size_of_abn_unit)-1]:
                self.add_unit_testframe(self.numbers[i], j)

    