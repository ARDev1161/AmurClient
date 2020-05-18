// Amur logic controller with ADB-0.42 board
#include "logiccontroller.h"

using namespace std;

int main(int argc, char *argv[])
{
    for(int i = 0;i < argc;i++)
        cout << argv[i] << endl;

    LogicController amurLogic;

    return 0;
}
