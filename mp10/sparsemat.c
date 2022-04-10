/*partner: jinj2(me)
*Besides the provided function,delete_node and add_tuples_value
*are also implemented. Other provided functions are to load a 
*function from a given file, give the value in the sparse matrix
*with the row and col, set a value in a tuple with given values and
*row and cols, save the matrix to a file, adding two matrixes,and
*deleting the matrix.
*/
#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>
void delete_node(sp_tuples * mat_t,int row,int col);
void add_tuples_value(sp_tuples * mat_t, int row, int col, double value);

/*This function will delete the item at the given
*rows and cols. If the item does not exist, do nothing.*/
void delete_node(sp_tuples * mat_t,int row,int col){
	int n,nz;
	n = mat_t->n;
	nz = mat_t->nz;  //initialize
	int index = row * n + col;
	int compare;
	sp_tuples_node *nodes = mat_t->tuples_head; //set the linked list
	sp_tuples_node *nodes_prev = NULL;
	sp_tuples_node *nodes_next = nodes->next; 
	for(int i = 0;i<nz;i++){
		compare = nodes->row * n + nodes->col; //this is the current index
		if(i ==0 && compare == index){
			mat_t->tuples_head = nodes->next; //if is the first & index is the same
			free(nodes);
			nodes = NULL;  //delete the node
			mat_t->nz--;
			break;}
		else if(compare == index){  //if it is the same index
			nodes_prev->next = nodes_next; 
			free(nodes);
			nodes = NULL;  //delete the node
			mat_t->nz--;
			break;}
		nodes_prev = nodes;
		nodes = nodes->next;
		if(i!= nz-1) //if not the last
		nodes_next = nodes->next;} //point the prev item to the next
		return;
}



/*This function will load a matrix from a given file*/
sp_tuples * load_tuples(char* input_file)
{
	FILE* f;
	f=fopen(input_file,"r");
	sp_tuples* tuples = malloc(sizeof(sp_tuples));//allocate the memory for the first
	int m,n,nz=0;
	tuples->nz = nz;
	int row,col,check,first_flag =0;
	double val;
	fscanf(f,"%d %d\n",&m,&n); //get the parameters
	tuples->m = m;
	tuples->n = n;
//////////////////////scan the first line and assign the pointer in the tuple struct	
	sp_tuples_node *nodes = NULL;
	nodes = malloc(sizeof(sp_tuples_node));  //get the first line 
	while(first_flag == 0){
		fscanf(f,"%d %d %lf\n",&row,&col,&val);
		if(val == 0)
			continue;
		nodes->row = row;
		nodes->col = col;
		nodes->value = val;
		tuples->tuples_head = nodes;
		tuples->nz++;
		first_flag = 1;}
/////////////////////scan all the other lines
	while(1){
		check = fscanf(f,"%d %d %lf\n",&row,&col,&val); //get all the other lines
		if(check == EOF)
			break;
		set_tuples(tuples, row, col, val);}
	fclose(f);
    return tuples;
}


/*this function takes the row and col and returns the 
*value with the row and column*/
double gv_tuples(sp_tuples * mat_t,int row,int col)

{
	sp_tuples_node *nodes= NULL;
	nodes = mat_t->tuples_head;
	int nz = mat_t->nz;
	double val= 0.0;
	for(int i = 0;i<nz;i++){
		if(nodes->row == row && nodes->col == col){ //if row and col matches
			val = nodes->value;
			return val;}
		nodes = nodes->next;}
    return 0;
}


/*This function takes all the value and try to add them into the 
*matrix by order. If value is zero delete the node,else add the node in*/
void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
	int n,nz;
	n = mat_t->n;
	nz = mat_t->nz;
	int index = row * n + col;
	int prev_index = 0;
	int next_index;
	sp_tuples_node *nodes = mat_t->tuples_head; //initialize
	sp_tuples_node *prev_nodes = NULL;
	if(value != 0){ //if value is not zero
		for(int i = 0;i<=nz;i++){
			if(i !=nz)
			next_index = nodes->row * n + nodes->col;
			if(index==next_index){
				nodes->value = value; //if item already exist,overwrite
				break;}
			else if(i==0 && index<next_index){//case:first
				sp_tuples_node *new_nodes = NULL;
		        new_nodes = malloc(sizeof(sp_tuples_node));
				new_nodes->row = row;
				new_nodes->col = col;
				new_nodes->value = value;
				new_nodes->next = nodes;
				mat_t->tuples_head = new_nodes;
				mat_t->nz++;
				break;}
			else if(index>prev_index && index<next_index){//case: middle
				sp_tuples_node *new_nodes = NULL;
		        new_nodes = malloc(sizeof(sp_tuples_node));
				new_nodes->row = row;
				new_nodes->col = col;
				new_nodes->value = value;
				new_nodes->next = nodes;
				prev_nodes->next = new_nodes;
				mat_t->nz++;
				break;}
			else if(i == nz){ //case:last
				sp_tuples_node *new_nodes = NULL;
		        new_nodes = malloc(sizeof(sp_tuples_node));
				new_nodes->row = row;
				new_nodes->col = col;
				new_nodes->value = value;
				new_nodes->next = NULL;
				prev_nodes->next = new_nodes;
				mat_t->nz++;
				break;}
			prev_index = next_index;
			prev_nodes = nodes;
			if(i !=nz-1)
			nodes = nodes->next;}}
	else if(value == 0){
		delete_node(mat_t,row,col);} //delete if value is zero
    return;
}


