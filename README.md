# NeoControlLab — EmbarcaTech

Atividade de sistemas embarcados em **C** para Raspberry Pi Pico W, com uso de matriz de LEDs NeoPixel.

## Objetivo e comportamento observado

No arquivo `NeoControlLab.c`, o programa configura uma interrupção para o botão A (GPIO 5), sorteia números de 1 a 6 e usa funções auxiliares para apresentar os números na matriz NeoPixel. O código também inclui efeitos visuais e testes de cores.

## Tecnologias
C, Raspberry Pi Pico SDK, CMake, GPIO, interrupções e NeoPixel.

## Arquivos principais

- `NeoControlLab.c`: lógica principal e tratamento do botão.
- `numeros_neopixel.c/.h`: funções de apresentação dos números.
- `testes_cores.c/.h`: rotinas relacionadas a cores.
- `efeito_curva_ar.c/.h`: efeito visual.
- `CMakeLists.txt`: configuração de compilação do alvo `NeoControlLab`.

## Compilação — estado da auditoria

O `CMakeLists.txt` utiliza o Pico SDK e faz referência a arquivos no diretório `LabNeoPixel/`, **que não consta na listagem da raiz do repositório**. Portanto, não foi possível validar a compilação. Antes de executar com CMake e SDK instalados, obtenha as dependências e confira os caminhos previstos.

Nenhum código ou arquivo original foi modificado por esta documentação.

## Melhorias futuras

Completar as dependências referenciadas, documentar pinagem e hardware utilizado e registrar evidências de execução.

**Contexto:** atividade acadêmica EmbarcaTech.
