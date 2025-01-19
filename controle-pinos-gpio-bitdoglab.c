#include <stdio.h>
#include "pico/stdlib.h"

#define LED_VERMELHO 13
#define LED_AZUL 12
#define LED_VERDE 11
#define PINO_BUZZER 21



char entrada;

//Funções 
void iniciar_pinos(); 
void ativar_buzzer(int duration);

int main() {
    iniciar_pinos(); 
    stdio_init_all(); 
    sleep_ms(500);   

    while (true) {  
        printf("Aguardando entrada: ");

        // Usa scanf para capturar um caractere
        if (scanf(" %c", &entrada) == 1) { // Captura e verifica se foi bem-sucedido
            printf("\nEntrada: %c\n", entrada);
          switch (entrada){
            case 'A':
            printf("LED VERMELHO ON \n");
            break;
            case 'B':
            printf("BUZZER! \n");
            ativar_buzzer(1000);
            break;
            case 'F':
            printf("ENTRANDO NO MODO BOOT! \n");
            break;
            default:
            printf("ENTRADA INVÁLIDA \n");
          }
        } else {
            printf("\nErro ao capturar entrada.\n");
        }

        sleep_ms(250); // Aguarda um pouco antes de repetir
    }
}

void iniciar_pinos(){
    gpio_init(LED_VERMELHO);
    gpio_init(LED_VERDE);
    gpio_init(LED_AZUL);
    gpio_init(PINO_BUZZER);

    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    gpio_set_dir(LED_VERDE, GPIO_OUT);
    gpio_set_dir(LED_AZUL, GPIO_OUT);
    gpio_set_dir(PINO_BUZZER, GPIO_OUT);
}

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

