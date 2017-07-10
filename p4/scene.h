#ifndef _SCENE_H_
#define _SCENE_H_

#include "model.h"
#include <stdbool.h>

/** Representation for a whole scene, a collection of models. */
typedef struct {
  /** Number of models in the scene. */
  int mCount;
  
  /** Capacity of the model list. */
  int mCap;

  /** List of pointers to models. */
  Model **mList;
} Scene;

#endif
Scene *makeScene();
void freeScene( Scene *s );
bool addModel(Scene *s, Model *m);
bool deleteModel(Scene *s, char const *name);
void saveScene( Scene *s, char const *fname );
bool applyToScene( Scene *s, char const *name,
void (*f)( double pt[ 2 ], double a, double b ), double a, double b );
