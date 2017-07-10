/**
  @file sene.c
  @author Wenting Zheng (wzheng8)
  
  This program is to load five models from files, save the scene to the output file
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scene.h"
#include "model.h"


#define CAP 10

/**
  This function is to dynamically allocate an instance of Scene, and initialize its fields
  
  @return a pointer to a dynamically allocated instance of Scene
*/
Scene *makeScene()
{
  Scene *s = (Scene *) malloc(sizeof(Scene));
  s->mCount = 0;
  s->mCap = CAP;
  s->mList = (Model **)malloc(s->mCap * sizeof(Model*));
  return s;
}

/**
  This function is to free the dynamically allocated memory used to store the given Scene
  
  @param s dynamically allocated memory used to store the given Scene
*/
void freeScene( Scene *s )
{
  int cou = s->mCount;
  for (int i = 0; i < cou; i++){
    freeModel(s->mList[i]);
  }
  free(s->mList);
  free(s);
}

/**
  This function is to add a model to the scene
  
  @param s dynamically allocated memory used to store the given Scene
  @param m model to be added to the scene
  @return true if the model is added and false if not
*/
bool addModel(Scene *s, Model *m)
{
  if (s->mCount >= s->mCap - 1){
    s->mCap += CAP;
    s->mList = (Model **)realloc(s->mList, s->mCap * sizeof(Model*));
  }
  int idx = s->mCount;
  for (int i = 0; i < s->mCount; i++){
    if (strcmp(m->name, s->mList[i]->name) < 0){
      idx = i;
      break;
    }
    if (!strcmp(m->name, s->mList[i]->name)){
      return false;
    }
  }
  for (int i = s->mCount - 1; i >= idx; i--){
    s->mList[i + 1] = s->mList[i];
  }
  s->mList[idx] = m;
  (s->mCount)++;
  return true;
}

/**
  This function is to add a model to the scene
  
  @param s dynamically allocated memory used to store the given Scene
  @param name of the model to be deleted from the scene
  @return true if the model is deleted and false if it is not in the scene
*/
bool deleteModel(Scene *s, char const *name)
{
  int idx = -1;
  for (int i = 0; i < s->mCount; i++){
    if (strcmp(s->mList[i]->name, name) == 0){
      idx = i;
      break;
    }
  }
  if (idx != -1){
    freeModel(s->mList[idx]);
    for (int i = idx; i < s->mCount - 1; i++){
      s->mList[i] = s->mList[i + 1];
    }
    s->mCount--;
    return true;
  } else {
    return false;
  }
}

/**
  This function is to save the scene to a file
  
  @param s dynamically allocated memory used to store the given Scene
  @param fname name of the file to save the scene
*/
void saveScene( Scene *s, char const *fname)
{
  FILE *fp = fopen(fname, "w");
  if (!fp){
    fprintf(stderr, "Can't open file: %s\n", fname);
  }
  
  for (int i = 0; i < s->mCount; i++){
    for (int j = 0; j < s->mList[i]->pCount; j += 2){
      fprintf(fp, "%.3lf %.3lf\n%.3lf %.3lf\n\n",
      s->mList[i]->pList[j][0], s->mList[i]->pList[j][1],
      s->mList[i]->pList[j + 1][0], s->mList[i]->pList[j + 1][1]);
    }
  }
  fclose(fp);
}

/**
  This function is to find the model in the list of models matching the given name
  and uses the given function to apply a transfor mation to the model
  
  @param s dynamically allocated memory used to store the given Scene
  @param name of the modle
  @param f function accepts point to transfor m, a and b are given by applyToScene()
  @param a degree/factor/x displacement
  @param b y displacement or 0
  @return true if the modle is found in the scene false if not
*/
bool applyToScene( Scene *s, char const *name,
void (*f)( double pt[ 2 ], double a, double b ), double a, double b )
{
  for (int i = 0; i < s->mCount; i++){
    if (strcmp(s->mList[i]->name, name) == 0){
      applyToModel( s->mList[i], f, a, b);
      return true;
    }
  }
  return false;
}
