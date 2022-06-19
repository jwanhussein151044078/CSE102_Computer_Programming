#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_SIZE 100
#define MAX_len 1000

void read_values(char *filename , double array[MAX_SIZE] , int *pointer );
void read_polynomial(char * filename ,char str[MAX_len]);
double calculate(double value );
void write(char * filename);

void main(void)
{	
	write("evaluations.txt");	
}

void read_values(char *filename , double array[MAX_SIZE] , int *pointer){ /*  read the value from the text file  */
	double a ;
	int i =0;
	FILE * file = fopen(filename,"r");
	while ((a != EOF) && (i < MAX_SIZE)){
		a = fscanf(file,"%lf",&array[i]);
		i++;
	}
	*pointer = i-1;
	fclose(file);
}

void read_polynomial(char * filename ,char str[MAX_len]){ /*  read the equation from the file  */
	char charecter;
	int i=0, j=0;
	FILE * file = fopen(filename,"r");
	 do
    {
        charecter = fgetc(file);
        if (feof(file)){
            break ;
        }
        if (charecter != ' '){
        	str[i] = charecter;
        	i++;
        }    
    }while(1);
	fclose(file);

}

void write(char * filename){ /* print the results obtained by inserting the value of the array into the calculate function  */ 
	FILE * file = fopen(filename,"w");
	double array[MAX_SIZE],results;
	int pointer ,i;
	read_values("values.txt",array,&pointer);
	for (i = 0; i < pointer; i++)
	{	
		fprintf(file, "%.2f\n",calculate(array[i]));
	}
	fclose(file);
	
}

double calculate(double value){
	char str[MAX_len], temp[MAX_len],coefficien_temp[MAX_len],power_temp[MAX_len] ;
	int i =0 , j =0 ,q = 0,w=0;
	double coefficient =0 ,power=0 , monomial =0 ,results =0 ,value1;
	read_polynomial("polynomial.txt",str);

	while(str[i]){
		/*  separating the monomials of the  equation  */
		if(str[i] == '+'){i++;temp[j] = '+';j =1;}
		else if(str[i] == '-'){i++;temp[j] = '-';j =1;}
		while(str[i] != '+' && str[i] != '-' && str[i]){
			temp[j] = str[i];
			i++;
			j++;

		}
		temp[j]='\0';
		if (str[i] != '+' && str[i] != '-' ){i++;}
		j=0;
		/*  find the coeffician of the monomials  */
		while(temp[q] != 'x'){
			coefficien_temp[q] = temp[q] ;
			q++;
		} 
		coefficien_temp[q]='\0';
		if(coefficien_temp[0] == '+' && coefficien_temp[1] == '\0') {coefficient = 1;}
		else if(coefficien_temp[0] == '-' && coefficien_temp[1] == '\0') {coefficient = -1;}
		else if(coefficien_temp[0] == '\0'){coefficient =1 ;}
		else{
			sscanf(coefficien_temp,"%lf",&coefficient);
		}
		/*  find the power of the monomials  */
		q++;
		if(temp[q] == '^'){
			q++;
			while(temp[q]){
				power_temp[w] = temp[q];
				q++;
				w++;
			}
			power_temp[w]='\0';
			sscanf(power_temp,"%lf",&power);
		}
		else power =1 ;
		q=0;
		w=0;
		value1 = pow(value,power); /*  value1 is value raised to the power of power  */
		monomial = coefficient * value1 ;
		results = results +	monomial ;
	}
	return results;
}

