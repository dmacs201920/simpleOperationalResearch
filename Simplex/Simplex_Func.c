#define CMAX 10
#define VMAX 10
#include "Simplex_Header.h"
int NC, NV, NOPTIMAL=1,P1,P2,XERR;
char R;
double array[CMAX][VMAX];
FILE *f;
void Data(int argc,char *argv[]) 
{
  double R1,R2;
  int i,j;
  f = fopen(argv[1],"a");
  if (f == NULL)
  { printf("file doesn't exist\n");
    exit(-1);
  }
  printf(" SIMPLEX METHOD\n\n");
  printf(" MAXIMIZE (Y/N) ? ");
  scanf("%c", &R);
  printf("\n NUMBER OF VARIABLES OF THE FUNCTION ? ");
  scanf("%d", &NV);
  printf("\n NUMBER OF CONSTRAINTS ? ");
  scanf("%d", &NC);
  fprintf(f,"\n SIMPLEX METHOD\n\n");
  fprintf(f," MAXIMIZE (Y/N) ? ");
  fprintf(f,"%c\n",R);
  fprintf(f,"\n NUMBER OF VARIABLES OF THE FUNCTION ? ");
  fprintf(f,"%d\n",NV);
  fprintf(f,"\n NUMBER OF CONSTRAINTS ? ");
  fprintf(f,"%d\n",NC);
  if (R == 'Y' || R=='y')
  {
    printf("\n 'MAXIMIZING' \n");
    fprintf(f,"\n 'MAXIMIZING' \n");
    fprintf(f,"\n");
    R1 = 1.0;
  }
  else
  {
    printf("\n 'MINIMIZING' \n");
    fprintf(f,"\n 'MINIMIZING' \n");
    fprintf(f,"\n");
    R1 = -1.0;
  }
  printf("\n INPUT COEFFICIENTS OF THE FUNCTION:\n");
  fprintf(f,"\n INPUT COEFFICIENTS OF THE FUNCTION:\n");
  for (j = 1; j<=NV; j++)
  {
    printf(" x%d ? ", j); 
    fprintf(f," x%d ? ", j); 
    scanf("%lf", &R2);
    fprintf(f," %6.3lf\n", R2);
    array[1][j+1] = R2 * R1;
  }
  fprintf(f," Right hand side ? "); 
  printf(" Right hand side ? "); 
  scanf("%lf", &R2);
  fprintf(f," %6.3lf\n", R2);
  array[1][1] = R2 * R1;
  for (i = 1; i<=NC; i++) 
  {
    printf("\n CONSTRAINT #%d:\n", i);
    fprintf(f,"\n CONSTRAINT #%d:\n", i);
    for (j = 1; j<=NV; j++) 
    {
      printf(" x%d ? ", j); 
      fprintf(f," x%d ? ", j); 
      scanf("%lf", &R2);
      fprintf(f,"%6.3lf\n",R2);
      array[i + 1][j + 1] = -R2;
    }
    printf(" Right hand side ? ");
    fprintf(f," Right hand side ? ");
    scanf("%lf", &array[i+1][1]);
    fprintf(f,"%6.3lf\n",array[i+1][1]);
  }
  for(j=1; j<=NV; j++) 
    array[0][j+1] = j;
  for(i=NV+1; i<=NV+NC; i++) 
    array[i-NV+1][0] = i;
}
void Pivot();
void Formula();
void Optimize();
void Simplex() 
{
  while(NOPTIMAL==1){
    Pivot();
    Formula();
    Optimize();
  }
}
void Pivot() 
{
  double RAP,V,XMAX;
  int i,j;
  XMAX = 0.0;
  for(j=2; j<=NV+1; j++)
  {
    if (array[1][j] > 0.0 && array[1][j] > XMAX)
    {
      XMAX = array[1][j];
      P2 = j;
    }
  }
  RAP = 999999.0;
  for (i=2; i<=NC+1; i++)
  {
    if (array[i][P2] >= 0.0) 
      continue;
    V = fabs(array[i][1] / array[i][P2]);
    if (V < RAP)
    {
      RAP = V;
      P1 = i;
    }
  }
  V = array[0][P2];
  array[0][P2] = array[P1][0];
  array[P1][0] = V;
}
void Formula() 
{;
  int i,j;
  for (i=1; i<=NC+1; i++)
  {
    if (i == P1)
      continue;
    for (j=1; j<=NV+1; j++)
    {
      if (j == P2)
        continue;
      array[i][j] -= array[P1][j] * array[i][P2] / array[P1][P2];
    }
  }
  array[P1][P2] = 1.0 / array[P1][P2];
  for (j=1; j<=NV+1; j++)
  {
    if (j == P2)
      continue;
    array[P1][j] *= fabs(array[P1][P2]);
  }
  for (i=1; i<=NC+1; i++)
  {
    if (i == P1 )
      continue;
    array[i][P2] *= array[P1][P2];
  }
}
void Optimize()
{
  int i,j;
  for (i=2; i<=NC+1; i++)
    if (array[i][1] < 0.0)
      XERR = 1;
  NOPTIMAL = 0;
  if (XERR == 1)
    return;
  for (j=2; j<=NV+1; j++)
    if (array[1][j] > 0.0)
      NOPTIMAL = 1;
}
void Results() 
{
  int pseudo=0;
  printf("\n\n RESULTS:\n\n");
  fprintf(f,"\n\n RESULTS:\n\n");
  int i,j;
  if (XERR != 0){
    printf(" NO SOLUTION.\n");
    fprintf(f," NO SOLUTION.\n");
    printf("\n");
    fprintf(f,"\n");
  nl(100);
    return;
  }
  print_tableau();
  for (i=1; i<=NV; i++)
    for (j=2; j<=NC+1; j++) 
    {
      if (array[j][0] != 1.0*i){
        pseudo=1;
        continue;
      }
      printf(" VARIABLE #%d: %6.3lf\n", i, array[j][1]);
      fprintf(f," VARIABLE #%d: %6.3lf\n", i, array[j][1]);
    }
  printf("\n ECONOMIC FUNCTION: %6.3lf\n", array[1][1]);
  fprintf(f,"\n ECONOMIC FUNCTION: %6.3lf\n", array[1][1]);
  printf("\n");
  fprintf(f,"\n");
  if(pseudo==1){
    printf("\n This is a pseudo optima solution.....\n");
    fprintf(f,"\n This is a pseudo optima solution.....\n");
  }
  nl(100);
}

