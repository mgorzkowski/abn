#!/usr/bin/env python
import unittest
import traceback
import ctypes
import sys

sys.path.append('../wrappers')
from abn_wrapper import ABN

class ArithmeticFunctions(unittest.TestCase):

    def setUp(self):
        self.VOLUME = 4
        self.abn = ABN('../bin/libabn.so')
        self.number1 = self.abn.create(self.VOLUME)
        self.number2 = self.abn.create(self.VOLUME)
        self.abn.reset(self.number1)
        self.abn.reset(self.number2)
        for i in range(0, 4*self.VOLUME):
            self.abn.set_byte(self.number1, 1835*(i+1)%256, i)
            self.abn.set_byte(self.number2, 3016*(i+1)%256, i)

    def test_simple_addition(self):
        a = self.abn.create_copy(self.number1)
        b = self.abn.create_copy(self.number2)
        c = self.abn.create(1+self.VOLUME)
        self.abn.reset(c)
        pa = int('0x' + self.abn.to_string(a), base=16)
        pb = int('0x' + self.abn.to_string(b), base=16)
        self.abn.add(c, a, b)
        pc = int('0x' + self.abn.to_string(c), base=16)
        print hex(pa)
        print hex(pb)
        print hex(pc)
        print hex(pa+pb)
        self.assertEqual(pc, pa+pb)

    def test_simple_multiplication(self):
        a = self.abn.create_copy(self.number1)
        b = self.abn.create_copy(self.number2)
        c = self.abn.create(2*self.VOLUME)
        pa = int('0x' + self.abn.to_string(a), base=16)
        pb = int('0x' + self.abn.to_string(b), base=16)
        self.abn.mul(c, a, b)
        pc = int('0x' + self.abn.to_string(c), base=16)
        self.assertEqual(pc, pa*pb)

    def tearDown(self):
        self.abn.free(self.number1)
        self.abn.free(self.number2)

if __name__ == '__main__':
    unittest.main()
