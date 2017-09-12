#ifndef Q_LEARNING
#define Q_LEARNING

#define ulli unsigned long long int

#define INVALID ~(0)
#define TERMINAL ~(0)

typedef struct Qlearning Qlearning;
struct Qlearning
{
	// the state number max unsigned long long int is the termina state and is not defined
	double** Q;		// Q[s][a] ==>> Qvalue for taking action a when in state s
	double** E;		// E[s][a] ==>> Eligibility trace
	
	ulli state_count;	// number of states in state space
	ulli action_count;	// number of actions in action space
	
	double alpha;	// represents learning rate
	double gama;	// represents the rememberance for past encountered rewards
	double lambda;	// represents decay eligibility trace factor
	double epsilon;	// represents the probability for exploration
	
	ulli state_prev;	// previously encountered state ~(0) == terminal state for no previous state
	ulli action_prev;	// not describeable if state_prev == ~(0)
	
	double* temp;		//  a temporary vector used for coputation
};

// used to initialize Qlearning struct
void init_Qlearning(Qlearning* Qlearn, ulli state_count, ulli action_count,double alpha,double gama,double lamda,double epsilon);

// policy to try , this function returns action to be tried
ulli policy(Qlearning* Q, ulli state);

// this method uses the defined policy to get the action and update the Qvalues using the initialized values
// return INVALID if state = TERMINAL
ulli get_action(Qlearning* Qlearn,double reward,ulli state);

// call this function to delete all of the values of the Qlearning struct
void delete_Qlearning(Qlearning* Qlearn);

// call this function for debug purpose
void print_Qlearning(Qlearning* Qlearn);

#endif
