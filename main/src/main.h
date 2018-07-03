//standard libs and esp libs
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "nvs_flash.h"
#include "nvs.h"
#include <sdkconfig.h>

//my libs
#include "../lib/wifi/wifi.h"
#include "../lib/socket/socket.h"
#include "../lib/http/http.h"
#include "../lib/functions/functions.h"

void app_main();
