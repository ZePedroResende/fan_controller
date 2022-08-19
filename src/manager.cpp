#include "manager.h"

#include <string.h>

#include <fstream>
#include <sstream>

namespace fan_controller {

Manager::Manager() : Reader() {}

void Manager::setCoolerBoost(enum CoolerBoostStatus coolerboost) {
  if (this->coolerBoost() == coolerboost) return;

  try {
    std::fstream file;
    openFileRW(file);

    unsigned char data = 0;

    if (coolerboost == CoolerBoostStatus::ON) {
      data |= static_cast<unsigned char>(CoolerBoostON);
    } else if (coolerboost == CoolerBoostStatus::OFF) {
      data &= static_cast<unsigned char>(CoolerBoostOFF) | 0x0F;
    } else {
      return;
    }

    file.seekp(CoolerBoost);
    file.write(reinterpret_cast<char *>(&data), sizeof(data));
    file.close();
  } catch (std::ios_base::failure &e) {
    throw std::runtime_error(std::string(strerror(errno)));
  }
}

void Manager::openFileRW(std::fstream &file) {
  file.exceptions(std::fstream::failbit);

  try {
    file.open(ECFilePath,
              std::fstream::in | std::fstream::out | std::fstream::binary);
  } catch (std::ios_base::failure &e) {
    throw std::runtime_error(std::string(strerror(errno)));
  }
}

}  // namespace fan_controller
