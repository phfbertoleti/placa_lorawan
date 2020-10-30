/* Programa: leitura do sensor corrente e tensão INA219
 * Descrição: leitura do sensor corrente e tensão INA219, fazendo uso do OLED para exibição de 
 *            informações textuais
 * Autor: Pedro Bertoleti
 * 
 * Este programa faz uso das bibliotecas de display OLED (SSD1306) da Adafruit:
 * - https://github.com/adafruit/Adafruit_SSD1306
 * - https://github.com/adafruit/Adafruit-GFX-Library
 * 
 * Além disso, esse programa faz uso da biblioteca do sensor BMP180 da Adafruit:
 * - https://github.com/adafruit/Adafruit_INA219
 */

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_INA219.h> 

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

/* Definição - endereço I²C do INA219 */
#define INA219_I2C_ADDR    0x40

/* Variaveis globais */
char linha_str[OLED_LINE_MAX_SIZE];
int estado_led;
Adafruit_INA219 ina219(INA219_I2C_ADDR);
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
    pinMode(GPIO_LED, OUTPUT);
    estado_led = HIGH;
    digitalWrite(GPIO_LED, estado_led);
        
    /* Inicializa I²C (para comunicação com OLED e BMP180)*/
    Wire.begin(OLED_SDA_PIN, OLED_SCL_PIN);

    /* Inicializa INA219 */
    ina219.begin();

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
    float tensao_V, corrente_mA;

    tensao_V = ina219.getBusVoltage_V();
    corrente_mA = ina219.getCurrent_mA();
    
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setCursor(0,OLED_LINHA_1);
    display.println("     Dados - INA219");
    display.setCursor(0,OLED_LINHA_2);
    display.println("_____________________");
    display.setTextSize(1);
    display.setCursor(0,OLED_LINHA_3);
    sprintf(linha_str,"V: %.3fV", tensao_V); 
    display.println(linha_str);
    display.setCursor(0,OLED_LINHA_5);
    sprintf(linha_str,"T: %.3fmA", corrente_mA); 
    display.println(linha_str);
    display.display();

    /* Pisca LED da placa */
    if (estado_led == LOW)
        estado_led = HIGH;
    else
        estado_led = LOW;
           
    digitalWrite(GPIO_LED, estado_led);

    /* Aguarda 1 segundo para próxima leitura */
    delay(1000);
}