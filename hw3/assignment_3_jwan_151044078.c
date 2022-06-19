#include <stdio.h>
#include <string.h>

#define Max_len_row 250 /*  Maximum length of each row is 250  */
#define Max_row 100 /*  Maximum number of rows is 100  */

void read(char* filename , char input_array[Max_row][Max_len_row] , int * line_counter);
void searching(char input_array[Max_row][Max_len_row] , char str[Max_len_row]);

void main(void){
	
	char 	str1[]="Xanthos",
			str2[]="Patara",
			str3[]="Myra",
			str4[]="Arycanda",
			str5[]="Phaselis";
	char input_array[Max_row][Max_len_row];
	searching(input_array,str1);
	searching(input_array,str2);
	searching(input_array,str3);
	searching(input_array,str4);
	searching(input_array,str5);

}

void read(char* filename , char input_array[Max_row][Max_len_row] , int * line_counter){
	
	int i=0 ,counter =0;
	FILE * file ;
	char line[Max_len_row];
	file = fopen(filename,"r") ;
	while (fgets(line,sizeof(line),file) && counter < Max_row){ /*  reading the file line by line and cant read more than 100 line  */
		strcpy(input_array[i++],line); /*  copys the file into a 2D string array  */
		counter++;  /*  calculating the number of rows that the file include   */
	}
	*line_counter = counter ; /*  a pointer to stor the number of rows  */
	fclose(file);
}

void searching(char input_array[Max_row][Max_len_row] , char str[Max_len_row]){

	int line_counter ;
	int found ;
	int i = 0 ,j = 0, counter1 , counter2 ;
	read("input.txt",input_array,&line_counter);
	
	for (i=0 ; i < line_counter ;i++){ 
		for (j=0 ; input_array[i][j] != '\0'; j++){
			if (str[0] == input_array[i][j]){ /*  when find the first element from the substring in the input array string  */
				counter1 = 1 ; counter2 = 1 ;
				found =0 ;
				while (counter1 < strlen(str)){ /*  scanning horizontally  */
					if (str[counter1] == input_array[i][j + counter1]){ 
						found =1 ;
						counter1++;
					}
					else {
						found = 0;
						counter1 = strlen(str);
					}
				}
				if(found == 1){
					printf("%s (%d,%d) Horizontal\n",str , i+1 , j+1  );
				}
				while (counter2 < strlen(str)){ /*  scanning vertically  */
					if (str[counter2] == input_array[i + counter2][j]){
						found =2 ;
						counter2++;
					}
					else {
						found = 0;
						counter2 = strlen(str);
					}
				}	
				if(found == 2){
					printf("%s (%d,%d) Vertical\n",str , i+1 , j+1  );	
				}	
			}
		}
	}
}