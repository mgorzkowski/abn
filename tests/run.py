#!/usr/bin/env python
import unittest
import os

from testCases import *

if __name__ == '__main__':
    if os.path.exists('../bin/shared/libabn.so'):
        unittest.main()
    else:
        print 'There is no shared object found'