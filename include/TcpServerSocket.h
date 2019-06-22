#ifndef __TCPSERVERSOCKET__
#define __TCPSERVERSOCKET__

#include "TcpSocket.h"

class TcpServerSocket : public TcpSocket{
  public:
    
  public:
    TcpServerSocket();
    ~TcpServerSocket();

    int start();
    void listen();
};


#endif // __TCPSERVERSOCKET__
