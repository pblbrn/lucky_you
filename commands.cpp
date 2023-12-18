#include "commands.h"
#define PATH_BATT_CHARGE_NOW "/sys/class/power_supply/BAT0/subsystem/BAT0/status"
#include <QObject>

Commands::Commands()
{

}

//void Commands::interpretMSG()
void Commands::chargeStatus()
{
    std::string battStatus;
    std::ifstream myfile (PATH_BATT_CHARGE_NOW);
    while(myfile)    {
        myfile >> battStatus;
    }
    QString mytext = QString::fromStdString(battStatus);
   // QString mytext = QString::fromStdString(battStatus);
    //send
}
