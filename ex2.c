#include <stdlib.h>		// exit(3)
#include <pthread.h>
#include <stdio.h>      // printf and friends
#include <stdint.h>     // uint64_t and friends
#include <inttypes.h>   // PRIu64 and friends

#define NUM_THREADS     5

#define BUFLEN (8192)

uint64_t globalbuf[BUFLEN];

void *PrintHello(void *threadid)
{
    uint64_t i;
    for( i=0; i<BUFLEN; i++ ){
        globalbuf[i]++;
    }
    pthread_exit(NULL);
 }

int main (int argc, char *argv[]) {
	pthread_t threads[NUM_THREADS];
	int rc;
	long t;
    uint64_t i;
	for(t=0; t<NUM_THREADS; t++){
		rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
		if (rc){
			printf("ERROR; return code from pthread_create() is %d\n", rc);
			exit(-1);
		}
	}

	for( t=0; t<NUM_THREADS; t++ ){
		pthread_join( threads[t], NULL );
	}
    for( i=0; i<BUFLEN; i++ ){
        fprintf( stdout, "%" PRIu64 "", globalbuf[i] );
    }
    fprintf( stdout, "\n" );

    /* Last thing that main() should do */
    pthread_exit(NULL);
 }
