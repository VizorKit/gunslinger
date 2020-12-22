#include "./socket.h"
#include "../debug/debug.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

static int sockfd, reusefd, clientfd;
static struct sockaddr_in6 server_address;
static int bindfd;
static int error = 0;

int socket_init() {
  sockfd = socket(AF_INET6, SOCK_STREAM, 0);
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reusefd, sizeof(reusefd));
  if (sockfd == -1) {
    debug_print("%s\n", "socket failed");
    error = 1;
  }
  return error;
}

int socket_bind() {
  server_address.sin6_family = AF_INET6;
  server_address.sin6_addr = in6addr_any;
  server_address.sin6_port = htons(8080);

  bindfd =
      bind(sockfd, (struct sockaddr *)&server_address, sizeof(server_address));
  if (bindfd != 0) {
    debug_print("%s\n", "bind failed");
    error = 1;
  }
  return error;
}

int socket_listen() {
  int listenfd = listen(sockfd, 5);
  if (listenfd != 0) {
    debug_print("listenfd %d\n", listenfd);
    error = 1;
  }
  return error;
}

int socket_close() {
  close(sockfd);
  return error;
}

int socket_loop() {
  while (1) {
    clientfd = accept(sockfd, NULL, NULL);
    if (clientfd != -1) {
      char buf[8192];
      char *lastpos;
      int size;
      close(sockfd);

      while (1) {
        size = recv(clientfd, buf, 8192, 0);
        if (size == 0) {
          break;
        }
        lastpos = strchr(buf, '\n');
        send(clientfd, buf, lastpos + 1 - buf, 0);
      }
      close(clientfd);
    }
  }
}
