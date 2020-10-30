/* Programa: pisca-led da placa lorawan
 * Descrição: pisca o led da placa lorawan (1 segundo on, 1 segundo off)
 * Autor: Pedro Bertoleti
 */
#define GPIO_LED   23

void setup() 
{
    pinMode(GPIO_LED, OUTPUT);
    Serial.begin(115200);
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
