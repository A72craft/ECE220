/* partner: jinj2(me)
* This code contains the function that will make the game,remake the game, check for cells,
*move the game in four directions, and check if anything else can be moved. Apart from the 
*given function I also created one that will copy a array.
*/
#include "game.h"
void copy_array(const int array[],int copy[], int size);
void copy_array(const int array[],int copy[], int size){
	for (int i = 0;i<size;i++){
		copy[i]=array[i];}
}

game * make_game(int rows, int cols)
{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));

	mygame->rows = rows;
	mygame->cols = cols;  //initialize all variables
	mygame->score = 0;
	for (int i = 0;i<rows;i++){
		for (int j = 0; j<cols;j++){  //for all cells, assign -1
			mygame->cells[i*cols+j] = -1;}}
    return mygame;
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
{
	/*Frees dynamically allocated memory used by cells in previous game,
	 then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
	free((*_cur_game_ptr)->cells);
	(*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));

	(*_cur_game_ptr)->rows = new_rows;
	(*_cur_game_ptr)->cols = new_cols;  //Re-initialize all variables
	(*_cur_game_ptr)->score = 0;
	for (int i = 0;i<new_rows;i++){
		for (int j = 0; j<new_cols;j++){  //for all cells, assign -1
			(*_cur_game_ptr)->cells[i*new_cols+j] = -1;}}
	return;	
}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)
{
	int r = cur_game->rows;
	int c = cur_game->cols;  //retrive the data
	cell * acell;
	if(row < 0 || col < 0 || row>=r || col>=c)  //if out of bounds
    return NULL;   //return null
	else{
	acell = &cur_game->cells[(row)*c+col];  //assign the pointer
	return acell;}
}


int move_w(game * cur_game)
{
    //YOUR CODE STARTS HERE
	int rows = cur_game->rows; // get the rows and columns
	int cols = cur_game->cols;
	int flag = 0;
///////////////////////////////////////////
	for (int j = 0;j<cols;j++){
		for (int i = 1;i<rows;i++){ //for every item,counting from top to bottom
			if(cur_game->cells[i*cols+j]!=-1){ //if not empty 
				for(int k = 0;k<i;k++){
					if(cur_game->cells[k*cols+j] == -1){ //if found an empty cell
						cur_game->cells[k*cols+j] = cur_game->cells[i*cols+j]; //put the value in the empty cell
						cur_game->cells[i*cols+j] = -1;  //set original to -1
						flag = 1;
						break;}}}}}
///////////////////////////////////////////
	for (int j = 0;j<cols;j++){
		for (int i = 0;i<rows-1;i++){ //for every item,counting from top to bottom
			if(cur_game->cells[i*cols+j]!=-1){ //if not empty 
				if(cur_game->cells[i*cols+j] == cur_game->cells[(i+1)*cols+j]){
					cur_game->cells[i*cols+j] = 2*cur_game->cells[i*cols+j];//merge by *2 the value and set the other to -1
					cur_game->cells[(i+1)*cols+j] = -1;
					cur_game->score = cur_game->score + 2*cur_game->cells[i*cols+j];
					flag = 1;}}}}
///////////////////////////////////////////
	for (int j = 0;j<cols;j++){
		for (int i = 1;i<rows;i++){ //for every item,counting from top to bottom
			if(cur_game->cells[i*cols+j]!=-1){ //if not empty 
				for(int k = 0;k<i;k++){
					if(cur_game->cells[k*cols+j] == -1){
						cur_game->cells[k*cols+j] = cur_game->cells[i*cols+j];
						cur_game->cells[i*cols+j] = -1;
						flag = 1;
						break;}}}}}
	if (flag == 0)
		return 0;
    return 1;
};

int move_s(game * cur_game) //slide down
{
    //YOUR CODE STARTS HERE
	int rows = cur_game->rows; // get the rows and columns
	int cols = cur_game->cols;
	int flag = 0;
	for (int j = 0;j<cols;j++){
		for (int i = rows-1;i>=0;i--){ //for every item,counting from bottom to top
			if(cur_game->cells[i*cols+j]!=-1){ //if not empty 
				for(int k = rows - 1;k>i;k--){
					if(cur_game->cells[k*cols+j] == -1){ //if found an empty cell
						cur_game->cells[k*cols+j] = cur_game->cells[i*cols+j]; //put the value in the empty cell
						cur_game->cells[i*cols+j] = -1; //set original to -1
						flag = 1;
						break;}}}}}
///////////////////////////////////////////
	for (int j = 0;j<cols;j++){
		for (int i = rows-1;i>0;i--){ //for every item,counting from top to bottom
			if(cur_game->cells[i*cols+j]!=-1){ //if not empty 
				if(cur_game->cells[i*cols+j] == cur_game->cells[(i-1)*cols+j]){
					cur_game->cells[i*cols+j] = 2*cur_game->cells[i*cols+j];//merge by *2 the value and set the other to -1
					cur_game->cells[(i-1)*cols+j] = -1;
					cur_game->score = cur_game->score + 2*cur_game->cells[i*cols+j];
					flag = 1;}}}}
///////////////////////////////////////////
	for (int j = 0;j<cols;j++){
		for (int i = rows-1;i>=0;i--){ //for every item,counting from bottom to top
			if(cur_game->cells[i*cols+j]!=-1){ //if not empty 
				for(int k = rows - 1;k>i;k--){
					if(cur_game->cells[k*cols+j] == -1){
						cur_game->cells[k*cols+j] = cur_game->cells[i*cols+j];
						cur_game->cells[i*cols+j] = -1;
						flag = 1;
						break;}}}}}
	if (flag == 0)
	return 0;
    return 1;
};

int move_a(game * cur_game) //slide left
{
    //YOUR CODE STARTS HERE
	int rows = cur_game->rows; // get the rows and columns
	int cols = cur_game->cols;
	int flag = 0;
	for (int i = 0;i<rows;i++){
		for (int j = 0;j<cols;j++){ //for every item,counting from left to right
			if(cur_game->cells[i*cols+j]!=-1){ //if not empty 
				for(int k = 0;k<j;k++){
					if(cur_game->cells[i*cols+k] == -1){ //if found an empty cell
						cur_game->cells[i*cols+k] = cur_game->cells[i*cols+j]; //put the value in the cell
						cur_game->cells[i*cols+j] = -1; //set original to -1
						flag = 1;
						break;}}}}}
///////////////////////////////////////////
	for (int i = 0;i<rows;i++){
		for (int j = 0;j<cols-1;j++){ //for every item,counting from top to bottom
			if(cur_game->cells[i*cols+j]!=-1){ //if not empty 
				if(cur_game->cells[i*cols+(j+1)] == cur_game->cells[i*cols+j]){
					cur_game->cells[i*cols+j] = 2*cur_game->cells[i*cols+j];//merge by *2 the value and set the other to -1
					cur_game->cells[i*cols+(j+1)] = -1;
					cur_game->score = cur_game->score + 2*cur_game->cells[i*cols+j];
					flag = 1;}}}}
///////////////////////////////////////////
	for (int i = 0;i<rows;i++){
		for (int j = 0;j<cols;j++){ //for every item,counting from top to bottom
			if(cur_game->cells[i*cols+j]!=-1){ //if not empty 
				for(int k = 0;k<j;k++){
					if(cur_game->cells[i*cols+k] == -1){
						cur_game->cells[i*cols+k] = cur_game->cells[i*cols+j];
						cur_game->cells[i*cols+j] = -1;
						flag = 1;
						break;}}}}}
	if (flag == 0)
	return 0;
    return 1;
};

int move_d(game * cur_game){ //slide to the right
    //YOUR CODE STARTS HERE
	int rows = cur_game->rows; // get the rows and columns
	int cols = cur_game->cols;
	int flag = 0;
	for (int i = 0;i<rows;i++){
		for (int j = cols - 1;j>=0;j--){ //for every item,counting from right to left
			if(cur_game->cells[i*cols+j]!=-1){ //if not empty 
				for(int k = cols - 1;k>j;k--){
					if(cur_game->cells[i*cols+k] == -1){ //if found an empty cell
						cur_game->cells[i*cols+k] = cur_game->cells[i*cols+j]; //put the value in the empty cell
						cur_game->cells[i*cols+j] = -1; //set original to -1
						flag = 1;
						break;}}}}}
///////////////////////////////////////////
	for (int i = 0;i<rows;i++){
		for (int j = cols - 1;j>0;j--){ //for every item,counting from top to bottom
			if(cur_game->cells[i*cols+j]!=-1){ //if not empty 
				if(cur_game->cells[i*cols+(j-1)] == cur_game->cells[i*cols+j]){
					cur_game->cells[i*cols+j] = 2*cur_game->cells[i*cols+j]; //merge by *2 the value and set the other to -1
					cur_game->cells[i*cols+(j-1)] = -1;
					cur_game->score = cur_game->score + 2*cur_game->cells[i*cols+j];
					flag = 1;}}}}
///////////////////////////////////////////
	for (int i = 0;i<rows;i++){
		for (int j = cols - 1;j>=0;j--){ //for every item,counting from top to bottom
			if(cur_game->cells[i*cols+j]!=-1){ //if not empty 
				for(int k = cols - 1;k>j;k--){
					if(cur_game->cells[i*cols+k] == -1){
						cur_game->cells[i*cols+k] = cur_game->cells[i*cols+j];
						cur_game->cells[i*cols+j] = -1;
						flag = 1;
						break;}}}}}
	if (flag == 0)
	return 0;
    return 1;
};

int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
	Return 1 if there are possible legal moves, 0 if there are none.
 */
{
    //YOUR CODE STARTS HERE
	int rows = cur_game->rows; // get the rows and columns
	int cols = cur_game->cols;
	int size = rows*cols;
	int copy[size];
	int i,j;
	copy_array(cur_game->cells,copy,size);
	for(i =0;i<rows;i++){
		for (j = 0;j<cols;j++){  //find if there is an empty cell
			if(copy[i*cols+j] == -1)
			return 1;}}
	for(i =0;i<rows;i++){
		for (j = 0;j<cols;j++){
		if( i == 0 && j == 0){   //case: upperleftmost
			if(copy[i*cols+j] == copy[(i+1)*cols+j] || copy[i*cols+j] == copy[i*cols+j+1])
			return 1;}
		else if( i == 0 && j == cols-1){   //case: upperightmost
			if(copy[i*cols+j] == copy[(i+1)*cols+j] || copy[i*cols+j] == copy[i*cols+j-1])
			return 1;}
		else if( i == rows - 1 && j == 0){   //case: lowerleftmost
			if(copy[i*cols+j] == copy[(i-1)*cols+j] || copy[i*cols+j] == copy[i*cols+j+1])
			return 1;}
		else if( i == rows - 1 && j == cols - 1){   //case: lowerrightmost
			if(copy[i*cols+j] == copy[(i-1)*cols+j] || copy[i*cols+j] == copy[i*cols+j-1])
			return 1;}
		else if( i == 0 ){   //case: upper,but not the leftmost or rightmost
			if(copy[i*cols+j]==copy[(i+1)*cols+j]||copy[i*cols+j]==copy[i*cols+j+1]||copy[i*cols+j]==copy[i*cols+j-1])
			return 1;}
		else if( i == rows - 1 ){   //case: lower,but not the leftmost or rightmost
			if(copy[i*cols+j]==copy[(i-1)*cols+j]||copy[i*cols+j]==copy[i*cols+j+1]||copy[i*cols+j]==copy[i*cols+j-1])
			return 1;}
		else if( j == 0 ){   //case: leftmost,but not the top or bot
			if(copy[i*cols+j]==copy[(i+1)*cols+j]||copy[i*cols+j]==copy[(i-1)*cols+j]||copy[i*cols+j]==copy[i*cols+j+1])
			return 1;}
		else if( j == cols - 1 ){   //case: rightmost,but not the top or bot
			if(copy[i*cols+j]==copy[(i+1)*cols+j]||copy[i*cols+j]==copy[(i-1)*cols+j]||copy[i*cols+j]==copy[i*cols+j-1])
			return 1;}
		else{   //every other case
			if(copy[i*cols+j]==copy[(i+1)*cols+j]||copy[i*cols+j]==copy[(i-1)*cols+j]||copy[i*cols+j]==copy[i*cols+j-1] ||copy[i*cols+j]==copy[i*cols+j+1])
			return 1;}}}
	return 0;
}


/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{
	
	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;
	
    if (cell_ptr == NULL){ 	
        printf("Bad Cell Pointer.\n");
        exit(0);
    }
	
	
	//check for an empty cell
	int emptycheck = 0;
	int i;
	
	for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
		if ((*cell_ptr) == -1){
				emptycheck = 1;
				break;
		}		
        cell_ptr += 1;
	}
	if (emptycheck == 0){
		printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
		exit(0);
	}
	
    int ind,row,col;
	int num;
    do{
		ind = rand()%((cur_game->rows)*(cur_game->cols));
		col = ind%(cur_game->cols);
		row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
	num = rand()%20;
	if(num <= 1){
		*get_cell(cur_game, row, col) = 4; // 1/10th chance
	}
	else{
		*get_cell(cur_game, row, col) = 2;// 9/10th chance
	}
}

int print_game(game * cur_game) 
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;
	
	printf("\n\n\nscore:%d\n",cur_game->score); 
	
	
	printf("\u2554"); // topleft box char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // top box char
	printf("\u2557\n"); //top right char 
	
	
    for(i = 0; i < rows; i++){
		printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  "); 
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
					default:
						printf("  X  ");

                }

            }
            cell_ptr++;
        }
	printf("\u2551\n"); //print right wall and newline
    }
	
	printf("\u255A"); // print bottom left char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // bottom char
	printf("\u255D\n"); //bottom right char
	
    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{ 
	int rows,cols;
	char buf[200];
	char garbage[2];
    int move_success = 0;
	
    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
	case 'n':
		//get row and col input for new game
		dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
		while (NULL == fgets(buf,200,stdin)) {
			printf("\nProgram Terminated.\n");
			return 0;
		}
		
		if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
		rows < 0 || cols < 0){
			printf("Invalid dimensions.\n");
			goto dim_prompt;
		} 
		
		remake_game(&cur_game,rows,cols);
		
		move_success = 1;
		
    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }

	
	
	
    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game); 
		 print_game(cur_game);
    } 

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}
