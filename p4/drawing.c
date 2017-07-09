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

#define NAME_LIMIT 20


/**
  Program starting point
  
  @return exit status
*/
int main()
{
  int cmd = 0;
  printf("cmd %d> ", ++cmd);
  
  char choice[10];
  char name[NAME_LIMIT + 1];
  Scene *s;
  Model *m;
  while (scanf("%9s", choice) == 1){
    if (cmd == 1){
      s = makeScene();
    }

    if (strcmp(choice, "load") == 0){
      char fname[NAME_LIMIT + 1];
      if (scanf("%20s %20s", name, fname) == 2) {
          m = loadModel(fname);
          if (m){
            strcpy(m->name, name);
            if (!addModel(s, m)) {
              fprintf(stderr, "Command %d invalid\n", cmd);
            }
          }
      } else {
        fprintf(stderr, "Command %d invalid\n", cmd);
      }
    } else if (strcmp(choice, "translate") == 0) {
      double x, y;
      if (scanf("%20s %lf %lf", name, &x, &y) == 3){
        if (!applyToScene(s, name, translateModel, x, y)) {
          fprintf(stderr, "Command %d invalid\n", cmd);
        }
      }
    } else if (strcmp(choice, "rotate") == 0) {
      double degree;
      if (scanf("%20s %lf", name, &degree) == 2){
        if (!applyToScene(s, name, rotateModel, degree, 0)) {
          fprintf(stderr, "Command %d invalid\n", cmd);
        }
      }
    } else if (strcmp(choice, "scale") == 0) {
      double factor;
      if (scanf("%20s %lf", name, &factor) == 2) {
        if (!applyToScene(s, name, scaleModel, factor, 0)) {
          fprintf(stderr, "Command %d invalid\n", cmd);
        }
      }
    } else if (strcmp(choice, "list") == 0) {
      for (int i = 0; i < s->mCount; i++){
        printf("%s %s (%d)\n", s->mList[i]->name, s->mList[i]->fname, s->mList[i]->pCount / 2);
      }
    } else if (strcmp(choice, "delete") == 0) {
      if (scanf("%20s", name)){
        deleteModel(s, name);
      } else {
        fprintf(stderr, "Command %d invalid\n", cmd);
      }
    } else if (strcmp(choice, "save") == 0) {
      if (scanf("%20s", name)) {
        saveScene(s, name);
      } else {
        fprintf(stderr, "Command %d invalid\n", cmd);
      }
    } else if (strcmp(choice, "quit") == 0) {
      freeScene(s);
      break;
    } else { //invalid input
      scanf("%*[^\n]s");
    }
    printf("cmd %d> ", ++cmd);
  }
  return 0;
}
