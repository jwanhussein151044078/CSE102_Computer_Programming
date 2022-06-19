#include <stdio.h>
#include <stdlib.h>

#define M_number 1000

void readf(char* filename , double arry[M_number] , int *j);
void imputation(double **ar );
void write(char* filename ,double **array,double *f_array,int *index_array,int *cunks_size_array,int cunks_number );
void sort(double *array , int *arry ,int * index , int n);

int main(void)
	{
		double **ar;
  		imputation(ar);
		return 0;
	}

void readf(char* filename , double arry[M_number] , int *j)
	{
		int a , i;

		FILE * f;
		f = fopen(filename,"r");
		while((a != EOF)&&(i<M_number))
			{ 
				a = fscanf(f,"%lf ",&arry[i]);
				i++;
			}
		*j = i-1;
		fclose(f);
	}	

void write(char* filename ,double **array,double *f_array,int *index_array,int *cunks_size_array,int cunks_number )
	{
		int i,j;
		FILE *f;
		f = fopen(filename,"w");
		for(i=0;i<cunks_number;i++)
		{
			for(j=0;j<(cunks_size_array[i]);j++)
			{
				fprintf(f, "%f ",array[i][j] );
			}
			fprintf(f, "\n" );
		}
		
		fclose(f);
	}
void imputation(double **ar)
	{
		int i , j, cunks=0 ,x=0, sep_count=0 , count=0 , next_cunk=0 , *cunks_size ,cunk_number=0 ,index_count=0, *index_num;
		double arr[M_number],*cunks_avg ;
		readf("input.txt",arr,&j);
		for(i=0;i < M_number && i<j ;i++)/*  counting the number of seperator  */
		{
			if(arr[i]==0.0)
			{
				if(arr[i+1]==0.0)
				{
					if(arr[i+2]==0.0)
					{
						sep_count++;
						i=i+2;
					}
				}
			}
		}
		i=0;
		while(i<(sep_count+1))/*  counting the number of cunks  */
		{
			int on = 1 ;
			count =0;
			while((on == 1)&&(count < j))
			{
				if(arr[next_cunk+count] != 0.0)
				{
					count++;	
				}
				else 
				{
					if(arr[next_cunk+count+1] != 0.0)
					{
						count++;	
					}
					else 
					{
						if(arr[next_cunk+count+2] != 0.0)
						{
							count++;						
						}
						else 
						{
							on = 0;
						}	
					}
				}
			}
			next_cunk =	next_cunk + count + 3 ;
			if (count != 0 )
			{
				cunk_number++;
			}	
			i++;	
		}
		index_num = malloc((cunk_number)*sizeof(int));/*  allocating the array will contain cunks start index  */
		cunks_size = malloc((cunk_number)*sizeof(int));/*  allocating the array will contain each cunks size  */
		cunks_avg = malloc((cunk_number)*sizeof(double));/*  allocating the array will contain each cunks average  */
		i=0; next_cunk=0 ; count=0 ;
		while(i<(sep_count+1)) 
		{
			int on = 1 ;
			count =0;
			while((on == 1)&&(count < j))
			{
				if(arr[next_cunk+count] != 0.0)
				{
					
					cunks_avg[cunks]=(cunks_avg[cunks]+arr[next_cunk+count]);
					count++;
				}
				else 
				{
					if(arr[next_cunk+count+1] != 0.0)
					{
						cunks_avg[cunks]=(cunks_avg[cunks]+arr[next_cunk+count]);
						count++;
					}
					else 
					{
						if(arr[next_cunk+count+2] != 0.0)
						{
							
							cunks_avg[cunks]=(cunks_avg[cunks]+arr[next_cunk+count]);
							count++;				
						}
						else 
						{
							on = 0;
							index_count--;
						}
					}
				}
				index_count++;
			}
			next_cunk =	next_cunk + count + 3 ;
			if (count != 0 )
			{
				index_num[cunks] = index_count - count;
				cunks_avg[cunks]=cunks_avg[cunks]/count;
				cunks_size[cunks]=count;
				cunks++;
			}
			index_count = index_count + 3;
			i++;	
		}
		sort( cunks_avg,cunks_size ,index_num, cunk_number);
		ar = malloc(cunk_number * sizeof(double *));
		for(i=0;i<cunk_number;i++)
		{
			ar[i] = malloc(cunks_size[i]*sizeof(double));
			for(x=0;x<cunks_size[i];x++)
			{
				ar[i][x]=arr[(index_num[i]+x)];
			} 
		}
		write("output.txt",ar,arr,index_num,cunks_size,cunk_number );
}

void sort(double *array , int *arry ,int * index , int n)
	{
		int i,j;
		double swap;
		int swap1,swap2 ;
		for (i = 0 ; i < ( n - 1 ); i++)
  		{
    		for (j = 0 ; j < (n - i - 1); j++)
    		{
      			if (array[j] > array[j+1]) /* For decreasing order use < */
      			{
        			swap = array[j];
        			swap1 = index[j];
        			swap2 = arry[j];
        			array[j] = array[j+1];
        			index[j] = index[j+1];
        			arry[j] = arry[j+1];
        			array[j+1] = swap;
        			index[j+1] = swap1;
        			arry[j+1] = swap2;
      			}
    		}


		}
	}	

