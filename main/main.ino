#include <WiFi.h>

const char* ssid = "JosephJokerRadio";
const char* password = "esqueci_A_Senha";

const int VCOPin = 25; 

WiFiServer server(80); // Cria um objeto servidor na porta 80

void setup() {
  Serial.begin(115200);
  
  pinMode(VCOPin, OUTPUT); // Define o pino de saída como saída analógica

  // Configura o WiFi como Access Point
  WiFi.softAP(ssid, password);

  Serial.println();
  Serial.println("Access Point configurado:");
  Serial.println(WiFi.softAPIP());

  // Inicializa o servidor
  server.begin();
}

void loop() {
  // Verifica se há clientes conectados
  WiFiClient client = server.available();
  if (client) {
    Serial.println("Nova requisição HTTP recebida.");

    // Lê a solicitação HTTP do cliente
    String request = client.readStringUntil('\r');
    client.flush();

    // Analisa a solicitação HTTP em busca do parâmetro "frequency"
    float frequency = 0.0;
    if (request.indexOf("frequency=") != -1) {
      frequency = request.substring(request.indexOf("frequency=") + 6).toFloat();
    }
  float vco_voltage = 1.0;
   
  if ( frequency >= 97 && frequency < 99) {
      float vco_voltage = 1.9; // Tensão desejada em volts
      int analog_vco = map(vco_voltage, 0.0, 3.3, 0, 255); // Mapeia a tensão desejada para o valor do DAC
  }
   else if (frequency >= 99 && frequency < 102) {
      float vco_voltage = 2.0; // Tensão desejada em volts
      int analog_vco = map(vco_voltage, 0.0, 3.3, 0, 255); // Mapeia a tensão desejada para o valor do DAC
  
 } else if (frequency >= 102 && frequency < 103) {
    float vco_voltage = 2.1; // Tensão desejada em volts
    int analog_vco = map(vco_voltage, 0.0, 3.3, 0, 255); // Mapeia a tensão desejada para o valor do DAC

 } else if (frequency >= 103 && frequency < 104) {
    float vco_voltage = 2.2; // Tensão desejada em volts
    int analog_vco = map(vco_voltage, 0.0, 3.3, 0, 255); // Mapeia a tensão desejada para o valor do DAC

 } else if (frequency >= 104 && frequency < 105) {
    float vco_voltage = 2.3; // Tensão desejada em volts
    int analog_vco = map(vco_voltage, 0.0, 3.3, 0, 255); // Mapeia a tensão desejada para o valor do DAC

 } else if (frequency >= 105 && frequency < 108) {
    float vco_voltage = 2.6; // Tensão desejada em volts
    int analog_vco = map(vco_voltage, 0.0, 3.3, 0, 255); // Mapeia a tensão desejada para o valor do DAC

 } else if (frequency >= 108 && frequency < 109) {
    float vco_voltage = 2.7; // Tensão desejada em volts
    int analog_vco = map(vco_voltage, 0.0, 3.3, 0, 255); // Mapeia a tensão desejada para o valor do DAC

 } else if (frequency >= 109 && frequency < 110) {
    float vco_voltage = 2.7; // Tensão desejada em volts
    int analog_vco = map(vco_voltage, 0.0, 3.3, 0, 255); // Mapeia a tensão desejada para o valor do DAC

 } else if (frequency >= 110 && frequency < 112) {
    float vco_voltage = 2.9; // Tensão desejada em volts
    int analog_vco = map(vco_voltage, 0.0, 3.3, 0, 255); // Mapeia a tensão desejada para o valor do DAC

 } else if (frequency >= 112 && frequency < 113) {
    float vco_voltage = 3.0; // Tensão desejada em volts
    int analog_vco = map(vco_voltage, 0.0, 3.3, 0, 255); // Mapeia a tensão desejada para o valor do DAC
 } else if (frequency >= 113 && frequency < 115) {
    float vco_voltage = 3.1; // Tensão desejada em volts
    int analog_vco = map(vco_voltage, 0.0, 3.3, 0, 255); // Mapeia a tensão desejada para o valor do DAC

 } else if (frequency >= 115 && frequency < 116) {
    float vco_voltage = 3.2; // Tensão desejada em volts
    int analog_vco = map(vco_voltage, 0.0, 3.3, 0, 255); // Mapeia a tensão desejada para o valor do DAC

 } else if (frequency >= 116 && frequency < 119) {
    float vco_voltage = 3.3; // Tensão desejada em volts
    int analog_vco = map(vco_voltage, 0.0, 3.3, 0, 255); // Mapeia a tensão desejada para o valor do DAC
}

 
 analogWrite(VCOPin, vco_voltage); // Define a saída analógica para 1 (255 é o valor máximo)
    
    // Envia uma resposta HTTP para o cliente
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");
    client.println();
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("<head><title>ESP32 Access Point</title></head>");
    client.println("<body>");
    client.println("<h1>ESP32 Access Point</h1>");
    client.println("<p>Requisição HTTP recebida!</p>");
    client.println("</body>");
    client.println("</html>");
    // Serial.print("frequencia recebida e enviado para o VCO: %f", frequency);

    // Aguarda um breve intervalo para que a resposta seja enviada ao cliente
    delay(10);
    client.stop();
  }
}
