#!/usr/bin/env python3
import unittest
import traceback
import os
import utilities
import inspect
from termcolor import colored

import basicOperations
import arithmeticOperations
import bitwiseOperations

main_suite_modules = [arithmeticOperations, bitwiseOperations, basicOperations]

def addTestsFromModuleAndSubmodules(suite, module):
    suite.addTests(unittest.TestLoader().loadTestsFromModule(module))
    for name, member in inspect.getmembers(module):
        if name.endswith('_tests') and inspect.ismodule(member):
            addTestsFromModuleAndSubmodules(suite, member)

def getSuitesDictionary():
    suites = {}
    for testModule in main_suite_modules:
        suites[testModule] = unittest.TestSuite()
        addTestsFromModuleAndSubmodules(suites[testModule], testModule)
    return suites

def runSuites(suiteDictionary, verbosity = 1):
    runner = unittest.TextTestRunner(verbosity=verbosity)
    result_infos = []
    for module, suite in iter(suiteDictionary.items()):
        print('\nRunnig tests from "' + module.__name__ + '":')
        result = runner.run(suite)
        result_infos.append({'module': module, 'result': result})
    return result_infos

def printResults(result_infos):
    print('\n')
    succesful = True
    for result_info in result_infos:
        print(result_info['module'].__name__ + ":")
        print("\trun: " + str(result_info['result'].testsRun))
        print("\terrors: " + str(len(result_info['result'].errors)))
        print("\tfailures: " + str(len(result_info['result'].failures)))
        print()
        if not result_info['result'].wasSuccessful():
            succesful = False
    if succesful:
        print(colored('[Success]', 'green'))
    else:
        print(colored('[Errors or fails occured]', 'red'))
    print('\n')

if __name__ == '__main__':
    if os.path.exists(utilities.abn_shared_object_path):
        try:
            suiteDictionary = getSuitesDictionary()
            result_infos = runSuites(suiteDictionary, verbosity = 3)
            printResults(result_infos)
        except:
            traceback.print_exc()
    else:
        print('There is no shared object found')
