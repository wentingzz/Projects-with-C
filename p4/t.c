/**
  @file drawing.c
  @author Wenting Zheng (wzheng8)
  
  This program is to load five models from files, save the scene to the output file
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scene.h"
#include "model.h"

#include <time.h>
#define READ_VARS 4


/**
  Program starting point
  
  @return exit status
*/
int main()
{
  int count = 0;
  int name;
  int mList[20];
  while(scanf("%d", &name) == 1){
    if(name == -1){
      for(int i = 0; i < count; i++){
        printf("%d ", mList[i]);
      }
      printf("\n%d", count);
      printf("\n");
      return 0;
    }
    
    int idx = count;
    for(int i = 0; i < count; i++){
      if(name < mList[i]){
        idx = i;
        break;
      }
    }
    printf("(%d)\n", idx);
    for(int i = count - 1; i >= idx; i--){
      mList[i + 1] = mList[i];
    }
    mList[idx] = name;
    (count)++;
    for(int i = 0; i < count; i++){
        printf("%d ", mList[i]);
      }
      printf("\n%d\n", count);
  }
  return 0;
}
