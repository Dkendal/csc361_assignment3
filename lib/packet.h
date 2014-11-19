#ifndef H_PACKET
#define H_PACKET value

#include <string>

#define DAT 0x01
#define ACK 0x02
#define SYN 0x04
#define FIN 0x08
#define RST 0x10

using namespace std;

class Packet
{
  public:
    Packet(unsigned char, unsigned short, unsigned short);
    ~Packet();


    string GetContent();
    void SetContent(string);

    bool IsAck();
    bool IsDat();
    bool IsFin();
    bool IsRst();
    bool IsSyn();

  private:
    unsigned char flags;
    unsigned short seqno;
    unsigned short ackno;
    unsigned short window_size;
    unsigned short payload_length;
    string content;
};
#endif
