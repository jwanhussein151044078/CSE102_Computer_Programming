#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 7

typedef struct face {
	int **face1;
	int **face2;
	int **face3;
	int **face4;
	int **face5;
	int **face6;
}FACE;

typedef struct line {
	char command[NAME_LEN];
	int face_num;
	char row_column[NAME_LEN];
	int row_column_number;
	char direction[NAME_LEN];
}LINE;

typedef struct commands {
	LINE *data;
	int size;
}COMMANDS;

FACE initial_faces(int n);
void read_file(char *filename, COMMANDS *commands , int *n );
FACE solve(COMMANDS commands, int *cube_size, int *shrink_size);
void shrink(FACE face,int size);
void rotate(FACE face,int size,int shrink,int face_number , char row_column[NAME_LEN] , int number ,char direction[NAME_LEN]);
void rot_case_1(int **array1 , int **array2 ,int **array3 ,int **array4 ,int size , int number,int shrink);
void rot_case_2(int **array1 , int **array2 ,int **array3 ,int **array4 ,int size , int number,int shrink);
void rot_case_3(int **array1 , int **array2 ,int **array3 ,int **array4 ,int size , int number,int shrink);
void flip_vertical(int **array , int size , int shrink);
void flip_horizontal(int **array , int size , int shrink);
void print_cube(char *filename,FACE face , int n, int z);
void free_cube(FACE face , int size);

void main(void){
	int cube_size ,shrink_size ;
	COMMANDS commands ;
	FACE face =	solve(commands,&cube_size,&shrink_size);
	print_cube("result.txt",face ,cube_size, shrink_size);
	free_cube(face,cube_size);
}

FACE initial_faces(int n){

	FACE face ;
	int i =0,
		j =0;

	face.face1 = malloc(n*sizeof(int *));
	face.face2 = malloc(n*sizeof(int *));
	face.face3 = malloc(n*sizeof(int *));
	face.face4 = malloc(n*sizeof(int *));
	face.face5 = malloc(n*sizeof(int *));
	face.face6 = malloc(n*sizeof(int *));
	for (i=0 ;i<n;i++){
		face.face1[i] =malloc(n*sizeof(int)); 
		face.face2[i] =malloc(n*sizeof(int));
		face.face3[i] =malloc(n*sizeof(int));
		face.face4[i] =malloc(n*sizeof(int));
		face.face5[i] =malloc(n*sizeof(int));
		face.face6[i] =malloc(n*sizeof(int));
		for(j=0;j<n;j++){
			face.face1[i][j] = 0;
			face.face2[i][j] = 1;
			face.face3[i][j] = 2;
			face.face4[i][j] = 3;
			face.face5[i][j] = 4;
			face.face6[i][j] = 5;
		}
	}

	return face;	 
}

void read_file(char *filename, COMMANDS *commands   ,int *n){

	int i = 0,shrink = 0;

	FILE *file = fopen(filename , "r");

	fscanf(file,"%d",n);
	commands->size = 0 ;
	commands->data = malloc(sizeof(LINE));
	while(!feof(file)){
		
		if (fscanf(file,"%s",commands->data[commands->size].command)){	

			if(strcmp(commands->data[commands->size].command,"rotate") == 0){
				fscanf(file,"%d %s %d %s",&commands->data[commands->size].face_num,
										  commands->data[commands->size].row_column,
										  &commands->data[commands->size].row_column_number,
										  commands->data[commands->size].direction);

			}
			commands->data = realloc(commands->data,(commands->size + 2 )*sizeof(LINE));
			commands->size++;

		}
	}
	commands->size--;	
	fclose(file);
	for(i=0;i<commands->size;i++){
		if(strcmp(commands->data[i].command,"rotate") == 0){
			commands->data[i].row_column_number += shrink ;
		}
		if(strcmp(commands->data[i].command,"shrink") == 0){
			shrink++;
		}
	}
}

