/*partners: jinj2(me)
 *This program prints a specific row of the
 *"pascal's triangle". To do it, it takes the
 *input of the row that the users want, and 
 *calculate and print each of the coefficients
 *until the whole row has been printed out.
 */
#include <stdio.h>
#include <stdlib.h>

int main(){
  int row,k,x,n; /*these are the counters and variables*/
  unsigned long int result,up;
  result = 1;
  x = 0;
  n = 0;  /*assign value to the variables*/
  k =1;
  printf("Enter a row index: "); /*ask for the input*/
  scanf("%d",&row);    /*get the input*/
  n =row;     /*set the variable used in calculation*/
  x = row;     /*set the counter to the row*/
  printf("1 "); /*print the first number in every row*/
   x = x - 1;
  while(x == 0 || x>0){
    up = n+1-k;
   result = result * up; 
   result = result/k;   /*the calculation*/
   printf("%lu ",result);
   x = x-1; /*counter decrease by one*/
   k++;
}

  return 0;
}
