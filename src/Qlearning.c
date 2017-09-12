#include "../inc/Qlearning.h"
#include <math.h>
#include "../inc/vector.h"
#include <stdlib.h>
#include <stdio.h>

void init_Qlearning(Qlearning* Qlearn, ulli state_count, ulli action_count,double alpha,double gama,double lambda,double epsilon)
{
	Qlearn->state_count = state_count;
	Qlearn->action_count = action_count;
	Qlearn->alpha = alpha;
	Qlearn->gama = gama;
	Qlearn->lambda = lambda;
	Qlearn->epsilon = epsilon;
	
	// Q value matrix
	Qlearn->Q = ( (double**) (malloc( sizeof(double*) * Qlearn->state_count )) );
	for( ulli i=0; i<Qlearn->state_count ; i++ )
	{
		Qlearn->Q[i] = ( (double*) (malloc( sizeof(double) * Qlearn->action_count )) );
		COPY_VECT_SCALER( Qlearn->Q[i] , 0 , Qlearn->action_count );
	}
	
	// Eligibility matrix
	Qlearn->E = ( (double**) (malloc( sizeof(double*) * Qlearn->state_count )) );
	for( ulli i=0; i<Qlearn->state_count ; i++ )
	{
		Qlearn->E[i] = ( (double*) (malloc( sizeof(double) * Qlearn->action_count )) );
		COPY_VECT_SCALER( Qlearn->E[i] , 0 , Qlearn->action_count );
	}
	
	// initializing state_prev to TERMINAL
	Qlearn->state_prev = TERMINAL;
	
	Qlearn->temp = (double*)(malloc(sizeof(double)*Qlearn->action_count));
}

// policy function is to be defined to specify what action to take in a given state
ulli policy(Qlearning* Qlearn,ulli state)
{
	ulli best_action;

	double rand_prob = ((double)(rand() % 1000000))/1000000;
	if( rand_prob <= Qlearn->epsilon )
	{
		best_action = (rand() % Qlearn->action_count);
	}
	else
	{
		double max_gain = Qlearn->Q[state][0];
		ulli stack_size = 1;
		Qlearn->temp[0] = 0;
		for(ulli i=1;i<Qlearn->action_count;i++)
		{
			if( max_gain < Qlearn->Q[state][i] )
			{
				stack_size = 1;
				Qlearn->temp[0] = i;
				max_gain = Qlearn->Q[state][i];
			}
			else if ( max_gain == Qlearn->Q[state][i] )
			{
				stack_size++;
				Qlearn->temp[stack_size-1] = i;
			}
		}
		best_action = Qlearn->temp[ (rand() % stack_size) ];
	}
	
	return best_action;
}

// pass state = TERMINAL_STATE to reinitialize the eligibility traces
// if a TERMINAL state is reached INVALID action is received
ulli get_action(Qlearning* Qlearn,double reward,ulli state)
{
	ulli action;
	
	// update policy
	
	// pick up action using policy, 
	// if TERMINAL state, the  action is invalid
	if( state == TERMINAL )
	{
		action = INVALID;
	}
	else	// else get action using the policy
	{
		action = policy(Qlearn,state);
	}
	
	// if make updates to Qvalue function only if previous state was not a terminal state
	if( Qlearn->state_prev != TERMINAL )	// that this is not out first attempt
	{
		double Qnew;
		if( state == TERMINAL )	// if the terminal state is reached just update states
		{
			Qnew = 0;
		}
		else
		{
			Qnew = Qlearn->Q[state][action];
		}
		
		// calculate delta
		double delta = (reward + Qlearn->gama * Qnew - Qlearn->Q[Qlearn->state_prev][Qlearn->action_prev]);
	
		// update eligibility value
		Qlearn->E[Qlearn->state_prev][Qlearn->action_prev] += 1;
	
		// update your Q values and E values
		for( ulli i=0; i<Qlearn->state_count ; i++ )
		{
			// update Q values of ith state
			COMPUTE_VECT_SCALER(Qlearn->temp,Qlearn->E[i],'*',(Qlearn->alpha * delta),Qlearn->action_count);
			COMPUTE_VECT_VECT(Qlearn->Q[i],Qlearn->Q[i],'+',Qlearn->temp,Qlearn->action_count);
			
			// update eligibity traces of ith state
			COMPUTE_VECT_SCALER(Qlearn->E[i],Qlearn->E[i],'*',Qlearn->gama * Qlearn->lambda,Qlearn->action_count);
		}
	}
	
	// make eligibility traces zero if current state achieved is a terminal state
	// this means we have completed an episode
	if( state == TERMINAL && Qlearn->state_prev != TERMINAL ) // this means if it is terminal state and reinitialize eligibility traces
	{
		// make eligibility trace vector to zero
		for( ulli i=0; i<Qlearn->state_count ; i++ )
		{
			COPY_VECT_SCALER( Qlearn->E[i] , 0 , Qlearn->action_count );
		}
	}
	
	// update _prev variables
	Qlearn->state_prev = state;
	Qlearn->action_prev = action;
	
	return action;
}

// delete Qlearning structure
void delete_Qlearning(Qlearning* Qlearn)
{
	for( ulli i=0; i<Qlearn->state_count ; i++ )
	{
		free( Qlearn->Q[i] );
	}
	free( Qlearn->Q );
	
	for( ulli i=0; i<Qlearn->state_count ; i++ )
	{
		free( Qlearn->E[i] );
	}
	free( Qlearn->E );
	
	free(Qlearn->temp);
}

// print Qlearning structure
void print_Qlearning(Qlearning* Qlearn)
{
	for( ulli i=0; i<Qlearn->state_count ; i++ )
	{
		printf("Qvalue of state %lld : ",i);PRINT_VECT( Qlearn->Q[i] , Qlearn->action_count);printf("\n");
	}
	printf("\n");
	for( ulli i=0; i<Qlearn->state_count ; i++ )
	{
		printf("eligibility of state %lld : ",i);PRINT_VECT( Qlearn->E[i] , Qlearn->action_count);printf("\n");
	}
}
