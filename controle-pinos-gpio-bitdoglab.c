#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "pico/bootrom.h" //biblioteca para reboot do raspberry - Matheus

// Definição dos pinos dos LEDs e do buzzer
#define LED_VERMELHO 13
#define LED_AZUL 12
#define LED_VERDE 11
#define PINO_BUZZER 21

// Variáveis globais
const char senha_padrao[] = "1234"; // Senha padrão
char senha_digitada[10];           // Buffer para armazenar a senha digitada
int senha_index = 0;               // Índice do buffer de senha
bool modo_senha = false;           // Flag para indicar o modo de senha
bool senha_valida = false;         // Flag para indicar a senha correta
// Funções auxiliares
void iniciar_pinos();
void desligar_todos_leds();
void ligar_led(uint pin);
void ativar_buzzer(int duration);
void tocar_nota(uint frequency, uint duration);
void tocar_musica_acerto();
void tocar_musica_erro();
void processar_comando(const char *comando);
bool verificar_senha();
void exibir_menu();

int main() {
    iniciar_pinos(); // Inicializa os pinos dos LEDs e do buzzer
    stdio_init_all(); // Inicializa o sistema de entrada/saída padrão
    sleep_ms(500); // Pequeno atraso para estabilização

    // Define o buffer de saída como não bufferizado
    setvbuf(stdout, NULL, _IONBF, 0);

    getchar();
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
    printf("*     - Entra no modo de senha\n");
    printf("F     - Entra no modo BOOTSEL\n");
    printf("============================\n");
}

// Inicializa os pinos dos LEDs e do buzzer

void iniciar_pinos() {
    gpio_init(LED_VERMELHO);
    gpio_init(LED_VERDE);
    gpio_init(LED_AZUL);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    gpio_set_dir(LED_VERDE, GPIO_OUT);
    gpio_set_dir(LED_AZUL, GPIO_OUT);

    gpio_set_function(PINO_BUZZER, GPIO_FUNC_PWM); // Configura o pino do buzzer como saída PWM
    uint slice_num = pwm_gpio_to_slice_num(PINO_BUZZER);
    pwm_config config = pwm_get_default_config();
    pwm_init(slice_num, &config, true); // Inicializa o PWM

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
    uint frequency = 440; // Frequência padrão para o buzzer (nota A4)
    uint slice_num = pwm_gpio_to_slice_num(PINO_BUZZER);
    uint32_t top = 125000000 / frequency; // Calcula o valor do PWM para a frequência desejada
    pwm_set_wrap(slice_num, top);
    pwm_set_gpio_level(PINO_BUZZER, top / 2); // Define 50% de duty cycle
    sleep_ms(duration); // Duração do som
    pwm_set_gpio_level(PINO_BUZZER, 0); // Desliga o buzzer
}


void tocar_nota(uint frequency, uint duration) {
    uint slice_num = pwm_gpio_to_slice_num(PINO_BUZZER);
    uint32_t top = 125000000 / frequency; // Calcula o valor do PWM para a frequência desejada
    pwm_set_wrap(slice_num, top);
    pwm_set_gpio_level(PINO_BUZZER, top / 2); // Define 50% de duty cycle
    sleep_ms(duration); // Aguarda o tempo da nota
    pwm_set_gpio_level(PINO_BUZZER, 0); // Desliga o buzzer
    sleep_ms(50); // Pequena pausa entre as notas
}

// Toca a música de acerto
void tocar_musica_acerto() {
    tocar_nota(659, 300); // E5
    tocar_nota(784, 300); // G5
    tocar_nota(988, 300); // B5
    tocar_nota(1047, 400); // C6
}

// Toca a música de erro
void tocar_musica_erro() {
    tocar_nota(200, 300); // Nota grave
    tocar_nota(150, 300); // Nota mais grave
    tocar_nota(100, 400); // Nota ainda mais grave
}

// Verifica a senha digitada
bool verificar_senha() {
    if (strcmp(senha_digitada, senha_padrao) == 0) {
        printf("\nSenha correta! Acesso permitido.\n");
        desligar_todos_leds();
        ligar_led(LED_VERDE);
        tocar_musica_acerto();
        return true;
    } else {
        printf("\nSenha incorreta! Acesso negado.\n");
        desligar_todos_leds();
        ligar_led(LED_VERMELHO);
        tocar_musica_erro();
        return false;
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
        case 'F': //reboot do raspberry - Matheus
            if (strcasecmp(comando, "F") == 0) {
                printf("Entrando no modo BOOTSEL...\n");
                sleep_ms(500);
                reset_usb_boot(0, 0);
            }
            else{
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

        case '*':
            if (strcasecmp(comando, "*") == 0) {
                printf("Entrando no modo de senha\n");
                printf("Digite a senha ou pressione '#' para sair: ");
                while (!modo_senha)
                {
                    char c = getchar();
                    if (c == '\n' || c == '\r') {
                        senha_digitada[senha_index] = '\0';
                        modo_senha= verificar_senha();
                        senha_index = 0;
                        printf("Digite a senha ou pressione '#' para sair: ");
                    } else if (c == '#') {
                        break;
                    } else if (c == 127) {
                        if (senha_index > 0) {
                            senha_index--;
                            printf("\b \b");
                        }
                    } else if (senha_index < sizeof(senha_digitada) - 1) {
                        senha_digitada[senha_index] = c;
                        senha_index++;
                        putchar(c);
                    }
                }
                
            } else {
                printf("Comando inválido: %s\n", comando);
            }
            break;

        default:
            printf("Comando desconhecido: %s\n", comando);
            break;
    }
}