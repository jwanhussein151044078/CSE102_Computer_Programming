#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NAMELEN 25
#define op_len 9

typedef struct input_c {
    int state;
    char name[NAMELEN];
    struct input_c *next;
} INPUT;

typedef struct output_c {
    int state;
    char name[NAMELEN];
} OUTPUT;

typedef struct line_c {
    char keyword[op_len];
    int size_of_input;
    INPUT *input ;
    OUTPUT *output ;
} LINE;

typedef struct logic_c {
    LINE *data;
    int size;
} LOGIC;

typedef struct digit_i {
    int state;
    struct digit_i *next;
} DIGIT;

typedef struct line_i {
    int size_of_input;
    DIGIT *digit ;
} LINE_I;

typedef struct logic_i {
    LINE_I *data;
    int size;
} DIGIT_I;

void read_circuit(char *filename , LOGIC *logic );
int compare(char str1[NAMELEN]);
void read_input(char *filename , DIGIT_I *digit);
int checking(LOGIC logic ,DIGIT_I digit);
void set_input_to_circuit(LOGIC logic ,DIGIT_I digit);
void output_for_line(LOGIC logic,int *former_out);
void AND_gate(LOGIC logic , int i );
void OR_gate(LOGIC logic , int i );
void NOT_gate(LOGIC logic , int i );
void FLIPFLOP_gate(LOGIC logic , int i, int out);
int find_output_line(LOGIC logic);
void freeing_struct_cir(LOGIC logic);
void freeing_struct_in(DIGIT_I digit);

void main(void){
	
	LOGIC logic ;
	DIGIT_I digit ;
	
	read_circuit("circuit.txt",&logic );
	read_input("input.txt",&digit);
	set_input_to_circuit(logic ,digit);
	freeing_struct_cir(logic);
	freeing_struct_in(digit);
}

void read_circuit( char *filename, LOGIC *logic ){

	char temp[NAMELEN];
	int first_in = 1 ,
		first_out = 1 ;
	INPUT *cur = NULL ;

	FILE *file = fopen(filename,"r");
		if (file == NULL){
			printf("can not open the file \n");
			return ;
		}
		logic->size = 0 ;
		logic->data = malloc(sizeof(LINE));
		logic->data[logic->size].size_of_input = 0;

		while(!feof(file)){
			fscanf(file,"%s",temp);

			if (compare(temp)){
				strcpy(logic->data[logic->size++].keyword,temp);
				logic->data = realloc(logic->data,(logic->size+1)*sizeof(LINE));
				if (strcmp(temp,"INPUT") == 0){
					first_in = 1 ;
					first_out = 0 ; 
				}
				else{
					first_in = 0 ;
					first_out = 1 ;	
				}
				logic->data[logic->size-1].size_of_input = 0;
			}
			else if (first_in){
				
				logic->data[logic->size-1].input = malloc(sizeof(INPUT));
				cur = logic->data[logic->size-1].input ;
				strcpy(cur->name,temp);
				cur->state = 0 ;
				cur->next = malloc(sizeof(INPUT));
				cur = cur->next;
				first_in = 0 ;
				logic->data[logic->size-1].size_of_input++;

			}
			else if (first_out){

				logic->data[logic->size-1].output = malloc(sizeof(OUTPUT));
				strcpy(logic->data[logic->size-1].output->name,temp);
				logic->data[logic->size-1].output->state = 0 ;
				first_out = 0 ;
				first_in = 1;

			}
			else{
				logic->data[logic->size-1].size_of_input++;
				
				strcpy(cur->name,temp);
				cur->state = 0 ;
				cur->next = malloc(sizeof(INPUT));
				cur = cur->next ;
			}
		}
	fclose(file);	
}



