# Controle Remoto de Lâmpada via Wi-Fi utilizando Arduino e MQTT
Este repositório contém o código-fonte necessário para controlar uma lâmpada remotamente através de uma conexão Wi-Fi utilizando o protocolo MQTT. O projeto utiliza a placa ESP8266, que possui Wi-Fi integrado, em vez do Arduino UNO.

## Componentes utilizados
* Placa ESP8266
* Módulo relé (Certifique-se de que este seja compatível com a placa que será usada, visto que o ESP8266 possui uma saída de 3V e não de 5V como no Arduino.
* Lâmpada

## Bibliotecas
O código utiliza as seguintes bibliotecas:
* ESP8266WiFi.h: Biblioteca para conectar-se à rede Wi-Fi.
* PubSubClient.h: Biblioteca para comunicação MQTT.

## Configurações
Antes de utilizar o código, é necessário ajustar as seguintes configurações:

### Credenciais Wi-Fi
~~~.ino
const char* ssid = "SEU_SSID"; // Insira o nome da sua rede Wi-Fi
const char* password = "SUA_SENHA"; // Insira a senha da sua rede Wi-Fi
~~~

### Credenciais do MQTT Broker e tópicos
~~~.ino
const char* mqtt_broker = "broker.hivemq.com"; // Endereço do broker MQTT
const char* topic1 = "led/builtin/L1"; // Tópico para controlar o LED 1
const char* topic2 = "led/builtin/L2"; // Tópico para controlar o LED 2
const char* topic3 = "led/builtin/ALL"; // Tópico para controlar todos os LEDs
const char* mqtt_username = ""; // Nome de usuário MQTT (caso necessário)
const char* mqtt_password = ""; // Senha MQTT (caso necessário)
~~~

Certifique-se de ajustar as credenciais de acordo com a sua configuração específica.

## Funcionamento 
1. O código conecta-se à rede Wi-Fi configurada.
2. Após a conexão Wi-Fi ser estabelecida, o código tenta conectar-se ao broker MQTT.
3. Uma vez conectado ao broker MQTT, o código subscreve aos tópicos relevantes e publica uma mensagem de confirmação para cada um deles.
4. O código aguarda a recepção de mensagens MQTT nos tópicos subscritos.
5. Quando uma mensagem é recebida, o código executa a função de callback, que controla o estado dos LEDs com base na mensagem recebida.

## Controle dos LEDs
* Tópico "led/builtin/L1": Controla o LED 1 individualmente.
* Tópico "led/builtin/L2": Controla o LED 2 individualmente.
* Tópico "led/builtin/ALL": Controla ambos os LEDs simultaneamente

As mensagens válidas para acender os LEDs são:

* "1": Liga o LED.
* "0": Desliga o LED.

## Importante 
Certifique-se de ter configurado corretamente as conexões físicas entre a placa ESP8266, o módulo relé e a lâmpada. O código assume que o pino D0 da placa está conectado ao módulo relé que controla o LED 1, e o pino D3 está conectado ao módulo relé que controla o LED 2.

_Este código foi desenvolvido para fins educacionais e pode ser modificado de acordo com as necessidades do projeto. Logo, para não se utilizar uma alta voltagem foi-se utilizado três LEDs controlados individualmente, como apresentado no código._
