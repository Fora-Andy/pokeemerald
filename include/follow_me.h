#ifndef FOLLOWER_EVENT_H
#define FOLLOWER_EVENT_H

extern struct FollowerAvatar gFollower;
void TrySpawnFollower(s16 x, s16 y, u8 nextDirection);
void DeleteFollower();
void MoveFollower(u8 nextMovementId);
u16 GetFollowerGraphicID();

struct FollowerAvatar
{
    bool8 active:1;
    u8 eventObjectId;
    u8 nextMovementId;
};

#define EVENT_OBJ_ID_FOLLOWER 0xFC

#endif // FOLLOWER_EVENT_H
