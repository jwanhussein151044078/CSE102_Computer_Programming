#include <stdio.h>

#define len 100

void read_file(char *file,char *str);
void print(char c,int count);
void recursive(char *str,int count);

void main()
{
	char str[len];
	int count=0;
	read_file("input.txt",str);
	recursive(str,count);
	
}

void read_file(char *file,char *str)
{
	FILE * i_File = fopen(file,"r") ;
	fscanf(i_File, "%s", str );
	fclose(i_File) ;
}

void recursive(char *str,int count)
{
	int i ;
	if(str[0]!='\0')
	{	
	 	if(str[0]=='('){
			count++;
		}
		else if(str[0]==')'){
			count--;
		}	
		else if((str[0]>='a' && str[0] <= 'z' ) || ( str[0]>='A' && str[0]<='Z' )){
			for(i=0;i<count;i++){
				printf("-");
			}
			printf("%c\n",str[0]);
		}
		recursive(str+1,count);	
	}
	
}

