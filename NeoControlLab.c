#include <stdio.h>                         // Biblioteca padrão para entrada e saída (ex: printf)
#include "pico/stdlib.h"                   // Inicialização padrão da Raspberry Pi Pico
#include "hardware/gpio.h"                 // Controle dos pinos GPIO
#include "hardware/irq.h"                  // Controle de interrupções
#include "neopixel_driver.h"               // Biblioteca para controlar os LEDs NeoPixel
#include "testes_cores.h"                  // Biblioteca auxiliar com funções de cores (personalizadas)
#include "efeitos.h"                       // Biblioteca auxiliar com efeitos visuais
#include "efeito_curva_ar.h"              // Biblioteca com efeito específico para curva de ar
#include "numeros_neopixel.h"             // Funções para desenhar números na matriz NeoPixel
#include <stdlib.h>                        // Biblioteca para números aleatórios
#include "pico/time.h"                     // Biblioteca de tempo (ex: time_us_32)

#define BOTAO_A 5                          // Define o pino GPIO 5 como o botão A

// Variável global que indica se o botão foi pressionado
// É "volatile" porque pode ser alterada pela interrupção
volatile bool botao_pressionado = false;

// === FUNÇÃO DE INTERRUPÇÃO ===
// Essa função é chamada automaticamente quando o botão é pressionado
void gpio_callback(uint gpio, uint32_t events) {
    if (gpio == BOTAO_A && (events & GPIO_IRQ_EDGE_FALL)) {
        botao_pressionado = true;  // Marca que o botão foi pressionado
    }
}

// === SORTEIO ENTRE DOIS VALORES ===
// Retorna um número aleatório entre min e max (inclusive)
int sorteia_entre(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// === MOSTRA NÚMERO SORTEADO NA MATRIZ ===
// Limpa a matriz e chama a função correta conforme o número sorteado
void mostrar_numero_sorteado(int numero) {
    npClear();  // Apaga todos os LEDs da matriz

    switch (numero) {
        case 1: mostrar_numero_1(); break;
        case 2: mostrar_numero_2(); break;
        case 3: mostrar_numero_3(); break;
        case 4: mostrar_numero_4(); break;
        case 5: mostrar_numero_5(); break;
        case 6: mostrar_numero_6(); break;
    }
}

// === CONFIGURAÇÃO DO BOTÃO A ===
// Define o botão como entrada com pull-up e ativa a interrupção
void configurar_botao() {
    gpio_init(BOTAO_A);  // Inicializa o pino como GPIO
    gpio_set_dir(BOTAO_A, GPIO_IN);  // Define como entrada
    gpio_pull_up(BOTAO_A);  // Ativa resistor de pull-up interno
    gpio_set_irq_enabled_with_callback(BOTAO_A, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);
    // Habilita interrupção na borda de descida (quando o botão é pressionado)
}

// === FUNÇÃO PRINCIPAL ===
int main() {
    stdio_init_all();               // Inicializa o sistema de entrada e saída padrão (USB serial)
    sleep_ms(1000);                 // Aguarda 1 segundo (tempo para conectar a porta serial)

    npInit(LED_PIN);                // Inicializa a matriz/fita NeoPixel

    // Acende todos os LEDs em vermelho para indicar inicialização
    npSetAll(100, 0, 0);            // Define a cor vermelha
    npWrite();                      // Atualiza os LEDs
    sleep_ms(500);                  // Aguarda 0,5 segundo

    npClear();                      // Limpa os LEDs
    npWrite();                      // Atualiza a fita para desligar

    srand(time_us_32());            // Inicializa a semente do número aleatório com tempo atual

    configurar_botao();             // Configura o botão com interrupção

    printf("Sistema pronto. Aguardando botão A (GPIO 5)...\n");

    // LOOP INFINITO
    while (true) {
        if (botao_pressionado) {     // Verifica se houve clique
            botao_pressionado = false;  // Reseta o estado do botão

            printf("Botão A pressionado! Sorteando...\n");

            int vezes = sorteia_entre(10, 30);  // Decide quantas vezes vai sortear

            // Sorteia e mostra números aleatórios por um tempo
            for (int i = 0; i < vezes; i++) {
                int n = sorteia_entre(1, 6);  // Sorteia um número entre 1 e 6
                printf("Número sorteado: %d\n", n);
                mostrar_numero_sorteado(n);  // Mostra o número na matriz
                sleep_ms(300);               // Aguarda 300ms entre cada número
            }

            printf("Aguardando nova pressão do botão...\n");
        }

        sleep_ms(10);  // Pequena espera para evitar uso excessivo da CPU
    }
}



