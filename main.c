#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

void ping(int s, char *message) {
  char buf[8192];

  strncpy(buf, message, sizeof(buf));
  send(s, buf, strlen(buf), 0);
  recv(s, buf, 8192, 0);
  strtok(buf, "\n");
  puts(buf);
}

int main() {
  int s;
  struct sockaddr_in6 addr;

  s = socket(AF_INET6, SOCK_STREAM, 0);
  addr.sin6_family = AF_INET6;
  addr.sin6_port = htons(8080);
  printf("inet_pton\n");
  inet_pton(AF_INET6, "::1", &addr.sin6_addr);
  connect(s, (struct sockaddr *)&addr, sizeof(addr));
  printf("connected\n");
  ping(s, "hoge\n");
  ping(s, "fuga\n");
  ping(s, "piyo\n");
  printf("\n done.\n");
  close(s);
  return 0;
}
