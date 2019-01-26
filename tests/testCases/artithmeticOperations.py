#!/usr/bin/env python
import sys
sys.path.append('../wrappers/python')

import unittest
import ctypes

from abn_wrapper import ABN
from utilities import Utilities

class ArithmeticOperations(unittest.TestCase):

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

    # move this methods to utilities

    def print_numbers(self, a):
        for i in a:
            print str(self.utilities.abn_to_long(i))

    def get_default_bit_number(self):
        return 8 * self.abn.size_of_abn_unit * self.utilities.volume_of_test_numbers

    def normalize(self, a, bits):
        return a % (1<<bits)

    # test frames

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

    def add_unit_testframe(self, a, b):
        temp = self.abn.create_copy(a)
        a = self.abn.create(self.utilities.volume_of_test_numbers + 1)
        self.abn.copy(a, temp)
        pa = self.utilities.abn_to_long(a)
        self.abn.adu(a, b)
        a = self.utilities.abn_to_long(a)
        self.assertEqual(pa+b, a)

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

    def incrementation_testframe(self, a):
        a = self.abn.create_copy(a)
        b = self.utilities.abn_to_long(a)
        self.abn.inc(a)
        a = self.utilities.abn_to_long(a)
        b = self.normalize(b+1, self.get_default_bit_number())
        self.assertEqual(a, b)

    def decrementation_testframe(self, a):
        a = self.abn.create_copy(a)
        b = self.utilities.abn_to_long(a)
        self.abn.dec(a)
        a = self.utilities.abn_to_long(a)
        b = self.normalize(b-1, self.get_default_bit_number())
        self.assertEqual(a, b)

    def negation_testframe(self, a):
        a = self.abn.create_copy(a)
        pa = - self.utilities.abn_to_signed_long(a, self.get_default_bit_number())
        self.abn.neg(a)
        a = self.utilities.abn_to_signed_long(a, self.get_default_bit_number())
        if pa == 1<<(self.get_default_bit_number() - 1):
            pass
        else:
            self.assertEqual(a, pa)

    def multiplication_testframe(self, a, b):
        a = self.abn.create_copy(a)
        b = self.abn.create_copy(b)
        c = self.abn.create(2*self.utilities.volume_of_test_numbers)
        self.abn.reset(c)
        self.abn.mul(c, a, b)
        a = self.utilities.abn_to_long(a)
        b = self.utilities.abn_to_long(b)
        c = self.utilities.abn_to_long(c)
        self.assertEqual(a*b, c)

    def sign_multiplication_testframe(self, a, b):
        a = self.abn.create_copy(a)
        b = self.abn.create_copy(b)
        c = self.abn.create(2*self.utilities.volume_of_test_numbers)
        self.abn.reset(c)
        self.abn.smul(c, a, b)
        a = self.utilities.abn_to_signed_long(a, self.get_default_bit_number())
        b = self.utilities.abn_to_signed_long(b, self.get_default_bit_number())
        c = self.utilities.abn_to_signed_long(c, 2*self.get_default_bit_number())
        temp = self.normalize(a*b, 2*self.get_default_bit_number())
        c = self.normalize(c, 2*self.get_default_bit_number())
        self.assertEqual(temp, c)

    def is_positive_testframe(self, a):
        a = self.abn.create_copy(a)
        result = self.abn.is_positive(a)
        a = self.utilities.abn_to_signed_long(a, self.get_default_bit_number())
        self.assertEqual(result, a>=0)

    def is_negative_testframe(self, a):
        a = self.abn.create_copy(a)
        result = self.abn.is_negative(a)
        a = self.utilities.abn_to_signed_long(a, self.get_default_bit_number())
        self.assertEqual(result, a<0)

    def absolute_value_testframe(self, a):
        a = self.abn.create_copy(a)
        pa = abs(self.utilities.abn_to_signed_long(a, self.get_default_bit_number()))
        self.abn.abs(a)
        a = self.utilities.abn_to_signed_long(a, self.get_default_bit_number())
        if pa == 1<<(self.get_default_bit_number() - 1):
            self.assertEqual(a,-pa)
        else:
            self.assertEqual(a,pa)

    # Test Cases

    def test_addition(self):
        for i in range(0, len(self.numbers)):
            for j in range(0, len(self.numbers)):
                self.add_testframe(self.numbers[i], self.numbers[j])

    def test_unit_addition(self):
        for i in range(0, len(self.numbers)):
            for j in [0, 1, 2, (1<<self.abn.size_of_abn_unit)-2, (1<<self.abn.size_of_abn_unit)-1]:
                self.add_unit_testframe(self.numbers[i], j)

    def test_summation(self):
        for i in range(0, len(self.numbers)):
            for j in range(0, len(self.numbers)):
                self.sum_testframe(self.numbers[i], self.numbers[j])

    def test_incrementation(self):
        for i in range(0, len(self.numbers)):
            self.incrementation_testframe(self.numbers[i])

    def test_decrementation(self):
        for i in range(0, len(self.numbers)):
            self.decrementation_testframe(self.numbers[i])

    def test_negation(self):
        for i in range(0, len(self.numbers)):
            self.negation_testframe(self.numbers[i])

    def test_multiplication(self):
        for i in range(0, len(self.numbers)):
            for j in range(0, len(self.numbers)):
                self.multiplication_testframe(self.numbers[i], self.numbers[j])

    def test_sign_multipication(self):
        for i in range(0, len(self.numbers)):
            for j in range(0, len(self.numbers)):
                self.sign_multiplication_testframe(self.numbers[i], self.numbers[j])

    def test_is_positive(self):
        for i in range(0, len(self.numbers)):
            self.is_positive_testframe(self.numbers[i])

    def test_is_negative(self):
        for i in range(0, len(self.numbers)):
            self.is_negative_testframe(self.numbers[i])

    def test_absolute_value(self):
        for i in range(0, len(self.numbers)):
            self.absolute_value_testframe(self.numbers[i])