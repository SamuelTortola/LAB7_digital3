#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *hilo_funcion(void *arg) {
    printf("Hilo ejecutándose con prioridad ajustada.\n");
    while (1) {
        // Simulación de trabajo del hilo
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t hilo;
    pthread_attr_t attr;
    struct sched_param param;
    int politica = SCHED_FIFO;  // Otras opciones: SCHED_RR, SCHED_OTHER (por defecto)
    
    // Inicializar atributos del hilo
    pthread_attr_init(&attr);
    
    // Establecer la política de escalonamiento
    pthread_attr_setschedpolicy(&attr, politica);

    // Establecer la prioridad del hilo
    param.sched_priority = 50;  // Valores típicos de 1 a 99 para FIFO y RR
    pthread_attr_setschedparam(&attr, &param);
    
    // Crear el hilo con los atributos modificados
    if (pthread_create(&hilo, &attr, hilo_funcion, NULL) != 0) {
        perror("Error al crear el hilo");
        return 1;
    }

    // Liberar los atributos
    pthread_attr_destroy(&attr);

    // Esperar a que el hilo termine (nunca ocurrirá en este ejemplo)
    pthread_join(hilo, NULL);

    return 0;
}