void read_input(char *filename , DIGIT_I *digit){

	char ch ;
	int i = 0 ,dig = 0,j=0;
	DIGIT *cur = NULL ;

	FILE * file = fopen(filename,"r");

		if (file == NULL){
			printf("cant open the file \n");
			return ;
		}
		digit->data = malloc(sizeof(LINE_I));
		digit->data[i].digit = malloc(sizeof(DIGIT));
		digit->size = 0;
		digit->data[digit->size].size_of_input = 0 ;
		cur = digit->data[digit->size].digit ;
		while(!feof(file)){
			ch = fgetc(file);

			if (((ch -'0') == 1 || (ch -'0') == 0) && ch != EOF){

				cur->state = ch -'0';
				digit->data[digit->size].size_of_input++;
				cur->next =  malloc(sizeof(DIGIT));
				cur = cur->next ;
			}
				
			
			else if (ch == '\n'){
				digit->size++;
				digit->data = realloc(digit->data,(digit->size+1)*sizeof(LINE_I));
				digit->data[digit->size].digit = malloc(sizeof(DIGIT));
				cur = digit->data[digit->size].digit ;
				digit->data[digit->size].size_of_input = 0 ;
			}
			else if (ch != ' ' && ch != EOF){
				printf("you have wrong digit in your input file \n");
				printf("check line (%d)\n",digit->size+1 );
				exit(1);
			}
		}
		
	
	fclose(file);


}



int compare(char str[NAMELEN]){

	if (strcmp(str,"INPUT") !=0 && strcmp(str,"AND") !=0 &&
		strcmp(str,"OR") !=0 && strcmp(str,"NOT") !=0 &&
		strcmp(str,"FLIPFLOP") !=0 ){

		return 0 ;
	}
	else return 1 ;

}

void set_input_to_circuit(LOGIC logic ,DIGIT_I digit){

	int i=0 , j=0 , q=0 , w=0 , former_out=0 ;
	INPUT *cur_c = NULL, *cur= NULL;
	DIGIT *cur_i = NULL;

	if (checking(logic ,digit)){
		
		for ( i=0 ; i < digit.size ; i++ ){
			if (digit.data[i].size_of_input != 0){
				cur_i = digit.data[i].digit;
				for ( j=0 ; j<logic.size ; j++ ){

					cur_c = logic.data[j].input;
					if(strcmp(logic.data[j].keyword,"INPUT") == 0){
						q=0;
						while(q < logic.data[j].size_of_input){

							cur_c->state = cur_i->state ;
							cur_i = cur_i->next;
							cur_c = cur_c->next;
							q++;	
						}

					}
				}
				output_for_line(logic,&former_out);
				printf("%d\n",find_output_line(logic) );
			}
		}
	}
	
}

int checking(LOGIC logic ,DIGIT_I digit){

	int row , colum , in_p_num =0 ,i =0 , j =0 , counter =0 ;
	INPUT *cur = NULL ;
	char **temp;
	
	for(i=0;i<logic.size;i++){
		if (strcmp(logic.data[i].keyword,"INPUT") == 0){
			in_p_num += logic.data[i].size_of_input;

		}
		else if (strcmp(logic.data[i].keyword,"AND") == 0 ||
				 strcmp(logic.data[i].keyword,"OR") == 0){

			if(logic.data[i].size_of_input != 2){
				printf("%d\n", logic.data[i].size_of_input);
				printf("%s\n",logic.data[i].input->next->name );
				printf("check input in line (%d) of circuit file \n",i+1);
				exit(1);
			}
		}
		else if (strcmp(logic.data[i].keyword,"NOT") == 0 ||
				 strcmp(logic.data[i].keyword,"FLIPFLOP") == 0){

			if(logic.data[i].size_of_input != 1){
				printf("check input in line (%d) of circuit file \n",i+1);
				exit(1);
			}
		}
	}

	temp = malloc((in_p_num)*sizeof(char*));
	for(i=0;i<in_p_num;i++){
		temp[i] = malloc((NAMELEN)*sizeof(char));
	}

	for (i = 0; i < logic.size; ++i)
	{
		if (strcmp(logic.data[i].keyword,"INPUT") == 0){
			if (logic.data[i].input != NULL){
				cur = logic.data[i].input; 
				while (j < logic.data[i].size_of_input){
					strcpy(temp[counter++],cur->name);
					cur = cur->next;
					j++;
				}
				j=0;
			}		 
		}
	}
	
	for (i = 0; i < in_p_num; ++i)
	{
		for(j=i+1;j<in_p_num;j++){
			if (strcmp(temp[i],temp[j])==0){
				printf("redeclaration of ( %s )\n",temp[i]);
				exit (1);
			}
		}
		free(temp[i]);
	}
	free(temp);

	for (i=0 ; i < digit.size ; i++){
		if (digit.data[i].size_of_input != 0){
			if (digit.data[i].size_of_input != in_p_num){
				printf("Check the number of variables defined in line (%d) and try again\n",i+1 );
				exit(1);
			}
		}
	}
	return 1 ; 
}