FACE solve(COMMANDS commands , int *cube_size , int *shrink_size){


	int n,size,shrink=0;
	read_file("commands.txt",&commands,&n );

	FACE face = initial_faces(n) ;
	size = n ;
	
	for(int i = 0 ; i < commands.size ;i++){

		if (strcmp(commands.data[i].command,"rotate") == 0){
			rotate(face,size,shrink,
				   commands.data[i].face_num,
				   commands.data[i].row_column,
				   commands.data[i].row_column_number,
				   commands.data[i].direction);
		}

		else if (strcmp(commands.data[i].command,"shrink") == 0){
			
			shrink++;			
		}
	}
	*shrink_size = shrink;
	*cube_size = n ;
	return face ;
}



void rotate(FACE face,int size,int shrink,int face_number , char row_column[NAME_LEN] , int number ,char direction[NAME_LEN]){

	switch (face_number) {
		case 0 :
				if (strcmp(row_column,"row") == 0){
					if (strcmp(direction,"right") == 0){
						rot_case_1( face.face1 , face.face2 , face.face3 , face.face4 ,size,number,shrink);
					}
					if (strcmp(direction,"left") == 0){
						rot_case_1( face.face4 , face.face3 , face.face2 , face.face1 ,size,number,shrink);
					}
				}
				else if (strcmp(row_column,"column") == 0){
					flip_vertical(face.face3,size ,shrink);
					flip_horizontal(face.face3,size ,shrink);
					if (strcmp(direction,"up") == 0){
						rot_case_2( face.face1 , face.face5 , face.face3 , face.face6 ,size,number,shrink);
					}
					if (strcmp(direction,"down") == 0){
						rot_case_2( face.face6 , face.face3 , face.face5 , face.face1 ,size,number,shrink);
					}
					flip_vertical(face.face3,size ,shrink);
					flip_horizontal(face.face3,size ,shrink);
				}
			break;
		case 1 :
				if (strcmp(row_column,"row") == 0){
					if (strcmp(direction,"right") == 0){
						rot_case_1( face.face1 , face.face2 , face.face3 , face.face4 ,size,number,shrink);
					}
					if (strcmp(direction,"left") == 0){
						rot_case_1( face.face4 , face.face3 , face.face2 , face.face1 ,size,number,shrink);
					}
				}
				else if (strcmp(row_column,"column") == 0){
					flip_vertical(face.face4,size ,shrink);
					flip_vertical(face.face6,size ,shrink);
					flip_horizontal(face.face5,size ,shrink);
					if (strcmp(direction,"up") == 0){
						rot_case_3( face.face2 , face.face5 , face.face4 , face.face6 ,size,number,shrink);
					}
					if (strcmp(direction,"down") == 0){
						rot_case_3( face.face2 , face.face6 , face.face4 , face.face5 ,size,number,shrink);
					}
					flip_vertical(face.face4,size ,shrink);
					flip_horizontal(face.face5,size ,shrink);
					flip_vertical(face.face6,size ,shrink);
				}

			break;
		case 2 :
				if (strcmp(row_column,"row") == 0){
					if (strcmp(direction,"right") == 0){
						rot_case_1( face.face1 , face.face2 , face.face3 , face.face4 ,size,number,shrink);
					}
					if (strcmp(direction,"left") == 0){
						rot_case_1( face.face4 , face.face3 , face.face2 , face.face1 ,size,number,shrink);
					}
				}
				else if (strcmp(row_column,"column") == 0){
					flip_vertical(face.face3,size ,shrink);
					flip_horizontal(face.face3,size ,shrink);
					if (strcmp(direction,"up") == 0){
						rot_case_2( face.face6 , face.face3 , face.face5 , face.face1 ,size,size-number-1,shrink);
					}
					if (strcmp(direction,"down") == 0){
						rot_case_2( face.face1 , face.face5 , face.face3 , face.face6 ,size,size-number-1,shrink);
					}
					flip_vertical(face.face3,size ,shrink);
					flip_horizontal(face.face3,size ,shrink);
				} 
				
			break;
		case 3 :
				if (strcmp(row_column,"row") == 0){
					if (strcmp(direction,"right") == 0){
						rot_case_1( face.face1 , face.face2 , face.face3 , face.face4 ,size,number,shrink);
					}
					if (strcmp(direction,"left") == 0){
						rot_case_1( face.face4 , face.face3 , face.face2 , face.face1 ,size,number,shrink);
					}
				}
				else if (strcmp(row_column,"column") == 0){
					flip_vertical(face.face4,size ,shrink);
					flip_horizontal(face.face5,size ,shrink);
					flip_vertical(face.face6,size ,shrink);
					if (strcmp(direction,"up") == 0){
						rot_case_3( face.face2 , face.face6 , face.face4 , face.face5 ,size,size-1-number,shrink);
					}
					if (strcmp(direction,"down") == 0){
						rot_case_3( face.face2 , face.face5 , face.face4 , face.face6 ,size,size-1-number,shrink);
					}
					flip_vertical(face.face4,size ,shrink);
					flip_horizontal(face.face5,size ,shrink);
					flip_vertical(face.face6,size ,shrink);
				}
			
			break;
		case 4 : 
				if (strcmp(row_column,"row") == 0){
					flip_vertical(face.face4,size ,shrink);
					flip_horizontal(face.face5,size ,shrink);
					flip_vertical(face.face6,size ,shrink);
					if (strcmp(direction,"right") == 0){
						rot_case_3( face.face2 , face.face6 , face.face4 , face.face5 ,size,size-1-number,shrink);
					}
					if (strcmp(direction,"left") == 0){
						rot_case_3( face.face2 , face.face5 , face.face4 , face.face6 ,size,size-1-number,shrink);
					}
					flip_vertical(face.face4,size ,shrink);
					flip_horizontal(face.face5,size ,shrink);
					flip_vertical(face.face6,size ,shrink);
				}
				else if (strcmp(row_column,"column") == 0){
					flip_vertical(face.face3,size ,shrink);
					flip_horizontal(face.face3,size ,shrink);
					if (strcmp(direction,"up") == 0){
						rot_case_2( face.face1 , face.face5 , face.face3 , face.face6 ,size,number,shrink);
					}
					if (strcmp(direction,"down") == 0){
						rot_case_2( face.face6 , face.face3 , face.face5 , face.face1 ,size,number,shrink);
					}
					flip_vertical(face.face3,size ,shrink);
					flip_horizontal(face.face3,size ,shrink);
				}
			break;
			
		case 5 :
				if (strcmp(row_column,"row") == 0){
					flip_vertical(face.face4,size ,shrink);
					flip_horizontal(face.face5,size ,shrink);
					flip_vertical(face.face5,size ,shrink);
					if (strcmp(direction,"right") == 0){
						rot_case_3( face.face2 , face.face5 , face.face4 , face.face6 ,size,number,shrink);
					}
					if (strcmp(direction,"left") == 0){
						rot_case_3( face.face2 , face.face6 , face.face4 , face.face5 ,size,number,shrink);
					}
					flip_vertical(face.face4,size ,shrink);
					flip_vertical(face.face5,size ,shrink);
					flip_horizontal(face.face5,size ,shrink);
				}
				else if (strcmp(row_column,"column") == 0){
					flip_vertical(face.face3,size ,shrink);
					flip_horizontal(face.face3,size ,shrink);
					if (strcmp(direction,"up") == 0){
						rot_case_2( face.face1 , face.face5 , face.face3 , face.face6 ,size,number,shrink);
					}
					if (strcmp(direction,"down") == 0){
						rot_case_2( face.face6 , face.face3 , face.face5 , face.face1 ,size,number,shrink);
					}
					flip_vertical(face.face3,size ,shrink);
					flip_horizontal(face.face3,size ,shrink);
				}
			
			break;
	}

}

