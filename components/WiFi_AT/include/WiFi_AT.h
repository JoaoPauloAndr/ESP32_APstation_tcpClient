#ifndef WIFI_AT_H
#define WIFI_AT_H

#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"

#include "lwip/err.h"
#include "lwip/sys.h"

#define EXAMPLE_ESP_WIFI_SSID      "ESP32AP"//CONFIG_ESP_WIFI_SSID
#define EXAMPLE_ESP_WIFI_PASS      "98SEVEN7"//CONFIG_ESP_WIFI_PASSWORD
//#define EXAMPLE_ESP_MAXIMUM_RETRY  CONFIG_ESP_MAXIMUM_RETRY

/* FreeRTOS event group to signal when we are connected*/
static EventGroupHandle_t s_wifi_event_group;

/* The event group allows multiple bits for each event, but we only care about two events:
 * - we are connected to the AP with an IP
 * - we failed to connect after the maximum amount of retries */
#define WIFI_SUCCESS 1 << 0
#define WIFI_FAILURE 1 << 1
#define TCP_SUCCESS  1 << 0
#define TCP_FAILURE  1 << 1
#define MAX_FAILURES 10

static const char *WIFI_TAG = "wifi station";
static int s_retry_num = 0;

esp_err_t wifi_init_sta(void);

#endif
