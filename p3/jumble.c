/**
  @file jumble.c
  @author Wenting Zheng (wzheng8)

  This program is to read in a word list and find word(s) matching the input letters
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* list storing the words*/
char words[100000][21];

/* the number of words on the word list*/
int wordCount;

/**
  read the word list from the file with the given name,
  storing it in the global words array and setting wordCount
  
  @param filename name of the file storing the word list
*/
void readWords( char const *filename )
{
  FILE * input = fopen(filename, "r");
  int count = 0;
  char ch;
  while (fscanf(input, "%c", &ch) == 1) {
    if (ch == '\n') {
      wordCount++;
      words[wordCount][count] = '\0'; // make it string
      count = 0;
    } else {
      words[wordCount][count++] = ch;
    }
  }
}

/**
  prompts the user for letters and stores them in the given array, letters
  
  @param letters pointer to the start of the array of letters given by user
  @return true if the user's input letters are valid
*/
bool getLetters( char * letters )
{
  int count = 0;
  char next;
  while ((next = letters[count++]) != '\0'){
    if (count == 20){
      return false;
    } else if ( !(next >= 'A' && next <= 'Z') && !(next >= 'a' && next <= 'z') ){ //not letter
      return false;
    }
  }
  return true;
}

/**
  Returns the length of the given array
  
  @param word array
  @return the given array's length
*/
int arraylength(char const * word)
{
  int result = 0;
  while (word[result] != '\0'){
    if ( (word[result] >= 'A' && word[result] <= 'Z') || (word[result] >= 'a' && word[result] <= 'z')){
      result++;
    }
  }
  return result;
}

/**
  Returns true if every character in list1 exists in list2
  
  @param list1 pointer to a list of characters
  @param list2 pointer to a list of characters
  @return true if characters in list1 are contained in list2
*/
bool contains(char const * list1, char const * list2)
{
  int idx = 0;
  int idx2 = 0;
  bool result;
  while ( list1[idx] != '\0'){ // take one char in list 1
    result = false;
    while ( list2[idx2] != '\0'){ // try to find the same char in list 2
      if (list1[idx] == list2[idx2]){ // find, break the while loop
        result = true;
        break;
      }
      idx2++;
    }
    if (!result){ //this char doesn't exist in another list
      return false;
    }
    idx++;
    idx2 = 0; //ready for another circle to start
  }
  return result;
}

/**
  Given a word and letters, this function returns true if the given word matches
  (contains exactly) the given letters
  
  @param word in the words list
  @param letters given by the user
  @return true if the two arrays have the same letters
*/
bool matches( char const * word, char const * letters )
{
  if (arraylength(word) != arraylength(letters) ||
      !contains(letters, word) ||
      !contains(word, letters)){
    return false;
  }
  return true;
}

/**
  Program starting point

  @param argc how many command-line arguments were given
  @param argv used to get the input word list file name
  @return exist status
*/
int main( int argc, char *argv[] )
{
  readWords(argv[1]);
  char lett[21];
  
  do{
    printf("letters> ");
    if (scanf("%s", lett) != 1){
      break;
    }
    if (!getLetters(&lett[0])){
      printf("Invalid letters");
    }
    for (int i = 0; i < wordCount; i++){
    if (matches(&words[i][0], &lett[0])){
      printf("%s\n", words[i]);
    }
  }
  } while (true);
  return 0;
}
