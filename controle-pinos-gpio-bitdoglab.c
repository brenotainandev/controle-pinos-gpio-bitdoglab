#include <stdio.h>
#include <string.h>
#include <ctype.h>
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

    // Define o buffer de saída como não bufferizado
    setvbuf(stdout, NULL, _IONBF, 0);

    printf("\n=== Bem-vindo ao Sistema de Controle GPIO ===\n");

    char comando[10]; // Buffer para o comando digitado
    int i = 0;        // Índice do buffer

    exibir_menu();

    printf("\nDigite um comando: "); // Exibe o prompt inicial

    while (true) {
        char c = getchar(); // Captura um caractere do terminal

        if (c == '\n' || c == '\r') { // Verifica se é Enter
            comando[i] = '\0'; // Finaliza a string
            printf("\nComando completo: %s\n", comando);
            processar_comando(comando); // Processa o comando
            i = 0; // Reseta o índice do buffer
            printf("\nDigite um comando: "); // Solicita novo comando
        } else if (c == 127) { // Verifica se é Backspace
            if (i > 0) {
                i--;
                printf("\b \b"); // Remove o último caractere na tela
            }
        } else if (i < sizeof(comando) - 1) { // Verifica se há espaço no buffer
            comando[i++] = c; // Armazena o caractere no buffer
            putchar(c); // Imprime o caractere na mesma linha
        }
    }

    return 0;
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
    if (strlen(comando) == 0) {
        printf("Comando vazio. Digite algo.\n");
        return;
    }

    switch (toupper(comando[0])) {
        case 'R':
            if (strcasecmp(comando, "RED") == 0) {
                printf("Ligando LED VERMELHO\n");
                desligar_todos_leds();
                ligar_led(LED_VERMELHO);
            } else {
                printf("Comando inválido: %s\n", comando);
            }
            break;

        case 'G':
            if (strcasecmp(comando, "GREEN") == 0) {
                printf("Ligando LED VERDE\n");
                desligar_todos_leds();
                ligar_led(LED_VERDE);
            } else {
                printf("Comando inválido: %s\n", comando);
            }
            break;

        case 'B':
            if (strcasecmp(comando, "BLUE") == 0) {
                printf("Ligando LED AZUL\n");
                desligar_todos_leds();
                ligar_led(LED_AZUL);
            } else if (strcasecmp(comando, "BUZZ") == 0) {
                printf("Ativando o BUZZER\n");
                ativar_buzzer(1000);
            } else {
                printf("Comando inválido: %s\n", comando);
            }
            break;

        case 'W':
            if (strcasecmp(comando, "WHITE") == 0) {
                printf("Ligando TODOS os LEDs (luz branca)\n");
                gpio_put(LED_VERMELHO, 1);
                gpio_put(LED_VERDE, 1);
                gpio_put(LED_AZUL, 1);
            } else {
                printf("Comando inválido: %s\n", comando);
            }
            break;

        case 'O':
            if (strcasecmp(comando, "OFF") == 0) {
                printf("Desligando TODOS os LEDs\n");
                desligar_todos_leds();
            } else {
                printf("Comando inválido: %s\n", comando);
            }
            break;

        default:
            printf("Comando desconhecido: %s\n", comando);
            break;
    }
}