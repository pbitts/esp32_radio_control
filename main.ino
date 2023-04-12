#include <WiFi.h>

const char* ssid = "JosephJokerRadio";
const char* password = "esqueci_A_Senha";

const int analogOutPin = 25; // Define o pino de saída analógica

void setup() {
  Serial.begin(115200);

  pinMode(analogOutPin, OUTPUT); // Define o pino de saída como saída analógica

  // Inicializa o WiFi como Access Point
  WiFi.softAP(ssid, password);

  // Configura o endpoint "station"
  WiFi.onSoftAPModeStationConnected(onStationConnected);
}

void loop() {
  // Nada a ser feito no loop
}

void onStationConnected(WiFiEventSoftAPModeStationConnected event) {
  Serial.print("Nova estação conectada: ");
  Serial.println(event.mac.toString());

  // Configura o servidor HTTP para lidar com a solicitação "station"
  WiFi.softAPHTTPServer(onHTTPRequest);
}

void onHTTPRequest(WiFiClient client) {
  // Lê a solicitação HTTP do cliente
  String request = client.readStringUntil('\r');
  client.flush();

  // Analisa a solicitação HTTP em busca do parâmetro "valor"
  float valor = 0.0;
  if (request.indexOf("valor=") != -1) {
    valor = request.substring(request.indexOf("valor=") + 6).toFloat();
  }

  // Converte o valor para a saída analógica
  int analogValue = map(valor, 87.5, 108.0, 0, 4095);

  // Define a saída analógica
  analogWrite(analogOutPin, analogValue);

  // Envia uma resposta HTTP de confirmação para o cliente
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/plain");
  client.println("Connection: close");
  client.println();
  client.printf("Valor recebido e enviado para o VCO: %f", valor);
}
