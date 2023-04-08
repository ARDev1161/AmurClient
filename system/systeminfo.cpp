#include "systeminfo.h"

namespace System {
namespace Info {

std::string getMachineID()
{
    return Shell::exec("cat /etc/machine-id");
}

std::string getUUID()
{
    return Shell::exec("sudo cat /sys/class/dmi/id/product_uuid");
}

std::string getSerialProduct()
{
    return Shell::exec("sudo cat /sys/class/dmi/id/product_serial");
}

std::string getSerialChassis()
{
    return Shell::exec("sudo cat /sys/class/dmi/id/chassis_serial");
}

std::string getSerialBoard()
{
    return Shell::exec("sudo cat /sys/class/dmi/id/board_serial");
}

} // namespace Info
} // namespace System
