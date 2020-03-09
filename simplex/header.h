#include<stdio.h>
#include<stdlib.h>
#include<math.h>
void Data();
void Pivot();
void Formula();
void Optimize();
void Simplex();
void Results();
static const double epsilon   = 1.0e-8;
void print_tableau();
void nl(int k);
int equal(double a, double b);
