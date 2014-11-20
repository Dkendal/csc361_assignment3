#ifndef RDP_H
#define RDP_H
#include <string>

using namespace std;
class RDP
{
public:
  RDP(const char*, const char*);
  //~RDP();
  void Send(string content);
  void Recv();

private:
  const char *ip, *port;
  /* data */
};
#endif
