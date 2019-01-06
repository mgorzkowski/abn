#!/usr/bin/env python
import sys
sys.path.append('../wrappers')

import unittest
import ctypes

from abn_wrapper import ABN
from utilities import Utilities

class ArithmeticFunctions(unittest.TestCase):

    def setUp(self):
        try:
            self.abn = ABN('../bin/libabn.so')
        except:
            print "Cannot load share object. Make sure that libabn.so exists in the porper place"
            sys.exit(-1)
        self.utilities = Utilities(self.abn)
        self.numbers = tuple(self.utilities.get_test_numbers())

    def test_simple_addition(self):
        a = self.abn.create_copy(self.numbers[0])
        b = self.abn.create_copy(self.numbers[1])
        c = self.abn.create(self.utilities.volume_of_test_numbers+1)
        self.abn.reset(c)
        self.abn.add(c, a, b)
        a = self.utilities.abn_to_long(a)
        b = self.utilities.abn_to_long(b)
        c = self.utilities.abn_to_long(c)
        self.assertEqual(a+b, c)

    def test_simple_incrementation(self):
        a = self.abn.create_copy(self.numbers[0])
        b = self.abn.create_copy(a)
        self.abn.inc(a)
        a = self.utilities.abn_to_long(a)
        b = self.utilities.abn_to_long(b)
        self.assertEqual(a, b+1)

    def test_simple_decrementation(self):
        a = self.abn.create_copy(self.numbers[0])
        b = self.abn.create_copy(a)
        self.abn.dec(a)
        a = self.utilities.abn_to_long(a)
        b = self.utilities.abn_to_long(b)
        self.assertEqual(a, b-1)

    def test_simple_negation(self):
        """ Try to change it """
        a = self.abn.create_copy(self.numbers[0])
        b = self.abn.create_copy(a)
        self.abn.neg(a)
        self.abn.neg(a)
        pa = self.utilities.abn_to_long(a)
        pb = self.utilities.abn_to_long(b)
        self.assertEqual(pa, pb)
        self.abn.neg(a)
        pa = int(self.utilities.shex(self.utilities.abn_to_long(a))[:-1], base=16)
        pb = int(self.utilities.shex(self.utilities.abn_to_long(b))[:-1], base=16)
        self.assertEqual(pb, pa)

    def test_simple_in_positive(self):
        a = self.abn.create_copy(self.numbers[0])
        self.abn.set_byte(a, 0x7F, 4*self.utilities.volume_of_test_numbers-1)
        result = self.abn.is_positive(a)
        self.assertEqual(result, True)

    def test_simple_in_negative(self):
        a = self.abn.create_copy(self.numbers[0])
        self.abn.set_byte(a, 0x80, 4*self.utilities.volume_of_test_numbers-1)
        result = self.abn.is_negative(a)
        self.assertEqual(result, True)

    def test_simple_multiplication(self):
        a = self.abn.create_copy(self.numbers[0])
        b = self.abn.create_copy(self.numbers[1])
        c = self.abn.create(2*self.utilities.volume_of_test_numbers)
        self.abn.mul(c, a, b)
        a = self.utilities.abn_to_long(a)
        b = self.utilities.abn_to_long(b)
        c = self.utilities.abn_to_long(c)
        self.assertEqual(a*b, c)

    def test_simple_sign_multipication(self):
        """ Try to change it """
        self.assertEqual(0,0)

    def tearDown(self):
        self.utilities.free_test_numbers(self.numbers)
