/* partner: jinj2(me)
 *bug1: a missing ";" in the main.c, line 26
 *bug2: at line 41, it should be <= instead of <
 *bug3: ret should be 1 if there is a semiprime
 *bug4: at line23, it should be < instead of <=
 */



#include <stdlib.h>
#include <stdio.h>


/*
 * is_prime: determines whether the provided number is prime or not
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number)
{
    int i;
    if (number == 1) {return 0;}
    for (i = 2; i <= number; i++) { //for each number smaller than it
        if (number % i == 0) { //check if the remainder is 0
            return 1;
        }
    }
    return 0;
}


/*
 * print_semiprimes: prints all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b)
{
    int i, j, k;
    int ret = 0;
    for (i = a; i <=b; i++) { //for each item in interval
        //check if semiprime
        for (j = 2; j <= i; j++) {
            if (i%j == 0) {
                if (is_prime(j)) {
                    k = i%j;
                    if (is_prime(k)) {
                        printf("%d ", i);
			ret = 1;
                    }
                }
            }
        }

    }
    printf("\n");
    return ret;

}
