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
    maze_t * maze = malloc(sizeof(maze_t));
	f = fopen(fileName,"r");
	
	
	
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
	width = maze.width;
	height = maze.height;
	stcol = maze.startColumn;
	strow = maze.startRow;
	endcol = maze.endColumn;
	endrow = maze.endRow;
	for(i = 0;i<height;i++){
		for(j = 0;j<width;j++){
			if(i == stcol && j ==strow){
				printf("S");
				continue;}
			if(i == endcol && j ==endrow){
				printf("E");
				continue;}
			if(maze->[i][j] == 1){
				printf("%");
				continue;}
			if(maze->[i][j] == 0){
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
    // Your code here. Make sure to replace following line with your own code.
    return 0;
}
