#!/usr/bin/env python
import sys
sys.path.append('../wrappers/python')

import unittest
import ctypes

from abn_wrapper import ABN
from utilities import *

class Incrementation_tests(OperationTestCase):

    #Testframes
    def incrementation_testframe(self, a):
        a = self.abn.create_copy(a)
        b = self.utilities.abn_to_long(a)
        self.abn.inc(a)
        a = self.utilities.abn_to_long(a)
        b = self.utilities.normalize(b+1, self.utilities.get_default_bit_number())
        self.assertEqual(a, b)

    def test_incrementation(self):
        for i in range(0, len(self.numbers)):
            self.incrementation_testframe(self.numbers[i])