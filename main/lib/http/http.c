#include "http.h"
struct http_response gen_http_response_all(char *status_code, int  content_length, char *content_type, char *data)
{
  struct http_response resp;

  resp.status_code = malloc(sizeof(char)*getLengthOfCharArray(status_code));
  strcpy(resp.status_code, status_code);

  resp.content_length = content_length;

  resp.content_type = malloc(sizeof(char)*getLengthOfCharArray(content_type));
  strcpy(resp.content_type, content_type);

  resp.data = malloc(sizeof(char)*getLengthOfCharArray(data));
  strcpy(resp.data, data);

  return resp;
}

struct http_response gen_http_response(char *status_code, char *content_type, char *data)
{
  struct http_response resp = gen_http_response_all(status_code, getLengthOfCharArray(data), content_type, data);
  return resp;
}

char* gen_http_response_str(struct http_response resp)
{
  char *respStr = malloc(sizeof(char) * CONFIG_TCP_SND_BUF_DEFAULT);
  sprintf(respStr,"%s\nContent-length: %d\nContent-Type: %s\n\n%s",resp.status_code,resp.content_length,resp.content_type,resp.data);
  return respStr;
}
void print_http_response(struct http_response resp)
{
  printf("Printing http resonse \n");
  printf("Status code    = %s\n", resp.status_code);
  printf("Content length = %d\n", resp.content_length);
  printf("Content_type   = %s\n", resp.content_type);
  printf("Data           = %s\n", resp.data);

}
