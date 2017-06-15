#!/bin/bash
FAIL=0

# make a fresh copy of the target programs
make clean
make
if [ $? -ne 0 ]; then
  echo "**** Make (compilation) FAILED"
  FAIL=1
fi

# Function to run the jumble program against a test case and check
# its output and exit status for correct behavior
testJumble() {
  TESTNO=$1
  ESTATUS=$2
  INPUT=$3

  rm -f output.txt stderr.txt

  echo "Jumble test $TESTNO: ./jumble < input-j$TESTNO.txt $INPUT > output.txt 2>stderr.txt"
  ./jumble < input-j$TESTNO.txt $INPUT > output.txt 2>stderr.txt
  STATUS=$?

  # Make sure the program exited with the right exit status.
  if [ $STATUS -ne $ESTATUS ]
  then
      echo "**** Jumble test $TESTNO FAILED - incorrect exit status. Expected: $ESTATUS Got: $STATUS"
      FAIL=1
      return 1
  fi
  
  # Make sure the error message is right, if it was supposed to print
  # an error message.
  if [ -f stderr-j$TESTNO.txt ]; then
    if ! diff -q stderr-j$TESTNO.txt stderr.txt >/dev/null 2>&1
    then
      echo "**** Jumble test $TESTNO FAILED - error message is incorrect."
      FAIL=1
      return 1
    fi
  else
    if [ -s stderr.txt ]; then
      echo "**** Jumble test $TESTNO FAILED - generated unexpected output to stderr."
      FAIL=1
      return 1
    fi
  fi

  # Make sure the output matches the expected output.
  
  if ! diff -q expected-j$TESTNO.txt output.txt >/dev/null 2>&1
  then
      echo "**** Jumble test $TESTNO FAILED - output didn't match the expected output"
      FAIL=1
      return 1
  fi

  echo "Jumble test $TESTNO PASS"
  return 0
}

# Function to run the puzzle program against a test case and check its
# output and exit status for correct behavior
testPuzzle() {
  TESTNO=$1
  ESTATUS=$2

  rm -f output.txt stderr.txt

  echo "Puzzle test $TESTNO: ./puzzle input-p$TESTNO.txt > output.txt 2> stderr.txt"
  ./puzzle input-p$TESTNO.txt > output.txt 2> stderr.txt
  STATUS=$?

  # Make sure the program exited with the right exit status.
  if [ $STATUS -ne $ESTATUS ]
  then
      echo "**** Puzzle test $TESTNO FAILED - incorrect exit status. Expected: $ESTATUS Got: $STATUS"
      FAIL=1
      return 1
  fi

  # Make sure the error message is right, if it was supposed to print
  # an error message.
  if [ -f stderr-p$TESTNO.txt ]; then
    if ! diff -q stderr-p$TESTNO.txt stderr.txt >/dev/null 2>&1
    then
      echo "**** Puzzle test $TESTNO FAILED - error message is incorrect."
      FAIL=1
      return 1
    fi
  else
    if [ -s stderr.txt ]; then
      echo "**** Puzzle test $TESTNO FAILED - generated unexpected output to stderr."
      FAIL=1
      return 1
    fi
  fi

  # Make sure the output matches the expected output.
  
  if ! diff -q expected-p$TESTNO.txt output.txt >/dev/null 2>&1
  then
      echo "**** Puzzle test $TESTNO FAILED - output didn't match the expected output"
      FAIL=1
      return 1
  fi

  echo "Puzzle test $TESTNO PASS"
  return 0
}

# Test the jumble program
testJumble 1 0 words-large.txt
testJumble 2 0 words-small.txt
testJumble 3 0 words-med.txt
testJumble 4 0 words-large.txt
testJumble 5 0 words-small.txt
testJumble 6 1 words-non-existent.txt
testJumble 7 1 words-bad7.txt
testJumble 8 1 words-bad8.txt

# Test the puzzle program.
testPuzzle 1 0
testPuzzle 2 0
testPuzzle 3 0
testPuzzle 4 0
testPuzzle 5 0
testPuzzle 6 1
testPuzzle 7 1
testPuzzle 8 1

if [ $FAIL -ne 0 ]; then
  echo "FAILING TESTS!"
  exit 13
else 
  echo "Tests successful"
  exit 0
fi
