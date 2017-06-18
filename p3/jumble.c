/**
  @file jumble.c
  @author Wenting Zheng (wzheng8)

  This program is to read in a word list and find word(s) matching the input letters
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_WORDS 100000
#define MAX_LENGTH 21
#define ALPHABET 26

/* list storing the words*/
char words[MAX_WORDS][MAX_LENGTH];

/* the number of words on the word list*/
int wordCount = 0;

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
  while (fscanf(input, "%c", &ch) == 1 && wordCount < MAX_WORDS) {
    if (ch >= 'a' && ch <= 'z'){ //valid letters
      words[wordCount][count++] = ch;
    } else if (ch == '\n') { //another word
      words[wordCount++][count] = '\0'; // make it string
      count = 0;
    } else {
      wordCount = MAX_WORDS;
    }
  }
  fclose(input);
}

/**
  prompts the user for letters and stores them in the given array, letters
  
  @param letters pointer to the start of the array of letters given by user
  @return true if the user's input letters are valid
*/
bool getLetters( char * letters )
{
  int count;
  printf("letters> ");
  while (scanf("%s", letters) == 1){
    while (letters[count] != '\0'){
      if (letters[count] < 'a' || letters[count] > 'z' || count == MAX_LENGTH){
        count = 0;
        printf("Invalid letters\nletters> ");
        break;
      }
      count++;
    }
    return true;
  }
  return false;
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
  int len1 = strlen(word);
  int len2 = strlen(letters);
  if (len1 != len2){
    return false;
  } else {
    int count1[ALPHABET] = {0};
    int count2[ALPHABET] = {0};
    for (int i = 0; i < len1; i++){
      count1[(*(word + i)) - 'a']++;
      count2[(*(letters + i)) - 'a']++;
    }
    for (int i = 0; i < ALPHABET; i++){
      if ((*(count1 + i)) != (*(count2 + i))){
        return false;
      }
    }
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
  if (argc != 2){
    fprintf(stderr, "usage: jumble <word-file>\n");
    return 1;
  }
  
  FILE * input = fopen(argv[1], "r");
  if (!input){
    fprintf(stderr, "Can't open word file\n");
    return 1;
  }
  fclose(input);
  readWords(argv[1]);
  if (wordCount >= MAX_WORDS){
    fprintf(stderr, "Invalid word file\n");
    return 1;
  }
  
  char lett[MAX_LENGTH];
  
  while (getLetters(&lett[0])){
    for (int i = 0; i <= wordCount; i++){
      if (matches(&words[i][0], &lett[0])){
        printf("%s\n", words[i]);
        break;
      }
    }
  }
  return 0;
}
