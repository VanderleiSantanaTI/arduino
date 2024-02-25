#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "ANDRADE GOES";
const char* password = "";

WebServer server(8000);

int ledPin = 2; // O pino onde o LED está conectado
bool ledState = false; // Estado inicial do LED é desligado

void setup() {

  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  
  Serial.println();
  Serial.print("Conectando-se a ");
  Serial.println(ssid);

    //inicio do bloco*** Configuração do IP fixo
  IPAddress ip(192, 168, 15, 8); // Insira o endereço IP fixo desejado
  IPAddress gateway(192, 168, 15, 1); // Insira o endereço do gateway
  IPAddress subnet(255, 255, 255, 0); // Insira a máscara de sub-rede
  WiFi.config(ip, gateway, subnet);
  // fim do bloco

  // Inicializa a conexão Wi-Fi
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectada.");
  Serial.println("Endereço de IP: ");
  
  Serial.println(WiFi.localIP());

  // Roteamento de URLs
  server.on("/", HTTP_GET, [](){
  String response = ledState ? "LED {'estadoLed': 'desligado'}" : "LED {'estadoLed': 'ligado'}";
  server.send(200, "text/plain", response);
  });
  server.on("/led/on", HTTP_GET, [](){
    digitalWrite(ledPin, HIGH);
    ledState = true;
    server.send(200, "text/plain", "Acao {'LED':'ligado'}");
  });

  server.on("/led/off", HTTP_GET, [](){
    digitalWrite(ledPin, LOW);
    ledState = false;
    server.send(200, "text/plain", "Acao {'LED':'desligado'}");
  });

  server.on("/led/status", HTTP_GET, [](){
    if (ledState) {
      server.send(200, "text/plain", "LED está ligado");
    } else {
      server.send(200, "text/plain", "LED está desligado");
    }
  });

  server.begin();
}

void loop() {
  server.handleClient();

}    