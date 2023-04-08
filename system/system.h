#ifndef MISC_H
#define MISC_H

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <chrono>
#include <sys/times.h>
#include <unistd.h>
#include <vector>

#include "shell.h"

typedef uint8_t Byte;        //< Definition of byte type
typedef uint16_t doubleByte; //< Definition of double byte type

namespace System {
namespace Misc {

/*!
  Make temproary file for firmware
\param[in] path Path to directory for temproary file
\param[in] fileStream Reference to std::ofstream
\return Path to temroary file, if error return "".
*/
std::string makeTemp(std::string path, std::ofstream &fileStream);

/*!
  Conversion from vector of bytes to string
\param[in] data Input vector of bytes
\return Output string
*/
std::string vectorToString(const std::vector<Byte> &data);

/*!
  Conversion from string to vector of bytes
\param[in] data Input string
\return Output vector of bytes
*/
std::vector<Byte> stringToVector(const std::string &data);

} // namespace Misc
} // namespace System

#endif // MISC_H
