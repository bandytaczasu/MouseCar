#ifndef CONNECTIONCLASS_H
#define CONNECTIONCLASS_H

#include "myscene.h"
#include "myview.h"
#include "myrect.h"

class ConnectionClass
{

public:

    ConnectionClass();

    bool connectionEscape = false;

    void sendEscSign();

signals:
    void ConnectEscPress();
};

#endif // CONNECTIONCLASS_H
