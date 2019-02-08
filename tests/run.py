#!/usr/bin/env python
import unittest
import traceback
import os
import utilities
from termcolor import colored

import basicOperations
import arithmeticOperations
import bitwiseOperations

def getSuitesDictionary():
    testModules = [arithmeticOperations, bitwiseOperations, basicOperations]
    suites = {}
    for testModule in testModules:
        suites[testModule] = unittest.TestSuite()
        suites[testModule].addTests(unittest.TestLoader().loadTestsFromModule(testModule))
    return suites

def runSuites(suiteDictionary, verbosity = 1):
    runner = unittest.TextTestRunner(verbosity=verbosity)
    result_infos = []
    for module, suite in suiteDictionary.iteritems():
        print '\nRunnig tests from "' + module.__name__ + '":'
        result = runner.run(suite)
        result_infos.append({'module': module, 'result': result})
    return result_infos

def printResults(result_infos):
    print '\n'
    succesful = True
    for result_info in result_infos:
        print str(result_info['result']) + '\t--->\t' + result_info['module'].__name__
        if not result_info['result'].wasSuccessful():
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
            result_infos = runSuites(suiteDictionary, verbosity = 3)
            printResults(result_infos)
        except:
            traceback.print_exc()
    else:
        print 'There is no shared object found'