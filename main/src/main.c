#include "main.h"
void app_main()
{
  printf("%s\n", "starting ...");
  // struct http_response resp = gen_http_response("test", "test","test");
  // print_http_response(resp);
  // char *str = malloc(100);
  // strcpy(str, gen_http_response_str(resp));
  // printf("str = %s\n", str);

  nvs_flash_init();
  wifi_conn_init();
  socket_server();

  vTaskDelay(1000 / portTICK_PERIOD_MS);
}
