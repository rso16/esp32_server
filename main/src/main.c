#include "main.h"
void app_main()
{
  printf("%s\n", "starting ...");
  // struct http_response resp = gen_http_response("test", "test","test");
  // print_http_response(resp);
  // char *str = malloc(100);
  // strcpy(str, gen_http_response_str(resp));
  // printf("str = %s\n", str);

  initSD();
  // getPosOfLine("/sdcard/test.html",5);




  // printf("%s\n", getFileAsStr("/sdcard/test.html"));
  // int lines = getAmountOfLines("/sdcard/test.html");
  // for (size_t i = 0; i <= lines; i++)
  // {
  //   // printf("size = %d\n", getLineSize("/sdcard/test.html",i));
  //   printf("%s", getFileLine("/sdcard/test.html", i));
  //   // printf("-----------------------------------\n");
  // }
  // printf("\n");
  printf("file =\n %s\n", getFileAsStr("/sdcard/test.html"));
  printf("file =\n %s\n", getFileAsStr("/sdcard/test.html"));
  printf("file =\n %s\n", getFileAsStr("/sdcard/test.html"));
  printf("file =\n %s\n", getFileAsStr("/sdcard/test.html"));
  printf("file =\n %s\n", getFileAsStr("/sdcard/test.html"));


  nvs_flash_init();
  wifi_conn_init();
  socket_server();

  vTaskDelay(1000 / portTICK_PERIOD_MS);
}
