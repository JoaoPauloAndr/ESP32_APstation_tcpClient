#include "nvs_flash.h"
#include "WiFi_AT.h"
#include "TCP_Client.h"

void app_main(void)
{
    esp_err_t status = WIFI_FAILURE;
    //Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    ESP_LOGI(WIFI_TAG, "ESP_WIFI_MODE_STA");
    status = wifi_init_sta();

    if (WIFI_SUCCESS != status)
	{
		ESP_LOGI(WIFI_TAG, "Failed to associate to AP, dying...");
		return;
	}

    xTaskCreate(tcp_client_init, "tcp_client", 4096, NULL, 5, NULL);
}
