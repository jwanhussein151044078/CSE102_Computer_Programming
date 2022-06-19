#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define P_BI_G_NUMBER 728

void bi_grams_generator(char *posible_bi_grams[P_BI_G_NUMBER]);
double dissimilarity(char *file_l ,char *file_x,char *posible_bi_grams[P_BI_G_NUMBER]);
double absolute_value(double x);
void print_dissimilarity(void);
void reset_arrays(double array[P_BI_G_NUMBER]);
void read_file(char * File , double array[P_BI_G_NUMBER] ,char *posible_bi_grams[P_BI_G_NUMBER]);

void main(void)
{
	print_dissimilarity();
}
/*  creating a 2D string array that include all the possibilitis  */
void bi_grams_generator(char *posible_bi_grams[P_BI_G_NUMBER]){ 
	char a = 'a' , space = ' ';
	int i=0 ,j=0 ,q=0,w=0;

	while(i<P_BI_G_NUMBER)  
	{
		if(q== 28){q=0;j++;w=0;}
		while(q<28){
   			posible_bi_grams[i]=calloc(2, sizeof(char));
   			if (q == 0){
   				posible_bi_grams[i][0]=space;
  				posible_bi_grams[i][1]=a+j;	
   			}
   			else if (q == 27){
   				posible_bi_grams[i][0]=a+j;
  				posible_bi_grams[i][1]=space;
   			}
   			else {  
   				posible_bi_grams[i][0]=a+j;
  				posible_bi_grams[i][1]=a+w;
  				w++;
  			}
  			i++;
  			q++;
		}
	}
}
/*  find and return the value of the dissimilarity  */
double dissimilarity(char *file_l ,char *file_x,char *posible_bi_grams[P_BI_G_NUMBER]){
		
	int i = 0 ;

	double array_x[P_BI_G_NUMBER] ,
		   array_l[P_BI_G_NUMBER] ,
		   dissimilarity = 0.0 ,
		   sub = 0.0 ;

	/*  resetting the arrays to zero  */
	reset_arrays(array_x); 
	reset_arrays(array_l);
	
	read_file(file_x,array_x,posible_bi_grams);
	read_file(file_l,array_l,posible_bi_grams);
	
	for (i = 0; i < P_BI_G_NUMBER ; i++ ){

		sub = array_x[i] - array_l[i];
		dissimilarity = dissimilarity + absolute_value(sub);	
	
	}
	
	return dissimilarity ;

}

/*  function to return the absolute value  */
double absolute_value(double x){
	
	if (x < 0){
		x = x * -1 ;
	}
	return x ;
}

/*  function to reset the array to zero  */
void reset_arrays(double array[P_BI_G_NUMBER]){
	int i = 0 ;

	for (i=0;i<P_BI_G_NUMBER;i++){
		array[i] = 0.0 ; 
	} 

}

/*  function that count the occurrence of each bi-gram  */
void read_file(char * File , double array[P_BI_G_NUMBER] ,char *posible_bi_grams[P_BI_G_NUMBER]){
	
	char  *temp = malloc(2*sizeof(char)) ,
		  ch ;
	
	int s_o_bigrams = 0 ,
		i = 0 ;

	FILE* file = fopen(File,"r");

		ch = getc(file);
		temp[0] = ch ;
		
		while((ch = getc(file)) != EOF){
			temp[1] = ch ;
			if (temp[1] == '\n'){temp[1] = ' ';}
			else if (temp[0] == '\n'){temp[0] = ' ';}
			
			if ((temp[0] != ' ' || temp[1] != ' ') && (temp[0] != '\n' && temp[1] != '\n' )){
				
				for( i=0 ; i < P_BI_G_NUMBER ; i++ ){
					//printf("%s\n",temp );
					if (strncmp(temp,posible_bi_grams[i],2) == 0){
						array[i]++;
						break;
					}
				}
				s_o_bigrams++;
			}
			temp[0] = temp[1] ;
		}
		if (temp[0] != ' ' && temp[1] != ' '){

			temp[1] = ' ';
			for( i=0 ; i < P_BI_G_NUMBER ; i++ ){
					//printf("%s\n",temp );
					if (strncmp(temp,posible_bi_grams[i],2) == 0){
						array[i]++;
						break;
					}
			}
			s_o_bigrams++;
		}

		for(i=0;i<P_BI_G_NUMBER;i++){
			array[i] = array[i] / s_o_bigrams;
		}

	free(temp);
	fclose(file);
}

void print_dissimilarity(void){
	int i = 0 ;
	char *posible_bi_grams[P_BI_G_NUMBER] ;

	bi_grams_generator(posible_bi_grams);

	printf("%f\n",dissimilarity("language_1.txt","language_x.txt",posible_bi_grams) );
	printf("%f\n",dissimilarity("language_2.txt","language_x.txt",posible_bi_grams) );
	printf("%f\n",dissimilarity("language_3.txt","language_x.txt",posible_bi_grams) );
	printf("%f\n",dissimilarity("language_4.txt","language_x.txt",posible_bi_grams) );
	printf("%f\n",dissimilarity("language_5.txt","language_x.txt",posible_bi_grams) );
	
	for(i = 0 ; i < P_BI_G_NUMBER ; i++ ){
		
		free(posible_bi_grams[i]);
	}
}