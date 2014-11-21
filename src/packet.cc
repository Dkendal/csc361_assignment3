#include <string>
#include <sstream>
#include "packet.h"
#include <stdio.h>
#include <iostream>
#include <assert.h>

Packet::Packet(int flags, int seqno, int ackno, int window_size) :
  flags(flags), seqno(seqno), ackno(ackno), window_size(window_size), magic("UVicCSc361")
{
  SetContent("");
}

Packet::Packet(int flags, int seqno, int ackno, int window_size, string content = "") :
  flags(flags), seqno(seqno), ackno(ackno), window_size(window_size), magic("UVicCSc361")
{
  SetContent(content);
}

Packet::~Packet() {}

//_magic_ _type_ _seqno_ _ackno_ _len_ _win_\n\n
Packet::Packet(const char *str)
{
  const char *pat = "%s %d %d %d %d %d \n\n";
  char magic_c[100] = {};

  flags = ackno = seqno = window_size = content_length = 0;

  int retval = sscanf(str, pat, magic_c, &flags, &seqno, &ackno, &content_length,
      &window_size);

  magic = magic_c;

  assert(retval == 6);
 }

string Packet::GetContent()
{
  return this->content;
}

void Packet::SetContent(string content)
{
  this->content = content;
  this->content_length = content.length();
}

bool Packet::IsDat()
{
  return (flags & DAT) != 0;
}

bool Packet::IsFin()
{
  return (flags & FIN) != 0;
}

bool Packet::IsRst()
{
  return (flags & RST) != 0;
}

bool Packet::IsAck()
{
  return (flags & ACK) != 0;
}

bool Packet::IsSyn()
{
  return (flags & SYN) != 0;
}

// _magic_ _type_ _seqno_ _ackno_ _len_ _win_\n\n
string Packet::ToStr()
{
  stringstream ss;

  ss << magic << ' ' << flags << ' ' << seqno << ' ' << ackno
    << ' ' << content_length << ' ' << window_size << "\n\n";

  return ss.str();
}

int Packet::GetContentLength()
{
  return this->content_length;
}

int Packet::GetFlags()
{
  return this->flags;
}
