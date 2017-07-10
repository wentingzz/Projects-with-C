/**
  @file model.c
  @author Wenting Zheng (wzheng8)
  
  This program is to load, free, and transform model in the scene
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "model.h"

/** degree to radian*/
#define RADIAN 3.14159265358979323846 / 180

/** initial capacity of model list*/
#define CAP 10

/** four variable to read from the file*/
#define FOUR_VARIABLE 4

/**
  This function is to read a model from a file with the given name and
  return a pointer to a dynamically allocated instance of model
  if  the input file can't be opened or if  the model isn't in the right for mat,
  the function will print an error message and return NULL
  
  @param fname file's name containing modles
  @return a pointer to a dynamically allocated instance of model
*/
Model *loadModel( char const *fname )
{
  FILE *fp = fopen(fname, "r");
  if (!fp){
    fprintf(stderr, "Can't open file: %s\n", fname);
    return NULL;
  }
  int cap = CAP;
  int pCount = 0;
  double (*pList)[2] = (double (*)[2])malloc( cap * 2 * sizeof(double) );
  
  //(pList + pCount)[0]
  while (fscanf(fp, "%lf %lf\n%lf %lf\n", &pList[pCount][0],
  &pList[pCount][1],  &pList[pCount + 1][0], &pList[pCount + 1][1]) == 4){
    pCount += 2;
    if (pCount >= cap){
      cap *= 2;
      pList = (double (*)[2])realloc( pList, cap * 2 * sizeof(double) );
    }
  }
  if (fscanf(fp, "%*[^\n]s") == 1){
    fprintf(stderr, "Invalid model for mat: %s\n", fname);
    free(pList);
    fclose(fp);
    return NULL;
  }
  Model *f = (Model *) malloc(sizeof(Model));
  strcpy(f->fname, fname);
  f->pCount = pCount;
  f->pList = pList;
  fclose(fp);
  return f;
}

/**
  This function is to free the dynamically allocated memory used to store the given Model
  
  @param m dynamically allocated memory used to store the given Model
*/
void freeModel( Model *m )
{
  free(m->pList);
  free(m);
}

/**
  This function is to make a line larger or smaller
  
  @param pt two endpoints of a line
  @param a factor
  @param b parameter never used
*/
void scaleModel(double pt[ 2 ], double a, double b)
{
  pt[0] *= a;
  pt[1] *= a;
}

/**
  This function is to move one line by x and y displacement
  
  @param pt two endpoints of a line
  @param a x displacement
  @param b y displacement
*/
void translateModel(double pt[ 2 ], double a, double b)
{
  pt[0] += a;
  pt[1] += b;
}

/**
  This function is to rotate one line
  
  @param pt two endpoints of a line
  @param a degree
  @param b parameter never used
*/
void rotateModel(double pt[ 2 ], double a, double b)
{
  double x = pt[0];
  double co = cos(a * RADIAN);
  double si = sin(a * RADIAN);
  pt[0] = pt[0] * co - pt[1] * si;
  pt[1] = x * si + pt[1] * co;
}

/**
  This function is to perfor m geometric transfor mation to selected model in scene
  
  @param m selected model
  @param f function accepts point to transfor m, a and b are given by applyToScene()
  @param a degree/factor/x displacement
  @param b y displacement or 0
*/
void applyToModel( Model *m, void (*f)( double pt[ 2 ], double a, double b ), double a, double b )
{
  for (int i = 0; i < m->pCount; i++){
    f(m->pList[i], a, b);
  }
}
