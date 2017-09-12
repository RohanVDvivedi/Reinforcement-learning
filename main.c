#include "Qlearning.h"
#include <stdio.h>

enum action_space{top=0,bottom,left,right};

#define ulli unsigned long long int

int main()
{
	Qlearning qlearning;
	init_Qlearning(&qlearning,16,4,0.25,0.75,0.99,0.15);
	double reward;ulli new_state;
	ulli action;
	while(1)
	{
		printf("enter next state and reward : ");
		scanf("%lld %lf",&new_state,&reward);
		
		action = get_action(&qlearning,reward,new_state);
			
		switch(action)
		{
			case top:
				{
					printf("action = TOP\n");
					break;
				}
			case bottom:
				{
					printf("action = BOTTOM\n");
					break;
				}
			case left:
				{
					printf("action = LEFT\n");
					break;
				}
			case right:
				{
					printf("action = RIGHT\n");
					break;
				}
			case INVALID:
				{
					printf("action = INVALID\n");
					break;
				}
		}

		print_Qlearning(&qlearning);
		printf("\n");
	}
	return 0;
}
