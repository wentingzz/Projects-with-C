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
  int cmd = 0;
  printf("cmd %d> ", ++cmd);
  
  char choice[10];
  char name[21];
  Scene *s;
  Model *m; 
  while (scanf("%9s", choice) == 1){
    if (cmd == 1){
      s = makeScene();
    }

    if (strcmp(choice, "load") == 0){
      char fname[21];
      if (scanf("%20s %20s", name, fname) == 2) {
          m = loadModel(fname);
          if (m){
            strcpy(m->name, name);
            addModel(s, m);
//             if (s->mCount >= s->mCap - 1){
//               s->mCap += 10;
//               s->mList = (Model **)realloc(s->mList, s->mCap * sizeof(Model*));
//             }
//             int idx = s->mCount;
//             for (int i = 0; i < s->mCount; i++){
//               if (strncmp(m->name, s->mList[i]->name, 20) < 0){
//                 idx = i;
//                 break;
//               }
//             }
//             for (int i = s->mCount - 1; i >= idx; i--){
//               s->mList[i + 1] = s->mList[i];
//             }
//             s->mList[idx] = m;
//             (s->mCount)++;
          }
      }
    } else if (strcmp(choice, "translate") == 0) {
      double x, y;
      if (scanf("%20s %lf %lf\n", name, &x, &y) == 3){
        applyToScene(s, name, translateModel, x, y);
      }
    } else if (strcmp(choice, "rotate") == 0) {
      double degree;
      if (scanf("%20s %lf\n", name, &degree) == 2){
        applyToScene(s, name, rotateModel, degree, 0);
      }
    } else if (strcmp(choice, "scale") == 0) {
      double factor;
      scanf("%20s %lf\n", name, &factor);
      applyToScene(s, name, scaleModel, factor, 0);
    } else if (strcmp(choice, "list") == 0) {
      for (int i = 0; i < s->mCount; i++){
        printf("%s %s (%d)\n", s->mList[i]->name, s->mList[i]->fname, s->mList[i]->pCount / 2);
      }
    } else if (strcmp(choice, "delete") == 0) {
      if (scanf("%20s\n", name)){
        deleteModel(s, name);
      }
    } else if (strcmp(choice, "save") == 0) {
      if (scanf("%20s\n", name)) {
        saveScene(s, name);
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
