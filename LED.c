#include <wiringPi.h>
#include <stdio.h>
#include <unistd.h>  // Para sleep()

#define LED1 26  // Pin 26 en numeración wiringPi
#define LED2 27  // Pin 27 en numeración wiringPi

int main() {
    // Inicializar wiringPi
    if (wiringPiSetup() == -1) {
        printf("Error al inicializar wiringPi\n");
        return 1;
    }

    // Configurar pines como salida
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);

    printf("Encendiendo y apagando LEDs en bucle...\n");

    while (1) {
        digitalWrite(LED1, HIGH);
        digitalWrite(LED2, HIGH);
        printf("LEDs encendidos\n");
        sleep(1);

        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        printf("LEDs apagados\n");
        sleep(1);
    }

    return 0;
}
