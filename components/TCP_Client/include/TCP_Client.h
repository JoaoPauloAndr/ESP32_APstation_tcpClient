#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <string.h>
#include <sys/param.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "lwip/err.h"
#include "lwip/sockets.h"

#define HOST_IP_ADDR "192.168.4.1"  //AP IP

#define PORT 3333//CONFIG_EXAMPLE_PORT

static const char *TCP_TAG = "example";
static const char *payload = "Message from ESP32 ";

void tcp_client_init();  //void *pvParameters

#endif