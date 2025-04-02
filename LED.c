#include <wiringPi.h>
#include <stdio.h>
#include <unistd.h>  // Para sleep()

#define LED_PASO1 2       // GPIO 2 de la Raspberry
#define LED_PASO2 3       // GPIO 3 de la Raspberry
#define LED_PEATONAL 27   // GPIO 27 de la Raspberry
#define BOTON_PEATONAL 26 // GPIO 26 de la Raspberry

int main() {
    // Inicializar wiringPi
    if (wiringPiSetup() == -1) {
        printf("Error al inicializar wiringPi\n");
        return 1;
    }

    // Configurar pines como salida
    pinMode(LED_PASO1, OUTPUT);
    pinMode(LED_PASO2, OUTPUT);
    pinMode(LED_PEATONAL, OUTPUT);

    // Configurar el pin del botón como entrada con pull-down
    pinMode(BOTON_PEATONAL, INPUT);
    pullUpDnControl(BOTON_PEATONAL, PUD_DOWN);

    printf("Presiona el botón para encender los LEDs en secuencia...\n");

    while (1) {
        // Leer el estado del botón
        if (digitalRead(BOTON_PEATONAL) == HIGH) {
            printf("Botón presionado, encendiendo LEDs en secuencia...\n");

            // Encender LED_PASO1
            digitalWrite(LED_PASO1, HIGH);
            sleep(1); // Esperar 1 segundo
            digitalWrite(LED_PASO1, LOW);

            // Encender LED_PASO2
            digitalWrite(LED_PASO2, HIGH);
            sleep(1); // Esperar 1 segundo
            digitalWrite(LED_PASO2, LOW);

            // Encender LED_PEATONAL
            digitalWrite(LED_PEATONAL, HIGH);
            sleep(1); // Esperar 1 segundo
            digitalWrite(LED_PEATONAL, LOW);

            printf("Secuencia completada.\n");

            // Esperar a que el botón sea liberado para evitar múltiples activaciones
            while (digitalRead(BOTON_PEATONAL) == HIGH) {
                usleep(1000); // Esperar 1 ms
            }
        }

        usleep(1000); // Pequeño retraso para evitar lecturas rápidas
    }

    return 0;
}