/*saves the tuple to a file*/
void save_tuples(char * file_name, sp_tuples * mat_t)
{
	FILE *f;
	int nz = mat_t->nz;
	f=fopen(file_name,"w");
	fprintf(f,"%d %d\n",mat_t->m,mat_t->n); //print the parameters
	sp_tuples_node *nodes = mat_t->tuples_head;
	for(int i = 0;i<nz;i++){
		fprintf(f,"%d %d %f\n",nodes->row,nodes->col,nodes->value); //print the rows
		nodes = nodes->next;}
	fclose(f);
	return;
}


/*this function adds two matrixes together*/
sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){
	sp_tuples * matC = malloc(sizeof(sp_tuples));
	sp_tuples_node* nodeA = matA->tuples_head;
	sp_tuples_node* nodeB = matB->tuples_head; //initialize
	if(matA->m !=matB->m ||matA->n !=matB->n)
		return NULL; //if parameters does not match up
	matC->m = matA->m;
	matC->n = matA->n;
	matC->nz = 0;
	for(int i = 0;i< matA->nz;i++){
		int row,col;
		double value;
		row = nodeA->row;
		col = nodeA->col;
		value = nodeA->value;
		if(i==0){ //make matC = matA just like the load function
		sp_tuples_node*	nodeC = malloc(sizeof(sp_tuples_node));
		nodeC->row = row;
		nodeC->col = col;
		nodeC->value = value;
		matC->tuples_head = nodeC;
		matC->nz=1;}
		else{
			set_tuples(matC,row,col,value);}
		if(i!=matA->nz-1)
			nodeA = nodeA->next;}
	matC->nz = matA->nz;
	for(int i = 0;i< matB->nz;i++){ //using add_tuples_value,add matB to matC(which is currently matA)
		int row,col;
		double value;
		row = nodeB->row;
		col = nodeB->col;
		value = nodeB->value;
		add_tuples_value(matC,row,col,value);
		if(i!= matB->nz -1 )
		nodeB = nodeB->next;}
		
		
	return matC;
}



/*sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){

    return retmat;
}*/


/*This function frees all the memory space that are passed in*/
void destroy_tuples(sp_tuples * mat_t){
	sp_tuples_node *nodes;
	sp_tuples_node *next_nodes;
	nodes = mat_t->tuples_head;
	next_nodes= NULL;
	int nz = mat_t->nz;
	for(int i = 0;i<nz;i++){ //free all the  nodes
		next_nodes = nodes->next;
		free(nodes);
		nodes = next_nodes;}
	free(mat_t); //free the first
	nodes = NULL;
	mat_t = NULL; //pointer points to NULL
	next_nodes = NULL;
    return;
}  
/*This is set_tuples,but instead of overwriting the value, it adds them together*/
void add_tuples_value(sp_tuples * mat_t, int row, int col, double value)
{
	int n,nz;
	n = mat_t->n;
	nz = mat_t->nz;
	int index = row * n + col;
	int prev_index = 0;
	int next_index;
	sp_tuples_node *nodes = mat_t->tuples_head;//initialize
	sp_tuples_node *prev_nodes = NULL;
	if(value != 0){
		for(int i = 0;i<=nz;i++){
			if(i !=nz)
			next_index = nodes->row * n + nodes->col; //adds them together
			if(index==next_index){
				nodes->value = nodes->value+value;
				break;}
			else if(i==0 && index<next_index){//case: first
				sp_tuples_node *new_nodes = NULL;
				new_nodes = malloc(sizeof(sp_tuples_node));
				new_nodes->row = row;
				new_nodes->col = col;
				new_nodes->value = value;
				new_nodes->next = nodes;
				mat_t->tuples_head = new_nodes;
				mat_t->nz++;
				break;}
			else if(index>prev_index && index<next_index){//case: middle
				sp_tuples_node *new_nodes = NULL;
		        new_nodes = malloc(sizeof(sp_tuples_node));
				new_nodes->row = row;
				new_nodes->col = col;
				new_nodes->value = value;
				new_nodes->next = nodes;
				prev_nodes->next = new_nodes;
				mat_t->nz++;
				break;}
			else if(i == nz){//case: last
				sp_tuples_node *new_nodes = NULL;
		        new_nodes = malloc(sizeof(sp_tuples_node));
				new_nodes->row = row;
				new_nodes->col = col;
				new_nodes->value = value;
				new_nodes->next = NULL;
				prev_nodes->next = new_nodes;
				mat_t->nz++;
				break;}
			prev_index = next_index;
			prev_nodes = nodes;
			if(i !=nz-1)
			nodes = nodes->next;}}
	else if(value == 0){//do nothing if value is zero
		return;}
    return;
}




