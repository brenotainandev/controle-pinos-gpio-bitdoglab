# Controle de Pinos GPIO com Microcontrolador RP2040

## Descrição do Projeto
Este projeto utiliza o microcontrolador RP2040 para controlar LEDs RGB e um buzzer por meio da porta UART. Ele foi desenvolvido para ser executado na ferramenta educacional **BitDogLab** e permite a interação com os periféricos conectados usando comandos enviados pelo terminal.

As funcionalidades incluem ligar LEDs (vermelho, verde, azul ou todos simultaneamente), desligar os LEDs, acionar o buzzer com duração específica e entrar em modo de senha ou modo de boot.

## Demonstração
- Vídeo: [YouTube](https://www.youtube.com/shorts/_KuICMaZcZk)

## Equipe

- **Líder do Projeto**: João Vitor de Siqueira Santana Costa
- **Desenvolvedores**:
  - Matheus Pereira Alves
  - Rodrigo Damasceno Sampaio
  - Erick Barros Ferreira Gomes
  - João Vitor de Siqueira Santana Costa
  - Natália Freitas Tolentino
  - Eduarda da Silva Santos
  - Breno Tainan Aguiar

## Requisitos de Hardware

- Ferramenta educacional **BitDogLab**.
- Cabo USB (micro-USB para USB-A).
- Microcontrolador RP2040.
- LEDs RGB (conectados aos GPIOs 11, 12 e 13).
- Buzzer (conectado ao GPIO 21).

## Requisitos de Software

- **VS Code** com extensão de suporte para RP2040.
- **Pico SDK** (instalado e configurado).
- Simulador **Wokwi** (opcional para simulação do circuito).
- **PuTTY** ou outro emulador de terminal UART.

## Estrutura do Projeto

```
controle-pinos-gpio-bitdoglab/
├── controle-pinos-gpio-bitdoglab.c   # Código fonte principal
├── CMakeLists.txt                    # Configuração do CMake
├── diagram.json                      # Diagrama do circuito no Wokwi
├── pico_sdk_import.cmake             # Importação do Pico SDK
├── README.md                         # Documentação do projeto
└── wokwi.toml                        # Configuração para o Wokwi
```

## Funcionalidades

1. **Controle dos LEDs**:
   - `RED`: Liga o LED vermelho (GPIO 13).
   - `GREEN`: Liga o LED verde (GPIO 11).
   - `BLUE`: Liga o LED azul (GPIO 12).
   - `WHITE`: Liga todos os LEDs (luz branca).
   - `OFF`: Desliga todos os LEDs.

2. **Controle do Buzzer**:
   - `BUZZ`: Ativa o buzzer por 1 segundo (GPIO 21).

3. **Modo de Senha**:
   - `*`: Ativa o modo de senha.
   - Digite a senha `1234` para acerto (música de sucesso) ou digite uma senha errada para ouvir a música de erro.

4. **Modo BOOTSEL**:
   - `F`: Reinicia o microcontrolador e entra no modo BOOTSEL.

## Como Usar

### 1. Conectar o Microcontrolador

- Certifique-se de que os periféricos (LEDs e buzzer) estão corretamente conectados ao RP2040 conforme descrito abaixo:
  - LED verde: GPIO 11
  - LED azul: GPIO 12
  - LED vermelho: GPIO 13
  - Buzzer: GPIO 21

### 2. Compilar o Projeto

1. Clone o repositório:
   ```bash
   git clone https://github.com/brenotainandev/controle-pinos-gpio-bitdoglab.git
   cd controle-pinos-gpio-bitdoglab
   ```
2. Crie uma pasta de build e compile:
   ```bash
   mkdir build && cd build
   cmake ..
   make
   ```
3. Envie o binário para o RP2040:
   - Coloque o RP2040 em modo BOOTSEL (pressione o botão BOOTSEL enquanto conecta o cabo USB).
   - Copie o arquivo `.uf2` gerado para o dispositivo detectado.

### 3. Executar

- Abra o emulador de terminal UART (como PuTTY) com as seguintes configurações:
  - Baud rate: `115200`

- Interaja com o sistema digitando comandos no terminal conforme o menu exibido:

```
=== MENU ===
RED   - Liga o LED vermelho
GREEN - Liga o LED verde
BLUE  - Liga o LED azul
WHITE - Liga todos os LEDs (luz branca)
OFF   - Desliga todos os LEDs
BUZZ  - Ativa o buzzer
*     - Entra no modo de senha
F     - Entra no modo BOOTSEL
============================
```

## Exemplo de Execução

1. Ao iniciar o sistema, o menu é exibido:
   ```
   === MENU ===
   RED   - Liga o LED vermelho
   GREEN - Liga o LED verde
   BLUE  - Liga o LED azul
   WHITE - Liga todos os LEDs (luz branca)
   OFF   - Desliga todos os LEDs
   BUZZ  - Ativa o buzzer
   *     - Entra no modo de senha
   F     - Entra no modo BOOTSEL
   ============================
   Digite um comando:
   ```

2. Digite `RED` e veja o LED vermelho acender.
3. Digite `*`, insira a senha `1234` e veja o comportamento correspondente.
4. Digite `F` para entrar no modo BOOTSEL.