#define CMAX 10
#define VMAX 10
#include "header.h"
int NC, NV, NOPTIMAL,P1,P2,XERR;
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
    printf("\n SIMPLEX METHOD\n\n");
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
	fprintf(f,"\n");
	R1 = 1.0;
    }
    else
    {
	printf("\n 'MINIMIZING' \n");
	fprintf(f,"\n");
	fputc (1,f);
	R1 = -1.0;
    }
    printf("\n INPUT COEFFICIENTS OF THE FUNCTION:\n");
    fprintf(f,"\n INPUT COEFFICIENTS OF THE FUNCTION:\n");
    for (j = 1; j<=NV; j++)
    {
	printf(" #%d ? ", j); 
	fprintf(f," #%d ? ", j); 
	scanf("%lf", &R2);
	fprintf(f," %lf\n", R2);
	array[1][j+1] = R2 * R1;
    }
    fprintf(f," Right hand side ? "); 
    fputc (1,f);
    printf(" Right hand side ? "); 
    fscanf(f,"%lf", &R2);
    fputc (1,f);
    scanf("%lf", &R2);
    fscanf(f,"%lf", &R2);
    fputc (1,f);
    array[1][1] = R2 * R1;
    for (i = 1; i<=NC; i++) 
    {
	printf("\n CONSTRAINT #%d:\n", i);
	fprintf(f,"\n CONSTRAINT #%d:\n", i);
	fputc (1,f);
	for (j = 1; j<=NV; j++) 
	{
	    printf(" #%d ? ", j); 
	    fprintf(f," #%d ? ", j); 
	    fputc (1,f);
	    scanf("%lf", &R2);
	    fscanf(f,"%lf", &R2);
	    fputc (1,f);
	    array[i + 1][j + 1] = -R2;
	}
	printf(" Right hand side ? ");
	fprintf(f," Right hand side ? ");
	fputc (1,f);
	scanf("%lf", &array[i+1][1]);
	fscanf(f,"%lf", &array[i+1][1]);
	fputc (1,f);
    }
    printf("\n\n RESULTS:\n\n");
    fprintf(f,"\n\n RESULTS:\n\n");
    fputc (1,f);
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
Repeat: Pivot();
	Formula();
	Optimize();
	if (NOPTIMAL == 1)
	    goto Repeat;
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
	    goto Repeat;
	V = fabs(array[i][1] / array[i][P2]);
	if (V < RAP)
	{
	    RAP = V;
	    P1 = i;
	}
Repeat:;}
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
	    goto Break2;
	for (j=1; j<=NV+1; j++)
	{
	    if (j == P2)
		goto Break1;
	    array[i][j] -= array[P1][j] * array[i][P2] / array[P1][P2];
Break1:;}
Break2:;}
    array[P1][P2] = 1.0 / array[P1][P2];
    for (j=1; j<=NV+1; j++)
    {
	if (j == P2)
	    goto Break0;
	array[P1][j] *= fabs(array[P1][P2]);
Break0:;}
    for (i=1; i<=NC+1; i++)
    {
	if (i == P1 )
	    goto Break3;
	array[i][P2] *= array[P1][P2];
Break3:;}
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
    int i,j;
    if (XERR == 0)
	goto PrintSol;
    printf(" NO SOLUTION.\n");
    fprintf(f," NO SOLUTION.\n");
    fputc (1,f);
    goto End0;
PrintSol:
    for (i=1; i<=NV; i++)
	for (j=2; j<=NC+1; j++) 
	{
	    if (array[j][0] != 1.0*i) 
		goto End1;
	    printf(" VARIABLE #%d: %f\n", i, array[j][1]);
	    fprintf(f," VARIABLE #%d: %f\n", i, array[j][1]);
	    fputc (1,f);
End1: ;}
    print_tableau();
    printf("\n ECONOMIC FUNCTION: %f\n", array[1][1]);
    fprintf(f,"\n ECONOMIC FUNCTION: %f\n", array[1][1]);
    fputc (1,f);
End0:
    printf("\n");
    fprintf(f,"\n");
}

void print_tableau()
{
    int i, j;
    printf("\nFinal Tableau\n");
    nl(60);
    printf("%-6s%5s", "col:", "b[i]");
    for(j=1;j<NV+1; j++) { printf("    x%d,", (int)array[0][j+1]); } printf("\n");

    for(i=0;i<NC+1; i++) 
    {
	if (i==0)
	{
	    if(R=='1')
		printf("MAX:"); 
	    else
		printf("MIN:");
	}
	else
	    printf("x%d: ", (int)array[i+1][0]);
	for(j=0;j<NV+1; j++) 
	{
	    if ( equal( (int)array[i+1][j+1] , array[i+1][j+1] ) )
		printf(" %6d", (int)array[i+1][j+1]);
	    else
		printf(" %6.2lf", array[i+1][j+1]);
	}
	printf("\n");
    }
    nl(60);
}

void nl(int k)
{   
    int j; 
    for(j=0;j<k;j++) 
	putchar('-');
    putchar('\n'); 
}

int equal(double a, double b) 
{   
    return fabs(a-b) < epsilon; 
}
