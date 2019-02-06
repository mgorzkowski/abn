#!/usr/bin/env python
import unittest
import traceback
import os
import utilities
from termcolor import colored

import arithmeticOperations
import bitwiseOperations

def getSuitesDictionary():
    testModules = [arithmeticOperations, bitwiseOperations]
    suites = {}
    for testModule in testModules:
        suites[testModule] = unittest.TestSuite()
        suites[testModule].addTests(unittest.TestLoader().loadTestsFromModule(testModule))
    return suites

def runSuites(suiteDictionary, verbosity = 1):
    runner = unittest.TextTestRunner(verbosity=verbosity)
    results = []
    for module, suite in suiteDictionary.iteritems():
        print '\nRunnig tests from ' + module.__name__ + ':'
        result = runner.run(suite)
        results.append(result)
    return results

def printResults(results):
    print '\n'
    succesful = True
    for result in results:
        print result
        if not result.wasSuccessful():
            succesful = False
    if succesful:
        print colored('[Success]', 'green')
    else:
        print colored('[Errors or fails occured]', 'red')
    print '\n'

if __name__ == '__main__':
    if os.path.exists('../bin/shared/libabn.so'):
        try:
            suiteDictionary = getSuitesDictionary()
            results = runSuites(suiteDictionary, verbosity = 3)
            printResults(results)
        except:
            traceback.print_exc()
    else:
        print 'There is no shared object found'