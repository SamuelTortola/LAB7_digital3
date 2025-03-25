////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
//Universidad del valle de Guatemala
//Alan Gomez - 22115
//Samuel Tortola - 22094
//Curso Digital 3 -  IE9059
//Laboratorio 7 
//Hardware: Raspberry Pi 5 8GB RAM
//Escalonamiento de Tareas, Prioridades y Sincronización usando Semaphores 
//FECHA 19/03/2025
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

/*El presente programa consiste en utilizar 3 LEDS para una calle para permitir el paso
de una dirección del tránsito, otra dirección del transito y una luz peatonal. La luz encendida representa
“luz verde” (carros o peatones pueden avanzar), y la luz apagada representa “luz roja” (carros o
peatones deben detenerse). La luz peatonal sólo se activará si un botón (push button) se ha
presionado previamente (el botón es para indicar el deseo de los peatones de cruzar la calle).*/


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

#define LED_PASO1 2   //GPIO 2 de la Raspberry
#define LED_PASO2 3  //GPIO 3 de la Raspberry
#define LED_PEATONAL 27  //GPIO 27 de la Raspberry
#define BOTON_PEATONAL 26  //GPIO 26 de la Raspberry




////////////////////////////////////////////////////////////////////////////////////
//Variables globales
////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////
//Funciones 
////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////
//MAIN
////////////////////////////////////////////////////////////////////////////////////

int main(void) {
  wiringPiSetup();
  pinMode(LED_PASO1, OUTPUT);
  pinMode(LED_PASO2, OUTPUT);
  pinMode(LED_PEATONAL, OUTPUT);
  pinMode(BOTON_PEATONAL, INPUT);

    while (1){
       // Encender luz de la primera dirección
       digitalWrite(LED_PASO1, HIGH);
       digitalWrite(LED_PASO2, LOW);
       digitalWrite(LED_PEATONAL, LOW);
       sleep(1); // Esperar 1 segundo

       // Encender luz de la segunda dirección
       digitalWrite(LED_PASO1, LOW);
       digitalWrite(LED_PASO2, HIGH);
       digitalWrite(LED_PEATONAL, LOW);
       sleep(1); // Esperar 1 segundo

        // Revisar el botón peatonal
        if (check_button()) {
        // Encender luz peatonal
        digitalWrite(LED_PASO1, LOW);
        digitalWrite(LED_PASO2, LOW);
        digitalWrite(LED_PEATONAL, HIGH);
        sleep(1); // Esperar 1 segundo

        // Resetear el estado del botón
        clear_button();
    }


    }
    return 0;
}