void rot_case_1(int **array1 , int **array2 ,int **array3 ,int **array4 ,int size,int number,int shrink){

	int temp[size];
	int i  ;

	for (i=0;i<size;i++){
		temp[i] = array1[number][i];
		array1[number][i] = array4[number][i];
		array4[number][i] = array3[number][i];
		array3[number][i] = array2[number][i];
		array2[number][i] = temp[i];
	}
}

void rot_case_2(int **array1 , int **array2 ,int **array3 ,int **array4 ,int size,int number,int shrink){

	int temp[size];
	int i ;

	for (i=0;i<size;i++){
		temp[i] = array1[i][number];
		array1[i][number] = array4[i][number];
		array4[i][number] = array3[i][number];
		array3[i][number] = array2[i][number];
		array2[i][number] = temp[i];
	}
}

void rot_case_3(int **array1 , int **array2 ,int **array3 ,int **array4 ,int size,int number,int shrink){

	int temp[size];
	int i ;

	for(i = 0; i < size ; i++){
		temp[i] = array1[i][number];
		array1[i][number] = array4[number][i];
		array4[number][i] = array3[i][number];
		array3[i][number] = array2[number][i];
		array2[number][i] = temp[i];
	}
}

void flip_vertical(int **array , int size , int shrink){

	int i =0 , j=0 ,temp , q;
	for (i=shrink; i < size ;i++){

		for(j=shrink,q=size-1 ; j <(size/2) ; j++,q--){
			temp = array[i][j];
			array[i][j] = array[i][q];
			array[i][q] = temp ;
		}
	}
}

