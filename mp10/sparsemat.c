/*
*/
#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>
void delete_node(sp_tuples * mat_t,int row,int col);

void delete_node(sp_tuples * mat_t,int row,int col){
	int n,nz;
	n = mat_t->n;
	nz = mat_t->nz;
	int index = row * n + col;
	int compare;
	sp_tuples_node *nodes = mat_t->tuples_head;
	sp_tuples_node *nodes_prev = NULL;
	sp_tuples_node *nodes_next = nodes->next;
	for(int i = 0;i<nz;i++){
		compare = nodes->row * n +nodes->col;
		if(i ==0 && compare == index){
			mat_t->tuples_head = nodes->next;
			free(nodes);
			nodes = NULL;
			break;}
		else if(compare == index){
			nodes_prev->next = nodes_next;
			free(nodes);
			nodes = NULL;
			break;}
		nodes_prev = nodes;
		nodes = nodes->next;
		nodes_next = nodes->next;}
		return;
}




sp_tuples * load_tuples(char* input_file)
{
	FILE* f;
	f=fopen(input_file,"r");
	sp_tuples* tuples = malloc(sizeof(sp_tuples));
	int m,n,nz=0;
	tuples->nz = nz;
	int row,col,check,first_flag =0;
	double val;
	fscanf(f,"%d %d\n",&m,&n);
	tuples->m = m;
	tuples->n = n;
//////////////////////scan the first line and assign the pointer in the tuple struct	
	sp_tuples_node *nodes = NULL;
	nodes = malloc(sizeof(sp_tuples_node));
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
		check = fscanf(f,"%d %d %lf\n",&row,&col,&val);
		if(check == 0)
			break;
		if(val == 0)
			continue;
		set_tuples(tuples, row, col, val);}

/*backup, if sort cannot be done while scaning
	nodes->next = (*sp_tuples_node)malloc(sizeof(sp_tuples_node));
	nodes->next->row = row;
	nodes->next->col = col;
	nodes->next->value = val;
	nodes=nodes->next;
	tuples->nz++;}*/






    return NULL;
}



double gv_tuples(sp_tuples * mat_t,int row,int col)

{
	sp_tuples_node *nodes= NULL;
	nodes = mat_t->tuples_head;
	int nz = mat_t->nz;
	double val= 0.0;
	for(int i = 0;i<nz;i++){
		if(nodes->row == row && nodes->col == col){
			val = nodes->value;
			return val;}
		nodes = nodes->next;}
    return 0;
}



void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
	int n,nz;
	n = mat_t->n;
	nz = mat_t->nz;
	int index = row * n + col;
	int compare,first_com;
	sp_tuples_node *nodes = mat_t->tuples_head;
	sp_tuples_node *nodes_prev = nodes;
	sp_tuples_node *nodes_next = nodes->next;
	first_com = nodes->row * n +nodes->col;
	if(value != 0){
		for(int i = 0;i<=nz;i++){
			compare = nodes->row * n +nodes->col;
			if(compare==index){
				nodes->value = value;}
			else if(compare<index){
				sp_tuples_node* new_nodes = malloc(sizeof(sp_tuples_node));
				nodes_prev->next = new_nodes;
				new_nodes->row = row;
				new_nodes->col = col;
				new_nodes->value = value;
				new_nodes->next = nodes_next;
				mat_t->nz++;
				break;}
			else if(first_com>index){
				sp_tuples_node* new_nodes = malloc(sizeof(sp_tuples_node));
				mat_t->tuples_head = new_nodes;
				new_nodes->row = row;
				new_nodes->col = col;
				new_nodes->value = value;
				new_nodes->next = nodes;
				mat_t->nz++;
				break;}
			nodes_prev = nodes;
			nodes = nodes->next;}}
	else if(value == 0){
		delete_node(mat_t,row,col);}
    return;
}



void save_tuples(char * file_name, sp_tuples * mat_t)
{
	FILE *f;
	int nz = mat_t->nz;
	f=fopen(file_name,"w");
	fprintf(f,"%d %d\n",mat_t->m,mat_t->n);
	sp_tuples_node *nodes = mat_t->tuples_head;
	for(int i = 0;i<nz;i++){
		fprintf(f,"%d %d %f\n",nodes->row,nodes->col,nodes->value);
		nodes = nodes->next;}
	fclose(f);
	return;
}



sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){

	return matA;
}



/*sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){

    return retmat;
}*/


	
void destroy_tuples(sp_tuples * mat_t){
	sp_tuples_node *nodes;
	sp_tuples_node *next_nodes;
	nodes = mat_t->tuples_head;
	next_nodes= NULL;
	int nz = mat_t->nz;
	for(int i = 0;i<nz;i++){
		next_nodes = nodes->next;
		free(nodes);
		nodes = next_nodes;}
	free(mat_t);
	nodes = NULL;
	mat_t = NULL;
	next_nodes = NULL;
    return;
}  






