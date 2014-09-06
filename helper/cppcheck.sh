#!/bin/sh

# this script runs cppcheck with appropriate parameters for checking the src and test folders

cppcheck --enable=warning,style,performance,portability,information,missingInclude --language=c --std=c11 --suppress=missingIncludeSystem ../src/ ../test/
