# 📡 Projeto IoT – Medição de Intensidade de Sinal WiFi (RSSI) com ESP32 e Envio via MQTT para Ubidots

## 📘 Descrição Geral do Projeto
Este projeto realiza a **leitura contínua da intensidade do sinal WiFi (RSSI, em dBm)** utilizando um **ESP32**.  
Os valores coletados são enviados em **tempo real** para a plataforma **Ubidots** usando o protocolo **MQTT**, permitindo a visualização dos dados em um dashboard com gráfico de linha (tempo × dBm).

O teste final inclui uma simulação de **gaiola de Faraday** dentro do elevador do Inteli, demonstrando como o sinal WiFi despenca drasticamente dentro do ambiente metálico e se recupera ao sair.

---

## 🎯 Objetivos da Atividade
- Conectar o ESP32 à rede WiFi `Inteli.Iot`
- Medir o RSSI da conexão em dBm
- Publicar os valores em um broker MQTT Ubidots
- Criar um dashboard com gráfico atualizado em tempo real
- Realizar testes em cenários diferentes:
  - Ambiente aberto
  - Longe do AP
  - **Dentro do elevador (bloqueio de sinal)**
- Registrar o experimento em vídeo e enviar via Adalove

---

## 🛠️ Hardware Utilizado
- ESP32 WROOM-32U  
- Cabo USB  
- Rede WiFi **Inteli.Iot**



## 🧰 Bibliotecas Utilizadas
#include <WiFi.h>
#include <PubSubClient.h>


"🎥 Vídeo da Demonstração

Clique para assistir o vídeo no Google Drive:

🔗 https://drive.google.com/file/d/1UH3gD8c-rBSXhPg6Gz9PUoOQB65yXfOX/view?usp=drive_link
