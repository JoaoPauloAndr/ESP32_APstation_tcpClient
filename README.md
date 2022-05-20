# Comunicação com ESP32 via WiFi - Station

Este código usa os exemplos da ESP-IDF `station` e `tcp_client` como base. Ele habilita o modo Station no ESP32 para se conectar a um AP em uma ESP32 e implementa um cliente TCP que manda exemplos de comandos AT.

## Como Usar

### Hardware Requerido

Este exemplo foi feito para e testado em placas ESP32-WROOM-32 e ESP32-C3.

### Configurar o projeto

```
idf.py menuconfig
```

### Build e Flash

```
idf.py build
idf.py -p PORT flash monitor
```

(Toggle do monitor serial: ``Ctrl-]``)