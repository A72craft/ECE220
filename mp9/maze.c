#include <stdio.h>
#include <stdlib.h>
#include "maze.h"


/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
	FILE *f;
	int i,j;
	int h,w;
	char buf[200];
    maze_t * maze = malloc(sizeof(maze_t));
	f = fopen(fileName,"r");
	sscanf(buf,"%d %d",&w,&h);
	maze->cells = (char**)malloc(h*sizeof(char*));
	for(i = 0;i<h;i++){
		maze->cells[i] = (char*)malloc(w*sizeof(char));}
	for(i = 0;i <h;i++){
		for(j = 0;j<w;j++){
			fscanf(f,"%c",&maze->cells[i][j]);
			if(maze->cells[i][j] == "S"){
				maze->startColumn = j;
                maze->startRow = i;}
			else if(maze->cells[i][j] == "E"){
				maze->endColumn = j;
                maze->endRow = i;}}}		
	maze->height = h;
	maze->width = w;
	fclose(f);
	return maze;
}
	

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    free(maze->cells);
	free(maze);
	maze = NULL;
	return;
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    int i,j;
	int width,height;
	int stcol,strow,endcol,endrow;
	width = maze->width;
	height = maze->height;
	stcol = maze->startColumn;
	strow = maze->startRow;
	endcol = maze->endColumn;
	endrow = maze->endRow;
	for(i = 0;i<height;i++){
		for(j = 0;j<width;j++){
			if(i == stcol && j ==strow){
				printf("S");
				continue;}
			if(i == endcol && j ==endrow){
				printf("E");
				continue;}
			if(maze->cells[i][j]=="~"){
				printf("~");
				continue;}
			if(maze->cells[i][j] =="%"){
				printf("%%");
				continue;}
			if(maze->cells[i][j] ==" "){
				printf(" ");
				continue;}}
		printf("\n");}
	return;
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row)
{
    if(col >=maze->width || col<0 || row >=maze->height || row<0)
		return 0;  //If (col, row) outside bounds of the maze return false
	if(maze->cells[row][col] !=" ")
		return 0;  //if (col, row) is not an empty cell return false
	if(col == maze->endColumn && row == maze->endRow)
		return 1;  //if (col, row) is the end of the maze return true
	maze->cells[row][col] = "*";
	if(solveMazeDFS(maze,col-1,row)==1)
		return 1;
	if(solveMazeDFS(maze,col+1,row)==1)
		return 1;
	if(solveMazeDFS(maze,col,row-1)==1)
		return 1;
	if(solveMazeDFS(maze,col,row+1)==1)
		return 1;
	maze->cells[row][col] = "~";
	return 0;}
