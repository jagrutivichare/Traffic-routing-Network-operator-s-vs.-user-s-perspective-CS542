#include <stdlib.h>
#include <stdio.h>


float A=0,c1=0,c2=0,a1,a2,f1,f2,controlVar1,controlVar2,totalDelay;

static void printResult()
{
  (void) printf("Control variable a1 = %.2f  \n", controlVar1/100);
  (void) printf("Control variable a2 = %.2f  \n", controlVar2/100);
  (void) printf("Total Delay = %.2f \n", totalDelay);
}

static float calculateTotalDelay(float a1,float a2,float f1,float f2)
{
  float d1,d2;
   if (a1 != 0){
      d1 = 1/(c1-f1);
    } else {
      d1=0;
    }
    if (a2 != 0){
      d2 = 1/(c2-f2);
    } else {
      d2=0;
    }
    return (d1+d2);
}

static void calculateFinalResult(float a1,float a2,float f1,float f2)
{
    float totaltempDelay=calculateTotalDelay(a1,a2,f1,f2);
    if (totalDelay > totaltempDelay) {
      totalDelay = totaltempDelay;
      controlVar1 = a1;
      controlVar2 = a2;
    }
}

static float calculateTrafficIntensity(float a)
{
  return ((a/100)*A);
}

static void takeUserInputs()
{
   printf("Please input allocated traffic (A): ");
   scanf("%f", &A);
   while (A >= (c1+c2)) {
     printf("Please input capacity of route 1 (c1): ");
     scanf("%f", &c1);
     printf("Please input capacity of route 2 (c2): ");
     scanf("%f", &c2);
   }
}

static void initialise()
{
  controlVar1=0,controlVar2=0,totalDelay=100;
}

int main()
{
  initialise();
  takeUserInputs();
  (void) printf("\nFetching result for network operator...\n");
  for (a1=100;a1>=0;a1--) {
    a2 = 100-a1;
    f1 = calculateTrafficIntensity(a1);
    f2 = calculateTrafficIntensity(a2);
    if (f1 <= c1 && f2 <= c2) {
	calculateFinalResult(a1,a2,f1,f2);
     }
  }
  printResult();
  printf("\n");
  getch();
}
