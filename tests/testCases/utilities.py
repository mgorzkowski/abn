import sys
sys.path.append('../wrappers')

from abn_wrapper import ABN

volume_of_test_numbers = 4
amount_of_test_numbers = 4
#test_numbers = []

class Utilities:

    def __init__(self, abn_lib):
        self.abn = abn_lib
        self.volume_of_test_numbers = 4
        self.amount_of_test_numbers = 4

    def abn_to_long(self, a):
        return int('0x' + self.abn.to_string(a), base=16)

    def hex_to_long(self, a):
        if not '0x' in a:
            a = '0x' + a
        return int(a, base=16)

    def shex(self, a):
        base = 1 << (8 * self.abn.size_of_abn_unit * self.volume_of_test_numbers)
        if a >= base/2:
            a = base - a
        return hex(a);

    def get_test_numbers(self):
        test_numbers = []
        for n in range(1, self.amount_of_test_numbers):
            temp = self.abn.create(self.volume_of_test_numbers)
            self.abn.reset(temp)
            for i in range(0, self.abn.size_of_abn_unit*self.volume_of_test_numbers):
                self.abn.set_byte(temp, (n+1)*1835*(i+1)%256, i)
            test_numbers.append(temp)
        return test_numbers

    def free_test_numbers(self, test_numbers_list):
        for i in range(1, len(test_numbers_list)):
            self.abn.free(test_numbers_list[i])
        test_numbers = None
