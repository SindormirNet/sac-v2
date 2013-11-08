#ifndef SAC_H
#define SAC_H
#include "mainwindow.h"

class Vacio {
private:
    int id;

public:
    QRectF position;
    QPen aspect;
};

typedef struct {
  int src;
  int dst;
  int type;
  int pos;
  int vel;
  int gotoexit;
  int flags;
  int ack;
  int nack;
} sac_datagram;

#endif // SAC_H
