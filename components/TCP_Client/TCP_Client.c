/* WiFi station Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "TCP_Client.h"

void tcp_client_init()
{
    char rx_buffer[256];
    char host_ip[] = HOST_IP_ADDR;
    int addr_family = 0;
    int ip_protocol = 0;

    char char_array[3][100] = {0};
    strcat(char_array[0], at1);
    strcat(char_array[1], at2);
    strcat(char_array[2], at3);

    while (1) {
//#if defined(CONFIG_EXAMPLE_IPV4)
        struct sockaddr_in dest_addr;
        dest_addr.sin_addr.s_addr = inet_addr(host_ip);
        dest_addr.sin_family = AF_INET;
        dest_addr.sin_port = htons(PORT);
        addr_family = AF_INET;
        ip_protocol = IPPROTO_IP;
// #elif defined(CONFIG_EXAMPLE_IPV6)
//         struct sockaddr_in6 dest_addr = { 0 };
//         inet6_aton(host_ip, &dest_addr.sin6_addr);
//         dest_addr.sin6_family = AF_INET6;
//         dest_addr.sin6_port = htons(PORT);
//         dest_addr.sin6_scope_id = esp_netif_get_netif_impl_index(EXAMPLE_INTERFACE);
//         addr_family = AF_INET6;
//         ip_protocol = IPPROTO_IPV6;
// #elif defined(CONFIG_EXAMPLE_SOCKET_IP_INPUT_STDIN)
//         struct sockaddr_storage dest_addr = { 0 };
//         ESP_ERROR_CHECK(get_addr_from_stdin(PORT, SOCK_STREAM, &ip_protocol, &addr_family, &dest_addr));
// #endif
        int sock =  socket(addr_family, SOCK_STREAM, ip_protocol);
        if (sock < 0) {
            ESP_LOGE(TCP_TAG, "Unable to create socket: errno %d", errno);
            break;
        }
        ESP_LOGI(TCP_TAG, "Socket created, connecting to %s:%d", host_ip, PORT);

        int err = connect(sock, (struct sockaddr *)&dest_addr, sizeof(struct sockaddr_in6));
        if (err != 0) {
            ESP_LOGE(TCP_TAG, "Socket unable to connect: errno %d", errno);
            break;
        }
        ESP_LOGI(TCP_TAG, "Successfully connected");

        while (1) 
        {
            for(int i = 0; i < 3; i++)
            {
                int err = send(sock, char_array[i], strlen(char_array[i]), 0);
                if (err < 0) {
                    ESP_LOGE(TCP_TAG, "Error occurred during sending: errno %d", errno);
                    break;
                }

                int len = recv(sock, rx_buffer, sizeof(rx_buffer) - 1, 0);
                // Error occurred during receiving
                if (len < 0) {
                    ESP_LOGE(TCP_TAG, "recv failed: errno %d", errno);
                    break;
                }
                // Data received
                else {
                    rx_buffer[len] = 0; // Null-terminate whatever we received and treat like a string
                    ESP_LOGI(TCP_TAG, "Received %d bytes from %s:", len, host_ip);
                    ESP_LOGI(TCP_TAG, "%s", rx_buffer);
                }

                vTaskDelay(200 / portTICK_PERIOD_MS);
            }
        }

        if (sock != -1) {
            ESP_LOGE(TCP_TAG, "Shutting down socket and restarting...");
            shutdown(sock, 0);
            close(sock);
        }
    }
    vTaskDelete(NULL);
}

