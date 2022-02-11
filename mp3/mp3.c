/*group members: jinj2(me)
 *
 *
 *
 */
#include <stdio.h>
#include <stdlib.h>

int main(){
  int row,k,x,n;
  unsigned long int result,up;
  result = 1;
  x = 0;
  n = 0;
  k =1;
  printf("Enter a row index: ");
  scanf("%d",&row);
  n =row;
  x = row;
   printf("1 ");
   x = x - 1;
  while(x == 0 || x>0){
    up = n+1-k;
   result = result * up;
   result = result/k;
   printf("%lu ",result);
   x = x-1;
   k++;
}

  return 0;
}
