#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#define MAX_THREAD 6 // Maximum thread
#define MAX_OPERATION 40000000 // must be multiple of MAX_THREAD

typedef struct{
	long int min;
	long int max;
}Sequence;

void *arithematic_thread(void *args){
	int min, max;
	Sequence *seq = (Sequence *)args;
	min = seq->min;
	max = seq->max;
	

	int m=5;
	for(int i=min; i<max; i++)
	{
		m= i*i;		
	}
	
	double a=5.0;
	double i = 1.0;
	for(i = min; i < max; i = i + 1.0)
	{	
		a=i*i;
	}
		
	return NULL;
}



int main(int args, char *argv[]){
	pthread_t tid[MAX_THREAD];
	int indx = 0;
	long int operationPerThread = 0;
	Sequence sendData[MAX_THREAD];
	operationPerThread = MAX_OPERATION/MAX_THREAD;
	// create thread
	
	long ns=0;
	long int ns1,ns2;
	struct timespec spec1, spec2;
	clock_gettime(CLOCK_REALTIME, &spec1);
	ns1 = spec1.tv_nsec;

	long int total_nano_seconds=0;
	double max_operations;
	for(indx = 0; indx < MAX_THREAD; indx++)
	{	
		
		sendData[indx].min = indx*operationPerThread + 1;
		sendData[indx].max = sendData[indx].min + operationPerThread - 1;   	
		

		long int nano_seconds;
		struct timespec specm, specm2;
		clock_gettime(CLOCK_REALTIME, &specm);
		nano_seconds = specm.tv_nsec;		
           	
		pthread_create(&tid[indx], NULL, arithematic_thread, (void *)(sendData + indx));
	     
	    long int nano_seconds2;
	    clock_gettime(CLOCK_REALTIME, &specm2);
		nano_seconds2 = specm2.tv_nsec;
	    total_nano_seconds+=(nano_seconds2-nano_seconds);
		max_operations = sendData[indx].max;

	}

	// wait till all thread finish
	for(indx = 0; indx < MAX_THREAD; indx++)
	{
		pthread_join(tid[indx], NULL);
	}
	
		clock_gettime(CLOCK_REALTIME, &spec2);
		ns2=spec2.tv_nsec;

		ns=ns2-ns1;
		
		printf("total time taken to creating thread :%ld \n",total_nano_seconds);
		
		printf("total time :%ld\n",ns);

		printf("operation performed in one second :%lf\n",max_operations/1000000000);
		
		printf("effective time :%ld\n",(ns-total_nano_seconds));

	return 0;
}
