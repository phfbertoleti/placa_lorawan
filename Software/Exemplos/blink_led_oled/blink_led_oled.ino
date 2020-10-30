/* Programa: pisca-led da placa lorawan e uso do OLED
 * Descrição: pisca o led da placa lorawan (1 segundo on, 1 segundo off), fazendo uso do
 *            OLED para exibição de informações textuais
 * Autor: Pedro Bertoleti
 * 
 * Este programa faz uso das bibliotecas de display OLED (SSD1306) da Adafruit:
 * - https://github.com/adafruit/Adafruit_SSD1306
 * - https://github.com/adafruit/Adafruit-GFX-Library
 */

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

/* Definição - GPIO do LED */
#define GPIO_LED   23

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

/* Variveis globais */
Adafruit_SSD1306 display(OLED_SCREEN_WIDTH, 
                         OLED_SCREEN_HEIGHT, 
                         &Wire, 
                         OLED_RESET, 
                         100000UL, 
                         100000UL);

void setup() 
{
    pinMode(GPIO_LED, OUTPUT);
    Serial.begin(115200);

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
    }
}

void loop() 
{
    Serial.println("Led aceso");
    digitalWrite(GPIO_LED, HIGH);  
    delay(1000);                   

    Serial.println("Led apagado");
    digitalWrite(GPIO_LED, LOW);   
    delay(1000);                   
}
