#include <stdlib.h>
#include <iostream>

#define CONTENT_INDEX 3
int main(int argc, const char *argv[])
{
  bool sending = argc >= CONTENT_INDEX;

  if (argc <= 2) {
    std::cerr << "arguments: host_ip host_port [content]" << std::endl;
    exit(-1);
  }

  //RDP rdp(argv[1], argv[2]);

  return 0;
}
