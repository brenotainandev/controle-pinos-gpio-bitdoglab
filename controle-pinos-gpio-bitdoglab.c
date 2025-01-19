#include <stdio.h>
#include "pico/stdlib.h"

#define PINO_BUZZER 15

// Aciona o buzzer
void ativar_buzzer(int duration)
{
    duration /= 2; // Divide a duração por 2 para gerar pulsos mais curtos
    for (int i = 0; i < duration; i++)
    {
        gpio_put(PINO_BUZZER, 1);
        sleep_us(500); // Meio período do ciclo
        gpio_put(PINO_BUZZER, 0);
        sleep_us(500); // Meio período do ciclo
    }
}

int main()
{
    stdio_init_all();

    while (true)
    {
        printf("Hello, world!\n");
        ativar_buzzer(1000);
        sleep_ms(1000);
    }
}
