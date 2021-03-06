/*
partner: jinj2(me)
Besides the three function provided in the OG code, I also
wrote 3 extra functions.
1.one_to_eight:this function check whether the 4 inputs are 
  between 1 to 8.
2.perfect_guess:this function takes in 4 array(sol,guess,sol_pair,
  guess_pair). When the solution is equal to the guess, both is marked 
  as paired and the number of perfect_guess is returned.
3.misplace_guess:this function takees in 4 array(sol,guess,sol_pair,
  guess_pair). It will first check if the guess is paired.If not, it will
  be compared to all the not-paired solutions, and both will be marked paired 
  if they are equal. The number of misplaced guesses are returned.
*/
#include <stdio.h>
#include <stdlib.h>

#include "prog5.h"

static int guess_number;
static int solution1;
static int solution2;
static int solution3;
static int solution4;


/*this function check whether the 4 inputs are between 1 and 8.
If not, return 0*/
int one_to_eight(const int w,int x,int y,int z){
	if( w<1 || w>8){
		return 0;}
	if( x<1 || x>8){
		return 0;}
	if( y<1 || y>8){
		return 0;}
	if( z<1 || z>8){
		return 0;}
	return 1;}

/*this function "perfect guess" takes 4 arrays(solution,guess, and their pairing status)
and compares the solution to the guess. If is the same, both the pairing 
status are 1 and perfect is increased by one*/
int perfect_guess(int sol[4],int guess[4],int sol_pair[4],int guess_pair[4]){
	int i;
	int perfect=0;
	for (i = 0;i<4;i++){   //check all 4 numbers
		if (sol[i] == guess[i]){
			sol_pair[i] = 1;    //if paired, set the pairing status
			guess_pair[i] = 1;  //for both to be 1
			perfect = perfect + 1;}  //increment by one 
			}
	return perfect;}

/*this function "misplace_guess" takes 4 arrays(solution,guess, and their pairing status)
and compares the guess to all the solution. Both the status of them needs to be
available. It will compare all available guess to all available solutions,
setting the status to 1 if is the same and add 1 to misplaced*/
int misplace_guess(int sol[4],int guess[4],int sol_pair[4],int guess_pair[4]){
	int i ; //i for guess
	int j ; //j for solution
	int misplace = 0;
	for (i = 0;i<4;i++){   //for all guesses
		if (guess_pair[i] ==0){  //if not marked as paired 
			for (j=0;j<4;j++){  //then for all solution
				if (guess[i]==sol[j] && sol_pair[j] == 0){  //check if are the same AND solution is not paired
					guess_pair[i] = 1;  //then mark as paired
					sol_pair[j] = 1;
					misplace = misplace + 1;   //increment by one 
					break;}
				}
		}
	}
	return misplace;}
/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the 
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid. 
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */
int
set_seed (const char seed_str[])
{
  int seed; //the int treated as seed
  int return_value;  //return value of sscanf
  int ret;  //the final return value of the function
  char post[2];  //stuff
  return_value = sscanf (seed_str, "%d%1s", &seed, post); //scan the string input
 if(return_value==1){
   srand(seed);  //since only the int was read,set the seed and ret 1
   ret = 1;}
 else{
   ret = 0;  //something else is read. Ret 0 and print the error message
   printf("set_seed: invalid seed\n");}
   
    return ret;
}


/*
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above. 
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 * INPUTS: none
 * OUTPUTS: *one -- the first solution value (between 1 and 8)
 *          *two -- the second solution value (between 1 and 8)
 *          *three -- the third solution value (between 1 and 8)
 *          *four -- the fourth solution value (between 1 and 8)
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */
void
start_game (int* one, int* two, int* three, int* four)
{
  *one = (rand()%8)+1;  //set the number for all four solutions
  solution1 = *one;
    *two = (rand()%8)+1;
    solution2 = *two;
    *three = (rand()%8)+1;
    solution3 = *three;
    *four = (rand()%8)+1;
  solution4 = *four;
    guess_number = 1;

}

/*
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str. 
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 integers, within the range 1-8). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format
 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
 *               If valid, the guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: the following are only valid if the function returns 1 (A valid guess)
 *          *one -- the first guess value (between 1 and 8)
 *          *two -- the second guess value (between 1 and 8)
 *          *three -- the third guess value (between 1 and 8)
 *          *four -- the fourth color value (between 1 and 8)
 * RETURN VALUE: 1 if the guess string is valid (the guess contains exactly four
 *               numbers between 1 and 8), or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess) 
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */
int
make_guess (const char guess_str[], int* one, int* two, 
	    int* three, int* four)
{
	int guess_pair[4]={0};   //initalize all the variables
	int sol_pair[4]={0};
	int guess[4]; int sol[4];
	int perfect=0;int misplace = 0;
	int w,x,y,z,ret_scanf,ret18;
	char post[2];
	ret_scanf = sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post);
	if (ret_scanf != 4 ){
		printf("make_guess: invalid guess\n");  //check if the input is valid
		return 0;}
	ret18 = one_to_eight(w,x,y,z);
	if (ret18 == 0){                           //check if the number is between 1 and 8
		printf("make_guess: invalid guess\n");
		return 0;}
	guess[0] = w;*one = w;   //put the guessed number in pointers and arrays
	guess[1] = x;*two = x;
	guess[2] = y;*three = y;
	guess[3] = z;*four = z;
	sol[0] = solution1;      //put the solutions in the solution array
	sol[1] = solution2;
	sol[2] = solution3;
	sol[3] = solution4;
	perfect = perfect_guess(sol,guess,sol_pair,guess_pair); //call perfect_guess 
	misplace = misplace_guess(sol,guess,sol_pair,guess_pair);  //call misplace__guess
	printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n",guess_number, perfect,misplace);
	guess_number = guess_number + 1; //increment by one
    return 1;
}

	

