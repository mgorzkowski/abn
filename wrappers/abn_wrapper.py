#!/usr/bin/env python
from ctypes import *


# Type definitions

# _abn_unit must be the same type like abn_unit in abn/include/abn.h file one
_abn_unit = c_uint32

class _abn_t(Structure):
	_fields_ = [("chain", POINTER(_abn_unit)),
				("volume", c_uint)]

_abn_t_p = POINTER(_abn_t)


# ABN Wrapper

class ABN:
	"""This class wraps ABN library"""

	def __init__(self, file):

		# Library loading
		self.lib = CDLL(file)

		self.abn_unit = _abn_unit
		self.abn_t = _abn_t
		self.abn_t_p = _abn_t_p

		# Basic operations type settings
		self.lib.abn_create.argtypes = [c_uint]
		self.lib.abn_create.restype = self.abn_t_p
		self.lib.abn_create_copy.argtypes = [self.abn_t_p]
		self.lib.abn_create_copy.restype = self.abn_t_p
		self.lib.abn_create_empty.argtypes = None
		self.lib.abn_create_empty.restype = self.abn_t_p
		self.lib.abn_free.argtypes = [self.abn_t_p]
		self.lib.abn_free.restype = None
		self.lib.abn_reset.argtypes = [self.abn_t_p]
		self.lib.abn_reset.restype = None
		self.lib.abn_copy.argtypes = [self.abn_t_p, self.abn_t_p]
		self.lib.abn_copy.restype = None
		self.lib.abn_is_empty.argtypes = [self.abn_t_p]
		self.lib.abn_is_empty.restype = c_bool
		self.lib.abn_are_equal.argtypes = [self.abn_t_p, self.abn_t_p]
		self.lib.abn_are_equal.restype = c_bool
		self.lib.abn_get_byte.argtypes = [self.abn_t_p, c_uint]
		self.lib.abn_get_byte.restype = c_byte
		self.lib.abn_set_byte.argtypes = [self.abn_t_p, c_byte, c_uint]
		self.lib.abn_set_byte.restype = None
		self.lib.abn_to_string.argtypes = [self.abn_t_p]
		self.lib.abn_to_string.restype = c_char_p
		self.lib.abn_unit_to_string.argtypes = [self.abn_unit]
		self.lib.abn_unit_to_string.restype = c_char_p

		# Arithmetic operations type settings
		self.lib.abn_add.argtypes = [self.abn_t_p, self.abn_t_p, self.abn_t_p]
		self.lib.abn_add.restype = None
		self.lib.abn_inc.argtypes = [self.abn_t_p]
		self.lib.abn_inc.restype = None
		self.lib.abn_dec.argtypes = [self.abn_t_p]
		self.lib.abn_dec.restype = None
		self.lib.abn_neg.argtypes = [self.abn_t_p]
		self.lib.abn_neg.restype = None
		self.lib.abn_mul.argtypes = [self.abn_t_p, self.abn_t_p, self.abn_t_p]
		self.lib.abn_mul.restype = None
		self.lib.abn_smul.argtypes = [self.abn_t_p, self.abn_t_p, self.abn_t_p]
		self.lib.abn_smul.restype = None
		self.lib.abn_is_negative.argtypes = [self.abn_t_p]
		self.lib.abn_is_negative.restype = c_bool
		self.lib.abn_is_positive.argtypes = [self.abn_t_p]
		self.lib.abn_is_positive.restype = c_bool
		self.lib.abn_abs.argtypes = [self.abn_t_p]
		self.lib.abn_abs.restype = c_bool

		# Bit operations type settings
		self.lib.abn_not.argtypes = [self.abn_t_p]
		self.lib.abn_not.restype = None
		self.lib.abn_and.argtypes = [self.abn_t_p, self.abn_t_p, self.abn_t_p]
		self.lib.abn_and.restype = None
		self.lib.abn_or.argtypes = [self.abn_t_p, self.abn_t_p, self.abn_t_p]
		self.lib.abn_or.restype = None
		self.lib.abn_xor.argtypes = [self.abn_t_p, self.abn_t_p, self.abn_t_p]
		self.lib.abn_xor.restype = None
		self.lib.abn_nand.argtypes = [self.abn_t_p, self.abn_t_p, self.abn_t_p]
		self.lib.abn_nand.restype = None
		self.lib.abn_nor.argtypes = [self.abn_t_p, self.abn_t_p, self.abn_t_p]
		self.lib.abn_nor.restype = None
		self.lib.abn_shift_left.argtypes = [self.abn_t_p, c_uint]
		self.lib.abn_shift_left.restype = None
		self.lib.abn_shift_right.argtypes = [self.abn_t_p, c_uint]
		self.lib.abn_shift_right.restype = None
		self.lib.abn_rotate_left.argtypes = [self.abn_t_p, c_uint]
		self.lib.abn_rotate_left.restype = None
		self.lib.abn_rotate_right.argtypes = [self.abn_t_p, c_uint]
		self.lib.abn_rotate_right.restype = None

	# Wrap functions of basic operations

	def create(self, *params):
		return self.lib.abn_create(*params)

	def create_copy(self, *params):
		return self.lib.abn_create_copy(*params)

	def create_empty(self, *params):
		return self.lib.abn_create_empty(*params)

	def free(self, *params):
		return self.lib.abn_free(*params)

	def reset(self, *params):
		return self.lib.abn_reset(*params)

	def copy(self, *params):
		return self.lib.abn_copy(*params)

	def is_empty(self, *params):
		return self.lib.abn_is_empty(*params)

	def are_equal(self, *params):
		return self.lib.abn_are_equal(*params)

	def get_byte(self, *params):
		return self.lib.abn_get_byte(*params)

	def set_byte(self, *params):
		return self.lib.abn_set_byte(*params)

	def to_string(self, *params):
		return self.lib.abn_to_string(*params)

	def unit_to_string(self, *params):
		return self.lib.abn_unit_to_string(*params)
 
	# Wrap functions of arithmetic operations

	def add(self, *params):
		return self.lib.abn_add(*params)

	def inc(self, *params):
		return self.lib.abn_inc(*params)

	def dec(self, *params):
		return self.lib.abn_dec(*params)

	def neg(self, *params):
		return self.lib.abn_neg(*params)

	def mul(self, *params):
		return self.lib.abn_mul(*params)

	def smul(self, *params):
		return self.lib.abn_smul(*params)

	def is_negative(self, *params):
		return self.lib.abn_is_negative(*params)

	def is_positive(self, *params):
		return self.lib.abn_is_positive(*params)

	def abs(self, *params):
		return self.lib.abn_abs(*params)

	# Wrap functions of bit operations

	def bit_not(self, *params):
		return self.lib.abn_not(*params)

	def bit_and(self, *params):
		return self.lib.abn_and(*params)

	def bit_or(self, *params):
		return self.lib.abn_or(*params)

	def bit_xor(self, *params):
		return self.lib.abn_xor(*params)

	def bit_nand(self, *params):
		return self.lib.abn_nand(*params)

	def bit_nor(self, *params):
		return self.lib.abn_nor(*params)

	def shift_left(self, *params):
		return self.lib.abn_shift_left(*params)

	def shift_right(self, *params):
		return self.lib.abn_shift_right(*params)

	def rotate_left(self, *params):
		return self.lib.abn_rotate_left(*params)

	def rotate_right(self, *params):
		return self.lib.abn_rotate_right(*params)