void print_tableau()
{
  nl(70);
  int i=0, j=1;
  printf("\nFinal Tableau\n\n");
  fprintf(f,"\nFinal Tableau\n\n");
  nl(50);
  printf("%-6s%5s", "Basic:", "Sol.");
  fprintf(f,"%-6s%5s", "Basic:", "Sol.");
  for(j=1;j<NV+1; j++) 
  {
    printf("    x%d", (int)array[0][j+1]); 
    fprintf(f,"    x%d", (int)array[0][j+1]); 
  } 
  printf("\n");
  fprintf(f,"\n");

  for(i=0;i<NC+1; i++) 
  {
    if (i==0)
    {
      if(R=='1')
      {
        printf("MIN:"); 
        fprintf(f,"MIN:"); 
      }
      else
      {
        printf("MAX:");
        fprintf(f,"MAX:");
      }
    }
    else
    {
      printf("x%d: ", (int)array[i+1][0]);
      fprintf(f,"x%d: ", (int)array[i+1][0]);
    }
    for(j=0;j<NV+1; j++) 
    {
      if(j!=0){
        printf(" %6.3lf", -array[i+1][j+1]);
        fprintf(f," %6.3lf", -array[i+1][j+1]);
      }
      else{
        printf(" %6.3lf", array[i+1][j+1]);
        fprintf(f," %6.3lf", array[i+1][j+1]);
      }
    }
    printf("\n");
    fprintf(f,"\n");
  }
  nl(50);
  printf("\n");
  nl(70);
}

void nl(int k)
{   
  int j; 
  for(j=0;j<k;j++) 
  {
    putchar('-');
    putc('-',f);
  }
  putchar('\n'); 
  putc('\n',f);
}
