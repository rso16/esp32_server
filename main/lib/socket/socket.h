#ifndef SOCKET_H
#define SOCKET_H
  #include <lwip/sockets.h>
  #include <esp_log.h>
  #include <string.h>
  #include <errno.h>
  #include "sdkconfig.h"


  void socket_server();

  #define PORT_NUMBER 80
  static char tag[] = "socket_server";
  static char img[] = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A, 0x00, 0x00, 0x00, 0x0D, 0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x0A, 0x08, 0x02, 0x00, 0x00, 0x00, 0x02, 0x50, 0x58, 0xEA, 0x00, 0x00, 0x00, 0x01, 0x73, 0x52, 0x47, 0x42, 0x00, 0xAE, 0xCE, 0x1C, 0xE9, 0x00, 0x00, 0x00, 0x04, 0x67, 0x41, 0x4D, 0x41, 0x00, 0x00, 0xB1, 0x8F, 0x0B, 0xFC, 0x61, 0x05, 0x00, 0x00, 0x00, 0x09, 0x70, 0x48, 0x59, 0x73, 0x00, 0x00, 0x0E, 0xC3, 0x00, 0x00, 0x0E, 0xC3, 0x01, 0xC7, 0x6F, 0xA8, 0x64, 0x00, 0x00, 0x00, 0x13, 0x49, 0x44, 0x41, 0x54, 0x28, 0x53, 0x63, 0x78, 0x2B, 0xA3, 0x82, 0x07, 0x8D, 0x4A, 0x63, 0x41, 0x32, 0x2A, 0x00, 0x84, 0x7F, 0x75, 0x95, 0x44, 0x8D, 0x05, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4E, 0x44, 0xAE, 0x42, 0x60, 0x82 };

#endif
