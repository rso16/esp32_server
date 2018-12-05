#ifndef WIFI_H
#define WIFI_H

  #include "freertos/FreeRTOS.h"
  #include "freertos/task.h"
  #include "esp_system.h"
  #include "freertos/event_groups.h"
  #include "esp_log.h"
  #include "esp_wifi.h"
  #include "esp_event_loop.h"

  #define WIFI_SSID "ESP 32"
  #define WIFI_PASS "stuff123"
  #define TAG "wifi"

  esp_err_t wifi_event_handler(void *ctx, system_event_t *event);
  void wifi_conn_init();

#endif
