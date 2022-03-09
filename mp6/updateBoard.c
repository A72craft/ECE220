/*
group partner: jinj2(me)
there are three functions in here. countliveneighbor,
updateboard and alive stable. Besides these three there
is also a copy_array which copys a array. The specifics of
these array are down below.
*/
void copy_array(const int array[],int copy[], int size);

/*
This function counts the alive neighbor around the
given cell,which is usually eight. If the cell is in a
edge  or a corner, the cell outside the given space will
be discarded. The amount of live neighbors will be returned.
*/
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
This function will update the board. It will first make a copy of 
the board, then update the original board with the data from the copied 
board. The updated board is returned.(But it is a void function)
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {
	int size = boardRowSize*boardColSize; //get the size to create the copy
	int copy[size];
	copy_array(board,copy,size);   //create the copy
	for ( int r = 0; r<boardRowSize; r++){
		for (int c = 0;c<boardColSize;c++){ //go through all the cells in the board
			int live = countLiveNeighbor(copy,boardRowSize,boardColSize,r,c);
			if (live ==0 || live ==1 || live ==4||live==5||live==6||live==7||live==8){
				board[r*boardColSize+c] = 0; //if the number of alive cells next to it is the 
				continue;}					//above number, then it must be dead
			else if(live ==3){ //if the number of alive cells next to it is 3,it must be alive
				board[r*boardColSize+c] = 1;
				continue;} //if the number of alive cells is 2,it is what it used to be 
}
}
}

/*
this function checks if the board is stable. If it is stable then it
will return 1. Else return 0.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize){
	for ( int r = 0; r<boardRowSize; r++){
		for (int c = 0;c<boardColSize;c++){ //go through all the cells
			int live = countLiveNeighbor(board,boardRowSize,boardColSize,r,c);
			if (live ==0 || live ==1 || live ==4||live==5||live==6||live==7||live==8){
				if (board[r*boardColSize+c] != 0) //if the cell is not the same(dead) before
					return 0;                     //and after return 0
				continue;}
			else if(live ==3){                    //if the cell is not the same(alive)before and after
				if(board[r*boardColSize+c] != 1)  //return 0
					return 0;
				continue;}}}	return 1;}
/*
this function creates a copy of the original function
*/
void copy_array(const int array[],int copy[], int size){
	for (int i = 0;i<size;i++){
		copy[i]=array[i];}
}


				
				
			

