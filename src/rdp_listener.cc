#include "rdp_listener.h"

#include <sys/socket.h>

#include <string>
#include <sstream>
#include <iostream>

#include "udp_socket.h"
#include "packet.h"
#include "sender_inet_addr.h"

using namespace std;
RDPListener::RDPListener(UDPSocket *socket, const char *addr, int port) :
  socket(socket), addr(addr), port(port) {
  }


Listener::State RDPListener::IntialState()
{
  return Listener::CLOSED;
}

void RDPListener::LogRequest(SenderInetAddr request) {
  Packet req(request.content);
  std::cout << "r "
    << request.addr << ":" << request.port << " "
    << this->addr << ":" << this->port << " "
    << req.GetType() << " "
    << req.GetSeqno() << "/" << req.GetAckno() << " "
    << req.GetContentLength() << "/" << req.GetWindowLength() << std::endl;
}

void RDPListener::LogResponse(Packet response, SenderInetAddr request) {
  std::cout << "s "
    << this->addr << ":" << this->port << " "
    << request.addr << ":" << request.port << " "
    << response.GetType() << " "
    << response.GetSeqno() << "/" << response.GetAckno() << " "
    << response.GetContentLength() << "/" << response.GetWindowLength() << std::endl;
}

void RDPListener::Start()
{
  stringstream ss("");
  bool connected = true;

  SenderInetAddr request = {};

  socket->Bind(this->addr, this->port);

  Packet *req;
  do {
    socket->RecvFrom(0, &request);

    LogRequest(request);

    req = new Packet(request.content);

    Packet *response;

    //TODO check for missing packets

    if (req->IsSyn() || req->IsFin()) {
      response = new Packet(ACK, 0, req->GetSeqno() + 1, 10240, "");
    }
    else if (req->IsDat()) {
      ss << req->GetContent();
      response = new Packet(ACK, 0, req->GetSeqno() + req->GetContentLength(),
          10240, "");
    }
    if (req->IsFin()) {
      connected = false;
    }

    LogResponse(*response, request);

    socket->Send(response->ToStr().c_str(), 0, request.addr, request.port);

    delete response;
  } while (!req->IsFin());

  std::cout << ss.str() << std::endl;
  ss.clear();
}
