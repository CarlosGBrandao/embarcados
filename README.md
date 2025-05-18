# 🚗 Carrinho Seguidor de Linha – Arduino + ESP

## 🔧 Resumo

Projeto de um carrinho que:
- Segue uma linha preta com sensores MH.
- Evita obstáculos com sensor ultrassônico.
- Envia dados via serial para a ESP32 ou ESP8266.

## 📁 Códigos

- `arduino_carro.ino` – Código do Arduino para controle de sensores e motores.
- `esp_serial.ino` – Código da ESP para leitura dos dados enviados via serial.

## ⚙️ Componentes

- Arduino Uno/Nano  
- ESP32 ou ESP8266  
- Ponte H L298N  
- Sensores de linha (A0, A1)  
- Sensor ultrassônico (TRIG: 7, ECHO: 6)  
- Motores DC (IN1-4, ENA: 12, ENB: 2)
