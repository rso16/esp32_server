#ifndef HTTP_H
#define HTTP_H
  #include <stdio.h>
  #include <string.h>
  #include <stdlib.h>
  #include "../functions/functions.h"
  #include <sdkconfig.h>
  //structs
  struct http_response
  {
    char *status_code;
    int  content_length;
    char *content_type;
    char *data;
  };

  //functions
  struct http_response gen_http_response_all(char *status_code, int  content_length, char *content_type, char *data);
  struct http_response gen_http_response(char *status_code, char *content_type, char *data);
  char* gen_http_response_str(struct http_response resp);
  void print_http_response(struct http_response resp);

#endif
