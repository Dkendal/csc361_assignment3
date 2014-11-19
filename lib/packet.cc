#include <string>
#include "packet.h"

Packet::Packet(unsigned char flags, unsigned short seqno, unsigned short ackno) :
  flags(flags), seqno(seqno), ackno(ackno) {
}

string Packet::GetContent()
{
  return this->content;
}

void Packet::SetContent(string content)
{
  this->content = content;
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

// string Packet::GetChecksum()
// {
//   return this->checksum;
// }
//
// void Packet::SetChecksum(string content)
// {
//   this->checksum = checksum;
// }
