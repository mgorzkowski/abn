#!/usr/bin/env python
import sys
sys.path.append('../wrappers')

from utilities import *

class ArithmeticFunctions(unittest.TestCase):

    def setUp(self):
        self.numbers = get_test_numbers()

    def test_simple_addition(self):
        a = abn.create_copy(self.numbers[0])
        b = abn.create_copy(self.numbers[1])
        c = abn.create(volume_of_test_numbers+1)
        abn.add(c, a, b)
        a = abn_to_long(a)
        b = abn_to_long(b)
        c = abn_to_long(c)
        self.assertEqual(c, a+b)

    def test_simple_incrementation(self):
        a = abn.create_copy(self.numbers[0])
        b = abn.create_copy(a)
        abn.inc(a)
        a = abn_to_long(a)
        b = abn_to_long(b)
        self.assertEqual(a, b+1)

    def test_simple_decrementation(self):
        a = abn.create_copy(self.numbers[0])
        b = abn.create_copy(a)
        abn.dec(a)
        a = abn_to_long(a)
        b = abn_to_long(b)
        self.assertEqual(a, b-1)

    def test_simple_negation(self):
        """ Try to change it """
        a = abn.create_copy(self.numbers[0])
        b = abn.create_copy(a)
        abn.neg(a)
        abn.neg(a)
        pa = abn_to_long(a)
        pb = abn_to_long(b)
        self.assertEqual(pa, pb)
        abn.neg(a)
        pa = int(shex(abn_to_long(a))[:-1], base=16)
        pb = int(shex(abn_to_long(b))[:-1], base=16)
        self.assertEqual(pb, pa)

    def test_simple_in_positive(self):
        a = abn.create_copy(self.numbers[0])
        abn.set_byte(a, 0x7F, 4*volume_of_test_numbers-1)
        result = abn.is_positive(a)
        self.assertEqual(result, True)

    def test_simple_in_negative(self):
        a = abn.create_copy(self.numbers[0])
        abn.set_byte(a, 0x80, 4*volume_of_test_numbers-1)
        result = abn.is_negative(a)
        self.assertEqual(result, True)

    def test_simple_multiplication(self):
        a = abn.create_copy(self.numbers[0])
        b = abn.create_copy(self.numbers[1])
        c = abn.create(2*volume_of_test_numbers)
        abn.mul(c, a, b)
        pa = abn_to_long(a)
        pb = abn_to_long(b)
        pc = abn_to_long(c)
        self.assertEqual(pc, pa*pb)

    def test_simple_sign_multipication(self):
        """ Try to change it """
        self.assertEqual(0,0)

    def tearDown(self):
        free_test_numbers(self.numbers)
