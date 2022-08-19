#ifndef MANAGER_H
#define MANAGER_H

#include "constants.h"
#include "reader.h"

namespace fan_controller {

class Manager : public Reader {
 public:
  Manager();
  ~Manager() = default;

  void setCoolerBoost(enum CoolerBoostStatus coolerboost);

 private:
  void openFileRW(std::fstream &file);
};

}  // namespace fan_controller

#endif  // MANAGER_H
