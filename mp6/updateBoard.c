/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */
void copy_array(const int array[],int copy[], int size);


int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){
	int live = 0;                            //set living neighbors to 0
	for (int r=row-1;r<=row+1;r++){           //for the three rows
		if ( r>=0 && r<boardRowSize){         //if not a edge case
			for (int c = col-1;c<=col+1;c++){   //for the three columns
				if (c>=0 && c<boardColSize){    //if not a edge case
					if ( r==row && c ==col){     //if not the tested one
						 continue;}
						if( board[r*boardColSize+c]==1)    //if alive
							live = live + 1;}}}}
	return live;

}
/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {
	int size = boardRowSize*boardColSize;
	int copy[size];
	copy_array(board,copy,size);
	for ( int r = 0; r<boardRowSize; r++){
		for (int c = 0;c<boardColSize;c++){
			int live = countLiveNeighbor(copy,boardRowSize,boardColSize,r,c);
			if (live ==0 || live ==1 || live ==4||live==5||live==6||live==7||live==8){
				board[r*boardColSize+c] = 0;
				continue;}
			else if(live ==3){
				board[r*boardColSize+c] = 1;
				continue;}
}
}
}

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize){
	for ( int r = 0; r<boardRowSize; r++){
		for (int c = 0;c<boardColSize;c++){
			int live = countLiveNeighbor(board,boardRowSize,boardColSize,r,c);
			if (live ==0 || live ==1 || live ==4||live==5||live==6||live==7||live==8){
				if (board[r*boardColSize+c] != 0)
					return 0;
				continue;}
			else if(live ==3){
				if(board[r*boardColSize+c] != 1)
					return 0;
				continue;}}}	return 1;}

void copy_array(const int array[],int copy[], int size){
	for (int i = 0;i<size;i++){
		copy[i]=array[i];}
}


				
				
			

