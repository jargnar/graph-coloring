#ifndef COLORIZE_H
#define COLORIZE_H

extern int colors;
extern int Vcolor[100];
extern int possible[100][100];
extern int Psize;
extern int spilledV[100];
extern int spilledVsize;

extern void setColors(int);
extern void simplify();
extern void select(int);
extern void spill(int);
extern int getColor(int);

#endif

