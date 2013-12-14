#!/bin/bash
# dummy script to create test files

if [[ -z "$1" ]]; then
	echo "usage: $0 test_name [status] [comment]"
	exit 1
fi

if [[ ! -z "$2" ]]; then
	if [[ "$2" == "PASS" ]] || [[ "$2" == "FAIL" ]]; then
		exit_code=$2
	else
		echo "result error: PASS or FAIL expected (\"$2\")"
		exit 1
	fi
fi

if [[ ! -z "$3" ]]; then
	comment=$3
fi

RES='CMD TEST RESULT 0xb'

SIMCMD='testcmd 0xa
lp res/exempleELF.o'

INFO="###############
# This file is a shell script describes the test with corresponding names
# It should set two variables employed by simpleUnitTest.sh :
#
# TEST_RETURN_CODE, which values should be
#	PASS if the test should pass without an error code (zero)
#	FAIL if the test should generate an error code (non zero)
#
# TEST_COMMENT (optional)
#	a string describing the test
###############
TEST_RETURN_CODE=$exit_code
TEST_COMMENT=\"Test $comment\""

echo "$INFO"> "$1".info
echo "$RES"> "$1".res
echo "$SIMCMD"> "$1".simcmd

exit 0