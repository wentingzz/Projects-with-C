#ifndef _MODEL_H_
#define _MODEL_H_

#include <stdio.h>

/** Maximum length of name and filename strings. */
#define NAME_LIMIT 20

/** Representation for a model, a collection of line segments. */
typedef struct {
  /** Name of the model. */
  char name[ NAME_LIMIT + 1 ];
  
  /** File name it was loaded from. */
  char fname[ NAME_LIMIT + 1 ];
  
  /** Number of points in the model.  It has half this many line segments. */
  int pCount;

  /** List of points in the model, twice as long as the number
      of segments, since each segment has two points */
  double (*pList)[ 2 ];
} Model;

#endif

Model *loadModel( char const *fname );
void freeModel( Model *m );
void scaleModel(double pt[ 2 ], double a, double b);
void translateModel(double pt[ 2 ], double a, double b);
void rotateModel(double pt[ 2 ], double a, double b);
void applyToModel( Model *m, void (*f)( double pt[ 2 ], double a, double b ), double a, double b );