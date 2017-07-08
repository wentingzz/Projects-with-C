#!/bin/bash
FAIL=0

# make a fresh copy of the target programs
make clean
make
if [ $? -ne 0 ]; then
  echo "**** Make (compilation) FAILED"
  FAIL=1
fi

# Function to run the program against a test case and check
# its output files and exit status for correct behavior
testProgram() {
  TESTNO=$1
  OUTFILE=$2

  rm -f "$OUTFILE"

  echo " test $TESTNO: ./drawing < input-$TESTNO.txt > stdout.txt 2> stderr.txt"
  ./drawing < input-$TESTNO.txt > stdout.txt 2> stderr.txt
  STATUS=$?

  # Make sure the program exited with the right exit status.
  if [ $STATUS -ne 0 ]
  then
      echo "**** test $TESTNO FAILED - expected successful exit status."
      FAIL=1
      return 1
  fi

  # Make sure messages printed to standard output and standard error are
  # right.
  
  if ! diff -q estdout-$TESTNO.txt stdout.txt >/dev/null 2>&1
  then
      echo "**** test $TESTNO FAILED - output to standard output didn't match expected"
      FAIL=1
      return 1
  fi

  if ! diff -q estderr-$TESTNO.txt stderr.txt >/dev/null 2>&1
  then
      echo "**** test $TESTNO FAILED - output to standard error didn't match expected"
      FAIL=1
      return 1
  fi

  if ! diff -q eoutput-$TESTNO.txt "$OUTFILE" >/dev/null 2>&1
  then
      echo "**** test $TESTNO FAILED - output to $OUTFILE didn't match expected"
      FAIL=1
      return 1
  fi

  echo "Test $TESTNO PASS"
  return 0
}

# Test the hlight program
testProgram 1 output.txt
testProgram 2 output.txt
testProgram 3 output.txt
testProgram 4 output.txt
testProgram 5 output.txt
testProgram 6 output.txt
testProgram 7 output.txt
testProgram 8 output.txt
testProgram 9 output.txt
testProgram 10 output.txt
testProgram 11 output.txt
testProgram 12 output.txt
testProgram 13 output.txt
testProgram 14 alt-output.txt
testProgram 15 output.txt
testProgram 16 output.txt
testProgram 17 output.txt
testProgram 18 output.txt

if [ $FAIL -ne 0 ]; then
  echo "FAILING TESTS!"
  exit 13
else 
  echo "Tests successful"
  exit 0
fi
