#ifndef READER_H
#define READER_H

#include <fstream>
#include <vector>

#include "constants.h"

namespace fan_controller {

class Reader {
 public:
  Reader();
  ~Reader();

  // CPU
  int realtimeCPUTemp();

  // GPU
  int realtimeGPUTemp();

  enum CoolerBoostStatus coolerBoost();

 private:
  std::fstream file_;
};

}  // namespace fan_controller

#endif  // READER_H
