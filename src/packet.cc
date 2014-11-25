#include <string>
#include <sstream>
#include "packet.h"
#include <stdio.h>
#include <iostream>
#include <assert.h>

Packet::Packet(int flags, int seqno, int ackno, int window_size, string content = "") :
magic("UVicCSc361"), flags(flags), seqno(seqno), ackno(ackno), window_size(window_size) {
  SetContent(content);
}

Packet::~Packet() {}

//_magic_ _type_ _seqno_ _ackno_ _len_ _win_\n\n
Packet::Packet(string str) {
  const char *pat = "%s %d %d %d %d %d\n\n%s";
  char magic_c[100] = {};
  char buff[1100] = {};
  content = "";

  flags = ackno = seqno = window_size = content_length = 0;

  int retval = sscanf(str.c_str(), pat, magic_c, &flags, &seqno, &ackno, &content_length,
      &window_size, buff);

  magic = magic_c;

  if(retval == 7) {
    content = buff;
  }
}

string Packet::GetType() {
  switch (this->flags) {
    case SYN:
      return "SYN";
    case ACK:
      return "ACK";
    case DAT:
      return "DAT";
    case FIN:
      return "FIN";
    case RST:
      return "RST";
    default:
      return "ERR";
  }
}
string Packet::GetContent() {
  return this->content;
}

void Packet::SetContent(string content) {
  this->content = content;
  this->content_length = content.length();
}

bool Packet::IsDat() {
  return (flags & DAT) != 0;
}

bool Packet::IsFin() {
  return (flags & FIN) != 0;
}

bool Packet::IsRst() {
  return (flags & RST) != 0;
}

bool Packet::IsAck() {
  return (flags & ACK) != 0;
}

bool Packet::IsSyn() {
  return (flags & SYN) != 0;
}

// _magic_ _type_ _seqno_ _ackno_ _len_ _win_\n\n
string Packet::ToStr() {
  stringstream ss;

  ss << magic << ' ' << flags << ' ' << seqno << ' ' << ackno
    << ' ' << content_length << ' ' << window_size << "\n\n" << content;

  return ss.str();
}

int Packet::GetContentLength() {
  return this->content_length;
}

int Packet::GetFlags() {
  return this->flags;
}
