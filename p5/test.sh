#!/bin/bash
FAIL=0

# make a fresh copy of the target programs
make clean
make
if [ $? -ne 0 ]; then
  echo "**** Make (compilation) FAILED"
  FAIL=1
fi

# Check the results of an execution of encrypt.
# Splitting this out from the test function makes it easier
# to handle some error tests.
checkEncrypt() {
  TESTNO=$1
  ESTATUS=$2

  # Make sure the program exited with the right exit status.
  if [ $STATUS -ne $ESTATUS ]; then
      echo "**** Test failed - incorrect exit status. Expected: $ESTATUS Got: $STATUS"
      FAIL=1
      return 1
  fi

  # Check different things, depending on whether it's successful.
  if [ -s stdout.txt ]; then
      echo "**** Test failed - program shouldn't print anything to standard output"
      FAIL=1
      return 1
  fi
      
  # Check different things, depending on whether it's successful.
  if [ $ESTATUS -eq 0 ]; then
      # Make sure the output matches the expected output.
      diff -q encrypted-$TESTNO.bin encrypted.bin >/dev/null 2>&1
      if [ $? -ne 0 ]; then
	  echo "**** Test FAILED - encrypted output doesn't match expected"
	  FAIL=1
	  return 1
      fi
      
      if [ -s stderr.txt ]; then
	  echo "**** Test FAILED - shouldn't have printed any error output"
	  FAIL=1
	  return 1
      fi
  else
      # Make sure the output matches the expected output.
      diff -q stderr-$TESTNO.txt stderr.txt >/dev/null 2>&1
      if [ $? -ne 0 ]; then
	  echo "**** Test FAILED - printed the wrong error message"
	  FAIL=1
	  return 1
      fi
  fi

  echo "Test $TESTNO PASS"
  return 0
}

# Test the encryption program.
testEncrypt() {
  rm -f encrypted.bin stdout.txt stderr.txt

  echo "Test $1: ./encrypt input-$1.txt encrypted.bin > stdout.txt 2> stderr.txt"
  ./encrypt input-$1.txt encrypted.bin > stdout.txt 2> stderr.txt
  STATUS=$?

  checkEncrypt "$1" "$2"
}

# Check the results of an execution of decrypt.  Same idea as with
# checkEncrypt
checkDecrypt() {
  TESTNO=$1
  ESTATUS=$2

  # Make sure the program exited with the right exit status.
  if [ $STATUS -ne $ESTATUS ]; then
      echo "**** Test failed - incorrect exit status. Expected: $ESTATUS Got: $STATUS"
      FAIL=1
      return 1
  fi

  # Check different things, depending on whether it's successful.
  if [ -s stdout.txt ]; then
      echo "**** Test failed - program shouldn't print anything to standard output"
      FAIL=1
      return 1
  fi
      
  # Check different things, depending on whether it's successful.
  if [ $ESTATUS -eq 0 ]; then
      # The file we get back should match the corresponding input.
      diff -q input-$TESTNO.txt output.txt >/dev/null 2>&1
      if [ $? -ne 0 ]; then
	  echo "**** Test FAILED - decrypted output doesn't match expected"
	  FAIL=1
	  return 1
      fi
      
      if [ -s stderr.txt ]; then
	  echo "**** Test FAILED - shouldn't have printed any error output"
	  FAIL=1
	  return 1
      fi
  else
      # Make sure the output matches the expected output.
      diff -q stderr-$TESTNO.txt stderr.txt >/dev/null 2>&1
      if [ $? -ne 0 ]; then
	  echo "**** Test FAILED - printed the wrong error message"
	  FAIL=1
	  return 1
      fi
  fi

  echo "Test $TESTNO PASS"
  return 0
}

 # Test the decryption program.
testDecrypt() {
  rm -f output.txt stdout.txt stderr.txt

  echo "Test $1: ./decrypt encrypted-$1.bin output.txt > stdout.txt 2> stderr.txt"
  ./decrypt encrypted-$1.bin output.txt > stdout.txt 2> stderr.txt
  STATUS=$?

  checkDecrypt "$1" "$2"
}

# Test the encrypt program
echo
echo "Testing encrypt"
testEncrypt 1 0
testEncrypt 2 0
testEncrypt 3 0
testEncrypt 4 0
testEncrypt 5 0
testEncrypt 6 0
testEncrypt 7 0
testEncrypt 8 1

# invalid command-line arguments.
rm -f output.bin stdout.txt
echo "Test 10: ./encrypt a > stdout.txt 2> stderr.txt"
./encrypt a > stdout.txt 2> stderr.txt
STATUS=$?
checkEncrypt 10 1

# Test the decrypt program
echo
echo "Testing decrypt"
testDecrypt 1 0
testDecrypt 2 0
testDecrypt 3 0
testDecrypt 4 0
testDecrypt 5 0
testDecrypt 6 0
testDecrypt 7 0
testDecrypt 9 1
testDecrypt 11 1

if [ $FAIL -ne 0 ]; then
  echo "FAILING TESTS!"
  exit 13
else 
  echo "Tests successful"
  exit 0
fi
