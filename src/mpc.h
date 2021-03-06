#ifndef MPC_H
#define MPC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "mediakey.h"

#define MPC_META_SIZE           128
#define MPC_NAME_SIZE            64

typedef uint16_t MpcFlags;
enum {
    MPC_FLAG_UPDATE_META        = 0x0001,
    MPC_FLAG_UPDATE_ELAPSED     = 0x0002,
    MPC_FLAG_UPDATE_DURATION    = 0x0004,
    MPC_FLAG_UPDATE_STATUS      = 0x0008,
    MPC_FLAG_UPDATE_NAME        = 0x0100,
    MPC_FLAG_UPDATE_TRACKNUM    = 0x0200,
};

typedef uint16_t MpcStatus;
enum {
    MPC_PLAYING = 0x0001,
    MPC_PAUSED  = 0x0002,
    MPC_REPEAT  = 0x0010,
    MPC_SINGLE  = 0x0020,
    MPC_RANDOM  = 0x0040,
    MPC_CONSUME = 0x0080,
};

typedef struct {
    uint16_t flags;
    MpcStatus status;
    int32_t trackNum;
    int32_t elapsed;
    int32_t duration;
    char meta[MPC_META_SIZE];
    char name[MPC_NAME_SIZE];
} Mpc;

void mpcInit(void);
Mpc *mpcGet(void);

void mpcSyncRequest(void);

void mpcSendDigit(uint8_t dig);
void mpcFinishDigitInput(void);

void mpcLoadPlaylist(const char *name);
void mpcPlayTrack(int16_t num);

void mpcSendMediaKey(MediaKey key);

void mpcGetData(void);

#ifdef __cplusplus
}
#endif

#endif // MPC_H
