#ifndef H_PACKET
#define H_PACKET value

#include <string>

#define DAT 0x01
#define ACK 0x02
#define SYN 0x04
#define FIN 0x08
#define RST 0x1f

using namespace std;

class Packet
{
  public:
    Packet(unsigned int, unsigned int, unsigned int);
    ~Packet();


    string GetContent();
    void SetContent(string);
    string GetChecksum();
    void SetChecksum(string);

    bool IsAck();
    bool IsDat();
    bool IsFin();
    bool IsRst();
    bool IsSyn();

  private:
    unsigned int flags;
    unsigned int seqno;
    unsigned int ackno;
    unsigned int length;
    string checksum;
    string content;
};
#endif
