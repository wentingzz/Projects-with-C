#!/bin/bash
FAIL=0

# make a fresh copy of the target programs
make clean
make
if [ $? -ne 0 ]; then
  echo "**** Make (compilation) FAILED"
  FAIL=1
fi

# Function to run the hlight program against a test case and check
# its output and exit status for correct behavior
testHlight() {
  TESTNO=$1
  ESTATUS=$2

  rm -f output.txt

  echo "Hlight test $TESTNO: ./hlight < input-h$TESTNO.html > output.txt"
  ./hlight < input-h$TESTNO.html > output.txt
  STATUS=$?

  # Make sure the program exited with the right exit status.
  if [ $STATUS -ne $ESTATUS ]
  then
      echo "**** Hlight test $TESTNO FAILED - incorrect exit status. Expected: $ESTATUS Got: $STATUS"
      FAIL=1
      return 1
  fi

  # Make sure the output matches the expected output.
  
  if ! diff -q expected-h$TESTNO.txt output.txt >/dev/null 2>&1
  then
      echo "**** Hlight test $TESTNO FAILED - output didn't match the expected output"
      FAIL=1
      return 1
  fi

  echo "Hlight test $TESTNO PASS"
  return 0
}

# Function to run the voronoi program against a test case and check its
# output and exit status for correct behavior
testVoronoi() {
  TESTNO=$1
  ESTATUS=$2

  # Name of the output file depends on whether this is an error test case.
  if [ $ESTATUS -eq 0 ]
  then
      EXPECTED="expected-v$TESTNO.ppm"
      OUTPUT="output.ppm"
  else
      EXPECTED="expected-v$TESTNO.txt"
      OUTPUT="output.txt"
  fi

  rm -f "$OUTPUT"

  echo "Voronoi test $TESTNO: ./voronoi < input-v$TESTNO.txt > $OUTPUT"
  ./voronoi < input-v$TESTNO.txt > $OUTPUT
  STATUS=$?

  # Make sure the program exited with the right exit status.
  if [ $STATUS -ne $ESTATUS ]
  then
      echo "**** Voronoi test $TESTNO FAILED - incorrect exit status. Expected: $ESTATUS Got: $STATUS"
      FAIL=1
      return 1
  fi

  # Make sure the output matches the expected output.
  
  if ! diff -q $EXPECTED $OUTPUT >/dev/null 2>&1
  then
      echo "**** Voronoi test $TESTNO FAILED - output didn't match the expected output"
      FAIL=1
      return 1
  fi

  echo "Voronoi test $TESTNO PASS"
  return 0
}

# Test the hlight program
testHlight 1 0
testHlight 2 0
testHlight 3 0
testHlight 4 0
testHlight 5 101
testHlight 6 100

# Test the voronoi program.
testVoronoi 1 0
testVoronoi 2 0
testVoronoi 3 0
testVoronoi 4 0
testVoronoi 5 100
testVoronoi 6 100

if [ $FAIL -ne 0 ]; then
  echo "FAILING TESTS!"
  exit 13
else 
  echo "Tests successful"
  exit 0
fi
