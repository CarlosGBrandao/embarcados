#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "SSIDDASUAINTERNET";
const char* senha = "SENHADASUAINTERNET";

const char* servidor = "http://<ipdoservidor>/recebe_log.php"; // Ex: http://192.168.0.100/recebe_log.php

void setup() {
  Serial.begin(9600); 
  WiFi.begin(ssid, senha);

  Serial.println("Conectando ao Wi-Fi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado ao Wi-Fi.");
}



void loop() {
  
  if (Serial.available()) {
    String dadoRecebido = Serial.readStringUntil('\n'); 

    dadoRecebido.trim(); 

    if (dadoRecebido.length() > 0) {
      Serial.println("Enviando: " + dadoRecebido);

      if (WiFi.status() == WL_CONNECTED) {
        WiFiClient client;
        HTTPClient http;

        http.begin(client, servidor);
        http.addHeader("Content-Type", "application/x-www-form-urlencoded");

        String postData = "valor=" + dadoRecebido;

        int httpResponseCode = http.POST(postData);
        String resposta = http.getString();

        Serial.println("Resposta do servidor: " + resposta);
        http.end();
      } else {
        Serial.println("Wi-Fi desconectado!");
      }
    }
  }

  delay(500);
}
