#include"socket.h"
void socket_server()
{
	printf("test!!!!!\n");
	struct sockaddr_in clientAddress;
	struct sockaddr_in serverAddress;

	// Create a socket that we will listen upon.
	int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock < 0)
	{
		ESP_LOGE(tag, "socket: %d %s", sock, strerror(errno));
		goto END;
	}

	// Bind our server socket to a port.
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddress.sin_port = htons(PORT_NUMBER);
	int rc  = bind(sock, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
	if (rc < 0)
	{
		ESP_LOGE(tag, "bind: %d %s", rc, strerror(errno));
		goto END;
	}

	// Flag the socket as listening for new connections.
	rc = listen(sock, 1);
	if (rc < 0)
	{
		ESP_LOGE(tag, "listen: %d %s", rc, strerror(errno));
		goto END;
	}

	int counter = 1;
	while (1)
	{
		// Listen for a new client connection.
		socklen_t clientAddressLength = sizeof(clientAddress);
		int clientSock = accept(sock, (struct sockaddr *)&clientAddress, &clientAddressLength);
		if (clientSock < 0)
		{
			ESP_LOGE(tag, "accept: %d %s", clientSock, strerror(errno));
			goto END;
		}
		else
		{
			printf("New client\n");
		}

		// We now have a new client ...
		int total =	10*1024;
		int sizeUsed = 0;
		char *data = malloc(total);
		int counter = 1;
		// Loop reading data.
		while(counter)
		{
			ssize_t sizeRead = recv(clientSock, data + sizeUsed, total-sizeUsed, 1);
			if (sizeRead < 0)
			{
				ESP_LOGE(tag, "recv: %d %s", sizeRead, strerror(errno));
				goto END;
			}
			if (sizeRead == 0)
			{
				break;
			}
			sizeUsed += sizeRead;
			counter--;
		}

		// Finished reading data.

		ESP_LOGD("tag", "Data read (size: %d) was: %.*s", sizeUsed, sizeUsed, data);
		size_t size;
		if(strstr(data,"mystyle"))
		{
			printf("getting css\n");

			char str[] = "HTTP/1.1 200 OK\nContent-length: 34\nContent-Type: text/css\n\nbody{background-color: lightblue;}";
			printf("response = \n%s\n", str);
			size = sizeof(str);
			printf("size = %d\n", size);
			send(clientSock, str,size,1);
		}
		else if (strstr(data,"index") && !(strstr(data,"img")))
		{
			printf("getting index\n");
			struct http_response resp = gen_http_response("HTTP/1.1 200 OK", "text/html","<html><head><link rel=stylesheet type=text/css href=mystyle.css></head><body><H1>Hello world!!</H1><img src=\"data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAAUAAAAFCAYAAACNbyblAAAAHElEQVQI12P4//8/w38GIAXDIBKE0DHxgljNBAAO9TXL0Y4OHwAAAABJRU5ErkJggg==\" alt=\"Red dot\"></body></html>");
			char *respStr = gen_http_response_str(resp);
			printf("response = \n%s\n", respStr);
			send(clientSock,respStr,getLengthOfCharArray(respStr),1);
			free(respStr);

		}
		else if(strstr(data,"img"))
		{
			char httpstr[] = "HTTP/1.1 200 OK\nContent-length: 377\nContent-Type: image/png\nContent-Transfer-Encoding: binary\ncharset=ISO-8859-4\n\n";
			printf("getting img\n");
			size = 377 + sizeof(httpstr);
			char str[size];
			strcpy(str, httpstr);
			strcat(str, img);
			printf("response = \n%s\n", str);
			printf("size = %d\n", size);
			send(clientSock, str,size,1);
		}
		else
		{
			printf("404");
			char str[] =  "HTTP/1.1 404 Not Found\nContent-length: 48\nContent-Type: text/html\n\n<html><body><H1>404 NOT FOUND</H1></body></html>";
			size = sizeof(str);
			printf("response = \n%s\n", str);
			printf("size = %d\n", size);
			send(clientSock, str,size,1);
		}

				//<link rel=\"stylesheet\" type=\"text/css\" href=\"mystyle.css\">
				// size = sizeof("HTTP/1.1 200 OK\nContent-length: 34\nContent-Type: text/html\n<H1>cyka blyat</H1></body></html>");
				// printf("size = %d\n", size);
				// send(clientSock, "HTTP/1.1 200 OK\nContent-length: 34\nContent-Type: text/html\n<H1>cyka blyat</H1></body></html>",size,1);

				//  size = sizeof("<!DOCTYPE html><html><body><p>This is a paragraph.</p><p>This is another paragraph.</p></body></html>\r\n\r\n");
				// printf("size = %d\n", size);
				// send(clientSock, "<!DOCTYPE html><html><body><p>This is a paragraph.</p><p>This is another paragraph.</p></body></html>\r\n\r\n",size,1);
				free(data);
				close(clientSock);
				printf("---------------------------------------------------------------------------------------------------------------\n");
	}
	END:
	vTaskDelete(NULL);
}

void sendHTTPResponse(int clientSock, struct http_response resp)
{
	// send(clientSock,respStr,getLengthOfCharArray(respStr))
}
