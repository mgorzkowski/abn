#!/usr/bin/env python
import sys
sys.path.append('../wrappers/python')

import unittest
import ctypes

from abn_wrapper import ABN
from utilities import Utilities

class BitOperations(unittest.TestCase):

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

    # test frames

    def and_testframe(self, a, b):
        a = self.abn.create_copy(a)
        b = self.abn.create_copy(b)
        c = self.abn.create(self.utilities.volume_of_test_numbers)
        self.abn.reset(c)
        self.abn.bit_and(c, b, a)
        pa = self.utilities.abn_to_long(a)
        pb = self.utilities.abn_to_long(b)
        pc = self.utilities.abn_to_long(c)
        self.assertEqual(pa & pb, pc)

    def or_testframe(self, a, b):
        a = self.abn.create_copy(a)
        b = self.abn.create_copy(b)
        c = self.abn.create(self.utilities.volume_of_test_numbers)
        self.abn.reset(c)
        self.abn.bit_or(c, b, a)
        pa = self.utilities.abn_to_long(a)
        pb = self.utilities.abn_to_long(b)
        pc = self.utilities.abn_to_long(c)
        self.assertEqual(pa | pb, pc)

    def not_testframe(self, a):
        a = self.abn.create_copy(a)
        b = self.abn.create_copy(a)
        self.abn.bit_not(b)
        pa = self.utilities.abn_to_long(a)
        pb = self.utilities.abn_to_long(b)
        self.assertEqual(self.utilities.bit_not(pa), pb)

    def xor_testframe(self, a, b):
        a = self.abn.create_copy(a)
        b = self.abn.create_copy(b)
        c = self.abn.create(self.utilities.volume_of_test_numbers)
        self.abn.reset(c)
        self.abn.bit_xor(c, b, a)
        pa = self.utilities.abn_to_long(a)
        pb = self.utilities.abn_to_long(b)
        pc = self.utilities.abn_to_long(c)
        self.assertEqual(pa ^ pb, pc)

    def nand_testframe(self, a, b):
        a = self.abn.create_copy(a)
        b = self.abn.create_copy(b)
        c = self.abn.create(self.utilities.volume_of_test_numbers)
        self.abn.reset(c)
        self.abn.bit_nand(c, b, a)
        pa = self.utilities.abn_to_long(a)
        pb = self.utilities.abn_to_long(b)
        pc = self.utilities.abn_to_long(c)
        self.assertEqual(self.utilities.bit_not(pa & pb), pc)

    def nor_testframe(self, a, b):
        a = self.abn.create_copy(a)
        b = self.abn.create_copy(b)
        c = self.abn.create(self.utilities.volume_of_test_numbers)
        self.abn.reset(c)
        self.abn.bit_nor(c, b, a)
        pa = self.utilities.abn_to_long(a)
        pb = self.utilities.abn_to_long(b)
        pc = self.utilities.abn_to_long(c)
        self.assertEqual(self.utilities.bit_not(pa | pb), pc)

    def shift_left_testframe(self, a, shift):
        a = self.abn.create_copy(a)
        b = self.abn.create_copy(a)
        self.abn.shift_left(a, shift)
        pa = self.utilities.abn_to_long(a)
        pb = self.utilities.abn_to_long(b)
        self.assertEqual(pa, self.utilities.normalize(pb<<shift, self.utilities.get_default_bit_number()))

    def shift_right_testframe(self, a, shift):
        a = self.abn.create_copy(a)
        b = self.abn.create_copy(a)
        self.abn.shift_right(a, shift)
        pa = self.utilities.abn_to_long(a)
        pb = self.utilities.abn_to_long(b)
        self.assertEqual(pa, self.utilities.normalize(pb>>shift, self.utilities.get_default_bit_number()))

    def rotate_left_testframe(self, a, shift):
        a = self.abn.create_copy(a)
        b = self.abn.create_copy(a)
        self.abn.rotate_left(a, shift)
        pa = self.utilities.abn_to_long(a)
        pb = self.utilities.abn_to_long(b)
        pb = self.utilities.normalize(pb<<shift, self.utilities.get_default_bit_number()) + self.utilities.normalize(pb>>(self.utilities.get_default_bit_number() - shift), self.utilities.get_default_bit_number())
        self.assertEqual(pa, pb)

    def rotate_right_testframe(self, a, shift):
        a = self.abn.create_copy(a)
        b = self.abn.create_copy(a)
        self.abn.rotate_right(a, shift)
        pa = self.utilities.abn_to_long(a)
        pb = self.utilities.abn_to_long(b)
        pb = self.utilities.normalize(pb>>shift, self.utilities.get_default_bit_number()) + self.utilities.normalize(pb<<(self.utilities.get_default_bit_number() - shift), self.utilities.get_default_bit_number())        
        self.assertEqual(pa, pb)

    # Test Cases

    def test_bitwise_and(self):
        for i in range(0, len(self.numbers)):
            for j in range(0, len(self.numbers)):
                self.and_testframe(self.numbers[i], self.numbers[j])

    def test_bitwise_or(self):
        for i in range(0, len(self.numbers)):
            for j in range(0, len(self.numbers)):
                self.or_testframe(self.numbers[i], self.numbers[j])

    def test_bitwise_not(self):
        for i in range(0, len(self.numbers)):
            self.not_testframe(self.numbers[i])

    def test_bitwise_xor(self):
        for i in range(0, len(self.numbers)):
            for j in range(0, len(self.numbers)):
                self.xor_testframe(self.numbers[i], self.numbers[j])

    def test_bitwise_nand(self):
        for i in range(0, len(self.numbers)):
            for j in range(0, len(self.numbers)):
                self.nand_testframe(self.numbers[i], self.numbers[j])

    def test_bitwise_nor(self):
        for i in range(0, len(self.numbers)):
            for j in range(0, len(self.numbers)):
                self.nor_testframe(self.numbers[i], self.numbers[j])

    def test_bitwise_shift_left(self):
        for i in range(0, len(self.numbers)):
            for j in range(0, self.utilities.get_default_bit_number()):
                self.shift_left_testframe(self.numbers[i], j)

    def test_bitwise_shift_right(self):
        for i in range(0, len(self.numbers)):
            for j in range(0, self.utilities.get_default_bit_number()):
                self.shift_right_testframe(self.numbers[i], j)

    def test_bitwise_rotate_left(self):
        for i in range(0, len(self.numbers)):
            for j in range(0, self.utilities.get_default_bit_number()):
                self.rotate_left_testframe(self.numbers[i], j)

    def test_bitwise_rotate_right(self):
        for i in range(0, len(self.numbers)):
            for j in range(0, self.utilities.get_default_bit_number()):
                self.rotate_right_testframe(self.numbers[i], j)
