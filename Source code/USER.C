#include <stdlib.h>
#include <stdio.h>


float A=0,c1=0,c2=0,c3=0,a1,a2,controlVar1,controlVar2,controlVar3,totalDelay;

static void printResult()
{
  (void) printf("Control variable a1 = %.2f  \n", controlVar1/100);
  (void) printf("Control variable a2 = %.2f  \n", controlVar2/100);
  (void) printf("Control variable a3 = %.2f  \n", controlVar3/100);
  (void) printf("Total Delay = %.2f \n", totalDelay);
}

static float calculateTotalDelay(float a1,float a2,float a3,float f1,float f2,float f3)
{
  float d1,d2,d3;
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
    if (a3 != 0){
      d3 = 1/(c3-f3);
    } else {
      d3=0;
    }
    return (d1+d2+d3);
}

static void calculateFinalResult(float a1,float a2,float a3,float f1,float f2,float f3)
{
    float totaltempDelay=calculateTotalDelay(a1,a2,a3,f1,f2,f3);
    if (totalDelay > totaltempDelay) {
      totalDelay = totaltempDelay;
      controlVar1 = a1;
      controlVar2 = a2;
      controlVar3 = a3;
    }
}

static void calculateTrafficIntensity(float a1,float a2,float a3)
{
   float f1 = ((a1/100)*A);
   float f2 = ((a2/100)*A);
   float f3 = ((a3/100)*A);
   if (f1<=c1 && f2<=c2 && f3<=c3) {
      calculateFinalResult(a1,a2,a3,f1,f2,f3);
   }
   
}

static void takeUserInputs()
{
   printf("Please input allocated traffic (A): ");
   scanf("%f", &A);
   while (A >= (c1+c2+c3)) {
     printf("Please input capacity of route 1 (c1): ");
     scanf("%f", &c1);
     printf("Please input capacity of route 2 (c2): ");
     scanf("%f", &c2);
     printf("Please input capacity of route 3 (c3): ");
     scanf("%f", &c3);
   }
}

static void initialise()
{
  controlVar1=0,controlVar2=0,controlVar3=0,totalDelay=100;
}

int main()
{
  initialise();
  takeUserInputs();
  (void) printf("\nFetching result for a user...\n");
  for (a1=0;a1<=100;a1++){
    for (a2=0;a2<=100;a2++){
      if (a1+a2==100){
	calculateTrafficIntensity(a1,a2,0);
      } else if ((a1+a2)<100){
	float a3=100-(a1+a2);
	calculateTrafficIntensity(a1,a2,a3);
      } else {
	/*Do nothing*/
      }
    }
  }
  printResult();
  getch();
}