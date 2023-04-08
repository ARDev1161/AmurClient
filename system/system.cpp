#include "system.h"

namespace System {
namespace Misc {
std::string makeTemp(std::string path, std::ofstream &fileStream) {
  path += "XXXXXX"; // make template for mstemp
  std::vector<char> dst_path(path.begin(), path.end());
  dst_path.push_back('\0');

  int fd = mkstemp(
      &dst_path[0]); // make file with unique name from template, via mkstemp ()
  if (fd != -1) {
    path.assign(dst_path.begin(), dst_path.end() - 1);
    fileStream.open(path.c_str(), std::ios_base::trunc | std::ios_base::out);
    close(fd);
    return path;
  }
  return "";
}

std::string vectorToString(const std::vector<Byte> &data) {
  std::stringstream ss;
  for (auto it = data.begin(); it != data.end(); it++)
    ss << *it;
  return ss.str();
}

std::vector<Byte> stringToVector(const std::string &data) {
  std::vector<Byte> vec(data.begin(), data.end());
  return vec;
}

} // namespace Misc
} // namespace System
