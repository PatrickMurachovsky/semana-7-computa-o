#include <WiFi.h>
#include <PubSubClient.h>

// ===== WIFI =====
const char* ssid     = "Inteli.Iot";
const char* password = "%(Yk(sxGMtvFEs.3";

// ===== Ubidots MQTT =====
const char* mqtt_server = "industrial.api.ubidots.com";
const int   mqtt_port   = 1883;

// Token da sua conta Ubidots (API Credentials)
const char* UBIDOTS_TOKEN = "BBUS-zP0jVQEnuJ5hPRGaTQ2ygM4HM8TDFQ";

// Nome do device no Ubidots (label do dispositivo)
const char* DEVICE_LABEL  = "new-variable";

WiFiClient espClient;
PubSubClient client(espClient);

unsigned long lastMsg = 0;
const unsigned long publishInterval = 1000; // 1 segundo

// ===== FUNÇÃO WIFI =====
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando ao WiFi: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

// ===== RECONEXÃO MQTT (UBIDOTS) =====
void reconnect() {
  while (!client.connected()) {
    Serial.print("Tentando conectar ao MQTT (Ubidots)... ");

    String clientId = "ESP32_RSSI_";
    clientId += String(random(0xffff), HEX);

    // Ubidots: username = TOKEN, senha = vazia
    if (client.connect(clientId.c_str(), UBIDOTS_TOKEN, "")) {
      Serial.println("conectado!");
    } else {
      Serial.print("falhou, rc=");
      Serial.print(client.state());
      Serial.println(" tentando de novo em 5 segundos...");
      delay(5000);
    }
  }
}

// ===== SETUP =====
void setup() {
  Serial.begin(115200);
  delay(1000);

  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
}

// ===== LOOP =====
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg > publishInterval) {
    lastMsg = now;

    long rssi = WiFi.RSSI(); // dBm

    char payload[64];
    snprintf(payload, sizeof(payload), "{\"rssi\": %ld}", rssi);

    String topic = String("/v1.6/devices/") + DEVICE_LABEL;

    bool ok = client.publish(topic.c_str(), payload);

    Serial.print("RSSI: ");
    Serial.print(rssi);
    Serial.print(" dBm | MQTT -> Ubidots: ");
    Serial.print(topic);
    Serial.print(" | Payload: ");
    Serial.print(payload);
    Serial.print(" | Status: ");
    Serial.println(ok ? "OK" : "ERRO");
  }
}
