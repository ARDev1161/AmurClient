#ifndef SHELL_H
#define SHELL_H

#include <array>
#include <iostream>
#include <memory>

namespace System {
namespace Shell {

/*!
  Execute command in shell & get result.
\param[in] cmd String of running command
\return Result string of executing command.
*/
std::string exec(const std::string &cmd);

/// Available suspend modes
enum SuspendMode {
  RAM_MEMORY,     ///< Suspend mode that saved data in RAM. ACPI S3 state
  DISK_HIBERNATE, ///< Suspend mode that saved data to HDD (known as
                  ///< hibernating). ACPI S4 state
  SHUTDOWN,       ///< Just shutdown. ACPI S5 state
  WAKEUP_WITHOUT_SLEEPENG ///< Setup only wakeup time, without any ACPI state
                          ///< change
};

/*!
  Suspend system.
\param[in] seconds Time for suspend, if used RAM_MEMORY or DISK_HIBERNATE mode.
default - 60 seconds. \param[in] mode Suspend mode, that defining of ACPI state.
\return Result string of executing suspend command.
*/
std::string suspendOnTime(int seconds = 60, SuspendMode mode = RAM_MEMORY);

/*!
  Suspend system.
\param[in] seconds Time for suspend, if used RAM_MEMORY or DISK_HIBERNATE mode.
default - 60 seconds. \param[in] mode Suspend mode, that defining of ACPI state.
\return Result string of executing suspend command.
*/
std::string suspendOnTime(int seconds = 60, int mode = 1);

/*!
  Reboot system
*/
void reboot();

/*!
  Poweroff system
*/
void poweroff();

} // namespace Shell
} // namespace System

#endif // SHELL_H
