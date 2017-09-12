#include"../inc/vector.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

// this source file consists of certain methods that are most easy to vectorize or to perform on a GPU but due to lack of my knowledge i haven't done it

// Computation between 2 vectors to give a vector
void COMPUTE_VECT_VECT(double* output,double* input1,char op,double* input2,ulli count)
{
	switch(op)
	{
		case '+':
		{
			for(ulli i=0;i<count;i++)
			{
				output[i] = input1[i] + input2[i];
			}
			break;
		}
		case '*':
		{
			for(ulli i=0;i<count;i++)
			{
				output[i] = input1[i] * input2[i];
			}
			break;
		}
		case '-':
		{
			for(ulli i=0;i<count;i++)
			{
				output[i] = input1[i] - input2[i];
			}
			break;
		}
		case '/':
		{
			for(ulli i=0;i<count;i++)
			{
				output[i] = input1[i] / input2[i];
			}
			break;
		}
	}
}

// computation between a vector and a scaler to give a vector
void COMPUTE_VECT_SCALER(double* output,double* input1,char op,double input2,ulli count)
{
	switch(op)
	{
		case '+':
		{
			for(ulli i=0;i<count;i++)
			{
				output[i] = input1[i] + input2;
			}
			break;
		}
		case '*':
		{
			for(ulli i=0;i<count;i++)
			{
				output[i] = input1[i] * input2;
			}
			break;
		}
		case '-':
		{
			for(ulli i=0;i<count;i++)
			{
				output[i] = input1[i] - input2;
			}
			break;
		}
		case '/':
		{
			for(ulli i=0;i<count;i++)
			{
				output[i] = input1[i] / input2;
			}
			break;
		}
	}
}

// copy a vector from a vector to another vector
void COPY_VECT_VECT(double* output,double* input,ulli count)
{
	for(ulli i=0;i<count;i++)
	{
		output[i] = input[i];
	}
}

// copy a vector to all of the scaler
void COPY_VECT_SCALER(double* output,double input,ulli count)
{
	for(ulli i=0;i<count;i++)
	{
		output[i] = input;
	}
}

// get all all the elements from the vectors inside a particular matrix that have the same index and copy them to a separate vector
void GET_MAT_VECT(double* output,double** input,ulli index,ulli count)
{
	for(ulli i=0;i<count;i++)
	{
		output[i] = input[i][index];
	}
}

// set all the elements in the matrix vectors at the indexed position to all the elements with the given vector correspondingly
void SET_MAT_VECT(double** output,double* input,ulli index,ulli count)
{
	for(ulli i=0;i<count;i++)
	{
		output[i][index] = input[i];
	}
}

// print a vectorjust another debug function statement
void PRINT_VECT(double* output,ulli count)
{
	for(ulli i=0;i<count;i++)
	{
		printf("%lf ",output[i]);
	}
}
// you know me know right ?
void PRINT_MAT(double** output,ulli count1,ulli count2)
{
	for(ulli i=0;i<count1;i++)
	{
		PRINT_VECT(output[i],count2);
		printf("\n");
	}
}

// set a vector with all random values in a max to min range
void RANDOM_VECT(double* output,double max,double min,ulli count)
{
	static int m = 0;
	if( m == 0 )
	{
		srand( time(NULL) );
		m++;
	}
	for(ulli i=0;i<count;i++)
	{
		output[i] = (  ( rand() % ( (ulli)( (max - min) * 1000000 ) ) ) / ((double)1000000) ) + min;
	}
}

// set matric values to random
void RANDOM_MAT(double** output,double max,double min,ulli count1,ulli count2)
{
	for(ulli i=0;i<count1;i++)
	{
		RANDOM_VECT(output[i],max,min,count2);
	}
}


