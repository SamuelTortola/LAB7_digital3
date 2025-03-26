////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
//Universidad del valle de Guatemala
//Alan Gomez - 22115
//Samuel Tortola - 22094
//Curso Digital 3 -  IE9059
//Laboratorio 7 
//Hardware: Raspberry Pi 5 8GB RAM
//Temporizadores, Tareas Periódicas y Sincronización Simple 
//FECHA 26/03/2025
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

/*El presente programa consiste en */


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
#include "IE3059lab7.h"
#include <wiringPi.h>




////////////////////////////////////////////////////////////////////////////////////
//Definiciones
////////////////////////////////////////////////////////////////////////////////////|

#define LED_PASO1 2   // de la Raspberry, físico 13
#define LED_PASO2 3  // de la Raspberry, físico 15
#define LED_PEATONAL 27  //de la Raspberry, físico 36
//#define BOTON_PEATONAL 26  // de la Raspberry, físico 32


////////////////////////////////////////////////////////////////////////////////////
//MAIN
////////////////////////////////////////////////////////////////////////////////////

int main(void) {
  wiringPiSetup();
  pinMode(LED_PASO1, OUTPUT);
  pinMode(LED_PASO2, OUTPUT);
  pinMode(LED_PEATONAL, OUTPUT);
  //pinMode(BOTON_PEATONAL, INPUT);



  pthread_t hilos[3]; // 3 hilos
    pthread_create(&hilos[0], NULL, (void*)&FIRST, NULL);    //Crear hilo 1
    pthread_create(&hilos[1], NULL, (void*)&SECOND, NULL);   //Crear hilo 2
    pthread_create(&hilos[2], NULL, (void*)&THIRD, NULL);    //Crear hilo 3


   // Esperar a que elos hilos terminen
   pthread_join(hilos[0], NULL);
   pthread_join(hilos[1], NULL);
   pthread_join(hilos[2], NULL);




    return 0;
}
