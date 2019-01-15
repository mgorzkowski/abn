#!/usr/bin/env python
import sys
sys.path.append('../wrappers')

import unittest
import ctypes

from abn_wrapper import ABN
from utilities import Utilities

class ArithmeticOperations(unittest.TestCase):

    def setUp(self):
        try:
            self.abn = ABN('../bin/libabn.so')
        except:
            print "Cannot load share object. Make sure that libabn.so exists in the porper place"
            sys.exit(-1)
        self.utilities = Utilities(self.abn)
        self.numbers = tuple(self.utilities.get_test_numbers())

    def tearDown(self):
        self.utilities.free_test_numbers(self.numbers)

    def print_numbers(self, a):
        for i in a:
            print str(self.utilities.abn_to_long(i))
    
    def compare(self, a, b, sign_position='default', signed=False):
        return self.assertEqual(self.utilities.normalize_to_compare(a, sign_position), self.utilities.normalize_to_compare(b, sign_position))

    # test frames

    def add_testframe(self, a, b):
        a = self.abn.create_copy(a)
        b = self.abn.create_copy(b)
        pa = self.utilities.abn_to_long(a)
        self.abn.add(a, b)
        a = self.utilities.abn_to_long(a)
        b = self.utilities.abn_to_long(b)
        self.compare(pa+b, a)

    def sum_testframe(self, a, b):
        a = self.abn.create_copy(a)
        b = self.abn.create_copy(b)
        c = self.abn.create(self.utilities.volume_of_test_numbers+1)
        self.abn.reset(c)
        self.abn.sum(c, a, b)
        a = self.utilities.abn_to_long(a)
        b = self.utilities.abn_to_long(b)
        c = self.utilities.abn_to_long(c)
        self.compare(a+b, c, sign_position=160)

    def incrementation_testframe(self, a):
        a = self.abn.create_copy(a)
        b = self.utilities.abn_to_long(a)
        self.abn.inc(a)
        a = self.utilities.abn_to_long(a)
        self.compare(a, b+1)

    def decrementation_testframe(self, a):
        a = self.abn.create_copy(a)
        b = self.utilities.abn_to_long(a)
        self.abn.dec(a)
        a = self.utilities.abn_to_long(a)
        self.compare(a, b-1, sign_position=128)

    def negation_testframe(self, a):
        a = self.abn.create_copy(a)
        pa = self.utilities.abn_to_signed_long(a)
        self.abn.neg(a)
        pa = -pa
        a = self.utilities.abn_to_signed_long(a)
        self.compare(a, pa)

    def multiplication_testframe(self, a, b):
        a = self.abn.create_copy(a)
        b = self.abn.create_copy(b)
        c = self.abn.create(2*self.utilities.volume_of_test_numbers)
        self.abn.reset(c)
        self.abn.mul(c, a, b)
        a = self.utilities.abn_to_long(a)
        b = self.utilities.abn_to_long(b)
        c = self.utilities.abn_to_long(c)
        sign_position = 2 * 8 * self.abn.size_of_abn_unit * self.utilities.volume_of_test_numbers
        self.compare(a*b, c, sign_position=sign_position)

    def sign_multiplication_testframe(self, a, b):
        a = self.abn.create_copy(a)
        b = self.abn.create_copy(b)
        c = self.abn.create(2*self.utilities.volume_of_test_numbers)
        self.abn.reset(c)
        self.abn.smul(c, a, b)
        a = self.utilities.abn_to_signed_long(a)
        b = self.utilities.abn_to_signed_long(b)
        print "\n\n\n\n"
        print "a = " + str(a)
        print "b = " + str(b)
        sign_position = 2 * 8 * self.abn.size_of_abn_unit * self.utilities.volume_of_test_numbers - 1
        c = self.utilities.abn_to_signed_long(c, sign_position=sign_position)
        d = self.utilities.normalize_to_compare(a*b, 255)
        #@c = self.utilities.normalize_to_compare(c, 255)
        print "\n"
        print "a*b " + str(a*b) + "   -   " +  hex(a*b)
        print "c " + str(c) + "   -   " + hex(c)
        print "d " + str(d) + "   -   " + hex(d)
        self.compare(a*b, c, sign_position=sign_position, signed=True)

    def is_positive_testframe(self, a):
        a = self.abn.create_copy(a)
        result = self.abn.is_positive(a)
        self.compare(result, True)

    def is_negative_testframe(self, a):
        a = self.abn.create_copy(a)
        result = self.abn.is_negative(a)
        self.compare(result, True)

    def absolute_value_testframe(self, a):
        a = self.abn.create_copy(a)
        pa = abs(self.utilities.abn_to_signed_long(a))
        self.abn.abs(a)
        a = self.utilities.abn_to_signed_long(a)
        self.compare(a,pa)

    # Test Cases

    def test_show_numbers(self):
        print "\n"
        for i in range(0, len(self.numbers)):
            print str(i) + ') 0x' + str(self.abn.to_string(self.numbers[i]))

    def test_addition(self):
        for i in range(0, len(self.numbers)):
            for j in range(0, len(self.numbers)):
                self.add_testframe(self.numbers[i], self.numbers[j])

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
                try:
                    self.sign_multiplication_testframe(self.numbers[i], self.numbers[j])
                except:
                    #print ">>> i = 0x" +  self.abn.to_string(self.numbers[i])
                    #print ">>> j = 0x" +  self.abn.to_string(self.numbers[j])
                    raise
    def etest_is_positive(self):
        self.is_positive_testframe(self.numbers[0])

    def etest_in_negative(self):
        self.is_negative_testframe(self.numbers[1])

    def etest_absolute_value(self):
        self.absolute_value_testframe(self.numbers[0])
        self.absolute_value_testframe(self.numbers[1])