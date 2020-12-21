#include "../src/socket/socket.h"
#include "../src/debug/debug.h"
#include <assert.h>

int main() {
  assert(socket_init() == 0);
  assert(socket_bind() == 0);
}