void output_for_line(LOGIC logic,int *former_out){

	int i = 0 , digit = 0 ,q=0,w=0,out;
	INPUT *cur;

	for ( i=0 ; i < logic.size ; i++ ){
		if (strcmp(logic.data[i].keyword,"AND") == 0){
			AND_gate(logic ,i );
		}

		else if (strcmp(logic.data[i].keyword,"OR") == 0){
			OR_gate(logic ,i );
		}

		else if (strcmp(logic.data[i].keyword,"NOT") == 0){
			NOT_gate(logic ,i );
		}

		else if (strcmp(logic.data[i].keyword,"FLIPFLOP") == 0){
			out = *former_out ;
			FLIPFLOP_gate(logic ,i , out );
			*former_out = logic.data[i].output->state ;
		}
	}
} 

void AND_gate(LOGIC logic , int i ){

	INPUT *cur;
	int	output ,
		j = 0  ,
		q = 0  , 
		first = 1 ,
		secound = 0 ,
		third = 0 ,
		found1 = 0 ,
		found2 = 0 ,
		found3 = 0 ;

	for ( j=i-1 ; j >= 0 ; j-- ){
		if (strcmp(logic.data[j].keyword,"INPUT") == 0){
			q = 0;
			first = 1 ;
			cur = logic.data[j].input ; 
			while (q < logic.data[j].size_of_input){
				if(first){
					if (strcmp(logic.data[i].input->name,cur->name) == 0){
						logic.data[i].input->state = cur->state ;
						first = 0 ;
						secound = 1 ;
						found1 = 1 ;
					}
					if (strcmp(logic.data[i].input->next->name,cur->name) == 0){
						logic.data[i].input->next->state = cur->state ;
						first = 0 ;
						third = 1 ;
						found1 = 1 ;
					
					}
				}
				if(secound){
					if (strcmp(logic.data[i].input->next->name,cur->name) == 0){
						logic.data[i].input->next->state = cur->state ;
						found2 = 1 ;
						break;
					}	
				}
				if(third){
					if (strcmp(logic.data[i].input->name,cur->name) == 0){
						logic.data[i].input->state = cur->state ;
						found3 = 1 ;
						break;
					}	
				}
				cur = cur->next;
				q++;
			}
		}
		else {
			if (found1 && secound){
				if (strcmp(logic.data[j].output->name,logic.data[i].input->next->name) == 0 ){
					logic.data[i].input->next->state = logic.data[j].output->state ;
					found2 = 1 ; 
				}
			}
			if (found1 && third){
				if (strcmp(logic.data[j].output->name,logic.data[i].input->name) == 0){
					logic.data[i].input->state = logic.data[j].output->state ;
					found3 = 1 ;
				}
			}
			else {
				if (strcmp(logic.data[j].output->name,logic.data[i].input->name) == 0){
					logic.data[i].input->state = logic.data[j].output->state ;
					found1 = 1 ;
				}
			
				if (strcmp(logic.data[j].output->name,logic.data[i].input->next->name) == 0){
					logic.data[i].input->state = logic.data[j].output->state ;
					found2 = 1;
//					printf("bbb\n");
				}
			}				
		}

	}
	if (!(found1 && (found2 || found3))){
		printf("invalid declaration in line ( %d )\n",i+1);
		exit(1);
	}
	if ((logic.data[i].input->next->state == 1) && (logic.data[i].input->state == 1 )){
		logic.data[i].output->state = 1 ;
	}
	else {
		logic.data[i].output->state = 0 ;	
	}
	for ( q = i+1 ; q < logic.size; q++ ){
		
		if (strcmp(logic.data[q].keyword,"INPUT") != 0){
			cur = logic.data[q].input;
			j=0;
			while(j<logic.data[q].size_of_input){
				if (strcmp(logic.data[i].output->name , cur->name) == 0){
					cur->state = logic.data[i].output->state ;
				}
				cur = cur->next;
				j++;
			}
		}
	}

}

