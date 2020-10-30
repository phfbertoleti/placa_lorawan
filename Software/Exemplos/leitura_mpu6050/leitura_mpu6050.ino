/* Programa: leitura da IMU MPU6050 (acelerômetro de 3 eixos, giroscópio de 3 eixos e 
             temperatura)
 * Descrição: leitura da IMU MPU6050, fazendo uso do OLED para exibição de informações 
 *            textuais
 * Autor: Pedro Bertoleti
 * 
 * Este programa faz uso das bibliotecas de display OLED (SSD1306) da Adafruit:
 * - https://github.com/adafruit/Adafruit_SSD1306
 * - https://github.com/adafruit/Adafruit-GFX-Library
 * 
 * Além disso, este programa faz uso das seguintes bibliotecas para o uso do
 * IMU MPU6050:
 * - https://github.com/adafruit/Adafruit_MPU6050
 * - https://github.com/adafruit/Adafruit_Sensor
 */

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

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

/* Definição - aceleração da gravidade */
#define VALOR_GRAVIDADE    9.80665  // m/s²

/* Variaveis globais */
char linha_str[OLED_LINE_MAX_SIZE];
int estado_led;
Adafruit_MPU6050 mpu;
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
        
    /* Inicializa I²C (para comunicação com OLED e MPU6050)*/
    Wire.begin(OLED_SDA_PIN, OLED_SCL_PIN);

    /* Inicializa MPU6050 */
    if (!mpu.begin()) 
    {
        Serial.println("ERRO: falha ao inicializar MPU6050. O ESP32 reiniciará em 1s...");
        delay(1000);
        ESP.restart();
    }
    else
    {
        /* Configura MPU6050:
           - Acelerômetro: +-2G
           - Giroscópio: +-500 graus/segundo
           - FrequÊncia de corte do filtro DLPF: 5Hz
        */
        mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
        mpu.setGyroRange(MPU6050_RANGE_500_DEG);
        mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
    }

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
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
   
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setCursor(0,OLED_LINHA_1);
    display.println("     Dados - MPU6050");
    display.setCursor(0,OLED_LINHA_2);
    display.println("_____________________");
    display.setTextSize(1);
    display.setCursor(0,OLED_LINHA_3);
    sprintf(linha_str,"A: %.1f, %.1f, %.1f g", a.acceleration.x/VALOR_GRAVIDADE,
                                               a.acceleration.y/VALOR_GRAVIDADE,
                                               a.acceleration.z/VALOR_GRAVIDADE); 
    display.println(linha_str);
    display.setCursor(0,OLED_LINHA_4);
    sprintf(linha_str,"G: %.0f, %.0f, %.0f", g.gyro.x,
                                             g.gyro.y,
                                             g.gyro.z); 
    display.println(linha_str);

    display.setCursor(0,OLED_LINHA_5);
    display.println("rad/s");

    display.setCursor(0,OLED_LINHA_6);
    sprintf(linha_str,"Temp: %.1fC", temp.temperature); 
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