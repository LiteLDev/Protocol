#pragma once
#include "protocol/deps/StdInt.h"

namespace protocol {
enum class LogAreaID : int32 {
  All = 0x0,
  Platform = 0x1,
  Entity = 0x2,
  Database = 0x3,
  Gui = 0x4,
  System = 0x5,
  Network = 0x6,
  Render = 0x7,
  Memory = 0x8,
  Animation = 0x9,
  Input = 0xA,
  Level = 0xB,
  Server = 0xC,
  Dlc = 0xD,
  Physics = 0xE,
  File = 0xF,
  Storage = 0x10,
  Realms = 0x11,
  Realmsapi = 0x12,
  Xboxlive = 0x13,
  Usermanager = 0x14,
  Xsapi = 0x15,
  Perf = 0x16,
  Telemetry = 0x17,
  Blocks = 0x18,
  Raknet = 0x19,
  Gameface = 0x1A,
  Sound = 0x1B,
  Interactive = 0x1C,
  Scripting = 0x1D,
  Playfab = 0x1E,
  Automation = 0x1F,
  Persona = 0x20,
  Texture = 0x21,
  Assetpackages = 0x22,
  Items = 0x23,
  Services = 0x24,
  Volumes = 0x25,
  Loottable = 0x26,
  Sidebar = 0x27,
  Localization = 0x28,
  Movement = 0x29,
  Liveevents = 0x2A,
  Editor = 0x2B,
  Unknown = 0x2C,
  Invalid = 10000,
  Count,
};
}