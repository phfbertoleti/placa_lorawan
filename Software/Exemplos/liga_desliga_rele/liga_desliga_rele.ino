/* Programa: liga / desliga relé da placa lorawan
 * Descrição: lliga / desliga relé da placa lorawan, fazendo 
 *            uso do OLED para exibição de informações textuais.
 * Autor: Pedro Bertoleti
 * 
 * Este programa faz uso das bibliotecas de display OLED (SSD1306) da Adafruit:
 * - https://github.com/adafruit/Adafruit_SSD1306
 * - https://github.com/adafruit/Adafruit-GFX-Library
 */

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

/* Definições - OLED */
#define OLED_CLEAR_LINE      "                     "
#define OLED_LINE_MAX_SIZE   21
#define OLED_SDA_PIN         4
#define OLED_SCL_PIN         15
#define OLED_ADDRESS         0x3C
#define OLED_RESET           16 
#define OLED_SCREEN_HEIGHT   64
#define OLED_SCREEN_WIDTH    128
#define OLED_LINHA_1         0
#define OLED_LINHA_2         10
#define OLED_LINHA_3         20
#define OLED_LINHA_4         30
#define OLED_LINHA_5         40
#define OLED_LINHA_6         50

/* Definição - GPIO do LED */
#define GPIO_LED   23

/* Definição - GPIO do rele */
#define GPIO_RELE   17

/* Variaveis globais */
char linha_str[OLED_LINE_MAX_SIZE];
Adafruit_SSD1306 display(OLED_SCREEN_WIDTH, 
                         OLED_SCREEN_HEIGHT, 
                         &Wire, 
                         OLED_RESET, 
                         100000UL, 
                         100000UL);
/*
 * Implementações
 */


void setup() 
{
    Serial.begin(115200);

    /* Configuração do LED */
    pinMode(GPIO_LED, OUTPUT);
    digitalWrite(GPIO_LED, LOW);

    /* Configuração do GPIO de controle do relé */
    pinMode(GPIO_RELE, OUTPUT);
    digitalWrite(GPIO_RELE, LOW);
        
    /* Inicializa I²C (para comunicação com OLED)*/
    Wire.begin(OLED_SDA_PIN, OLED_SCL_PIN);

    /* Inicializa display */
    if(!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) 
    { 
        Serial.println("[ERRO] não foi possivel inicializar display. O NodeMCU será reiniciado em 1s...");
        delay(1000);
        ESP.restart();
    }
    else
    {
        Serial.println("Display inicializado.");
        display.clearDisplay();
        display.setTextColor(WHITE);
        display.setTextSize(1);
        display.setCursor(0,OLED_LINHA_1);
        display.println("   Kit wifi Heltec");
        display.setCursor(0,OLED_LINHA_2);
        display.println("        LoRa V1");
        display.setCursor(0,OLED_LINHA_3);
        display.println("_____________________");
        display.setCursor(0,OLED_LINHA_5);
        display.println("Pedro Bertoleti");
        display.setCursor(0,OLED_LINHA_6);
        display.println("pedrobertoleti.com.br");
        display.display();
        delay(500);
    }
}

void loop() 
{
    /* Aciona relé da placa */
    digitalWrite(GPIO_RELE, HIGH);
    
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setCursor(0,OLED_LINHA_1);
    display.println("   Kit wifi Heltec");
    display.setCursor(0,OLED_LINHA_2);
    display.println("        LoRa V1");
    display.setCursor(0,OLED_LINHA_3);
    display.println("_____________________");
    display.setCursor(0,OLED_LINHA_5);
    display.println("Rele ligado");
    display.display();

    /* Liga LED da placa */
    digitalWrite(GPIO_LED, HIGH);

    delay(1000);

    /* Desliga relé da placa */
    digitalWrite(GPIO_RELE, LOW);
    
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setCursor(0,OLED_LINHA_1);
    display.println("   Kit wifi Heltec");
    display.setCursor(0,OLED_LINHA_2);
    display.println("        LoRa V1");
    display.setCursor(0,OLED_LINHA_3);
    display.println("_____________________");
    display.setCursor(0,OLED_LINHA_5);
    display.println("Rele desligado");
    display.display();

    /* Desliga LED da placa */
    digitalWrite(GPIO_LED, LOW);

    delay(1000);
}