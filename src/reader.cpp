#include "reader.h"

#include <cpuid.h>
#include <string.h>

#include <iostream>
#include <string>
#include <system_error>

namespace fan_controller {

Reader::Reader() {
  file_.exceptions(std::fstream::failbit);

  try {
    file_.open(ECFilePath, std::fstream::in | std::fstream::binary);
  } catch (std::ios_base::failure &e) {
    throw std::runtime_error(
        "An attempt to open the \"" + std::string(ECFilePath) +
        "\" file resulted in an error: " + std::string(strerror(errno)));
  }
}

Reader::~Reader() {}

int Reader::realtimeCPUTemp() {
  try {
    file_.seekg(cpu::temp);

    unsigned char data = 0;
    file_.read(reinterpret_cast<char *>(&data), sizeof(data));

    if (file_.gcount() != sizeof(data)) return -2;

    return static_cast<int>(data);
  } catch (std::ios_base::failure &e) {
    throw std::runtime_error("While reading realtime CPU temp: " +
                             std::string(strerror(errno)));
  }
}

int Reader::realtimeGPUTemp() {
  try {
    file_.seekg(gpu::temp);

    unsigned char data = 0;
    file_.read(reinterpret_cast<char *>(&data), sizeof(data));

    if (file_.gcount() != sizeof(data)) return -2;

    return static_cast<int>(data);
  } catch (std::ios_base::failure &e) {
    throw std::runtime_error("While reading realtime GPU temp: " +
                             std::string(strerror(errno)));
  }
}

CoolerBoostStatus Reader::coolerBoost() {
  try {
    file_.seekg(CoolerBoost);

    unsigned char data = 0;
    file_.read(reinterpret_cast<char *>(&data), sizeof(data));

    if (file_.gcount() != sizeof(data))
      throw std::runtime_error(std::string("While reading cooler boost: ") +
                               "read " + std::to_string(file_.gcount()) +
                               " byte(s), " + "should read " +
                               std::to_string(data) + "byte(s)");

    if (!(static_cast<int>(data) & CoolerBoostON))
      return CoolerBoostStatus::OFF;
    else
      return CoolerBoostStatus::ON;

  } catch (std::ios_base::failure &e) {
    throw std::runtime_error("While reading cooler boost: " +
                             std::string(strerror(errno)));
  }
}

}  // namespace fan_controller
