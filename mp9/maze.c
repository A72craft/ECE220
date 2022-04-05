/*partner: jinj2(me)
*For this mp 4 functions were created: createMaze,destroyMaze,printMaze,and
*solveMazeDFS. They each creates the maze,destroys the maze,prints the maze,
*and solves the maze with recursion.
*/
#include <stdio.h>
#include <stdlib.h>
#include "maze.h"


/*
*This function creates a maze with a given file name and scans the file to
*fill the maze.
 */
maze_t * createMaze(char * fileName)
{
	FILE *f;
	int i,j;
	int h,w; 
	char buf;    
    maze_t * maze = malloc(sizeof(maze_t)); //allocate memory for the struct
	f = fopen(fileName,"r");
	fscanf(f,"%d %d\n",&w,&h);  //get the rows and columns
	maze->cells = (char**)malloc(h*sizeof(char*)); //allocate the rows
	for(i = 0;i<h;i++){
		maze->cells[i] = (char*)malloc(w*sizeof(char));} //allocate the columns
	for(i = 0;i<h;i++){
		for(j = 0;j<w;j++){
			fscanf(f,"%c",&buf); //get the char one by one
			if(buf == 'S'){
				maze->startColumn = j; //get the starting point 
                maze->startRow = i;
				maze->cells[i][j] = buf;}
			else if(buf == 'E'){
				maze->endColumn = j;
                maze->endRow = i; //get the ending point
				maze->cells[i][j] = buf;}
			else if(buf == '\n'){ //get the newline
				j--;
				continue;}
			else{
				maze->cells[i][j] = buf;}}} //fill in the maze
	maze->height = h;
	(*maze).width = w;
	fclose(f);
	return maze;
}
	

/*
 *this function destroys the maze by setting all memory free.
 */
void destroyMaze(maze_t * maze)
{
	int i;
	for(i = 0;i<maze->height;i++){
    	free(maze->cells[i]);}
	free(maze->cells); //frees the memory
	free(maze);
	maze = NULL;
	return;
}

/*
 * This function prints the maze.
 */
void printMaze(maze_t * maze)
{
    int i,j;
	int width,height;
	int stcol,strow,endcol,endrow;
	width = maze->width;
	height = maze->height;
	stcol = maze->startColumn;
	strow = maze->startRow;    //get the data from the struct
	endcol = maze->endColumn;
	endrow = maze->endRow;
	for(i = 0;i<height;i++){
		for(j = 0;j<width;j++){  //for the maze
			if(i == strow && j ==stcol){
				printf("S");     //prints what is in the maze
				continue;}
			if(i == endrow && j ==endcol){
				printf("E");
				continue;}
			if(maze->cells[i][j]=='~'){
				printf("~");
				continue;}
			if(maze->cells[i][j] =='%'){
				printf("%%");
				continue;}
			if(maze->cells[i][j] == '*'){
				printf("*");
				continue;}
			if(maze->cells[i][j] ==' '){
				printf(" ");
				continue;}}
		printf("\n");} //prints newline at a new line
	return;
}

/*
*This function tries to solve the maze by recursion.It will go down
*a path until it is stuck. Then it will go back to the point where
*there is another path.
 */ 
int solveMazeDFS(maze_t * maze, int col, int row){

    if(col >=maze->width || col<0 || row >=maze->height || row<0)
		return 0;  //If (col, row) outside bounds of the maze return false
	if(row == maze->endRow && col ==maze->endColumn){
		maze->cells[maze->endRow][maze->endColumn] = 'E';
		maze->cells[maze->startRow][maze->startColumn] = 'S';
		return 1;} //if (col, row) is the end of the maze return true
	if( maze->cells[row][col] != ' ' &&maze->cells[row][col] != 'S'&&maze->cells[row][col] != 'E')
		return 0;  //if (col, row) is not an empty cell return false
		maze->cells[row][col] = '*'; //set cell as marked and a solution path
	if(solveMazeDFS(maze,col,row-1)==1) //go up,down,left,and right
		return 1;
	if(solveMazeDFS(maze,col,row+1)==1)
		return 1;
	if(solveMazeDFS(maze,col-1,row)==1)
		return 1;
	if(solveMazeDFS(maze,col+1,row)==1)
		return 1;
	maze->cells[row][col] = '~'; //set cell as marked and not a solution path
	return 0;}
