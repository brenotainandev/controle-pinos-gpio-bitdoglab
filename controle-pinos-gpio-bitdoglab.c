#include <stdio.h>
#include "pico/stdlib.h"

// Definição dos pinos dos LEDs e do buzzer
#define LED_VERMELHO 13
#define LED_AZUL 12
#define LED_VERDE 11
#define PINO_BUZZER 21

// Funções auxiliares
void iniciar_pinos();
void desligar_todos_leds();
void ligar_led(uint pin);
void ativar_buzzer(int duration);
void processar_comando(const char *comando);
void exibir_menu();

int main() {
    iniciar_pinos(); // Inicializa os pinos dos LEDs e do buzzer
    stdio_init_all(); // Inicializa o sistema de entrada/saída padrão
    sleep_ms(500); // Pequeno atraso para estabilização 

    while (true) {  
        printf("Aguardando entrada: ");

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

// === Funções Auxiliares ===

// Exibe o menu de opções
void exibir_menu() {
    printf("\n=== MENU ===\n");
    printf("RED   - Liga o LED vermelho\n");
    printf("GREEN - Liga o LED verde\n");
    printf("BLUE  - Liga o LED azul\n");
    printf("WHITE - Liga todos os LEDs (luz branca)\n");
    printf("OFF   - Desliga todos os LEDs\n");
    printf("BUZZ  - Ativa o buzzer\n");
    printf("============================\n");
}

// Inicializa os pinos dos LEDs e do buzzer
void iniciar_pinos() {
    gpio_init(LED_VERMELHO);
    gpio_init(LED_VERDE);
    gpio_init(LED_AZUL);
    gpio_init(PINO_BUZZER);

    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    gpio_set_dir(LED_VERDE, GPIO_OUT);
    gpio_set_dir(LED_AZUL, GPIO_OUT);
    gpio_set_dir(PINO_BUZZER, GPIO_OUT);

    desligar_todos_leds(); // Garante que todos os LEDs comecem desligados
}

// Desliga todos os LEDs
void desligar_todos_leds() {
    gpio_put(LED_VERMELHO, 0);
    gpio_put(LED_VERDE, 0);
    gpio_put(LED_AZUL, 0);
}

// Liga um LED específico
void ligar_led(uint pin) {
    gpio_put(pin, 1);
}

// Aciona o buzzer
void ativar_buzzer(int duration) {
    duration /= 2; // Divide a duração por 2 para gerar pulsos mais curtos
    for (int i = 0; i < duration; i++) {
        gpio_put(PINO_BUZZER, 1);
        sleep_us(500); // Meio período do ciclo
        gpio_put(PINO_BUZZER, 0);
        sleep_us(500); // Meio período do ciclo
    }
}

// Processa os comandos recebidos
void processar_comando(const char *comando) {

}