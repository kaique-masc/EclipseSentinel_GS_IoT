# Eclipse Sentinel IoT

## Integrantes

* Kaique Mascarenhas dos Santos RM565802
* Felipe Augusto Lopes Ferreira RM563982

---

# Descrição do Projeto

O Eclipse Sentinel IoT é uma solução de monitoramento inteligente para prevenção e resposta a desastres naturais.

O sistema utiliza um ESP32 conectado a sensores ambientais para coletar informações em tempo real sobre temperatura e umidade, permitindo identificar situações de risco como calor extremo, frio intenso, umidade excessiva ou baixa umidade.

Além disso, o sistema possui um botão de emergência para simular ocorrências críticas reportadas pela população ou pela Defesa Civil.

As informações são exibidas localmente em um display OLED e disponibilizadas através de uma API REST acessível pela rede Wi-Fi.

---

# Objetivo

Desenvolver uma solução IoT capaz de:

* Monitorar condições ambientais;
* Detectar situações de risco;
* Emitir alertas visuais;
* Disponibilizar dados através de endpoints REST;
* Apoiar ações preventivas da Defesa Civil.

---

# Tecnologias Utilizadas

## Hardware

* ESP32
* Sensor DHT22
* Botão de Emergência
* LED Verde
* LED Vermelho
* Display OLED SSD1306

## Software

* Arduino IDE
* ESP32
* Wokwi Simulator
* API REST
* Wi-Fi
* GitHub

---

# Arquitetura da Solução

O ESP32 realiza a leitura contínua dos sensores e verifica as condições ambientais.

Quando uma condição de risco é identificada:

* O LED vermelho é acionado;
* O status de alerta é atualizado;
* As informações são exibidas no OLED;
* Os dados ficam disponíveis via API REST.

Em condições normais:

* O LED verde permanece ligado;
* O sistema informa operação normal.

---

# Componentes Utilizados

| Componente | Quantidade |
|------------|------------|
| ESP32 | 1 |
| DHT22 | 1 |
| Botão | 1 |
| LED Verde | 1 |
| LED Vermelho | 1 |
| Display OLED SSD1306 | 1 |

---

# Entradas do Sistema

## Sensor DHT22

Responsável pela leitura de:

* Temperatura
* Umidade

## Botão de Emergência

Permite simular uma ocorrência crítica.

---

# Saídas do Sistema

## LED Verde

Indica operação normal.

## LED Vermelho

Indica situação de alerta.

## Display OLED

Exibe:

* Temperatura
* Umidade
* Status atual

---

# Regras de Negócio

O sistema gera alertas quando:

### Calor Extremo

Temperatura superior a 35°C.

### Frio Extremo

Temperatura inferior a 10°C.

### Umidade Elevada

Umidade superior a 80%.

### Baixa Umidade

Umidade inferior a 30%.

### Emergência Manual

Botão pressionado.

---

# Comunicação Wi-Fi

O ESP32 conecta-se à rede Wi-Fi e disponibiliza uma API REST para consulta dos dados monitorados.

---

# Endpoints da API

## GET /dados

Retorna temperatura e umidade atuais.

### Exemplo

```json
{
  "temperatura": 28.5,
  "umidade": 65.2
}
```

---

## GET /status

Retorna o status atual do sistema.

### Exemplo

```json
{
  "status": "NORMAL"
}
```

### Possíveis valores

* NORMAL
* CALOR ALTO
* MUITO FRIO
* UMIDADE ALTA
* UMIDADE BAIXA
* EMERGENCIA

---

## GET /alerta

Retorna o alerta atualmente ativo.

### Exemplo

```json
{
  "alerta": "CALOR ALTO"
}
```

---

# Dashboard

O sistema disponibiliza os dados através dos endpoints REST, permitindo integração com dashboards e aplicações web para visualização em tempo real.

---

# Requisitos Atendidos

## Entradas

* Sensor DHT22
* Botão de Emergência

## Saídas

* LED Verde
* LED Vermelho

## Interface Local

* Display OLED SSD1306

## Comunicação

* Wi-Fi

## API

* API REST

## Endpoints

* /dados
* /status
* /alerta

## Monitoramento

* Temperatura
* Umidade
* Estado de Emergência

---

# Simulação

A solução foi desenvolvida utilizando o simulador Wokwi com ESP32.

---

# Repositório

Inserir link do GitHub:

```text
(https://github.com/kaique-masc/EclipseSentinel_GS_IoT.git)
```

---

# Conclusão

O Eclipse Sentinel IoT demonstra como dispositivos conectados podem auxiliar no monitoramento ambiental e na prevenção de desastres naturais, fornecendo informações em tempo real para apoio à tomada de decisão da Defesa Civil e da população.
