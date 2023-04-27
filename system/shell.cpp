#include "shell.h"

namespace System {
namespace Shell {

std::string exec(const std::string &cmd) {
  std::array<char, 128> buffer;
  std::string result;
  std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"),
                                                pclose);
  if (!pipe) {
    throw std::runtime_error("popen() failed!");
  }
  while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
    result += buffer.data();
  }

  // Removing last \n
  if(result.back() == '\n')
    result.pop_back();

  return result;
}

std::string suspendOnTime(int seconds, int mode) {
  std::string suspend;
  switch (mode) {
  case 1:
    suspend = "-m mem";
    break;
  case 2:
    suspend = "-m disk";
    break;
  case 3:
    suspend = "-m off";
    break;
  case 0:
    suspend = "";
    break;
  default:
    std::cerr << "Bad SuspendMode" << std::endl;
    return "";
  }
  std::string cmd =
      "rtcwake " + suspend + " -s " +
      std::to_string(seconds); // -s - on seconds, -t - in certain time
  return exec(cmd);
}

std::string suspendOnTime(int seconds, SuspendMode mode) {
  std::string suspend;
  switch (mode) {
  case RAM_MEMORY:
    suspend = "-m mem";
    break;
  case DISK_HIBERNATE:
    suspend = "-m disk";
    break;
  case SHUTDOWN:
    suspend = "-m off";
    break;
  case WAKEUP_WITHOUT_SLEEPENG:
    suspend = "";
    break;
  default:
    std::cerr << "Bad SuspendMode" << std::endl;
    return "";
  }
  std::string cmd =
      "rtcwake " + suspend + " -s " +
      std::to_string(seconds); // -s - on seconds, -t - in certain time
  return exec(cmd);
}

void reboot() { exec("reboot"); }

void poweroff() { exec("poweroff"); }

} // namespace Shell
} // namespace System
