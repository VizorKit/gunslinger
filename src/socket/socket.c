#include "./socket.h"
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "../debug/debug.h"
#include <arpa/inet.h>

static int sockfd;
static struct sockaddr_in server_address;
static int bindfd;
static int error = 0;

int socket_init() {
  sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);

  if(sockfd == -1) {
    debug_print("%s\n", "socket failed");
    error = 1;
  }
  return error;
}

int socket_bind() {
  server_address.sin_family = AF_INET6;
  server_address.sin_addr.s_addr = htonl(INADDR_ANY);
  server_address.sin_port = htons(8080);

  bindfd = bind(sockfd, (struct sockaddr*)&server_address, sizeof(server_address));
  if(bindfd != 0) {
    debug_print("%s\n", "bind failed");
    error = 1;
  }
  return error;
}


