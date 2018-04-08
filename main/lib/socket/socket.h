#ifndef SOCKET_H
#define SOCKET_H
  #include <lwip/sockets.h>
  #include <esp_log.h>
  #include <string.h>
  #include <errno.h>
  #include "sdkconfig.h"

  #define PORT_NUMBER 80
  static char tag[] = "socket_server";

  void socket_server();

#endif
