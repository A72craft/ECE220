/* partner: jinj2(me)
 *bug1: a missing ";" in the main.c, line 26
 *    :the code will not compile when it's missing
 *bug2: at line 44(the second for), it should be < instead of <=
 *    :the code will check the number itself, which is not what we want
 *bug3: ret should be 1 if there is a semiprime
 *    :if missing, the code will not return the correct value
 *bug4: at line28, is_prime should return 0 iff
 *      the remainder is zero and the number does not equal i
 *    :the code will have trouble checking primes if not corrected
 *bug5:at print_semiprime,the function should exit the
 *     check semiprime loop with a break
 *    :when the number is a confirmed semiprime, the code should break
 *     and start to check the next number in the range
 *bug6:at line50, it should be k = i/j
 *    :the k will always equal to 0 if k=i%j, which is not something we want
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
        if (number % i == 0 && number!=i) { //check if the remainder is 0
            return 0;
        }
    }
    return 1;
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
        for (j = 2; j < i; j++) {
            if (i%j == 0) {
                if (is_prime(j)) {
                    k = i/j;
                    if (is_prime(k)) {
                        printf("%d ", i);
			ret = 1;
			break;
                    }
                }
            }
        }

    }
    printf("\n");
    return ret;

}
