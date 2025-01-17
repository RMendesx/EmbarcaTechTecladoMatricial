#include <stdio.h>
#include "pico/stdlib.h"

#define gpio_led_red 18
#define gpio_led_green 19
#define gpio_led_blue 20
#define gpio_buzzer 21

//definição das colunas e das linhas e mapeamento do teclado
int coluna[4] = {4, 3, 2, 1}; 
int linha[4] = {8, 7, 6, 5};
char teclas[4][4] = {
    '1', '2' , '3', 'A',
    '4', '5' , '6', 'B',
    '7', '8' , '9', 'C',
    '*', '0' , '#', 'D'
};

//Função para ativar e desligar leds
void piscar_led(uint gpio_led){   //Função que faz o led piscar com base no GPIO passado
    gpio_put(gpio_led, true);            //Ligar o led
    sleep_ms(2000);                      //Tempo de espera em milissegundos
    gpio_put(gpio_led, false);           //Desligar o led
}
//função de inicializar o teclado
void inicializar_teclado(uint8_t *colunas, uint8_t *linhas){
  //aguardando código
}

//função de leitura do teclado
char ler_teclado(uint8_t *colunas, uint8_t *linhas) {
  for (int i = 0; i < 4; i++) {
    gpio_put(linhas[i], 0);
    uint8_t result = 0;
    for (int j = 0; j < 4; j++){
      result |= gpio_get(colunas[j]);
    }
    if (result == 0) {
      char key = teclas[i][__builtin_ctz(result)];
      gpio_put(linhas[i], 1);
      return key;
    }
    gpio_put(linhas[i], 1);
  }
  return 0;
}

int main() {
    stdio_init_all();
    gpio_init(gpio_led_red);
    gpio_init(gpio_led_green);
    gpio_init(gpio_led_blue);
    gpio_init(gpio_buzzer);
    gpio_set_dir(gpio_led_red, GPIO_OUT);
    gpio_set_dir(gpio_led_green, GPIO_OUT);
    gpio_set_dir(gpio_led_blue, GPIO_OUT);
    gpio_set_dir(gpio_buzzer, GPIO_OUT);

    while (true) {

        char tecla_pressionada = ler_teclado(coluna, linha);  //Atribui a variável a tecla pressionada ao chamar a função
        printf("Tecla pressionada: %c\n", tecla_pressionada);
        
        switch(tecla_pressionada){ // Analisa a tecla pressionada e executa a ação definido a ela
            case 'A':
            piscar_led(gpio_led_blue);   //Verifica se a tecla A foi pressionada
            break;
            case 'B':                    //Verifica se a tecla B foi pressionada
            piscar_led(gpio_led_red);    //Chama a funcao piscar_periferico
            break;

            default:   
            printf("Tecla não configurada");
        }
      sleep_ms(100); // Delay para evitar leitura repetida 
      }
}
