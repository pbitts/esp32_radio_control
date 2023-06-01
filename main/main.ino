#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

const char* ssid = "JosephJokerRadio";
const char* password = "esqueci_A_Senha";

const int VCOPin = 25; 

WebServer server(80); // Cria um objeto servidor na porta 80

void handleRoot() {
  String html = "<form method='POST' action='/form'>";
  html += "<input type='number' name='frequencia'>";
  html += "<input type='submit' value='Enviar'>";
  html += "</form>";

  server.send(200, "text/html", html);
}

void handleForm() {
  if (server.hasArg("frequencia")) {
    String frequency = server.arg("frequencia");
    // Faça o que desejar com o número recebido
    // Exemplo: imprimir no monitor serial
    Serial.println("Frequencia recebida: " + frequency);

    server.send(200, "text/html", "Frequencia recebida com sucesso!");
    float frequencia = frequency.toFloat();
    float vco_voltage = ( (frequencia - 98 )/21 )*1.4 + 1.9;
      Serial.println("Frequência recebida:");
      Serial.println(frequencia);
      Serial.println("Voltagem enviada: ");
      Serial.println(vco_voltage);
      analogWrite(VCOPin, map(vco_voltage, 0.0, 3.3, 0, 255));
   
  } else {
    server.send(400, "text/plain", "Erro: número não recebido");
  }
}


void setup() {
  Serial.begin(115200);
  
  pinMode(VCOPin, OUTPUT); // Define o pino de saída como saída analógica

  // Configura o WiFi como Access Point

  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  server.on("/", handleRoot);
  server.on("/form", HTTP_POST, handleForm);

  server.begin();

  // Inicializa o servidor
  server.begin();
}

void loop() {
  server.handleClient();
}
