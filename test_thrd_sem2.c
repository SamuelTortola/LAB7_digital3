/*
* test_thrd_sem2.c
* Por: Luis Alberto Rivera
*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdlib.h> 

#define INIT_VALUE	1
#define THR_COUNT	5

void My_thread1(void *ptr);  // Prototipo

sem_t my_semaphore;	// counting semaphore

// Es posible correr programas pasando argumentos. El número de argumentos (incluyendo
// el nombre del programa) se guarda en argc, y los argumentos en sí (tomados como strings)
// se almacenan en argv.

// En este programa en particular, se verifica si se llama al programa con un número entero
// para el valor inicial del semáforo. Si no, se usa el valor por defecto. El programa se
// correría así (usando el nombre correcto del ejecutable):
//     ./mi_programa
// o así
//     ./mi_programa valor

int main(int argc, char *argv[])	// argv es un arreglo de cadenas
{
	int i, initial_val = INIT_VALUE;	// Valor por defecto
	pthread_t threads[THR_COUNT];		// arreglo de variables tipo pthread
	int thr_index[THR_COUNT];			// arreglo de índices

	if(argc == 2)	// si se ingresó un valor
		initial_val = atoi(argv[1]);	// convierte la cadena apuntada por argv[1] a un entero

	sem_init(&my_semaphore, 0, initial_val);	// inicializa el semáforo
	
	// ciclo para crear los hilos
	for(i = 0; i < THR_COUNT; i++)
	{
		thr_index[i] = i+1;
		// Notar que a cada hilo se le pasa la dirección del i-ésimo índice
		pthread_create(&threads[i], NULL, (void*)&My_thread1, (void*)(thr_index+i));
	}
	
	for(i = 0; i < THR_COUNT; i++)
	{
		pthread_join(threads[i], NULL);		// Espera a que todos los hilos terminen.
	}
	
	return(0);
}

void My_thread1(void *ptr)
{
	int *index = (int *)ptr;	// Para recuperar el índice.
	int value;
	
	sem_wait(&my_semaphore);
	sem_getvalue(&my_semaphore, &value);	// obtiene el valor actual del sem.
	printf("Thread #: %d, sem value: %d\n", *index, value);
	fflush(stdout);
	sleep(1);
	sem_post(&my_semaphore);
		
	pthread_exit(0);
}
