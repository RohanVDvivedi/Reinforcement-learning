#ifndef vectorh
#define vectorh

#define ulli unsigned long long int

void COMPUTE_VECT_VECT(double* output,double* input1,char op,double* input2,ulli count);
void COMPUTE_VECT_SCALER(double* output,double* input1,char op,double input2,ulli count);

void COPY_VECT_VECT(double* output,double* input,ulli count);
void COPY_VECT_SCALER(double* output,double input,ulli count);

void GET_MAT_VECT(double* output,double** input,ulli index,ulli count);
void SET_MAT_VECT(double** output,double* input,ulli index,ulli count);

void PRINT_VECT(double* output,ulli count);
void PRINT_MAT(double** output,ulli count1,ulli count2);

void RANDOM_VECT(double* output,double max,double min,ulli count);
void RANDOM_MAT(double** output,double max,double min,ulli count1,ulli count2);

#endif
