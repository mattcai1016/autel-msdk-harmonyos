#ifndef IMEDIA_PLAYER_FACTORY_H
#define IMEDIA_PLAYER_FACTORY_H

#include <memory>
#include "IMediaPlayer.h"
#include "ErrorCode.h"

namespace AutelMobileSdk
{
class AUTELSDK_API IMediaPlayerFactory
{
public:
    IMediaPlayerFactory() {}
    virtual ~IMediaPlayerFactory() {}

public:
    virtual std::shared_ptr<IMediaPlayer> CreatePlayer() = 0;
    virtual std::shared_ptr<IMediaPlayer> GetPlayer(int playerId) = 0;
};
}

#endif // !_AUTEL_IPLAYER_H_
