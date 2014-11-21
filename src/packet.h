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
    Packet(const char *);
    Packet(int, int, int, int);
    Packet(int, int, int, int, string);
    ~Packet();

    string GetContent();
    void SetContent(string);

    int GetFlags();

    int GetContentLength();

    bool IsAck();
    bool IsDat();
    bool IsFin();
    bool IsRst();
    bool IsSyn();

    string ToStr();

    int seqno;
    int ackno;
    int window_size;
    string magic;

  private:
    int flags;
    short content_length;
    string content;
};
#endif