void OR_gate(LOGIC logic , int i ){


	INPUT *cur;
	int	output ,
		j = 0  ,
		q = 0  , 
		first = 1 ,
		secound = 0 ,
		third = 0 ,
		found1 = 0 ,
		found2 = 0 ,
		found3 = 0 ;

	for ( j=0 ; j < i ; j++){
		if (strcmp(logic.data[j].keyword,"INPUT") == 0){
			q = 0;
			first = 1 ;
			cur = logic.data[j].input ; 
			while (q < logic.data[j].size_of_input){
				if(first){
					if (strcmp(logic.data[i].input->name,cur->name) == 0){
						logic.data[i].input->state = cur->state ;
						first = 0 ;
						secound = 1 ;
						found1 = 1 ;
					}
					if (strcmp(logic.data[i].input->next->name,cur->name) == 0){
						logic.data[i].input->next->state = cur->state ;
						first = 0 ;
						secound = 0 ;
						third = 1 ;
						found1 = 1 ;
					}
				}
				if(secound){
					if (strcmp(logic.data[i].input->next->name,cur->name) == 0){
						logic.data[i].input->next->state = cur->state ;
						found2 = 1 ;
						break;
					}	
				}
				if(third){
					if (strcmp(logic.data[i].input->name,cur->name) == 0){
						logic.data[i].input->state = cur->state ;
						found3 = 1 ;
						break;
					}	
				}
				cur = cur->next;
				q++;
			}
		}
		else {
			if (found1 && secound){
				if (strcmp(logic.data[j].output->name,logic.data[i].input->next->name) == 0 ){
					logic.data[i].input->next->state = logic.data[j].output->state ;
					found2 = 1 ; 
				}
			}
			if (found1 && third){
				if (strcmp(logic.data[j].output->name,logic.data[i].input->name) == 0){
					logic.data[i].input->state = logic.data[j].output->state ;
					found3 = 1 ;
				}
			}
			else {
				if (strcmp(logic.data[j].output->name,logic.data[i].input->name) == 0){
					logic.data[i].input->state = logic.data[j].output->state ;
					found1 = 1 ;
				}
			
				if (strcmp(logic.data[j].output->name,logic.data[i].input->next->name) == 0){
					logic.data[i].input->state = logic.data[j].output->state ;
					found2 = 1;
					found3 = 1;
				}
			}				
		}

	}
	if (!(found1 && (found2 || found3))){
		printf("invalid declaration in line ( %d )\n",i+1);
		exit(1);
	}
	if ((logic.data[i].input->next->state == 0) && (logic.data[i].input->state == 0 )){
		logic.data[i].output->state = 0 ;
	}
	else {
		logic.data[i].output->state = 1 ;	
	}
	for ( q = i+1 ; q < logic.size; q++ ){
		
		if (strcmp(logic.data[q].keyword,"INPUT") != 0){
			cur = logic.data[q].input;
			j=0;
			while(j<logic.data[q].size_of_input){
				if (strcmp(logic.data[i].output->name , cur->name) == 0){
					cur->state = logic.data[i].output->state ;
				}
				cur = cur->next;
				j++;
			}
		}
	}
}

