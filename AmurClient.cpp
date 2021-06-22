// Amur logic controller with ADB-0.42 board
#include "logiccontroller.h"

char const* build_date() // Return date of compilation this application
{
    return __DATE__;
}

char const* build_time() // Return time of compilation this application
{
    return __TIME__;
}

int main(int argc, char *argv[])
{
    std::cout << "Build on " << build_date() << "\t " << build_time() << std::endl;


    for(int i = 0;i < argc;i++)
        std::cout << argv[i] << std::endl;

    LogicController amurLogic;

    return 0;
}
