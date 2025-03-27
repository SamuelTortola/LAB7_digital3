/*
* test_thrd_sem1.c
* Por: Luis Alberto Rivera
*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdlib.h>
#include <time.h>

#define INIT_VALUE	1		// Para el valor inicial del semáforo

void My_thread1(void *ptr);	// prototipo

sem_t my_semaphore;	// counting semaphore

int main(void)
{
	pthread_t thread1;
	int counter = 0;

	srand(time(NULL));	// inicializa semilla del generador de números aleatorios

	// ¿Qué pasa si se usan otros valores iniciales?
	sem_init(&my_semaphore, 0, INIT_VALUE);

	pthread_create(&thread1, NULL, (void*)&My_thread1, (void *)&counter);
	
	while(counter < 20)
	{
		usleep(500000+rand()%1000001);	// tiempo aleatorio entre 0.5 y 1.5 segundos
		sem_wait(&my_semaphore);
		counter++;
		sem_post(&my_semaphore);
		printf("ParentThread: %d \n", counter);
	}
	
	pthread_join(thread1, NULL);		// espera que que el hilo termine.
	
	return(0);
}

void My_thread1(void *ptr)
{
	int *cont;	// Notar que se podría usar el mismo nombre, pero de todos modos
				// no sería la misma variable que la del main. Este es un puntero local.
	cont = (int *)ptr;	// Con esto, el puntero apunta a la dirección de la
						// variable del main.

	while(*cont < 20)
	{
		usleep(500000+rand()%1000001);	// tiempo aleatorio
		sem_wait(&my_semaphore);
		(*cont)++;
		sem_post(&my_semaphore);
		printf("My_thread1: %d \n", *cont);
	}
	
	pthread_exit(0);
}
