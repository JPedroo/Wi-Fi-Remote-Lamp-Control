#include <ESP8266WiFi.h> // Inclui a biblioteca Wi-Fi
#include <PubSubClient.h> // Inclui a biblioteca MQTT

// Credenciais para se conectar ao Wi-fi
const char* ssid = ".";
const char* password = "nopass123";

// Credenciais do MQTT broker e topics
const char* mqtt_broker = "broker.hivemq.com";
const char* topic1 = "led/builtin/L1"; //Tópico LED 1
const char* topic2 = "led/builtin/L2"; //Tópico LED 2
const char* topic3 = "led/builtin/ALL"; //Tópico para acender todos os leds
const char* mqtt_username= "";
const char* mqtt_password = ""; //Usuário e senha vazios pois o broker utilizado é público

//Variável boobleana para indicar se o ESP se conectou ao broker
bool mqttStatus = 0;

WiFiClient espClient; // Cria um cliente Wifi
PubSubClient client(espClient); // Cria um cliente MQTT

//Protótipos
bool connectMQTT();
void callback(char *topic, byte *payload, unsigned int length);


void setup() {
  Serial.begin(9600); // Inicializa a Serial

  pinMode(D0, OUTPUT); // Configura o Led1 como saída na porta D0
  pinMode(D3, OUTPUT); // Configura o Led2 como saída na porta D3

  digitalWrite(D0, LOW); // Força a inicialização do programa com o LED1 desligado
  digitalWrite(D3, LOW); // Força a inicialização do programa com o LED1 desligado


  WiFi.begin(ssid, password); // Conectar a rede Wi-fi
  while (WiFi.status() != WL_CONNECTED) { // While que confere se o ESP se conectou ao wi-fi
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected"); // Conectado com sucesso na rede wi-fi

  //Printa na serial o IP da rede conectada
  Serial.println(WiFi.localIP());

  mqttStatus = connectMQTT(); //Chama a função para se conectar ao MQTT e armazena o retorno da mesma
}

void loop() {
  if (mqttStatus) { //caso mqttStatus tiver valor armazenado
    client.loop(); //execução do cliente mqtt deifnido 
  }
}

bool connectMQTT() {
  byte tentativa = 0;
  client.setServer(mqtt_broker, 1883); //cofnigurando o servidor
  client.setCallback(callback); //configurando o callback 

  do {
    String client_id = "LAMP-"; //Define o nome do cliente MQTT
    client_id += String(WiFi.macAddress()); //Armazena na variável o MAC da rede

    if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("Exito na conexão"); //caso os parâmetros passados forem válidos
    
    } else {
      Serial.print("Falha ao conectar: ");
      Serial.print(client.state());
      Serial.println();
      Serial.print("Tentativa: ");
      Serial.println(tentativa);
      delay(2000);
    }
    tentativa++;
  } while (!client.connected() && tentativa < 5); //executa as tentativas de conexão enquanto a condição for válida

  if (tentativa < 5) {

    //Inscreve-se em um tópico e publica nele para obter um retorno de conexão
    client.publish(topic1,"OFF");
    client.subscribe(topic1); //led1

    client.publish(topic2,"OFF");
    client.subscribe(topic2); //led2

    client.publish(topic3,"OFF");
    client.subscribe(topic3); //todos os leds

    return 1; //retorna o valor que indica êxito na conexão com o MQTT
  } else {
    Serial.println("Não Conectado");
    return 0; //caso o ESP não consiga se conectar ao MQTT
  }
}

void callback(char* topic, byte* payload, unsigned int length) {

  //Informa através do monitor serial o tópico que a mensagem foi recebida e qual é a mensagem
  Serial.print("Mensagem chegou no tópico: "); 
  Serial.println(topic);
  Serial.println("Mensagem: ");

  String message = ""; //armazenará a mensagem recebida
  for (int i=0; i<length; i++) {
    message += (char)payload[i]; //vetor que armazena a mensagem e armazena a variável
    Serial.print(message);
  }

  Serial.println();
  Serial.println("---------------------------------------------");

  // Verifica qual o tópico da mensagem recebida
  if (strcmp(topic, "led/builtin/L1") == 0) {
    // Controla o LED 1
    if (message == "1") {
      digitalWrite(D0, HIGH);
    } else {
      digitalWrite(D0, LOW);
    }

  } else if (strcmp(topic, "led/builtin/L2") == 0) {
    // Controla o LED 2
    if (message == "1") {
      digitalWrite(D3, HIGH);
    } else {
      digitalWrite(D3, LOW);
    }

  } else {
    // Controla ambos os LEDs em conjunto
    if (message == "1") {
      digitalWrite(D0, HIGH);
      digitalWrite(D3, HIGH);
    } else {
      digitalWrite(D0, LOW);
      digitalWrite(D3, LOW);
    }
  }
}







 

  