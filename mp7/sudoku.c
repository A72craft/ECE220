/*

*/
#include "sudoku.h"
int is_val_in_row(const int val, const int i, const int sudoku[9][9]);
int is_val_in_col(const int val, const int j, const int sudoku[9][9]);
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]);
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]);
int cells_full(const int sudoku[9][9]);

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);
	for (int j = 0;j<9;j++){
		if (sudoku[i][j]==val)
			return 1;} 
  return 0;
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);
	for (int i = 0;i<9;i++){
		if (sudoku[i][j]==val)
			return 1;} 
  return 0;

}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9);
	int col,row;
	col = j/3; //col have 3 cases, 0,1,2, which corresponds to the 3 columns of the 3X3
	row = i/3; //row have 3 cases, 0,1,2, which corresponds to the 3 rows of 3X3
  	int new_row = row*3;
	int new_col = col*3;
	for (int r = new_row;r<new_row+3;r++){
		for (int c = new_col;c<new_col+3;c++){
			if (sudoku[r][c]==val)
				return 1;}}
  return 0;

}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);
	if (is_val_in_row(val,i,sudoku)==1)
		return 0;
	if (is_val_in_col(val,j,sudoku)==1)
		return 0;
	if (is_val_in_3x3_zone(val,i,j,sudoku)==1)
		return 0;

  return 1;

}

int cells_full(const int sudoku[9][9]){
	for (int i = 0;i<9;i++){
		for (int j =0;j<9;j++){
			if (sudoku[i][j]==0)
				return 0;}}
	return 1;
}

int cells_not_full(const int sudoku[9][9]){
	for (int i = 0;i<9;i++){
		for (int j =0;j<9;j++){
			if (sudoku[i][j]==0)
			return i,j;}}   //It can not pass 2 values. use pointer instead
}


// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {
	int i,j;
	if (cells_full(sudoku)==1)
		return 1;
	else
		i,j = cells_not_full(sudoku);
	for (int val = 1;val<=9;val++){
		if (is_val_valid(val,i,j,sudoku)==1){
			sudoku[i][j] = val;
			if (solve_sudoku(sudoku))
				return 1;
			sudoku[i][j] = 0;
			}
	}

  return 0;
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}