void NOT_gate(LOGIC logic , int i ){

	int found = 0 , j =0 , q =0;
	INPUT *cur ;

	for(j=i-1 ; j >= 0 ; j-- ){
		if (strcmp(logic.data[j].keyword,("INPUT")) == 0 && !found){
			cur = logic.data[j].input ;
			q =0;
			while(q < logic.data[j].size_of_input){
				if (strcmp(cur->name,logic.data[i].input->name) == 0 ){
					logic.data[i].input->state = cur->state;
					found = 1 ;
					break;
				}
				q++;
				cur = cur->next;
			}
		}
		else if (strcmp(logic.data[j].keyword,("INPUT")) != 0 && !found){
			if (strcmp(logic.data[j].output->name,logic.data[i].input->name) == 0){
				logic.data[i].input->state = logic.data[j].output->state ;
				found = 1 ;
				break;
			}
		}

	}
	if (!found ){
		printf("invalid declaration in line ( %d )\n",i+1);
		exit(1);
	}
	if (logic.data[i].input->state == 1){
		logic.data[i].output->state = 0;
	}
	if (logic.data[i].input->state == 0){
		logic.data[i].output->state = 1;
	}
	for ( q = i+1 ; q < logic.size; q++ ){
		
		if (strcmp(logic.data[q].keyword,"INPUT") != 0){
			cur = logic.data[q].input;
			j=0;
			while(j<logic.data[q].size_of_input){
				if (strcmp(logic.data[i].output->name , cur->name) == 0){
					cur->state = logic.data[i].output->state ;
				}
				cur = cur->next;
				j++;
			}
		}
	}
}

void FLIPFLOP_gate(LOGIC logic , int i, int out){

	int found = 0 , j =0 , q =0;
	INPUT *cur ;

	for(j=0 ; j < i ; j++ ){
		if (strcmp(logic.data[j].keyword,("INPUT")) == 0 && !found){
			cur = logic.data[j].input ;
			q =0;
			while(q < logic.data[j].size_of_input){
				if (strcmp(cur->name,logic.data[i].input->name) == 0 ){
					logic.data[i].input->state = cur->state;
					found = 1 ;
					break;
				}
				q++;
				cur = cur->next;
			}
		}
		else if (strcmp(logic.data[j].keyword,("INPUT")) != 0 && !found){
			if (strcmp(logic.data[j].output->name,logic.data[i].input->name) == 0){
				logic.data[i].input->state = logic.data[j].output->state ;
				found = 1 ;
				break;
			}
		}

	}
	if (!found ){
		printf("invalid declaration in line ( %d )\n",i+1);
		exit(1);
	}
	if (logic.data[i].input->state == out){
		logic.data[i].output->state = 0;
		
	}
	else {
		logic.data[i].output->state = 1;
		
	}
	for ( q = i+1 ; q < logic.size; q++ ){
		
		if (strcmp(logic.data[q].keyword,"INPUT") != 0){
			cur = logic.data[q].input;
			j=0;
			while(j<logic.data[q].size_of_input){
				if (strcmp(logic.data[i].output->name , cur->name) == 0){
					cur->state = logic.data[i].output->state ;
				}
				cur = cur->next;
				j++;
			}
		}
	}	
}

int find_output_line(LOGIC logic){
	int i =0 ;
	for(i=(logic.size-1) ; i >=0 ; i--){
		if (strcmp(logic.data[i].keyword,"INPUT") != 0){
			return logic.data[i].output->state ;
		}

	}
}	

void freeing_struct_cir(LOGIC logic){

	int i = 0 ,j=0 ,temp =0,q=0;
	INPUT *cur ;

	for(i =(logic.size-1) ;i >= 0;i--){
		if (logic.data[i].output != NULL){
			free(logic.data[i].output);
		}
		temp = logic.data[i].size_of_input;
		for (q=0; q < logic.data[i].size_of_input; ++q){
			cur = logic.data[i].input;
			while(j < temp){
				cur = cur->next;
				j++;
			}
			free(cur);
			temp--;
			j=0;
		}
	}
	free(logic.data);
	
}

void freeing_struct_in(DIGIT_I digit){

	int i = 0 ,j=0 ,temp =0,q=0;
	DIGIT *cur ;

	for(i =(digit.size-1) ;i >= 0;i--){
		
		temp = digit.data[i].size_of_input;
		for (q=0; q < digit.data[i].size_of_input; ++q){
			cur = digit.data[i].digit;
			while(j < temp){
				cur = cur->next;
				j++;
			}
			free(cur);
			temp--;
			j=0;
		}
	}
	free(digit.data);
	
}