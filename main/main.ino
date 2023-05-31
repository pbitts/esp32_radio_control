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
  float vco_voltage = ( (frequency - 98 )/21 )*1.4 + 1.9;
  Serial.println("Frequência recebida:");
  Serial.println(frequency);
  Serial.println("Voltagem enviada: ");
  Serial.println(vco_voltage);
   
 

 
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
