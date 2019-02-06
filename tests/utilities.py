import sys
sys.path.append('../wrappers/python')

from abn_wrapper import ABN
import unittest

class OperationTestCase(unittest.TestCase):

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

class Utilities:

    def __init__(self, abn_lib):
        self.abn = abn_lib
        self.volume_of_test_numbers = 4
        self.max_abn_value = (1 << (8 * self.abn.size_of_abn_unit * self.volume_of_test_numbers)) - 1
        self.max_abn_value_signed = (1 << (8 * self.abn.size_of_abn_unit * self.volume_of_test_numbers - 1)) - 1

    def abn_to_long(self, a):
        return int('0x' + self.abn.to_string(a), base=16)
    
    def abn_to_signed_long(self, a, bits):
        a = self.abn_to_long(a)
        threshold = 1<<bits
        if a >= threshold>>1:
            a = -(threshold - a)
        return a

    def hex_to_long(self, a):
        if not '0x' in a:
            a = '0x' + a
        return int(a, base=16)

    def hex_to_signed_long(self, a, sign_position='default'):
        if sign_position == 'default':
            threshold = self.max_abn_value_signed + 1
        else:
            threshold = 1 << sign_position
        a = self.hex_to_long(a)
        if a >= threshold:
            a = - (2*threshold - a)
        return a

    def print_numbers(self, numberSet):
        for i in numberSet:
            print str(self.abn_to_long(i))

    def get_default_bit_number(self):
        return 8 * self.abn.size_of_abn_unit * self.volume_of_test_numbers

    def normalize(self, number, bits):
        return number % (1<<bits)

    def bit_not(self, n):
        return (1 << self.get_default_bit_number()) - 1 - n

    def get_test_numbers(self):
        test_numbers = []

        # zero number
        temp = self.abn.create(self.volume_of_test_numbers)
        self.abn.reset(temp)
        test_numbers.append(temp)

        # one number
        temp = self.abn.create(self.volume_of_test_numbers)
        self.abn.reset(temp)
        self.abn.set_byte(temp, 1, 0)
        test_numbers.append(temp)

        # minus one number or max unsigned abn number
        temp = self.abn.create(self.volume_of_test_numbers)
        self.abn.reset(temp)
        self.abn.bit_not(temp)
        test_numbers.append(temp)

        # max and min signed abn number 
        temp = self.abn.create(self.volume_of_test_numbers)
        self.abn.reset(temp)
        self.abn.bit_not(temp)
        self.abn.set_byte(temp, 0x7F, self.abn.size_of_abn_unit*self.volume_of_test_numbers-1)
        test_numbers.append(temp)
        temp = self.abn.create_copy(temp)
        self.abn.bit_not(temp)
        test_numbers.append(temp)

        # four usual numbers
        for n in range(0, 4):
            temp = self.abn.create(self.volume_of_test_numbers)
            self.abn.reset(temp)
            for i in range(0, self.abn.size_of_abn_unit*self.volume_of_test_numbers):
                self.abn.set_byte(temp, (n+1)*2985*(i+1)%256, i)
            test_numbers.append(temp)
        return test_numbers

    def free_test_numbers(self, test_numbers_list):
        for i in range(1, len(test_numbers_list)):
            self.abn.free(test_numbers_list[i])
        test_numbers_list = None