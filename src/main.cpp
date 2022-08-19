#include <cstring>
#include <iostream>

#include "./constants.h"
#include "./manager.h"
#include "./reader.h"

using namespace fan_controller;

int main(int argc, char* argv[]) {
  auto manager_ = new Manager();
  auto reader_ = new Reader();

  std::cout << "cpu temp " << reader_->realtimeCPUTemp() << std::endl;
  std::cout << "gpu temp " << reader_->realtimeGPUTemp() << std::endl;

  if (argc > 1) {
    auto is_on = strcmp(argv[1], "1") == 0;
    auto set_coolerboost = is_on ? CoolerBoostStatus::ON : CoolerBoostStatus::OFF;
    auto status = is_on ? "On" : "Off";

    std::cout << "Setting cooler boost " << status << std::endl;

    manager_->setCoolerBoost(set_coolerboost);
  }

  return 0;
}
