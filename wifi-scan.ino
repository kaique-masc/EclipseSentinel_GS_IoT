#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define DHTPIN 15
#define DHTTYPE DHT22

#define BOTAO 4
#define LED_VERDE 18
#define LED_VERMELHO 19

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

DHT dht(DHTPIN, DHTTYPE);

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

WebServer server(80);

float temperatura = 0;
float umidade = 0;

String statusAtual = "NORMAL";

void atualizarSensores() {

  temperatura = dht.readTemperature();
  umidade = dht.readHumidity();

  if (isnan(temperatura) || isnan(umidade)) {
    statusAtual = "ERRO SENSOR";
    return;
  }

  bool alerta = false;

  if (digitalRead(BOTAO) == LOW) {
    statusAtual = "EMERGENCIA";
    alerta = true;
  }

  else if (temperatura > 35) {
    statusAtual = "CALOR ALTO";
    alerta = true;
  }

  else if (temperatura < 10) {
    statusAtual = "MUITO FRIO";
    alerta = true;
  }

  else if (umidade > 80) {
    statusAtual = "UMIDADE ALTA";
    alerta = true;
  }

  else if (umidade < 30) {
    statusAtual = "UMIDADE BAIXA";
    alerta = true;
  }

  else {
    statusAtual = "NORMAL";
  }

  digitalWrite(LED_VERDE, !alerta);
  digitalWrite(LED_VERMELHO, alerta);
}

void atualizarDisplay() {

  display.clearDisplay();

  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);

  display.setCursor(0, 0);
  display.print("Temp: ");
  display.print(temperatura, 1);
  display.println(" C");

  display.setCursor(0, 15);
  display.print("Umidade: ");
  display.print(umidade, 1);
  display.println("%");

  display.setCursor(0, 30);
  display.println("Status:");

  display.setCursor(0, 45);
  display.println(statusAtual);

  display.display();
}

void endpointDados() {

  atualizarSensores();

  String json = "{";
  json += "\"temperatura\":" + String(temperatura, 1) + ",";
  json += "\"umidade\":" + String(umidade, 1);
  json += "}";

  server.send(200, "application/json", json);
}

void endpointStatus() {

  atualizarSensores();

  String json = "{";
  json += "\"status\":\"" + statusAtual + "\"";
  json += "}";

  server.send(200, "application/json", json);
}

void endpointAlerta() {

  atualizarSensores();

  String json = "{";
  json += "\"alerta\":\"" + statusAtual + "\"";
  json += "}";

  server.send(200, "application/json", json);
}

void setup() {

  Serial.begin(115200);

  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(BOTAO, INPUT_PULLUP);

  dht.begin();

  Wire.begin(21, 22);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED nao encontrado");
    while (true);
  }

  display.clearDisplay();
  display.display();

  WiFi.begin("Wokwi-GUEST", "");

  Serial.print("Conectando");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi conectado");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  server.on("/dados", endpointDados);
  server.on("/status", endpointStatus);
  server.on("/alerta", endpointAlerta);

  server.begin();

  Serial.println("Servidor iniciado");
}

void loop() {

  atualizarSensores();
  atualizarDisplay();

  server.handleClient();

  delay(1000);
}