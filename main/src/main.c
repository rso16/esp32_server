#include "main.h"
void app_main()
{
  printf("%s\n", "starting ...");
  // initSD();
  nvs_flash_init();
  wifi_conn_init();
  socket_server();

  vTaskDelay(1000 / portTICK_PERIOD_MS);
}
