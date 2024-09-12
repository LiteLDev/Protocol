#pragma once

#include "protocol/deps/Utility/BinaryStream.h"
#include "protocol/network/Compressibility.h"
#include "protocol/network/IPacketHandlerDispatcher.h"
#include "protocol/network/MinecraftPacketIds.h"
#include "protocol/network/NetworkPeer.h"
#include "protocol/network/SubClientId.h"
#include "protocol/resources/PacketPriority.h"


namespace protocol {
class Packet {

  static const bool SHARE_WITH_HANDLER = false;
  PacketPriority mPriority = PacketPriority::Medium;
  NetworkPeer::Reliability mReliability =
      NetworkPeer::Reliability::ReliableOrdered;
  SubClientId mClientSubId = SubClientId::PrimaryClient;
  bool mIsHandled = false;
  NetworkPeer::PacketRecvTimepoint mReceiveTimepoint;
  IPacketHandlerDispatcher const *mHandler = nullptr;
  Compressibility mCompressible = Compressibility::Compressible;

public:
  [[nodiscard]] constexpr explicit Packet(
      PacketPriority priority = PacketPriority::Medium,
      NetworkPeer::Reliability reliability =
          NetworkPeer::Reliability::ReliableOrdered,
      SubClientId clientSubId = SubClientId::PrimaryClient,
      bool compress = true)
      : mPriority(priority), mReliability(reliability),
        mClientSubId(clientSubId),
        mCompressible(compress ? Compressibility::Compressible
                               : Compressibility::Incompressible) {}

  virtual ~Packet();
  virtual MinecraftPacketIds getId() const = 0;
  virtual std::string getName() const = 0;
  virtual bool checkSize(uint64, bool) const;
  virtual void write(class BinaryStream &stream) const = 0;
  virtual ExtendedStreamReadResult read(ReadOnlyBinaryStream &bitStream);
  virtual bool disallowBatching() const;
  virtual bool isValid() const;
  virtual StreamReadResult _read(ReadOnlyBinaryStream &stream) = 0;

  // void handle(class NetworkIdentifier const &source, class NetEventCallback
  // &callback,std::shared_ptr<class Packet> &packet);

  bool readNoHeader(ReadOnlyBinaryStream &, SubClientId const &);
  void writeWithHeader(SubClientId subClientId,
                       class BinaryStream &bitstream) const;
};
} // namespace protocol