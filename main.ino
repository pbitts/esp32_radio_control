#include <WiFi.h>

const char* ssid = "JosephJokerRadio";
const char* password = "esqueci_A_Senha";

const int VCOPin = 25; 

void setup() {
  Serial.begin(115200);

  pinMode(VCOPin, OUTPUT); // Define o pino de saída como saída analógica

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

  // Analisa a solicitação HTTP em busca do parâmetro "frequency"
  float frequency = 0.0;
  if (request.indexOf("frequency=") != -1) {
    frequency = request.substring(request.indexOf("frequency=") + 6).toFloat();
  }

  // Converte o frequency para a saída analógica
  int analog_vco = map(frequency, 87.5, 108.0, 0, 4095);

  // Define a saída analógica
  analogWrite(VCOPin, analog_vco);

  // Envia uma resposta HTTP de confirmação para o cliente
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/plain");
  client.println("Connection: close");
  client.println();
  client.printf("frequency recebido e enviado para o VCO: %f", frequency);
}
