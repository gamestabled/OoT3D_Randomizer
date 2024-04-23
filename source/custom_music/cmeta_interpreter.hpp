#pragma once

#include <3ds.h>
#include <string>
#include <array>

class CMetaInterpreter {
  public:
    CMetaInterpreter(std::string path);
    ~CMetaInterpreter();

    const std::array<u32, 4>& GetBanks();
    u16 GetChannelFlags();
    u8 GetVolume();
    const std::string& GetCategory();

  private:
    std::array<u32, 4> banks;
    u16 channelFlags;
    u8 volume;
    std::string category;
};
