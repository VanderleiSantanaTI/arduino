#include <WiFi.h>

const char* ssid = "ANDRADE GOES";
const char* password = "";
int LED = 2;
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);

  Serial.println();
  Serial.print("Conectando-se a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectada.");
  Serial.println("Endereço de IP: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New Client.");
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n') {
          if (currentLine.length() == 0) {
                   client.println("HTTP/1.1 200 OK");
        client.println("Content-type:text/html");
        client.println();
        client.println("<!DOCTYPE HTML>");
        client.println("<html>");
     
        // Adicione um estilo básico para tornar os botões mais visíveis
        
        client.println("<head>\
                        <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\
                        <style>\
                         button { padding: 10px 20px; font-size: 16px; }\
                        .ligButton{background-color: blue; color: rgb(255,255,255)}\
                        .desButton{background-color: red; color: rgb(255,255,255)}\
                        .estadoText{font-family: SANS-SERIF;margin-top: 30px;text-align: -webkit-center;font-weight: bold;}}\
                           </style>\
                        </head>");

        client.println("<body>");
        client.println("<h1>Controle do LED</h1>");

        // Adicione botões para ligar e desligar o LED
        client.println("<button class=\"ligButton\" onclick=\"turnOnLED()\">Ligar LED</button>");
        client.println("<button class=\"desButton\" onclick=\"turnOffLED()\">Desligar LED</button>");
        
        client.println("<br>");
        client.println("<div class =\"estadoText\" id=\"estadoLED\"></div>");
        client.println("<img id=\"imagemLED\" src=\"https://static.vecteezy.com/ti/vetor-gratis/p3/21058324-brilhando-e-desligada-a-lampada-eletrica-ilustracaoial-vetor.jpg\" style=\"width: 100px; height: 100px; display: block; margin: 0 auto; text-align: center;\">");

        client.println("<script>");
        client.println("function turnOnLED() {");
        client.println("  fetch('/H').then(response => {");
        client.println("    document.getElementById('estadoLED').innerHTML = 'LED Ligado';");
        client.println("    document.getElementById('imagemLED').src = 'https://img.myloview.com.br/quadros/lampada-acesa-luz-700-1109866.jpg'; // Substitua 'led_on.png' pelo caminho da sua imagem de LED ligado");
        client.println("  });");
        client.println("}");
        client.println("function turnOffLED() {");
        client.println("  fetch('/L').then(response => {");
        client.println("    document.getElementById('estadoLED').innerHTML = 'LED Desligado';");
        client.println("    document.getElementById('imagemLED').src = 'https://img.freepik.com/vetores-gratis/lampada-realistica-isolada-de-vetor-sobre-branco_1284-41931.jpg';");
        client.println("  });");
        client.println("}");
        client.println("</script>");

        client.println("</body>");
        client.println("</html>");
        break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(LED, HIGH);
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(LED, LOW);
        }
      }
    }
    client.stop();
    Serial.println("Client Disconnected.");
  }
}