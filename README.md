# Placa LoRaWAN - repositório oficial

Este é o repositório oficial da placa LoRaWAN, placa de desenvolvimento para protótipos em Internet das Coisas com LoRaWAN, Bluetooth (CLE e clássico) e WiFi, fazendo uso do módulo Heltec wifi LoRa V1.

Este projeto é totalmente open-source (licença: MIT).

## Princípio de funcionamento

Essa placa tem objetivo de facilitar o desenvolvimento de protótipos em Internet das Coisas. A melhor forma encontrada para facilitar isso, foi disponibilizar conexões / soquetes para módulo de controle (Heltec wifi LoRa V1) e módulos sensores, conforme a seguir:

* Módulo MPU6050
* Módulo BMP180
* Módulo INA219
* Módulo MQ-2

Para comunicação com módulos (exemplo: GPS) e microcontroladores externos, a placa conta ainda com uma interface UART (níveis 3V3 e 5V, selecionável por jumper / ponte soldada na placa) e uma interface I²C (nível 3V3).

Além disso, essa placa permite o uso do módulo de controle Heltec wifi LoRa V1 com bateria (LiPo ou Li-Ion, de 1 célula), permitindo tamem a recarga e medição da tensão da mesma.

Isso significa que mesmo que você possua pouca experiência com eletrônica e soldagem, conseguirá facilmente montar e utilizar a placa.

## Funcionalidades

Esta placa, usada juntamente com um módulo Heltec wifi LoRa V1 e os sensores que a placa suporta, compreende as seguintes funcionaliades:
 
* Conectividades wifi, Bluetooth (BLE e clássico), LoRa e LoRaWAN.
* Medição de temperatura
* Medição de pressão barométrica
* Medição de aceleração (3 eixos)
* Giroscópio (3 eixos)
* Tensão e corrente DC
* Detecção de gases inflamávei e fumaça
* Display OLED 0.96" (azul)

Além disso, a placa possui conector para alimentação através de energias renováveis (solar, eólica ou hidráulica), com tensão de alimentação de até 15V.

## O que está disponivel neste repositório?

Resposta curta: 100% do projeto. Ou seja:

* Projeto completo de hardware (feito no KiCad 5.1.5)
* Arquivos gerber, já nos padrões para fabricação exigidos pela JLCPCB (www.jlcpcb.com)
* Softwares de exemplo (todos feitos na Arduino IDE, fazendo uso de bibliotecas populares e consagradas)
* Lista de materiais (BOM)
* Bibliotecas e footprints KiCad (para transistor FQP30N06L e Heltec wifi LoRa V1, sendo este último desenhado por mim).

## Desejo contribuir com novas funcionalidades ou correções. Sou bem vindo?

Claro. Sinta-se a vontade para contribuir com o projeto. Toda melhoria é bem vinda!

## Gostei do seu trabalho. Onde consigo mais coisas publicadas por você?

Visite meu [site pessoal](http://www.pedrobertoleti.com.br) para ter acesso a quase tudo que publico no Brasil e exterior.
