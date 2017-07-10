/**
  @file drawing.c
  @author Wenting Zheng (wzheng8)
  
  This program is to load five models from files, modify them and save them to 
  the scene to the output file
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scene.h"
#include "model.h"

/** Max length of name*/
#define NAME_LIMIT 20

/** Max length of choice*/
#define CHOICE_LIMIT 10

/** Number of variables read from the user when the choice is translate*/
#define TRANS 3

/**
  Program starting point
  
  @return exit status
*/
int main()
{
  int cmd = 0;
  printf("cmd %d> ", ++cmd);
  
  char choice[CHOICE_LIMIT];
  char name[NAME_LIMIT + 1];
  Scene *s;
  Model *m;

  while (scanf("%9s", choice) == 1){
    if (cmd == 1){
      s = makeScene();
    }
    
    if (strcmp(choice, "load") == 0){
      char fname[NAME_LIMIT + 1];
      if (scanf("%20s", name) && getchar() == ' ' && scanf("%20s", fname) && getchar() == '\n'){
        m = loadModel(fname);
          if (m){
            strcpy(m->name, name);
            if (!addModel(s, m)) {
              fprintf(stderr, "Command %d invalid\n", cmd);
            }
          }
      } else {
        goto invalid;
      }
    } else if (strcmp(choice, "translate") == 0) {
      double x, y;
      if (scanf("%20s %lf %lf", name, &x, &y) == TRANS){
        if (!applyToScene(s, name, translateModel, x, y)) {
          fprintf(stderr, "Command %d invalid\n", cmd);
        }
      } else {
        goto invalid;
      }
    } else if (strcmp(choice, "rotate") == 0) {
      double degree;
      if (scanf("%20s %lf", name, &degree) == 2){
        if (!applyToScene(s, name, rotateModel, degree, 0)) {
          fprintf(stderr, "Command %d invalid\n", cmd);
        }
      } else {
        goto invalid;
      }
    } else if (strcmp(choice, "scale") == 0) {
      double factor;
      if (scanf("%20s %lf", name, &factor) == 2) {
        if (!applyToScene(s, name, scaleModel, factor, 0)) {
          fprintf(stderr, "Command %d invalid\n", cmd);
        }
      } else {
        goto invalid;
      }
    } else if (strcmp(choice, "list") == 0) {
      if(getchar() != '\n'){
        goto invalid;
      }
      for (int i = 0; i < s->mCount; i++){
        printf("%s %s (%d)\n", s->mList[i]->name, s->mList[i]->fname, s->mList[i]->pCount / 2);
      }
    } else if (strcmp(choice, "delete") == 0) {
      if (scanf("%20s", name)){
        if (!deleteModel(s, name)) {
          fprintf(stderr, "Command %d invalid\n", cmd);
        }
      } else {
        goto invalid;
      }
    } else if (strcmp(choice, "copy") == 0) {
      char dname[NAME_LIMIT + 1];
      if (scanf("%20s %20s", dname, name) == 2) {
        for (int i = 0; i < s->mCount; i++){
          if (strcmp(s->mList[i]->name, name) == 0){
            m = loadModel(s->mList[i]->fname);
            break;
          }
        }
        strcpy(m->name, dname);
        if (!addModel(s, m)) {
          fprintf(stderr, "Command %d invalid\n", cmd);
        }
      } else {
        goto invalid;
      }
    } else if (strcmp(choice, "save") == 0) {
      if (scanf("%20s", name) == 1) {
        saveScene(s, name);
      } else {
        goto invalid;
      }
    } else if (strcmp(choice, "quit") == 0) {
      freeScene(s);
      break;
    } else { //invalid input
      invalid: fprintf(stderr, "Command %d invalid\n", cmd);
      scanf("%*[^\n]s");
    }
    printf("cmd %d> ", ++cmd);
  }
  return 0;
}
