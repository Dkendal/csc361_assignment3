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
    Packet(string);
    Packet(int flags, int seqno, int ackno, int window_size, string content);
    ~Packet();

    string GetContent();
    void SetContent(string);

    int GetFlags();
    int GetAckno() { return ackno; }
    int GetSeqno() { return seqno; }
    int GetContentLength();
    int GetWindowLength() { return window_size; }
    string GetType();


    bool IsAck();
    bool IsDat();
    bool IsFin();
    bool IsRst();
    bool IsSyn();

    // "_magic_ _type_ _seqno_ _ackno_ _len_ _win_\n\n"
    string ToStr();

  private:
    string magic;
    int flags;
    int seqno;
    int ackno;
    short content_length;
    int window_size;
    string content;
};
#endif
