#ifndef SYSTEMINFO_H
#define SYSTEMINFO_H

#include <string>
#include "shell.h"

namespace System {
namespace Info {

    std::string getMachineID(); //systemd machine-id
    std::string getUUID();

    std::string getSerialProduct();
    std::string getSerialChassis();
    std::string getSerialBoard();

} // namespace Info
} // namespace System
#endif // SYSTEMINFO_H
