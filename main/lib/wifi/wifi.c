//code to handle wifi
#include "wifi.h"
esp_err_t wifi_event_handler(void *ctx, system_event_t *event)
{
    switch(event->event_id)
    {
      case SYSTEM_EVENT_STA_START:
          esp_wifi_connect();
          break;
      case SYSTEM_EVENT_STA_GOT_IP:
          printf("Our IP address is " IPSTR "\n",
          IP2STR(&event->event_info.got_ip.ip_info.ip));
          printf("We have now connected to a station and can do things...\n");
          break;
      default:
          break;
    }
    return ESP_OK;
}

void wifi_conn_init()
{

    tcpip_adapter_init();
    // wifi_event_group = xEventGroupCreate();
    ESP_ERROR_CHECK( esp_event_loop_init(wifi_event_handler, NULL) );
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK( esp_wifi_init(&cfg) );
    ESP_ERROR_CHECK( esp_wifi_set_storage(WIFI_STORAGE_RAM) );
    wifi_config_t wifi_config = {
        .ap = {
            .ssid = WIFI_SSID,
            .password = WIFI_PASS,
            .authmode = WIFI_AUTH_WPA_PSK,
            .max_connection = 5
        },
    };
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK( esp_wifi_set_config(ESP_IF_WIFI_AP, &wifi_config) );
    ESP_LOGI(TAG, "start the WIFI SSID:[%s] password:[%s]\n", WIFI_SSID, WIFI_PASS);
    ESP_ERROR_CHECK( esp_wifi_start() );
}
