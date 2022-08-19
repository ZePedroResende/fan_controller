#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace fan_controller {

static constexpr char  ECFilePath[]{"/sys/kernel/debug/ec/ec0/io"};

static constexpr int  CoolerBoost{0x98};

constexpr int  CoolerBoostON{0x80};
constexpr int  CoolerBoostOFF{0x00};

enum class CoolerBoostStatus { ON, OFF, Unknown };

struct cpu {
  static constexpr int  temp{0x68};
};

struct gpu {
  static constexpr int  temp{0x80};
};

}  // namespace fan_controller

#endif  // CONSTANTS_H