void flip_horizontal(int **array , int size , int shrink){

	int i =0 , j=0, temp , q ;

	for (i = shrink ,q = size-1; i < (size/2) ; i++,q-- ){
		for(j = shrink ; j < size ; j++){
			temp = array[i][j];
			array[i][j] = array[q][j];
			array[q][j] = temp ;
		}
	}
}

void print_cube(char *filename,FACE face , int n, int z){

	int i , j ;

	FILE * file = fopen(filename,"w");
	for (i=z;i<n;i++){
		for (j=z ; j < n; j++)
		{
			fprintf(file,"%d ",face.face1[i][j] );
		}
		fprintf(file,"\n");
	}
	fprintf(file,"\n");
	for (i=z;i<n;i++){
		for ( j=z ; j < n; j++)
		{
			fprintf(file,"%d ",face.face2[i][j] );
		}
		fprintf(file,"\n");
	}
	fprintf(file,"\n");
	for (i=z;i<n;i++){
		for ( j=z ; j < n; j++)
		{
			fprintf(file,"%d ",face.face3[i][j] );
		}
		fprintf(file,"\n");
	}
	fprintf(file,"\n");
	for (i=z;i<n;i++){
		for ( j=z ; j < n; j++)
		{
			fprintf(file,"%d ",face.face4[i][j] );
		}
		fprintf(file,"\n");
	}
	fprintf(file,"\n");
	for (i=z;i<n;i++){
		for ( j =z; j < n; j++)
		{
			fprintf(file,"%d ",face.face5[i][j] );
		}
		fprintf(file,"\n");
	}
	fprintf(file,"\n");
	for (i=z;i<n;i++){
		for ( j=z; j < n; j++)
		{
			fprintf(file,"%d ",face.face6[i][j] );
		}
		fprintf(file,"\n");
	}
	fclose(file);
}

void free_cube(FACE face ,int size){

	int i =0 ;

	for (int i = 0; i < size; ++i){

		free(face.face1[i]);
		free(face.face2[i]);
		free(face.face3[i]);
		free(face.face4[i]);
		free(face.face5[i]);
		free(face.face6[i]);
	}
	free(face.face1);
	free(face.face2);
	free(face.face3);
	free(face.face4);
	free(face.face5);
	free(face.face6);
}

