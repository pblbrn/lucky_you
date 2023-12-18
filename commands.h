#ifndef COMMANDS_H
#define COMMANDS_H

#include <fstream>

enum COMMANDS{ChargeStatus, Speak, Mugshot};

class Commands
{
public:
    Commands();
    void chargeStatus();
    void speak();
    void mugshot();
};

#endif // COMMANDS_H
