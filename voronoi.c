/**
   @file voronoi.c
   @author Wenting Zheng (wzheng8)
   
   this program is to print an image file according to the input file
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define MAX_INTENSITY 255
#define MAX_ROW 100
#define INVALID_EXIT 100
#define TOTAL_INPUTS 6

/** x value of first point */
double x1;
/** y value of first point */
double y1;
/** x value of second point */
double x2;
/** y value of second point */
double y2;
/** x value of third point */
double x3;
/** y value of third point */
double y3;

/**
  Return true if the given pixel is the closest one to the given point
  
  @param col x value of the given point
  @param row y value of the given point
  @param x value of one of the input points
  @param y value of one of the input points
  
  @return true if the given pixel is the closest one to the given point
 */
bool nearestPoint( int col, int row, double x, double y )
{
  if (col == round(x) && row == round(y)) {
    return true;
  } else {
    return false;
  }
}

/**
  Prints out the right color for the pixel:
  the region closest to the first point in red,
  the region closest to the second point in green
  the region closest to the third in blue
  
  @param col x value of the given point
  @param row y value of the given point
 */
void chooseColor( int col, int row )
{
  if (nearestPoint(col, row, x1, y1) || nearestPoint(col, row, x2, y2) ||
  nearestPoint(col, row, x3, y3)) {
    printf("%3d %3d %3d ", MAX_INTENSITY, MAX_INTENSITY, MAX_INTENSITY);
  } else {
    double d1 = (col - x1) * (col - x1) + (row - y1) * (row - y1);
    double d2 = (col - x2) * (col - x2) + (row - y2) * (row - y2);
    double d3 = (col - x3) * (col - x3) + (row - y3) * (row - y3);
    if (d1 <= d2)   {
      if (d3 <= d1) {//d3<d1<d2 blue
        printf("%3d %3d %3d ", 0, 0, MAX_INTENSITY);
      } else {//d1<d3<d2 or d1<d2<d3 red
        printf("%3d %3d %3d ", MAX_INTENSITY, 0, 0);
      }
    } else { //d2<d1
      if (d3 <= d2) {//d3<d2<d1 blue
        printf("%3d %3d %3d ", 0, 0, MAX_INTENSITY);
      } else {//d2<d3<d1 or d2<d1<d3 green
        printf("%3d %3d %3d ", 0, MAX_INTENSITY, 0);
      }
    }
  }
}

/**
  Program starting point, reads input from the standard file and writes image out
  to output file
  
  @return program exit status
*/
int main()
{
  int numbers = scanf(" %lf  %lf\n %lf  %lf\n %lf  %lf", &x1, &y1, &x2, &y2, &x3, &y3);
  if (numbers != TOTAL_INPUTS) {
    printf("Invalid input\n");
    return INVALID_EXIT;
  }
  printf("P3\n");
  printf("%d %d\n", MAX_ROW, MAX_ROW);
  printf("%d\n", MAX_INTENSITY);
  for (int i = 0; i < MAX_ROW; i++) { //row
    for (int j = 0; j < MAX_ROW; j++) { //col
      chooseColor(j, i);
    }
    printf("\n");
  }
  return EXIT_SUCCESS;
}
