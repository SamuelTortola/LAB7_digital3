////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
//Universidad del valle de Guatemala
//Alan Gomez - 22115
//Samuel Tortola - 22094
//Curso Digital 3 -  IE9059
//Laboratorio 7 
//Hardware: Raspberry Pi 5 8GB RAM
//Temporizadores, Tareas Periódicas y Sincronización Simple 
//FECHA 18/03/2025
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
/*El presente programa consiste en un programa con tres hilos. Cada hilo es responsable de encender
y apagar una de las luces. Para evitar que haya más de una luz encendida a la vez, se implementa 
 un mecanismo de sincronización para los hilos. Esto se hizo por medio de semáforos
(semaphores). Se ajustó  la prioridad y la política de escalonamiento de los hilos. El
programa permite ingresar como argumentos las prioridades de los tres hilos. Si se corre el
programa sin argumentos, las prioridades por defecto deben ser todas iguales a 1.  */
////////////////////////////////////////////////////////////////////////////////////
//Bibliotecas
////////////////////////////////////////////////////////////////////////////////////
#define _GNU_SOURCE 
#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sched.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <sys/timerfd.h>
#include <wiringPi.h>
#include <stdio.h>
#include <semaphore.h>// Libreria de semaforos
#include "IE3059lab7.h"

////////////////////////////////////////////////////////////////////////////////////
// Definiciones
////////////////////////////////////////////////////////////////////////////////////
#define LED_PASO1 2   // de la Raspberry, físico 13
#define LED_PASO2 3  // de la Raspberry, físico 15
#define LED_PEATONAL 27  //de la Raspberry, físico 36
#define BOTON_PEATONAL 26  // de la Raspberry, físico 32

#define INIT_VALUE 1 // Valor inicial del semáforo

////////////////////////////////////////////////////////////////////////////////////
// Variables globales
////////////////////////////////////////////////////////////////////////////////////
pthread_t hilo[3];
sem_t my_semaphore; // Semáforo
int estado_boton = 0; // Variable para almacenar el estado del botón    
int boton_presionado = 0; // Variable para registrar si el botón fue presionado
////////////////////////////////////////////////////////////////////////////////////
// Funciones
////////////////////////////////////////////////////////////////////////////////////
void *LUZ_1(void *arg) {
    while (1) {
        sem_wait(&my_semaphore);
        digitalWrite(LED_PASO1, HIGH);
        sleep(1); // 1 segundo de espera
        digitalWrite(LED_PASO1, LOW);
        sem_post(&my_semaphore);
        usleep(1000); // 1 ms de espera
    }
    return NULL;
}

void *LUZ_2(void *arg) {
    while (1) {
        sem_wait(&my_semaphore);
        digitalWrite(LED_PASO2, HIGH);
        sleep(1); // 1 segundo de espera
        digitalWrite(LED_PASO2, LOW);
        sem_post(&my_semaphore);
        usleep(1000); // 1 ms de espera
    }
    return NULL;
}
void *LUZ_3(void *arg) {

    while (1) {
        // Si el botón fue presionado, activar la luz peatonal
        sem_wait(&my_semaphore);
        if (check_button()) {
            digitalWrite(LED_PEATONAL, HIGH);
            sleep(1); // 1 segundo de espera
            digitalWrite(LED_PEATONAL, LOW);
            // Resetear el estado del botón
            clear_button();
        }

        sem_post(&my_semaphore);

        usleep(10000); // 1 ms de espera
    }
    return NULL;
}

////////////////////////////////////////////////////////////////////////////////////
// MAIN
////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[]) {
    // Inicializar WiringPi y configurar pines
    wiringPiSetup();
    // Configurar pines como salida
    pinMode(LED_PASO1, OUTPUT);
    pinMode(LED_PASO2, OUTPUT);
    pinMode(LED_PEATONAL, OUTPUT);
    // Configurar el pin del botón como entrada con pull-down
    pinMode(BOTON_PEATONAL, INPUT);
    pullUpDnControl(BOTON_PEATONAL, PUD_DOWN);

    // Inicializar semáforo
    sem_init(&my_semaphore, 0, INIT_VALUE);
    /////////////////////////////////////////////////////////////////////////////
    // Configurar prioridades
    pthread_t hilo[3];
    pthread_attr_t attr[3];
    struct sched_param param[3];
    int politica = SCHED_RR;

    int prioridades[3] = {1, 1, 1}; // Prioridades por defecto

    // Si se ingresaron prioridades como argumentos
    if (argc == 4) {
        prioridades[0] = atoi(argv[1]);
        prioridades[1] = atoi(argv[2]);
        prioridades[2] = atoi(argv[3]);
    }


    // Crear hilos con prioridades
for (int i = 0; i < 3; i++) {
    // Inicializar atributos del hilo
    pthread_attr_init(&attr[i]);

    // Establecer la política de escalonamiento
    pthread_attr_setschedpolicy(&attr[i], politica); // Política Round Robin (SCHED_RR)

    // Establecer la política de herencia de programación
    pthread_attr_setinheritsched(&attr[i], PTHREAD_EXPLICIT_SCHED); 
    //Esta línea es clave para que se use la política y prioridad definida porque por defecto se hereda la política y prioridad del hilo padre

    // Establecer la prioridad del hilo
    param[i].sched_priority = prioridades[i];
    pthread_attr_setschedparam(&attr[i], &param[i]);

    // Crear el hilo correspondiente
    if (i == 0) {
        pthread_create(&hilo[i], &attr[i], LUZ_1, NULL);
    } else if (i == 1) {
        pthread_create(&hilo[i], &attr[i], LUZ_2, NULL);
    } else if (i == 2) {
        pthread_create(&hilo[i], &attr[i], LUZ_3, NULL);
    }
}


    // Mantener el programa en ejecución
    while (1) {
        usleep(1000);// 50000 microsegundos = 50 ms
    }

    // Destruir semáforo
    sem_destroy(&my_semaphore);

    return 0;
}
