/**
  @file model.c
  @author Wenting Zheng (wzheng8)
  
  This program is to load five models from files, save the scene to the output file
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "model.h"

#define PI 3.14159265

/**
  This function is to read a model from a file with the given name and
  return a pointer to a dynamically allocated instance of model
  If the input file can't be opened or if the model isn't in the right format,
  the function will print an error message and return NULL
  
  @param fname file's name containing modles
  @return a pointer to a dynamically allocated instance of model
*/
Model *loadModel( char const *fname )
{
  FILE *fp = fopen(fname, "r");
  if(!fp){
    fprintf(stderr, "Can't open file: %s", fname);
    return NULL;
  }
  int cap = 10;
  int pCount = 0;
  double (*pList)[2] = (double (*)[2])malloc( cap * 2 * sizeof(double) );
  
  //(pList + pCount)[0]
  while(fscanf(fp, "%lf %lf\n%lf %lf\n", &pList[pCount][0], &pList[pCount][1],  &pList[pCount + 1][0], &pList[pCount + 1][1]) == 4){
//     printf("%.3lf %.3lf\n%.3lf %.3lf\n\n", pList[pCount][0], pList[pCount][1],  pList[pCount + 1][0], pList[pCount + 1][1]);
    
    pCount += 2;
    if(pCount >= cap){
      cap *= 2;
      pList = (double (*)[2])realloc( pList, cap * 2 * sizeof(double) );
    }
  }
  if(fscanf(fp, "%*[^\n]s") == 1){
    fprintf(stderr, "Invalid model format: %s", fname);
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

void scaleModel(double pt[ 2 ], double a, double b)
{
  pt[0] *= a;
  pt[1] *= a;
}

void translateModel(double pt[ 2 ], double a, double b)
{
  pt[0] += a;
  pt[1] += b;
}

void rotateModel(double pt[ 2 ], double a, double b)
{
  int x = pt[0];
  double co = cos(a * PI / 180);
  double si = sin(a * PI / 180);
  pt[0] = pt[0] * co - pt[1] * si;
  pt[1] = x * si + pt[1] * co;
}

/**
  This function is to perform geometric transformation to selected model in scene
  
  @param m selected model
  @param f function accepts point to transform, a and b are given by applyToScene()
  @param m dynamically allocated memory used to store the given Model
  @param m dynamically allocated memory used to store the given Model
*/
void applyToModel( Model *m, void (*f)( double pt[ 2 ], double a, double b ), double a, double b )
{
  for(int i = 0; i < m->pCount; i++){
    f(m->pList[i], a, b);
  }
}