#include "global.h"
#include "alloc.h"
#include "battle_pyramid.h"
#include "berry.h"
#include "decoration.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "event_scripts.h"
#include "faraway_island.h"
#include "field_camera.h"
#include "field_effect.h"
#include "field_effect_helpers.h"
#include "field_player_avatar.h"
#include "field_weather.h"
#include "fieldmap.h"
#include "follow_me.h"
#include "mauville_old_man.h"
#include "metatile_behavior.h"
#include "overworld.h"
#include "palette.h"
#include "random.h"
#include "sprite.h"
#include "task.h"
#include "trainer_see.h"
#include "trainer_hill.h"
#include "util.h"
#include "constants/event_object_movement_constants.h"
#include "constants/event_objects.h"
#include "constants/field_effects.h"
#include "constants/items.h"

// this file was known as evobjmv.c in Game Freak's original source

#define movement_type_def(setup, table) \
static u8 setup##_callback(struct EventObject *, struct Sprite *);\
void setup(struct Sprite *sprite)\
{\
    UpdateEventObjectCurrentMovement(&gEventObjects[sprite->data[0]], sprite, setup##_callback);\
}\
static u8 setup##_callback(struct EventObject *eventObject, struct Sprite *sprite)\
{\
    return table[sprite->data[1]](eventObject, sprite);\
}

#define movement_type_empty_callback(setup) \
static u8 setup##_callback(struct EventObject *, struct Sprite *);\
void setup(struct Sprite *sprite)\
{\
    UpdateEventObjectCurrentMovement(&gEventObjects[sprite->data[0]], sprite, setup##_callback);\
}\
static u8 setup##_callback(struct EventObject *eventObject, struct Sprite *sprite)\
{\
    return 0;\
}

EWRAM_DATA struct LockedAnimEventObjects *gLockedAnimEventObjects = {0};

static void MoveCoordsInDirection(u32, s16 *, s16 *, s16, s16);
static bool8 EventObjectExecSingleMovementAction(struct EventObject *, struct Sprite *);
static void SetMovementDelay(struct Sprite *, s16);
static bool8 WaitForMovementDelay(struct Sprite *);
static u8 GetCollisionInDirection(struct EventObject *, u8);
static u32 state_to_direction(u8, u32, u32);
static void TryEnableEventObjectAnim(struct EventObject *, struct Sprite *);
static void EventObjectExecHeldMovementAction(struct EventObject *, struct Sprite *);
static void UpdateEventObjectSpriteAnimPause(struct EventObject *, struct Sprite *);
static bool8 IsCoordOutsideEventObjectMovementRange(struct EventObject *, s16, s16);
static bool8 IsMetatileDirectionallyImpassable(struct EventObject *, s16, s16, u8);
static bool8 DoesObjectCollideWithObjectAt(struct EventObject *, s16, s16);
static void sub_8096530(struct EventObject *, struct Sprite *);
static void UpdateEventObjSpriteVisibility(struct EventObject *, struct Sprite *);
static void EventObjectUpdateMetatileBehaviors(struct EventObject*);
static void GetGroundEffectFlags_Reflection(struct EventObject*, u32*);
static void GetGroundEffectFlags_TallGrassOnSpawn(struct EventObject*, u32*);
static void GetGroundEffectFlags_LongGrassOnSpawn(struct EventObject*, u32*);
static void GetGroundEffectFlags_SandHeap(struct EventObject*, u32*);
static void GetGroundEffectFlags_ShallowFlowingWater(struct EventObject*, u32*);
static void GetGroundEffectFlags_ShortGrass(struct EventObject*, u32*);
static void GetGroundEffectFlags_HotSprings(struct EventObject*, u32*);
static void GetGroundEffectFlags_TallGrassOnBeginStep(struct EventObject*, u32*);
static void GetGroundEffectFlags_LongGrassOnBeginStep(struct EventObject*, u32*);
static void GetGroundEffectFlags_Tracks(struct EventObject*, u32*);
static void GetGroundEffectFlags_Puddle(struct EventObject*, u32*);
static void GetGroundEffectFlags_Ripple(struct EventObject*, u32*);
static void GetGroundEffectFlags_Seaweed(struct EventObject*, u32*);
static void GetGroundEffectFlags_JumpLanding(struct EventObject*, u32*);
static u8 EventObjectCheckForReflectiveSurface(struct EventObject*);
static u8 GetReflectionTypeByMetatileBehavior(u32);
static void InitObjectPriorityByZCoord(struct Sprite *sprite, u8 z);
static void EventObjectUpdateSubpriority(struct EventObject*, struct Sprite*);
static void DoTracksGroundEffect_None(struct EventObject*, struct Sprite*, u8);
static void DoTracksGroundEffect_Footprints(struct EventObject*, struct Sprite*, u8);
static void DoTracksGroundEffect_BikeTireTracks(struct EventObject*, struct Sprite*, u8);
static void DoRippleFieldEffect(struct EventObject*, struct Sprite*);
static void DoGroundEffects_OnSpawn(struct EventObject*, struct Sprite*);
static void DoGroundEffects_OnBeginStep(struct EventObject*, struct Sprite*);
static void DoGroundEffects_OnFinishStep(struct EventObject*, struct Sprite*);
static void sub_8097D68(struct Sprite*);
static void ApplyLevitateMovement(u8);
static bool8 MovementType_Disguise_Callback(struct EventObject *, struct Sprite *);
static bool8 MovementType_Hidden_Callback(struct EventObject *, struct Sprite *);
static void CreateReflectionEffectSprites(void);
static u8 GetEventObjectIdByLocalId(u8);
static u8 GetEventObjectIdByLocalIdAndMapInternal(u8, u8, u8);
static bool8 GetAvailableEventObjectId(u16, u8, u8, u8 *);
static void SetEventObjectDynamicGraphicsId(struct EventObject *);
static void RemoveEventObjectInternal(struct EventObject *);
static u16 GetEventObjectFlagIdByEventObjectId(u8);
static void UpdateEventObjectVisibility(struct EventObject *, struct Sprite *);
static void MakeObjectTemplateFromEventObjectTemplate(struct EventObjectTemplate *, struct SpriteTemplate *, const struct SubspriteTable **);
static void GetEventObjectMovingCameraOffset(s16 *, s16 *);
static struct EventObjectTemplate *GetEventObjectTemplateByLocalIdAndMap(u8, u8, u8);
static void RemoveEventObjectIfOutsideView(struct EventObject *);
static void sub_808E1B8(u8, s16, s16);
static void SetPlayerAvatarEventObjectIdAndObjectId(u8, u8);
static void sub_808E38C(struct EventObject *);
static u8 sub_808E8F4(const struct SpritePalette *);
static u16 FindEventObjectPaletteIndexByTag(u16);
static void sub_808EAB0(u16, u8);
static bool8 EventObjectDoesZCoordMatch(struct EventObject *, u8);
static void ObjectCB_CameraObject(struct Sprite *);
static void CameraObject_0(struct Sprite *);
static void CameraObject_1(struct Sprite *);
static void CameraObject_2(struct Sprite *);
static struct EventObjectTemplate *FindEventObjectTemplateByLocalId(u8 localId, struct EventObjectTemplate *templates, u8 count);
static void ClearEventObjectMovement(struct EventObject *, struct Sprite *);
static void EventObjectSetSingleMovement(struct EventObject *, struct Sprite *, u8);
static void oamt_npc_ministep_reset(struct Sprite *, u8, u8);
static void UpdateEventObjectSpriteSubpriorityAndVisibility(struct Sprite *);

const struct SpriteTemplate gCameraSpriteTemplate = {0, 0xFFFF, &gDummyOamData, gDummySpriteAnimTable, NULL, gDummySpriteAffineAnimTable, ObjectCB_CameraObject};

void (*const gCameraObjectFuncs[])(struct Sprite *) = {
    CameraObject_0,
    CameraObject_1,
    CameraObject_2,
};

#include "data/field_event_obj/event_object_graphics.h"

// movement type callbacks
static void (*const sMovementTypeCallbacks[])(struct Sprite *) =
{
    [MOVEMENT_TYPE_NONE] = MovementType_None,
    [MOVEMENT_TYPE_LOOK_AROUND] = MovementType_LookAround,
    [MOVEMENT_TYPE_WANDER_AROUND] = MovementType_WanderAround,
    [MOVEMENT_TYPE_WANDER_UP_AND_DOWN] = MovementType_WanderUpAndDown,
    [MOVEMENT_TYPE_WANDER_DOWN_AND_UP] = MovementType_WanderUpAndDown,
    [MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT] = MovementType_WanderLeftAndRight,
    [MOVEMENT_TYPE_WANDER_RIGHT_AND_LEFT] = MovementType_WanderLeftAndRight,
    [MOVEMENT_TYPE_FACE_UP] = MovementType_FaceDirection,
    [MOVEMENT_TYPE_FACE_DOWN] = MovementType_FaceDirection,
    [MOVEMENT_TYPE_FACE_LEFT] = MovementType_FaceDirection,
    [MOVEMENT_TYPE_FACE_RIGHT] = MovementType_FaceDirection,
    [MOVEMENT_TYPE_PLAYER] = MovementType_Player,
    [MOVEMENT_TYPE_BERRY_TREE_GROWTH] = MovementType_BerryTreeGrowth,
    [MOVEMENT_TYPE_FACE_DOWN_AND_UP] = MovementType_FaceDownAndUp,
    [MOVEMENT_TYPE_FACE_LEFT_AND_RIGHT] = MovementType_FaceLeftAndRight,
    [MOVEMENT_TYPE_FACE_UP_AND_LEFT] = MovementType_FaceUpAndLeft,
    [MOVEMENT_TYPE_FACE_UP_AND_RIGHT] = MovementType_FaceUpAndRight,
    [MOVEMENT_TYPE_FACE_DOWN_AND_LEFT] = MovementType_FaceDownAndLeft,
    [MOVEMENT_TYPE_FACE_DOWN_AND_RIGHT] = MovementType_FaceDownAndRight,
    [MOVEMENT_TYPE_FACE_DOWN_UP_AND_LEFT] = MovementType_FaceDownUpAndLeft,
    [MOVEMENT_TYPE_FACE_DOWN_UP_AND_RIGHT] = MovementType_FaceDownUpAndRight,
    [MOVEMENT_TYPE_FACE_UP_LEFT_AND_RIGHT] = MovementType_FaceUpRightAndLeft,
    [MOVEMENT_TYPE_FACE_DOWN_LEFT_AND_RIGHT] = MovementType_FaceDownRightAndLeft,
    [MOVEMENT_TYPE_ROTATE_COUNTERCLOCKWISE] = MovementType_RotateCounterclockwise,
    [MOVEMENT_TYPE_ROTATE_CLOCKWISE] = MovementType_RotateClockwise,
    [MOVEMENT_TYPE_WALK_UP_AND_DOWN] = MovementType_WalkBackAndForth,
    [MOVEMENT_TYPE_WALK_DOWN_AND_UP] = MovementType_WalkBackAndForth,
    [MOVEMENT_TYPE_WALK_LEFT_AND_RIGHT] = MovementType_WalkBackAndForth,
    [MOVEMENT_TYPE_WALK_RIGHT_AND_LEFT] = MovementType_WalkBackAndForth,
    [MOVEMENT_TYPE_WALK_SEQUENCE_UP_RIGHT_LEFT_DOWN] = MovementType_WalkSequenceUpRightLeftDown,
    [MOVEMENT_TYPE_WALK_SEQUENCE_RIGHT_LEFT_DOWN_UP] = MovementType_WalkSequenceRightLeftDownUp,
    [MOVEMENT_TYPE_WALK_SEQUENCE_DOWN_UP_RIGHT_LEFT] = MovementType_WalkSequenceDownUpRightLeft,
    [MOVEMENT_TYPE_WALK_SEQUENCE_LEFT_DOWN_UP_RIGHT] = MovementType_WalkSequenceLeftDownUpRight,
    [MOVEMENT_TYPE_WALK_SEQUENCE_UP_LEFT_RIGHT_DOWN] = MovementType_WalkSequenceUpLeftRightDown,
    [MOVEMENT_TYPE_WALK_SEQUENCE_LEFT_RIGHT_DOWN_UP] = MovementType_WalkSequenceLeftRightDownUp,
    [MOVEMENT_TYPE_WALK_SEQUENCE_DOWN_UP_LEFT_RIGHT] = MovementType_WalkSequenceDownUpLeftRight,
    [MOVEMENT_TYPE_WALK_SEQUENCE_RIGHT_DOWN_UP_LEFT] = MovementType_WalkSequenceRightDownUpLeft,
    [MOVEMENT_TYPE_WALK_SEQUENCE_LEFT_UP_DOWN_RIGHT] = MovementType_WalkSequenceLeftUpDownRight,
    [MOVEMENT_TYPE_WALK_SEQUENCE_UP_DOWN_RIGHT_LEFT] = MovementType_WalkSequenceUpDownRightLeft,
    [MOVEMENT_TYPE_WALK_SEQUENCE_RIGHT_LEFT_UP_DOWN] = MovementType_WalkSequenceRightLeftUpDown,
    [MOVEMENT_TYPE_WALK_SEQUENCE_DOWN_RIGHT_LEFT_UP] = MovementType_WalkSequenceDownRightLeftUp,
    [MOVEMENT_TYPE_WALK_SEQUENCE_RIGHT_UP_DOWN_LEFT] = MovementType_WalkSequenceRightUpDownLeft,
    [MOVEMENT_TYPE_WALK_SEQUENCE_UP_DOWN_LEFT_RIGHT] = MovementType_WalkSequenceUpDownLeftRight,
    [MOVEMENT_TYPE_WALK_SEQUENCE_LEFT_RIGHT_UP_DOWN] = MovementType_WalkSequenceLeftRightUpDown,
    [MOVEMENT_TYPE_WALK_SEQUENCE_DOWN_LEFT_RIGHT_UP] = MovementType_WalkSequenceDownLeftRightUp,
    [MOVEMENT_TYPE_WALK_SEQUENCE_UP_LEFT_DOWN_RIGHT] = MovementType_WalkSequenceUpLeftDownRight,
    [MOVEMENT_TYPE_WALK_SEQUENCE_DOWN_RIGHT_UP_LEFT] = MovementType_WalkSequenceDownRightUpLeft,
    [MOVEMENT_TYPE_WALK_SEQUENCE_LEFT_DOWN_RIGHT_UP] = MovementType_WalkSequenceLeftDownRightUp,
    [MOVEMENT_TYPE_WALK_SEQUENCE_RIGHT_UP_LEFT_DOWN] = MovementType_WalkSequenceRightUpLeftDown,
    [MOVEMENT_TYPE_WALK_SEQUENCE_UP_RIGHT_DOWN_LEFT] = MovementType_WalkSequenceUpRightDownLeft,
    [MOVEMENT_TYPE_WALK_SEQUENCE_DOWN_LEFT_UP_RIGHT] = MovementType_WalkSequenceDownLeftUpRight,
    [MOVEMENT_TYPE_WALK_SEQUENCE_LEFT_UP_RIGHT_DOWN] = MovementType_WalkSequenceLeftUpRightDown,
    [MOVEMENT_TYPE_WALK_SEQUENCE_RIGHT_DOWN_LEFT_UP] = MovementType_WalkSequenceRightDownLeftUp,
    [MOVEMENT_TYPE_COPY_PLAYER] = MovementType_CopyPlayer,
    [MOVEMENT_TYPE_COPY_PLAYER_OPPOSITE] = MovementType_CopyPlayer,
    [MOVEMENT_TYPE_COPY_PLAYER_COUNTERCLOCKWISE] = MovementType_CopyPlayer,
    [MOVEMENT_TYPE_COPY_PLAYER_CLOCKWISE] = MovementType_CopyPlayer,
    [MOVEMENT_TYPE_TREE_DISGUISE] = MovementType_TreeDisguise,
    [MOVEMENT_TYPE_MOUNTAIN_DISGUISE] = MovementType_MountainDisguise,
    [MOVEMENT_TYPE_COPY_PLAYER_IN_GRASS] = MovementType_CopyPlayerInGrass,
    [MOVEMENT_TYPE_COPY_PLAYER_OPPOSITE_IN_GRASS] = MovementType_CopyPlayerInGrass,
    [MOVEMENT_TYPE_COPY_PLAYER_COUNTERCLOCKWISE_IN_GRASS] = MovementType_CopyPlayerInGrass,
    [MOVEMENT_TYPE_COPY_PLAYER_CLOCKWISE_IN_GRASS] = MovementType_CopyPlayerInGrass,
    [MOVEMENT_TYPE_HIDDEN] = MovementType_Hidden,
    [MOVEMENT_TYPE_WALK_IN_PLACE_DOWN] = MovementType_WalkInPlace,
    [MOVEMENT_TYPE_WALK_IN_PLACE_UP] = MovementType_WalkInPlace,
    [MOVEMENT_TYPE_WALK_IN_PLACE_LEFT] = MovementType_WalkInPlace,
    [MOVEMENT_TYPE_WALK_IN_PLACE_RIGHT] = MovementType_WalkInPlace,
    [MOVEMENT_TYPE_JOG_IN_PLACE_DOWN] = MovementType_JogInPlace,
    [MOVEMENT_TYPE_JOG_IN_PLACE_UP] = MovementType_JogInPlace,
    [MOVEMENT_TYPE_JOG_IN_PLACE_LEFT] = MovementType_JogInPlace,
    [MOVEMENT_TYPE_JOG_IN_PLACE_RIGHT] = MovementType_JogInPlace,
    [MOVEMENT_TYPE_RUN_IN_PLACE_DOWN] = MovementType_RunInPlace,
    [MOVEMENT_TYPE_RUN_IN_PLACE_UP] = MovementType_RunInPlace,
    [MOVEMENT_TYPE_RUN_IN_PLACE_LEFT] = MovementType_RunInPlace,
    [MOVEMENT_TYPE_RUN_IN_PLACE_RIGHT] = MovementType_RunInPlace,
    [MOVEMENT_TYPE_INVISIBLE] = MovementType_Invisible,
    [MOVEMENT_TYPE_WALK_SLOWLY_IN_PLACE_DOWN] = MovementType_WalkSlowlyInPlace,
    [MOVEMENT_TYPE_WALK_SLOWLY_IN_PLACE_UP] = MovementType_WalkSlowlyInPlace,
    [MOVEMENT_TYPE_WALK_SLOWLY_IN_PLACE_LEFT] = MovementType_WalkSlowlyInPlace,
    [MOVEMENT_TYPE_WALK_SLOWLY_IN_PLACE_RIGHT] = MovementType_WalkSlowlyInPlace,
};

const u8 gRangedMovementTypes[] = {
    [MOVEMENT_TYPE_NONE] = 0,
    [MOVEMENT_TYPE_LOOK_AROUND] = 0,
    [MOVEMENT_TYPE_WANDER_AROUND] = 1,
    [MOVEMENT_TYPE_WANDER_UP_AND_DOWN] = 1,
    [MOVEMENT_TYPE_WANDER_DOWN_AND_UP] = 1,
    [MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT] = 1,
    [MOVEMENT_TYPE_WANDER_RIGHT_AND_LEFT] = 1,
    [MOVEMENT_TYPE_FACE_UP] = 0,
    [MOVEMENT_TYPE_FACE_DOWN] = 0,
    [MOVEMENT_TYPE_FACE_LEFT] = 0,
    [MOVEMENT_TYPE_FACE_RIGHT] = 0,
    [MOVEMENT_TYPE_PLAYER] = 0,
    [MOVEMENT_TYPE_BERRY_TREE_GROWTH] = 0,
    [MOVEMENT_TYPE_FACE_DOWN_AND_UP] = 0,
    [MOVEMENT_TYPE_FACE_LEFT_AND_RIGHT] = 0,
    [MOVEMENT_TYPE_FACE_UP_AND_LEFT] = 0,
    [MOVEMENT_TYPE_FACE_UP_AND_RIGHT] = 0,
    [MOVEMENT_TYPE_FACE_DOWN_AND_LEFT] = 0,
    [MOVEMENT_TYPE_FACE_DOWN_AND_RIGHT] = 0,
    [MOVEMENT_TYPE_FACE_DOWN_UP_AND_LEFT] = 0,
    [MOVEMENT_TYPE_FACE_DOWN_UP_AND_RIGHT] = 0,
    [MOVEMENT_TYPE_FACE_UP_LEFT_AND_RIGHT] = 0,
    [MOVEMENT_TYPE_FACE_DOWN_LEFT_AND_RIGHT] = 0,
    [MOVEMENT_TYPE_ROTATE_COUNTERCLOCKWISE] = 0,
    [MOVEMENT_TYPE_ROTATE_CLOCKWISE] = 0,
    [MOVEMENT_TYPE_WALK_UP_AND_DOWN] = 1,
    [MOVEMENT_TYPE_WALK_DOWN_AND_UP] = 1,
    [MOVEMENT_TYPE_WALK_LEFT_AND_RIGHT] = 1,
    [MOVEMENT_TYPE_WALK_RIGHT_AND_LEFT] = 1,
    [MOVEMENT_TYPE_WALK_SEQUENCE_UP_RIGHT_LEFT_DOWN] = 1,
    [MOVEMENT_TYPE_WALK_SEQUENCE_RIGHT_LEFT_DOWN_UP] = 1,
    [MOVEMENT_TYPE_WALK_SEQUENCE_DOWN_UP_RIGHT_LEFT] = 1,
    [MOVEMENT_TYPE_WALK_SEQUENCE_LEFT_DOWN_UP_RIGHT] = 1,
    [MOVEMENT_TYPE_WALK_SEQUENCE_UP_LEFT_RIGHT_DOWN] = 1,
    [MOVEMENT_TYPE_WALK_SEQUENCE_LEFT_RIGHT_DOWN_UP] = 1,
    [MOVEMENT_TYPE_WALK_SEQUENCE_DOWN_UP_LEFT_RIGHT] = 1,
    [MOVEMENT_TYPE_WALK_SEQUENCE_RIGHT_DOWN_UP_LEFT] = 1,
    [MOVEMENT_TYPE_WALK_SEQUENCE_LEFT_UP_DOWN_RIGHT] = 1,
    [MOVEMENT_TYPE_WALK_SEQUENCE_UP_DOWN_RIGHT_LEFT] = 1,
    [MOVEMENT_TYPE_WALK_SEQUENCE_RIGHT_LEFT_UP_DOWN] = 1,
    [MOVEMENT_TYPE_WALK_SEQUENCE_DOWN_RIGHT_LEFT_UP] = 1,
    [MOVEMENT_TYPE_WALK_SEQUENCE_RIGHT_UP_DOWN_LEFT] = 1,
    [MOVEMENT_TYPE_WALK_SEQUENCE_UP_DOWN_LEFT_RIGHT] = 1,
    [MOVEMENT_TYPE_WALK_SEQUENCE_LEFT_RIGHT_UP_DOWN] = 1,
    [MOVEMENT_TYPE_WALK_SEQUENCE_DOWN_LEFT_RIGHT_UP] = 1,
    [MOVEMENT_TYPE_WALK_SEQUENCE_UP_LEFT_DOWN_RIGHT] = 1,
    [MOVEMENT_TYPE_WALK_SEQUENCE_DOWN_RIGHT_UP_LEFT] = 1,
    [MOVEMENT_TYPE_WALK_SEQUENCE_LEFT_DOWN_RIGHT_UP] = 1,
    [MOVEMENT_TYPE_WALK_SEQUENCE_RIGHT_UP_LEFT_DOWN] = 1,
    [MOVEMENT_TYPE_WALK_SEQUENCE_UP_RIGHT_DOWN_LEFT] = 1,
    [MOVEMENT_TYPE_WALK_SEQUENCE_DOWN_LEFT_UP_RIGHT] = 1,
    [MOVEMENT_TYPE_WALK_SEQUENCE_LEFT_UP_RIGHT_DOWN] = 1,
    [MOVEMENT_TYPE_WALK_SEQUENCE_RIGHT_DOWN_LEFT_UP] = 1,
    [MOVEMENT_TYPE_COPY_PLAYER] = 1,
    [MOVEMENT_TYPE_COPY_PLAYER_OPPOSITE] = 1,
    [MOVEMENT_TYPE_COPY_PLAYER_COUNTERCLOCKWISE] = 1,
    [MOVEMENT_TYPE_COPY_PLAYER_CLOCKWISE] = 1,
    [MOVEMENT_TYPE_TREE_DISGUISE] = 0,
    [MOVEMENT_TYPE_MOUNTAIN_DISGUISE] = 0,
    [MOVEMENT_TYPE_COPY_PLAYER_IN_GRASS] = 1,
    [MOVEMENT_TYPE_COPY_PLAYER_OPPOSITE_IN_GRASS] = 1,
    [MOVEMENT_TYPE_COPY_PLAYER_COUNTERCLOCKWISE_IN_GRASS] = 1,
    [MOVEMENT_TYPE_COPY_PLAYER_CLOCKWISE_IN_GRASS] = 1,
    [MOVEMENT_TYPE_HIDDEN] = 0,
    [MOVEMENT_TYPE_WALK_IN_PLACE_DOWN] = 0,
    [MOVEMENT_TYPE_WALK_IN_PLACE_UP] = 0,
    [MOVEMENT_TYPE_WALK_IN_PLACE_LEFT] = 0,
    [MOVEMENT_TYPE_WALK_IN_PLACE_RIGHT] = 0,
    [MOVEMENT_TYPE_JOG_IN_PLACE_DOWN] = 0,
    [MOVEMENT_TYPE_JOG_IN_PLACE_UP] = 0,
    [MOVEMENT_TYPE_JOG_IN_PLACE_LEFT] = 0,
    [MOVEMENT_TYPE_JOG_IN_PLACE_RIGHT] = 0,
    [MOVEMENT_TYPE_RUN_IN_PLACE_DOWN] = 0,
    [MOVEMENT_TYPE_RUN_IN_PLACE_UP] = 0,
    [MOVEMENT_TYPE_RUN_IN_PLACE_LEFT] = 0,
    [MOVEMENT_TYPE_RUN_IN_PLACE_RIGHT] = 0,
    [MOVEMENT_TYPE_INVISIBLE] = 0,
    [MOVEMENT_TYPE_WALK_SLOWLY_IN_PLACE_DOWN] = 0,
    [MOVEMENT_TYPE_WALK_SLOWLY_IN_PLACE_UP] = 0,
    [MOVEMENT_TYPE_WALK_SLOWLY_IN_PLACE_LEFT] = 0,
    [MOVEMENT_TYPE_WALK_SLOWLY_IN_PLACE_RIGHT] = 0,
};

const u8 gInitialMovementTypeFacingDirections[] = {
    [MOVEMENT_TYPE_NONE] = DIR_SOUTH,
    [MOVEMENT_TYPE_LOOK_AROUND] = DIR_SOUTH,
    [MOVEMENT_TYPE_WANDER_AROUND] = DIR_SOUTH,
    [MOVEMENT_TYPE_WANDER_UP_AND_DOWN] = DIR_NORTH,
    [MOVEMENT_TYPE_WANDER_DOWN_AND_UP] = DIR_SOUTH,
    [MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT] = DIR_WEST,
    [MOVEMENT_TYPE_WANDER_RIGHT_AND_LEFT] = DIR_EAST,
    [MOVEMENT_TYPE_FACE_UP] = DIR_NORTH,
    [MOVEMENT_TYPE_FACE_DOWN] = DIR_SOUTH,
    [MOVEMENT_TYPE_FACE_LEFT] = DIR_WEST,
    [MOVEMENT_TYPE_FACE_RIGHT] = DIR_EAST,
    [MOVEMENT_TYPE_PLAYER] = DIR_SOUTH,
    [MOVEMENT_TYPE_BERRY_TREE_GROWTH] = DIR_SOUTH,
    [MOVEMENT_TYPE_FACE_DOWN_AND_UP] = DIR_SOUTH,
    [MOVEMENT_TYPE_FACE_LEFT_AND_RIGHT] = DIR_WEST,
    [MOVEMENT_TYPE_FACE_UP_AND_LEFT] = DIR_NORTH,
    [MOVEMENT_TYPE_FACE_UP_AND_RIGHT] = DIR_NORTH,
    [MOVEMENT_TYPE_FACE_DOWN_AND_LEFT] = DIR_SOUTH,
    [MOVEMENT_TYPE_FACE_DOWN_AND_RIGHT] = DIR_SOUTH,
    [MOVEMENT_TYPE_FACE_DOWN_UP_AND_LEFT] = DIR_SOUTH,
    [MOVEMENT_TYPE_FACE_DOWN_UP_AND_RIGHT] = DIR_SOUTH,
    [MOVEMENT_TYPE_FACE_UP_LEFT_AND_RIGHT] = DIR_NORTH,
    [MOVEMENT_TYPE_FACE_DOWN_LEFT_AND_RIGHT] = DIR_SOUTH,
    [MOVEMENT_TYPE_ROTATE_COUNTERCLOCKWISE] = DIR_SOUTH,
    [MOVEMENT_TYPE_ROTATE_CLOCKWISE] = DIR_SOUTH,
    [MOVEMENT_TYPE_WALK_UP_AND_DOWN] = DIR_NORTH,
    [MOVEMENT_TYPE_WALK_DOWN_AND_UP] = DIR_SOUTH,
    [MOVEMENT_TYPE_WALK_LEFT_AND_RIGHT] = DIR_WEST,
    [MOVEMENT_TYPE_WALK_RIGHT_AND_LEFT] = DIR_EAST,
    [MOVEMENT_TYPE_WALK_SEQUENCE_UP_RIGHT_LEFT_DOWN] = DIR_NORTH,
    [MOVEMENT_TYPE_WALK_SEQUENCE_RIGHT_LEFT_DOWN_UP] = DIR_EAST,
    [MOVEMENT_TYPE_WALK_SEQUENCE_DOWN_UP_RIGHT_LEFT] = DIR_SOUTH,
    [MOVEMENT_TYPE_WALK_SEQUENCE_LEFT_DOWN_UP_RIGHT] = DIR_WEST,
    [MOVEMENT_TYPE_WALK_SEQUENCE_UP_LEFT_RIGHT_DOWN] = DIR_NORTH,
    [MOVEMENT_TYPE_WALK_SEQUENCE_LEFT_RIGHT_DOWN_UP] = DIR_WEST,
    [MOVEMENT_TYPE_WALK_SEQUENCE_DOWN_UP_LEFT_RIGHT] = DIR_SOUTH,
    [MOVEMENT_TYPE_WALK_SEQUENCE_RIGHT_DOWN_UP_LEFT] = DIR_EAST,
    [MOVEMENT_TYPE_WALK_SEQUENCE_LEFT_UP_DOWN_RIGHT] = DIR_WEST,
    [MOVEMENT_TYPE_WALK_SEQUENCE_UP_DOWN_RIGHT_LEFT] = DIR_NORTH,
    [MOVEMENT_TYPE_WALK_SEQUENCE_RIGHT_LEFT_UP_DOWN] = DIR_EAST,
    [MOVEMENT_TYPE_WALK_SEQUENCE_DOWN_RIGHT_LEFT_UP] = DIR_SOUTH,
    [MOVEMENT_TYPE_WALK_SEQUENCE_RIGHT_UP_DOWN_LEFT] = DIR_EAST,
    [MOVEMENT_TYPE_WALK_SEQUENCE_UP_DOWN_LEFT_RIGHT] = DIR_NORTH,
    [MOVEMENT_TYPE_WALK_SEQUENCE_LEFT_RIGHT_UP_DOWN] = DIR_WEST,
    [MOVEMENT_TYPE_WALK_SEQUENCE_DOWN_LEFT_RIGHT_UP] = DIR_SOUTH,
    [MOVEMENT_TYPE_WALK_SEQUENCE_UP_LEFT_DOWN_RIGHT] = DIR_NORTH,
    [MOVEMENT_TYPE_WALK_SEQUENCE_DOWN_RIGHT_UP_LEFT] = DIR_SOUTH,
    [MOVEMENT_TYPE_WALK_SEQUENCE_LEFT_DOWN_RIGHT_UP] = DIR_WEST,
    [MOVEMENT_TYPE_WALK_SEQUENCE_RIGHT_UP_LEFT_DOWN] = DIR_EAST,
    [MOVEMENT_TYPE_WALK_SEQUENCE_UP_RIGHT_DOWN_LEFT] = DIR_NORTH,
    [MOVEMENT_TYPE_WALK_SEQUENCE_DOWN_LEFT_UP_RIGHT] = DIR_SOUTH,
    [MOVEMENT_TYPE_WALK_SEQUENCE_LEFT_UP_RIGHT_DOWN] = DIR_WEST,
    [MOVEMENT_TYPE_WALK_SEQUENCE_RIGHT_DOWN_LEFT_UP] = DIR_EAST,
    [MOVEMENT_TYPE_COPY_PLAYER] = DIR_NORTH,
    [MOVEMENT_TYPE_COPY_PLAYER_OPPOSITE] = DIR_SOUTH,
    [MOVEMENT_TYPE_COPY_PLAYER_COUNTERCLOCKWISE] = DIR_WEST,
    [MOVEMENT_TYPE_COPY_PLAYER_CLOCKWISE] = DIR_EAST,
    [MOVEMENT_TYPE_TREE_DISGUISE] = DIR_SOUTH,
    [MOVEMENT_TYPE_MOUNTAIN_DISGUISE] = DIR_SOUTH,
    [MOVEMENT_TYPE_COPY_PLAYER_IN_GRASS] = DIR_NORTH,
    [MOVEMENT_TYPE_COPY_PLAYER_OPPOSITE_IN_GRASS] = DIR_SOUTH,
    [MOVEMENT_TYPE_COPY_PLAYER_COUNTERCLOCKWISE_IN_GRASS] = DIR_WEST,
    [MOVEMENT_TYPE_COPY_PLAYER_CLOCKWISE_IN_GRASS] = DIR_EAST,
    [MOVEMENT_TYPE_HIDDEN] = DIR_SOUTH,
    [MOVEMENT_TYPE_WALK_IN_PLACE_DOWN] = DIR_SOUTH,
    [MOVEMENT_TYPE_WALK_IN_PLACE_UP] = DIR_NORTH,
    [MOVEMENT_TYPE_WALK_IN_PLACE_LEFT] = DIR_WEST,
    [MOVEMENT_TYPE_WALK_IN_PLACE_RIGHT] = DIR_EAST,
    [MOVEMENT_TYPE_JOG_IN_PLACE_DOWN] = DIR_SOUTH,
    [MOVEMENT_TYPE_JOG_IN_PLACE_UP] = DIR_NORTH,
    [MOVEMENT_TYPE_JOG_IN_PLACE_LEFT] = DIR_WEST,
    [MOVEMENT_TYPE_JOG_IN_PLACE_RIGHT] = DIR_EAST,
    [MOVEMENT_TYPE_RUN_IN_PLACE_DOWN] = DIR_SOUTH,
    [MOVEMENT_TYPE_RUN_IN_PLACE_UP] = DIR_NORTH,
    [MOVEMENT_TYPE_RUN_IN_PLACE_LEFT] = DIR_WEST,
    [MOVEMENT_TYPE_RUN_IN_PLACE_RIGHT] = DIR_EAST,
    [MOVEMENT_TYPE_INVISIBLE] = DIR_SOUTH,
    [MOVEMENT_TYPE_WALK_SLOWLY_IN_PLACE_DOWN] = DIR_SOUTH,
    [MOVEMENT_TYPE_WALK_SLOWLY_IN_PLACE_UP] = DIR_NORTH,
    [MOVEMENT_TYPE_WALK_SLOWLY_IN_PLACE_LEFT] = DIR_WEST,
    [MOVEMENT_TYPE_WALK_SLOWLY_IN_PLACE_RIGHT] = DIR_EAST,
};

#define EVENT_OBJ_PAL_TAG_0  0x1103
#define EVENT_OBJ_PAL_TAG_1  0x1104
#define EVENT_OBJ_PAL_TAG_2  0x1105
#define EVENT_OBJ_PAL_TAG_3  0x1106
#define EVENT_OBJ_PAL_TAG_4  0x1107
#define EVENT_OBJ_PAL_TAG_5  0x1108
#define EVENT_OBJ_PAL_TAG_6  0x1109
#define EVENT_OBJ_PAL_TAG_7  0x110A
#define EVENT_OBJ_PAL_TAG_8  0x1100
#define EVENT_OBJ_PAL_TAG_9  0x1101
#define EVENT_OBJ_PAL_TAG_10 0x1102
#define EVENT_OBJ_PAL_TAG_11 0x1115
#define EVENT_OBJ_PAL_TAG_12 0x110B
#define EVENT_OBJ_PAL_TAG_13 0x110C
#define EVENT_OBJ_PAL_TAG_14 0x110D
#define EVENT_OBJ_PAL_TAG_15 0x110E
#define EVENT_OBJ_PAL_TAG_16 0x110F
#define EVENT_OBJ_PAL_TAG_17 0x1110
#define EVENT_OBJ_PAL_TAG_18 0x1111
#define EVENT_OBJ_PAL_TAG_19 0x1112
#define EVENT_OBJ_PAL_TAG_20 0x1113
#define EVENT_OBJ_PAL_TAG_21 0x1114
#define EVENT_OBJ_PAL_TAG_22 0x1116
#define EVENT_OBJ_PAL_TAG_23 0x1117
#define EVENT_OBJ_PAL_TAG_24 0x1118
#define EVENT_OBJ_PAL_TAG_25 0x1119
#define EVENT_OBJ_PAL_TAG_26 0x111B
#define EVENT_OBJ_PAL_TAG_27 0x111C
#define EVENT_OBJ_PAL_TAG_28 0x111D
#define EVENT_OBJ_PAL_TAG_29 0x111E
#define EVENT_OBJ_PAL_TAG_30 0x111F
#define EVENT_OBJ_PAL_TAG_31 0x1120
#define EVENT_OBJ_PAL_TAG_32 0x1121
#define EVENT_OBJ_PAL_TAG_33 0x1122
#define EVENT_OBJ_PAL_TAG_34 0x1123
#define EVENT_OBJ_PAL_PKMN_1 4388 //pkmn_1
#define EVENT_OBJ_PAL_PKMN_2 4389 //pkmn_2
#define EVENT_OBJ_PAL_PKMN_3 4390 //pkmn_3
#define EVENT_OBJ_PAL_PKMN_4 4391 //pkmn_4
#define EVENT_OBJ_PAL_PKMN_5 4392 //pkmn_5
#define EVENT_OBJ_PAL_PKMN_6 4393 //pkmn_6
#define EVENT_OBJ_PAL_PKMN_7 4394 //pkmn_7
#define EVENT_OBJ_PAL_PKMN_8 4395 //pkmn_8
#define EVENT_OBJ_PAL_PKMN_9 4396 //pkmn_9
#define EVENT_OBJ_PAL_PKMN_10 4397 //pkmn_10
#define EVENT_OBJ_PAL_PKMN_11 4398 //pkmn_11
#define EVENT_OBJ_PAL_PKMN_12 4399 //pkmn_12
#define EVENT_OBJ_PAL_PKMN_13 4400 //pkmn_13
#define EVENT_OBJ_PAL_PKMN_14 4401 //pkmn_14
#define EVENT_OBJ_PAL_PKMN_15 4402 //pkmn_15
#define EVENT_OBJ_PAL_PKMN_16 4403 //pkmn_16
#define EVENT_OBJ_PAL_PKMN_17 4404 //pkmn_17
#define EVENT_OBJ_PAL_PKMN_18 4405 //pkmn_18
#define EVENT_OBJ_PAL_PKMN_19 4406 //pkmn_19
#define EVENT_OBJ_PAL_PKMN_20 4407 //pkmn_20
#define EVENT_OBJ_PAL_PKMN_21 4408 //pkmn_21
#define EVENT_OBJ_PAL_PKMN_22 4409 //pkmn_22
#define EVENT_OBJ_PAL_PKMN_23 4410 //pkmn_23
#define EVENT_OBJ_PAL_PKMN_24 4411 //pkmn_24
#define EVENT_OBJ_PAL_PKMN_25 4412 //pkmn_25
#define EVENT_OBJ_PAL_PKMN_26 4413 //pkmn_26
#define EVENT_OBJ_PAL_PKMN_27 4414 //pkmn_27
#define EVENT_OBJ_PAL_PKMN_28 4415 //pkmn_28
#define EVENT_OBJ_PAL_PKMN_29 4416 //pkmn_29
#define EVENT_OBJ_PAL_PKMN_30 4417 //pkmn_30
#define EVENT_OBJ_PAL_PKMN_31 4418 //pkmn_31
#define EVENT_OBJ_PAL_PKMN_32 4419 //pkmn_32
#define EVENT_OBJ_PAL_PKMN_33 4420 //pkmn_33
#define EVENT_OBJ_PAL_PKMN_34 4421 //pkmn_34
#define EVENT_OBJ_PAL_PKMN_35 4422 //pkmn_35
#define EVENT_OBJ_PAL_PKMN_36 4423 //pkmn_36
#define EVENT_OBJ_PAL_PKMN_37 4424 //pkmn_37
#define EVENT_OBJ_PAL_PKMN_38 4425 //pkmn_38
#define EVENT_OBJ_PAL_PKMN_39 4426 //pkmn_39
#define EVENT_OBJ_PAL_PKMN_40 4427 //pkmn_40
#define EVENT_OBJ_PAL_PKMN_41 4428 //pkmn_41
#define EVENT_OBJ_PAL_PKMN_42 4429 //pkmn_42
#define EVENT_OBJ_PAL_PKMN_43 4430 //pkmn_43
#define EVENT_OBJ_PAL_PKMN_44 4431 //pkmn_44
#define EVENT_OBJ_PAL_PKMN_45 4432 //pkmn_45
#define EVENT_OBJ_PAL_PKMN_46 4433 //pkmn_46
#define EVENT_OBJ_PAL_PKMN_47 4434 //pkmn_47
#define EVENT_OBJ_PAL_PKMN_48 4435 //pkmn_48
#define EVENT_OBJ_PAL_PKMN_49 4436 //pkmn_49
#define EVENT_OBJ_PAL_PKMN_50 4437 //pkmn_50
#define EVENT_OBJ_PAL_PKMN_51 4438 //pkmn_51
#define EVENT_OBJ_PAL_PKMN_52 4439 //pkmn_52
#define EVENT_OBJ_PAL_PKMN_53 4440 //pkmn_53
#define EVENT_OBJ_PAL_PKMN_54 4441 //pkmn_54
#define EVENT_OBJ_PAL_PKMN_55 4442 //pkmn_55
#define EVENT_OBJ_PAL_PKMN_56 4443 //pkmn_56
#define EVENT_OBJ_PAL_PKMN_57 4444 //pkmn_57
#define EVENT_OBJ_PAL_PKMN_58 4445 //pkmn_58
#define EVENT_OBJ_PAL_PKMN_59 4446 //pkmn_59
#define EVENT_OBJ_PAL_PKMN_60 4447 //pkmn_60
#define EVENT_OBJ_PAL_PKMN_61 4448 //pkmn_61
#define EVENT_OBJ_PAL_PKMN_62 4449 //pkmn_62
#define EVENT_OBJ_PAL_PKMN_63 4450 //pkmn_63
#define EVENT_OBJ_PAL_PKMN_64 4451 //pkmn_64
#define EVENT_OBJ_PAL_PKMN_65 4452 //pkmn_65
#define EVENT_OBJ_PAL_PKMN_66 4453 //pkmn_66
#define EVENT_OBJ_PAL_PKMN_67 4454 //pkmn_67
#define EVENT_OBJ_PAL_PKMN_68 4455 //pkmn_68
#define EVENT_OBJ_PAL_PKMN_69 4456 //pkmn_69
#define EVENT_OBJ_PAL_PKMN_70 4457 //pkmn_70
#define EVENT_OBJ_PAL_PKMN_71 4458 //pkmn_71
#define EVENT_OBJ_PAL_PKMN_72 4459 //pkmn_72
#define EVENT_OBJ_PAL_PKMN_73 4460 //pkmn_73
#define EVENT_OBJ_PAL_PKMN_74 4461 //pkmn_74
#define EVENT_OBJ_PAL_PKMN_75 4462 //pkmn_75
#define EVENT_OBJ_PAL_PKMN_76 4463 //pkmn_76
#define EVENT_OBJ_PAL_PKMN_77 4464 //pkmn_77
#define EVENT_OBJ_PAL_PKMN_78 4465 //pkmn_78
#define EVENT_OBJ_PAL_PKMN_79 4466 //pkmn_79
#define EVENT_OBJ_PAL_PKMN_80 4467 //pkmn_80
#define EVENT_OBJ_PAL_PKMN_81 4468 //pkmn_81
#define EVENT_OBJ_PAL_PKMN_82 4469 //pkmn_82
#define EVENT_OBJ_PAL_PKMN_83 4470 //pkmn_83
#define EVENT_OBJ_PAL_PKMN_84 4471 //pkmn_84
#define EVENT_OBJ_PAL_PKMN_85 4472 //pkmn_85
#define EVENT_OBJ_PAL_PKMN_86 4473 //pkmn_86
#define EVENT_OBJ_PAL_PKMN_87 4474 //pkmn_87
#define EVENT_OBJ_PAL_PKMN_88 4475 //pkmn_88
#define EVENT_OBJ_PAL_PKMN_89 4476 //pkmn_89
#define EVENT_OBJ_PAL_PKMN_90 4477 //pkmn_90
#define EVENT_OBJ_PAL_PKMN_91 4478 //pkmn_91
#define EVENT_OBJ_PAL_PKMN_92 4479 //pkmn_92
#define EVENT_OBJ_PAL_PKMN_93 4480 //pkmn_93
#define EVENT_OBJ_PAL_PKMN_94 4481 //pkmn_94
#define EVENT_OBJ_PAL_PKMN_95 4482 //pkmn_95
#define EVENT_OBJ_PAL_PKMN_96 4483 //pkmn_96
#define EVENT_OBJ_PAL_PKMN_97 4484 //pkmn_97
#define EVENT_OBJ_PAL_PKMN_98 4485 //pkmn_98
#define EVENT_OBJ_PAL_PKMN_99 4486 //pkmn_99
#define EVENT_OBJ_PAL_PKMN_100 4487 //pkmn_100
#define EVENT_OBJ_PAL_PKMN_101 4488 //pkmn_101
#define EVENT_OBJ_PAL_PKMN_102 4489 //pkmn_102
#define EVENT_OBJ_PAL_PKMN_103 4490 //pkmn_103
#define EVENT_OBJ_PAL_PKMN_104 4491 //pkmn_104
#define EVENT_OBJ_PAL_PKMN_105 4492 //pkmn_105
#define EVENT_OBJ_PAL_PKMN_106 4493 //pkmn_106
#define EVENT_OBJ_PAL_PKMN_107 4494 //pkmn_107
#define EVENT_OBJ_PAL_PKMN_108 4495 //pkmn_108
#define EVENT_OBJ_PAL_PKMN_109 4496 //pkmn_109
#define EVENT_OBJ_PAL_PKMN_110 4497 //pkmn_110
#define EVENT_OBJ_PAL_PKMN_111 4498 //pkmn_111
#define EVENT_OBJ_PAL_PKMN_112 4499 //pkmn_112
#define EVENT_OBJ_PAL_PKMN_113 4500 //pkmn_113
#define EVENT_OBJ_PAL_PKMN_114 4501 //pkmn_114
#define EVENT_OBJ_PAL_PKMN_115 4502 //pkmn_115
#define EVENT_OBJ_PAL_PKMN_116 4503 //pkmn_116
#define EVENT_OBJ_PAL_PKMN_117 4504 //pkmn_117
#define EVENT_OBJ_PAL_PKMN_118 4505 //pkmn_118
#define EVENT_OBJ_PAL_PKMN_119 4506 //pkmn_119
#define EVENT_OBJ_PAL_PKMN_120 4507 //pkmn_120
#define EVENT_OBJ_PAL_PKMN_121 4508 //pkmn_121
#define EVENT_OBJ_PAL_PKMN_122 4509 //pkmn_122
#define EVENT_OBJ_PAL_PKMN_123 4510 //pkmn_123
#define EVENT_OBJ_PAL_PKMN_124 4511 //pkmn_124
#define EVENT_OBJ_PAL_PKMN_125 4512 //pkmn_125
#define EVENT_OBJ_PAL_PKMN_126 4513 //pkmn_126
#define EVENT_OBJ_PAL_PKMN_127 4514 //pkmn_127
#define EVENT_OBJ_PAL_PKMN_128 4515 //pkmn_128
#define EVENT_OBJ_PAL_PKMN_129 4516 //pkmn_129
#define EVENT_OBJ_PAL_PKMN_130 4517 //pkmn_130
#define EVENT_OBJ_PAL_PKMN_131 4518 //pkmn_131
#define EVENT_OBJ_PAL_PKMN_132 4519 //pkmn_132
#define EVENT_OBJ_PAL_PKMN_133 4520 //pkmn_133
#define EVENT_OBJ_PAL_PKMN_134 4521 //pkmn_134
#define EVENT_OBJ_PAL_PKMN_135 4522 //pkmn_135
#define EVENT_OBJ_PAL_PKMN_136 4523 //pkmn_136
#define EVENT_OBJ_PAL_PKMN_137 4524 //pkmn_137
#define EVENT_OBJ_PAL_PKMN_138 4525 //pkmn_138
#define EVENT_OBJ_PAL_PKMN_139 4526 //pkmn_139
#define EVENT_OBJ_PAL_PKMN_140 4527 //pkmn_140
#define EVENT_OBJ_PAL_PKMN_141 4528 //pkmn_141
#define EVENT_OBJ_PAL_PKMN_142 4529 //pkmn_142
#define EVENT_OBJ_PAL_PKMN_143 4530 //pkmn_143
#define EVENT_OBJ_PAL_PKMN_144 4531 //pkmn_144
#define EVENT_OBJ_PAL_PKMN_145 4532 //pkmn_145
#define EVENT_OBJ_PAL_PKMN_146 4533 //pkmn_146
#define EVENT_OBJ_PAL_PKMN_147 4534 //pkmn_147
#define EVENT_OBJ_PAL_PKMN_148 4535 //pkmn_148
#define EVENT_OBJ_PAL_PKMN_149 4536 //pkmn_149
#define EVENT_OBJ_PAL_PKMN_150 4537 //pkmn_150
#define EVENT_OBJ_PAL_PKMN_151 4538 //pkmn_151
#define EVENT_OBJ_PAL_PKMN_152 4539 //pkmn_152
#define EVENT_OBJ_PAL_PKMN_153 4540 //pkmn_153
#define EVENT_OBJ_PAL_PKMN_154 4541 //pkmn_154
#define EVENT_OBJ_PAL_PKMN_155 4542 //pkmn_155
#define EVENT_OBJ_PAL_PKMN_156 4543 //pkmn_156
#define EVENT_OBJ_PAL_PKMN_157 4544 //pkmn_157
#define EVENT_OBJ_PAL_PKMN_158 4545 //pkmn_158
#define EVENT_OBJ_PAL_PKMN_159 4546 //pkmn_159
#define EVENT_OBJ_PAL_PKMN_160 4547 //pkmn_160
#define EVENT_OBJ_PAL_PKMN_161 4548 //pkmn_161
#define EVENT_OBJ_PAL_PKMN_162 4549 //pkmn_162
#define EVENT_OBJ_PAL_PKMN_163 4550 //pkmn_163
#define EVENT_OBJ_PAL_PKMN_164 4551 //pkmn_164
#define EVENT_OBJ_PAL_PKMN_165 4552 //pkmn_165
#define EVENT_OBJ_PAL_PKMN_166 4553 //pkmn_166
#define EVENT_OBJ_PAL_PKMN_167 4554 //pkmn_167
#define EVENT_OBJ_PAL_PKMN_168 4555 //pkmn_168
#define EVENT_OBJ_PAL_PKMN_169 4556 //pkmn_169
#define EVENT_OBJ_PAL_PKMN_170 4557 //pkmn_170
#define EVENT_OBJ_PAL_PKMN_171 4558 //pkmn_171
#define EVENT_OBJ_PAL_PKMN_172 4559 //pkmn_172
#define EVENT_OBJ_PAL_PKMN_173 4560 //pkmn_173
#define EVENT_OBJ_PAL_PKMN_174 4561 //pkmn_174
#define EVENT_OBJ_PAL_PKMN_175 4562 //pkmn_175
#define EVENT_OBJ_PAL_PKMN_176 4563 //pkmn_176
#define EVENT_OBJ_PAL_PKMN_177 4564 //pkmn_177
#define EVENT_OBJ_PAL_PKMN_178 4565 //pkmn_178
#define EVENT_OBJ_PAL_PKMN_179 4566 //pkmn_179
#define EVENT_OBJ_PAL_PKMN_180 4567 //pkmn_180
#define EVENT_OBJ_PAL_PKMN_181 4568 //pkmn_181
#define EVENT_OBJ_PAL_PKMN_182 4569 //pkmn_182
#define EVENT_OBJ_PAL_PKMN_183 4570 //pkmn_183
#define EVENT_OBJ_PAL_PKMN_184 4571 //pkmn_184
#define EVENT_OBJ_PAL_PKMN_185 4572 //pkmn_185
#define EVENT_OBJ_PAL_PKMN_186 4573 //pkmn_186
#define EVENT_OBJ_PAL_PKMN_187 4574 //pkmn_187
#define EVENT_OBJ_PAL_PKMN_188 4575 //pkmn_188
#define EVENT_OBJ_PAL_PKMN_189 4576 //pkmn_189
#define EVENT_OBJ_PAL_PKMN_190 4577 //pkmn_190
#define EVENT_OBJ_PAL_PKMN_191 4578 //pkmn_191
#define EVENT_OBJ_PAL_PKMN_192 4579 //pkmn_192
#define EVENT_OBJ_PAL_PKMN_193 4580 //pkmn_193
#define EVENT_OBJ_PAL_PKMN_194 4581 //pkmn_194
#define EVENT_OBJ_PAL_PKMN_195 4582 //pkmn_195
#define EVENT_OBJ_PAL_PKMN_196 4583 //pkmn_196
#define EVENT_OBJ_PAL_PKMN_197 4584 //pkmn_197
#define EVENT_OBJ_PAL_PKMN_198 4585 //pkmn_198
#define EVENT_OBJ_PAL_PKMN_199 4586 //pkmn_199
#define EVENT_OBJ_PAL_PKMN_200 4587 //pkmn_200
#define EVENT_OBJ_PAL_PKMN_201 4588 //pkmn_201
#define EVENT_OBJ_PAL_PKMN_202 4589 //pkmn_202
#define EVENT_OBJ_PAL_PKMN_203 4590 //pkmn_203
#define EVENT_OBJ_PAL_PKMN_204 4591 //pkmn_204
#define EVENT_OBJ_PAL_PKMN_205 4592 //pkmn_205
#define EVENT_OBJ_PAL_PKMN_206 4593 //pkmn_206
#define EVENT_OBJ_PAL_PKMN_207 4594 //pkmn_207
#define EVENT_OBJ_PAL_PKMN_208 4595 //pkmn_208
#define EVENT_OBJ_PAL_PKMN_209 4596 //pkmn_209
#define EVENT_OBJ_PAL_PKMN_210 4597 //pkmn_210
#define EVENT_OBJ_PAL_PKMN_211 4598 //pkmn_211
#define EVENT_OBJ_PAL_PKMN_212 4599 //pkmn_212
#define EVENT_OBJ_PAL_PKMN_213 4600 //pkmn_213
#define EVENT_OBJ_PAL_PKMN_214 4601 //pkmn_214
#define EVENT_OBJ_PAL_PKMN_215 4602 //pkmn_215
#define EVENT_OBJ_PAL_PKMN_216 4603 //pkmn_216
#define EVENT_OBJ_PAL_PKMN_217 4604 //pkmn_217
#define EVENT_OBJ_PAL_PKMN_218 4605 //pkmn_218
#define EVENT_OBJ_PAL_PKMN_219 4606 //pkmn_219
#define EVENT_OBJ_PAL_PKMN_220 4607 //pkmn_220
#define EVENT_OBJ_PAL_PKMN_221 4608 //pkmn_221
#define EVENT_OBJ_PAL_PKMN_222 4609 //pkmn_222
#define EVENT_OBJ_PAL_PKMN_223 4610 //pkmn_223
#define EVENT_OBJ_PAL_PKMN_224 4611 //pkmn_224
#define EVENT_OBJ_PAL_PKMN_225 4612 //pkmn_225
#define EVENT_OBJ_PAL_PKMN_226 4613 //pkmn_226
#define EVENT_OBJ_PAL_PKMN_227 4614 //pkmn_227
#define EVENT_OBJ_PAL_PKMN_228 4615 //pkmn_228
#define EVENT_OBJ_PAL_PKMN_229 4616 //pkmn_229
#define EVENT_OBJ_PAL_PKMN_230 4617 //pkmn_230
#define EVENT_OBJ_PAL_PKMN_231 4618 //pkmn_231
#define EVENT_OBJ_PAL_PKMN_232 4619 //pkmn_232
#define EVENT_OBJ_PAL_PKMN_233 4620 //pkmn_233
#define EVENT_OBJ_PAL_PKMN_234 4621 //pkmn_234
#define EVENT_OBJ_PAL_PKMN_235 4622 //pkmn_235
#define EVENT_OBJ_PAL_PKMN_236 4623 //pkmn_236
#define EVENT_OBJ_PAL_PKMN_237 4624 //pkmn_237
#define EVENT_OBJ_PAL_PKMN_238 4625 //pkmn_238
#define EVENT_OBJ_PAL_PKMN_239 4626 //pkmn_239
#define EVENT_OBJ_PAL_PKMN_240 4627 //pkmn_240
#define EVENT_OBJ_PAL_PKMN_241 4628 //pkmn_241
#define EVENT_OBJ_PAL_PKMN_242 4629 //pkmn_242
#define EVENT_OBJ_PAL_PKMN_243 4630 //pkmn_243
#define EVENT_OBJ_PAL_PKMN_244 4631 //pkmn_244
#define EVENT_OBJ_PAL_PKMN_245 4632 //pkmn_245
#define EVENT_OBJ_PAL_PKMN_246 4633 //pkmn_246
#define EVENT_OBJ_PAL_PKMN_247 4634 //pkmn_247
#define EVENT_OBJ_PAL_PKMN_248 4635 //pkmn_248
#define EVENT_OBJ_PAL_PKMN_249 4636 //pkmn_249
#define EVENT_OBJ_PAL_PKMN_250 4637 //pkmn_250
#define EVENT_OBJ_PAL_PKMN_251 4638 //pkmn_251
#define EVENT_OBJ_PAL_PKMN_252 4639 //pkmn_252
#define EVENT_OBJ_PAL_PKMN_253 4640 //pkmn_253
#define EVENT_OBJ_PAL_PKMN_254 4641 //pkmn_254
#define EVENT_OBJ_PAL_PKMN_255 4642 //pkmn_255
#define EVENT_OBJ_PAL_PKMN_256 4643 //pkmn_256
#define EVENT_OBJ_PAL_PKMN_257 4644 //pkmn_257
#define EVENT_OBJ_PAL_PKMN_258 4645 //pkmn_258
#define EVENT_OBJ_PAL_PKMN_259 4646 //pkmn_259
#define EVENT_OBJ_PAL_PKMN_260 4647 //pkmn_260
#define EVENT_OBJ_PAL_PKMN_261 4648 //pkmn_261
#define EVENT_OBJ_PAL_PKMN_262 4649 //pkmn_262
#define EVENT_OBJ_PAL_PKMN_263 4650 //pkmn_263
#define EVENT_OBJ_PAL_PKMN_264 4651 //pkmn_264
#define EVENT_OBJ_PAL_PKMN_265 4652 //pkmn_265
#define EVENT_OBJ_PAL_PKMN_266 4653 //pkmn_266
#define EVENT_OBJ_PAL_PKMN_267 4654 //pkmn_267
#define EVENT_OBJ_PAL_PKMN_268 4655 //pkmn_268
#define EVENT_OBJ_PAL_PKMN_269 4656 //pkmn_269
#define EVENT_OBJ_PAL_PKMN_270 4657 //pkmn_270
#define EVENT_OBJ_PAL_PKMN_271 4658 //pkmn_271
#define EVENT_OBJ_PAL_PKMN_272 4659 //pkmn_272
#define EVENT_OBJ_PAL_PKMN_273 4660 //pkmn_273
#define EVENT_OBJ_PAL_PKMN_274 4661 //pkmn_274
#define EVENT_OBJ_PAL_PKMN_275 4662 //pkmn_275
#define EVENT_OBJ_PAL_PKMN_276 4663 //pkmn_276
#define EVENT_OBJ_PAL_PKMN_277 4664 //pkmn_277
#define EVENT_OBJ_PAL_PKMN_278 4665 //pkmn_278
#define EVENT_OBJ_PAL_PKMN_279 4666 //pkmn_279
#define EVENT_OBJ_PAL_PKMN_280 4667 //pkmn_280
#define EVENT_OBJ_PAL_PKMN_281 4668 //pkmn_281
#define EVENT_OBJ_PAL_PKMN_282 4669 //pkmn_282
#define EVENT_OBJ_PAL_PKMN_283 4670 //pkmn_283
#define EVENT_OBJ_PAL_PKMN_284 4671 //pkmn_284
#define EVENT_OBJ_PAL_PKMN_285 4672 //pkmn_285
#define EVENT_OBJ_PAL_PKMN_286 4673 //pkmn_286
#define EVENT_OBJ_PAL_PKMN_287 4674 //pkmn_287
#define EVENT_OBJ_PAL_PKMN_288 4675 //pkmn_288
#define EVENT_OBJ_PAL_PKMN_289 4676 //pkmn_289
#define EVENT_OBJ_PAL_PKMN_290 4677 //pkmn_290
#define EVENT_OBJ_PAL_PKMN_291 4678 //pkmn_291
#define EVENT_OBJ_PAL_PKMN_292 4679 //pkmn_292
#define EVENT_OBJ_PAL_PKMN_293 4680 //pkmn_293
#define EVENT_OBJ_PAL_PKMN_294 4681 //pkmn_294
#define EVENT_OBJ_PAL_PKMN_295 4682 //pkmn_295
#define EVENT_OBJ_PAL_PKMN_296 4683 //pkmn_296
#define EVENT_OBJ_PAL_PKMN_297 4684 //pkmn_297
#define EVENT_OBJ_PAL_PKMN_298 4685 //pkmn_298
#define EVENT_OBJ_PAL_PKMN_299 4686 //pkmn_299
#define EVENT_OBJ_PAL_PKMN_300 4687 //pkmn_300
#define EVENT_OBJ_PAL_PKMN_301 4688 //pkmn_301
#define EVENT_OBJ_PAL_PKMN_302 4689 //pkmn_302
#define EVENT_OBJ_PAL_PKMN_303 4690 //pkmn_303
#define EVENT_OBJ_PAL_PKMN_304 4691 //pkmn_304
#define EVENT_OBJ_PAL_PKMN_305 4692 //pkmn_305
#define EVENT_OBJ_PAL_PKMN_306 4693 //pkmn_306
#define EVENT_OBJ_PAL_PKMN_307 4694 //pkmn_307
#define EVENT_OBJ_PAL_PKMN_308 4695 //pkmn_308
#define EVENT_OBJ_PAL_PKMN_309 4696 //pkmn_309
#define EVENT_OBJ_PAL_PKMN_310 4697 //pkmn_310
#define EVENT_OBJ_PAL_PKMN_311 4698 //pkmn_311
#define EVENT_OBJ_PAL_PKMN_312 4699 //pkmn_312
#define EVENT_OBJ_PAL_PKMN_313 4700 //pkmn_313
#define EVENT_OBJ_PAL_PKMN_314 4701 //pkmn_314
#define EVENT_OBJ_PAL_PKMN_315 4702 //pkmn_315
#define EVENT_OBJ_PAL_PKMN_316 4703 //pkmn_316
#define EVENT_OBJ_PAL_PKMN_317 4704 //pkmn_317
#define EVENT_OBJ_PAL_PKMN_318 4705 //pkmn_318
#define EVENT_OBJ_PAL_PKMN_319 4706 //pkmn_319
#define EVENT_OBJ_PAL_PKMN_320 4707 //pkmn_320
#define EVENT_OBJ_PAL_PKMN_321 4708 //pkmn_321
#define EVENT_OBJ_PAL_PKMN_322 4709 //pkmn_322
#define EVENT_OBJ_PAL_PKMN_323 4710 //pkmn_323
#define EVENT_OBJ_PAL_PKMN_324 4711 //pkmn_324
#define EVENT_OBJ_PAL_PKMN_325 4712 //pkmn_325
#define EVENT_OBJ_PAL_PKMN_326 4713 //pkmn_326
#define EVENT_OBJ_PAL_PKMN_327 4714 //pkmn_327
#define EVENT_OBJ_PAL_PKMN_328 4715 //pkmn_328
#define EVENT_OBJ_PAL_PKMN_329 4716 //pkmn_329
#define EVENT_OBJ_PAL_PKMN_330 4717 //pkmn_330
#define EVENT_OBJ_PAL_PKMN_331 4718 //pkmn_331
#define EVENT_OBJ_PAL_PKMN_332 4719 //pkmn_332
#define EVENT_OBJ_PAL_PKMN_333 4720 //pkmn_333
#define EVENT_OBJ_PAL_PKMN_334 4721 //pkmn_334
#define EVENT_OBJ_PAL_PKMN_335 4722 //pkmn_335
#define EVENT_OBJ_PAL_PKMN_336 4723 //pkmn_336
#define EVENT_OBJ_PAL_PKMN_337 4724 //pkmn_337
#define EVENT_OBJ_PAL_PKMN_338 4725 //pkmn_338
#define EVENT_OBJ_PAL_PKMN_339 4726 //pkmn_339
#define EVENT_OBJ_PAL_PKMN_340 4727 //pkmn_340
#define EVENT_OBJ_PAL_PKMN_341 4728 //pkmn_341
#define EVENT_OBJ_PAL_PKMN_342 4729 //pkmn_342
#define EVENT_OBJ_PAL_PKMN_343 4730 //pkmn_343
#define EVENT_OBJ_PAL_PKMN_344 4731 //pkmn_344
#define EVENT_OBJ_PAL_PKMN_345 4732 //pkmn_345
#define EVENT_OBJ_PAL_PKMN_346 4733 //pkmn_346
#define EVENT_OBJ_PAL_PKMN_347 4734 //pkmn_347
#define EVENT_OBJ_PAL_PKMN_348 4735 //pkmn_348
#define EVENT_OBJ_PAL_PKMN_349 4736 //pkmn_349
#define EVENT_OBJ_PAL_PKMN_350 4737 //pkmn_350
#define EVENT_OBJ_PAL_PKMN_351 4738 //pkmn_351
#define EVENT_OBJ_PAL_PKMN_352 4739 //pkmn_352
#define EVENT_OBJ_PAL_PKMN_353 4740 //pkmn_353
#define EVENT_OBJ_PAL_PKMN_354 4741 //pkmn_354
#define EVENT_OBJ_PAL_PKMN_355 4742 //pkmn_355
#define EVENT_OBJ_PAL_PKMN_356 4743 //pkmn_356
#define EVENT_OBJ_PAL_PKMN_357 4744 //pkmn_357
#define EVENT_OBJ_PAL_PKMN_358 4745 //pkmn_358
#define EVENT_OBJ_PAL_PKMN_359 4746 //pkmn_359
#define EVENT_OBJ_PAL_PKMN_360 4747 //pkmn_360
#define EVENT_OBJ_PAL_PKMN_361 4748 //pkmn_361
#define EVENT_OBJ_PAL_PKMN_362 4749 //pkmn_362
#define EVENT_OBJ_PAL_PKMN_363 4750 //pkmn_363
#define EVENT_OBJ_PAL_PKMN_364 4751 //pkmn_364
#define EVENT_OBJ_PAL_PKMN_365 4752 //pkmn_365
#define EVENT_OBJ_PAL_PKMN_366 4753 //pkmn_366
#define EVENT_OBJ_PAL_PKMN_367 4754 //pkmn_367
#define EVENT_OBJ_PAL_PKMN_368 4755 //pkmn_368
#define EVENT_OBJ_PAL_PKMN_369 4756 //pkmn_369
#define EVENT_OBJ_PAL_PKMN_370 4757 //pkmn_370
#define EVENT_OBJ_PAL_PKMN_371 4758 //pkmn_371
#define EVENT_OBJ_PAL_PKMN_372 4759 //pkmn_372
#define EVENT_OBJ_PAL_PKMN_373 4760 //pkmn_373
#define EVENT_OBJ_PAL_PKMN_374 4761 //pkmn_374
#define EVENT_OBJ_PAL_PKMN_375 4762 //pkmn_375
#define EVENT_OBJ_PAL_PKMN_376 4763 //pkmn_376
#define EVENT_OBJ_PAL_PKMN_377 4764 //pkmn_377
#define EVENT_OBJ_PAL_PKMN_378 4765 //pkmn_378
#define EVENT_OBJ_PAL_PKMN_379 4766 //pkmn_379
#define EVENT_OBJ_PAL_PKMN_380 4767 //pkmn_380
#define EVENT_OBJ_PAL_PKMN_381 4768 //pkmn_381
#define EVENT_OBJ_PAL_PKMN_382 4769 //pkmn_382
#define EVENT_OBJ_PAL_PKMN_383 4770 //pkmn_383
#define EVENT_OBJ_PAL_PKMN_384 4771 //pkmn_384
#define EVENT_OBJ_PAL_PKMN_385 4772 //pkmn_385
#define EVENT_OBJ_PAL_PKMN_386 4773 //pkmn_386
#define EVENT_OBJ_PAL_PKMN_387 4774 //pkmn_387
#define EVENT_OBJ_PAL_PKMN_388 4775 //pkmn_388
#define EVENT_OBJ_PAL_PKMN_389 4776 //pkmn_389
#define EVENT_OBJ_PAL_PKMN_390 4777 //pkmn_390
#define EVENT_OBJ_PAL_PKMN_391 4778 //pkmn_391
#define EVENT_OBJ_PAL_PKMN_392 4779 //pkmn_392
#define EVENT_OBJ_PAL_PKMN_393 4780 //pkmn_393
#define EVENT_OBJ_PAL_PKMN_394 4781 //pkmn_394
#define EVENT_OBJ_PAL_PKMN_395 4782 //pkmn_395
#define EVENT_OBJ_PAL_PKMN_396 4783 //pkmn_396
#define EVENT_OBJ_PAL_PKMN_397 4784 //pkmn_397
#define EVENT_OBJ_PAL_PKMN_398 4785 //pkmn_398
#define EVENT_OBJ_PAL_PKMN_399 4786 //pkmn_399
#define EVENT_OBJ_PAL_PKMN_400 4787 //pkmn_400
#define EVENT_OBJ_PAL_PKMN_401 4788 //pkmn_401
#define EVENT_OBJ_PAL_PKMN_402 4789 //pkmn_402
#define EVENT_OBJ_PAL_PKMN_403 4790 //pkmn_403
#define EVENT_OBJ_PAL_PKMN_404 4791 //pkmn_404
#define EVENT_OBJ_PAL_PKMN_405 4792 //pkmn_405
#define EVENT_OBJ_PAL_PKMN_406 4793 //pkmn_406
#define EVENT_OBJ_PAL_PKMN_407 4794 //pkmn_407
#define EVENT_OBJ_PAL_PKMN_408 4795 //pkmn_408
#define EVENT_OBJ_PAL_PKMN_409 4796 //pkmn_409
#define EVENT_OBJ_PAL_PKMN_410 4797 //pkmn_410
#define EVENT_OBJ_PAL_PKMN_411 4798 //pkmn_411
#define EVENT_OBJ_PAL_PKMN_412 4799 //pkmn_412
#define EVENT_OBJ_PAL_PKMN_413 4800 //pkmn_413
#define EVENT_OBJ_PAL_PKMN_414 4801 //pkmn_414
#define EVENT_OBJ_PAL_PKMN_415 4802 //pkmn_415
#define EVENT_OBJ_PAL_PKMN_416 4803 //pkmn_416
#define EVENT_OBJ_PAL_PKMN_417 4804 //pkmn_417
#define EVENT_OBJ_PAL_PKMN_418 4805 //pkmn_418
#define EVENT_OBJ_PAL_PKMN_419 4806 //pkmn_419
#define EVENT_OBJ_PAL_PKMN_420 4807 //pkmn_420
#define EVENT_OBJ_PAL_PKMN_421 4808 //pkmn_421
#define EVENT_OBJ_PAL_PKMN_422 4809 //pkmn_422
#define EVENT_OBJ_PAL_PKMN_423 4810 //pkmn_423
#define EVENT_OBJ_PAL_PKMN_424 4811 //pkmn_424
#define EVENT_OBJ_PAL_PKMN_425 4812 //pkmn_425
#define EVENT_OBJ_PAL_PKMN_426 4813 //pkmn_426
#define EVENT_OBJ_PAL_PKMN_427 4814 //pkmn_427
#define EVENT_OBJ_PAL_PKMN_428 4815 //pkmn_428
#define EVENT_OBJ_PAL_PKMN_429 4816 //pkmn_429
#define EVENT_OBJ_PAL_PKMN_430 4817 //pkmn_430
#define EVENT_OBJ_PAL_PKMN_431 4818 //pkmn_431
#define EVENT_OBJ_PAL_PKMN_432 4819 //pkmn_432
#define EVENT_OBJ_PAL_PKMN_433 4820 //pkmn_433
#define EVENT_OBJ_PAL_PKMN_434 4821 //pkmn_434
#define EVENT_OBJ_PAL_PKMN_435 4822 //pkmn_435
#define EVENT_OBJ_PAL_PKMN_436 4823 //pkmn_436
#define EVENT_OBJ_PAL_PKMN_437 4824 //pkmn_437
#define EVENT_OBJ_PAL_PKMN_438 4825 //pkmn_438
#define EVENT_OBJ_PAL_PKMN_439 4826 //pkmn_439
#define EVENT_OBJ_PAL_PKMN_440 4827 //pkmn_440
#define EVENT_OBJ_PAL_PKMN_441 4828 //pkmn_441
#define EVENT_OBJ_PAL_PKMN_442 4829 //pkmn_442
#define EVENT_OBJ_PAL_PKMN_443 4830 //pkmn_443
#define EVENT_OBJ_PAL_PKMN_444 4831 //pkmn_444
#define EVENT_OBJ_PAL_PKMN_445 4832 //pkmn_445
#define EVENT_OBJ_PAL_PKMN_446 4833 //pkmn_446
#define EVENT_OBJ_PAL_PKMN_447 4834 //pkmn_447
#define EVENT_OBJ_PAL_PKMN_448 4835 //pkmn_448
#define EVENT_OBJ_PAL_PKMN_449 4836 //pkmn_449
#define EVENT_OBJ_PAL_PKMN_450 4837 //pkmn_450
#define EVENT_OBJ_PAL_PKMN_451 4838 //pkmn_451
#define EVENT_OBJ_PAL_PKMN_452 4839 //pkmn_452
#define EVENT_OBJ_PAL_PKMN_453 4840 //pkmn_453
#define EVENT_OBJ_PAL_PKMN_454 4841 //pkmn_454
#define EVENT_OBJ_PAL_PKMN_455 4842 //pkmn_455
#define EVENT_OBJ_PAL_PKMN_456 4843 //pkmn_456
#define EVENT_OBJ_PAL_PKMN_457 4844 //pkmn_457
#define EVENT_OBJ_PAL_PKMN_458 4845 //pkmn_458
#define EVENT_OBJ_PAL_PKMN_459 4846 //pkmn_459
#define EVENT_OBJ_PAL_PKMN_460 4847 //pkmn_460
#define EVENT_OBJ_PAL_PKMN_461 4848 //pkmn_461
#define EVENT_OBJ_PAL_PKMN_462 4849 //pkmn_462
#define EVENT_OBJ_PAL_PKMN_463 4850 //pkmn_463
#define EVENT_OBJ_PAL_PKMN_464 4851 //pkmn_464
#define EVENT_OBJ_PAL_PKMN_465 4852 //pkmn_465
#define EVENT_OBJ_PAL_PKMN_466 4853 //pkmn_466
#define EVENT_OBJ_PAL_PKMN_467 4854 //pkmn_467
#define EVENT_OBJ_PAL_PKMN_468 4855 //pkmn_468
#define EVENT_OBJ_PAL_PKMN_469 4856 //pkmn_469
#define EVENT_OBJ_PAL_PKMN_470 4857 //pkmn_470
#define EVENT_OBJ_PAL_PKMN_471 4858 //pkmn_471
#define EVENT_OBJ_PAL_PKMN_472 4859 //pkmn_472
#define EVENT_OBJ_PAL_PKMN_473 4860 //pkmn_473
#define EVENT_OBJ_PAL_PKMN_474 4861 //pkmn_474
#define EVENT_OBJ_PAL_PKMN_475 4862 //pkmn_475
#define EVENT_OBJ_PAL_PKMN_476 4863 //pkmn_476
#define EVENT_OBJ_PAL_PKMN_477 4864 //pkmn_477
#define EVENT_OBJ_PAL_PKMN_478 4865 //pkmn_478
#define EVENT_OBJ_PAL_PKMN_479 4866 //pkmn_479
#define EVENT_OBJ_PAL_PKMN_480 4867 //pkmn_480
#define EVENT_OBJ_PAL_PKMN_481 4868 //pkmn_481
#define EVENT_OBJ_PAL_PKMN_482 4869 //pkmn_482
#define EVENT_OBJ_PAL_PKMN_483 4870 //pkmn_483
#define EVENT_OBJ_PAL_PKMN_484 4871 //pkmn_484
#define EVENT_OBJ_PAL_PKMN_485 4872 //pkmn_485
#define EVENT_OBJ_PAL_PKMN_486 4873 //pkmn_486
#define EVENT_OBJ_PAL_PKMN_487 4874 //pkmn_487
#define EVENT_OBJ_PAL_PKMN_488 4875 //pkmn_488
#define EVENT_OBJ_PAL_PKMN_489 4876 //pkmn_489
#define EVENT_OBJ_PAL_PKMN_490 4877 //pkmn_490
#define EVENT_OBJ_PAL_PKMN_491 4878 //pkmn_491
#define EVENT_OBJ_PAL_PKMN_492 4879 //pkmn_492
#define EVENT_OBJ_PAL_PKMN_493 4880 //pkmn_493
#define EVENT_OBJ_PAL_PKMN_494 4881 //pkmn_494
#define EVENT_OBJ_PAL_PKMN_495 4882 //pkmn_495
#define EVENT_OBJ_PAL_PKMN_496 4883 //pkmn_496
#define EVENT_OBJ_PAL_PKMN_497 4884 //pkmn_497
#define EVENT_OBJ_PAL_PKMN_498 4885 //pkmn_498
#define EVENT_OBJ_PAL_PKMN_499 4886 //pkmn_499
#define EVENT_OBJ_PAL_PKMN_500 4887 //pkmn_500
#define EVENT_OBJ_PAL_PKMN_501 4888 //pkmn_501
#define EVENT_OBJ_PAL_PKMN_502 4889 //pkmn_502
#define EVENT_OBJ_PAL_PKMN_503 4890 //pkmn_503
#define EVENT_OBJ_PAL_PKMN_504 4891 //pkmn_504
#define EVENT_OBJ_PAL_PKMN_505 4892 //pkmn_505
#define EVENT_OBJ_PAL_PKMN_506 4893 //pkmn_506
#define EVENT_OBJ_PAL_PKMN_507 4894 //pkmn_507
#define EVENT_OBJ_PAL_PKMN_508 4895 //pkmn_508
#define EVENT_OBJ_PAL_PKMN_509 4896 //pkmn_509
#define EVENT_OBJ_PAL_PKMN_510 4897 //pkmn_510
#define EVENT_OBJ_PAL_PKMN_511 4898 //pkmn_511
#define EVENT_OBJ_PAL_PKMN_512 4899 //pkmn_512
#define EVENT_OBJ_PAL_PKMN_513 4900 //pkmn_513
#define EVENT_OBJ_PAL_PKMN_514 4901 //pkmn_514
#define EVENT_OBJ_PAL_PKMN_515 4902 //pkmn_515
#define EVENT_OBJ_PAL_PKMN_516 4903 //pkmn_516
#define EVENT_OBJ_PAL_PKMN_517 4904 //pkmn_517
#define EVENT_OBJ_PAL_PKMN_518 4905 //pkmn_518
#define EVENT_OBJ_PAL_PKMN_519 4906 //pkmn_519
#define EVENT_OBJ_PAL_PKMN_520 4907 //pkmn_520
#define EVENT_OBJ_PAL_PKMN_521 4908 //pkmn_521
#define EVENT_OBJ_PAL_PKMN_522 4909 //pkmn_522
#define EVENT_OBJ_PAL_PKMN_523 4910 //pkmn_523
#define EVENT_OBJ_PAL_PKMN_524 4911 //pkmn_524
#define EVENT_OBJ_PAL_PKMN_525 4912 //pkmn_525
#define EVENT_OBJ_PAL_PKMN_526 4913 //pkmn_526
#define EVENT_OBJ_PAL_PKMN_527 4914 //pkmn_527
#define EVENT_OBJ_PAL_PKMN_528 4915 //pkmn_528
#define EVENT_OBJ_PAL_PKMN_529 4916 //pkmn_529
#define EVENT_OBJ_PAL_PKMN_530 4917 //pkmn_530
#define EVENT_OBJ_PAL_PKMN_531 4918 //pkmn_531
#define EVENT_OBJ_PAL_PKMN_532 4919 //pkmn_532
#define EVENT_OBJ_PAL_PKMN_533 4920 //pkmn_533
#define EVENT_OBJ_PAL_PKMN_534 4921 //pkmn_534
#define EVENT_OBJ_PAL_PKMN_535 4922 //pkmn_535
#define EVENT_OBJ_PAL_PKMN_536 4923 //pkmn_536
#define EVENT_OBJ_PAL_PKMN_537 4924 //pkmn_537
#define EVENT_OBJ_PAL_PKMN_538 4925 //pkmn_538
#define EVENT_OBJ_PAL_PKMN_539 4926 //pkmn_539
#define EVENT_OBJ_PAL_PKMN_540 4927 //pkmn_540
#define EVENT_OBJ_PAL_PKMN_541 4928 //pkmn_541
#define EVENT_OBJ_PAL_PKMN_542 4929 //pkmn_542
#define EVENT_OBJ_PAL_PKMN_543 4930 //pkmn_543
#define EVENT_OBJ_PAL_PKMN_544 4931 //pkmn_544
#define EVENT_OBJ_PAL_PKMN_545 4932 //pkmn_545
#define EVENT_OBJ_PAL_PKMN_546 4933 //pkmn_546
#define EVENT_OBJ_PAL_PKMN_547 4934 //pkmn_547
#define EVENT_OBJ_PAL_PKMN_548 4935 //pkmn_548
#define EVENT_OBJ_PAL_PKMN_549 4936 //pkmn_549
#define EVENT_OBJ_PAL_PKMN_550 4937 //pkmn_550
#define EVENT_OBJ_PAL_PKMN_551 4938 //pkmn_551
#define EVENT_OBJ_PAL_PKMN_552 4939 //pkmn_552
#define EVENT_OBJ_PAL_PKMN_553 4940 //pkmn_553
#define EVENT_OBJ_PAL_PKMN_554 4941 //pkmn_554
#define EVENT_OBJ_PAL_PKMN_555 4942 //pkmn_555
#define EVENT_OBJ_PAL_PKMN_556 4943 //pkmn_556
#define EVENT_OBJ_PAL_PKMN_557 4944 //pkmn_557
#define EVENT_OBJ_PAL_PKMN_558 4945 //pkmn_558
#define EVENT_OBJ_PAL_PKMN_559 4946 //pkmn_559
#define EVENT_OBJ_PAL_PKMN_560 4947 //pkmn_560
#define EVENT_OBJ_PAL_PKMN_561 4948 //pkmn_561
#define EVENT_OBJ_PAL_PKMN_562 4949 //pkmn_562
#define EVENT_OBJ_PAL_PKMN_563 4950 //pkmn_563
#define EVENT_OBJ_PAL_PKMN_564 4951 //pkmn_564
#define EVENT_OBJ_PAL_PKMN_565 4952 //pkmn_565
#define EVENT_OBJ_PAL_PKMN_566 4953 //pkmn_566
#define EVENT_OBJ_PAL_PKMN_567 4954 //pkmn_567
#define EVENT_OBJ_PAL_PKMN_568 4955 //pkmn_568
#define EVENT_OBJ_PAL_PKMN_569 4956 //pkmn_569
#define EVENT_OBJ_PAL_PKMN_570 4957 //pkmn_570
#define EVENT_OBJ_PAL_PKMN_571 4958 //pkmn_571
#define EVENT_OBJ_PAL_PKMN_572 4959 //pkmn_572
#define EVENT_OBJ_PAL_PKMN_573 4960 //pkmn_573
#define EVENT_OBJ_PAL_PKMN_574 4961 //pkmn_574
#define EVENT_OBJ_PAL_PKMN_575 4962 //pkmn_575
#define EVENT_OBJ_PAL_PKMN_576 4963 //pkmn_576
#define EVENT_OBJ_PAL_PKMN_577 4964 //pkmn_577
#define EVENT_OBJ_PAL_PKMN_578 4965 //pkmn_578
#define EVENT_OBJ_PAL_PKMN_579 4966 //pkmn_579
#define EVENT_OBJ_PAL_PKMN_580 4967 //pkmn_580
#define EVENT_OBJ_PAL_PKMN_581 4968 //pkmn_581
#define EVENT_OBJ_PAL_PKMN_582 4969 //pkmn_582
#define EVENT_OBJ_PAL_PKMN_583 4970 //pkmn_583
#define EVENT_OBJ_PAL_PKMN_584 4971 //pkmn_584
#define EVENT_OBJ_PAL_PKMN_585 4972 //pkmn_585
#define EVENT_OBJ_PAL_PKMN_586 4973 //pkmn_586
#define EVENT_OBJ_PAL_PKMN_587 4974 //pkmn_587
#define EVENT_OBJ_PAL_PKMN_588 4975 //pkmn_588
#define EVENT_OBJ_PAL_PKMN_589 4976 //pkmn_589
#define EVENT_OBJ_PAL_PKMN_590 4977 //pkmn_590
#define EVENT_OBJ_PAL_PKMN_591 4978 //pkmn_591
#define EVENT_OBJ_PAL_PKMN_592 4979 //pkmn_592
#define EVENT_OBJ_PAL_PKMN_593 4980 //pkmn_593
#define EVENT_OBJ_PAL_PKMN_594 4981 //pkmn_594
#define EVENT_OBJ_PAL_PKMN_595 4982 //pkmn_595
#define EVENT_OBJ_PAL_PKMN_596 4983 //pkmn_596
#define EVENT_OBJ_PAL_PKMN_597 4984 //pkmn_597
#define EVENT_OBJ_PAL_PKMN_598 4985 //pkmn_598
#define EVENT_OBJ_PAL_PKMN_599 4986 //pkmn_599
#define EVENT_OBJ_PAL_PKMN_600 4987 //pkmn_600
#define EVENT_OBJ_PAL_PKMN_601 4988 //pkmn_601
#define EVENT_OBJ_PAL_PKMN_602 4989 //pkmn_602
#define EVENT_OBJ_PAL_PKMN_603 4990 //pkmn_603
#define EVENT_OBJ_PAL_PKMN_604 4991 //pkmn_604
#define EVENT_OBJ_PAL_PKMN_605 4992 //pkmn_605
#define EVENT_OBJ_PAL_PKMN_606 4993 //pkmn_606
#define EVENT_OBJ_PAL_PKMN_607 4994 //pkmn_607
#define EVENT_OBJ_PAL_PKMN_608 4995 //pkmn_608
#define EVENT_OBJ_PAL_PKMN_609 4996 //pkmn_609
#define EVENT_OBJ_PAL_PKMN_610 4997 //pkmn_610
#define EVENT_OBJ_PAL_PKMN_611 4998 //pkmn_611
#define EVENT_OBJ_PAL_PKMN_612 4999 //pkmn_612
#define EVENT_OBJ_PAL_PKMN_613 5000 //pkmn_613
#define EVENT_OBJ_PAL_PKMN_614 5001 //pkmn_614
#define EVENT_OBJ_PAL_PKMN_615 5002 //pkmn_615
#define EVENT_OBJ_PAL_PKMN_616 5003 //pkmn_616
#define EVENT_OBJ_PAL_PKMN_617 5004 //pkmn_617
#define EVENT_OBJ_PAL_PKMN_618 5005 //pkmn_618
#define EVENT_OBJ_PAL_PKMN_619 5006 //pkmn_619
#define EVENT_OBJ_PAL_PKMN_620 5007 //pkmn_620
#define EVENT_OBJ_PAL_PKMN_621 5008 //pkmn_621
#define EVENT_OBJ_PAL_PKMN_622 5009 //pkmn_622
#define EVENT_OBJ_PAL_PKMN_623 5010 //pkmn_623
#define EVENT_OBJ_PAL_PKMN_624 5011 //pkmn_624
#define EVENT_OBJ_PAL_PKMN_625 5012 //pkmn_625
#define EVENT_OBJ_PAL_PKMN_626 5013 //pkmn_626
#define EVENT_OBJ_PAL_PKMN_627 5014 //pkmn_627
#define EVENT_OBJ_PAL_PKMN_628 5015 //pkmn_628
#define EVENT_OBJ_PAL_PKMN_629 5016 //pkmn_629
#define EVENT_OBJ_PAL_PKMN_630 5017 //pkmn_630
#define EVENT_OBJ_PAL_PKMN_631 5018 //pkmn_631
#define EVENT_OBJ_PAL_PKMN_632 5019 //pkmn_632
#define EVENT_OBJ_PAL_PKMN_633 5020 //pkmn_633
#define EVENT_OBJ_PAL_PKMN_634 5021 //pkmn_634
#define EVENT_OBJ_PAL_PKMN_635 5022 //pkmn_635
#define EVENT_OBJ_PAL_PKMN_636 5023 //pkmn_636
#define EVENT_OBJ_PAL_PKMN_637 5024 //pkmn_637
#define EVENT_OBJ_PAL_PKMN_638 5025 //pkmn_638
#define EVENT_OBJ_PAL_PKMN_639 5026 //pkmn_639
#define EVENT_OBJ_PAL_PKMN_640 5027 //pkmn_640
#define EVENT_OBJ_PAL_PKMN_641 5028 //pkmn_641
#define EVENT_OBJ_PAL_PKMN_642 5029 //pkmn_642
#define EVENT_OBJ_PAL_PKMN_643 5030 //pkmn_643
#define EVENT_OBJ_PAL_PKMN_644 5031 //pkmn_644
#define EVENT_OBJ_PAL_PKMN_645 5032 //pkmn_645
#define EVENT_OBJ_PAL_PKMN_646 5033 //pkmn_646
#define EVENT_OBJ_PAL_PKMN_647 5034 //pkmn_647
#define EVENT_OBJ_PAL_PKMN_648 5035 //pkmn_648
#define EVENT_OBJ_PAL_PKMN_649 5036 //pkmn_649
#define EVENT_OBJ_PAL_PKMN_650 5037 //pkmn_650
#define EVENT_OBJ_PAL_PKMN_651 5038 //pkmn_651
#define EVENT_OBJ_PAL_PKMN_652 5039 //pkmn_652
#define EVENT_OBJ_PAL_PKMN_653 5040 //pkmn_653
#define EVENT_OBJ_PAL_PKMN_654 5041 //pkmn_654
#define EVENT_OBJ_PAL_PKMN_655 5042 //pkmn_655
#define EVENT_OBJ_PAL_PKMN_656 5043 //pkmn_656
#define EVENT_OBJ_PAL_PKMN_657 5044 //pkmn_657
#define EVENT_OBJ_PAL_PKMN_658 5045 //pkmn_658
#define EVENT_OBJ_PAL_PKMN_659 5046 //pkmn_659
#define EVENT_OBJ_PAL_PKMN_660 5047 //pkmn_660
#define EVENT_OBJ_PAL_PKMN_661 5048 //pkmn_661
#define EVENT_OBJ_PAL_PKMN_662 5049 //pkmn_662
#define EVENT_OBJ_PAL_PKMN_663 5050 //pkmn_663
#define EVENT_OBJ_PAL_PKMN_664 5051 //pkmn_664
#define EVENT_OBJ_PAL_PKMN_665 5052 //pkmn_665
#define EVENT_OBJ_PAL_PKMN_666 5053 //pkmn_666
#define EVENT_OBJ_PAL_PKMN_667 5054 //pkmn_667
#define EVENT_OBJ_PAL_PKMN_668 5055 //pkmn_668
#define EVENT_OBJ_PAL_PKMN_669 5056 //pkmn_669
#define EVENT_OBJ_PAL_PKMN_670 5057 //pkmn_670
#define EVENT_OBJ_PAL_PKMN_671 5058 //pkmn_671
#define EVENT_OBJ_PAL_PKMN_672 5059 //pkmn_672
#define EVENT_OBJ_PAL_PKMN_673 5060 //pkmn_673
#define EVENT_OBJ_PAL_PKMN_674 5061 //pkmn_674
#define EVENT_OBJ_PAL_PKMN_675 5062 //pkmn_675
#define EVENT_OBJ_PAL_PKMN_676 5063 //pkmn_676
#define EVENT_OBJ_PAL_PKMN_677 5064 //pkmn_677
#define EVENT_OBJ_PAL_PKMN_678 5065 //pkmn_678
#define EVENT_OBJ_PAL_PKMN_679 5066 //pkmn_679
#define EVENT_OBJ_PAL_PKMN_680 5067 //pkmn_680
#define EVENT_OBJ_PAL_PKMN_681 5068 //pkmn_681
#define EVENT_OBJ_PAL_PKMN_682 5069 //pkmn_682
#define EVENT_OBJ_PAL_PKMN_683 5070 //pkmn_683
#define EVENT_OBJ_PAL_PKMN_684 5071 //pkmn_684
#define EVENT_OBJ_PAL_PKMN_685 5072 //pkmn_685
#define EVENT_OBJ_PAL_PKMN_686 5073 //pkmn_686
#define EVENT_OBJ_PAL_PKMN_687 5074 //pkmn_687
#define EVENT_OBJ_PAL_PKMN_688 5075 //pkmn_688
#define EVENT_OBJ_PAL_PKMN_689 5076 //pkmn_689
#define EVENT_OBJ_PAL_PKMN_690 5077 //pkmn_690
#define EVENT_OBJ_PAL_PKMN_691 5078 //pkmn_691
#define EVENT_OBJ_PAL_PKMN_692 5079 //pkmn_692
#define EVENT_OBJ_PAL_PKMN_693 5080 //pkmn_693
#define EVENT_OBJ_PAL_PKMN_694 5081 //pkmn_694
#define EVENT_OBJ_PAL_PKMN_695 5082 //pkmn_695
#define EVENT_OBJ_PAL_PKMN_696 5083 //pkmn_696
#define EVENT_OBJ_PAL_PKMN_697 5084 //pkmn_697
#define EVENT_OBJ_PAL_PKMN_698 5085 //pkmn_698
#define EVENT_OBJ_PAL_PKMN_699 5086 //pkmn_699
#define EVENT_OBJ_PAL_PKMN_700 5087 //pkmn_700
#define EVENT_OBJ_PAL_PKMN_701 5088 //pkmn_701
#define EVENT_OBJ_PAL_PKMN_702 5089 //pkmn_702
#define EVENT_OBJ_PAL_PKMN_703 5090 //pkmn_703
#define EVENT_OBJ_PAL_PKMN_704 5091 //pkmn_704
#define EVENT_OBJ_PAL_PKMN_705 5092 //pkmn_705
#define EVENT_OBJ_PAL_PKMN_706 5093 //pkmn_706
#define EVENT_OBJ_PAL_PKMN_707 5094 //pkmn_707
#define EVENT_OBJ_PAL_PKMN_708 5095 //pkmn_708
#define EVENT_OBJ_PAL_PKMN_709 5096 //pkmn_709
#define EVENT_OBJ_PAL_PKMN_710 5097 //pkmn_710
#define EVENT_OBJ_PAL_PKMN_711 5098 //pkmn_711
#define EVENT_OBJ_PAL_PKMN_712 5099 //pkmn_712
#define EVENT_OBJ_PAL_PKMN_713 5100 //pkmn_713
#define EVENT_OBJ_PAL_PKMN_714 5101 //pkmn_714
#define EVENT_OBJ_PAL_PKMN_715 5102 //pkmn_715
#define EVENT_OBJ_PAL_PKMN_716 5103 //pkmn_716
#define EVENT_OBJ_PAL_PKMN_717 5104 //pkmn_717
#define EVENT_OBJ_PAL_PKMN_718 5105 //pkmn_718
#define EVENT_OBJ_PAL_PKMN_719 5106 //pkmn_719
#define EVENT_OBJ_PAL_PKMN_720 5107 //pkmn_720
#define EVENT_OBJ_PAL_PKMN_721 5108 //pkmn_721
#define EVENT_OBJ_PAL_PKMN_722 5109 //pkmn_722
#define EVENT_OBJ_PAL_PKMN_723 5110 //pkmn_723
#define EVENT_OBJ_PAL_PKMN_724 5111 //pkmn_724
#define EVENT_OBJ_PAL_PKMN_725 5112 //pkmn_725
#define EVENT_OBJ_PAL_PKMN_726 5113 //pkmn_726
#define EVENT_OBJ_PAL_PKMN_727 5114 //pkmn_727
#define EVENT_OBJ_PAL_PKMN_728 5115 //pkmn_728
#define EVENT_OBJ_PAL_PKMN_729 5116 //pkmn_729
#define EVENT_OBJ_PAL_PKMN_730 5117 //pkmn_730
#define EVENT_OBJ_PAL_PKMN_731 5118 //pkmn_731
#define EVENT_OBJ_PAL_PKMN_732 5119 //pkmn_732
#define EVENT_OBJ_PAL_PKMN_733 5120 //pkmn_733
#define EVENT_OBJ_PAL_PKMN_734 5121 //pkmn_734
#define EVENT_OBJ_PAL_PKMN_735 5122 //pkmn_735
#define EVENT_OBJ_PAL_PKMN_736 5123 //pkmn_736
#define EVENT_OBJ_PAL_PKMN_737 5124 //pkmn_737
#define EVENT_OBJ_PAL_PKMN_738 5125 //pkmn_738
#define EVENT_OBJ_PAL_PKMN_739 5126 //pkmn_739
#define EVENT_OBJ_PAL_PKMN_740 5127 //pkmn_740
#define EVENT_OBJ_PAL_PKMN_741 5128 //pkmn_741
#define EVENT_OBJ_PAL_PKMN_742 5129 //pkmn_742
#define EVENT_OBJ_PAL_PKMN_743 5130 //pkmn_743
#define EVENT_OBJ_PAL_PKMN_744 5131 //pkmn_744
#define EVENT_OBJ_PAL_PKMN_745 5132 //pkmn_745
#define EVENT_OBJ_PAL_PKMN_746 5133 //pkmn_746
#define EVENT_OBJ_PAL_PKMN_747 5134 //pkmn_747
#define EVENT_OBJ_PAL_PKMN_748 5135 //pkmn_748
#define EVENT_OBJ_PAL_PKMN_749 5136 //pkmn_749
#define EVENT_OBJ_PAL_PKMN_750 5137 //pkmn_750
#define EVENT_OBJ_PAL_PKMN_751 5138 //pkmn_751
#define EVENT_OBJ_PAL_PKMN_752 5139 //pkmn_752
#define EVENT_OBJ_PAL_PKMN_753 5140 //pkmn_753
#define EVENT_OBJ_PAL_PKMN_754 5141 //pkmn_754
#define EVENT_OBJ_PAL_PKMN_755 5142 //pkmn_755
#define EVENT_OBJ_PAL_PKMN_756 5143 //pkmn_756
#define EVENT_OBJ_PAL_PKMN_757 5144 //pkmn_757
#define EVENT_OBJ_PAL_PKMN_758 5145 //pkmn_758
#define EVENT_OBJ_PAL_PKMN_759 5146 //pkmn_759
#define EVENT_OBJ_PAL_PKMN_760 5147 //pkmn_760
#define EVENT_OBJ_PAL_PKMN_761 5148 //pkmn_761
#define EVENT_OBJ_PAL_PKMN_762 5149 //pkmn_762
#define EVENT_OBJ_PAL_PKMN_763 5150 //pkmn_763
#define EVENT_OBJ_PAL_PKMN_764 5151 //pkmn_764
#define EVENT_OBJ_PAL_PKMN_765 5152 //pkmn_765
#define EVENT_OBJ_PAL_PKMN_766 5153 //pkmn_766
#define EVENT_OBJ_PAL_PKMN_767 5154 //pkmn_767
#define EVENT_OBJ_PAL_PKMN_768 5155 //pkmn_768
#define EVENT_OBJ_PAL_PKMN_769 5156 //pkmn_769
#define EVENT_OBJ_PAL_PKMN_770 5157 //pkmn_770
#define EVENT_OBJ_PAL_PKMN_771 5158 //pkmn_771
#define EVENT_OBJ_PAL_PKMN_772 5159 //pkmn_772
#define EVENT_OBJ_PAL_PKMN_773 5160 //pkmn_773
#define EVENT_OBJ_PAL_PKMN_774 5161 //pkmn_774
#define EVENT_OBJ_PAL_PKMN_775 5162 //pkmn_775
#define EVENT_OBJ_PAL_PKMN_776 5163 //pkmn_776
#define EVENT_OBJ_PAL_PKMN_777 5164 //pkmn_777
#define EVENT_OBJ_PAL_PKMN_778 5165 //pkmn_778
#define EVENT_OBJ_PAL_PKMN_779 5166 //pkmn_779
#define EVENT_OBJ_PAL_PKMN_780 5167 //pkmn_780
#define EVENT_OBJ_PAL_PKMN_781 5168 //pkmn_781
#define EVENT_OBJ_PAL_PKMN_782 5169 //pkmn_782
#define EVENT_OBJ_PAL_PKMN_783 5170 //pkmn_783
#define EVENT_OBJ_PAL_PKMN_784 5171 //pkmn_784
#define EVENT_OBJ_PAL_PKMN_785 5172 //pkmn_785
#define EVENT_OBJ_PAL_PKMN_786 5173 //pkmn_786
#define EVENT_OBJ_PAL_PKMN_787 5174 //pkmn_787
#define EVENT_OBJ_PAL_PKMN_788 5175 //pkmn_788
#define EVENT_OBJ_PAL_PKMN_789 5176 //pkmn_789
#define EVENT_OBJ_PAL_PKMN_790 5177 //pkmn_790
#define EVENT_OBJ_PAL_PKMN_791 5178 //pkmn_791
#define EVENT_OBJ_PAL_PKMN_792 5179 //pkmn_792
#define EVENT_OBJ_PAL_PKMN_793 5180 //pkmn_793
#define EVENT_OBJ_PAL_PKMN_794 5181 //pkmn_794
#define EVENT_OBJ_PAL_PKMN_795 5182 //pkmn_795
#define EVENT_OBJ_PAL_PKMN_796 5183 //pkmn_796
#define EVENT_OBJ_PAL_PKMN_797 5184 //pkmn_797
#define EVENT_OBJ_PAL_PKMN_798 5185 //pkmn_798
#define EVENT_OBJ_PAL_PKMN_799 5186 //pkmn_799
#define EVENT_OBJ_PAL_PKMN_800 5187 //pkmn_800
#define EVENT_OBJ_PAL_PKMN_801 5188 //pkmn_801
#define EVENT_OBJ_PAL_PKMN_802 5189 //pkmn_802
#define EVENT_OBJ_PAL_PKMN_803 5190 //pkmn_803
#define EVENT_OBJ_PAL_PKMN_804 5191 //pkmn_804
#define EVENT_OBJ_PAL_PKMN_805 5192 //pkmn_805
#define EVENT_OBJ_PAL_PKMN_806 5193 //pkmn_806
#define EVENT_OBJ_PAL_PKMN_807 5194 //pkmn_807
#define EVENT_OBJ_PAL_TAG_NONE 0x14FF

#include "data/field_event_obj/field_effect_object_template_pointers.h"
#include "data/field_event_obj/event_object_pic_tables.h"
#include "data/field_event_obj/event_object_anims.h"
#include "data/field_event_obj/base_oam.h"
#include "data/field_event_obj/event_object_subsprites.h"
#include "data/field_event_obj/event_object_graphics_info.h"
#include "data/field_event_obj/event_object_graphics_info_pointers.h"

const struct SpritePalette sEventObjectSpritePalettes[] = {
    {gEventObjectPalette0,  EVENT_OBJ_PAL_TAG_0},
    {gEventObjectPalette1,  EVENT_OBJ_PAL_TAG_1},
    {gEventObjectPalette2,  EVENT_OBJ_PAL_TAG_2},
    {gEventObjectPalette3,  EVENT_OBJ_PAL_TAG_3},
    {gEventObjectPalette4,  EVENT_OBJ_PAL_TAG_4},
    {gEventObjectPalette5,  EVENT_OBJ_PAL_TAG_5},
    {gEventObjectPalette6,  EVENT_OBJ_PAL_TAG_6},
    {gEventObjectPalette7,  EVENT_OBJ_PAL_TAG_7},
    {gEventObjectPalette8,  EVENT_OBJ_PAL_TAG_8},
    {gEventObjectPalette9,  EVENT_OBJ_PAL_TAG_9},
    {gEventObjectPalette10, EVENT_OBJ_PAL_TAG_10},
    {gEventObjectPalette11, EVENT_OBJ_PAL_TAG_11},
    {gEventObjectPalette12, EVENT_OBJ_PAL_TAG_12},
    {gEventObjectPalette13, EVENT_OBJ_PAL_TAG_13},
    {gEventObjectPalette14, EVENT_OBJ_PAL_TAG_14},
    {gEventObjectPalette15, EVENT_OBJ_PAL_TAG_15},
    {gEventObjectPalette16, EVENT_OBJ_PAL_TAG_16},
    {gEventObjectPalette17, EVENT_OBJ_PAL_TAG_17},
    {gEventObjectPalette18, EVENT_OBJ_PAL_TAG_18},
    {gEventObjectPalette19, EVENT_OBJ_PAL_TAG_19},
    {gEventObjectPalette20, EVENT_OBJ_PAL_TAG_20},
    {gEventObjectPalette21, EVENT_OBJ_PAL_TAG_21},
    {gEventObjectPalette22, EVENT_OBJ_PAL_TAG_22},
    {gEventObjectPalette23, EVENT_OBJ_PAL_TAG_23},
    {gEventObjectPalette24, EVENT_OBJ_PAL_TAG_24},
    {gEventObjectPalette25, EVENT_OBJ_PAL_TAG_25},
    {gEventObjectPalette26, EVENT_OBJ_PAL_TAG_26},
    {gEventObjectPalette27, EVENT_OBJ_PAL_TAG_27},
    {gEventObjectPalette28, EVENT_OBJ_PAL_TAG_28},
    {gEventObjectPalette29, EVENT_OBJ_PAL_TAG_29},
    {gEventObjectPalette30, EVENT_OBJ_PAL_TAG_30},
    {gEventObjectPalette31, EVENT_OBJ_PAL_TAG_31},
    {gEventObjectPalette32, EVENT_OBJ_PAL_TAG_32},
    {gEventObjectPalette33, EVENT_OBJ_PAL_TAG_33},
    {gEventObjectPalette34, EVENT_OBJ_PAL_TAG_34},
    {gEventObjectPalette_pkmn_1, EVENT_OBJ_PAL_PKMN_1},
    {gEventObjectPalette_pkmn_2, EVENT_OBJ_PAL_PKMN_2},
    {gEventObjectPalette_pkmn_3, EVENT_OBJ_PAL_PKMN_3},
    {gEventObjectPalette_pkmn_4, EVENT_OBJ_PAL_PKMN_4},
    {gEventObjectPalette_pkmn_5, EVENT_OBJ_PAL_PKMN_5},
    {gEventObjectPalette_pkmn_6, EVENT_OBJ_PAL_PKMN_6},
    {gEventObjectPalette_pkmn_7, EVENT_OBJ_PAL_PKMN_7},
    {gEventObjectPalette_pkmn_8, EVENT_OBJ_PAL_PKMN_8},
    {gEventObjectPalette_pkmn_9, EVENT_OBJ_PAL_PKMN_9},
    {gEventObjectPalette_pkmn_10, EVENT_OBJ_PAL_PKMN_10},
    {gEventObjectPalette_pkmn_11, EVENT_OBJ_PAL_PKMN_11},
    {gEventObjectPalette_pkmn_12, EVENT_OBJ_PAL_PKMN_12},
    {gEventObjectPalette_pkmn_13, EVENT_OBJ_PAL_PKMN_13},
    {gEventObjectPalette_pkmn_14, EVENT_OBJ_PAL_PKMN_14},
    {gEventObjectPalette_pkmn_15, EVENT_OBJ_PAL_PKMN_15},
    {gEventObjectPalette_pkmn_16, EVENT_OBJ_PAL_PKMN_16},
    {gEventObjectPalette_pkmn_17, EVENT_OBJ_PAL_PKMN_17},
    {gEventObjectPalette_pkmn_18, EVENT_OBJ_PAL_PKMN_18},
    {gEventObjectPalette_pkmn_19, EVENT_OBJ_PAL_PKMN_19},
    {gEventObjectPalette_pkmn_20, EVENT_OBJ_PAL_PKMN_20},
    {gEventObjectPalette_pkmn_21, EVENT_OBJ_PAL_PKMN_21},
    {gEventObjectPalette_pkmn_22, EVENT_OBJ_PAL_PKMN_22},
    {gEventObjectPalette_pkmn_23, EVENT_OBJ_PAL_PKMN_23},
    {gEventObjectPalette_pkmn_24, EVENT_OBJ_PAL_PKMN_24},
    {gEventObjectPalette_pkmn_25, EVENT_OBJ_PAL_PKMN_25},
    {gEventObjectPalette_pkmn_26, EVENT_OBJ_PAL_PKMN_26},
    {gEventObjectPalette_pkmn_27, EVENT_OBJ_PAL_PKMN_27},
    {gEventObjectPalette_pkmn_28, EVENT_OBJ_PAL_PKMN_28},
    {gEventObjectPalette_pkmn_29, EVENT_OBJ_PAL_PKMN_29},
    {gEventObjectPalette_pkmn_30, EVENT_OBJ_PAL_PKMN_30},
    {gEventObjectPalette_pkmn_31, EVENT_OBJ_PAL_PKMN_31},
    {gEventObjectPalette_pkmn_32, EVENT_OBJ_PAL_PKMN_32},
    {gEventObjectPalette_pkmn_33, EVENT_OBJ_PAL_PKMN_33},
    {gEventObjectPalette_pkmn_34, EVENT_OBJ_PAL_PKMN_34},
    {gEventObjectPalette_pkmn_35, EVENT_OBJ_PAL_PKMN_35},
    {gEventObjectPalette_pkmn_36, EVENT_OBJ_PAL_PKMN_36},
    {gEventObjectPalette_pkmn_37, EVENT_OBJ_PAL_PKMN_37},
    {gEventObjectPalette_pkmn_38, EVENT_OBJ_PAL_PKMN_38},
    {gEventObjectPalette_pkmn_39, EVENT_OBJ_PAL_PKMN_39},
    {gEventObjectPalette_pkmn_40, EVENT_OBJ_PAL_PKMN_40},
    {gEventObjectPalette_pkmn_41, EVENT_OBJ_PAL_PKMN_41},
    {gEventObjectPalette_pkmn_42, EVENT_OBJ_PAL_PKMN_42},
    {gEventObjectPalette_pkmn_43, EVENT_OBJ_PAL_PKMN_43},
    {gEventObjectPalette_pkmn_44, EVENT_OBJ_PAL_PKMN_44},
    {gEventObjectPalette_pkmn_45, EVENT_OBJ_PAL_PKMN_45},
    {gEventObjectPalette_pkmn_46, EVENT_OBJ_PAL_PKMN_46},
    {gEventObjectPalette_pkmn_47, EVENT_OBJ_PAL_PKMN_47},
    {gEventObjectPalette_pkmn_48, EVENT_OBJ_PAL_PKMN_48},
    {gEventObjectPalette_pkmn_49, EVENT_OBJ_PAL_PKMN_49},
    {gEventObjectPalette_pkmn_50, EVENT_OBJ_PAL_PKMN_50},
    {gEventObjectPalette_pkmn_51, EVENT_OBJ_PAL_PKMN_51},
    {gEventObjectPalette_pkmn_52, EVENT_OBJ_PAL_PKMN_52},
    {gEventObjectPalette_pkmn_53, EVENT_OBJ_PAL_PKMN_53},
    {gEventObjectPalette_pkmn_54, EVENT_OBJ_PAL_PKMN_54},
    {gEventObjectPalette_pkmn_55, EVENT_OBJ_PAL_PKMN_55},
    {gEventObjectPalette_pkmn_56, EVENT_OBJ_PAL_PKMN_56},
    {gEventObjectPalette_pkmn_57, EVENT_OBJ_PAL_PKMN_57},
    {gEventObjectPalette_pkmn_58, EVENT_OBJ_PAL_PKMN_58},
    {gEventObjectPalette_pkmn_59, EVENT_OBJ_PAL_PKMN_59},
    {gEventObjectPalette_pkmn_60, EVENT_OBJ_PAL_PKMN_60},
    {gEventObjectPalette_pkmn_61, EVENT_OBJ_PAL_PKMN_61},
    {gEventObjectPalette_pkmn_62, EVENT_OBJ_PAL_PKMN_62},
    {gEventObjectPalette_pkmn_63, EVENT_OBJ_PAL_PKMN_63},
    {gEventObjectPalette_pkmn_64, EVENT_OBJ_PAL_PKMN_64},
    {gEventObjectPalette_pkmn_65, EVENT_OBJ_PAL_PKMN_65},
    {gEventObjectPalette_pkmn_66, EVENT_OBJ_PAL_PKMN_66},
    {gEventObjectPalette_pkmn_67, EVENT_OBJ_PAL_PKMN_67},
    {gEventObjectPalette_pkmn_68, EVENT_OBJ_PAL_PKMN_68},
    {gEventObjectPalette_pkmn_69, EVENT_OBJ_PAL_PKMN_69},
    {gEventObjectPalette_pkmn_70, EVENT_OBJ_PAL_PKMN_70},
    {gEventObjectPalette_pkmn_71, EVENT_OBJ_PAL_PKMN_71},
    {gEventObjectPalette_pkmn_72, EVENT_OBJ_PAL_PKMN_72},
    {gEventObjectPalette_pkmn_73, EVENT_OBJ_PAL_PKMN_73},
    {gEventObjectPalette_pkmn_74, EVENT_OBJ_PAL_PKMN_74},
    {gEventObjectPalette_pkmn_75, EVENT_OBJ_PAL_PKMN_75},
    {gEventObjectPalette_pkmn_76, EVENT_OBJ_PAL_PKMN_76},
    {gEventObjectPalette_pkmn_77, EVENT_OBJ_PAL_PKMN_77},
    {gEventObjectPalette_pkmn_78, EVENT_OBJ_PAL_PKMN_78},
    {gEventObjectPalette_pkmn_79, EVENT_OBJ_PAL_PKMN_79},
    {gEventObjectPalette_pkmn_80, EVENT_OBJ_PAL_PKMN_80},
    {gEventObjectPalette_pkmn_81, EVENT_OBJ_PAL_PKMN_81},
    {gEventObjectPalette_pkmn_82, EVENT_OBJ_PAL_PKMN_82},
    {gEventObjectPalette_pkmn_83, EVENT_OBJ_PAL_PKMN_83},
    {gEventObjectPalette_pkmn_84, EVENT_OBJ_PAL_PKMN_84},
    {gEventObjectPalette_pkmn_85, EVENT_OBJ_PAL_PKMN_85},
    {gEventObjectPalette_pkmn_86, EVENT_OBJ_PAL_PKMN_86},
    {gEventObjectPalette_pkmn_87, EVENT_OBJ_PAL_PKMN_87},
    {gEventObjectPalette_pkmn_88, EVENT_OBJ_PAL_PKMN_88},
    {gEventObjectPalette_pkmn_89, EVENT_OBJ_PAL_PKMN_89},
    {gEventObjectPalette_pkmn_90, EVENT_OBJ_PAL_PKMN_90},
    {gEventObjectPalette_pkmn_91, EVENT_OBJ_PAL_PKMN_91},
    {gEventObjectPalette_pkmn_92, EVENT_OBJ_PAL_PKMN_92},
    {gEventObjectPalette_pkmn_93, EVENT_OBJ_PAL_PKMN_93},
    {gEventObjectPalette_pkmn_94, EVENT_OBJ_PAL_PKMN_94},
    {gEventObjectPalette_pkmn_95, EVENT_OBJ_PAL_PKMN_95},
    {gEventObjectPalette_pkmn_96, EVENT_OBJ_PAL_PKMN_96},
    {gEventObjectPalette_pkmn_97, EVENT_OBJ_PAL_PKMN_97},
    {gEventObjectPalette_pkmn_98, EVENT_OBJ_PAL_PKMN_98},
    {gEventObjectPalette_pkmn_99, EVENT_OBJ_PAL_PKMN_99},
    {gEventObjectPalette_pkmn_100, EVENT_OBJ_PAL_PKMN_100},
    {gEventObjectPalette_pkmn_101, EVENT_OBJ_PAL_PKMN_101},
    {gEventObjectPalette_pkmn_102, EVENT_OBJ_PAL_PKMN_102},
    {gEventObjectPalette_pkmn_103, EVENT_OBJ_PAL_PKMN_103},
    {gEventObjectPalette_pkmn_104, EVENT_OBJ_PAL_PKMN_104},
    {gEventObjectPalette_pkmn_105, EVENT_OBJ_PAL_PKMN_105},
    {gEventObjectPalette_pkmn_106, EVENT_OBJ_PAL_PKMN_106},
    {gEventObjectPalette_pkmn_107, EVENT_OBJ_PAL_PKMN_107},
    {gEventObjectPalette_pkmn_108, EVENT_OBJ_PAL_PKMN_108},
    {gEventObjectPalette_pkmn_109, EVENT_OBJ_PAL_PKMN_109},
    {gEventObjectPalette_pkmn_110, EVENT_OBJ_PAL_PKMN_110},
    {gEventObjectPalette_pkmn_111, EVENT_OBJ_PAL_PKMN_111},
    {gEventObjectPalette_pkmn_112, EVENT_OBJ_PAL_PKMN_112},
    {gEventObjectPalette_pkmn_113, EVENT_OBJ_PAL_PKMN_113},
    {gEventObjectPalette_pkmn_114, EVENT_OBJ_PAL_PKMN_114},
    {gEventObjectPalette_pkmn_115, EVENT_OBJ_PAL_PKMN_115},
    {gEventObjectPalette_pkmn_116, EVENT_OBJ_PAL_PKMN_116},
    {gEventObjectPalette_pkmn_117, EVENT_OBJ_PAL_PKMN_117},
    {gEventObjectPalette_pkmn_118, EVENT_OBJ_PAL_PKMN_118},
    {gEventObjectPalette_pkmn_119, EVENT_OBJ_PAL_PKMN_119},
    {gEventObjectPalette_pkmn_120, EVENT_OBJ_PAL_PKMN_120},
    {gEventObjectPalette_pkmn_121, EVENT_OBJ_PAL_PKMN_121},
    {gEventObjectPalette_pkmn_122, EVENT_OBJ_PAL_PKMN_122},
    {gEventObjectPalette_pkmn_123, EVENT_OBJ_PAL_PKMN_123},
    {gEventObjectPalette_pkmn_124, EVENT_OBJ_PAL_PKMN_124},
    {gEventObjectPalette_pkmn_125, EVENT_OBJ_PAL_PKMN_125},
    {gEventObjectPalette_pkmn_126, EVENT_OBJ_PAL_PKMN_126},
    {gEventObjectPalette_pkmn_127, EVENT_OBJ_PAL_PKMN_127},
    {gEventObjectPalette_pkmn_128, EVENT_OBJ_PAL_PKMN_128},
    {gEventObjectPalette_pkmn_129, EVENT_OBJ_PAL_PKMN_129},
    {gEventObjectPalette_pkmn_130, EVENT_OBJ_PAL_PKMN_130},
    {gEventObjectPalette_pkmn_131, EVENT_OBJ_PAL_PKMN_131},
    {gEventObjectPalette_pkmn_132, EVENT_OBJ_PAL_PKMN_132},
    {gEventObjectPalette_pkmn_133, EVENT_OBJ_PAL_PKMN_133},
    {gEventObjectPalette_pkmn_134, EVENT_OBJ_PAL_PKMN_134},
    {gEventObjectPalette_pkmn_135, EVENT_OBJ_PAL_PKMN_135},
    {gEventObjectPalette_pkmn_136, EVENT_OBJ_PAL_PKMN_136},
    {gEventObjectPalette_pkmn_137, EVENT_OBJ_PAL_PKMN_137},
    {gEventObjectPalette_pkmn_138, EVENT_OBJ_PAL_PKMN_138},
    {gEventObjectPalette_pkmn_139, EVENT_OBJ_PAL_PKMN_139},
    {gEventObjectPalette_pkmn_140, EVENT_OBJ_PAL_PKMN_140},
    {gEventObjectPalette_pkmn_141, EVENT_OBJ_PAL_PKMN_141},
    {gEventObjectPalette_pkmn_142, EVENT_OBJ_PAL_PKMN_142},
    {gEventObjectPalette_pkmn_143, EVENT_OBJ_PAL_PKMN_143},
    {gEventObjectPalette_pkmn_144, EVENT_OBJ_PAL_PKMN_144},
    {gEventObjectPalette_pkmn_145, EVENT_OBJ_PAL_PKMN_145},
    {gEventObjectPalette_pkmn_146, EVENT_OBJ_PAL_PKMN_146},
    {gEventObjectPalette_pkmn_147, EVENT_OBJ_PAL_PKMN_147},
    {gEventObjectPalette_pkmn_148, EVENT_OBJ_PAL_PKMN_148},
    {gEventObjectPalette_pkmn_149, EVENT_OBJ_PAL_PKMN_149},
    {gEventObjectPalette_pkmn_150, EVENT_OBJ_PAL_PKMN_150},
    {gEventObjectPalette_pkmn_151, EVENT_OBJ_PAL_PKMN_151},
    {gEventObjectPalette_pkmn_152, EVENT_OBJ_PAL_PKMN_152},
    {gEventObjectPalette_pkmn_153, EVENT_OBJ_PAL_PKMN_153},
    {gEventObjectPalette_pkmn_154, EVENT_OBJ_PAL_PKMN_154},
    {gEventObjectPalette_pkmn_155, EVENT_OBJ_PAL_PKMN_155},
    {gEventObjectPalette_pkmn_156, EVENT_OBJ_PAL_PKMN_156},
    {gEventObjectPalette_pkmn_157, EVENT_OBJ_PAL_PKMN_157},
    {gEventObjectPalette_pkmn_158, EVENT_OBJ_PAL_PKMN_158},
    {gEventObjectPalette_pkmn_159, EVENT_OBJ_PAL_PKMN_159},
    {gEventObjectPalette_pkmn_160, EVENT_OBJ_PAL_PKMN_160},
    {gEventObjectPalette_pkmn_161, EVENT_OBJ_PAL_PKMN_161},
    {gEventObjectPalette_pkmn_162, EVENT_OBJ_PAL_PKMN_162},
    {gEventObjectPalette_pkmn_163, EVENT_OBJ_PAL_PKMN_163},
    {gEventObjectPalette_pkmn_164, EVENT_OBJ_PAL_PKMN_164},
    {gEventObjectPalette_pkmn_165, EVENT_OBJ_PAL_PKMN_165},
    {gEventObjectPalette_pkmn_166, EVENT_OBJ_PAL_PKMN_166},
    {gEventObjectPalette_pkmn_167, EVENT_OBJ_PAL_PKMN_167},
    {gEventObjectPalette_pkmn_168, EVENT_OBJ_PAL_PKMN_168},
    {gEventObjectPalette_pkmn_169, EVENT_OBJ_PAL_PKMN_169},
    {gEventObjectPalette_pkmn_170, EVENT_OBJ_PAL_PKMN_170},
    {gEventObjectPalette_pkmn_171, EVENT_OBJ_PAL_PKMN_171},
    {gEventObjectPalette_pkmn_172, EVENT_OBJ_PAL_PKMN_172},
    {gEventObjectPalette_pkmn_173, EVENT_OBJ_PAL_PKMN_173},
    {gEventObjectPalette_pkmn_174, EVENT_OBJ_PAL_PKMN_174},
    {gEventObjectPalette_pkmn_175, EVENT_OBJ_PAL_PKMN_175},
    {gEventObjectPalette_pkmn_176, EVENT_OBJ_PAL_PKMN_176},
    {gEventObjectPalette_pkmn_177, EVENT_OBJ_PAL_PKMN_177},
    {gEventObjectPalette_pkmn_178, EVENT_OBJ_PAL_PKMN_178},
    {gEventObjectPalette_pkmn_179, EVENT_OBJ_PAL_PKMN_179},
    {gEventObjectPalette_pkmn_180, EVENT_OBJ_PAL_PKMN_180},
    {gEventObjectPalette_pkmn_181, EVENT_OBJ_PAL_PKMN_181},
    {gEventObjectPalette_pkmn_182, EVENT_OBJ_PAL_PKMN_182},
    {gEventObjectPalette_pkmn_183, EVENT_OBJ_PAL_PKMN_183},
    {gEventObjectPalette_pkmn_184, EVENT_OBJ_PAL_PKMN_184},
    {gEventObjectPalette_pkmn_185, EVENT_OBJ_PAL_PKMN_185},
    {gEventObjectPalette_pkmn_186, EVENT_OBJ_PAL_PKMN_186},
    {gEventObjectPalette_pkmn_187, EVENT_OBJ_PAL_PKMN_187},
    {gEventObjectPalette_pkmn_188, EVENT_OBJ_PAL_PKMN_188},
    {gEventObjectPalette_pkmn_189, EVENT_OBJ_PAL_PKMN_189},
    {gEventObjectPalette_pkmn_190, EVENT_OBJ_PAL_PKMN_190},
    {gEventObjectPalette_pkmn_191, EVENT_OBJ_PAL_PKMN_191},
    {gEventObjectPalette_pkmn_192, EVENT_OBJ_PAL_PKMN_192},
    {gEventObjectPalette_pkmn_193, EVENT_OBJ_PAL_PKMN_193},
    {gEventObjectPalette_pkmn_194, EVENT_OBJ_PAL_PKMN_194},
    {gEventObjectPalette_pkmn_195, EVENT_OBJ_PAL_PKMN_195},
    {gEventObjectPalette_pkmn_196, EVENT_OBJ_PAL_PKMN_196},
    {gEventObjectPalette_pkmn_197, EVENT_OBJ_PAL_PKMN_197},
    {gEventObjectPalette_pkmn_198, EVENT_OBJ_PAL_PKMN_198},
    {gEventObjectPalette_pkmn_199, EVENT_OBJ_PAL_PKMN_199},
    {gEventObjectPalette_pkmn_200, EVENT_OBJ_PAL_PKMN_200},
    {gEventObjectPalette_pkmn_201, EVENT_OBJ_PAL_PKMN_201},
    {gEventObjectPalette_pkmn_202, EVENT_OBJ_PAL_PKMN_202},
    {gEventObjectPalette_pkmn_203, EVENT_OBJ_PAL_PKMN_203},
    {gEventObjectPalette_pkmn_204, EVENT_OBJ_PAL_PKMN_204},
    {gEventObjectPalette_pkmn_205, EVENT_OBJ_PAL_PKMN_205},
    {gEventObjectPalette_pkmn_206, EVENT_OBJ_PAL_PKMN_206},
    {gEventObjectPalette_pkmn_207, EVENT_OBJ_PAL_PKMN_207},
    {gEventObjectPalette_pkmn_208, EVENT_OBJ_PAL_PKMN_208},
    {gEventObjectPalette_pkmn_209, EVENT_OBJ_PAL_PKMN_209},
    {gEventObjectPalette_pkmn_210, EVENT_OBJ_PAL_PKMN_210},
    {gEventObjectPalette_pkmn_211, EVENT_OBJ_PAL_PKMN_211},
    {gEventObjectPalette_pkmn_212, EVENT_OBJ_PAL_PKMN_212},
    {gEventObjectPalette_pkmn_213, EVENT_OBJ_PAL_PKMN_213},
    {gEventObjectPalette_pkmn_214, EVENT_OBJ_PAL_PKMN_214},
    {gEventObjectPalette_pkmn_215, EVENT_OBJ_PAL_PKMN_215},
    {gEventObjectPalette_pkmn_216, EVENT_OBJ_PAL_PKMN_216},
    {gEventObjectPalette_pkmn_217, EVENT_OBJ_PAL_PKMN_217},
    {gEventObjectPalette_pkmn_218, EVENT_OBJ_PAL_PKMN_218},
    {gEventObjectPalette_pkmn_219, EVENT_OBJ_PAL_PKMN_219},
    {gEventObjectPalette_pkmn_220, EVENT_OBJ_PAL_PKMN_220},
    {gEventObjectPalette_pkmn_221, EVENT_OBJ_PAL_PKMN_221},
    {gEventObjectPalette_pkmn_222, EVENT_OBJ_PAL_PKMN_222},
    {gEventObjectPalette_pkmn_223, EVENT_OBJ_PAL_PKMN_223},
    {gEventObjectPalette_pkmn_224, EVENT_OBJ_PAL_PKMN_224},
    {gEventObjectPalette_pkmn_225, EVENT_OBJ_PAL_PKMN_225},
    {gEventObjectPalette_pkmn_226, EVENT_OBJ_PAL_PKMN_226},
    {gEventObjectPalette_pkmn_227, EVENT_OBJ_PAL_PKMN_227},
    {gEventObjectPalette_pkmn_228, EVENT_OBJ_PAL_PKMN_228},
    {gEventObjectPalette_pkmn_229, EVENT_OBJ_PAL_PKMN_229},
    {gEventObjectPalette_pkmn_230, EVENT_OBJ_PAL_PKMN_230},
    {gEventObjectPalette_pkmn_231, EVENT_OBJ_PAL_PKMN_231},
    {gEventObjectPalette_pkmn_232, EVENT_OBJ_PAL_PKMN_232},
    {gEventObjectPalette_pkmn_233, EVENT_OBJ_PAL_PKMN_233},
    {gEventObjectPalette_pkmn_234, EVENT_OBJ_PAL_PKMN_234},
    {gEventObjectPalette_pkmn_235, EVENT_OBJ_PAL_PKMN_235},
    {gEventObjectPalette_pkmn_236, EVENT_OBJ_PAL_PKMN_236},
    {gEventObjectPalette_pkmn_237, EVENT_OBJ_PAL_PKMN_237},
    {gEventObjectPalette_pkmn_238, EVENT_OBJ_PAL_PKMN_238},
    {gEventObjectPalette_pkmn_239, EVENT_OBJ_PAL_PKMN_239},
    {gEventObjectPalette_pkmn_240, EVENT_OBJ_PAL_PKMN_240},
    {gEventObjectPalette_pkmn_241, EVENT_OBJ_PAL_PKMN_241},
    {gEventObjectPalette_pkmn_242, EVENT_OBJ_PAL_PKMN_242},
    {gEventObjectPalette_pkmn_243, EVENT_OBJ_PAL_PKMN_243},
    {gEventObjectPalette_pkmn_244, EVENT_OBJ_PAL_PKMN_244},
    {gEventObjectPalette_pkmn_245, EVENT_OBJ_PAL_PKMN_245},
    {gEventObjectPalette_pkmn_246, EVENT_OBJ_PAL_PKMN_246},
    {gEventObjectPalette_pkmn_247, EVENT_OBJ_PAL_PKMN_247},
    {gEventObjectPalette_pkmn_248, EVENT_OBJ_PAL_PKMN_248},
    {gEventObjectPalette_pkmn_249, EVENT_OBJ_PAL_PKMN_249},
    {gEventObjectPalette_pkmn_250, EVENT_OBJ_PAL_PKMN_250},
    {gEventObjectPalette_pkmn_251, EVENT_OBJ_PAL_PKMN_251},
    {gEventObjectPalette_pkmn_252, EVENT_OBJ_PAL_PKMN_252},
    {gEventObjectPalette_pkmn_253, EVENT_OBJ_PAL_PKMN_253},
    {gEventObjectPalette_pkmn_254, EVENT_OBJ_PAL_PKMN_254},
    {gEventObjectPalette_pkmn_255, EVENT_OBJ_PAL_PKMN_255},
    {gEventObjectPalette_pkmn_256, EVENT_OBJ_PAL_PKMN_256},
    {gEventObjectPalette_pkmn_257, EVENT_OBJ_PAL_PKMN_257},
    {gEventObjectPalette_pkmn_258, EVENT_OBJ_PAL_PKMN_258},
    {gEventObjectPalette_pkmn_259, EVENT_OBJ_PAL_PKMN_259},
    {gEventObjectPalette_pkmn_260, EVENT_OBJ_PAL_PKMN_260},
    {gEventObjectPalette_pkmn_261, EVENT_OBJ_PAL_PKMN_261},
    {gEventObjectPalette_pkmn_262, EVENT_OBJ_PAL_PKMN_262},
    {gEventObjectPalette_pkmn_263, EVENT_OBJ_PAL_PKMN_263},
    {gEventObjectPalette_pkmn_264, EVENT_OBJ_PAL_PKMN_264},
    {gEventObjectPalette_pkmn_265, EVENT_OBJ_PAL_PKMN_265},
    {gEventObjectPalette_pkmn_266, EVENT_OBJ_PAL_PKMN_266},
    {gEventObjectPalette_pkmn_267, EVENT_OBJ_PAL_PKMN_267},
    {gEventObjectPalette_pkmn_268, EVENT_OBJ_PAL_PKMN_268},
    {gEventObjectPalette_pkmn_269, EVENT_OBJ_PAL_PKMN_269},
    {gEventObjectPalette_pkmn_270, EVENT_OBJ_PAL_PKMN_270},
    {gEventObjectPalette_pkmn_271, EVENT_OBJ_PAL_PKMN_271},
    {gEventObjectPalette_pkmn_272, EVENT_OBJ_PAL_PKMN_272},
    {gEventObjectPalette_pkmn_273, EVENT_OBJ_PAL_PKMN_273},
    {gEventObjectPalette_pkmn_274, EVENT_OBJ_PAL_PKMN_274},
    {gEventObjectPalette_pkmn_275, EVENT_OBJ_PAL_PKMN_275},
    {gEventObjectPalette_pkmn_276, EVENT_OBJ_PAL_PKMN_276},
    {gEventObjectPalette_pkmn_277, EVENT_OBJ_PAL_PKMN_277},
    {gEventObjectPalette_pkmn_278, EVENT_OBJ_PAL_PKMN_278},
    {gEventObjectPalette_pkmn_279, EVENT_OBJ_PAL_PKMN_279},
    {gEventObjectPalette_pkmn_280, EVENT_OBJ_PAL_PKMN_280},
    {gEventObjectPalette_pkmn_281, EVENT_OBJ_PAL_PKMN_281},
    {gEventObjectPalette_pkmn_282, EVENT_OBJ_PAL_PKMN_282},
    {gEventObjectPalette_pkmn_283, EVENT_OBJ_PAL_PKMN_283},
    {gEventObjectPalette_pkmn_284, EVENT_OBJ_PAL_PKMN_284},
    {gEventObjectPalette_pkmn_285, EVENT_OBJ_PAL_PKMN_285},
    {gEventObjectPalette_pkmn_286, EVENT_OBJ_PAL_PKMN_286},
    {gEventObjectPalette_pkmn_287, EVENT_OBJ_PAL_PKMN_287},
    {gEventObjectPalette_pkmn_288, EVENT_OBJ_PAL_PKMN_288},
    {gEventObjectPalette_pkmn_289, EVENT_OBJ_PAL_PKMN_289},
    {gEventObjectPalette_pkmn_290, EVENT_OBJ_PAL_PKMN_290},
    {gEventObjectPalette_pkmn_291, EVENT_OBJ_PAL_PKMN_291},
    {gEventObjectPalette_pkmn_292, EVENT_OBJ_PAL_PKMN_292},
    {gEventObjectPalette_pkmn_293, EVENT_OBJ_PAL_PKMN_293},
    {gEventObjectPalette_pkmn_294, EVENT_OBJ_PAL_PKMN_294},
    {gEventObjectPalette_pkmn_295, EVENT_OBJ_PAL_PKMN_295},
    {gEventObjectPalette_pkmn_296, EVENT_OBJ_PAL_PKMN_296},
    {gEventObjectPalette_pkmn_297, EVENT_OBJ_PAL_PKMN_297},
    {gEventObjectPalette_pkmn_298, EVENT_OBJ_PAL_PKMN_298},
    {gEventObjectPalette_pkmn_299, EVENT_OBJ_PAL_PKMN_299},
    {gEventObjectPalette_pkmn_300, EVENT_OBJ_PAL_PKMN_300},
    {gEventObjectPalette_pkmn_301, EVENT_OBJ_PAL_PKMN_301},
    {gEventObjectPalette_pkmn_302, EVENT_OBJ_PAL_PKMN_302},
    {gEventObjectPalette_pkmn_303, EVENT_OBJ_PAL_PKMN_303},
    {gEventObjectPalette_pkmn_304, EVENT_OBJ_PAL_PKMN_304},
    {gEventObjectPalette_pkmn_305, EVENT_OBJ_PAL_PKMN_305},
    {gEventObjectPalette_pkmn_306, EVENT_OBJ_PAL_PKMN_306},
    {gEventObjectPalette_pkmn_307, EVENT_OBJ_PAL_PKMN_307},
    {gEventObjectPalette_pkmn_308, EVENT_OBJ_PAL_PKMN_308},
    {gEventObjectPalette_pkmn_309, EVENT_OBJ_PAL_PKMN_309},
    {gEventObjectPalette_pkmn_310, EVENT_OBJ_PAL_PKMN_310},
    {gEventObjectPalette_pkmn_311, EVENT_OBJ_PAL_PKMN_311},
    {gEventObjectPalette_pkmn_312, EVENT_OBJ_PAL_PKMN_312},
    {gEventObjectPalette_pkmn_313, EVENT_OBJ_PAL_PKMN_313},
    {gEventObjectPalette_pkmn_314, EVENT_OBJ_PAL_PKMN_314},
    {gEventObjectPalette_pkmn_315, EVENT_OBJ_PAL_PKMN_315},
    {gEventObjectPalette_pkmn_316, EVENT_OBJ_PAL_PKMN_316},
    {gEventObjectPalette_pkmn_317, EVENT_OBJ_PAL_PKMN_317},
    {gEventObjectPalette_pkmn_318, EVENT_OBJ_PAL_PKMN_318},
    {gEventObjectPalette_pkmn_319, EVENT_OBJ_PAL_PKMN_319},
    {gEventObjectPalette_pkmn_320, EVENT_OBJ_PAL_PKMN_320},
    {gEventObjectPalette_pkmn_321, EVENT_OBJ_PAL_PKMN_321},
    {gEventObjectPalette_pkmn_322, EVENT_OBJ_PAL_PKMN_322},
    {gEventObjectPalette_pkmn_323, EVENT_OBJ_PAL_PKMN_323},
    {gEventObjectPalette_pkmn_324, EVENT_OBJ_PAL_PKMN_324},
    {gEventObjectPalette_pkmn_325, EVENT_OBJ_PAL_PKMN_325},
    {gEventObjectPalette_pkmn_326, EVENT_OBJ_PAL_PKMN_326},
    {gEventObjectPalette_pkmn_327, EVENT_OBJ_PAL_PKMN_327},
    {gEventObjectPalette_pkmn_328, EVENT_OBJ_PAL_PKMN_328},
    {gEventObjectPalette_pkmn_329, EVENT_OBJ_PAL_PKMN_329},
    {gEventObjectPalette_pkmn_330, EVENT_OBJ_PAL_PKMN_330},
    {gEventObjectPalette_pkmn_331, EVENT_OBJ_PAL_PKMN_331},
    {gEventObjectPalette_pkmn_332, EVENT_OBJ_PAL_PKMN_332},
    {gEventObjectPalette_pkmn_333, EVENT_OBJ_PAL_PKMN_333},
    {gEventObjectPalette_pkmn_334, EVENT_OBJ_PAL_PKMN_334},
    {gEventObjectPalette_pkmn_335, EVENT_OBJ_PAL_PKMN_335},
    {gEventObjectPalette_pkmn_336, EVENT_OBJ_PAL_PKMN_336},
    {gEventObjectPalette_pkmn_337, EVENT_OBJ_PAL_PKMN_337},
    {gEventObjectPalette_pkmn_338, EVENT_OBJ_PAL_PKMN_338},
    {gEventObjectPalette_pkmn_339, EVENT_OBJ_PAL_PKMN_339},
    {gEventObjectPalette_pkmn_340, EVENT_OBJ_PAL_PKMN_340},
    {gEventObjectPalette_pkmn_341, EVENT_OBJ_PAL_PKMN_341},
    {gEventObjectPalette_pkmn_342, EVENT_OBJ_PAL_PKMN_342},
    {gEventObjectPalette_pkmn_343, EVENT_OBJ_PAL_PKMN_343},
    {gEventObjectPalette_pkmn_344, EVENT_OBJ_PAL_PKMN_344},
    {gEventObjectPalette_pkmn_345, EVENT_OBJ_PAL_PKMN_345},
    {gEventObjectPalette_pkmn_346, EVENT_OBJ_PAL_PKMN_346},
    {gEventObjectPalette_pkmn_347, EVENT_OBJ_PAL_PKMN_347},
    {gEventObjectPalette_pkmn_348, EVENT_OBJ_PAL_PKMN_348},
    {gEventObjectPalette_pkmn_349, EVENT_OBJ_PAL_PKMN_349},
    {gEventObjectPalette_pkmn_350, EVENT_OBJ_PAL_PKMN_350},
    {gEventObjectPalette_pkmn_351, EVENT_OBJ_PAL_PKMN_351},
    {gEventObjectPalette_pkmn_352, EVENT_OBJ_PAL_PKMN_352},
    {gEventObjectPalette_pkmn_353, EVENT_OBJ_PAL_PKMN_353},
    {gEventObjectPalette_pkmn_354, EVENT_OBJ_PAL_PKMN_354},
    {gEventObjectPalette_pkmn_355, EVENT_OBJ_PAL_PKMN_355},
    {gEventObjectPalette_pkmn_356, EVENT_OBJ_PAL_PKMN_356},
    {gEventObjectPalette_pkmn_357, EVENT_OBJ_PAL_PKMN_357},
    {gEventObjectPalette_pkmn_358, EVENT_OBJ_PAL_PKMN_358},
    {gEventObjectPalette_pkmn_359, EVENT_OBJ_PAL_PKMN_359},
    {gEventObjectPalette_pkmn_360, EVENT_OBJ_PAL_PKMN_360},
    {gEventObjectPalette_pkmn_361, EVENT_OBJ_PAL_PKMN_361},
    {gEventObjectPalette_pkmn_362, EVENT_OBJ_PAL_PKMN_362},
    {gEventObjectPalette_pkmn_363, EVENT_OBJ_PAL_PKMN_363},
    {gEventObjectPalette_pkmn_364, EVENT_OBJ_PAL_PKMN_364},
    {gEventObjectPalette_pkmn_365, EVENT_OBJ_PAL_PKMN_365},
    {gEventObjectPalette_pkmn_366, EVENT_OBJ_PAL_PKMN_366},
    {gEventObjectPalette_pkmn_367, EVENT_OBJ_PAL_PKMN_367},
    {gEventObjectPalette_pkmn_368, EVENT_OBJ_PAL_PKMN_368},
    {gEventObjectPalette_pkmn_369, EVENT_OBJ_PAL_PKMN_369},
    {gEventObjectPalette_pkmn_370, EVENT_OBJ_PAL_PKMN_370},
    {gEventObjectPalette_pkmn_371, EVENT_OBJ_PAL_PKMN_371},
    {gEventObjectPalette_pkmn_372, EVENT_OBJ_PAL_PKMN_372},
    {gEventObjectPalette_pkmn_373, EVENT_OBJ_PAL_PKMN_373},
    {gEventObjectPalette_pkmn_374, EVENT_OBJ_PAL_PKMN_374},
    {gEventObjectPalette_pkmn_375, EVENT_OBJ_PAL_PKMN_375},
    {gEventObjectPalette_pkmn_376, EVENT_OBJ_PAL_PKMN_376},
    {gEventObjectPalette_pkmn_377, EVENT_OBJ_PAL_PKMN_377},
    {gEventObjectPalette_pkmn_378, EVENT_OBJ_PAL_PKMN_378},
    {gEventObjectPalette_pkmn_379, EVENT_OBJ_PAL_PKMN_379},
    {gEventObjectPalette_pkmn_380, EVENT_OBJ_PAL_PKMN_380},
    {gEventObjectPalette_pkmn_381, EVENT_OBJ_PAL_PKMN_381},
    {gEventObjectPalette_pkmn_382, EVENT_OBJ_PAL_PKMN_382},
    {gEventObjectPalette_pkmn_383, EVENT_OBJ_PAL_PKMN_383},
    {gEventObjectPalette_pkmn_384, EVENT_OBJ_PAL_PKMN_384},
    {gEventObjectPalette_pkmn_385, EVENT_OBJ_PAL_PKMN_385},
    {gEventObjectPalette_pkmn_386, EVENT_OBJ_PAL_PKMN_386},
    {gEventObjectPalette_pkmn_387, EVENT_OBJ_PAL_PKMN_387},
    {gEventObjectPalette_pkmn_388, EVENT_OBJ_PAL_PKMN_388},
    {gEventObjectPalette_pkmn_389, EVENT_OBJ_PAL_PKMN_389},
    {gEventObjectPalette_pkmn_390, EVENT_OBJ_PAL_PKMN_390},
    {gEventObjectPalette_pkmn_391, EVENT_OBJ_PAL_PKMN_391},
    {gEventObjectPalette_pkmn_392, EVENT_OBJ_PAL_PKMN_392},
    {gEventObjectPalette_pkmn_393, EVENT_OBJ_PAL_PKMN_393},
    {gEventObjectPalette_pkmn_394, EVENT_OBJ_PAL_PKMN_394},
    {gEventObjectPalette_pkmn_395, EVENT_OBJ_PAL_PKMN_395},
    {gEventObjectPalette_pkmn_396, EVENT_OBJ_PAL_PKMN_396},
    {gEventObjectPalette_pkmn_397, EVENT_OBJ_PAL_PKMN_397},
    {gEventObjectPalette_pkmn_398, EVENT_OBJ_PAL_PKMN_398},
    {gEventObjectPalette_pkmn_399, EVENT_OBJ_PAL_PKMN_399},
    {gEventObjectPalette_pkmn_400, EVENT_OBJ_PAL_PKMN_400},
    {gEventObjectPalette_pkmn_401, EVENT_OBJ_PAL_PKMN_401},
    {gEventObjectPalette_pkmn_402, EVENT_OBJ_PAL_PKMN_402},
    {gEventObjectPalette_pkmn_403, EVENT_OBJ_PAL_PKMN_403},
    {gEventObjectPalette_pkmn_404, EVENT_OBJ_PAL_PKMN_404},
    {gEventObjectPalette_pkmn_405, EVENT_OBJ_PAL_PKMN_405},
    {gEventObjectPalette_pkmn_406, EVENT_OBJ_PAL_PKMN_406},
    {gEventObjectPalette_pkmn_407, EVENT_OBJ_PAL_PKMN_407},
    {gEventObjectPalette_pkmn_408, EVENT_OBJ_PAL_PKMN_408},
    {gEventObjectPalette_pkmn_409, EVENT_OBJ_PAL_PKMN_409},
    {gEventObjectPalette_pkmn_410, EVENT_OBJ_PAL_PKMN_410},
    {gEventObjectPalette_pkmn_411, EVENT_OBJ_PAL_PKMN_411},
    {gEventObjectPalette_pkmn_412, EVENT_OBJ_PAL_PKMN_412},
    {gEventObjectPalette_pkmn_413, EVENT_OBJ_PAL_PKMN_413},
    {gEventObjectPalette_pkmn_414, EVENT_OBJ_PAL_PKMN_414},
    {gEventObjectPalette_pkmn_415, EVENT_OBJ_PAL_PKMN_415},
    {gEventObjectPalette_pkmn_416, EVENT_OBJ_PAL_PKMN_416},
    {gEventObjectPalette_pkmn_417, EVENT_OBJ_PAL_PKMN_417},
    {gEventObjectPalette_pkmn_418, EVENT_OBJ_PAL_PKMN_418},
    {gEventObjectPalette_pkmn_419, EVENT_OBJ_PAL_PKMN_419},
    {gEventObjectPalette_pkmn_420, EVENT_OBJ_PAL_PKMN_420},
    {gEventObjectPalette_pkmn_421, EVENT_OBJ_PAL_PKMN_421},
    {gEventObjectPalette_pkmn_422, EVENT_OBJ_PAL_PKMN_422},
    {gEventObjectPalette_pkmn_423, EVENT_OBJ_PAL_PKMN_423},
    {gEventObjectPalette_pkmn_424, EVENT_OBJ_PAL_PKMN_424},
    {gEventObjectPalette_pkmn_425, EVENT_OBJ_PAL_PKMN_425},
    {gEventObjectPalette_pkmn_426, EVENT_OBJ_PAL_PKMN_426},
    {gEventObjectPalette_pkmn_427, EVENT_OBJ_PAL_PKMN_427},
    {gEventObjectPalette_pkmn_428, EVENT_OBJ_PAL_PKMN_428},
    {gEventObjectPalette_pkmn_429, EVENT_OBJ_PAL_PKMN_429},
    {gEventObjectPalette_pkmn_430, EVENT_OBJ_PAL_PKMN_430},
    {gEventObjectPalette_pkmn_431, EVENT_OBJ_PAL_PKMN_431},
    {gEventObjectPalette_pkmn_432, EVENT_OBJ_PAL_PKMN_432},
    {gEventObjectPalette_pkmn_433, EVENT_OBJ_PAL_PKMN_433},
    {gEventObjectPalette_pkmn_434, EVENT_OBJ_PAL_PKMN_434},
    {gEventObjectPalette_pkmn_435, EVENT_OBJ_PAL_PKMN_435},
    {gEventObjectPalette_pkmn_436, EVENT_OBJ_PAL_PKMN_436},
    {gEventObjectPalette_pkmn_437, EVENT_OBJ_PAL_PKMN_437},
    {gEventObjectPalette_pkmn_438, EVENT_OBJ_PAL_PKMN_438},
    {gEventObjectPalette_pkmn_439, EVENT_OBJ_PAL_PKMN_439},
    {gEventObjectPalette_pkmn_440, EVENT_OBJ_PAL_PKMN_440},
    {gEventObjectPalette_pkmn_441, EVENT_OBJ_PAL_PKMN_441},
    {gEventObjectPalette_pkmn_442, EVENT_OBJ_PAL_PKMN_442},
    {gEventObjectPalette_pkmn_443, EVENT_OBJ_PAL_PKMN_443},
    {gEventObjectPalette_pkmn_444, EVENT_OBJ_PAL_PKMN_444},
    {gEventObjectPalette_pkmn_445, EVENT_OBJ_PAL_PKMN_445},
    {gEventObjectPalette_pkmn_446, EVENT_OBJ_PAL_PKMN_446},
    {gEventObjectPalette_pkmn_447, EVENT_OBJ_PAL_PKMN_447},
    {gEventObjectPalette_pkmn_448, EVENT_OBJ_PAL_PKMN_448},
    {gEventObjectPalette_pkmn_449, EVENT_OBJ_PAL_PKMN_449},
    {gEventObjectPalette_pkmn_450, EVENT_OBJ_PAL_PKMN_450},
    {gEventObjectPalette_pkmn_451, EVENT_OBJ_PAL_PKMN_451},
    {gEventObjectPalette_pkmn_452, EVENT_OBJ_PAL_PKMN_452},
    {gEventObjectPalette_pkmn_453, EVENT_OBJ_PAL_PKMN_453},
    {gEventObjectPalette_pkmn_454, EVENT_OBJ_PAL_PKMN_454},
    {gEventObjectPalette_pkmn_455, EVENT_OBJ_PAL_PKMN_455},
    {gEventObjectPalette_pkmn_456, EVENT_OBJ_PAL_PKMN_456},
    {gEventObjectPalette_pkmn_457, EVENT_OBJ_PAL_PKMN_457},
    {gEventObjectPalette_pkmn_458, EVENT_OBJ_PAL_PKMN_458},
    {gEventObjectPalette_pkmn_459, EVENT_OBJ_PAL_PKMN_459},
    {gEventObjectPalette_pkmn_460, EVENT_OBJ_PAL_PKMN_460},
    {gEventObjectPalette_pkmn_461, EVENT_OBJ_PAL_PKMN_461},
    {gEventObjectPalette_pkmn_462, EVENT_OBJ_PAL_PKMN_462},
    {gEventObjectPalette_pkmn_463, EVENT_OBJ_PAL_PKMN_463},
    {gEventObjectPalette_pkmn_464, EVENT_OBJ_PAL_PKMN_464},
    {gEventObjectPalette_pkmn_465, EVENT_OBJ_PAL_PKMN_465},
    {gEventObjectPalette_pkmn_466, EVENT_OBJ_PAL_PKMN_466},
    {gEventObjectPalette_pkmn_467, EVENT_OBJ_PAL_PKMN_467},
    {gEventObjectPalette_pkmn_468, EVENT_OBJ_PAL_PKMN_468},
    {gEventObjectPalette_pkmn_469, EVENT_OBJ_PAL_PKMN_469},
    {gEventObjectPalette_pkmn_470, EVENT_OBJ_PAL_PKMN_470},
    {gEventObjectPalette_pkmn_471, EVENT_OBJ_PAL_PKMN_471},
    {gEventObjectPalette_pkmn_472, EVENT_OBJ_PAL_PKMN_472},
    {gEventObjectPalette_pkmn_473, EVENT_OBJ_PAL_PKMN_473},
    {gEventObjectPalette_pkmn_474, EVENT_OBJ_PAL_PKMN_474},
    {gEventObjectPalette_pkmn_475, EVENT_OBJ_PAL_PKMN_475},
    {gEventObjectPalette_pkmn_476, EVENT_OBJ_PAL_PKMN_476},
    {gEventObjectPalette_pkmn_477, EVENT_OBJ_PAL_PKMN_477},
    {gEventObjectPalette_pkmn_478, EVENT_OBJ_PAL_PKMN_478},
    {gEventObjectPalette_pkmn_479, EVENT_OBJ_PAL_PKMN_479},
    {gEventObjectPalette_pkmn_480, EVENT_OBJ_PAL_PKMN_480},
    {gEventObjectPalette_pkmn_481, EVENT_OBJ_PAL_PKMN_481},
    {gEventObjectPalette_pkmn_482, EVENT_OBJ_PAL_PKMN_482},
    {gEventObjectPalette_pkmn_483, EVENT_OBJ_PAL_PKMN_483},
    {gEventObjectPalette_pkmn_484, EVENT_OBJ_PAL_PKMN_484},
    {gEventObjectPalette_pkmn_485, EVENT_OBJ_PAL_PKMN_485},
    {gEventObjectPalette_pkmn_486, EVENT_OBJ_PAL_PKMN_486},
    {gEventObjectPalette_pkmn_487, EVENT_OBJ_PAL_PKMN_487},
    {gEventObjectPalette_pkmn_488, EVENT_OBJ_PAL_PKMN_488},
    {gEventObjectPalette_pkmn_489, EVENT_OBJ_PAL_PKMN_489},
    {gEventObjectPalette_pkmn_490, EVENT_OBJ_PAL_PKMN_490},
    {gEventObjectPalette_pkmn_491, EVENT_OBJ_PAL_PKMN_491},
    {gEventObjectPalette_pkmn_492, EVENT_OBJ_PAL_PKMN_492},
    {gEventObjectPalette_pkmn_493, EVENT_OBJ_PAL_PKMN_493},
    {gEventObjectPalette_pkmn_494, EVENT_OBJ_PAL_PKMN_494},
    {gEventObjectPalette_pkmn_495, EVENT_OBJ_PAL_PKMN_495},
    {gEventObjectPalette_pkmn_496, EVENT_OBJ_PAL_PKMN_496},
    {gEventObjectPalette_pkmn_497, EVENT_OBJ_PAL_PKMN_497},
    {gEventObjectPalette_pkmn_498, EVENT_OBJ_PAL_PKMN_498},
    {gEventObjectPalette_pkmn_499, EVENT_OBJ_PAL_PKMN_499},
    {gEventObjectPalette_pkmn_500, EVENT_OBJ_PAL_PKMN_500},
    {gEventObjectPalette_pkmn_501, EVENT_OBJ_PAL_PKMN_501},
    {gEventObjectPalette_pkmn_502, EVENT_OBJ_PAL_PKMN_502},
    {gEventObjectPalette_pkmn_503, EVENT_OBJ_PAL_PKMN_503},
    {gEventObjectPalette_pkmn_504, EVENT_OBJ_PAL_PKMN_504},
    {gEventObjectPalette_pkmn_505, EVENT_OBJ_PAL_PKMN_505},
    {gEventObjectPalette_pkmn_506, EVENT_OBJ_PAL_PKMN_506},
    {gEventObjectPalette_pkmn_507, EVENT_OBJ_PAL_PKMN_507},
    {gEventObjectPalette_pkmn_508, EVENT_OBJ_PAL_PKMN_508},
    {gEventObjectPalette_pkmn_509, EVENT_OBJ_PAL_PKMN_509},
    {gEventObjectPalette_pkmn_510, EVENT_OBJ_PAL_PKMN_510},
    {gEventObjectPalette_pkmn_511, EVENT_OBJ_PAL_PKMN_511},
    {gEventObjectPalette_pkmn_512, EVENT_OBJ_PAL_PKMN_512},
    {gEventObjectPalette_pkmn_513, EVENT_OBJ_PAL_PKMN_513},
    {gEventObjectPalette_pkmn_514, EVENT_OBJ_PAL_PKMN_514},
    {gEventObjectPalette_pkmn_515, EVENT_OBJ_PAL_PKMN_515},
    {gEventObjectPalette_pkmn_516, EVENT_OBJ_PAL_PKMN_516},
    {gEventObjectPalette_pkmn_517, EVENT_OBJ_PAL_PKMN_517},
    {gEventObjectPalette_pkmn_518, EVENT_OBJ_PAL_PKMN_518},
    {gEventObjectPalette_pkmn_519, EVENT_OBJ_PAL_PKMN_519},
    {gEventObjectPalette_pkmn_520, EVENT_OBJ_PAL_PKMN_520},
    {gEventObjectPalette_pkmn_521, EVENT_OBJ_PAL_PKMN_521},
    {gEventObjectPalette_pkmn_522, EVENT_OBJ_PAL_PKMN_522},
    {gEventObjectPalette_pkmn_523, EVENT_OBJ_PAL_PKMN_523},
    {gEventObjectPalette_pkmn_524, EVENT_OBJ_PAL_PKMN_524},
    {gEventObjectPalette_pkmn_525, EVENT_OBJ_PAL_PKMN_525},
    {gEventObjectPalette_pkmn_526, EVENT_OBJ_PAL_PKMN_526},
    {gEventObjectPalette_pkmn_527, EVENT_OBJ_PAL_PKMN_527},
    {gEventObjectPalette_pkmn_528, EVENT_OBJ_PAL_PKMN_528},
    {gEventObjectPalette_pkmn_529, EVENT_OBJ_PAL_PKMN_529},
    {gEventObjectPalette_pkmn_530, EVENT_OBJ_PAL_PKMN_530},
    {gEventObjectPalette_pkmn_531, EVENT_OBJ_PAL_PKMN_531},
    {gEventObjectPalette_pkmn_532, EVENT_OBJ_PAL_PKMN_532},
    {gEventObjectPalette_pkmn_533, EVENT_OBJ_PAL_PKMN_533},
    {gEventObjectPalette_pkmn_534, EVENT_OBJ_PAL_PKMN_534},
    {gEventObjectPalette_pkmn_535, EVENT_OBJ_PAL_PKMN_535},
    {gEventObjectPalette_pkmn_536, EVENT_OBJ_PAL_PKMN_536},
    {gEventObjectPalette_pkmn_537, EVENT_OBJ_PAL_PKMN_537},
    {gEventObjectPalette_pkmn_538, EVENT_OBJ_PAL_PKMN_538},
    {gEventObjectPalette_pkmn_539, EVENT_OBJ_PAL_PKMN_539},
    {gEventObjectPalette_pkmn_540, EVENT_OBJ_PAL_PKMN_540},
    {gEventObjectPalette_pkmn_541, EVENT_OBJ_PAL_PKMN_541},
    {gEventObjectPalette_pkmn_542, EVENT_OBJ_PAL_PKMN_542},
    {gEventObjectPalette_pkmn_543, EVENT_OBJ_PAL_PKMN_543},
    {gEventObjectPalette_pkmn_544, EVENT_OBJ_PAL_PKMN_544},
    {gEventObjectPalette_pkmn_545, EVENT_OBJ_PAL_PKMN_545},
    {gEventObjectPalette_pkmn_546, EVENT_OBJ_PAL_PKMN_546},
    {gEventObjectPalette_pkmn_547, EVENT_OBJ_PAL_PKMN_547},
    {gEventObjectPalette_pkmn_548, EVENT_OBJ_PAL_PKMN_548},
    {gEventObjectPalette_pkmn_549, EVENT_OBJ_PAL_PKMN_549},
    {gEventObjectPalette_pkmn_550, EVENT_OBJ_PAL_PKMN_550},
    {gEventObjectPalette_pkmn_551, EVENT_OBJ_PAL_PKMN_551},
    {gEventObjectPalette_pkmn_552, EVENT_OBJ_PAL_PKMN_552},
    {gEventObjectPalette_pkmn_553, EVENT_OBJ_PAL_PKMN_553},
    {gEventObjectPalette_pkmn_554, EVENT_OBJ_PAL_PKMN_554},
    {gEventObjectPalette_pkmn_555, EVENT_OBJ_PAL_PKMN_555},
    {gEventObjectPalette_pkmn_556, EVENT_OBJ_PAL_PKMN_556},
    {gEventObjectPalette_pkmn_557, EVENT_OBJ_PAL_PKMN_557},
    {gEventObjectPalette_pkmn_558, EVENT_OBJ_PAL_PKMN_558},
    {gEventObjectPalette_pkmn_559, EVENT_OBJ_PAL_PKMN_559},
    {gEventObjectPalette_pkmn_560, EVENT_OBJ_PAL_PKMN_560},
    {gEventObjectPalette_pkmn_561, EVENT_OBJ_PAL_PKMN_561},
    {gEventObjectPalette_pkmn_562, EVENT_OBJ_PAL_PKMN_562},
    {gEventObjectPalette_pkmn_563, EVENT_OBJ_PAL_PKMN_563},
    {gEventObjectPalette_pkmn_564, EVENT_OBJ_PAL_PKMN_564},
    {gEventObjectPalette_pkmn_565, EVENT_OBJ_PAL_PKMN_565},
    {gEventObjectPalette_pkmn_566, EVENT_OBJ_PAL_PKMN_566},
    {gEventObjectPalette_pkmn_567, EVENT_OBJ_PAL_PKMN_567},
    {gEventObjectPalette_pkmn_568, EVENT_OBJ_PAL_PKMN_568},
    {gEventObjectPalette_pkmn_569, EVENT_OBJ_PAL_PKMN_569},
    {gEventObjectPalette_pkmn_570, EVENT_OBJ_PAL_PKMN_570},
    {gEventObjectPalette_pkmn_571, EVENT_OBJ_PAL_PKMN_571},
    {gEventObjectPalette_pkmn_572, EVENT_OBJ_PAL_PKMN_572},
    {gEventObjectPalette_pkmn_573, EVENT_OBJ_PAL_PKMN_573},
    {gEventObjectPalette_pkmn_574, EVENT_OBJ_PAL_PKMN_574},
    {gEventObjectPalette_pkmn_575, EVENT_OBJ_PAL_PKMN_575},
    {gEventObjectPalette_pkmn_576, EVENT_OBJ_PAL_PKMN_576},
    {gEventObjectPalette_pkmn_577, EVENT_OBJ_PAL_PKMN_577},
    {gEventObjectPalette_pkmn_578, EVENT_OBJ_PAL_PKMN_578},
    {gEventObjectPalette_pkmn_579, EVENT_OBJ_PAL_PKMN_579},
    {gEventObjectPalette_pkmn_580, EVENT_OBJ_PAL_PKMN_580},
    {gEventObjectPalette_pkmn_581, EVENT_OBJ_PAL_PKMN_581},
    {gEventObjectPalette_pkmn_582, EVENT_OBJ_PAL_PKMN_582},
    {gEventObjectPalette_pkmn_583, EVENT_OBJ_PAL_PKMN_583},
    {gEventObjectPalette_pkmn_584, EVENT_OBJ_PAL_PKMN_584},
    {gEventObjectPalette_pkmn_585, EVENT_OBJ_PAL_PKMN_585},
    {gEventObjectPalette_pkmn_586, EVENT_OBJ_PAL_PKMN_586},
    {gEventObjectPalette_pkmn_587, EVENT_OBJ_PAL_PKMN_587},
    {gEventObjectPalette_pkmn_588, EVENT_OBJ_PAL_PKMN_588},
    {gEventObjectPalette_pkmn_589, EVENT_OBJ_PAL_PKMN_589},
    {gEventObjectPalette_pkmn_590, EVENT_OBJ_PAL_PKMN_590},
    {gEventObjectPalette_pkmn_591, EVENT_OBJ_PAL_PKMN_591},
    {gEventObjectPalette_pkmn_592, EVENT_OBJ_PAL_PKMN_592},
    {gEventObjectPalette_pkmn_593, EVENT_OBJ_PAL_PKMN_593},
    {gEventObjectPalette_pkmn_594, EVENT_OBJ_PAL_PKMN_594},
    {gEventObjectPalette_pkmn_595, EVENT_OBJ_PAL_PKMN_595},
    {gEventObjectPalette_pkmn_596, EVENT_OBJ_PAL_PKMN_596},
    {gEventObjectPalette_pkmn_597, EVENT_OBJ_PAL_PKMN_597},
    {gEventObjectPalette_pkmn_598, EVENT_OBJ_PAL_PKMN_598},
    {gEventObjectPalette_pkmn_599, EVENT_OBJ_PAL_PKMN_599},
    {gEventObjectPalette_pkmn_600, EVENT_OBJ_PAL_PKMN_600},
    {gEventObjectPalette_pkmn_601, EVENT_OBJ_PAL_PKMN_601},
    {gEventObjectPalette_pkmn_602, EVENT_OBJ_PAL_PKMN_602},
    {gEventObjectPalette_pkmn_603, EVENT_OBJ_PAL_PKMN_603},
    {gEventObjectPalette_pkmn_604, EVENT_OBJ_PAL_PKMN_604},
    {gEventObjectPalette_pkmn_605, EVENT_OBJ_PAL_PKMN_605},
    {gEventObjectPalette_pkmn_606, EVENT_OBJ_PAL_PKMN_606},
    {gEventObjectPalette_pkmn_607, EVENT_OBJ_PAL_PKMN_607},
    {gEventObjectPalette_pkmn_608, EVENT_OBJ_PAL_PKMN_608},
    {gEventObjectPalette_pkmn_609, EVENT_OBJ_PAL_PKMN_609},
    {gEventObjectPalette_pkmn_610, EVENT_OBJ_PAL_PKMN_610},
    {gEventObjectPalette_pkmn_611, EVENT_OBJ_PAL_PKMN_611},
    {gEventObjectPalette_pkmn_612, EVENT_OBJ_PAL_PKMN_612},
    {gEventObjectPalette_pkmn_613, EVENT_OBJ_PAL_PKMN_613},
    {gEventObjectPalette_pkmn_614, EVENT_OBJ_PAL_PKMN_614},
    {gEventObjectPalette_pkmn_615, EVENT_OBJ_PAL_PKMN_615},
    {gEventObjectPalette_pkmn_616, EVENT_OBJ_PAL_PKMN_616},
    {gEventObjectPalette_pkmn_617, EVENT_OBJ_PAL_PKMN_617},
    {gEventObjectPalette_pkmn_618, EVENT_OBJ_PAL_PKMN_618},
    {gEventObjectPalette_pkmn_619, EVENT_OBJ_PAL_PKMN_619},
    {gEventObjectPalette_pkmn_620, EVENT_OBJ_PAL_PKMN_620},
    {gEventObjectPalette_pkmn_621, EVENT_OBJ_PAL_PKMN_621},
    {gEventObjectPalette_pkmn_622, EVENT_OBJ_PAL_PKMN_622},
    {gEventObjectPalette_pkmn_623, EVENT_OBJ_PAL_PKMN_623},
    {gEventObjectPalette_pkmn_624, EVENT_OBJ_PAL_PKMN_624},
    {gEventObjectPalette_pkmn_625, EVENT_OBJ_PAL_PKMN_625},
    {gEventObjectPalette_pkmn_626, EVENT_OBJ_PAL_PKMN_626},
    {gEventObjectPalette_pkmn_627, EVENT_OBJ_PAL_PKMN_627},
    {gEventObjectPalette_pkmn_628, EVENT_OBJ_PAL_PKMN_628},
    {gEventObjectPalette_pkmn_629, EVENT_OBJ_PAL_PKMN_629},
    {gEventObjectPalette_pkmn_630, EVENT_OBJ_PAL_PKMN_630},
    {gEventObjectPalette_pkmn_631, EVENT_OBJ_PAL_PKMN_631},
    {gEventObjectPalette_pkmn_632, EVENT_OBJ_PAL_PKMN_632},
    {gEventObjectPalette_pkmn_633, EVENT_OBJ_PAL_PKMN_633},
    {gEventObjectPalette_pkmn_634, EVENT_OBJ_PAL_PKMN_634},
    {gEventObjectPalette_pkmn_635, EVENT_OBJ_PAL_PKMN_635},
    {gEventObjectPalette_pkmn_636, EVENT_OBJ_PAL_PKMN_636},
    {gEventObjectPalette_pkmn_637, EVENT_OBJ_PAL_PKMN_637},
    {gEventObjectPalette_pkmn_638, EVENT_OBJ_PAL_PKMN_638},
    {gEventObjectPalette_pkmn_639, EVENT_OBJ_PAL_PKMN_639},
    {gEventObjectPalette_pkmn_640, EVENT_OBJ_PAL_PKMN_640},
    {gEventObjectPalette_pkmn_641, EVENT_OBJ_PAL_PKMN_641},
    {gEventObjectPalette_pkmn_642, EVENT_OBJ_PAL_PKMN_642},
    {gEventObjectPalette_pkmn_643, EVENT_OBJ_PAL_PKMN_643},
    {gEventObjectPalette_pkmn_644, EVENT_OBJ_PAL_PKMN_644},
    {gEventObjectPalette_pkmn_645, EVENT_OBJ_PAL_PKMN_645},
    {gEventObjectPalette_pkmn_646, EVENT_OBJ_PAL_PKMN_646},
    {gEventObjectPalette_pkmn_647, EVENT_OBJ_PAL_PKMN_647},
    {gEventObjectPalette_pkmn_648, EVENT_OBJ_PAL_PKMN_648},
    {gEventObjectPalette_pkmn_649, EVENT_OBJ_PAL_PKMN_649},
    {gEventObjectPalette_pkmn_650, EVENT_OBJ_PAL_PKMN_650},
    {gEventObjectPalette_pkmn_651, EVENT_OBJ_PAL_PKMN_651},
    {gEventObjectPalette_pkmn_652, EVENT_OBJ_PAL_PKMN_652},
    {gEventObjectPalette_pkmn_653, EVENT_OBJ_PAL_PKMN_653},
    {gEventObjectPalette_pkmn_654, EVENT_OBJ_PAL_PKMN_654},
    {gEventObjectPalette_pkmn_655, EVENT_OBJ_PAL_PKMN_655},
    {gEventObjectPalette_pkmn_656, EVENT_OBJ_PAL_PKMN_656},
    {gEventObjectPalette_pkmn_657, EVENT_OBJ_PAL_PKMN_657},
    {gEventObjectPalette_pkmn_658, EVENT_OBJ_PAL_PKMN_658},
    {gEventObjectPalette_pkmn_659, EVENT_OBJ_PAL_PKMN_659},
    {gEventObjectPalette_pkmn_660, EVENT_OBJ_PAL_PKMN_660},
    {gEventObjectPalette_pkmn_661, EVENT_OBJ_PAL_PKMN_661},
    {gEventObjectPalette_pkmn_662, EVENT_OBJ_PAL_PKMN_662},
    {gEventObjectPalette_pkmn_663, EVENT_OBJ_PAL_PKMN_663},
    {gEventObjectPalette_pkmn_664, EVENT_OBJ_PAL_PKMN_664},
    {gEventObjectPalette_pkmn_665, EVENT_OBJ_PAL_PKMN_665},
    {gEventObjectPalette_pkmn_666, EVENT_OBJ_PAL_PKMN_666},
    {gEventObjectPalette_pkmn_667, EVENT_OBJ_PAL_PKMN_667},
    {gEventObjectPalette_pkmn_668, EVENT_OBJ_PAL_PKMN_668},
    {gEventObjectPalette_pkmn_669, EVENT_OBJ_PAL_PKMN_669},
    {gEventObjectPalette_pkmn_670, EVENT_OBJ_PAL_PKMN_670},
    {gEventObjectPalette_pkmn_671, EVENT_OBJ_PAL_PKMN_671},
    {gEventObjectPalette_pkmn_672, EVENT_OBJ_PAL_PKMN_672},
    {gEventObjectPalette_pkmn_673, EVENT_OBJ_PAL_PKMN_673},
    {gEventObjectPalette_pkmn_674, EVENT_OBJ_PAL_PKMN_674},
    {gEventObjectPalette_pkmn_675, EVENT_OBJ_PAL_PKMN_675},
    {gEventObjectPalette_pkmn_676, EVENT_OBJ_PAL_PKMN_676},
    {gEventObjectPalette_pkmn_677, EVENT_OBJ_PAL_PKMN_677},
    {gEventObjectPalette_pkmn_678, EVENT_OBJ_PAL_PKMN_678},
    {gEventObjectPalette_pkmn_679, EVENT_OBJ_PAL_PKMN_679},
    {gEventObjectPalette_pkmn_680, EVENT_OBJ_PAL_PKMN_680},
    {gEventObjectPalette_pkmn_681, EVENT_OBJ_PAL_PKMN_681},
    {gEventObjectPalette_pkmn_682, EVENT_OBJ_PAL_PKMN_682},
    {gEventObjectPalette_pkmn_683, EVENT_OBJ_PAL_PKMN_683},
    {gEventObjectPalette_pkmn_684, EVENT_OBJ_PAL_PKMN_684},
    {gEventObjectPalette_pkmn_685, EVENT_OBJ_PAL_PKMN_685},
    {gEventObjectPalette_pkmn_686, EVENT_OBJ_PAL_PKMN_686},
    {gEventObjectPalette_pkmn_687, EVENT_OBJ_PAL_PKMN_687},
    {gEventObjectPalette_pkmn_688, EVENT_OBJ_PAL_PKMN_688},
    {gEventObjectPalette_pkmn_689, EVENT_OBJ_PAL_PKMN_689},
    {gEventObjectPalette_pkmn_690, EVENT_OBJ_PAL_PKMN_690},
    {gEventObjectPalette_pkmn_691, EVENT_OBJ_PAL_PKMN_691},
    {gEventObjectPalette_pkmn_692, EVENT_OBJ_PAL_PKMN_692},
    {gEventObjectPalette_pkmn_693, EVENT_OBJ_PAL_PKMN_693},
    {gEventObjectPalette_pkmn_694, EVENT_OBJ_PAL_PKMN_694},
    {gEventObjectPalette_pkmn_695, EVENT_OBJ_PAL_PKMN_695},
    {gEventObjectPalette_pkmn_696, EVENT_OBJ_PAL_PKMN_696},
    {gEventObjectPalette_pkmn_697, EVENT_OBJ_PAL_PKMN_697},
    {gEventObjectPalette_pkmn_698, EVENT_OBJ_PAL_PKMN_698},
    {gEventObjectPalette_pkmn_699, EVENT_OBJ_PAL_PKMN_699},
    {gEventObjectPalette_pkmn_700, EVENT_OBJ_PAL_PKMN_700},
    {gEventObjectPalette_pkmn_701, EVENT_OBJ_PAL_PKMN_701},
    {gEventObjectPalette_pkmn_702, EVENT_OBJ_PAL_PKMN_702},
    {gEventObjectPalette_pkmn_703, EVENT_OBJ_PAL_PKMN_703},
    {gEventObjectPalette_pkmn_704, EVENT_OBJ_PAL_PKMN_704},
    {gEventObjectPalette_pkmn_705, EVENT_OBJ_PAL_PKMN_705},
    {gEventObjectPalette_pkmn_706, EVENT_OBJ_PAL_PKMN_706},
    {gEventObjectPalette_pkmn_707, EVENT_OBJ_PAL_PKMN_707},
    {gEventObjectPalette_pkmn_708, EVENT_OBJ_PAL_PKMN_708},
    {gEventObjectPalette_pkmn_709, EVENT_OBJ_PAL_PKMN_709},
    {gEventObjectPalette_pkmn_710, EVENT_OBJ_PAL_PKMN_710},
    {gEventObjectPalette_pkmn_711, EVENT_OBJ_PAL_PKMN_711},
    {gEventObjectPalette_pkmn_712, EVENT_OBJ_PAL_PKMN_712},
    {gEventObjectPalette_pkmn_713, EVENT_OBJ_PAL_PKMN_713},
    {gEventObjectPalette_pkmn_714, EVENT_OBJ_PAL_PKMN_714},
    {gEventObjectPalette_pkmn_715, EVENT_OBJ_PAL_PKMN_715},
    {gEventObjectPalette_pkmn_716, EVENT_OBJ_PAL_PKMN_716},
    {gEventObjectPalette_pkmn_717, EVENT_OBJ_PAL_PKMN_717},
    {gEventObjectPalette_pkmn_718, EVENT_OBJ_PAL_PKMN_718},
    {gEventObjectPalette_pkmn_719, EVENT_OBJ_PAL_PKMN_719},
    {gEventObjectPalette_pkmn_720, EVENT_OBJ_PAL_PKMN_720},
    {gEventObjectPalette_pkmn_721, EVENT_OBJ_PAL_PKMN_721},
    {gEventObjectPalette_pkmn_722, EVENT_OBJ_PAL_PKMN_722},
    {gEventObjectPalette_pkmn_723, EVENT_OBJ_PAL_PKMN_723},
    {gEventObjectPalette_pkmn_724, EVENT_OBJ_PAL_PKMN_724},
    {gEventObjectPalette_pkmn_725, EVENT_OBJ_PAL_PKMN_725},
    {gEventObjectPalette_pkmn_726, EVENT_OBJ_PAL_PKMN_726},
    {gEventObjectPalette_pkmn_727, EVENT_OBJ_PAL_PKMN_727},
    {gEventObjectPalette_pkmn_728, EVENT_OBJ_PAL_PKMN_728},
    {gEventObjectPalette_pkmn_729, EVENT_OBJ_PAL_PKMN_729},
    {gEventObjectPalette_pkmn_730, EVENT_OBJ_PAL_PKMN_730},
    {gEventObjectPalette_pkmn_731, EVENT_OBJ_PAL_PKMN_731},
    {gEventObjectPalette_pkmn_732, EVENT_OBJ_PAL_PKMN_732},
    {gEventObjectPalette_pkmn_733, EVENT_OBJ_PAL_PKMN_733},
    {gEventObjectPalette_pkmn_734, EVENT_OBJ_PAL_PKMN_734},
    {gEventObjectPalette_pkmn_735, EVENT_OBJ_PAL_PKMN_735},
    {gEventObjectPalette_pkmn_736, EVENT_OBJ_PAL_PKMN_736},
    {gEventObjectPalette_pkmn_737, EVENT_OBJ_PAL_PKMN_737},
    {gEventObjectPalette_pkmn_738, EVENT_OBJ_PAL_PKMN_738},
    {gEventObjectPalette_pkmn_739, EVENT_OBJ_PAL_PKMN_739},
    {gEventObjectPalette_pkmn_740, EVENT_OBJ_PAL_PKMN_740},
    {gEventObjectPalette_pkmn_741, EVENT_OBJ_PAL_PKMN_741},
    {gEventObjectPalette_pkmn_742, EVENT_OBJ_PAL_PKMN_742},
    {gEventObjectPalette_pkmn_743, EVENT_OBJ_PAL_PKMN_743},
    {gEventObjectPalette_pkmn_744, EVENT_OBJ_PAL_PKMN_744},
    {gEventObjectPalette_pkmn_745, EVENT_OBJ_PAL_PKMN_745},
    {gEventObjectPalette_pkmn_746, EVENT_OBJ_PAL_PKMN_746},
    {gEventObjectPalette_pkmn_747, EVENT_OBJ_PAL_PKMN_747},
    {gEventObjectPalette_pkmn_748, EVENT_OBJ_PAL_PKMN_748},
    {gEventObjectPalette_pkmn_749, EVENT_OBJ_PAL_PKMN_749},
    {gEventObjectPalette_pkmn_750, EVENT_OBJ_PAL_PKMN_750},
    {gEventObjectPalette_pkmn_751, EVENT_OBJ_PAL_PKMN_751},
    {gEventObjectPalette_pkmn_752, EVENT_OBJ_PAL_PKMN_752},
    {gEventObjectPalette_pkmn_753, EVENT_OBJ_PAL_PKMN_753},
    {gEventObjectPalette_pkmn_754, EVENT_OBJ_PAL_PKMN_754},
    {gEventObjectPalette_pkmn_755, EVENT_OBJ_PAL_PKMN_755},
    {gEventObjectPalette_pkmn_756, EVENT_OBJ_PAL_PKMN_756},
    {gEventObjectPalette_pkmn_757, EVENT_OBJ_PAL_PKMN_757},
    {gEventObjectPalette_pkmn_758, EVENT_OBJ_PAL_PKMN_758},
    {gEventObjectPalette_pkmn_759, EVENT_OBJ_PAL_PKMN_759},
    {gEventObjectPalette_pkmn_760, EVENT_OBJ_PAL_PKMN_760},
    {gEventObjectPalette_pkmn_761, EVENT_OBJ_PAL_PKMN_761},
    {gEventObjectPalette_pkmn_762, EVENT_OBJ_PAL_PKMN_762},
    {gEventObjectPalette_pkmn_763, EVENT_OBJ_PAL_PKMN_763},
    {gEventObjectPalette_pkmn_764, EVENT_OBJ_PAL_PKMN_764},
    {gEventObjectPalette_pkmn_765, EVENT_OBJ_PAL_PKMN_765},
    {gEventObjectPalette_pkmn_766, EVENT_OBJ_PAL_PKMN_766},
    {gEventObjectPalette_pkmn_767, EVENT_OBJ_PAL_PKMN_767},
    {gEventObjectPalette_pkmn_768, EVENT_OBJ_PAL_PKMN_768},
    {gEventObjectPalette_pkmn_769, EVENT_OBJ_PAL_PKMN_769},
    {gEventObjectPalette_pkmn_770, EVENT_OBJ_PAL_PKMN_770},
    {gEventObjectPalette_pkmn_771, EVENT_OBJ_PAL_PKMN_771},
    {gEventObjectPalette_pkmn_772, EVENT_OBJ_PAL_PKMN_772},
    {gEventObjectPalette_pkmn_773, EVENT_OBJ_PAL_PKMN_773},
    {gEventObjectPalette_pkmn_774, EVENT_OBJ_PAL_PKMN_774},
    {gEventObjectPalette_pkmn_775, EVENT_OBJ_PAL_PKMN_775},
    {gEventObjectPalette_pkmn_776, EVENT_OBJ_PAL_PKMN_776},
    {gEventObjectPalette_pkmn_777, EVENT_OBJ_PAL_PKMN_777},
    {gEventObjectPalette_pkmn_778, EVENT_OBJ_PAL_PKMN_778},
    {gEventObjectPalette_pkmn_779, EVENT_OBJ_PAL_PKMN_779},
    {gEventObjectPalette_pkmn_780, EVENT_OBJ_PAL_PKMN_780},
    {gEventObjectPalette_pkmn_781, EVENT_OBJ_PAL_PKMN_781},
    {gEventObjectPalette_pkmn_782, EVENT_OBJ_PAL_PKMN_782},
    {gEventObjectPalette_pkmn_783, EVENT_OBJ_PAL_PKMN_783},
    {gEventObjectPalette_pkmn_784, EVENT_OBJ_PAL_PKMN_784},
    {gEventObjectPalette_pkmn_785, EVENT_OBJ_PAL_PKMN_785},
    {gEventObjectPalette_pkmn_786, EVENT_OBJ_PAL_PKMN_786},
    {gEventObjectPalette_pkmn_787, EVENT_OBJ_PAL_PKMN_787},
    {gEventObjectPalette_pkmn_788, EVENT_OBJ_PAL_PKMN_788},
    {gEventObjectPalette_pkmn_789, EVENT_OBJ_PAL_PKMN_789},
    {gEventObjectPalette_pkmn_790, EVENT_OBJ_PAL_PKMN_790},
    {gEventObjectPalette_pkmn_791, EVENT_OBJ_PAL_PKMN_791},
    {gEventObjectPalette_pkmn_792, EVENT_OBJ_PAL_PKMN_792},
    {gEventObjectPalette_pkmn_793, EVENT_OBJ_PAL_PKMN_793},
    {gEventObjectPalette_pkmn_794, EVENT_OBJ_PAL_PKMN_794},
    {gEventObjectPalette_pkmn_795, EVENT_OBJ_PAL_PKMN_795},
    {gEventObjectPalette_pkmn_796, EVENT_OBJ_PAL_PKMN_796},
    {gEventObjectPalette_pkmn_797, EVENT_OBJ_PAL_PKMN_797},
    {gEventObjectPalette_pkmn_798, EVENT_OBJ_PAL_PKMN_798},
    {gEventObjectPalette_pkmn_799, EVENT_OBJ_PAL_PKMN_799},
    {gEventObjectPalette_pkmn_800, EVENT_OBJ_PAL_PKMN_800},
    {gEventObjectPalette_pkmn_801, EVENT_OBJ_PAL_PKMN_801},
    {gEventObjectPalette_pkmn_802, EVENT_OBJ_PAL_PKMN_802},
    {gEventObjectPalette_pkmn_803, EVENT_OBJ_PAL_PKMN_803},
    {gEventObjectPalette_pkmn_804, EVENT_OBJ_PAL_PKMN_804},
    {gEventObjectPalette_pkmn_805, EVENT_OBJ_PAL_PKMN_805},
    {gEventObjectPalette_pkmn_806, EVENT_OBJ_PAL_PKMN_806},
    {gEventObjectPalette_pkmn_807, EVENT_OBJ_PAL_PKMN_807},
    {NULL,                  0x0000},
};

#include "data/field_event_obj/berry_tree_graphics_tables.h"
#include "data/field_event_obj/field_effect_objects.h"

const s16 gMovementDelaysMedium[] = {32, 64,  96, 128};
const s16 gMovementDelaysLong[] =   {32, 64, 128, 192};
const s16 gMovementDelaysShort[] =  {32, 48,  64,  80};

#include "data/field_event_obj/movement_type_func_tables.h"

const u8 gFaceDirectionAnimNums[] = {
    [DIR_NONE] = 0,
    [DIR_SOUTH] = 0,
    [DIR_NORTH] = 1,
    [DIR_WEST] = 2,
    [DIR_EAST] = 3,
    [DIR_SOUTHWEST] = 0,
    [DIR_SOUTHEAST] = 0,
    [DIR_NORTHWEST] = 1,
    [DIR_NORTHEAST] = 1,
};
const u8 gMoveDirectionAnimNums[] = {
    [DIR_NONE] = 4,
    [DIR_SOUTH] = 4,
    [DIR_NORTH] = 5,
    [DIR_WEST] = 6,
    [DIR_EAST] = 7,
    [DIR_SOUTHWEST] = 4,
    [DIR_SOUTHEAST] = 4,
    [DIR_NORTHWEST] = 5,
    [DIR_NORTHEAST] = 5,
};
const u8 gMoveDirectionFastAnimNums[] = {
    [DIR_NONE] = 8,
    [DIR_SOUTH] = 8,
    [DIR_NORTH] = 9,
    [DIR_WEST] = 10,
    [DIR_EAST] = 11,
    [DIR_SOUTHWEST] = 8,
    [DIR_SOUTHEAST] = 8,
    [DIR_NORTHWEST] = 9,
    [DIR_NORTHEAST] = 9,
};
const u8 gMoveDirectionFasterAnimNums[] = {
    [DIR_NONE] = 12,
    [DIR_SOUTH] = 12,
    [DIR_NORTH] = 13,
    [DIR_WEST] = 14,
    [DIR_EAST] = 15,
    [DIR_SOUTHWEST] = 12,
    [DIR_SOUTHEAST] = 12,
    [DIR_NORTHWEST] = 13,
    [DIR_NORTHEAST] = 13,
};
const u8 gMoveDirectionFastestAnimNums[] = {
    [DIR_NONE] = 16,
    [DIR_SOUTH] = 16,
    [DIR_NORTH] = 17,
    [DIR_WEST] = 18,
    [DIR_EAST] = 19,
    [DIR_SOUTHWEST] = 16,
    [DIR_SOUTHEAST] = 16,
    [DIR_NORTHWEST] = 17,
    [DIR_NORTHEAST] = 17,
};
const u8 gJumpSpecialDirectionAnimNums[] = { // used for jumping onto surf mon
    [DIR_NONE] = 20,
    [DIR_SOUTH] = 20,
    [DIR_NORTH] = 21,
    [DIR_WEST] = 22,
    [DIR_EAST] = 23,
    [DIR_SOUTHWEST] = 20,
    [DIR_SOUTHEAST] = 20,
    [DIR_NORTHWEST] = 21,
    [DIR_NORTHEAST] = 21,
};
const u8 gAcroWheelieDirectionAnimNums[] = {
    [DIR_NONE] = 20,
    [DIR_SOUTH] = 20,
    [DIR_NORTH] = 21,
    [DIR_WEST] = 22,
    [DIR_EAST] = 23,
    [DIR_SOUTHWEST] = 20,
    [DIR_SOUTHEAST] = 20,
    [DIR_NORTHWEST] = 21,
    [DIR_NORTHEAST] = 21,
};
const u8 gUnrefAnimNums_08375633[] = {
    [DIR_NONE] = 24,
    [DIR_SOUTH] = 24,
    [DIR_NORTH] = 25,
    [DIR_WEST] = 26,
    [DIR_EAST] = 27,
    [DIR_SOUTHWEST] = 24,
    [DIR_SOUTHEAST] = 24,
    [DIR_NORTHWEST] = 25,
    [DIR_NORTHEAST] = 25,
};
const u8 gAcroEndWheelieDirectionAnimNums[] = {
    [DIR_NONE] = 28,
    [DIR_SOUTH] = 28,
    [DIR_NORTH] = 29,
    [DIR_WEST] = 30,
    [DIR_EAST] = 31,
    [DIR_SOUTHWEST] = 28,
    [DIR_SOUTHEAST] = 28,
    [DIR_NORTHWEST] = 29,
    [DIR_NORTHEAST] = 29,
};
const u8 gAcroUnusedActionDirectionAnimNums[] = {
    [DIR_NONE] = 32,
    [DIR_SOUTH] = 32,
    [DIR_NORTH] = 33,
    [DIR_WEST] = 34,
    [DIR_EAST] = 35,
    [DIR_SOUTHWEST] = 32,
    [DIR_SOUTHEAST] = 32,
    [DIR_NORTHWEST] = 33,
    [DIR_NORTHEAST] = 33,
};
const u8 gAcroWheeliePedalDirectionAnimNums[] = {
    [DIR_NONE] = 36,
    [DIR_SOUTH] = 36,
    [DIR_NORTH] = 37,
    [DIR_WEST] = 38,
    [DIR_EAST] = 39,
    [DIR_SOUTHWEST] = 36,
    [DIR_SOUTHEAST] = 36,
    [DIR_NORTHWEST] = 37,
    [DIR_NORTHEAST] = 37,
};
const u8 gFishingDirectionAnimNums[] = {
    [DIR_NONE] = 0,
    [DIR_SOUTH] = 0,
    [DIR_NORTH] = 1,
    [DIR_WEST] = 2,
    [DIR_EAST] = 3,
    [DIR_SOUTHWEST] = 0,
    [DIR_SOUTHEAST] = 0,
    [DIR_NORTHWEST] = 1,
    [DIR_NORTHEAST] = 1,
};
const u8 gFishingNoCatchDirectionAnimNums[] = {
    [DIR_NONE] = 4,
    [DIR_SOUTH] = 4,
    [DIR_NORTH] = 5,
    [DIR_WEST] = 6,
    [DIR_EAST] = 7,
    [DIR_SOUTHWEST] = 4,
    [DIR_SOUTHEAST] = 4,
    [DIR_NORTHWEST] = 5,
    [DIR_NORTHEAST] = 5,
};
const u8 gFishingBiteDirectionAnimNums[] = {
    [DIR_NONE] = 8,
    [DIR_SOUTH] = 8,
    [DIR_NORTH] = 9,
    [DIR_WEST] = 10,
    [DIR_EAST] = 11,
    [DIR_SOUTHWEST] = 8,
    [DIR_SOUTHEAST] = 8,
    [DIR_NORTHWEST] = 9,
    [DIR_NORTHEAST] = 9,
};
const u8 gRunningDirectionAnimNums[] = {
    [DIR_NONE] = 20,
    [DIR_SOUTH] = 20,
    [DIR_NORTH] = 21,
    [DIR_WEST] = 22,
    [DIR_EAST] = 23,
    [DIR_SOUTHWEST] = 20,
    [DIR_SOUTHEAST] = 20,
    [DIR_NORTHWEST] = 21,
    [DIR_NORTHEAST] = 21,
};

const u8 gTrainerFacingDirectionMovementTypes[] = {
    [DIR_NONE] = MOVEMENT_TYPE_FACE_DOWN,
    [DIR_SOUTH] = MOVEMENT_TYPE_FACE_DOWN,
    [DIR_NORTH] = MOVEMENT_TYPE_FACE_UP,
    [DIR_WEST] = MOVEMENT_TYPE_FACE_LEFT,
    [DIR_EAST] = MOVEMENT_TYPE_FACE_RIGHT,
    [DIR_SOUTHWEST] = MOVEMENT_TYPE_FACE_DOWN,
    [DIR_SOUTHEAST] = MOVEMENT_TYPE_FACE_DOWN,
    [DIR_NORTHWEST] = MOVEMENT_TYPE_FACE_UP,
    [DIR_NORTHEAST] = MOVEMENT_TYPE_FACE_UP,
};

bool8 (*const gOppositeDirectionBlockedMetatileFuncs[])(u8) = {
    MetatileBehavior_IsSouthBlocked,
    MetatileBehavior_IsNorthBlocked,
    MetatileBehavior_IsWestBlocked,
    MetatileBehavior_IsEastBlocked
};

bool8 (*const gDirectionBlockedMetatileFuncs[])(u8) = {
    MetatileBehavior_IsNorthBlocked,
    MetatileBehavior_IsSouthBlocked,
    MetatileBehavior_IsEastBlocked,
    MetatileBehavior_IsWestBlocked
};

static const struct Coords16 sDirectionToVectors[] = {
    { 0,  0},
    { 0,  1},
    { 0, -1},
    {-1,  0},
    { 1,  0},
    {-1,  1},
    { 1,  1},
    {-1, -1},
    { 1, -1}
};

const u8 gFaceDirectionMovementActions[] = {
    MOVEMENT_ACTION_FACE_DOWN,
    MOVEMENT_ACTION_FACE_DOWN,
    MOVEMENT_ACTION_FACE_UP,
    MOVEMENT_ACTION_FACE_LEFT,
    MOVEMENT_ACTION_FACE_RIGHT,
};
const u8 gWalkSlowMovementActions[] = {
    MOVEMENT_ACTION_WALK_SLOW_DOWN,
    MOVEMENT_ACTION_WALK_SLOW_DOWN,
    MOVEMENT_ACTION_WALK_SLOW_UP,
    MOVEMENT_ACTION_WALK_SLOW_LEFT,
    MOVEMENT_ACTION_WALK_SLOW_RIGHT,
};
const u8 gWalkNormalMovementActions[] = {
    MOVEMENT_ACTION_WALK_NORMAL_DOWN,
    MOVEMENT_ACTION_WALK_NORMAL_DOWN,
    MOVEMENT_ACTION_WALK_NORMAL_UP,
    MOVEMENT_ACTION_WALK_NORMAL_LEFT,
    MOVEMENT_ACTION_WALK_NORMAL_RIGHT,
};
const u8 gWalkFastMovementActions[] = {
    MOVEMENT_ACTION_WALK_FAST_DOWN,
    MOVEMENT_ACTION_WALK_FAST_DOWN,
    MOVEMENT_ACTION_WALK_FAST_UP,
    MOVEMENT_ACTION_WALK_FAST_LEFT,
    MOVEMENT_ACTION_WALK_FAST_RIGHT,
};
const u8 gRideWaterCurrentMovementActions[] = {
    MOVEMENT_ACTION_RIDE_WATER_CURRENT_DOWN,
    MOVEMENT_ACTION_RIDE_WATER_CURRENT_DOWN,
    MOVEMENT_ACTION_RIDE_WATER_CURRENT_UP,
    MOVEMENT_ACTION_RIDE_WATER_CURRENT_LEFT,
    MOVEMENT_ACTION_RIDE_WATER_CURRENT_RIGHT,
};
const u8 gWalkFastestMovementActions[] = {
    MOVEMENT_ACTION_WALK_FASTEST_DOWN,
    MOVEMENT_ACTION_WALK_FASTEST_DOWN,
    MOVEMENT_ACTION_WALK_FASTEST_UP,
    MOVEMENT_ACTION_WALK_FASTEST_LEFT,
    MOVEMENT_ACTION_WALK_FASTEST_RIGHT,
};
const u8 gSlideMovementActions[] = {
    MOVEMENT_ACTION_SLIDE_DOWN,
    MOVEMENT_ACTION_SLIDE_DOWN,
    MOVEMENT_ACTION_SLIDE_UP,
    MOVEMENT_ACTION_SLIDE_LEFT,
    MOVEMENT_ACTION_SLIDE_RIGHT,
};
const u8 gPlayerRunMovementActions[] = {
    MOVEMENT_ACTION_PLAYER_RUN_DOWN,
    MOVEMENT_ACTION_PLAYER_RUN_DOWN,
    MOVEMENT_ACTION_PLAYER_RUN_UP,
    MOVEMENT_ACTION_PLAYER_RUN_LEFT,
    MOVEMENT_ACTION_PLAYER_RUN_RIGHT,
};
const u8 gJump2MovementActions[] = {
    MOVEMENT_ACTION_JUMP_2_DOWN,
    MOVEMENT_ACTION_JUMP_2_DOWN,
    MOVEMENT_ACTION_JUMP_2_UP,
    MOVEMENT_ACTION_JUMP_2_LEFT,
    MOVEMENT_ACTION_JUMP_2_RIGHT,
};
const u8 gJumpInPlaceMovementActions[] = {
    MOVEMENT_ACTION_JUMP_IN_PLACE_DOWN,
    MOVEMENT_ACTION_JUMP_IN_PLACE_DOWN,
    MOVEMENT_ACTION_JUMP_IN_PLACE_UP,
    MOVEMENT_ACTION_JUMP_IN_PLACE_LEFT,
    MOVEMENT_ACTION_JUMP_IN_PLACE_RIGHT,
};
const u8 gJumpInPlaceTurnAroundMovementActions[] = {
    MOVEMENT_ACTION_JUMP_IN_PLACE_UP_DOWN,
    MOVEMENT_ACTION_JUMP_IN_PLACE_UP_DOWN,
    MOVEMENT_ACTION_JUMP_IN_PLACE_DOWN_UP,
    MOVEMENT_ACTION_JUMP_IN_PLACE_RIGHT_LEFT,
    MOVEMENT_ACTION_JUMP_IN_PLACE_LEFT_RIGHT,
};
const u8 gJumpMovementActions[] = {
    MOVEMENT_ACTION_JUMP_DOWN,
    MOVEMENT_ACTION_JUMP_DOWN,
    MOVEMENT_ACTION_JUMP_UP,
    MOVEMENT_ACTION_JUMP_LEFT,
    MOVEMENT_ACTION_JUMP_RIGHT,
};
const u8 gJumpSpecialMovementActions[] = {
    MOVEMENT_ACTION_JUMP_SPECIAL_DOWN,
    MOVEMENT_ACTION_JUMP_SPECIAL_DOWN,
    MOVEMENT_ACTION_JUMP_SPECIAL_UP,
    MOVEMENT_ACTION_JUMP_SPECIAL_LEFT,
    MOVEMENT_ACTION_JUMP_SPECIAL_RIGHT,
};
const u8 gWalkInPlaceSlowMovementActions[] = {
    MOVEMENT_ACTION_WALK_IN_PLACE_SLOW_DOWN,
    MOVEMENT_ACTION_WALK_IN_PLACE_SLOW_DOWN,
    MOVEMENT_ACTION_WALK_IN_PLACE_SLOW_UP,
    MOVEMENT_ACTION_WALK_IN_PLACE_SLOW_LEFT,
    MOVEMENT_ACTION_WALK_IN_PLACE_SLOW_RIGHT,
};
const u8 gWalkInPlaceNormalMovementActions[] = {
    MOVEMENT_ACTION_WALK_IN_PLACE_NORMAL_DOWN,
    MOVEMENT_ACTION_WALK_IN_PLACE_NORMAL_DOWN,
    MOVEMENT_ACTION_WALK_IN_PLACE_NORMAL_UP,
    MOVEMENT_ACTION_WALK_IN_PLACE_NORMAL_LEFT,
    MOVEMENT_ACTION_WALK_IN_PLACE_NORMAL_RIGHT,
};
const u8 gWalkInPlaceFastMovementActions[] = {
    MOVEMENT_ACTION_WALK_IN_PLACE_FAST_DOWN,
    MOVEMENT_ACTION_WALK_IN_PLACE_FAST_DOWN,
    MOVEMENT_ACTION_WALK_IN_PLACE_FAST_UP,
    MOVEMENT_ACTION_WALK_IN_PLACE_FAST_LEFT,
    MOVEMENT_ACTION_WALK_IN_PLACE_FAST_RIGHT,
};
const u8 gWalkInPlaceFastestMovementActions[] = {
    MOVEMENT_ACTION_WALK_IN_PLACE_FASTEST_DOWN,
    MOVEMENT_ACTION_WALK_IN_PLACE_FASTEST_DOWN,
    MOVEMENT_ACTION_WALK_IN_PLACE_FASTEST_UP,
    MOVEMENT_ACTION_WALK_IN_PLACE_FASTEST_LEFT,
    MOVEMENT_ACTION_WALK_IN_PLACE_FASTEST_RIGHT,
};
const u8 gAcroWheelieFaceDirectionMovementActions[] = {
    MOVEMENT_ACTION_ACRO_WHEELIE_FACE_DOWN,
    MOVEMENT_ACTION_ACRO_WHEELIE_FACE_DOWN,
    MOVEMENT_ACTION_ACRO_WHEELIE_FACE_UP,
    MOVEMENT_ACTION_ACRO_WHEELIE_FACE_LEFT,
    MOVEMENT_ACTION_ACRO_WHEELIE_FACE_RIGHT,
};
const u8 gAcroPopWheelieFaceDirectionMovementActions[] = {
    MOVEMENT_ACTION_ACRO_POP_WHEELIE_DOWN,
    MOVEMENT_ACTION_ACRO_POP_WHEELIE_DOWN,
    MOVEMENT_ACTION_ACRO_POP_WHEELIE_UP,
    MOVEMENT_ACTION_ACRO_POP_WHEELIE_LEFT,
    MOVEMENT_ACTION_ACRO_POP_WHEELIE_RIGHT,
};
const u8 gAcroEndWheelieFaceDirectionMovementActions[] = {
    MOVEMENT_ACTION_ACRO_END_WHEELIE_FACE_DOWN,
    MOVEMENT_ACTION_ACRO_END_WHEELIE_FACE_DOWN,
    MOVEMENT_ACTION_ACRO_END_WHEELIE_FACE_UP,
    MOVEMENT_ACTION_ACRO_END_WHEELIE_FACE_LEFT,
    MOVEMENT_ACTION_ACRO_END_WHEELIE_FACE_RIGHT,
};
const u8 gAcroWheelieHopFaceDirectionMovementActions[] = {
    MOVEMENT_ACTION_ACRO_WHEELIE_HOP_FACE_DOWN,
    MOVEMENT_ACTION_ACRO_WHEELIE_HOP_FACE_DOWN,
    MOVEMENT_ACTION_ACRO_WHEELIE_HOP_FACE_UP,
    MOVEMENT_ACTION_ACRO_WHEELIE_HOP_FACE_LEFT,
    MOVEMENT_ACTION_ACRO_WHEELIE_HOP_FACE_RIGHT,
};
const u8 gAcroWheelieHopDirectionMovementActions[] = {
    MOVEMENT_ACTION_ACRO_WHEELIE_HOP_DOWN,
    MOVEMENT_ACTION_ACRO_WHEELIE_HOP_DOWN,
    MOVEMENT_ACTION_ACRO_WHEELIE_HOP_UP,
    MOVEMENT_ACTION_ACRO_WHEELIE_HOP_LEFT,
    MOVEMENT_ACTION_ACRO_WHEELIE_HOP_RIGHT,
};
const u8 gAcroWheelieJumpDirectionMovementActions[] = {
    MOVEMENT_ACTION_ACRO_WHEELIE_JUMP_DOWN,
    MOVEMENT_ACTION_ACRO_WHEELIE_JUMP_DOWN,
    MOVEMENT_ACTION_ACRO_WHEELIE_JUMP_UP,
    MOVEMENT_ACTION_ACRO_WHEELIE_JUMP_LEFT,
    MOVEMENT_ACTION_ACRO_WHEELIE_JUMP_RIGHT,
};
const u8 gAcroWheelieInPlaceDirectionMovementActions[] = {
    MOVEMENT_ACTION_ACRO_WHEELIE_IN_PLACE_DOWN,
    MOVEMENT_ACTION_ACRO_WHEELIE_IN_PLACE_DOWN,
    MOVEMENT_ACTION_ACRO_WHEELIE_IN_PLACE_UP,
    MOVEMENT_ACTION_ACRO_WHEELIE_IN_PLACE_LEFT,
    MOVEMENT_ACTION_ACRO_WHEELIE_IN_PLACE_RIGHT,
};
const u8 gAcroPopWheelieMoveDirectionMovementActions[] = {
    MOVEMENT_ACTION_ACRO_POP_WHEELIE_MOVE_DOWN,
    MOVEMENT_ACTION_ACRO_POP_WHEELIE_MOVE_DOWN,
    MOVEMENT_ACTION_ACRO_POP_WHEELIE_MOVE_UP,
    MOVEMENT_ACTION_ACRO_POP_WHEELIE_MOVE_LEFT,
    MOVEMENT_ACTION_ACRO_POP_WHEELIE_MOVE_RIGHT,
};
const u8 gAcroWheelieMoveDirectionMovementActions[] = {
    MOVEMENT_ACTION_ACRO_WHEELIE_MOVE_DOWN,
    MOVEMENT_ACTION_ACRO_WHEELIE_MOVE_DOWN,
    MOVEMENT_ACTION_ACRO_WHEELIE_MOVE_UP,
    MOVEMENT_ACTION_ACRO_WHEELIE_MOVE_LEFT,
    MOVEMENT_ACTION_ACRO_WHEELIE_MOVE_RIGHT,
};
const u8 gAcroEndWheelieMoveDirectionMovementActions[] = {
    MOVEMENT_ACTION_ACRO_END_WHEELIE_MOVE_DOWN,
    MOVEMENT_ACTION_ACRO_END_WHEELIE_MOVE_DOWN,
    MOVEMENT_ACTION_ACRO_END_WHEELIE_MOVE_UP,
    MOVEMENT_ACTION_ACRO_END_WHEELIE_MOVE_LEFT,
    MOVEMENT_ACTION_ACRO_END_WHEELIE_MOVE_RIGHT,
};

const u8 gOppositeDirections[] = {
    DIR_NORTH,
    DIR_SOUTH,
    DIR_EAST,
    DIR_WEST,
    DIR_NORTHEAST,
    DIR_NORTHWEST,
    DIR_SOUTHEAST,
    DIR_SOUTHWEST,
};

const u8 gUnknown_0850DC2F[][4] = {
    {2, 1, 4, 3},
    {1, 2, 3, 4},
    {3, 4, 2, 1},
    {4, 3, 1, 2}
};

const u8 gUnknown_0850DC3F[][4] = {
    {2, 1, 4, 3},
    {1, 2, 3, 4},
    {4, 3, 1, 2},
    {3, 4, 2, 1}
};

#include "data/field_event_obj/movement_action_func_tables.h"

// Code

static void ClearEventObject(struct EventObject *eventObject)
{
    *eventObject = (struct EventObject){};
    eventObject->localId = 0xFF;
    eventObject->mapNum = 0xFF;
    eventObject->mapGroup = 0xFF;
    eventObject->movementActionId = 0xFF;
}

static void ClearAllEventObjects(void)
{
    u8 i;

    for (i = 0; i < EVENT_OBJECTS_COUNT; i++)
        ClearEventObject(&gEventObjects[i]);
}

void ResetEventObjects(void)
{
    ClearLinkPlayerEventObjects();
    ClearAllEventObjects();
    ClearPlayerAvatarInfo();
    CreateReflectionEffectSprites();
}

static void CreateReflectionEffectSprites(void)
{
    u8 spriteId = CreateSpriteAtEnd(gFieldEffectObjectTemplatePointers[21], 0, 0, 31);
    gSprites[spriteId].oam.affineMode = 1;
    InitSpriteAffineAnim(&gSprites[spriteId]);
    StartSpriteAffineAnim(&gSprites[spriteId], 0);
    gSprites[spriteId].invisible = TRUE;

    spriteId = CreateSpriteAtEnd(gFieldEffectObjectTemplatePointers[21], 0, 0, 31);
    gSprites[spriteId].oam.affineMode = 1;
    InitSpriteAffineAnim(&gSprites[spriteId]);
    StartSpriteAffineAnim(&gSprites[spriteId], 1);
    gSprites[spriteId].invisible = TRUE;
}

u8 GetFirstInactiveEventObjectId(void)
{
    u8 i;
    for (i = 0; i < EVENT_OBJECTS_COUNT; i++)
    {
        if (!gEventObjects[i].active)
            break;
    }

    return i;
}

u8 GetEventObjectIdByLocalIdAndMap(u8 localId, u8 mapNum, u8 mapGroupId)
{
    if (localId < EVENT_OBJ_ID_PLAYER)
    {
        return GetEventObjectIdByLocalIdAndMapInternal(localId, mapNum, mapGroupId);
    }
    return GetEventObjectIdByLocalId(localId);
}

bool8 TryGetEventObjectIdByLocalIdAndMap(u8 localId, u8 mapNum, u8 mapGroupId, u8 *eventObjectId)
{
    *eventObjectId = GetEventObjectIdByLocalIdAndMap(localId, mapNum, mapGroupId);
    if (*eventObjectId == EVENT_OBJECTS_COUNT)
        return TRUE;
    else
        return FALSE;
}

u8 GetEventObjectIdByXY(s16 x, s16 y)
{
    u8 i;
    for (i = 0; i < EVENT_OBJECTS_COUNT; i++)
    {
        if (gEventObjects[i].active && gEventObjects[i].currentCoords.x == x && gEventObjects[i].currentCoords.y == y)
            break;
    }

    return i;
}

static u8 GetEventObjectIdByLocalIdAndMapInternal(u8 localId, u8 mapNum, u8 mapGroupId)
{
    u8 i;
    for (i = 0; i < EVENT_OBJECTS_COUNT; i++)
    {
        if (gEventObjects[i].active && gEventObjects[i].localId == localId && gEventObjects[i].mapNum == mapNum && gEventObjects[i].mapGroup == mapGroupId)
            return i;
    }

    return EVENT_OBJECTS_COUNT;
}

static u8 GetEventObjectIdByLocalId(u8 localId)
{
    u8 i;
    for (i = 0; i < EVENT_OBJECTS_COUNT; i++)
    {
        if (gEventObjects[i].active && gEventObjects[i].localId == localId)
            return i;
    }

    return EVENT_OBJECTS_COUNT;
}

#define NONMATCHING
// This function has the same nonmatching quirk as in Ruby/Sapphire.
#ifdef NONMATCHING
static u8 InitEventObjectStateFromTemplate(struct EventObjectTemplate *template, u8 mapNum, u8 mapGroup)
{
    struct EventObject *eventObject;
    u8 eventObjectId;
    s16 x;
    s16 y;

    // mapNum and mapGroup are in the wrong registers (r7/r6 instead of r6/r7)
    if (GetAvailableEventObjectId(template->localId, mapNum, mapGroup, &eventObjectId))
    {
        return EVENT_OBJECTS_COUNT;
    }
    eventObject = &gEventObjects[eventObjectId];
    ClearEventObject(eventObject);
    x = template->x + 7;
    y = template->y + 7;
    eventObject->active = TRUE;
    eventObject->triggerGroundEffectsOnMove = TRUE;
    eventObject->graphicsId = template->graphicsId;
    eventObject->movementType = template->movementType;
    eventObject->localId = template->localId;
    eventObject->mapNum = mapNum;
    eventObject->mapGroup = mapGroup;
    eventObject->initialCoords.x = x;
    eventObject->initialCoords.y = y;
    eventObject->currentCoords.x = x;
    eventObject->currentCoords.y = y;
    eventObject->previousCoords.x = x;
    eventObject->previousCoords.y = y;
    eventObject->currentElevation = template->elevation;
    eventObject->previousElevation = template->elevation;
    // For some reason, 0x0F is placed in r9, to be used later
    eventObject->range.as_nybbles.x = template->movementRangeX;
    eventObject->range.as_nybbles.y = template->movementRangeY;
    eventObject->trainerType = template->trainerType;
    eventObject->trainerRange_berryTreeId = template->trainerRange_berryTreeId;
    eventObject->previousMovementDirection = gInitialMovementTypeFacingDirections[template->movementType];
    SetEventObjectDirection(eventObject, eventObject->previousMovementDirection);
    SetEventObjectDynamicGraphicsId(eventObject);

    if (gRangedMovementTypes[eventObject->movementType])
    {
        if ((eventObject->range.as_nybbles.x) == 0)
        {
            // r9 is invoked here
            eventObject->range.as_nybbles.x++;
        }
        if ((eventObject->range.as_nybbles.y) == 0)
        {
            eventObject->range.as_nybbles.y++;
        }
    }
    return eventObjectId;
}
#else
static NAKED u8 InitEventObjectStateFromTemplate(struct EventObjectTemplate *template, u8 mapId, u8 mapGroupId)
{
    asm_unified("\tpush {r4-r7,lr}\n"
                "\tmov r7, r9\n"
                "\tmov r6, r8\n"
                "\tpush {r6,r7}\n"
                "\tsub sp, 0x4\n"
                "\tadds r5, r0, 0\n"
                "\tlsls r1, 24\n"
                "\tlsrs r6, r1, 24\n"
                "\tlsls r2, 24\n"
                "\tlsrs r7, r2, 24\n"
                "\tldrb r0, [r5]\n"
                "\tadds r1, r6, 0\n"
                "\tadds r2, r7, 0\n"
                "\tmov r3, sp\n"
                "\tbl GetAvailableEventObjectId\n"
                "\tlsls r0, 24\n"
                "\tcmp r0, 0\n"
                "\tbeq _0808D66E\n"
                "\tmovs r0, 0x10\n"
                "\tb _0808D762\n"
                "_0808D66E:\n"
                "\tmov r0, sp\n"
                "\tldrb r1, [r0]\n"
                "\tlsls r0, r1, 3\n"
                "\tadds r0, r1\n"
                "\tlsls r0, 2\n"
                "\tldr r1, =gEventObjects\n"
                "\tadds r4, r0, r1\n"
                "\tadds r0, r4, 0\n"
                "\tbl ClearEventObject\n"
                "\tldrh r3, [r5, 0x4]\n"
                "\tadds r3, 0x7\n"
                "\tlsls r3, 16\n"
                "\tlsrs r3, 16\n"
                "\tldrh r2, [r5, 0x6]\n"
                "\tadds r2, 0x7\n"
                "\tlsls r2, 16\n"
                "\tlsrs r2, 16\n"
                "\tldrb r0, [r4]\n"
                "\tmovs r1, 0x1\n"
                "\torrs r0, r1\n"
                "\tmovs r1, 0x4\n"
                "\torrs r0, r1\n"
                "\tstrb r0, [r4]\n"
                "\tldrb r0, [r5, 0x1]\n"
                "\tstrb r0, [r4, 0x5]\n"
                "\tldrb r0, [r5, 0x9]\n"
                "\tstrb r0, [r4, 0x6]\n"
                "\tldrb r0, [r5]\n"
                "\tstrb r0, [r4, 0x8]\n"
                "\tstrb r6, [r4, 0x9]\n"
                "\tstrb r7, [r4, 0xA]\n"
                "\tstrh r3, [r4, 0xC]\n"
                "\tstrh r2, [r4, 0xE]\n"
                "\tstrh r3, [r4, 0x10]\n"
                "\tstrh r2, [r4, 0x12]\n"
                "\tstrh r3, [r4, 0x14]\n"
                "\tstrh r2, [r4, 0x16]\n"
                "\tldrb r0, [r5, 0x8]\n"
                "\tmovs r7, 0xF\n"
                "\tadds r1, r7, 0\n"
                "\tands r1, r0\n"
                "\tldrb r2, [r4, 0xB]\n"
                "\tmovs r0, 0x10\n"
                "\tnegs r0, r0\n"
                "\tmov r8, r0\n"
                "\tands r0, r2\n"
                "\torrs r0, r1\n"
                "\tstrb r0, [r4, 0xB]\n"
                "\tldrb r1, [r5, 0x8]\n"
                "\tlsls r1, 4\n"
                "\tands r0, r7\n"
                "\torrs r0, r1\n"
                "\tstrb r0, [r4, 0xB]\n"
                "\tldrb r1, [r5, 0xA]\n"
                "\tlsls r1, 28\n"
                "\tmovs r0, 0xF\n"
                "\tmov r9, r0\n"
                "\tlsrs r1, 28\n"
                "\tldrb r2, [r4, 0x19]\n"
                "\tmov r0, r8\n"
                "\tands r0, r2\n"
                "\torrs r0, r1\n"
                "\tstrb r0, [r4, 0x19]\n"
                "\tldrb r1, [r5, 0xA]\n"
                "\tlsrs r1, 4\n"
                "\tlsls r1, 4\n"
                "\tands r0, r7\n"
                "\torrs r0, r1\n"
                "\tstrb r0, [r4, 0x19]\n"
                "\tldrh r0, [r5, 0xC]\n"
                "\tstrb r0, [r4, 0x7]\n"
                "\tldrh r0, [r5, 0xE]\n"
                "\tstrb r0, [r4, 0x1D]\n"
                "\tldr r1, =gInitialMovementTypeFacingDirections\n"
                "\tldrb r0, [r5, 0x9]\n"
                "\tadds r0, r1\n"
                "\tldrb r1, [r0]\n"
                "\tadds r0, r4, 0\n"
                "\tadds r0, 0x20\n"
                "\tstrb r1, [r0]\n"
                "\tldrb r1, [r0]\n"
                "\tadds r0, r4, 0\n"
                "\tbl SetEventObjectDirection\n"
                "\tadds r0, r4, 0\n"
                "\tbl SetEventObjectDynamicGraphicsId\n"
                "\tldr r1, =gRangedMovementTypes\n"
                "\tldrb r0, [r4, 0x6]\n"
                "\tadds r0, r1\n"
                "\tldrb r0, [r0]\n"
                "\tcmp r0, 0\n"
                "\tbeq _0808D75E\n"
                "\tldrb r2, [r4, 0x19]\n"
                "\tadds r0, r7, 0\n"
                "\tands r0, r2\n"
                "\tcmp r0, 0\n"
                "\tbne _0808D746\n"
                "\tlsls r0, r2, 28\n"
                "\tlsrs r0, 28\n"
                "\tadds r0, 0x1\n"
                "\tmov r1, r9\n"
                "\tands r0, r1\n"
                "\tmov r1, r8\n"
                "\tands r1, r2\n"
                "\torrs r1, r0\n"
                "\tstrb r1, [r4, 0x19]\n"
                "_0808D746:\n"
                "\tldrb r2, [r4, 0x19]\n"
                "\tmovs r0, 0xF0\n"
                "\tands r0, r2\n"
                "\tcmp r0, 0\n"
                "\tbne _0808D75E\n"
                "\tlsrs r1, r2, 4\n"
                "\tadds r1, 0x1\n"
                "\tlsls r1, 4\n"
                "\tadds r0, r7, 0\n"
                "\tands r0, r2\n"
                "\torrs r0, r1\n"
                "\tstrb r0, [r4, 0x19]\n"
                "_0808D75E:\n"
                "\tmov r0, sp\n"
                "\tldrb r0, [r0]\n"
                "_0808D762:\n"
                "\tadd sp, 0x4\n"
                "\tpop {r3,r4}\n"
                "\tmov r8, r3\n"
                "\tmov r9, r4\n"
                "\tpop {r4-r7}\n"
                "\tpop {r1}\n"
                "\tbx r1\n"
                ".pool");
}
#endif

u8 Unref_TryInitLocalEventObject(u8 localId)
{
    u8 i;
    u8 eventObjectCount;
    struct EventObjectTemplate *template;

    if (gMapHeader.events != NULL)
    {
        if (InBattlePyramid())
        {
            eventObjectCount = GetNumBattlePyramidEventObjects();
        }
        else if (InTrainerHill())
        {
            eventObjectCount = 2;
        }
        else
        {
            eventObjectCount = gMapHeader.events->eventObjectCount;
        }
        for (i = 0; i < eventObjectCount; i++)
        {
            template = &gSaveBlock1Ptr->eventObjectTemplates[i];
            if (template->localId == localId && !FlagGet(template->flagId))
            {
                return InitEventObjectStateFromTemplate(template, gSaveBlock1Ptr->location.mapNum, gSaveBlock1Ptr->location.mapGroup);
            }
        }
    }
    return EVENT_OBJECTS_COUNT;
}

static bool8 GetAvailableEventObjectId(u16 localId, u8 mapNum, u8 mapGroup, u8 *eventObjectId)
// Looks for an empty slot.
// Returns FALSE and the location of the available slot
// in *eventObjectId.
// If no slots are available, or if the object is already
// loaded, returns TRUE.
{
    u8 i = 0;

    for (i = 0; i < EVENT_OBJECTS_COUNT; i++)
    {
        if (!gEventObjects[i].active)
            break;
        if (gEventObjects[i].localId == localId && gEventObjects[i].mapNum == mapNum && gEventObjects[i].mapGroup == mapGroup)
            return TRUE;
    }
    if (i >= EVENT_OBJECTS_COUNT)
        return TRUE;
    *eventObjectId = i;
    do
    {
        if (gEventObjects[i].active && gEventObjects[i].localId == localId && gEventObjects[i].mapNum == mapNum && gEventObjects[i].mapGroup == mapGroup)
            return TRUE;
        i++;
    } while (i < EVENT_OBJECTS_COUNT);
    return FALSE;
}

static void RemoveEventObject(struct EventObject *eventObject)
{
    eventObject->active = FALSE;
    RemoveEventObjectInternal(eventObject);
}

void RemoveEventObjectByLocalIdAndMap(u8 localId, u8 mapNum, u8 mapGroup)
{
    u8 eventObjectId;
    if (!TryGetEventObjectIdByLocalIdAndMap(localId, mapNum, mapGroup, &eventObjectId))
    {
        FlagSet(GetEventObjectFlagIdByEventObjectId(eventObjectId));
        RemoveEventObject(&gEventObjects[eventObjectId]);
    }
}

static void RemoveEventObjectInternal(struct EventObject *eventObject)
{
    u8 paletteNum;

    struct SpriteFrameImage image;
    image.size = GetEventObjectGraphicsInfo(eventObject->graphicsId)->size;
    gSprites[eventObject->spriteId].images = &image;
    paletteNum = gSprites[eventObject->spriteId].oam.paletteNum;
    DestroySprite(&gSprites[eventObject->spriteId]);
    FieldEffectFreePaletteIfUnused(paletteNum);
}

void RemoveAllEventObjectsExceptPlayer(void)
{
    u8 i;

    for (i = 0; i < EVENT_OBJECTS_COUNT; i++)
    {
        if (i != gPlayerAvatar.eventObjectId)
            RemoveEventObject(&gEventObjects[i]);
    }
}

static u8 TrySetupEventObjectSprite(struct EventObjectTemplate *eventObjectTemplate, struct SpriteTemplate *spriteTemplate, u8 mapNum, u8 mapGroup, s16 cameraX, s16 cameraY)
{
    u8 spriteId;
    u8 paletteSlot;
    u8 eventObjectId;
    struct Sprite *sprite;
    struct EventObject *eventObject;
    const struct EventObjectGraphicsInfo *graphicsInfo;

    eventObjectId = InitEventObjectStateFromTemplate(eventObjectTemplate, mapNum, mapGroup);
    if (eventObjectId == EVENT_OBJECTS_COUNT)
        return EVENT_OBJECTS_COUNT;

    eventObject = &gEventObjects[eventObjectId];
    graphicsInfo = GetEventObjectGraphicsInfo(eventObject->graphicsId);
    if (spriteTemplate->paletteTag != 0xffff)
    {
        LoadEventObjectPalette(spriteTemplate->paletteTag);
        UpdatePaletteGammaType(IndexOfSpritePaletteTag(spriteTemplate->paletteTag), GAMMA_ALT);
    }

    if (eventObject->movementType == MOVEMENT_TYPE_INVISIBLE)
        eventObject->invisible = TRUE;

    spriteId = CreateSprite(spriteTemplate, 0, 0, 0);
    if (spriteId == MAX_SPRITES)
    {
        gEventObjects[eventObjectId].active = FALSE;
        return EVENT_OBJECTS_COUNT;
    }

    sprite = &gSprites[spriteId];
    sub_8092FF0(eventObject->currentCoords.x + cameraX, eventObject->currentCoords.y + cameraY, &sprite->pos1.x, &sprite->pos1.y);
    sprite->centerToCornerVecX = -(graphicsInfo->width >> 1);
    sprite->centerToCornerVecY = -(graphicsInfo->height >> 1);
    sprite->pos1.x += 8;
    sprite->pos1.y += 16 + sprite->centerToCornerVecY;
    sprite->coordOffsetEnabled = TRUE;
    sprite->data[0] = eventObjectId;
    eventObject->spriteId = spriteId;
    eventObject->inanimate = graphicsInfo->inanimate;
    if (!eventObject->inanimate)
        StartSpriteAnim(sprite, GetFaceDirectionAnimNum(eventObject->facingDirection));

    SetObjectSubpriorityByZCoord(eventObject->previousElevation, sprite, 1);
    UpdateEventObjectVisibility(eventObject, sprite);
    return eventObjectId;
}

static u8 TrySpawnEventObjectTemplate(struct EventObjectTemplate *eventObjectTemplate, u8 mapNum, u8 mapGroup, s16 cameraX, s16 cameraY)
{
    u8 eventObjectId;
    struct SpriteTemplate spriteTemplate;
    struct SpriteFrameImage spriteFrameImage;
    const struct EventObjectGraphicsInfo *graphicsInfo;
    const struct SubspriteTable *subspriteTables = NULL;

    graphicsInfo = GetEventObjectGraphicsInfo(eventObjectTemplate->graphicsId);
    MakeObjectTemplateFromEventObjectTemplate(eventObjectTemplate, &spriteTemplate, &subspriteTables);
    spriteFrameImage.size = graphicsInfo->size;
    spriteTemplate.images = &spriteFrameImage;
    eventObjectId = TrySetupEventObjectSprite(eventObjectTemplate, &spriteTemplate, mapNum, mapGroup, cameraX, cameraY);
    if (eventObjectId == EVENT_OBJECTS_COUNT)
        return EVENT_OBJECTS_COUNT;

    gSprites[gEventObjects[eventObjectId].spriteId].images = graphicsInfo->images;
    if (subspriteTables)
        SetSubspriteTables(&gSprites[gEventObjects[eventObjectId].spriteId], subspriteTables);

    return eventObjectId;
}

u8 SpawnSpecialEventObject(struct EventObjectTemplate *eventObjectTemplate)
{
    s16 cameraX;
    s16 cameraY;

    GetEventObjectMovingCameraOffset(&cameraX, &cameraY);
    return TrySpawnEventObjectTemplate(eventObjectTemplate, gSaveBlock1Ptr->location.mapNum, gSaveBlock1Ptr->location.mapGroup, cameraX, cameraY);
}

u8 SpawnSpecialEventObjectParameterized(u16 graphicsId, u8 movementBehavior, u8 localId, s16 x, s16 y, u8 z)
{
    struct EventObjectTemplate eventObjectTemplate;

    x -= 7;
    y -= 7;
    eventObjectTemplate.localId = localId;
    eventObjectTemplate.graphicsId = graphicsId;
    eventObjectTemplate.x = x;
    eventObjectTemplate.y = y;
    eventObjectTemplate.elevation = z;
    eventObjectTemplate.movementType = movementBehavior;
    eventObjectTemplate.movementRangeX = 0;
    eventObjectTemplate.movementRangeY = 0;
    eventObjectTemplate.trainerType = 0;
    eventObjectTemplate.trainerRange_berryTreeId = 0;
    return SpawnSpecialEventObject(&eventObjectTemplate);
}

u8 TrySpawnEventObject(u8 localId, u8 mapNum, u8 mapGroup)
{
    struct EventObjectTemplate *eventObjectTemplate;
    s16 cameraX, cameraY;

    eventObjectTemplate = GetEventObjectTemplateByLocalIdAndMap(localId, mapNum, mapGroup);
    if (!eventObjectTemplate)
        return EVENT_OBJECTS_COUNT;

    GetEventObjectMovingCameraOffset(&cameraX, &cameraY);
    return TrySpawnEventObjectTemplate(eventObjectTemplate, mapNum, mapGroup, cameraX, cameraY);
}

static void MakeObjectTemplateFromEventObjectGraphicsInfo(u16 graphicsId, void (*callback)(struct Sprite *), struct SpriteTemplate *spriteTemplate, const struct SubspriteTable **subspriteTables)
{
    const struct EventObjectGraphicsInfo *graphicsInfo = GetEventObjectGraphicsInfo(graphicsId);

    spriteTemplate->tileTag = graphicsInfo->tileTag;
    spriteTemplate->paletteTag = graphicsInfo->paletteTag1;
    spriteTemplate->oam = graphicsInfo->oam;
    spriteTemplate->anims = graphicsInfo->anims;
    spriteTemplate->images = graphicsInfo->images;
    spriteTemplate->affineAnims = graphicsInfo->affineAnims;
    spriteTemplate->callback = callback;
    *subspriteTables = graphicsInfo->subspriteTables;
}

static void MakeObjectTemplateFromEventObjectGraphicsInfoWithCallbackIndex(u16 graphicsId, u16 callbackIndex, struct SpriteTemplate *spriteTemplate, const struct SubspriteTable **subspriteTables)
{
    MakeObjectTemplateFromEventObjectGraphicsInfo(graphicsId, sMovementTypeCallbacks[callbackIndex], spriteTemplate, subspriteTables);
}

static void MakeObjectTemplateFromEventObjectTemplate(struct EventObjectTemplate *eventObjectTemplate, struct SpriteTemplate *spriteTemplate, const struct SubspriteTable **subspriteTables)
{
    MakeObjectTemplateFromEventObjectGraphicsInfoWithCallbackIndex(eventObjectTemplate->graphicsId, eventObjectTemplate->movementType, spriteTemplate, subspriteTables);
}

u8 AddPseudoEventObject(u16 graphicsId, void (*callback)(struct Sprite *), s16 x, s16 y, u8 subpriority)
{
    struct SpriteTemplate *spriteTemplate;
    const struct SubspriteTable *subspriteTables;
    struct Sprite *sprite;
    u8 spriteId;

    spriteTemplate = malloc(sizeof(struct SpriteTemplate));
    MakeObjectTemplateFromEventObjectGraphicsInfo(graphicsId, callback, spriteTemplate, &subspriteTables);
    if (spriteTemplate->paletteTag != 0xFFFF)
    {
        LoadEventObjectPalette(spriteTemplate->paletteTag);
    }
    spriteId = CreateSprite(spriteTemplate, x, y, subpriority);
    free(spriteTemplate);

    if (spriteId != MAX_SPRITES && subspriteTables != NULL)
    {
        sprite = &gSprites[spriteId];
        SetSubspriteTables(sprite, subspriteTables);
        sprite->subspriteMode = 2;
    }
    return spriteId;
}

u8 sprite_new(u16 graphicsId, u8 a1, s16 x, s16 y, u8 z, u8 direction)
{
    u8 spriteId;
    struct Sprite *sprite;
    struct SpriteTemplate spriteTemplate;
    const struct SubspriteTable *subspriteTables;
    const struct EventObjectGraphicsInfo *graphicsInfo;

    graphicsInfo = GetEventObjectGraphicsInfo(graphicsId);
    MakeObjectTemplateFromEventObjectGraphicsInfo(graphicsId, UpdateEventObjectSpriteSubpriorityAndVisibility, &spriteTemplate, &subspriteTables);
    *(u16 *)&spriteTemplate.paletteTag = 0xFFFF;
    x += 7;
    y += 7;
    sub_80930E0(&x, &y, 8, 16);
    spriteId = CreateSpriteAtEnd(&spriteTemplate, x, y, 0);
    if (spriteId != MAX_SPRITES)
    {
        sprite = &gSprites[spriteId];
        sprite->centerToCornerVecX = -(graphicsInfo->width >> 1);
        sprite->centerToCornerVecY = -(graphicsInfo->height >> 1);
        sprite->pos1.y += sprite->centerToCornerVecY;
        sprite->oam.paletteNum = graphicsInfo->paletteSlot;
        if (sprite->oam.paletteNum >= 16)
        {
            sprite->oam.paletteNum -= 16;
        }
        sprite->coordOffsetEnabled = TRUE;
        sprite->data[0] = a1;
        sprite->data[1] = z;
        if (graphicsInfo->paletteSlot >= 16)
        {
            sub_808EAB0(graphicsInfo->paletteTag1, graphicsInfo->paletteSlot | 0xf0);
        }
        if (subspriteTables != NULL)
        {
            SetSubspriteTables(sprite, subspriteTables);
            sprite->subspriteMode = 2;
        }
        InitObjectPriorityByZCoord(sprite, z);
        SetObjectSubpriorityByZCoord(z, sprite, 1);
        StartSpriteAnim(sprite, GetFaceDirectionAnimNum(direction));
    }
    return spriteId;
}

void TrySpawnEventObjects(s16 cameraX, s16 cameraY)
{
    u8 i;
    u8 objectCount;

    if (gMapHeader.events != NULL)
    {
        s16 left = gSaveBlock1Ptr->pos.x - 2;
        s16 right = gSaveBlock1Ptr->pos.x + 17;
        s16 top = gSaveBlock1Ptr->pos.y;
        s16 bottom = gSaveBlock1Ptr->pos.y + 16;

        if (InBattlePyramid())
        {
            objectCount = GetNumBattlePyramidEventObjects();
        }
        else if (InTrainerHill())
        {
            objectCount = 2;
        }
        else
        {
            objectCount = gMapHeader.events->eventObjectCount;
        }

        for (i = 0; i < objectCount; i++)
        {
            struct EventObjectTemplate *template = &gSaveBlock1Ptr->eventObjectTemplates[i];
            s16 npcX = template->x + 7;
            s16 npcY = template->y + 7;

            if (top <= npcY && bottom >= npcY && left <= npcX && right >= npcX
                && !FlagGet(template->flagId))
                TrySpawnEventObjectTemplate(template, gSaveBlock1Ptr->location.mapNum, gSaveBlock1Ptr->location.mapGroup, cameraX, cameraY);
        }
    }
}

void RemoveEventObjectsOutsideView(void)
{
    u8 i, j;
    bool8 isActiveLinkPlayer;

    for (i = 0; i < EVENT_OBJECTS_COUNT; i++)
    {
        for (j = 0, isActiveLinkPlayer = FALSE; j < ARRAY_COUNT(gLinkPlayerEventObjects); j++)
        {
            if (gLinkPlayerEventObjects[j].active && i == gLinkPlayerEventObjects[j].eventObjId)
                isActiveLinkPlayer = TRUE;
        }
        if (!isActiveLinkPlayer)
        {
            struct EventObject *eventObject = &gEventObjects[i];

            if (eventObject->active && !eventObject->isPlayer)
                RemoveEventObjectIfOutsideView(eventObject);
        }
    }
}

static void RemoveEventObjectIfOutsideView(struct EventObject *eventObject)
{
    s16 left =   gSaveBlock1Ptr->pos.x - 2;
    s16 right =  gSaveBlock1Ptr->pos.x + 17;
    s16 top =    gSaveBlock1Ptr->pos.y;
    s16 bottom = gSaveBlock1Ptr->pos.y + 16;

    if (eventObject->currentCoords.x >= left && eventObject->currentCoords.x <= right
     && eventObject->currentCoords.y >= top && eventObject->currentCoords.y <= bottom)
        return;
    if (eventObject->initialCoords.x >= left && eventObject->initialCoords.x <= right
     && eventObject->initialCoords.y >= top && eventObject->initialCoords.y <= bottom)
        return;
    RemoveEventObject(eventObject);
}

void sub_808E16C(s16 x, s16 y)
{
    u8 i;

    ClearPlayerAvatarInfo();
    for (i = 0; i < EVENT_OBJECTS_COUNT; i++)
    {
        if (gEventObjects[i].active)
        {
            sub_808E1B8(i, x, y);
        }
    }
    CreateReflectionEffectSprites();
}

static void sub_808E1B8(u8 eventObjectId, s16 x, s16 y)
{
    u8 spriteId;
    struct Sprite *sprite;
    struct EventObject *eventObject;
    struct SpriteTemplate spriteTemplate;
    struct SpriteFrameImage spriteFrameImage;
    const struct SubspriteTable *subspriteTables;
    const struct EventObjectGraphicsInfo *graphicsInfo;

#define i spriteId
    for (i = 0; i < ARRAY_COUNT(gLinkPlayerEventObjects); i++)
    {
        if (gLinkPlayerEventObjects[i].active && eventObjectId == gLinkPlayerEventObjects[i].eventObjId)
        {
            return;
        }
    }
#undef i

    eventObject = &gEventObjects[eventObjectId];
    subspriteTables = NULL;
    graphicsInfo = GetEventObjectGraphicsInfo(eventObject->graphicsId);
    spriteFrameImage.size = graphicsInfo->size;
    MakeObjectTemplateFromEventObjectGraphicsInfoWithCallbackIndex(eventObject->graphicsId, eventObject->movementType, &spriteTemplate, &subspriteTables);
    spriteTemplate.images = &spriteFrameImage;
    if (spriteTemplate.paletteTag != 0xffff)
    {
        LoadEventObjectPalette(spriteTemplate.paletteTag);
        UpdatePaletteGammaType(IndexOfSpritePaletteTag(spriteTemplate.paletteTag), GAMMA_ALT);
    }
    spriteId = CreateSprite(&spriteTemplate, 0, 0, 0);
    if (spriteId != MAX_SPRITES)
    {
        sprite = &gSprites[spriteId];
        sub_8092FF0(x + eventObject->currentCoords.x, y + eventObject->currentCoords.y, &sprite->pos1.x, &sprite->pos1.y);
        sprite->centerToCornerVecX = -(graphicsInfo->width >> 1);
        sprite->centerToCornerVecY = -(graphicsInfo->height >> 1);
        sprite->pos1.x += 8;
        sprite->pos1.y += 16 + sprite->centerToCornerVecY;
        sprite->images = graphicsInfo->images;
        if (eventObject->movementType == MOVEMENT_TYPE_PLAYER)
        {
            SetPlayerAvatarEventObjectIdAndObjectId(eventObjectId, spriteId);
            eventObject->warpArrowSpriteId = CreateWarpArrowSprite();
        }
        if (subspriteTables != NULL)
        {
            SetSubspriteTables(sprite, subspriteTables);
        }
        sprite->coordOffsetEnabled = TRUE;
        sprite->data[0] = eventObjectId;
        eventObject->spriteId = spriteId;
        if (!eventObject->inanimate && eventObject->movementType != MOVEMENT_TYPE_PLAYER)
        {
            StartSpriteAnim(sprite, GetFaceDirectionAnimNum(eventObject->facingDirection));
        }
        sub_808E38C(eventObject);
        SetObjectSubpriorityByZCoord(eventObject->previousElevation, sprite, 1);
    }
}

static void sub_808E38C(struct EventObject *eventObject)
{
    eventObject->singleMovementActive = FALSE;
    eventObject->triggerGroundEffectsOnMove = TRUE;
    eventObject->hasShadow = FALSE;
    eventObject->hasReflection = FALSE;
    eventObject->inShortGrass = FALSE;
    eventObject->inShallowFlowingWater = FALSE;
    eventObject->inSandPile = FALSE;
    eventObject->inHotSprings = FALSE;
    EventObjectClearHeldMovement(eventObject);
}

static void SetPlayerAvatarEventObjectIdAndObjectId(u8 eventObjectId, u8 spriteId)
{
    gPlayerAvatar.eventObjectId = eventObjectId;
    gPlayerAvatar.spriteId = spriteId;
    gPlayerAvatar.gender = GetPlayerAvatarGenderByGraphicsId(gEventObjects[eventObjectId].graphicsId);
    SetPlayerAvatarExtraStateTransition(gEventObjects[eventObjectId].graphicsId, 0x20);
}

void EventObjectSetGraphicsId(struct EventObject *eventObject, u16 graphicsId)
{
    const struct EventObjectGraphicsInfo *graphicsInfo;
    struct Sprite *sprite;
    u8 paletteSlot;

    graphicsInfo = GetEventObjectGraphicsInfo(graphicsId);
    sprite = &gSprites[eventObject->spriteId];
    paletteSlot = graphicsInfo->paletteSlot;
    if (paletteSlot == 0)
    {
        PatchObjectPalette(graphicsInfo->paletteTag1, graphicsInfo->paletteSlot);
    }
    else if (paletteSlot >= 16)
    {
        paletteSlot -= 16;
        sub_808EAB0(graphicsInfo->paletteTag1, paletteSlot);
    }
    sprite->oam.shape = graphicsInfo->oam->shape;
    sprite->oam.size = graphicsInfo->oam->size;
    sprite->images = graphicsInfo->images;
    sprite->anims = graphicsInfo->anims;
    sprite->subspriteTables = graphicsInfo->subspriteTables;
    sprite->oam.paletteNum = paletteSlot;
    eventObject->inanimate = graphicsInfo->inanimate;
    eventObject->graphicsId = graphicsId;
    SetSpritePosToMapCoords(eventObject->currentCoords.x, eventObject->currentCoords.y, &sprite->pos1.x, &sprite->pos1.y);
    sprite->centerToCornerVecX = -(graphicsInfo->width >> 1);
    sprite->centerToCornerVecY = -(graphicsInfo->height >> 1);
    sprite->pos1.x += 8;
    sprite->pos1.y += 16 + sprite->centerToCornerVecY;
    if (eventObject->trackedByCamera)
    {
        CameraObjectReset1();
    }
}

void EventObjectSetGraphicsIdByLocalIdAndMap(u8 localId, u8 mapNum, u8 mapGroup, u16 graphicsId)
{
    u8 eventObjectId;

    if (!TryGetEventObjectIdByLocalIdAndMap(localId, mapNum, mapGroup, &eventObjectId))
    {
        EventObjectSetGraphicsId(&gEventObjects[eventObjectId], graphicsId);
    }
}

void EventObjectTurn(struct EventObject *eventObject, u8 direction)
{
    SetEventObjectDirection(eventObject, direction);
    if (!eventObject->inanimate)
    {
        StartSpriteAnim(&gSprites[eventObject->spriteId], GetFaceDirectionAnimNum(eventObject->facingDirection));
        SeekSpriteAnim(&gSprites[eventObject->spriteId], 0);
    }
}

void EventObjectTurnByLocalIdAndMap(u8 localId, u8 mapNum, u8 mapGroup, u8 direction)
{
    u8 eventObjectId;

    if (!TryGetEventObjectIdByLocalIdAndMap(localId, mapNum, mapGroup, &eventObjectId))
    {
        EventObjectTurn(&gEventObjects[eventObjectId], direction);
    }
}

void PlayerObjectTurn(struct PlayerAvatar *playerAvatar, u8 direction)
{
    EventObjectTurn(&gEventObjects[playerAvatar->eventObjectId], direction);
}

static void get_berry_tree_graphics(struct EventObject *eventObject, struct Sprite *sprite)
{
    u8 berryStage;
    u8 berryId;

    eventObject->invisible = TRUE;
    sprite->invisible = TRUE;
    berryStage = GetStageByBerryTreeId(eventObject->trainerRange_berryTreeId);
    if (berryStage != 0)
    {
        eventObject->invisible = FALSE;
        sprite->invisible = FALSE;
        berryId = GetBerryTypeByBerryTreeId(eventObject->trainerRange_berryTreeId) - 1;
        berryStage--;
        if (berryId > ITEM_TO_BERRY(LAST_BERRY_INDEX))
            berryId = 0;

        LoadEventObjectPalette(gBerryTreePaletteTagTablePointers[berryId][berryStage]);
        EventObjectSetGraphicsId(eventObject, gBerryTreeEventObjectGraphicsIdTablePointers[berryId][berryStage]);
        sprite->images = gBerryTreePicTablePointers[berryId];
        sprite->oam.paletteNum = IndexOfSpritePaletteTag(gBerryTreePaletteTagTablePointers[berryId][berryStage]);
        UpdatePaletteGammaType(sprite->oam.paletteNum, GAMMA_ALT);
        StartSpriteAnim(sprite, berryStage);
    }
}

const struct EventObjectGraphicsInfo *GetEventObjectGraphicsInfo(u16 graphicsId)
{
    u8 bard;

    if (graphicsId >= SPRITE_VAR)
    {
        graphicsId = VarGetEventObjectGraphicsId(graphicsId - SPRITE_VAR);
    }
    if (graphicsId == EVENT_OBJ_GFX_BARD)
    {
        bard = GetCurrentMauvilleOldMan();
        return gMauvilleOldManGraphicsInfoPointers[bard];
    }
    if (graphicsId >= NUM_OBJECT_GRAPHICS_INFO)
    {
        graphicsId = EVENT_OBJ_GFX_NINJA_BOY;
    }
    return gEventObjectGraphicsInfoPointers[graphicsId];
}

static void SetEventObjectDynamicGraphicsId(struct EventObject *eventObject)
{
    if (eventObject->graphicsId >= SPRITE_VAR)
    {
        eventObject->graphicsId = VarGetEventObjectGraphicsId(eventObject->graphicsId - SPRITE_VAR);
    }
}

void npc_by_local_id_and_map_set_field_1_bit_x20(u8 localId, u8 mapNum, u8 mapGroup, u8 state)
{
    u8 eventObjectId;

    if (!TryGetEventObjectIdByLocalIdAndMap(localId, mapNum, mapGroup, &eventObjectId))
    {
        gEventObjects[eventObjectId].invisible = state;
    }
}

void EventObjectGetLocalIdAndMap(struct EventObject *eventObject, void *localId, void *mapNum, void *mapGroup)
{
    *(u8*)(localId) = eventObject->localId;
    *(u8*)(mapNum) = eventObject->mapNum;
    *(u8*)(mapGroup) = eventObject->mapGroup;
}

void sub_808E75C(s16 x, s16 y)
{
    u8 eventObjectId;
    struct EventObject *eventObject;

    eventObjectId = GetEventObjectIdByXY(x, y);
    if (eventObjectId != EVENT_OBJECTS_COUNT)
    {
        eventObject = &gEventObjects[eventObjectId];
        eventObject->triggerGroundEffectsOnMove = TRUE;
    }
}

void sub_808E78C(u8 localId, u8 mapNum, u8 mapGroup, u8 subpriority)
{
    u8 eventObjectId;
    struct EventObject *eventObject;
    struct Sprite *sprite;

    if (!TryGetEventObjectIdByLocalIdAndMap(localId, mapNum, mapGroup, &eventObjectId))
    {
        eventObject = &gEventObjects[eventObjectId];
        sprite = &gSprites[eventObject->spriteId];
        eventObject->fixedPriority = TRUE;
        sprite->subpriority = subpriority;
    }
}

void sub_808E7E4(u8 localId, u8 mapNum, u8 mapGroup)
{
    u8 eventObjectId;
    struct EventObject *eventObject;

    if (!TryGetEventObjectIdByLocalIdAndMap(localId, mapNum, mapGroup, &eventObjectId))
    {
        eventObject = &gEventObjects[eventObjectId];
        eventObject->fixedPriority = FALSE;
        eventObject->triggerGroundEffectsOnMove = TRUE;
    }
}

void sub_808E82C(u8 localId, u8 mapNum, u8 mapGroup, s16 x, s16 y)
{
    u8 eventObjectId;
    struct Sprite *sprite;

    if (!TryGetEventObjectIdByLocalIdAndMap(localId, mapNum, mapGroup, &eventObjectId))
    {
        sprite = &gSprites[gEventObjects[eventObjectId].spriteId];
        sprite->pos2.x = x;
        sprite->pos2.y = y;
    }
}

void FreeAndReserveObjectSpritePalettes(void)
{
    FreeAllSpritePalettes();
    gReservedSpritePaletteCount = 12;
}

void LoadEventObjectPalette(u16 paletteTag)
{
    u16 i = FindEventObjectPaletteIndexByTag(paletteTag);

    if (i != EVENT_OBJ_PAL_TAG_NONE) // always true
    {
        sub_808E8F4(&sEventObjectSpritePalettes[i]);
    }
}

void Unused_LoadEventObjectPaletteSet(u16 *paletteTags)
{
    u8 i;

    for (i = 0; paletteTags[i] != EVENT_OBJ_PAL_TAG_NONE; i++)
    {
        LoadEventObjectPalette(paletteTags[i]);
    }
}

static u8 sub_808E8F4(const struct SpritePalette *spritePalette)
{
    if (IndexOfSpritePaletteTag(spritePalette->tag) != 0xFF)
    {
        return 0xFF;
    }
    return LoadSpritePalette(spritePalette);
}

void PatchObjectPalette(u16 paletteTag, u8 paletteSlot)
{
    u16 paletteIndex = FindEventObjectPaletteIndexByTag(paletteTag);

    LoadPalette(sEventObjectSpritePalettes[paletteIndex].data, 16 * paletteSlot + 0x100, 0x20);
}

void PatchObjectPaletteRange(const u16 *paletteTags, u8 minSlot, u8 maxSlot)
{
    while (minSlot < maxSlot)
    {
        PatchObjectPalette(*paletteTags, minSlot);
        paletteTags++;
        minSlot++;
    }
}

static u16 FindEventObjectPaletteIndexByTag(u16 tag)
{
    u16 i;

    for (i = 0; sEventObjectSpritePalettes[i].tag != EVENT_OBJ_PAL_TAG_NONE; i++)
    {
        if (sEventObjectSpritePalettes[i].tag == tag)
        {
            return i;
        }
    }
    return 0xFF;
}

static void sub_808EAB0(u16 tag, u8 slot)
{
    PatchObjectPalette(tag, slot);
}

void unref_sub_808EAC4(struct EventObject *eventObject, s16 x, s16 y)
{
    eventObject->previousCoords.x = eventObject->currentCoords.x;
    eventObject->previousCoords.y = eventObject->currentCoords.y;
    eventObject->currentCoords.x += x;
    eventObject->currentCoords.y += y;
}

void ShiftEventObjectCoords(struct EventObject *eventObject, s16 x, s16 y)
{
    eventObject->previousCoords.x = eventObject->currentCoords.x;
    eventObject->previousCoords.y = eventObject->currentCoords.y;
    eventObject->currentCoords.x = x;
    eventObject->currentCoords.y = y;
}

static void SetEventObjectCoords(struct EventObject *eventObject, s16 x, s16 y)
{
    eventObject->previousCoords.x = x;
    eventObject->previousCoords.y = y;
    eventObject->currentCoords.x = x;
    eventObject->currentCoords.y = y;
}

void MoveEventObjectToMapCoords(struct EventObject *eventObject, s16 x, s16 y)
{
    struct Sprite *sprite;
    const struct EventObjectGraphicsInfo *graphicsInfo;

    sprite = &gSprites[eventObject->spriteId];
    graphicsInfo = GetEventObjectGraphicsInfo(eventObject->graphicsId);
    SetEventObjectCoords(eventObject, x, y);
    SetSpritePosToMapCoords(eventObject->currentCoords.x, eventObject->currentCoords.y, &sprite->pos1.x, &sprite->pos1.y);
    sprite->centerToCornerVecX = -(graphicsInfo->width >> 1);
    sprite->centerToCornerVecY = -(graphicsInfo->height >> 1);
    sprite->pos1.x += 8;
    sprite->pos1.y += 16 + sprite->centerToCornerVecY;
    sub_808E38C(eventObject);
    if (eventObject->trackedByCamera)
        CameraObjectReset1();
}

void TryMoveEventObjectToMapCoords(u8 localId, u8 mapNum, u8 mapGroup, s16 x, s16 y)
{
    u8 eventObjectId;
    if (!TryGetEventObjectIdByLocalIdAndMap(localId, mapNum, mapGroup, &eventObjectId))
    {
        x += 7;
        y += 7;
        MoveEventObjectToMapCoords(&gEventObjects[eventObjectId], x, y);
    }
}

void ShiftStillEventObjectCoords(struct EventObject *eventObject)
{
    ShiftEventObjectCoords(eventObject, eventObject->currentCoords.x, eventObject->currentCoords.y);
}

void UpdateEventObjectCoordsForCameraUpdate(void)
{
    u8 i;
    s16 dx;
    s16 dy;

    if (gCamera.active)
    {
        dx = gCamera.x;
        dy = gCamera.y;
        for (i = 0; i < EVENT_OBJECTS_COUNT; i++)
        {
            if (gEventObjects[i].active)
            {
                gEventObjects[i].initialCoords.x -= dx;
                gEventObjects[i].initialCoords.y -= dy;
                gEventObjects[i].currentCoords.x -= dx;
                gEventObjects[i].currentCoords.y -= dy;
                gEventObjects[i].previousCoords.x -= dx;
                gEventObjects[i].previousCoords.y -= dy;
            }
        }
    }
}

u8 GetEventObjectIdByXYZ(u16 x, u16 y, u8 z)
{
    u8 i;

    for (i = 0; i < EVENT_OBJECTS_COUNT; i++)
    {
        if (gEventObjects[i].active)
        {
            if (gEventObjects[i].currentCoords.x == x && gEventObjects[i].currentCoords.y == y && EventObjectDoesZCoordMatch(&gEventObjects[i], z))
            {
                return i;
            }
        }
    }
    return EVENT_OBJECTS_COUNT;
}

static bool8 EventObjectDoesZCoordMatch(struct EventObject *eventObject, u8 z)
{
    if (eventObject->currentElevation != 0 && z != 0 && eventObject->currentElevation != z)
    {
        return FALSE;
    }
    return TRUE;
}

void UpdateEventObjectsForCameraUpdate(s16 x, s16 y)
{
    UpdateEventObjectCoordsForCameraUpdate();
    TrySpawnEventObjects(x, y);
    RemoveEventObjectsOutsideView();
}

u8 AddCameraObject(u8 linkedSpriteId)
{
    u8 spriteId = CreateSprite(&gCameraSpriteTemplate, 0, 0, 4);

    gSprites[spriteId].invisible = TRUE;
    gSprites[spriteId].data[0] = linkedSpriteId;
    return spriteId;
}

static void ObjectCB_CameraObject(struct Sprite *sprite)
{
    void (*callbacks[ARRAY_COUNT(gCameraObjectFuncs)])(struct Sprite *);

    memcpy(callbacks, gCameraObjectFuncs, sizeof gCameraObjectFuncs);
    callbacks[sprite->data[1]](sprite);
}

static void CameraObject_0(struct Sprite *sprite)
{
    sprite->pos1.x = gSprites[sprite->data[0]].pos1.x;
    sprite->pos1.y = gSprites[sprite->data[0]].pos1.y;
    sprite->invisible = TRUE;
    sprite->data[1] = 1;
    CameraObject_1(sprite);
}

static void CameraObject_1(struct Sprite *sprite)
{
    s16 x = gSprites[sprite->data[0]].pos1.x;
    s16 y = gSprites[sprite->data[0]].pos1.y;

    sprite->data[2] = x - sprite->pos1.x;
    sprite->data[3] = y - sprite->pos1.y;
    sprite->pos1.x = x;
    sprite->pos1.y = y;
}

static void CameraObject_2(struct Sprite *sprite)
{
    sprite->pos1.x = gSprites[sprite->data[0]].pos1.x;
    sprite->pos1.y = gSprites[sprite->data[0]].pos1.y;
    sprite->data[2] = 0;
    sprite->data[3] = 0;
}

static struct Sprite *FindCameraObject(void)
{
    u8 i;

    for (i = 0; i < MAX_SPRITES; i++)
    {
        if (gSprites[i].inUse && gSprites[i].callback == ObjectCB_CameraObject)
        {
            return &gSprites[i];
        }
    }
    return NULL;
}

void CameraObjectReset1(void)
{
    struct Sprite *cameraObject;

    cameraObject = FindCameraObject();
    if (cameraObject != NULL)
    {
        cameraObject->data[1] = 0;
        cameraObject->callback(cameraObject);
    }
}

void CameraObjectSetFollowedObjectId(u8 objectId)
{
    struct Sprite *cameraObject;

    cameraObject = FindCameraObject();
    if (cameraObject != NULL)
    {
        cameraObject->data[0] = objectId;
        CameraObjectReset1();
    }
}

u8 CameraObjectGetFollowedObjectId(void)
{
    struct Sprite *cameraObject;

    cameraObject = FindCameraObject();
    if (cameraObject == NULL)
    {
        return MAX_SPRITES;
    }
    return cameraObject->data[0];
}

void CameraObjectReset2(void)
{
    FindCameraObject()->data[1] = 2;
}

u8 CopySprite(struct Sprite *sprite, s16 x, s16 y, u8 subpriority)
{
    u8 i;

    for (i = 0; i < MAX_SPRITES; i++)
    {
        if (!gSprites[i].inUse)
        {
            gSprites[i] = *sprite;
            gSprites[i].pos1.x = x;
            gSprites[i].pos1.y = y;
            gSprites[i].subpriority = subpriority;
            break;
        }
    }
    return i;
}

u8 CreateCopySpriteAt(struct Sprite *sprite, s16 x, s16 y, u8 subpriority)
{
    s16 i;

    for (i = MAX_SPRITES - 1; i > -1; i--)
    {
        if (!gSprites[i].inUse)
        {
            gSprites[i] = *sprite;
            gSprites[i].pos1.x = x;
            gSprites[i].pos1.y = y;
            gSprites[i].subpriority = subpriority;
            return i;
        }
    }
    return MAX_SPRITES;
}

void SetEventObjectDirection(struct EventObject *eventObject, u8 direction)
{
    s8 d2;
    eventObject->previousMovementDirection = eventObject->facingDirection;
    if (!eventObject->facingDirectionLocked)
    {
        d2 = direction;
        eventObject->facingDirection = d2;
    }
    eventObject->movementDirection = direction;
}

static const u8 *GetEventObjectScriptPointerByLocalIdAndMap(u8 localId, u8 mapNum, u8 mapGroup)
{
    return GetEventObjectTemplateByLocalIdAndMap(localId, mapNum, mapGroup)->script;
}

const u8 *GetEventObjectScriptPointerByEventObjectId(u8 eventObjectId)
{
    return GetEventObjectScriptPointerByLocalIdAndMap(gEventObjects[eventObjectId].localId, gEventObjects[eventObjectId].mapNum, gEventObjects[eventObjectId].mapGroup);
}

static u16 GetEventObjectFlagIdByLocalIdAndMap(u8 localId, u8 mapNum, u8 mapGroup)
{
    return GetEventObjectTemplateByLocalIdAndMap(localId, mapNum, mapGroup)->flagId;
}

static u16 GetEventObjectFlagIdByEventObjectId(u8 eventObjectId)
{
    return GetEventObjectFlagIdByLocalIdAndMap(gEventObjects[eventObjectId].localId, gEventObjects[eventObjectId].mapNum, gEventObjects[eventObjectId].mapGroup);
}

u8 sub_808F080(u8 localId, u8 mapNum, u8 mapGroup)
{
    u8 eventObjectId;

    if (TryGetEventObjectIdByLocalIdAndMap(localId, mapNum, mapGroup, &eventObjectId))
    {
        return 0xFF;
    }
    return gEventObjects[eventObjectId].trainerType;
}

u8 sub_808F0BC(u8 eventObjectId)
{
    return gEventObjects[eventObjectId].trainerType;
}

u8 sub_808F0D4(u8 localId, u8 mapNum, u8 mapGroup)
{
    u8 eventObjectId;

    if (TryGetEventObjectIdByLocalIdAndMap(localId, mapNum, mapGroup, &eventObjectId))
    {
        return 0xFF;
    }
    return gEventObjects[eventObjectId].trainerRange_berryTreeId;
}

u8 EventObjectGetBerryTreeId(u8 eventObjectId)
{
    return gEventObjects[eventObjectId].trainerRange_berryTreeId;
}

static struct EventObjectTemplate *GetEventObjectTemplateByLocalIdAndMap(u8 localId, u8 mapNum, u8 mapGroup)
{
    struct EventObjectTemplate *templates;
    const struct MapHeader *mapHeader;
    u8 count;

    if (gSaveBlock1Ptr->location.mapNum == mapNum && gSaveBlock1Ptr->location.mapGroup == mapGroup)
    {
        templates = gSaveBlock1Ptr->eventObjectTemplates;
        count = gMapHeader.events->eventObjectCount;
    }
    else
    {
        mapHeader = Overworld_GetMapHeaderByGroupAndId(mapGroup, mapNum);
        templates = mapHeader->events->eventObjects;
        count = mapHeader->events->eventObjectCount;
    }
    return FindEventObjectTemplateByLocalId(localId, templates, count);
}

static struct EventObjectTemplate *FindEventObjectTemplateByLocalId(u8 localId, struct EventObjectTemplate *templates, u8 count)
{
    u8 i;

    for (i = 0; i < count; i++)
    {
        if (templates[i].localId == localId)
        {
            return &templates[i];
        }
    }
    return NULL;
}

struct EventObjectTemplate *GetBaseTemplateForEventObject(const struct EventObject *eventObject)
{
    int i;

    if (eventObject->mapNum != gSaveBlock1Ptr->location.mapNum || eventObject->mapGroup != gSaveBlock1Ptr->location.mapGroup)
    {
        return NULL;
    }
    for (i = 0; i < EVENT_OBJECT_TEMPLATES_COUNT; i++)
    {
        if (eventObject->localId == gSaveBlock1Ptr->eventObjectTemplates[i].localId)
        {
            return &gSaveBlock1Ptr->eventObjectTemplates[i];
        }
    }
    return NULL;
}

void OverrideTemplateCoordsForEventObject(const struct EventObject *eventObject)
{
    struct EventObjectTemplate *eventObjectTemplate;

    eventObjectTemplate = GetBaseTemplateForEventObject(eventObject);
    if (eventObjectTemplate != NULL)
    {
        eventObjectTemplate->x = eventObject->currentCoords.x - 7;
        eventObjectTemplate->y = eventObject->currentCoords.y - 7;
    }
}

static void OverrideEventObjectTemplateScript(const struct EventObject *eventObject, const u8 *script)
{
    struct EventObjectTemplate *eventObjectTemplate;

    eventObjectTemplate = GetBaseTemplateForEventObject(eventObject);
    if (eventObjectTemplate)
        eventObjectTemplate->script = script;
}

void TryOverrideTemplateCoordsForEventObject(const struct EventObject *eventObject, u8 movementType)
{
    struct EventObjectTemplate *eventObjectTemplate;

    eventObjectTemplate = GetBaseTemplateForEventObject(eventObject);
    if (eventObjectTemplate != NULL)
    {
        eventObjectTemplate->movementType = movementType;
    }
}

void TryOverrideEventObjectTemplateCoords(u8 localId, u8 mapNum, u8 mapGroup)
{
    u8 eventObjectId;
    if (!TryGetEventObjectIdByLocalIdAndMap(localId, mapNum, mapGroup, &eventObjectId))
        OverrideTemplateCoordsForEventObject(&gEventObjects[eventObjectId]);
}

void OverrideSecretBaseDecorationSpriteScript(u8 localId, u8 mapNum, u8 mapGroup, u8 decorationCategory)
{
    u8 eventObjectId;
    if (!TryGetEventObjectIdByLocalIdAndMap(localId, mapNum, mapGroup, &eventObjectId))
    {
        switch (decorationCategory)
        {
        case DECORCAT_DOLL:
            OverrideEventObjectTemplateScript(&gEventObjects[eventObjectId], SecretBase_EventScript_DollInteract);
            break;
        case DECORCAT_CUSHION:
            OverrideEventObjectTemplateScript(&gEventObjects[eventObjectId], SecretBase_EventScript_CushionInteract);
            break;
        }
    }
}

movement_type_empty_callback(MovementType_None)
movement_type_def(MovementType_WanderAround, gMovementTypeFuncs_WanderAround)

bool8 MovementType_WanderAround_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    ClearEventObjectMovement(eventObject, sprite);
    sprite->data[1] = 1;
    return TRUE;
}

bool8 MovementType_WanderAround_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    EventObjectSetSingleMovement(eventObject, sprite, GetFaceDirectionMovementAction(eventObject->facingDirection));
    sprite->data[1] = 2;
    return TRUE;
}

bool8 MovementType_WanderAround_Step2(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (!EventObjectExecSingleMovementAction(eventObject, sprite))
    {
        return FALSE;
    }
    SetMovementDelay(sprite, gMovementDelaysMedium[Random() & 3]);
    sprite->data[1] = 3;
    return TRUE;
}

bool8 MovementType_WanderAround_Step3(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (WaitForMovementDelay(sprite))
    {
        sprite->data[1] = 4;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementType_WanderAround_Step4(struct EventObject *eventObject, struct Sprite *sprite)
{
    u8 directions[4];
    u8 chosenDirection;

    memcpy(directions, gStandardDirections, sizeof directions);
    chosenDirection = directions[Random() & 3];
    SetEventObjectDirection(eventObject, chosenDirection);
    sprite->data[1] = 5;
    if (GetCollisionInDirection(eventObject, chosenDirection))
    {
        sprite->data[1] = 1;
    }
    return TRUE;
}

bool8 MovementType_WanderAround_Step5(struct EventObject *eventObject, struct Sprite *sprite)
{
    EventObjectSetSingleMovement(eventObject, sprite, GetWalkNormalMovementAction(eventObject->movementDirection));
    eventObject->singleMovementActive = 1;
    sprite->data[1] = 6;
    return TRUE;
}

bool8 MovementType_WanderAround_Step6(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (EventObjectExecSingleMovementAction(eventObject, sprite))
    {
        eventObject->singleMovementActive = 0;
        sprite->data[1] = 1;
    }
    return FALSE;
}

bool8 EventObjectIsTrainerAndCloseToPlayer(struct EventObject *eventObject)
{
    s16 playerX;
    s16 playerY;
    s16 objX;
    s16 objY;
    s16 minX;
    s16 maxX;
    s16 minY;
    s16 maxY;

    if (!TestPlayerAvatarFlags(PLAYER_AVATAR_FLAG_DASH))
    {
        return FALSE;
    }
    if (eventObject->trainerType != 1 && eventObject->trainerType != 3)
    {
        return FALSE;
    }
    PlayerGetDestCoords(&playerX, &playerY);
    objX = eventObject->currentCoords.x;
    objY = eventObject->currentCoords.y;
    minX = objX - eventObject->trainerRange_berryTreeId;
    minY = objY - eventObject->trainerRange_berryTreeId;
    maxX = objX + eventObject->trainerRange_berryTreeId;
    maxY = objY + eventObject->trainerRange_berryTreeId;
    if (minX > playerX || maxX < playerX || minY > playerY || maxY < playerY)
    {
        return FALSE;
    }
    return TRUE;
}

u8 GetVectorDirection(s16 dx, s16 dy, s16 absdx, s16 absdy)
{
    u8 direction;

    if (absdx > absdy)
    {
        direction = DIR_EAST;
        if (dx < 0)
        {
            direction = DIR_WEST;
        }
    }
    else
    {
        direction = DIR_SOUTH;
        if (dy < 0)
        {
            direction = DIR_NORTH;
        }
    }
    return direction;
}

u8 GetLimitedVectorDirection_SouthNorth(s16 dx, s16 dy, s16 absdx, s16 absdy)
{
    u8 direction;

    direction = DIR_SOUTH;
    if (dy < 0)
    {
        direction = DIR_NORTH;
    }
    return direction;
}

u8 GetLimitedVectorDirection_WestEast(s16 dx, s16 dy, s16 absdx, s16 absdy)
{
    u8 direction;

    direction = DIR_EAST;
    if (dx < 0)
    {
        direction = DIR_WEST;
    }
    return direction;
}

u8 GetLimitedVectorDirection_WestNorth(s16 dx, s16 dy, s16 absdx, s16 absdy)
{
    u8 direction;

    direction = GetVectorDirection(dx, dy, absdx, absdy);
    if (direction == DIR_SOUTH)
    {
        direction = GetLimitedVectorDirection_WestEast(dx, dy, absdx, absdy);
        if (direction == DIR_EAST)
        {
            direction = DIR_NORTH;
        }
    }
    else if (direction == DIR_EAST)
    {
        direction = GetLimitedVectorDirection_SouthNorth(dx, dy, absdx, absdy);
        if (direction == DIR_SOUTH)
        {
            direction = DIR_NORTH;
        }
    }
    return direction;
}

u8 GetLimitedVectorDirection_EastNorth(s16 dx, s16 dy, s16 absdx, s16 absdy)
{
    u8 direction;

    direction = GetVectorDirection(dx, dy, absdx, absdy);
    if (direction == DIR_SOUTH)
    {
        direction = GetLimitedVectorDirection_WestEast(dx, dy, absdx, absdy);
        if (direction == DIR_WEST)
        {
            direction = DIR_NORTH;
        }
    }
    else if (direction == DIR_WEST)
    {
        direction = GetLimitedVectorDirection_SouthNorth(dx, dy, absdx, absdy);
        if (direction == DIR_SOUTH)
        {
            direction = DIR_NORTH;
        }
    }
    return direction;
}

u8 GetLimitedVectorDirection_WestSouth(s16 dx, s16 dy, s16 absdx, s16 absdy)
{
    u8 direction;

    direction = GetVectorDirection(dx, dy, absdx, absdy);
    if (direction == DIR_NORTH)
    {
        direction = GetLimitedVectorDirection_WestEast(dx, dy, absdx, absdy);
        if (direction == DIR_EAST)
        {
            direction = DIR_SOUTH;
        }
    }
    else if (direction == DIR_EAST)
    {
        direction = GetLimitedVectorDirection_SouthNorth(dx, dy, absdx, absdy);
        if (direction == DIR_NORTH)
        {
            direction = DIR_SOUTH;
        }
    }
    return direction;
}

u8 GetLimitedVectorDirection_EastSouth(s16 dx, s16 dy, s16 absdx, s16 absdy)
{
    u8 direction;

    direction = GetVectorDirection(dx, dy, absdx, absdy);
    if (direction == DIR_NORTH)
    {
        direction = GetLimitedVectorDirection_WestEast(dx, dy, absdx, absdy);
        if (direction == DIR_WEST)
        {
            direction = DIR_SOUTH;
        }
    }
    else if (direction == DIR_WEST)
    {
        direction = GetLimitedVectorDirection_SouthNorth(dx, dy, absdx, absdy);
        if (direction == DIR_NORTH)
        {
            direction = DIR_SOUTH;
        }
    }
    return direction;
}

u8 GetLimitedVectorDirection_SouthNorthWest(s16 dx, s16 dy, s16 absdx, s16 absdy)
{
    u8 direction;

    direction = GetVectorDirection(dx, dy, absdx, absdy);
    if (direction == DIR_EAST)
    {
        direction = GetLimitedVectorDirection_SouthNorth(dx, dy, absdx, absdy);
    }
    return direction;
}

u8 GetLimitedVectorDirection_SouthNorthEast(s16 dx, s16 dy, s16 absdx, s16 absdy)
{
    u8 direction;

    direction = GetVectorDirection(dx, dy, absdx, absdy);
    if (direction == DIR_WEST)
    {
        direction = GetLimitedVectorDirection_SouthNorth(dx, dy, absdx, absdy);
    }
    return direction;
}

u8 GetLimitedVectorDirection_NorthWestEast(s16 dx, s16 dy, s16 absdx, s16 absdy)
{
    u8 direction;

    direction = GetVectorDirection(dx, dy, absdx, absdy);
    if (direction == DIR_SOUTH)
    {
        direction = GetLimitedVectorDirection_WestEast(dx, dy, absdx, absdy);
    }
    return direction;
}

u8 GetLimitedVectorDirection_SouthWestEast(s16 dx, s16 dy, s16 absdx, s16 absdy)
{
    u8 direction;

    direction = GetVectorDirection(dx, dy, absdx, absdy);
    if (direction == DIR_NORTH)
    {
        direction = GetLimitedVectorDirection_WestEast(dx, dy, absdx, absdy);
    }
    return direction;
}

u8 TryGetTrainerEncounterDirection(struct EventObject *eventObject, u8 movementType)
{
    s16 dx, dy;
    s16 absdx, absdy;

    if (!EventObjectIsTrainerAndCloseToPlayer(eventObject))
    {
        return 0;
    }
    PlayerGetDestCoords(&dx, &dy);
    dx -= eventObject->currentCoords.x;
    dy -= eventObject->currentCoords.y;
    absdx = dx;
    absdy = dy;
    if (absdx < 0)
    {
        absdx = -absdx;
    }
    if (absdy < 0)
    {
        absdy = -absdy;
    }
    return gGetVectorDirectionFuncs[movementType](dx, dy, absdx, absdy);
}

movement_type_def(MovementType_LookAround, gMovementTypeFuncs_LookAround)

bool8 MovementType_LookAround_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    ClearEventObjectMovement(eventObject, sprite);
    sprite->data[1] = 1;
    return TRUE;
}

bool8 MovementType_LookAround_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    EventObjectSetSingleMovement(eventObject, sprite, GetFaceDirectionMovementAction(eventObject->facingDirection));
    sprite->data[1] = 2;
    return TRUE;
}

bool8 MovementType_LookAround_Step2(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (EventObjectExecSingleMovementAction(eventObject, sprite))
    {
        SetMovementDelay(sprite, gMovementDelaysMedium[Random() & 3]);
        eventObject->singleMovementActive = 0;
        sprite->data[1] = 3;
    }
    return FALSE;
}

bool8 MovementType_LookAround_Step3(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (WaitForMovementDelay(sprite) || EventObjectIsTrainerAndCloseToPlayer(eventObject))
    {
        sprite->data[1] = 4;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementType_LookAround_Step4(struct EventObject *eventObject, struct Sprite *sprite)
{
    u8 direction;
    u8 directions[4];
    memcpy(directions, gStandardDirections, sizeof directions);
    direction = TryGetTrainerEncounterDirection(eventObject, RUNFOLLOW_ANY);
    if (direction == DIR_NONE)
        direction = directions[Random() & 3];

    SetEventObjectDirection(eventObject, direction);
    sprite->data[1] = 1;
    return TRUE;
}

movement_type_def(MovementType_WanderUpAndDown, gMovementTypeFuncs_WanderUpAndDown)

bool8 MovementType_WanderUpAndDown_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    ClearEventObjectMovement(eventObject, sprite);
    sprite->data[1] = 1;
    return TRUE;
}

bool8 MovementType_WanderUpAndDown_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    EventObjectSetSingleMovement(eventObject, sprite, GetFaceDirectionMovementAction(eventObject->facingDirection));
    sprite->data[1] = 2;
    return TRUE;
}

bool8 MovementType_WanderUpAndDown_Step2(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (!EventObjectExecSingleMovementAction(eventObject, sprite))
    {
        return FALSE;
    }
    SetMovementDelay(sprite, gMovementDelaysMedium[Random() & 3]);
    sprite->data[1] = 3;
    return TRUE;
}

bool8 MovementType_WanderUpAndDown_Step3(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (WaitForMovementDelay(sprite))
    {
        sprite->data[1] = 4;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementType_WanderUpAndDown_Step4(struct EventObject *eventObject, struct Sprite *sprite)
{
    u8 direction;
    u8 directions[2];
    memcpy(directions, gUpAndDownDirections, sizeof directions);
    direction = directions[Random() & 1];
    SetEventObjectDirection(eventObject, direction);
    sprite->data[1] = 5;
    if (GetCollisionInDirection(eventObject, direction))
    {
        sprite->data[1] = 1;
    }
    return TRUE;
}

bool8 MovementType_WanderUpAndDown_Step5(struct EventObject *eventObject, struct Sprite *sprite)
{
    EventObjectSetSingleMovement(eventObject, sprite, GetWalkNormalMovementAction(eventObject->movementDirection));
    eventObject->singleMovementActive = 1;
    sprite->data[1] = 6;
    return TRUE;
}

bool8 MovementType_WanderUpAndDown_Step6(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (EventObjectExecSingleMovementAction(eventObject, sprite))
    {
        eventObject->singleMovementActive = 0;
        sprite->data[1] = 1;
    }
    return FALSE;
}

movement_type_def(MovementType_WanderLeftAndRight, gMovementTypeFuncs_WanderLeftAndRight)

bool8 MovementType_WanderLeftAndRight_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    ClearEventObjectMovement(eventObject, sprite);
    sprite->data[1] = 1;
    return TRUE;
}

bool8 MovementType_WanderLeftAndRight_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    EventObjectSetSingleMovement(eventObject, sprite, GetFaceDirectionMovementAction(eventObject->facingDirection));
    sprite->data[1] = 2;
    return TRUE;
}

bool8 MovementType_WanderLeftAndRight_Step2(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (!EventObjectExecSingleMovementAction(eventObject, sprite))
    {
        return FALSE;
    }
    SetMovementDelay(sprite, gMovementDelaysMedium[Random() & 3]);
    sprite->data[1] = 3;
    return TRUE;
}

bool8 MovementType_WanderLeftAndRight_Step3(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (WaitForMovementDelay(sprite))
    {
        sprite->data[1] = 4;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementType_WanderLeftAndRight_Step4(struct EventObject *eventObject, struct Sprite *sprite)
{
    u8 direction;
    u8 directions[2];
    memcpy(directions, gLeftAndRightDirections, sizeof directions);
    direction = directions[Random() & 1];
    SetEventObjectDirection(eventObject, direction);
    sprite->data[1] = 5;
    if (GetCollisionInDirection(eventObject, direction))
    {
        sprite->data[1] = 1;
    }
    return TRUE;
}

bool8 MovementType_WanderLeftAndRight_Step5(struct EventObject *eventObject, struct Sprite *sprite)
{
    EventObjectSetSingleMovement(eventObject, sprite, GetWalkNormalMovementAction(eventObject->movementDirection));
    eventObject->singleMovementActive = 1;
    sprite->data[1] = 6;
    return TRUE;
}

bool8 MovementType_WanderLeftAndRight_Step6(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (EventObjectExecSingleMovementAction(eventObject, sprite))
    {
        eventObject->singleMovementActive = 0;
        sprite->data[1] = 1;
    }
    return FALSE;
}

movement_type_def(MovementType_FaceDirection, gMovementTypeFuncs_FaceDirection)

bool8 MovementType_FaceDirection_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    ClearEventObjectMovement(eventObject, sprite);
    EventObjectSetSingleMovement(eventObject, sprite, GetFaceDirectionMovementAction(eventObject->facingDirection));
    sprite->data[1] = 1;
    return TRUE;
}

bool8 MovementType_FaceDirection_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (EventObjectExecSingleMovementAction(eventObject, sprite))
    {
        sprite->data[1] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementType_FaceDirection_Step2(struct EventObject *eventObject, struct Sprite *sprite)
{
    eventObject->singleMovementActive = 0;
    return FALSE;
}

static bool8 EventObjectCB2_BerryTree(struct EventObject *eventObject, struct Sprite *sprite);
extern bool8 (*const gMovementTypeFuncs_BerryTreeGrowth[])(struct EventObject *eventObject, struct Sprite *sprite);
void MovementType_BerryTreeGrowth(struct Sprite *sprite)
{
    struct EventObject *eventObject;

    eventObject = &gEventObjects[sprite->data[0]];
    if (!(sprite->data[7] & 1))
    {
        get_berry_tree_graphics(eventObject, sprite);
        sprite->data[7] |= 1;
    }
    UpdateEventObjectCurrentMovement(eventObject, sprite, EventObjectCB2_BerryTree);
}
static bool8 EventObjectCB2_BerryTree(struct EventObject *eventObject, struct Sprite *sprite)
{
    return gMovementTypeFuncs_BerryTreeGrowth[sprite->data[1]](eventObject, sprite);
}

bool8 MovementType_BerryTreeGrowth_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    u8 berryStage;
    ClearEventObjectMovement(eventObject, sprite);
    eventObject->invisible = TRUE;
    sprite->invisible = TRUE;
    berryStage = GetStageByBerryTreeId(eventObject->trainerRange_berryTreeId);
    if (berryStage == 0)
    {
        if (!(sprite->data[7] & 4) && sprite->animNum == 4)
        {
            gFieldEffectArguments[0] = eventObject->currentCoords.x;
            gFieldEffectArguments[1] = eventObject->currentCoords.y;
            gFieldEffectArguments[2] = sprite->subpriority - 1;
            gFieldEffectArguments[3] = sprite->oam.priority;
            FieldEffectStart(FLDEFF_BERRY_TREE_GROWTH_SPARKLE);
            sprite->animNum = berryStage;
        }
        return FALSE;
    }
    eventObject->invisible = FALSE;
    sprite->invisible = FALSE;
    berryStage --;
    if (sprite->animNum != berryStage)
    {
        sprite->data[1] = 2;
        return TRUE;
    }
    get_berry_tree_graphics(eventObject, sprite);
    EventObjectSetSingleMovement(eventObject, sprite, MOVEMENT_ACTION_START_ANIM_IN_DIRECTION);
    sprite->data[1] = 1;
    return TRUE;
}

bool8 MovementType_BerryTreeGrowth_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (EventObjectExecSingleMovementAction(eventObject, sprite))
    {
        sprite->data[1] = 0;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementType_BerryTreeGrowth_Step2(struct EventObject *eventObject, struct Sprite *sprite)
{
    eventObject->singleMovementActive = 1;
    sprite->data[1] = 3;
    sprite->data[2] = 0;
    sprite->data[7] |= 2;
    gFieldEffectArguments[0] = eventObject->currentCoords.x;
    gFieldEffectArguments[1] = eventObject->currentCoords.y;
    gFieldEffectArguments[2] = sprite->subpriority - 1;
    gFieldEffectArguments[3] = sprite->oam.priority;
    FieldEffectStart(FLDEFF_BERRY_TREE_GROWTH_SPARKLE);
    return TRUE;
}

bool8 MovementType_BerryTreeGrowth_Step3(struct EventObject *eventObject, struct Sprite *sprite)
{
    sprite->data[2]++;
    eventObject->invisible = (sprite->data[2] & 0x02) >> 1;
    sprite->animPaused = TRUE;
    if (sprite->data[2] > 64)
    {
        get_berry_tree_graphics(eventObject, sprite);
        sprite->data[1] = 4;
        sprite->data[2] = 0;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementType_BerryTreeGrowth_Step4(struct EventObject *eventObject, struct Sprite *sprite)
{
    sprite->data[2]++;
    eventObject->invisible = (sprite->data[2] & 0x02) >> 1;
    sprite->animPaused = TRUE;
    if (sprite->data[2] > 64)
    {
        sprite->data[1] = 0;
        sprite->data[7] &= ~0x0002;
        return TRUE;
    }
    return FALSE;
}

movement_type_def(MovementType_FaceDownAndUp, gMovementTypeFuncs_FaceDownAndUp)

bool8 MovementType_FaceDownAndUp_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    ClearEventObjectMovement(eventObject, sprite);
    sprite->data[1] = 1;
    return TRUE;
}

bool8 MovementType_FaceDownAndUp_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    EventObjectSetSingleMovement(eventObject, sprite, GetFaceDirectionMovementAction(eventObject->facingDirection));
    sprite->data[1] = 2;
    return TRUE;
}

bool8 MovementType_FaceDownAndUp_Step2(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (EventObjectExecSingleMovementAction(eventObject, sprite))
    {
        SetMovementDelay(sprite, gMovementDelaysMedium[Random() & 3]);
        eventObject->singleMovementActive = 0;
        sprite->data[1] = 3;
    }
    return FALSE;
}

bool8 MovementType_FaceDownAndUp_Step3(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (WaitForMovementDelay(sprite) || EventObjectIsTrainerAndCloseToPlayer(eventObject))
    {
        sprite->data[1] = 4;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementType_FaceDownAndUp_Step4(struct EventObject *eventObject, struct Sprite *sprite)
{
    u8 direction;
    u8 directions[2];
    memcpy(directions, gUpAndDownDirections, sizeof gUpAndDownDirections);
    direction = TryGetTrainerEncounterDirection(eventObject, RUNFOLLOW_NORTH_SOUTH);
    if (direction == 0)
    {
        direction = directions[Random() & 1];
    }
    SetEventObjectDirection(eventObject, direction);
    sprite->data[1] = 1;
    return TRUE;
}

movement_type_def(MovementType_FaceLeftAndRight, gMovementTypeFuncs_FaceLeftAndRight)

bool8 MovementType_FaceLeftAndRight_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    ClearEventObjectMovement(eventObject, sprite);
    sprite->data[1] = 1;
    return TRUE;
}

bool8 MovementType_FaceLeftAndRight_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    EventObjectSetSingleMovement(eventObject, sprite, GetFaceDirectionMovementAction(eventObject->facingDirection));
    sprite->data[1] = 2;
    return TRUE;
}

bool8 MovementType_FaceLeftAndRight_Step2(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (EventObjectExecSingleMovementAction(eventObject, sprite))
    {
        SetMovementDelay(sprite, gMovementDelaysMedium[Random() & 3]);
        eventObject->singleMovementActive = 0;
        sprite->data[1] = 3;
    }
    return FALSE;
}

bool8 MovementType_FaceLeftAndRight_Step3(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (WaitForMovementDelay(sprite) || EventObjectIsTrainerAndCloseToPlayer(eventObject))
    {
        sprite->data[1] = 4;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementType_FaceLeftAndRight_Step4(struct EventObject *eventObject, struct Sprite *sprite)
{
    u8 direction;
    u8 directions[2];
    memcpy(directions, gLeftAndRightDirections, sizeof gLeftAndRightDirections);
    direction = TryGetTrainerEncounterDirection(eventObject, RUNFOLLOW_EAST_WEST);
    if (direction == 0)
    {
        direction = directions[Random() & 1];
    }
    SetEventObjectDirection(eventObject, direction);
    sprite->data[1] = 1;
    return TRUE;
}

movement_type_def(MovementType_FaceUpAndLeft, gMovementTypeFuncs_FaceUpAndLeft)

bool8 MovementType_FaceUpAndLeft_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    ClearEventObjectMovement(eventObject, sprite);
    sprite->data[1] = 1;
    return TRUE;
}

bool8 MovementType_FaceUpAndLeft_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    EventObjectSetSingleMovement(eventObject, sprite, GetFaceDirectionMovementAction(eventObject->facingDirection));
    sprite->data[1] = 2;
    return TRUE;
}

bool8 MovementType_FaceUpAndLeft_Step2(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (EventObjectExecSingleMovementAction(eventObject, sprite))
    {
        SetMovementDelay(sprite, gMovementDelaysShort[Random() & 3]);
        eventObject->singleMovementActive = 0;
        sprite->data[1] = 3;
    }
    return FALSE;
}

bool8 MovementType_FaceUpAndLeft_Step3(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (WaitForMovementDelay(sprite) || EventObjectIsTrainerAndCloseToPlayer(eventObject))
    {
        sprite->data[1] = 4;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementType_FaceUpAndLeft_Step4(struct EventObject *eventObject, struct Sprite *sprite)
{
    u8 direction;
    u8 directions[2];
    memcpy(directions, gUpAndLeftDirections, sizeof gUpAndLeftDirections);
    direction = TryGetTrainerEncounterDirection(eventObject, RUNFOLLOW_NORTH_WEST);
    if (direction == 0)
    {
        direction = directions[Random() & 1];
    }
    SetEventObjectDirection(eventObject, direction);
    sprite->data[1] = 1;
    return TRUE;
}

movement_type_def(MovementType_FaceUpAndRight, gMovementTypeFuncs_FaceUpAndRight)

bool8 MovementType_FaceUpAndRight_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    ClearEventObjectMovement(eventObject, sprite);
    sprite->data[1] = 1;
    return TRUE;
}

bool8 MovementType_FaceUpAndRight_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    EventObjectSetSingleMovement(eventObject, sprite, GetFaceDirectionMovementAction(eventObject->facingDirection));
    sprite->data[1] = 2;
    return TRUE;
}

bool8 MovementType_FaceUpAndRight_Step2(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (EventObjectExecSingleMovementAction(eventObject, sprite))
    {
        SetMovementDelay(sprite, gMovementDelaysShort[Random() & 3]);
        eventObject->singleMovementActive = 0;
        sprite->data[1] = 3;
    }
    return FALSE;
}

bool8 MovementType_FaceUpAndRight_Step3(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (WaitForMovementDelay(sprite) || EventObjectIsTrainerAndCloseToPlayer(eventObject))
    {
        sprite->data[1] = 4;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementType_FaceUpAndRight_Step4(struct EventObject *eventObject, struct Sprite *sprite)
{
    u8 direction;
    u8 directions[2];
    memcpy(directions, gUpAndRightDirections, sizeof gUpAndRightDirections);
    direction = TryGetTrainerEncounterDirection(eventObject, RUNFOLLOW_NORTH_EAST);
    if (direction == 0)
    {
        direction = directions[Random() & 1];
    }
    SetEventObjectDirection(eventObject, direction);
    sprite->data[1] = 1;
    return TRUE;
}

movement_type_def(MovementType_FaceDownAndLeft, gMovementTypeFuncs_FaceDownAndLeft)

bool8 MovementType_FaceDownAndLeft_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    ClearEventObjectMovement(eventObject, sprite);
    sprite->data[1] = 1;
    return TRUE;
}

bool8 MovementType_FaceDownAndLeft_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    EventObjectSetSingleMovement(eventObject, sprite, GetFaceDirectionMovementAction(eventObject->facingDirection));
    sprite->data[1] = 2;
    return TRUE;
}

bool8 MovementType_FaceDownAndLeft_Step2(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (EventObjectExecSingleMovementAction(eventObject, sprite))
    {
        SetMovementDelay(sprite, gMovementDelaysShort[Random() & 3]);
        eventObject->singleMovementActive = 0;
        sprite->data[1] = 3;
    }
    return FALSE;
}

bool8 MovementType_FaceDownAndLeft_Step3(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (WaitForMovementDelay(sprite) || EventObjectIsTrainerAndCloseToPlayer(eventObject))
    {
        sprite->data[1] = 4;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementType_FaceDownAndLeft_Step4(struct EventObject *eventObject, struct Sprite *sprite)
{
    u8 direction;
    u8 directions[2];
    memcpy(directions, gDownAndLeftDirections, sizeof gDownAndLeftDirections);
    direction = TryGetTrainerEncounterDirection(eventObject, RUNFOLLOW_SOUTH_WEST);
    if (direction == 0)
    {
        direction = directions[Random() & 1];
    }
    SetEventObjectDirection(eventObject, direction);
    sprite->data[1] = 1;
    return TRUE;
}

movement_type_def(MovementType_FaceDownAndRight, gMovementTypeFuncs_FaceDownAndRight)

bool8 MovementType_FaceDownAndRight_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    ClearEventObjectMovement(eventObject, sprite);
    sprite->data[1] = 1;
    return TRUE;
}

bool8 MovementType_FaceDownAndRight_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    EventObjectSetSingleMovement(eventObject, sprite, GetFaceDirectionMovementAction(eventObject->facingDirection));
    sprite->data[1] = 2;
    return TRUE;
}

bool8 MovementType_FaceDownAndRight_Step2(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (EventObjectExecSingleMovementAction(eventObject, sprite))
    {
        SetMovementDelay(sprite, gMovementDelaysShort[Random() & 3]);
        eventObject->singleMovementActive = 0;
        sprite->data[1] = 3;
    }
    return FALSE;
}

bool8 MovementType_FaceDownAndRight_Step3(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (WaitForMovementDelay(sprite) || EventObjectIsTrainerAndCloseToPlayer(eventObject))
    {
        sprite->data[1] = 4;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementType_FaceDownAndRight_Step4(struct EventObject *eventObject, struct Sprite *sprite)
{
    u8 direction;
    u8 directions[2];
    memcpy(directions, gDownAndRightDirections, sizeof gDownAndRightDirections);
    direction = TryGetTrainerEncounterDirection(eventObject, RUNFOLLOW_SOUTH_EAST);
    if (direction == 0)
    {
        direction = directions[Random() & 1];
    }
    SetEventObjectDirection(eventObject, direction);
    sprite->data[1] = 1;
    return TRUE;
}

movement_type_def(MovementType_FaceDownUpAndLeft, gMovementTypeFuncs_FaceDownUpAndLeft)

bool8 MovementType_FaceDownUpAndLeft_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    ClearEventObjectMovement(eventObject, sprite);
    sprite->data[1] = 1;
    return TRUE;
}

bool8 MovementType_FaceDownUpAndLeft_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    EventObjectSetSingleMovement(eventObject, sprite, GetFaceDirectionMovementAction(eventObject->facingDirection));
    sprite->data[1] = 2;
    return TRUE;
}

bool8 MovementType_FaceDownUpAndLeft_Step2(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (EventObjectExecSingleMovementAction(eventObject, sprite))
    {
        SetMovementDelay(sprite, gMovementDelaysShort[Random() & 3]);
        eventObject->singleMovementActive = 0;
        sprite->data[1] = 3;
    }
    return FALSE;
}

bool8 MovementType_FaceDownUpAndLeft_Step3(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (WaitForMovementDelay(sprite) || EventObjectIsTrainerAndCloseToPlayer(eventObject))
    {
        sprite->data[1] = 4;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementType_FaceDownUpAndLeft_Step4(struct EventObject *eventObject, struct Sprite *sprite)
{
    u8 direction;
    u8 directions[4];
    memcpy(directions, gDownUpAndLeftDirections, sizeof gDownUpAndLeftDirections);
    direction = TryGetTrainerEncounterDirection(eventObject, RUNFOLLOW_NORTH_SOUTH_WEST);
    if (direction == 0)
    {
        direction = directions[Random() & 3];
    }
    SetEventObjectDirection(eventObject, direction);
    sprite->data[1] = 1;
    return TRUE;
}

movement_type_def(MovementType_FaceDownUpAndRight, gMovementTypeFuncs_FaceDownUpAndRight)

bool8 MovementType_FaceDownUpAndRight_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    ClearEventObjectMovement(eventObject, sprite);
    sprite->data[1] = 1;
    return TRUE;
}

bool8 MovementType_FaceDownUpAndRight_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    EventObjectSetSingleMovement(eventObject, sprite, GetFaceDirectionMovementAction(eventObject->facingDirection));
    sprite->data[1] = 2;
    return TRUE;
}

bool8 MovementType_FaceDownUpAndRight_Step2(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (EventObjectExecSingleMovementAction(eventObject, sprite))
    {
        SetMovementDelay(sprite, gMovementDelaysShort[Random() & 3]);
        eventObject->singleMovementActive = 0;
        sprite->data[1] = 3;
    }
    return FALSE;
}

bool8 MovementType_FaceDownUpAndRight_Step3(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (WaitForMovementDelay(sprite) || EventObjectIsTrainerAndCloseToPlayer(eventObject))
    {
        sprite->data[1] = 4;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementType_FaceDownUpAndRight_Step4(struct EventObject *eventObject, struct Sprite *sprite)
{
    u8 direction;
    u8 directions[4];
    memcpy(directions, gDownUpAndRightDirections, sizeof gDownUpAndRightDirections);
    direction = TryGetTrainerEncounterDirection(eventObject, RUNFOLLOW_NORTH_SOUTH_EAST);
    if (direction == 0)
    {
        direction = directions[Random() & 3];
    }
    SetEventObjectDirection(eventObject, direction);
    sprite->data[1] = 1;
    return TRUE;
}

movement_type_def(MovementType_FaceUpRightAndLeft, gMovementTypeFuncs_FaceUpLeftAndRight)

bool8 MovementType_FaceUpLeftAndRight_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    ClearEventObjectMovement(eventObject, sprite);
    sprite->data[1] = 1;
    return TRUE;
}

bool8 MovementType_FaceUpLeftAndRight_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    EventObjectSetSingleMovement(eventObject, sprite, GetFaceDirectionMovementAction(eventObject->facingDirection));
    sprite->data[1] = 2;
    return TRUE;
}

bool8 MovementType_FaceUpLeftAndRight_Step2(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (EventObjectExecSingleMovementAction(eventObject, sprite))
    {
        SetMovementDelay(sprite, gMovementDelaysShort[Random() & 3]);
        eventObject->singleMovementActive = 0;
        sprite->data[1] = 3;
    }
    return FALSE;
}

bool8 MovementType_FaceUpLeftAndRight_Step3(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (WaitForMovementDelay(sprite) || EventObjectIsTrainerAndCloseToPlayer(eventObject))
    {
        sprite->data[1] = 4;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementType_FaceUpLeftAndRight_Step4(struct EventObject *eventObject, struct Sprite *sprite)
{
    u8 direction;
    u8 directions[4];
    memcpy(directions, gUpLeftAndRightDirections, sizeof gUpLeftAndRightDirections);
    direction = TryGetTrainerEncounterDirection(eventObject, RUNFOLLOW_NORTH_EAST_WEST);
    if (direction == 0)
    {
        direction = directions[Random() & 3];
    }
    SetEventObjectDirection(eventObject, direction);
    sprite->data[1] = 1;
    return TRUE;
}

movement_type_def(MovementType_FaceDownRightAndLeft, gMovementTypeFuncs_FaceDownLeftAndRight)

bool8 MovementType_FaceDownLeftAndRight_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    ClearEventObjectMovement(eventObject, sprite);
    sprite->data[1] = 1;
    return TRUE;
}

bool8 MovementType_FaceDownLeftAndRight_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    EventObjectSetSingleMovement(eventObject, sprite, GetFaceDirectionMovementAction(eventObject->facingDirection));
    sprite->data[1] = 2;
    return TRUE;
}

bool8 MovementType_FaceDownLeftAndRight_Step2(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (EventObjectExecSingleMovementAction(eventObject, sprite))
    {
        SetMovementDelay(sprite, gMovementDelaysShort[Random() & 3]);
        eventObject->singleMovementActive = 0;
        sprite->data[1] = 3;
    }
    return FALSE;
}

bool8 MovementType_FaceDownLeftAndRight_Step3(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (WaitForMovementDelay(sprite) || EventObjectIsTrainerAndCloseToPlayer(eventObject))
    {
        sprite->data[1] = 4;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementType_FaceDownLeftAndRight_Step4(struct EventObject *eventObject, struct Sprite *sprite)
{
    u8 direction;
    u8 directions[4];
    memcpy(directions, gDownLeftAndRightDirections, sizeof gDownLeftAndRightDirections);
    direction = TryGetTrainerEncounterDirection(eventObject, RUNFOLLOW_SOUTH_EAST_WEST);
    if (direction == 0)
    {
        direction = directions[Random() & 3];
    }
    SetEventObjectDirection(eventObject, direction);
    sprite->data[1] = 1;
    return TRUE;
}

movement_type_def(MovementType_RotateCounterclockwise, gMovementTypeFuncs_RotateCounterclockwise)

bool8 MovementType_RotateCounterclockwise_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    ClearEventObjectMovement(eventObject, sprite);
    EventObjectSetSingleMovement(eventObject, sprite, GetFaceDirectionMovementAction(eventObject->facingDirection));
    sprite->data[1] = 1;
    return TRUE;
}

bool8 MovementType_RotateCounterclockwise_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (EventObjectExecSingleMovementAction(eventObject, sprite))
    {
        SetMovementDelay(sprite, 48);
        sprite->data[1] = 2;
    }
    return FALSE;
}

bool8 MovementType_RotateCounterclockwise_Step2(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (WaitForMovementDelay(sprite) || EventObjectIsTrainerAndCloseToPlayer(eventObject))
    {
        sprite->data[1] = 3;
    }
    return FALSE;
}

bool8 MovementType_RotateCounterclockwise_Step3(struct EventObject *eventObject, struct Sprite *sprite)
{
    u8 direction;
    u8 directions[5];
    memcpy(directions, gCounterclockwiseDirections, sizeof gCounterclockwiseDirections);
    direction = TryGetTrainerEncounterDirection(eventObject, RUNFOLLOW_ANY);
    if (direction == 0)
    {
        direction = directions[eventObject->facingDirection];
    }
    SetEventObjectDirection(eventObject, direction);
    sprite->data[1] = 0;
    return TRUE;
}

movement_type_def(MovementType_RotateClockwise, gMovementTypeFuncs_RotateClockwise)

bool8 MovementType_RotateClockwise_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    ClearEventObjectMovement(eventObject, sprite);
    EventObjectSetSingleMovement(eventObject, sprite, GetFaceDirectionMovementAction(eventObject->facingDirection));
    sprite->data[1] = 1;
    return TRUE;
}

bool8 MovementType_RotateClockwise_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (EventObjectExecSingleMovementAction(eventObject, sprite))
    {
        SetMovementDelay(sprite, 48);
        sprite->data[1] = 2;
    }
    return FALSE;
}

bool8 MovementType_RotateClockwise_Step2(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (WaitForMovementDelay(sprite) || EventObjectIsTrainerAndCloseToPlayer(eventObject))
    {
        sprite->data[1] = 3;
    }
    return FALSE;
}

bool8 MovementType_RotateClockwise_Step3(struct EventObject *eventObject, struct Sprite *sprite)
{
    u8 direction;
    u8 directions[5];
    memcpy(directions, gClockwiseDirections, sizeof gClockwiseDirections);
    direction = TryGetTrainerEncounterDirection(eventObject, RUNFOLLOW_ANY);
    if (direction == 0)
    {
        direction = directions[eventObject->facingDirection];
    }
    SetEventObjectDirection(eventObject, direction);
    sprite->data[1] = 0;
    return TRUE;
}

movement_type_def(MovementType_WalkBackAndForth, gMovementTypeFuncs_WalkBackAndForth)

bool8 MovementType_WalkBackAndForth_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    ClearEventObjectMovement(eventObject, sprite);
    sprite->data[1] = 1;
    return TRUE;
}

bool8 MovementType_WalkBackAndForth_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    u8 direction;

    direction = gInitialMovementTypeFacingDirections[eventObject->movementType];
    if (eventObject->directionSequenceIndex)
    {
        direction = GetOppositeDirection(direction);
    }
    SetEventObjectDirection(eventObject, direction);
    sprite->data[1] = 2;
    return TRUE;
}

bool8 MovementType_WalkBackAndForth_Step2(struct EventObject *eventObject, struct Sprite *sprite)
{
    bool8 collisionState;
    u8 movementActionId;

    if (eventObject->directionSequenceIndex && eventObject->initialCoords.x == eventObject->currentCoords.x && eventObject->initialCoords.y == eventObject->currentCoords.y)
    {
        eventObject->directionSequenceIndex = 0;
        SetEventObjectDirection(eventObject, GetOppositeDirection(eventObject->movementDirection));
    }
    collisionState = GetCollisionInDirection(eventObject, eventObject->movementDirection);
    movementActionId = GetWalkNormalMovementAction(eventObject->movementDirection);
    if (collisionState == TRUE)
    {
        eventObject->directionSequenceIndex++;
        SetEventObjectDirection(eventObject, GetOppositeDirection(eventObject->movementDirection));
        movementActionId = GetWalkNormalMovementAction(eventObject->movementDirection);
        collisionState = GetCollisionInDirection(eventObject, eventObject->movementDirection);
    }
    if (collisionState)
    {
        movementActionId = GetWalkInPlaceNormalMovementAction(eventObject->facingDirection);
    }
    EventObjectSetSingleMovement(eventObject, sprite, movementActionId);
    eventObject->singleMovementActive = 1;
    sprite->data[1] = 3;
    return TRUE;
}

bool8 MovementType_WalkBackAndForth_Step3(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (EventObjectExecSingleMovementAction(eventObject, sprite))
    {
        eventObject->singleMovementActive = 0;
        sprite->data[1] = 1;
    }
    return FALSE;
}

bool8 MovementType_WalkSequence_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    ClearEventObjectMovement(eventObject, sprite);
    sprite->data[1] = 1;
    return TRUE;
}

bool8 MoveNextDirectionInSequence(struct EventObject *eventObject, struct Sprite *sprite, u8 *route)
{
    u8 collisionState;
    u8 movementActionId;

    if (eventObject->directionSequenceIndex == 3 && eventObject->initialCoords.x == eventObject->currentCoords.x && eventObject->initialCoords.y == eventObject->currentCoords.y)
    {
        eventObject->directionSequenceIndex = 0;
    }
    SetEventObjectDirection(eventObject, route[eventObject->directionSequenceIndex]);
    movementActionId = GetWalkNormalMovementAction(eventObject->movementDirection);
    collisionState = GetCollisionInDirection(eventObject, eventObject->movementDirection);
    if (collisionState == TRUE)
    {
        eventObject->directionSequenceIndex++;
        SetEventObjectDirection(eventObject, route[eventObject->directionSequenceIndex]);
        movementActionId = GetWalkNormalMovementAction(eventObject->movementDirection);
        collisionState = GetCollisionInDirection(eventObject, eventObject->movementDirection);
    }
    if (collisionState)
    {
        movementActionId = GetWalkInPlaceNormalMovementAction(eventObject->facingDirection);
    }
    EventObjectSetSingleMovement(eventObject, sprite, movementActionId);
    eventObject->singleMovementActive = 1;
    sprite->data[1] = 2;
    return TRUE;
}

bool8 MovementType_WalkSequence_Step2(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (EventObjectExecSingleMovementAction(eventObject, sprite))
    {
        eventObject->singleMovementActive = 0;
        sprite->data[1] = 1;
    }
    return FALSE;
}

movement_type_def(MovementType_WalkSequenceUpRightLeftDown, gMovementTypeFuncs_WalkSequenceUpRightLeftDown)

u8 MovementType_WalkSequenceUpRightLeftDown_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    u8 directions[sizeof(gUpRightLeftDownDirections)];
    memcpy(directions, gUpRightLeftDownDirections, sizeof(gUpRightLeftDownDirections));
    if (eventObject->directionSequenceIndex == 2 && eventObject->initialCoords.x == eventObject->currentCoords.x)
    {
        eventObject->directionSequenceIndex = 3;
    }
    return MoveNextDirectionInSequence(eventObject, sprite, directions);
}

movement_type_def(MovementType_WalkSequenceRightLeftDownUp, gMovementTypeFuncs_WalkSequenceRightLeftDownUp)

u8 MovementType_WalkSequenceRightLeftDownUp_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    u8 directions[sizeof(gRightLeftDownUpDirections)];
    memcpy(directions, gRightLeftDownUpDirections, sizeof(gRightLeftDownUpDirections));
    if (eventObject->directionSequenceIndex == 1 && eventObject->initialCoords.x == eventObject->currentCoords.x)
    {
        eventObject->directionSequenceIndex = 2;
    }
    return MoveNextDirectionInSequence(eventObject, sprite, directions);
}

movement_type_def(MovementType_WalkSequenceDownUpRightLeft, gMovementTypeFuncs_WalkSequenceDownUpRightLeft)

u8 MovementType_WalkSequenceDownUpRightLeft_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    u8 directions[sizeof(gDownUpRightLeftDirections)];
    memcpy(directions, gDownUpRightLeftDirections, sizeof(gDownUpRightLeftDirections));
    if (eventObject->directionSequenceIndex == 1 && eventObject->initialCoords.y == eventObject->currentCoords.y)
    {
        eventObject->directionSequenceIndex = 2;
    }
    return MoveNextDirectionInSequence(eventObject, sprite, directions);
}

movement_type_def(MovementType_WalkSequenceLeftDownUpRight, gMovementTypeFuncs_WalkSequenceLeftDownUpRight)

u8 MovementType_WalkSequenceLeftDownUpRight_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    u8 directions[sizeof(gLeftDownUpRightDirections)];
    memcpy(directions, gLeftDownUpRightDirections, sizeof(gLeftDownUpRightDirections));
    if (eventObject->directionSequenceIndex == 2 && eventObject->initialCoords.y == eventObject->currentCoords.y)
    {
        eventObject->directionSequenceIndex = 3;
    }
    return MoveNextDirectionInSequence(eventObject, sprite, directions);
}

movement_type_def(MovementType_WalkSequenceUpLeftRightDown, gMovementTypeFuncs_WalkSequenceUpLeftRightDown)

u8 MovementType_WalkSequenceUpLeftRightDown_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    u8 directions[sizeof(gUpLeftRightDownDirections)];
    memcpy(directions, gUpLeftRightDownDirections, sizeof(gUpLeftRightDownDirections));
    if (eventObject->directionSequenceIndex == 2 && eventObject->initialCoords.x == eventObject->currentCoords.x)
    {
        eventObject->directionSequenceIndex = 3;
    }
    return MoveNextDirectionInSequence(eventObject, sprite, directions);
}

movement_type_def(MovementType_WalkSequenceLeftRightDownUp, gMovementTypeFuncs_WalkSequenceLeftRightDownUp)

u8 MovementType_WalkSequenceLeftRightDownUp_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    u8 directions[sizeof(gLeftRightDownUpDirections)];
    memcpy(directions, gLeftRightDownUpDirections, sizeof(gLeftRightDownUpDirections));
    if (eventObject->directionSequenceIndex == 1 && eventObject->initialCoords.x == eventObject->currentCoords.x)
    {
        eventObject->directionSequenceIndex = 2;
    }
    return MoveNextDirectionInSequence(eventObject, sprite, directions);
}

movement_type_def(MovementType_WalkSequenceDownUpLeftRight, gMovementTypeFuncs_WalkSequenceDownUpLeftRight)

u8 MovementType_WalkSequenceDownUpLeftRight_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    u8 directions[sizeof(gStandardDirections)];
    memcpy(directions, gStandardDirections, sizeof(gStandardDirections));
    if (eventObject->directionSequenceIndex == 1 && eventObject->initialCoords.y == eventObject->currentCoords.y)
    {
        eventObject->directionSequenceIndex = 2;
    }
    return MoveNextDirectionInSequence(eventObject, sprite, directions);
}

movement_type_def(MovementType_WalkSequenceRightDownUpLeft, gMovementTypeFuncs_WalkSequenceRightDownUpLeft)

u8 MovementType_WalkSequenceRightDownUpLeft_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    u8 directions[sizeof(gRightDownUpLeftDirections)];
    memcpy(directions, gRightDownUpLeftDirections, sizeof(gRightDownUpLeftDirections));
    if (eventObject->directionSequenceIndex == 2 && eventObject->initialCoords.y == eventObject->currentCoords.y)
    {
        eventObject->directionSequenceIndex = 3;
    }
    return MoveNextDirectionInSequence(eventObject, sprite, directions);
}

movement_type_def(MovementType_WalkSequenceLeftUpDownRight, gMovementTypeFuncs_WalkSequenceLeftUpDownRight)

u8 MovementType_WalkSequenceLeftUpDownRight_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    u8 directions[sizeof(gLeftUpDownRightDirections)];
    memcpy(directions, gLeftUpDownRightDirections, sizeof(gLeftUpDownRightDirections));
    if (eventObject->directionSequenceIndex == 2 && eventObject->initialCoords.y == eventObject->currentCoords.y)
    {
        eventObject->directionSequenceIndex = 3;
    }
    return MoveNextDirectionInSequence(eventObject, sprite, directions);
}

movement_type_def(MovementType_WalkSequenceUpDownRightLeft, gMovementTypeFuncs_WalkSequenceUpDownRightLeft)

u8 MovementType_WalkSequenceUpDownRightLeft_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    u8 directions[sizeof(gUpDownRightLeftDirections)];
    memcpy(directions, gUpDownRightLeftDirections, sizeof(gUpDownRightLeftDirections));
    if (eventObject->directionSequenceIndex == 1 && eventObject->initialCoords.y == eventObject->currentCoords.y)
    {
        eventObject->directionSequenceIndex = 2;
    }
    return MoveNextDirectionInSequence(eventObject, sprite, directions);
}

movement_type_def(MovementType_WalkSequenceRightLeftUpDown, gMovementTypeFuncs_WalkSequenceRightLeftUpDown)

u8 MovementType_WalkSequenceRightLeftUpDown_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    u8 directions[sizeof(gRightLeftUpDownDirections)];
    memcpy(directions, gRightLeftUpDownDirections, sizeof(gRightLeftUpDownDirections));
    if (eventObject->directionSequenceIndex == 1 && eventObject->initialCoords.x == eventObject->currentCoords.x)
    {
        eventObject->directionSequenceIndex = 2;
    }
    return MoveNextDirectionInSequence(eventObject, sprite, directions);
}

movement_type_def(MovementType_WalkSequenceDownRightLeftUp, gMovementTypeFuncs_WalkSequenceDownRightLeftUp)

u8 MovementType_WalkSequenceDownRightLeftUp_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    u8 directions[sizeof(gDownRightLeftUpDirections)];
    memcpy(directions, gDownRightLeftUpDirections, sizeof(gDownRightLeftUpDirections));
    if (eventObject->directionSequenceIndex == 2 && eventObject->initialCoords.x == eventObject->currentCoords.x)
    {
        eventObject->directionSequenceIndex = 3;
    }
    return MoveNextDirectionInSequence(eventObject, sprite, directions);
}

movement_type_def(MovementType_WalkSequenceRightUpDownLeft, gMovementTypeFuncs_WalkSequenceRightUpDownLeft)

u8 MovementType_WalkSequenceRightUpDownLeft_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    u8 directions[sizeof(gRightUpDownLeftDirections)];
    memcpy(directions, gRightUpDownLeftDirections, sizeof(gRightUpDownLeftDirections));
    if (eventObject->directionSequenceIndex == 2 && eventObject->initialCoords.y == eventObject->currentCoords.y)
    {
        eventObject->directionSequenceIndex = 3;
    }
    return MoveNextDirectionInSequence(eventObject, sprite, directions);
}

movement_type_def(MovementType_WalkSequenceUpDownLeftRight, gMovementTypeFuncs_WalkSequenceUpDownLeftRight)

u8 MovementType_WalkSequenceUpDownLeftRight_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    u8 directions[sizeof(gUpDownLeftRightDirections)];
    memcpy(directions, gUpDownLeftRightDirections, sizeof(gUpDownLeftRightDirections));
    if (eventObject->directionSequenceIndex == 1 && eventObject->initialCoords.y == eventObject->currentCoords.y)
    {
        eventObject->directionSequenceIndex = 2;
    }
    return MoveNextDirectionInSequence(eventObject, sprite, directions);
}

movement_type_def(MovementType_WalkSequenceLeftRightUpDown, gMovementTypeFuncs_WalkSequenceLeftRightUpDown)

u8 MovementType_WalkSequenceLeftRightUpDown_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    u8 directions[sizeof(gLeftRightUpDownDirections)];
    memcpy(directions, gLeftRightUpDownDirections, sizeof(gLeftRightUpDownDirections));
    if (eventObject->directionSequenceIndex == 1 && eventObject->initialCoords.x == eventObject->currentCoords.x)
    {
        eventObject->directionSequenceIndex = 2;
    }
    return MoveNextDirectionInSequence(eventObject, sprite, directions);
}

movement_type_def(MovementType_WalkSequenceDownLeftRightUp, gMovementTypeFuncs_WalkSequenceDownLeftRightUp)

u8 MovementType_WalkSequenceDownLeftRightUp_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    u8 directions[sizeof(gDownLeftRightUpDirections)];
    memcpy(directions, gDownLeftRightUpDirections, sizeof(gDownLeftRightUpDirections));
    if (eventObject->directionSequenceIndex == 2 && eventObject->initialCoords.x == eventObject->currentCoords.x)
    {
        eventObject->directionSequenceIndex = 3;
    }
    return MoveNextDirectionInSequence(eventObject, sprite, directions);
}

movement_type_def(MovementType_WalkSequenceUpLeftDownRight, gMovementTypeFuncs_WalkSequenceUpLeftDownRight)

u8 MovementType_WalkSequenceUpLeftDownRight_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    u8 directions[sizeof(gUpLeftDownRightDirections)];
    memcpy(directions, gUpLeftDownRightDirections, sizeof(gUpLeftDownRightDirections));
    if (eventObject->directionSequenceIndex == 2 && eventObject->initialCoords.y == eventObject->currentCoords.y)
    {
        eventObject->directionSequenceIndex = 3;
    }
    return MoveNextDirectionInSequence(eventObject, sprite, directions);
}

movement_type_def(MovementType_WalkSequenceDownRightUpLeft, gMovementTypeFuncs_WalkSequenceDownRightUpLeft)

u8 MovementType_WalkSequenceDownRightUpLeft_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    u8 directions[sizeof(gDownRightUpLeftDirections)];
    memcpy(directions, gDownRightUpLeftDirections, sizeof(gDownRightUpLeftDirections));
    if (eventObject->directionSequenceIndex == 2 && eventObject->initialCoords.y == eventObject->currentCoords.y)
    {
        eventObject->directionSequenceIndex = 3;
    }
    return MoveNextDirectionInSequence(eventObject, sprite, directions);
}

movement_type_def(MovementType_WalkSequenceLeftDownRightUp, gMovementTypeFuncs_WalkSequenceLeftDownRightUp)

u8 MovementType_WalkSequenceLeftDownRightUp_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    u8 directions[sizeof(gLeftDownRightUpDirections)];
    memcpy(directions, gLeftDownRightUpDirections, sizeof(gLeftDownRightUpDirections));
    if (eventObject->directionSequenceIndex == 2 && eventObject->initialCoords.x == eventObject->currentCoords.x)
    {
        eventObject->directionSequenceIndex = 3;
    }
    return MoveNextDirectionInSequence(eventObject, sprite, directions);
}

movement_type_def(MovementType_WalkSequenceRightUpLeftDown, gMovementTypeFuncs_WalkSequenceRightUpLeftDown)

u8 MovementType_WalkSequenceRightUpLeftDown_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    u8 directions[sizeof(gRightUpLeftDownDirections)];
    memcpy(directions, gRightUpLeftDownDirections, sizeof(gRightUpLeftDownDirections));
    if (eventObject->directionSequenceIndex == 2 && eventObject->initialCoords.x == eventObject->currentCoords.x)
    {
        eventObject->directionSequenceIndex = 3;
    }
    return MoveNextDirectionInSequence(eventObject, sprite, directions);
}

movement_type_def(MovementType_WalkSequenceUpRightDownLeft, gMovementTypeFuncs_WalkSequenceUpRightDownLeft)

u8 MovementType_WalkSequenceUpRightDownLeft_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    u8 directions[sizeof(gUpRightDownLeftDirections)];
    memcpy(directions, gUpRightDownLeftDirections, sizeof(gUpRightDownLeftDirections));
    if (eventObject->directionSequenceIndex == 2 && eventObject->initialCoords.y == eventObject->currentCoords.y)
    {
        eventObject->directionSequenceIndex = 3;
    }
    return MoveNextDirectionInSequence(eventObject, sprite, directions);
}

movement_type_def(MovementType_WalkSequenceDownLeftUpRight, gMovementTypeFuncs_WalkSequenceDownLeftUpRight)

u8 MovementType_WalkSequenceDownLeftUpRight_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    u8 directions[sizeof(gDownLeftUpRightDirections)];
    memcpy(directions, gDownLeftUpRightDirections, sizeof(gDownLeftUpRightDirections));
    if (eventObject->directionSequenceIndex == 2 && eventObject->initialCoords.y == eventObject->currentCoords.y)
    {
        eventObject->directionSequenceIndex = 3;
    }
    return MoveNextDirectionInSequence(eventObject, sprite, directions);
}

movement_type_def(MovementType_WalkSequenceLeftUpRightDown, gMovementTypeFuncs_WalkSequenceLeftUpRightDown)

u8 MovementType_WalkSequenceLeftUpRightDown_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    u8 directions[sizeof(gLeftUpRightDownDirections)];
    memcpy(directions, gLeftUpRightDownDirections, sizeof(gLeftUpRightDownDirections));
    if (eventObject->directionSequenceIndex == 2 && eventObject->initialCoords.x == eventObject->currentCoords.x)
    {
        eventObject->directionSequenceIndex = 3;
    }
    return MoveNextDirectionInSequence(eventObject, sprite, directions);
}

movement_type_def(MovementType_WalkSequenceRightDownLeftUp, gMovementTypeFuncs_WalkSequenceRightDownLeftUp)

u8 MovementType_WalkSequenceRightDownLeftUp_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    u8 directions[sizeof(gRightDownLeftUpDirections)];
    memcpy(directions, gRightDownLeftUpDirections, sizeof(gRightDownLeftUpDirections));
    if (eventObject->directionSequenceIndex == 2 && eventObject->initialCoords.x == eventObject->currentCoords.x)
    {
        eventObject->directionSequenceIndex = 3;
    }
    return MoveNextDirectionInSequence(eventObject, sprite, directions);
}

movement_type_def(MovementType_CopyPlayer, gMovementTypeFuncs_CopyPlayer)

bool8 MovementType_CopyPlayer_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    ClearEventObjectMovement(eventObject, sprite);
    if (eventObject->directionSequenceIndex == 0)
    {
        eventObject->directionSequenceIndex = GetPlayerFacingDirection();
    }
    sprite->data[1] = 1;
    return TRUE;
}

bool8 MovementType_CopyPlayer_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (gEventObjects[gPlayerAvatar.eventObjectId].movementActionId == 0xFF || gPlayerAvatar.tileTransitionState == T_TILE_CENTER)
    {
        return FALSE;
    }
    return gCopyPlayerMovementFuncs[PlayerGetCopyableMovement()](eventObject, sprite, GetPlayerMovementDirection(), NULL);
}

bool8 MovementType_CopyPlayer_Step2(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (EventObjectExecSingleMovementAction(eventObject, sprite))
    {
        eventObject->singleMovementActive = 0;
        sprite->data[1] = 1;
    }
    return FALSE;
}

bool8 CopyablePlayerMovement_None(struct EventObject *eventObject, struct Sprite *sprite, u8 playerDirection, bool8 tileCallback(u8))
{
    return FALSE;
}

bool8 CopyablePlayerMovement_FaceDirection(struct EventObject *eventObject, struct Sprite *sprite, u8 playerDirection, bool8 tileCallback(u8))
{
    EventObjectSetSingleMovement(eventObject, sprite, GetFaceDirectionMovementAction(state_to_direction(gInitialMovementTypeFacingDirections[eventObject->movementType], eventObject->directionSequenceIndex, playerDirection)));
    eventObject->singleMovementActive = 1;
    sprite->data[1] = 2;
    return TRUE;
}

bool8 CopyablePlayerMovement_GoSpeed0(struct EventObject *eventObject, struct Sprite *sprite, u8 playerDirection, bool8 tileCallback(u8))
{
    u32 direction;
    s16 x;
    s16 y;

    direction = playerDirection;
    if (EventObjectIsFarawayIslandMew(eventObject))
    {
        direction = GetMewMoveDirection();
        if (direction == DIR_NONE)
        {
            direction = playerDirection;
            direction = state_to_direction(gInitialMovementTypeFacingDirections[eventObject->movementType], eventObject->directionSequenceIndex, direction);
            EventObjectMoveDestCoords(eventObject, direction, &x, &y);
            EventObjectSetSingleMovement(eventObject, sprite, GetFaceDirectionMovementAction(direction));
            eventObject->singleMovementActive = 1;
            sprite->data[1] = 2;
            return TRUE;
        }
    }
    else
    {
        direction = state_to_direction(gInitialMovementTypeFacingDirections[eventObject->movementType], eventObject->directionSequenceIndex, direction);
    }
    EventObjectMoveDestCoords(eventObject, direction, &x, &y);
    EventObjectSetSingleMovement(eventObject, sprite, GetWalkNormalMovementAction(direction));
    if (GetCollisionAtCoords(eventObject, x, y, direction) || (tileCallback != NULL && !tileCallback(MapGridGetMetatileBehaviorAt(x, y))))
    {
        EventObjectSetSingleMovement(eventObject, sprite, GetFaceDirectionMovementAction(direction));
    }
    eventObject->singleMovementActive = 1;
    sprite->data[1] = 2;
    return TRUE;
}

bool8 CopyablePlayerMovement_GoSpeed1(struct EventObject *eventObject, struct Sprite *sprite, u8 playerDirection, bool8 tileCallback(u8))
{
    u32 direction;
    s16 x;
    s16 y;

    direction = playerDirection;
    direction = state_to_direction(gInitialMovementTypeFacingDirections[eventObject->movementType], eventObject->directionSequenceIndex, direction);
    EventObjectMoveDestCoords(eventObject, direction, &x, &y);
    EventObjectSetSingleMovement(eventObject, sprite, GetWalkFastMovementAction(direction));
    if (GetCollisionAtCoords(eventObject, x, y, direction) || (tileCallback != NULL && !tileCallback(MapGridGetMetatileBehaviorAt(x, y))))
    {
        EventObjectSetSingleMovement(eventObject, sprite, GetFaceDirectionMovementAction(direction));
    }
    eventObject->singleMovementActive = TRUE;
    sprite->data[1] = 2;
    return TRUE;
}

bool8 CopyablePlayerMovement_GoSpeed2(struct EventObject *eventObject, struct Sprite *sprite, u8 playerDirection, bool8 tileCallback(u8))
{
    u32 direction;
    s16 x;
    s16 y;

    direction = playerDirection;
    direction = state_to_direction(gInitialMovementTypeFacingDirections[eventObject->movementType], eventObject->directionSequenceIndex, direction);
    EventObjectMoveDestCoords(eventObject, direction, &x, &y);
    EventObjectSetSingleMovement(eventObject, sprite, GetWalkFastestMovementAction(direction));
    if (GetCollisionAtCoords(eventObject, x, y, direction) || (tileCallback != NULL && !tileCallback(MapGridGetMetatileBehaviorAt(x, y))))
    {
        EventObjectSetSingleMovement(eventObject, sprite, GetFaceDirectionMovementAction(direction));
    }
    eventObject->singleMovementActive = TRUE;
    sprite->data[1] = 2;
    return TRUE;
}

bool8 CopyablePlayerMovement_Slide(struct EventObject *eventObject, struct Sprite *sprite, u8 playerDirection, bool8 tileCallback(u8))
{
    u32 direction;
    s16 x;
    s16 y;

    direction = playerDirection;
    direction = state_to_direction(gInitialMovementTypeFacingDirections[eventObject->movementType], eventObject->directionSequenceIndex, direction);
    EventObjectMoveDestCoords(eventObject, direction, &x, &y);
    EventObjectSetSingleMovement(eventObject, sprite, GetSlideMovementAction(direction));
    if (GetCollisionAtCoords(eventObject, x, y, direction) || (tileCallback != NULL && !tileCallback(MapGridGetMetatileBehaviorAt(x, y))))
    {
        EventObjectSetSingleMovement(eventObject, sprite, GetFaceDirectionMovementAction(direction));
    }
    eventObject->singleMovementActive = TRUE;
    sprite->data[1] = 2;
    return TRUE;
}

bool8 cph_IM_DIFFERENT(struct EventObject *eventObject, struct Sprite *sprite, u8 playerDirection, bool8 tileCallback(u8))
{
    u32 direction;

    direction = playerDirection;
    direction = state_to_direction(gInitialMovementTypeFacingDirections[eventObject->movementType], eventObject->directionSequenceIndex, direction);
    EventObjectSetSingleMovement(eventObject, sprite, GetJumpInPlaceMovementAction(direction));
    eventObject->singleMovementActive = TRUE;
    sprite->data[1] = 2;
    return TRUE;
}

bool8 CopyablePlayerMovement_GoSpeed4(struct EventObject *eventObject, struct Sprite *sprite, u8 playerDirection, bool8 tileCallback(u8))
{
    u32 direction;
    s16 x;
    s16 y;

    direction = playerDirection;
    direction = state_to_direction(gInitialMovementTypeFacingDirections[eventObject->movementType], eventObject->directionSequenceIndex, direction);
    EventObjectMoveDestCoords(eventObject, direction, &x, &y);
    EventObjectSetSingleMovement(eventObject, sprite, GetJumpMovementAction(direction));
    if (GetCollisionAtCoords(eventObject, x, y, direction) || (tileCallback != NULL && !tileCallback(MapGridGetMetatileBehaviorAt(x, y))))
    {
        EventObjectSetSingleMovement(eventObject, sprite, GetFaceDirectionMovementAction(direction));
    }
    eventObject->singleMovementActive = TRUE;
    sprite->data[1] = 2;
    return TRUE;
}

bool8 CopyablePlayerMovement_Jump(struct EventObject *eventObject, struct Sprite *sprite, u8 playerDirection, bool8 tileCallback(u8))
{
    u32 direction;
    s16 x;
    s16 y;

    direction = playerDirection;
    direction = state_to_direction(gInitialMovementTypeFacingDirections[eventObject->movementType], eventObject->directionSequenceIndex, direction);
    x = eventObject->currentCoords.x;
    y = eventObject->currentCoords.y;
    MoveCoordsInDirection(direction, &x, &y, 2, 2);
    EventObjectSetSingleMovement(eventObject, sprite, GetJump2MovementAction(direction));
    if (GetCollisionAtCoords(eventObject, x, y, direction) || (tileCallback != NULL && !tileCallback(MapGridGetMetatileBehaviorAt(x, y))))
    {
        EventObjectSetSingleMovement(eventObject, sprite, GetFaceDirectionMovementAction(direction));
    }
    eventObject->singleMovementActive = TRUE;
    sprite->data[1] = 2;
    return TRUE;
}

movement_type_def(MovementType_CopyPlayerInGrass, gMovementTypeFuncs_CopyPlayerInGrass)

bool8 MovementType_CopyPlayerInGrass_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (gEventObjects[gPlayerAvatar.eventObjectId].movementActionId == 0xFF || gPlayerAvatar.tileTransitionState == T_TILE_CENTER)
    {
        return FALSE;
    }
    return gCopyPlayerMovementFuncs[PlayerGetCopyableMovement()](eventObject, sprite, GetPlayerMovementDirection(), MetatileBehavior_IsPokeGrass);
}

void MovementType_TreeDisguise(struct Sprite *sprite)
{
    struct EventObject *eventObject;

    eventObject = &gEventObjects[sprite->data[0]];
    if (eventObject->directionSequenceIndex == 0 || (eventObject->directionSequenceIndex == 1 && !sprite->data[7]))
    {
        EventObjectGetLocalIdAndMap(eventObject, &gFieldEffectArguments[0], &gFieldEffectArguments[1], &gFieldEffectArguments[2]);
        eventObject->fieldEffectSpriteId = FieldEffectStart(FLDEFF_TREE_DISGUISE);
        eventObject->directionSequenceIndex = 1;
        sprite->data[7]++;
    }
    UpdateEventObjectCurrentMovement(&gEventObjects[sprite->data[0]], sprite, MovementType_Disguise_Callback);
}

static bool8 MovementType_Disguise_Callback(struct EventObject *eventObject, struct Sprite *sprite)
{
    ClearEventObjectMovement(eventObject, sprite);
    return FALSE;
}

void MovementType_MountainDisguise(struct Sprite *sprite)
{
    struct EventObject *eventObject;

    eventObject = &gEventObjects[sprite->data[0]];
    if (eventObject->directionSequenceIndex == 0 || (eventObject->directionSequenceIndex == 1 && !sprite->data[7]))
    {
        EventObjectGetLocalIdAndMap(eventObject, &gFieldEffectArguments[0], &gFieldEffectArguments[1], &gFieldEffectArguments[2]);
        eventObject->fieldEffectSpriteId = FieldEffectStart(FLDEFF_MOUNTAIN_DISGUISE);
        eventObject->directionSequenceIndex = 1;
        sprite->data[7]++;
    }
    UpdateEventObjectCurrentMovement(&gEventObjects[sprite->data[0]], sprite, MovementType_Disguise_Callback);
}

void MovementType_Hidden(struct Sprite *sprite)
{
    if (!sprite->data[7])
    {
        gEventObjects[sprite->data[0]].fixedPriority = TRUE;
        sprite->subspriteMode = 2;
        sprite->oam.priority = 3;
        sprite->data[7]++;
    }
    UpdateEventObjectCurrentMovement(&gEventObjects[sprite->data[0]], sprite, MovementType_Hidden_Callback);
}

static bool8 MovementType_Hidden_Callback(struct EventObject *eventObject, struct Sprite *sprite)
{
    return gMovementTypeFuncs_Hidden[sprite->data[1]](eventObject, sprite);
}

bool8 MovementType_Hidden_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    ClearEventObjectMovement(eventObject, sprite);
    return FALSE;
}

bool8 MovementType_MoveInPlace_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (EventObjectExecSingleMovementAction(eventObject, sprite))
    {
        sprite->data[1] = 0;
    }
    return FALSE;
}

movement_type_def(MovementType_WalkInPlace, gMovementTypeFuncs_WalkInPlace)

bool8 MovementType_WalkInPlace_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    ClearEventObjectMovement(eventObject, sprite);
    EventObjectSetSingleMovement(eventObject, sprite, GetWalkInPlaceNormalMovementAction(eventObject->facingDirection));
    sprite->data[1] = 1;
    return TRUE;
}

movement_type_def(MovementType_WalkSlowlyInPlace, gMovementTypeFuncs_WalkSlowlyInPlace)

bool8 MovementType_WalkSlowlyInPlace_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    ClearEventObjectMovement(eventObject, sprite);
    EventObjectSetSingleMovement(eventObject, sprite, GetWalkInPlaceSlowMovementAction(eventObject->facingDirection));
    sprite->data[1] = 1;
    return TRUE;
}

movement_type_def(MovementType_JogInPlace, gMovementTypeFuncs_JogInPlace)

bool8 MovementType_JogInPlace_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    ClearEventObjectMovement(eventObject, sprite);
    EventObjectSetSingleMovement(eventObject, sprite, GetWalkInPlaceFastMovementAction(eventObject->facingDirection));
    sprite->data[1] = 1;
    return TRUE;
}

movement_type_def(MovementType_RunInPlace, gMovementTypeFuncs_RunInPlace)

bool8 MovementType_RunInPlace_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    ClearEventObjectMovement(eventObject, sprite);
    EventObjectSetSingleMovement(eventObject, sprite, GetWalkInPlaceFastestMovementAction(eventObject->facingDirection));
    sprite->data[1] = 1;
    return TRUE;
}

movement_type_def(MovementType_Invisible, gMovementTypeFuncs_Invisible)

bool8 MovementType_Invisible_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    ClearEventObjectMovement(eventObject, sprite);
    EventObjectSetSingleMovement(eventObject, sprite, GetFaceDirectionMovementAction(eventObject->facingDirection));
    eventObject->invisible = TRUE;
    sprite->data[1] = 1;
    return TRUE;
}
bool8 MovementType_Invisible_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (EventObjectExecSingleMovementAction(eventObject, sprite))
    {
        sprite->data[1] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementType_Invisible_Step2(struct EventObject *eventObject, struct Sprite *sprite)
{
    eventObject->singleMovementActive = 0;
    return FALSE;
}

static void ClearEventObjectMovement(struct EventObject *eventObject, struct Sprite *sprite)
{
    eventObject->singleMovementActive = 0;
    eventObject->heldMovementActive = FALSE;
    eventObject->heldMovementFinished = FALSE;
    eventObject->movementActionId = 0xFF;
    sprite->data[1] = 0;
}

u8 GetFaceDirectionAnimNum(u8 direction)
{
    return gFaceDirectionAnimNums[direction];
}

u8 GetMoveDirectionAnimNum(u8 direction)
{
    return gMoveDirectionAnimNums[direction];
}

u8 GetMoveDirectionFastAnimNum(u8 direction)
{
    return gMoveDirectionFastAnimNums[direction];
}

u8 GetMoveDirectionFasterAnimNum(u8 direction)
{
    return gMoveDirectionFasterAnimNums[direction];
}

u8 GetMoveDirectionFastestAnimNum(u8 direction)
{
    return gMoveDirectionFastestAnimNums[direction];
}

u8 GetJumpSpecialDirectionAnimNum(u8 direction)
{
    return gJumpSpecialDirectionAnimNums[direction];
}

u8 GetAcroWheelieDirectionAnimNum(u8 direction)
{
    return gAcroWheelieDirectionAnimNums[direction];
}

u8 Unref_GetAnimNums_08375633(u8 direction)
{
    return gUnrefAnimNums_08375633[direction];
}

u8 GetAcroEndWheelieDirectionAnimNum(u8 direction)
{
    return gAcroEndWheelieDirectionAnimNums[direction];
}

u8 GetAcroUnusedActionDirectionAnimNum(u8 direction)
{
    return gAcroUnusedActionDirectionAnimNums[direction];
}

u8 GetAcroWheeliePedalDirectionAnimNum(u8 direction)
{
    return gAcroWheeliePedalDirectionAnimNums[direction];
}

u8 GetFishingDirectionAnimNum(u8 direction)
{
    return gFishingDirectionAnimNums[direction];
}

u8 GetFishingNoCatchDirectionAnimNum(u8 direction)
{
    return gFishingNoCatchDirectionAnimNums[direction];
}

u8 GetFishingBiteDirectionAnimNum(u8 direction)
{
    return gFishingBiteDirectionAnimNums[direction];
}

u8 GetRunningDirectionAnimNum(u8 direction)
{
    return gRunningDirectionAnimNums[direction];
}

static const struct UnkStruct_085094AC *sub_8092A4C(const union AnimCmd *const *anims)
{
    const struct UnkStruct_085094AC *retval;

    for (retval = gUnknown_085094AC; retval->anims != NULL; retval++)
    {
        if (retval->anims == anims)
        {
            return retval;
        }
    }
    return NULL;
}

void npc_apply_anim_looping(struct EventObject *eventObject, struct Sprite *sprite, u8 animNum)
{
    const struct UnkStruct_085094AC *unk85094AC;

    if (!eventObject->inanimate)
    {
        sprite->animNum = animNum;
        unk85094AC = sub_8092A4C(sprite->anims);
        if (unk85094AC != NULL)
        {
            if (sprite->animCmdIndex == unk85094AC->animPos[0])
            {
                sprite->animCmdIndex = unk85094AC->animPos[3];
            }
            else if (sprite->animCmdIndex == unk85094AC->animPos[1])
            {
                sprite->animCmdIndex = unk85094AC->animPos[2];
            }
        }
        SeekSpriteAnim(sprite, sprite->animCmdIndex);
    }
}

void obj_npc_animation_step(struct EventObject *eventObject, struct Sprite *sprite, u8 animNum)
{
    const struct UnkStruct_085094AC *unk85094AC;

    if (!eventObject->inanimate)
    {
        u8 animPos;

        sprite->animNum = animNum;
        unk85094AC = sub_8092A4C(sprite->anims);
        if (unk85094AC != NULL)
        {
            animPos = unk85094AC->animPos[1];
            if (sprite->animCmdIndex <= unk85094AC->animPos[0])
            {
                animPos = unk85094AC->animPos[0];
            }
            SeekSpriteAnim(sprite, animPos);
        }
    }
}

// file boundary?

u8 GetDirectionToFace(s16 x1, s16 y1, s16 x2, s16 y2)
{
    if (x1 > x2)
    {
        return DIR_WEST;
    }
    if (x1 < x2)
    {
        return DIR_EAST;
    }
    if (y1 > y2)
    {
        return DIR_NORTH;
    }
    return DIR_SOUTH;
}

void SetTrainerMovementType(struct EventObject *eventObject, u8 movementType)
{
    eventObject->movementType = movementType;
    eventObject->directionSequenceIndex = 0;
    eventObject->playerCopyableMovement = 0;
    gSprites[eventObject->spriteId].callback = sMovementTypeCallbacks[movementType];
    gSprites[eventObject->spriteId].data[1] = 0;
}

u8 GetTrainerFacingDirectionMovementType(u8 direction)
{
    return gTrainerFacingDirectionMovementTypes[direction];
}

static u8 GetCollisionInDirection(struct EventObject *eventObject, u8 direction)
{
    s16 x;
    s16 y;
    x = eventObject->currentCoords.x;
    y = eventObject->currentCoords.y;
    MoveCoords(direction, &x, &y);
    return GetCollisionAtCoords(eventObject, x, y, direction);
}

u8 GetCollisionAtCoords(struct EventObject *eventObject, s16 x, s16 y, u32 dirn)
{
    u8 direction;

    direction = dirn;
    if (IsCoordOutsideEventObjectMovementRange(eventObject, x, y))
        return 1;
    else if (MapGridIsImpassableAt(x, y) || GetMapBorderIdAt(x, y) == -1 || IsMetatileDirectionallyImpassable(eventObject, x, y, direction))
        return 2;
    else if (eventObject->trackedByCamera && !CanCameraMoveInDirection(direction))
        return 2;
    else if (IsZCoordMismatchAt(eventObject->currentElevation, x, y))
        return 3;
    else if (DoesObjectCollideWithObjectAt(eventObject, x, y))
        return 4;
    return 0;
}

u8 GetCollisionFlagsAtCoords(struct EventObject *eventObject, s16 x, s16 y, u8 direction)
{
    u8 flags = 0;

    if (IsCoordOutsideEventObjectMovementRange(eventObject, x, y))
        flags |= 1;
    if (MapGridIsImpassableAt(x, y) || GetMapBorderIdAt(x, y) == -1 || IsMetatileDirectionallyImpassable(eventObject, x, y, direction) || (eventObject->trackedByCamera && !CanCameraMoveInDirection(direction)))
        flags |= 2;
    if (IsZCoordMismatchAt(eventObject->currentElevation, x, y))
        flags |= 4;
    if (DoesObjectCollideWithObjectAt(eventObject, x, y))
        flags |= 8;
    return flags;
}

static bool8 IsCoordOutsideEventObjectMovementRange(struct EventObject *eventObject, s16 x, s16 y)
{
    s16 left;
    s16 right;
    s16 top;
    s16 bottom;

    if (eventObject->range.as_nybbles.x != 0)
    {
        left = eventObject->initialCoords.x - eventObject->range.as_nybbles.x;
        right = eventObject->initialCoords.x + eventObject->range.as_nybbles.x;
        if (left > x || right < x)
        {
            return TRUE;
        }
    }
    if (eventObject->range.as_nybbles.y != 0)
    {
        top = eventObject->initialCoords.y - eventObject->range.as_nybbles.y;
        bottom = eventObject->initialCoords.y + eventObject->range.as_nybbles.y;
        if (top > y || bottom < y)
        {
            return TRUE;
        }
    }
    return FALSE;
}

static bool8 IsMetatileDirectionallyImpassable(struct EventObject *eventObject, s16 x, s16 y, u8 direction)
{
    if (gOppositeDirectionBlockedMetatileFuncs[direction - 1](eventObject->currentMetatileBehavior)
        || gDirectionBlockedMetatileFuncs[direction - 1](MapGridGetMetatileBehaviorAt(x, y)))
    {
        return TRUE;
    }
    return FALSE;
}

static bool8 DoesObjectCollideWithObjectAt(struct EventObject *eventObject, s16 x, s16 y)
{
    u8 i;
    struct EventObject *curObject;

    for (i = 0; i < EVENT_OBJECTS_COUNT; i++)
    {
        curObject = &gEventObjects[i];
      // If it is the player trying to pass the follower, we allow it
        if (eventObject-> localId == EVENT_OBJ_ID_PLAYER && curObject-> localId == EVENT_OBJ_ID_FOLLOWER)
        {
            continue ;
        }
        if (curObject->active && curObject != eventObject)
        {
            if ((curObject->currentCoords.x == x && curObject->currentCoords.y == y) || (curObject->previousCoords.x == x && curObject->previousCoords.y == y))
            {
                if (AreZCoordsCompatible(eventObject->currentElevation, curObject->currentElevation))
                {
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}

bool8 IsBerryTreeSparkling(u8 localId, u8 mapNum, u8 mapGroup)
{
    u8 eventObjectId;

    if (!TryGetEventObjectIdByLocalIdAndMap(localId, mapNum, mapGroup, &eventObjectId)
        && gSprites[gEventObjects[eventObjectId].spriteId].data[7] & 2)
    {
        return TRUE;
    }

    return FALSE;
}

void sub_8092EF0(u8 localId, u8 mapNum, u8 mapGroup)
{
    u8 eventObjectId;

    if (!TryGetEventObjectIdByLocalIdAndMap(localId, mapNum, mapGroup, &eventObjectId))
    {
        gSprites[gEventObjects[eventObjectId].spriteId].data[7] |= 0x04;
    }
}

void MoveCoords(u8 direction, s16 *x, s16 *y)
{
    *x += sDirectionToVectors[direction].x;
    *y += sDirectionToVectors[direction].y;
}

void sub_8092F60(u8 direction, s16 *x, s16 *y)
{
    *x += sDirectionToVectors[direction].x << 4;
    *y += sDirectionToVectors[direction].y << 4;
}

static void MoveCoordsInDirection(u32 dir, s16 *x, s16 *y, s16 deltaX, s16 deltaY)
{
    u8 direction = dir;
    s16 dx2 = (u16)deltaX;
    s16 dy2 = (u16)deltaY;
    if (sDirectionToVectors[direction].x > 0)
        *x += dx2;
    if (sDirectionToVectors[direction].x < 0)
        *x -= dx2;
    if (sDirectionToVectors[direction].y > 0)
        *y += dy2;
    if (sDirectionToVectors[direction].y < 0)
        *y -= dy2;
}

void sub_8092FF0(s16 x, s16 y, s16 *destX, s16 *destY)
{
    *destX = (x - gSaveBlock1Ptr->pos.x) << 4;
    *destY = (y - gSaveBlock1Ptr->pos.y) << 4;
    *destX -= gTotalCameraPixelOffsetX;
    *destY -= gTotalCameraPixelOffsetY;
}

void SetSpritePosToMapCoords(s16 mapX, s16 mapY, s16 *destX, s16 *destY)
{
    s16 dx = -gTotalCameraPixelOffsetX - gFieldCamera.x;
    s16 dy = -gTotalCameraPixelOffsetY - gFieldCamera.y;
    if (gFieldCamera.x > 0)
        dx += 1 << 4;

    if (gFieldCamera.x < 0)
        dx -= 1 << 4;

    if (gFieldCamera.y > 0)
        dy += 1 << 4;

    if (gFieldCamera.y < 0)
        dy -= 1 << 4;

    *destX = ((mapX - gSaveBlock1Ptr->pos.x) << 4) + dx;
    *destY = ((mapY - gSaveBlock1Ptr->pos.y) << 4) + dy;
}

void sub_80930E0(s16 *x, s16 *y, s16 dx, s16 dy)
{
    SetSpritePosToMapCoords(*x, *y, x, y);
    *x += dx;
    *y += dy;
}

static void GetEventObjectMovingCameraOffset(s16 *x, s16 *y)
{
    *x = 0;
    *y = 0;
    if (gFieldCamera.x > 0)
    {
        (*x)++;
    }
    if (gFieldCamera.x < 0)
    {
        (*x) --;
    }
    if (gFieldCamera.y > 0)
    {
        (*y)++;
    }
    if (gFieldCamera.y < 0)
    {
        (*y) --;
    }
}

void EventObjectMoveDestCoords(struct EventObject *eventObject, u32 direction, s16 *x, s16 *y)
{
    u8 newDirn = direction;
    *x = eventObject->currentCoords.x;
    *y = eventObject->currentCoords.y;
    MoveCoords(newDirn, x, y);
}

bool8 EventObjectIsMovementOverridden(struct EventObject *eventObject)
{
    if (eventObject->singleMovementActive || eventObject->heldMovementActive)
        return TRUE;

    return FALSE;
}

bool8 EventObjectIsHeldMovementActive(struct EventObject *eventObject)
{
    if (eventObject->heldMovementActive && eventObject->movementActionId != 0xFF)
        return TRUE;

    return FALSE;
}

bool8 EventObjectSetHeldMovement(struct EventObject *eventObject, u8 movementActionId)
{
    if (EventObjectIsMovementOverridden(eventObject))
        return TRUE;

    UnfreezeEventObject(eventObject);
    eventObject->movementActionId = movementActionId;
    eventObject->heldMovementActive = TRUE;
    eventObject->heldMovementFinished = FALSE;
    gSprites[eventObject->spriteId].data[2] = 0;
    // Add the following move to the follower if we are moving the player
    if (eventObject-> localId == 0xFF && (
        movementActionId == MOVEMENT_ACTION_WALK_NORMAL_RIGHT
        || movementActionId == MOVEMENT_ACTION_WALK_NORMAL_LEFT
        || movementActionId == MOVEMENT_ACTION_WALK_NORMAL_UP
        || movementActionId == MOVEMENT_ACTION_WALK_NORMAL_DOWN
        || movementActionId == MOVEMENT_ACTION_PLAYER_RUN_RIGHT
        || movementActionId == MOVEMENT_ACTION_PLAYER_RUN_LEFT
        || movementActionId == MOVEMENT_ACTION_PLAYER_RUN_UP
        || movementActionId == MOVEMENT_ACTION_PLAYER_RUN_DOWN
        || movementActionId == MOVEMENT_ACTION_JUMP_2_DOWN
        || movementActionId == MOVEMENT_ACTION_JUMP_2_LEFT
        || movementActionId == MOVEMENT_ACTION_JUMP_2_RIGHT))
    {
        MoveFollower (movementActionId);
    }
    return FALSE;
}

void EventObjectForceSetHeldMovement(struct EventObject *eventObject, u8 movementActionId)
{
    EventObjectClearHeldMovementIfActive(eventObject);
    EventObjectSetHeldMovement(eventObject, movementActionId);
}

void EventObjectClearHeldMovementIfActive(struct EventObject *eventObject)
{
    if (eventObject->heldMovementActive)
        EventObjectClearHeldMovement(eventObject);
}

void EventObjectClearHeldMovement(struct EventObject *eventObject)
{
    eventObject->movementActionId = 0xFF;
    eventObject->heldMovementActive = FALSE;
    eventObject->heldMovementFinished = FALSE;
    gSprites[eventObject->spriteId].data[1] = 0;
    gSprites[eventObject->spriteId].data[2] = 0;
}

u8 EventObjectCheckHeldMovementStatus(struct EventObject *eventObject)
{
    if (eventObject->heldMovementActive)
        return eventObject->heldMovementFinished;

    return 16;
}

u8 EventObjectClearHeldMovementIfFinished(struct EventObject *eventObject)
{
    u8 heldMovementStatus = EventObjectCheckHeldMovementStatus(eventObject);
    if (heldMovementStatus != 0 && heldMovementStatus != 16)
        EventObjectClearHeldMovementIfActive(eventObject);

    return heldMovementStatus;
}

u8 EventObjectGetHeldMovementActionId(struct EventObject *eventObject)
{
    if (eventObject->heldMovementActive)
        return eventObject->movementActionId;

    return 0xFF;
}

void UpdateEventObjectCurrentMovement(struct EventObject *eventObject, struct Sprite *sprite, bool8 (*callback)(struct EventObject *, struct Sprite *))
{
    DoGroundEffects_OnSpawn(eventObject, sprite);
    TryEnableEventObjectAnim(eventObject, sprite);
    if (EventObjectIsHeldMovementActive(eventObject))
    {
        EventObjectExecHeldMovementAction(eventObject, sprite);
    }
    else if (!eventObject->frozen)
    {
        while (callback(eventObject, sprite));
    }
    DoGroundEffects_OnBeginStep(eventObject, sprite);
    DoGroundEffects_OnFinishStep(eventObject, sprite);
    UpdateEventObjectSpriteAnimPause(eventObject, sprite);
    UpdateEventObjectVisibility(eventObject, sprite);
    EventObjectUpdateSubpriority(eventObject, sprite);
}

#define dirn_to_anim(name, table)\
u8 name(u32 idx)\
{\
    u8 direction;\
    u8 animIds[sizeof(table)];\
    direction = idx;\
    memcpy(animIds, (table), sizeof(table));\
    if (direction > DIR_EAST) direction = 0;\
    return animIds[direction];\
}

dirn_to_anim(GetFaceDirectionMovementAction, gFaceDirectionMovementActions);
dirn_to_anim(GetWalkSlowMovementAction, gWalkSlowMovementActions);
dirn_to_anim(GetWalkNormalMovementAction, gWalkNormalMovementActions);
dirn_to_anim(GetWalkFastMovementAction, gWalkFastMovementActions);
dirn_to_anim(GetRideWaterCurrentMovementAction, gRideWaterCurrentMovementActions);
dirn_to_anim(GetWalkFastestMovementAction, gWalkFastestMovementActions);
dirn_to_anim(GetSlideMovementAction, gSlideMovementActions);
dirn_to_anim(GetPlayerRunMovementAction, gPlayerRunMovementActions);
dirn_to_anim(GetJump2MovementAction, gJump2MovementActions);
dirn_to_anim(GetJumpInPlaceMovementAction, gJumpInPlaceMovementActions);
dirn_to_anim(GetJumpInPlaceTurnAroundMovementAction, gJumpInPlaceTurnAroundMovementActions);
dirn_to_anim(GetJumpMovementAction, gJumpMovementActions);
dirn_to_anim(GetJumpSpecialMovementAction, gJumpSpecialMovementActions);
dirn_to_anim(GetWalkInPlaceSlowMovementAction, gWalkInPlaceSlowMovementActions);
dirn_to_anim(GetWalkInPlaceNormalMovementAction, gWalkInPlaceNormalMovementActions);
dirn_to_anim(GetWalkInPlaceFastMovementAction, gWalkInPlaceFastMovementActions);
dirn_to_anim(GetWalkInPlaceFastestMovementAction, gWalkInPlaceFastestMovementActions);

bool8 EventObjectFaceOppositeDirection(struct EventObject *eventObject, u8 direction)
{
    return EventObjectSetHeldMovement(eventObject, GetFaceDirectionMovementAction(GetOppositeDirection(direction)));
}

dirn_to_anim(GetAcroWheelieFaceDirectionMovementAction, gAcroWheelieFaceDirectionMovementActions);
dirn_to_anim(GetAcroPopWheelieFaceDirectionMovementAction, gAcroPopWheelieFaceDirectionMovementActions);
dirn_to_anim(GetAcroEndWheelieFaceDirectionMovementAction, gAcroEndWheelieFaceDirectionMovementActions);
dirn_to_anim(GetAcroWheelieHopFaceDirectionMovementAction, gAcroWheelieHopFaceDirectionMovementActions);
dirn_to_anim(GetAcroWheelieHopDirectionMovementAction, gAcroWheelieHopDirectionMovementActions);
dirn_to_anim(GetAcroWheelieJumpDirectionMovementAction, gAcroWheelieJumpDirectionMovementActions);
dirn_to_anim(GetAcroWheelieInPlaceDirectionMovementAction, gAcroWheelieInPlaceDirectionMovementActions);
dirn_to_anim(GetAcroPopWheelieMoveDirectionMovementAction, gAcroPopWheelieMoveDirectionMovementActions);
dirn_to_anim(GetAcroWheelieMoveDirectionMovementAction, gAcroWheelieMoveDirectionMovementActions);
dirn_to_anim(GetAcroEndWheelieMoveDirectionMovementAction, gAcroEndWheelieMoveDirectionMovementActions);

u8 GetOppositeDirection(u8 direction)
{
    u8 directions[sizeof gOppositeDirections];

    memcpy(directions, gOppositeDirections, sizeof gOppositeDirections);
    if (direction < 1 || direction > (sizeof gOppositeDirections))
    {
        return direction;
    }
    return directions[direction - 1];
}

static u32 zffu_offset_calc(u8 a0, u8 a1)
{
    return gUnknown_0850DC2F[a0 - 1][a1 - 1];
}

static u32 state_to_direction(u8 a0, u32 a1, u32 a2)
{
    u32 zffuOffset;
    u8 a1_2;
    u8 a2_2;

    a1_2 = a1;
    a2_2 = a2;
    if (a1_2 == 0 || a2_2 == 0 || a1_2 > DIR_EAST || a2_2 > DIR_EAST)
    {
        return 0;
    }
    zffuOffset = zffu_offset_calc(a1_2, a2);
    return gUnknown_0850DC3F[a0 - 1][zffuOffset - 1];
}

static void EventObjectExecHeldMovementAction(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (gMovementActionFuncs[eventObject->movementActionId][sprite->data[2]](eventObject, sprite))
    {
        eventObject->heldMovementFinished = TRUE;
    }
}

static bool8 EventObjectExecSingleMovementAction(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (gMovementActionFuncs[eventObject->movementActionId][sprite->data[2]](eventObject, sprite))
    {
        eventObject->movementActionId = 0xFF;
        sprite->data[2] = 0;
        return TRUE;
    }
    return FALSE;
}

static void EventObjectSetSingleMovement(struct EventObject *eventObject, struct Sprite *sprite, u8 animId)
{
    eventObject->movementActionId = animId;
    sprite->data[2] = 0;
}

static void FaceDirection(struct EventObject *eventObject, struct Sprite *sprite, u8 direction)
{
    SetEventObjectDirection(eventObject, direction);
    ShiftStillEventObjectCoords(eventObject);
    obj_npc_animation_step(eventObject, sprite, GetMoveDirectionAnimNum(eventObject->facingDirection));
    sprite->animPaused = TRUE;
    sprite->data[2] = 1;
}

bool8 MovementAction_FaceDown_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    FaceDirection(eventObject, sprite, DIR_SOUTH);
    return TRUE;
}

bool8 MovementAction_FaceUp_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    FaceDirection(eventObject, sprite, DIR_NORTH);
    return TRUE;
}

bool8 MovementAction_FaceLeft_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    FaceDirection(eventObject, sprite, DIR_WEST);
    return TRUE;
}

bool8 MovementAction_FaceRight_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    FaceDirection(eventObject, sprite, DIR_EAST);
    return TRUE;
}

void npc_apply_direction(struct EventObject *eventObject, struct Sprite *sprite, u8 direction, u8 speed)
{
    s16 x;
    s16 y;

    x = eventObject->currentCoords.x;
    y = eventObject->currentCoords.y;
    SetEventObjectDirection(eventObject, direction);
    MoveCoords(direction, &x, &y);
    ShiftEventObjectCoords(eventObject, x, y);
    oamt_npc_ministep_reset(sprite, direction, speed);
    sprite->animPaused = FALSE;
    if (gLockedAnimEventObjects != NULL && FindLockedEventObjectIndex(eventObject) != EVENT_OBJECTS_COUNT)
    {
        sprite->animPaused = TRUE;
    }
    eventObject->triggerGroundEffectsOnMove = TRUE;
    sprite->data[2] = 1;
}

void do_go_anim(struct EventObject *eventObject, struct Sprite *sprite, u8 direction, u8 speed)
{
    u8 (*functions[ARRAY_COUNT(gUnknown_0850DEE8)])(u8);

    memcpy(functions, gUnknown_0850DEE8, sizeof gUnknown_0850DEE8);
    npc_apply_direction(eventObject, sprite, direction, speed);
    npc_apply_anim_looping(eventObject, sprite, functions[speed](eventObject->facingDirection));
}

void StartRunningAnim(struct EventObject *eventObject, struct Sprite *sprite, u8 direction)
{
    npc_apply_direction(eventObject, sprite, direction, 1);
    npc_apply_anim_looping(eventObject, sprite, GetRunningDirectionAnimNum(eventObject->facingDirection));
}

bool8 npc_obj_ministep_stop_on_arrival(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (obj_npc_ministep(sprite))
    {
        ShiftStillEventObjectCoords(eventObject);
        eventObject->triggerGroundEffectsOnStop = TRUE;
        sprite->animPaused = TRUE;
        return TRUE;
    }
    return FALSE;
}

void sub_8093AF0(struct EventObject *eventObject, struct Sprite *sprite, u8 direction)
{
    s16 x;
    s16 y;

    x = eventObject->currentCoords.x;
    y = eventObject->currentCoords.y;
    SetEventObjectDirection(eventObject, direction);
    MoveCoords(direction, &x, &y);
    ShiftEventObjectCoords(eventObject, x, y);
    sub_80976DC(sprite, direction);
    sprite->animPaused = FALSE;
    eventObject->triggerGroundEffectsOnMove = TRUE;
    sprite->data[2] = 1;
}

void sub_8093B60(struct EventObject *eventObject, struct Sprite *sprite, u8 direction)
{
    sub_8093AF0(eventObject, sprite, direction);
    npc_apply_anim_looping(eventObject, sprite, GetMoveDirectionAnimNum(eventObject->facingDirection));
}

bool8 an_walk_any_2(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (sub_80976EC(sprite))
    {
        ShiftStillEventObjectCoords(eventObject);
        eventObject->triggerGroundEffectsOnStop = TRUE;
        sprite->animPaused = TRUE;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_WalkSlowDiagonalUpLeft_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8093B60(eventObject, sprite, DIR_NORTHWEST);
    return MovementAction_WalkSlowDiagonalUpLeft_Step1(eventObject, sprite);
}

bool8 MovementAction_WalkSlowDiagonalUpLeft_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (an_walk_any_2(eventObject, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_WalkSlowDiagonalUpRight_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8093B60(eventObject, sprite, DIR_NORTHEAST);
    return MovementAction_WalkSlowDiagonalUpRight_Step1(eventObject, sprite);
}

bool8 MovementAction_WalkSlowDiagonalUpRight_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (an_walk_any_2(eventObject, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_WalkSlowDiagonalDownLeft_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8093B60(eventObject, sprite, DIR_SOUTHWEST);
    return MovementAction_WalkSlowDiagonalDownLeft_Step1(eventObject, sprite);
}

bool8 MovementAction_WalkSlowDiagonalDownLeft_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (an_walk_any_2(eventObject, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_WalkSlowDiagonalDownRight_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8093B60(eventObject, sprite, DIR_SOUTHEAST);
    return MovementAction_WalkSlowDiagonalDownRight_Step1(eventObject, sprite);
}

bool8 MovementAction_WalkSlowDiagonalDownRight_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (an_walk_any_2(eventObject, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_WalkSlowDown_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8093B60(eventObject, sprite, DIR_SOUTH);
    return MovementAction_WalkSlowDown_Step1(eventObject, sprite);
}

bool8 MovementAction_WalkSlowDown_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (an_walk_any_2(eventObject, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_WalkSlowUp_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8093B60(eventObject, sprite, DIR_NORTH);
    return MovementAction_WalkSlowUp_Step1(eventObject, sprite);
}

bool8 MovementAction_WalkSlowUp_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (an_walk_any_2(eventObject, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_WalkSlowLeft_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8093B60(eventObject, sprite, DIR_WEST);
    return MovementAction_WalkSlowLeft_Step1(eventObject, sprite);
}

bool8 MovementAction_WalkSlowLeft_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (an_walk_any_2(eventObject, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_WalkSlowRight_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8093B60(eventObject, sprite, DIR_EAST);
    return MovementAction_WalkSlowRight_Step1(eventObject, sprite);
}

bool8 MovementAction_WalkSlowRight_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (an_walk_any_2(eventObject, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_WalkNormalDiagonalUpLeft_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    do_go_anim(eventObject, sprite, DIR_NORTHWEST, 0);
    return MovementAction_WalkNormalDiagonalUpLeft_Step1(eventObject, sprite);
}

bool8 MovementAction_WalkNormalDiagonalUpLeft_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (npc_obj_ministep_stop_on_arrival(eventObject, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_WalkNormalDiagonalUpRight_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    do_go_anim(eventObject, sprite, DIR_NORTHEAST, 0);
    return MovementAction_WalkNormalDiagonalUpRight_Step1(eventObject, sprite);
}

bool8 MovementAction_WalkNormalDiagonalUpRight_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (npc_obj_ministep_stop_on_arrival(eventObject, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_WalkNormalDiagonalDownLeft_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    do_go_anim(eventObject, sprite, DIR_SOUTHWEST, 0);
    return MovementAction_WalkNormalDiagonalDownLeft_Step1(eventObject, sprite);
}

bool8 MovementAction_WalkNormalDiagonalDownLeft_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (npc_obj_ministep_stop_on_arrival(eventObject, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_WalkNormalDiagonalDownRight_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    do_go_anim(eventObject, sprite, DIR_SOUTHEAST, 0);
    return MovementAction_WalkNormalDiagonalDownRight_Step1(eventObject, sprite);
}

bool8 MovementAction_WalkNormalDiagonalDownRight_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (npc_obj_ministep_stop_on_arrival(eventObject, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_WalkNormalDown_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    do_go_anim(eventObject, sprite, DIR_SOUTH, 0);
    return MovementAction_WalkNormalDown_Step1(eventObject, sprite);
}

bool8 MovementAction_WalkNormalDown_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (npc_obj_ministep_stop_on_arrival(eventObject, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_WalkNormalUp_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    do_go_anim(eventObject, sprite, DIR_NORTH, 0);
    return MovementAction_WalkNormalUp_Step1(eventObject, sprite);
}

bool8 MovementAction_WalkNormalUp_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (npc_obj_ministep_stop_on_arrival(eventObject, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_WalkNormalLeft_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    do_go_anim(eventObject, sprite, DIR_WEST, 0);
    return MovementAction_WalkNormalLeft_Step1(eventObject, sprite);
}

bool8 MovementAction_WalkNormalLeft_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (npc_obj_ministep_stop_on_arrival(eventObject, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_WalkNormalRight_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    do_go_anim(eventObject, sprite, DIR_EAST, 0);
    return MovementAction_WalkNormalRight_Step1(eventObject, sprite);
}

bool8 MovementAction_WalkNormalRight_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (npc_obj_ministep_stop_on_arrival(eventObject, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

void sub_8093FC4(struct EventObject *eventObject, struct Sprite *sprite, u8 direction, u8 speed, u8 a5)
{
    s16 displacements[ARRAY_COUNT(gUnknown_0850DFBC)];
    s16 x;
    s16 y;

    memcpy(displacements, gUnknown_0850DFBC, sizeof gUnknown_0850DFBC);
    x = 0;
    y = 0;
    SetEventObjectDirection(eventObject, direction);
    MoveCoordsInDirection(direction, &x, &y, displacements[speed], displacements[speed]);
    ShiftEventObjectCoords(eventObject, eventObject->currentCoords.x + x, eventObject->currentCoords.y + y);
    sub_809783C(sprite, direction, speed, a5);
    sprite->data[2] = 1;
    sprite->animPaused = 0;
    eventObject->triggerGroundEffectsOnMove = 1;
    eventObject->disableCoveringGroundEffects = 1;
}

void maybe_shadow_1(struct EventObject *eventObject, struct Sprite *sprite, u8 direction, u8 speed, u8 a4)
{
    sub_8093FC4(eventObject, sprite, direction, speed, a4);
    npc_apply_anim_looping(eventObject, sprite, GetMoveDirectionAnimNum(eventObject->facingDirection));
    DoShadowFieldEffect(eventObject);
}

u8 sub_80940C4(struct EventObject *eventObject, struct Sprite *sprite, u8 callback(struct Sprite *))
{
    s16 displacements[ARRAY_COUNT(gUnknown_0850DFC2)];
    s16 x;
    s16 y;
    u8 result;

    memcpy(displacements, gUnknown_0850DFC2, sizeof gUnknown_0850DFC2);
    result = callback(sprite);
    if (result == 1 && displacements[sprite->data[4]] != 0)
    {
        x = 0;
        y = 0;
        MoveCoordsInDirection(eventObject->movementDirection, &x, &y, displacements[sprite->data[4]], displacements[sprite->data[4]]);
        ShiftEventObjectCoords(eventObject, eventObject->currentCoords.x + x, eventObject->currentCoords.y + y);
        eventObject->triggerGroundEffectsOnMove = TRUE;
        eventObject->disableCoveringGroundEffects = TRUE;
    }
    else if (result == 0xFF)
    {
        ShiftStillEventObjectCoords(eventObject);
        eventObject->triggerGroundEffectsOnStop = TRUE;
        eventObject->landingJump = TRUE;
        sprite->animPaused = TRUE;
    }
    return result;
}

u8 sub_8094188(struct EventObject *eventObject, struct Sprite *sprite)
{
    return sub_80940C4(eventObject, sprite, sub_809785C);
}

u8 sub_809419C(struct EventObject *eventObject, struct Sprite *sprite)
{
    return sub_80940C4(eventObject, sprite, sub_80978E4);
}

bool8 sub_80941B0(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (sub_8094188(eventObject, sprite) == 0xFF)
    {
        return TRUE;
    }
    return FALSE;
}

bool8 sub_80941C8(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (sub_809419C(eventObject, sprite) == 0xFF)
    {
        return TRUE;
    }
    return FALSE;
}

bool8 sub_80941E0(struct EventObject *eventObject, struct Sprite *sprite)
{
    switch (sub_8094188(eventObject, sprite))
    {
        case 255:
            return TRUE;
        case   1:
            SetEventObjectDirection(eventObject, GetOppositeDirection(eventObject->movementDirection));
            obj_npc_animation_step(eventObject, sprite, GetMoveDirectionAnimNum(eventObject->facingDirection));
        default:
            return FALSE;
    }
}

bool8 MovementAction_Jump2Down_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    maybe_shadow_1(eventObject, sprite, DIR_SOUTH, 2, 0);
    return MovementAction_Jump2Down_Step1(eventObject, sprite);
}

bool8 MovementAction_Jump2Down_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (sub_80941B0(eventObject, sprite))
    {
        eventObject->hasShadow = FALSE;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_Jump2Up_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    maybe_shadow_1(eventObject, sprite, DIR_NORTH, 2, 0);
    return MovementAction_Jump2Up_Step1(eventObject, sprite);
}

bool8 MovementAction_Jump2Up_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (sub_80941B0(eventObject, sprite))
    {
        eventObject->hasShadow = FALSE;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_Jump2Left_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    maybe_shadow_1(eventObject, sprite, DIR_WEST, 2, 0);
    return MovementAction_Jump2Left_Step1(eventObject, sprite);
}

bool8 MovementAction_Jump2Left_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (sub_80941B0(eventObject, sprite))
    {
        eventObject->hasShadow = FALSE;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_Jump2Right_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    maybe_shadow_1(eventObject, sprite, DIR_EAST, 2, 0);
    return MovementAction_Jump2Right_Step1(eventObject, sprite);
}

bool8 MovementAction_Jump2Right_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (sub_80941B0(eventObject, sprite))
    {
        eventObject->hasShadow = FALSE;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}


void sub_8094390(struct Sprite *sprite, u16 duration)
{
    sprite->data[2] = 1;
    sprite->data[3] = duration;
}

bool8 MovementAction_Delay_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (-- sprite->data[3] == 0)
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_Delay1_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8094390(sprite, 1);
    return MovementAction_Delay_Step1(eventObject, sprite);
}

bool8 MovementAction_Delay2_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8094390(sprite, 2);
    return MovementAction_Delay_Step1(eventObject, sprite);
}

bool8 MovementAction_Delay4_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8094390(sprite, 4);
    return MovementAction_Delay_Step1(eventObject, sprite);
}

bool8 MovementAction_Delay8_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8094390(sprite, 8);
    return MovementAction_Delay_Step1(eventObject, sprite);
}

bool8 MovementAction_Delay16_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8094390(sprite, 16);
    return MovementAction_Delay_Step1(eventObject, sprite);
}

bool8 MovementAction_WalkFastDown_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    do_go_anim(eventObject, sprite, DIR_SOUTH, 1);
    return MovementAction_WalkFastDown_Step1(eventObject, sprite);
}

bool8 MovementAction_WalkFastDown_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (npc_obj_ministep_stop_on_arrival(eventObject, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_WalkFastUp_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    do_go_anim(eventObject, sprite, DIR_NORTH, 1);
    return MovementAction_WalkFastUp_Step1(eventObject, sprite);
}

bool8 MovementAction_WalkFastUp_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (npc_obj_ministep_stop_on_arrival(eventObject, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_WalkFastLeft_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    do_go_anim(eventObject, sprite, DIR_WEST, 1);
    return MovementAction_WalkFastLeft_Step1(eventObject, sprite);
}

bool8 MovementAction_WalkFastLeft_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (npc_obj_ministep_stop_on_arrival(eventObject, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_WalkFastRight_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    do_go_anim(eventObject, sprite, DIR_EAST, 1);
    return MovementAction_WalkFastRight_Step1(eventObject, sprite);
}

bool8 MovementAction_WalkFastRight_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (npc_obj_ministep_stop_on_arrival(eventObject, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}


void sub_8094554(struct EventObject *eventObject, struct Sprite *sprite, u8 direction, u8 animNum, u16 duration)
{
    SetEventObjectDirection(eventObject, direction);
    npc_apply_anim_looping(eventObject, sprite, animNum);
    sprite->animPaused = FALSE;
    sprite->data[2] = 1;
    sprite->data[3] = duration;
}

bool8 MovementAction_WalkInPlace_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (-- sprite->data[3] == 0)
    {
        sprite->data[2] = 2;
        sprite->animPaused = TRUE;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_WalkInPlaceSlow_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (sprite->data[3] & 1)
    {
        sprite->animDelayCounter++;
    }
    return MovementAction_WalkInPlace_Step1(eventObject, sprite);
}

bool8 MovementAction_WalkInPlaceSlowDown_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8094554(eventObject, sprite, DIR_SOUTH, GetMoveDirectionAnimNum(DIR_SOUTH), 32);
    return MovementAction_WalkInPlaceSlow_Step1(eventObject, sprite);
}

bool8 MovementAction_WalkInPlaceSlowUp_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8094554(eventObject, sprite, DIR_NORTH, GetMoveDirectionAnimNum(DIR_NORTH), 32);
    return MovementAction_WalkInPlaceSlow_Step1(eventObject, sprite);
}

bool8 MovementAction_WalkInPlaceSlowLeft_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8094554(eventObject, sprite, DIR_WEST, GetMoveDirectionAnimNum(DIR_WEST), 32);
    return MovementAction_WalkInPlaceSlow_Step1(eventObject, sprite);
}

bool8 MovementAction_WalkInPlaceSlowRight_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8094554(eventObject, sprite, DIR_EAST, GetMoveDirectionAnimNum(DIR_EAST), 32);
    return MovementAction_WalkInPlaceSlow_Step1(eventObject, sprite);
}

bool8 MovementAction_WalkInPlaceNormalDown_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8094554(eventObject, sprite, DIR_SOUTH, GetMoveDirectionAnimNum(DIR_SOUTH), 16);
    return MovementAction_WalkInPlace_Step1(eventObject, sprite);
}

bool8 MovementAction_WalkInPlaceNormalUp_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8094554(eventObject, sprite, DIR_NORTH, GetMoveDirectionAnimNum(DIR_NORTH), 16);
    return MovementAction_WalkInPlace_Step1(eventObject, sprite);
}

bool8 MovementAction_WalkInPlaceNormalLeft_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8094554(eventObject, sprite, DIR_WEST, GetMoveDirectionAnimNum(DIR_WEST), 16);
    return MovementAction_WalkInPlace_Step1(eventObject, sprite);
}

bool8 MovementAction_WalkInPlaceNormalRight_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8094554(eventObject, sprite, DIR_EAST, GetMoveDirectionAnimNum(DIR_EAST), 16);
    return MovementAction_WalkInPlace_Step1(eventObject, sprite);
}

bool8 MovementAction_WalkInPlaceFastDown_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8094554(eventObject, sprite, DIR_SOUTH, GetMoveDirectionFastAnimNum(DIR_SOUTH), 8);
    return MovementAction_WalkInPlace_Step1(eventObject, sprite);
}

bool8 MovementAction_WalkInPlaceFastUp_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8094554(eventObject, sprite, DIR_NORTH, GetMoveDirectionFastAnimNum(DIR_NORTH), 8);
    return MovementAction_WalkInPlace_Step1(eventObject, sprite);
}

bool8 MovementAction_WalkInPlaceFastLeft_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8094554(eventObject, sprite, DIR_WEST, GetMoveDirectionFastAnimNum(DIR_WEST), 8);
    return MovementAction_WalkInPlace_Step1(eventObject, sprite);
}

bool8 MovementAction_WalkInPlaceFastRight_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8094554(eventObject, sprite, DIR_EAST, GetMoveDirectionFastAnimNum(DIR_EAST), 8);
    return MovementAction_WalkInPlace_Step1(eventObject, sprite);
}

bool8 MovementAction_WalkInPlaceFastestDown_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8094554(eventObject, sprite, DIR_SOUTH, GetMoveDirectionFasterAnimNum(DIR_SOUTH), 4);
    return MovementAction_WalkInPlace_Step1(eventObject, sprite);
}

bool8 MovementAction_WalkInPlaceFastestUp_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8094554(eventObject, sprite, DIR_NORTH, GetMoveDirectionFasterAnimNum(DIR_NORTH), 4);
    return MovementAction_WalkInPlace_Step1(eventObject, sprite);
}

bool8 MovementAction_WalkInPlaceFastestLeft_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8094554(eventObject, sprite, DIR_WEST, GetMoveDirectionFasterAnimNum(DIR_WEST), 4);
    return MovementAction_WalkInPlace_Step1(eventObject, sprite);
}

bool8 MovementAction_WalkInPlaceFastestRight_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8094554(eventObject, sprite, DIR_EAST, GetMoveDirectionFasterAnimNum(DIR_EAST), 4);
    return MovementAction_WalkInPlace_Step1(eventObject, sprite);
}

bool8 MovementAction_RideWaterCurrentDown_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    do_go_anim(eventObject, sprite, DIR_SOUTH, 2);
    return MovementAction_RideWaterCurrentDown_Step1(eventObject, sprite);
}

bool8 MovementAction_RideWaterCurrentDown_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (npc_obj_ministep_stop_on_arrival(eventObject, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_RideWaterCurrentUp_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    do_go_anim(eventObject, sprite, DIR_NORTH, 2);
    return MovementAction_RideWaterCurrentUp_Step1(eventObject, sprite);
}

bool8 MovementAction_RideWaterCurrentUp_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (npc_obj_ministep_stop_on_arrival(eventObject, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_RideWaterCurrentLeft_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    do_go_anim(eventObject, sprite, DIR_WEST, 2);
    return MovementAction_RideWaterCurrentLeft_Step1(eventObject, sprite);
}

bool8 MovementAction_RideWaterCurrentLeft_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (npc_obj_ministep_stop_on_arrival(eventObject, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_RideWaterCurrentRight_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    do_go_anim(eventObject, sprite, DIR_EAST, 2);
    return MovementAction_RideWaterCurrentRight_Step1(eventObject, sprite);
}

bool8 MovementAction_RideWaterCurrentRight_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (npc_obj_ministep_stop_on_arrival(eventObject, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_WalkFastestDown_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    do_go_anim(eventObject, sprite, DIR_SOUTH, 3);
    return MovementAction_WalkFastestDown_Step1(eventObject, sprite);
}

bool8 MovementAction_WalkFastestDown_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (npc_obj_ministep_stop_on_arrival(eventObject, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_WalkFastestUp_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    do_go_anim(eventObject, sprite, DIR_NORTH, 3);
    return MovementAction_WalkFastestUp_Step1(eventObject, sprite);
}

bool8 MovementAction_WalkFastestUp_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (npc_obj_ministep_stop_on_arrival(eventObject, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_WalkFastestLeft_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    do_go_anim(eventObject, sprite, DIR_WEST, 3);
    return MovementAction_WalkFastestLeft_Step1(eventObject, sprite);
}

bool8 MovementAction_WalkFastestLeft_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (npc_obj_ministep_stop_on_arrival(eventObject, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_WalkFastestRight_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    do_go_anim(eventObject, sprite, DIR_EAST, 3);
    return MovementAction_WalkFastestRight_Step1(eventObject, sprite);
}

bool8 MovementAction_WalkFastestRight_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (npc_obj_ministep_stop_on_arrival(eventObject, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_SlideDown_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    do_go_anim(eventObject, sprite, DIR_SOUTH, 4);
    return MovementAction_SlideDown_Step1(eventObject, sprite);
}

bool8 MovementAction_SlideDown_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (npc_obj_ministep_stop_on_arrival(eventObject, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_SlideUp_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    do_go_anim(eventObject, sprite, DIR_NORTH, 4);
    return MovementAction_SlideUp_Step1(eventObject, sprite);
}

bool8 MovementAction_SlideUp_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (npc_obj_ministep_stop_on_arrival(eventObject, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_SlideLeft_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    do_go_anim(eventObject, sprite, DIR_WEST, 4);
    return MovementAction_SlideLeft_Step1(eventObject, sprite);
}

bool8 MovementAction_SlideLeft_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (npc_obj_ministep_stop_on_arrival(eventObject, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_SlideRight_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    do_go_anim(eventObject, sprite, DIR_EAST, 4);
    return MovementAction_SlideRight_Step1(eventObject, sprite);
}

bool8 MovementAction_SlideRight_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (npc_obj_ministep_stop_on_arrival(eventObject, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_PlayerRunDown_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    StartRunningAnim(eventObject, sprite, DIR_SOUTH);
    return MovementAction_PlayerRunDown_Step1(eventObject, sprite);
}

bool8 MovementAction_PlayerRunDown_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (npc_obj_ministep_stop_on_arrival(eventObject, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_PlayerRunUp_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    StartRunningAnim(eventObject, sprite, DIR_NORTH);
    return MovementAction_PlayerRunUp_Step1(eventObject, sprite);
}

bool8 MovementAction_PlayerRunUp_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (npc_obj_ministep_stop_on_arrival(eventObject, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_PlayerRunLeft_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    StartRunningAnim(eventObject, sprite, DIR_WEST);
    return MovementAction_PlayerRunLeft_Step1(eventObject, sprite);
}

bool8 MovementAction_PlayerRunLeft_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (npc_obj_ministep_stop_on_arrival(eventObject, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_PlayerRunRight_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    StartRunningAnim(eventObject, sprite, DIR_EAST);
    return MovementAction_PlayerRunRight_Step1(eventObject, sprite);
}

bool8 MovementAction_PlayerRunRight_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (npc_obj_ministep_stop_on_arrival(eventObject, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

void StartSpriteAnimInDirection(struct EventObject *eventObject, struct Sprite *sprite, u8 direction, u8 animNum)
{
    SetAndStartSpriteAnim(sprite, animNum, 0);
    SetEventObjectDirection(eventObject, direction);
    sprite->data[2] = 1;
}

bool8 MovementAction_StartAnimInDirection_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    StartSpriteAnimInDirection(eventObject, sprite, eventObject->movementDirection, sprite->animNum);
    return FALSE;
}

bool8 MovementAction_WaitSpriteAnim(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (SpriteAnimEnded(sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

void sub_8094DE4(struct EventObject *eventObject, struct Sprite *sprite, u8 direction)
{
    sub_8093FC4(eventObject, sprite, direction, 1, 0);
    StartSpriteAnim(sprite, GetJumpSpecialDirectionAnimNum(direction));
}

bool8 MovementAction_JumpSpecialDown_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8094DE4(eventObject, sprite, DIR_SOUTH);
    return MovementAction_JumpSpecialDown_Step1(eventObject, sprite);
}

bool8 MovementAction_JumpSpecialDown_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (sub_80941C8(eventObject, sprite))
    {
        sprite->data[2] = 2;
        eventObject->landingJump = FALSE;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_JumpSpecialUp_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8094DE4(eventObject, sprite, DIR_NORTH);
    return MovementAction_JumpSpecialUp_Step1(eventObject, sprite);
}

bool8 MovementAction_JumpSpecialUp_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (sub_80941C8(eventObject, sprite))
    {
        sprite->data[2] = 2;
        eventObject->landingJump = FALSE;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_JumpSpecialLeft_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8094DE4(eventObject, sprite, DIR_WEST);
    return MovementAction_JumpSpecialLeft_Step1(eventObject, sprite);
}

bool8 MovementAction_JumpSpecialLeft_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (sub_80941C8(eventObject, sprite))
    {
        sprite->data[2] = 2;
        eventObject->landingJump = FALSE;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_JumpSpecialRight_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8094DE4(eventObject, sprite, DIR_EAST);
    return MovementAction_JumpSpecialRight_Step1(eventObject, sprite);
}

bool8 MovementAction_JumpSpecialRight_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (sub_80941C8(eventObject, sprite))
    {
        sprite->data[2] = 2;
        eventObject->landingJump = FALSE;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_FacePlayer_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    u8 playerObjectId;

    if (!TryGetEventObjectIdByLocalIdAndMap(EVENT_OBJ_ID_PLAYER, 0, 0, &playerObjectId))
    {
        FaceDirection(eventObject, sprite, GetDirectionToFace(eventObject->currentCoords.x, eventObject->currentCoords.y, gEventObjects[playerObjectId].currentCoords.x, gEventObjects[playerObjectId].currentCoords.y));
    }
    sprite->data[2] = 1;
    return TRUE;
}

bool8 MovementAction_FaceAwayPlayer_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    u8 playerObjectId;

    if (!TryGetEventObjectIdByLocalIdAndMap(EVENT_OBJ_ID_PLAYER, 0, 0, &playerObjectId))
    {
        FaceDirection(eventObject, sprite, GetOppositeDirection(GetDirectionToFace(eventObject->currentCoords.x, eventObject->currentCoords.y, gEventObjects[playerObjectId].currentCoords.x, gEventObjects[playerObjectId].currentCoords.y)));
    }
    sprite->data[2] = 1;
    return TRUE;
}

bool8 MovementAction_LockFacingDirection_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    eventObject->facingDirectionLocked = TRUE;
    sprite->data[2] = 1;
    return TRUE;
}

bool8 MovementAction_UnlockFacingDirection_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    eventObject->facingDirectionLocked = FALSE;
    sprite->data[2] = 1;
    return TRUE;
}

bool8 MovementAction_JumpDown_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    maybe_shadow_1(eventObject, sprite, DIR_SOUTH, 1, 2);
    return MovementAction_JumpDown_Step1(eventObject, sprite);
}

bool8 MovementAction_JumpDown_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (sub_80941B0(eventObject, sprite))
    {
        eventObject->hasShadow = 0;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_JumpUp_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    maybe_shadow_1(eventObject, sprite, DIR_NORTH, 1, 2);
    return MovementAction_JumpUp_Step1(eventObject, sprite);
}

bool8 MovementAction_JumpUp_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (sub_80941B0(eventObject, sprite))
    {
        eventObject->hasShadow = 0;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_JumpLeft_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    maybe_shadow_1(eventObject, sprite, DIR_WEST, 1, 2);
    return MovementAction_JumpLeft_Step1(eventObject, sprite);
}

bool8 MovementAction_JumpLeft_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (sub_80941B0(eventObject, sprite))
    {
        eventObject->hasShadow = 0;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_JumpRight_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    maybe_shadow_1(eventObject, sprite, DIR_EAST, 1, 2);
    return MovementAction_JumpRight_Step1(eventObject, sprite);
}

bool8 MovementAction_JumpRight_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (sub_80941B0(eventObject, sprite))
    {
        eventObject->hasShadow = 0;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_JumpInPlaceDown_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    maybe_shadow_1(eventObject, sprite, DIR_SOUTH, 0, 0);
    return MovementAction_JumpInPlaceDown_Step1(eventObject, sprite);
}

bool8 MovementAction_JumpInPlaceDown_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (sub_80941B0(eventObject, sprite))
    {
        eventObject->hasShadow = 0;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_JumpInPlaceUp_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    maybe_shadow_1(eventObject, sprite, DIR_NORTH, 0, 0);
    return MovementAction_JumpInPlaceUp_Step1(eventObject, sprite);
}

bool8 MovementAction_JumpInPlaceUp_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (sub_80941B0(eventObject, sprite))
    {
        eventObject->hasShadow = 0;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_JumpInPlaceLeft_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    maybe_shadow_1(eventObject, sprite, DIR_WEST, 0, 0);
    return MovementAction_JumpInPlaceLeft_Step1(eventObject, sprite);
}

bool8 MovementAction_JumpInPlaceLeft_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (sub_80941B0(eventObject, sprite))
    {
        eventObject->hasShadow = 0;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_JumpInPlaceRight_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    maybe_shadow_1(eventObject, sprite, DIR_EAST, 0, 0);
    return MovementAction_JumpInPlaceRight_Step1(eventObject, sprite);
}

bool8 MovementAction_JumpInPlaceRight_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (sub_80941B0(eventObject, sprite))
    {
        eventObject->hasShadow = 0;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_JumpInPlaceDownUp_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    maybe_shadow_1(eventObject, sprite, DIR_SOUTH, 0, 2);
    return MovementAction_JumpInPlaceDownUp_Step1(eventObject, sprite);
}

bool8 MovementAction_JumpInPlaceDownUp_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (sub_80941E0(eventObject, sprite))
    {
        eventObject->hasShadow = 0;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_JumpInPlaceUpDown_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    maybe_shadow_1(eventObject, sprite, DIR_NORTH, 0, 2);
    return MovementAction_JumpInPlaceUpDown_Step1(eventObject, sprite);
}

bool8 MovementAction_JumpInPlaceUpDown_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (sub_80941E0(eventObject, sprite))
    {
        eventObject->hasShadow = 0;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_JumpInPlaceLeftRight_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    maybe_shadow_1(eventObject, sprite, DIR_WEST, 0, 2);
    return MovementAction_JumpInPlaceLeftRight_Step1(eventObject, sprite);
}

bool8 MovementAction_JumpInPlaceLeftRight_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (sub_80941E0(eventObject, sprite))
    {
        eventObject->hasShadow = 0;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_JumpInPlaceRightLeft_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    maybe_shadow_1(eventObject, sprite, DIR_EAST, 0, 2);
    return MovementAction_JumpInPlaceRightLeft_Step1(eventObject, sprite);
}

bool8 MovementAction_JumpInPlaceRightLeft_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (sub_80941E0(eventObject, sprite))
    {
        eventObject->hasShadow = 0;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_FaceOriginalDirection_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    FaceDirection(eventObject, sprite, gInitialMovementTypeFacingDirections[eventObject->movementType]);
    return TRUE;
}

bool8 MovementAction_NurseJoyBowDown_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    StartSpriteAnimInDirection(eventObject, sprite, DIR_SOUTH, 0x14);
    return FALSE;
}

bool8 MovementAction_EnableJumpLandingGroundEffect_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    eventObject->disableJumpLandingGroundEffect = FALSE;
    sprite->data[2] = 1;
    return TRUE;
}

bool8 MovementAction_DisableJumpLandingGroundEffect_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    eventObject->disableJumpLandingGroundEffect = TRUE;
    sprite->data[2] = 1;
    return TRUE;
}

bool8 MovementAction_DisableAnimation_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    eventObject->inanimate = TRUE;
    sprite->data[2] = 1;
    return TRUE;
}

bool8 MovementAction_RestoreAnimation_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    eventObject->inanimate = GetEventObjectGraphicsInfo(eventObject->graphicsId)->inanimate;
    sprite->data[2] = 1;
    return TRUE;
}

bool8 MovementAction_SetInvisible_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    eventObject->invisible = TRUE;
    sprite->data[2] = 1;
    return TRUE;
}

bool8 MovementAction_SetVisible_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    eventObject->invisible = FALSE;
    sprite->data[2] = 1;
    return TRUE;
}

bool8 MovementAction_EmoteExclamationMark_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    EventObjectGetLocalIdAndMap(eventObject, &gFieldEffectArguments[0], &gFieldEffectArguments[1], &gFieldEffectArguments[2]);
    FieldEffectStart(FLDEFF_EXCLAMATION_MARK_ICON);
    sprite->data[2] = 1;
    return TRUE;
}

bool8 MovementAction_EmoteQuestionMark_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    EventObjectGetLocalIdAndMap(eventObject, &gFieldEffectArguments[0], &gFieldEffectArguments[1], &gFieldEffectArguments[2]);
    FieldEffectStart(FLDEFF_QUESTION_MARK_ICON);
    sprite->data[2] = 1;
    return TRUE;
}

bool8 MovementAction_EmoteHeart_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    EventObjectGetLocalIdAndMap(eventObject, &gFieldEffectArguments[0], &gFieldEffectArguments[1], &gFieldEffectArguments[2]);
    FieldEffectStart(FLDEFF_HEART_ICON);
    sprite->data[2] = 1;
    return TRUE;
}

bool8 MovementAction_RevealTrainer_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (eventObject->movementType == MOVEMENT_TYPE_HIDDEN)
    {
        sub_80B4578(eventObject);
        return FALSE;
    }
    if (eventObject->movementType != MOVEMENT_TYPE_TREE_DISGUISE && eventObject->movementType != MOVEMENT_TYPE_MOUNTAIN_DISGUISE)
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    sub_8155D78(eventObject);
    sprite->data[2] = 1;
    return MovementAction_RevealTrainer_Step1(eventObject, sprite);
}

bool8 MovementAction_RevealTrainer_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (sub_8155DA0(eventObject))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_RockSmashBreak_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    SetAndStartSpriteAnim(sprite, 1, 0);
    sprite->data[2] = 1;
    return FALSE;
}

bool8 MovementAction_RockSmashBreak_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (SpriteAnimEnded(sprite))
    {
        SetMovementDelay(sprite, 32);
        sprite->data[2] = 2;
    }
    return FALSE;
}

bool8 MovementAction_RockSmashBreak_Step2(struct EventObject *eventObject, struct Sprite *sprite)
{
    eventObject->invisible ^= TRUE;
    if (WaitForMovementDelay(sprite))
    {
        eventObject->invisible = TRUE;
        sprite->data[2] = 3;
    }
    return FALSE;
}

bool8 MovementAction_CutTree_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    SetAndStartSpriteAnim(sprite, 1, 0);
    sprite->data[2] = 1;
    return FALSE;
}

bool8 MovementAction_CutTree_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (SpriteAnimEnded(sprite))
    {
        SetMovementDelay(sprite, 32);
        sprite->data[2] = 2;
    }
    return FALSE;
}

bool8 MovementAction_CutTree_Step2(struct EventObject *eventObject, struct Sprite *sprite)
{
    eventObject->invisible ^= TRUE;
    if (WaitForMovementDelay(sprite))
    {
        eventObject->invisible = TRUE;
        sprite->data[2] = 3;
    }
    return FALSE;
}

bool8 MovementAction_SetFixedPriority_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    eventObject->fixedPriority = TRUE;
    sprite->data[2] = 1;
    return TRUE;
}

bool8 MovementAction_ClearFixedPriority_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    eventObject->fixedPriority = FALSE;
    sprite->data[2] = 1;
    return TRUE;
}

bool8 MovementAction_InitAffineAnim_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sprite->oam.affineMode = ST_OAM_AFFINE_DOUBLE;
    InitSpriteAffineAnim(sprite);
    sprite->affineAnimPaused = TRUE;
    sprite->subspriteMode = 0;
    return TRUE;
}

bool8 MovementAction_ClearAffineAnim_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    FreeOamMatrix(sprite->oam.matrixNum);
    sprite->oam.affineMode = ST_OAM_AFFINE_OFF;
    CalcCenterToCornerVec(sprite, sprite->oam.shape, sprite->oam.size, sprite->oam.affineMode);
    return TRUE;
}

bool8 MovementAction_Unknown1_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    eventObject->unk3_3 = TRUE;
    return TRUE;
}

bool8 MovementAction_Unknown2_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    eventObject->unk3_3 = FALSE;
    return TRUE;
}

bool8 MovementAction_WalkDownStartAffine_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8093B60(eventObject, sprite, DIR_SOUTH);
    sprite->affineAnimPaused = FALSE;
    StartSpriteAffineAnimIfDifferent(sprite, 0);
    return MovementAction_WalkDownStartAffine_Step1(eventObject, sprite);
}

bool8 MovementAction_WalkDownStartAffine_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (an_walk_any_2(eventObject, sprite))
    {
        sprite->affineAnimPaused = TRUE;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_WalkDownAffine_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8093B60(eventObject, sprite, DIR_SOUTH);
    sprite->affineAnimPaused = FALSE;
    ChangeSpriteAffineAnimIfDifferent(sprite, 1);
    return MovementAction_WalkDownAffine_Step1(eventObject, sprite);
}

bool8 MovementAction_WalkDownAffine_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (an_walk_any_2(eventObject, sprite))
    {
        sprite->affineAnimPaused = TRUE;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_WalkLeftAffine_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    do_go_anim(eventObject, sprite, DIR_WEST, 1);
    sprite->affineAnimPaused = FALSE;
    ChangeSpriteAffineAnimIfDifferent(sprite, 2);
    return MovementAction_WalkLeftAffine_Step1(eventObject, sprite);
}

bool8 MovementAction_WalkLeftAffine_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (npc_obj_ministep_stop_on_arrival(eventObject, sprite))
    {
        sprite->affineAnimPaused = TRUE;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_WalkRightAffine_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    do_go_anim(eventObject, sprite, DIR_EAST, 1);
    sprite->affineAnimPaused = FALSE;
    ChangeSpriteAffineAnimIfDifferent(sprite, 3);
    return MovementAction_WalkRightAffine_Step1(eventObject, sprite);
}

bool8 MovementAction_WalkRightAffine_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (npc_obj_ministep_stop_on_arrival(eventObject, sprite))
    {
        sprite->affineAnimPaused = TRUE;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

static void sub_80958C0(struct EventObject *eventObject, struct Sprite *sprite, u8 direction)
{
    SetEventObjectDirection(eventObject, direction);
    ShiftStillEventObjectCoords(eventObject);
    obj_npc_animation_step(eventObject, sprite, GetAcroWheeliePedalDirectionAnimNum(direction));
    sprite->animPaused = TRUE;
    sprite->data[2] = 1;
}

bool8 MovementAction_AcroWheelieFaceDown_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_80958C0(eventObject, sprite, DIR_SOUTH);
    return TRUE;
}

bool8 MovementAction_AcroWheelieFaceUp_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_80958C0(eventObject, sprite, DIR_NORTH);
    return TRUE;
}

bool8 MovementAction_AcroWheelieFaceLeft_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_80958C0(eventObject, sprite, DIR_WEST);
    return TRUE;
}

bool8 MovementAction_AcroWheelieFaceRight_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_80958C0(eventObject, sprite, DIR_EAST);
    return TRUE;
}

bool8 MovementAction_AcroPopWheelieDown_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    StartSpriteAnimInDirection(eventObject, sprite, DIR_SOUTH, GetAcroWheelieDirectionAnimNum(DIR_SOUTH));
    return FALSE;
}

bool8 MovementAction_AcroPopWheelieUp_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    StartSpriteAnimInDirection(eventObject, sprite, DIR_NORTH, GetAcroWheelieDirectionAnimNum(DIR_NORTH));
    return FALSE;
}

bool8 MovementAction_AcroPopWheelieLeft_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    StartSpriteAnimInDirection(eventObject, sprite, DIR_WEST, GetAcroWheelieDirectionAnimNum(DIR_WEST));
    return FALSE;
}

bool8 MovementAction_AcroPopWheelieRight_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    StartSpriteAnimInDirection(eventObject, sprite, DIR_EAST, GetAcroWheelieDirectionAnimNum(DIR_EAST));
    return FALSE;
}

bool8 MovementAction_AcroEndWheelieFaceDown_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    StartSpriteAnimInDirection(eventObject, sprite, DIR_SOUTH, GetAcroEndWheelieDirectionAnimNum(DIR_SOUTH));
    return FALSE;
}

bool8 MovementAction_AcroEndWheelieFaceUp_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    StartSpriteAnimInDirection(eventObject, sprite, DIR_NORTH, GetAcroEndWheelieDirectionAnimNum(DIR_NORTH));
    return FALSE;
}

bool8 MovementAction_AcroEndWheelieFaceLeft_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    StartSpriteAnimInDirection(eventObject, sprite, DIR_WEST, GetAcroEndWheelieDirectionAnimNum(DIR_WEST));
    return FALSE;
}

bool8 MovementAction_AcroEndWheelieFaceRight_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    StartSpriteAnimInDirection(eventObject, sprite, DIR_EAST, GetAcroEndWheelieDirectionAnimNum(DIR_EAST));
    return FALSE;
}

bool8 MovementAction_UnusedAcroActionDown_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    StartSpriteAnimInDirection(eventObject, sprite, DIR_SOUTH, GetAcroUnusedActionDirectionAnimNum(DIR_SOUTH));
    return FALSE;
}

bool8 MovementAction_UnusedAcroActionUp_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    StartSpriteAnimInDirection(eventObject, sprite, DIR_NORTH, GetAcroUnusedActionDirectionAnimNum(DIR_NORTH));
    return FALSE;
}

bool8 MovementAction_UnusedAcroActionLeft_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    StartSpriteAnimInDirection(eventObject, sprite, DIR_WEST, GetAcroUnusedActionDirectionAnimNum(DIR_WEST));
    return FALSE;
}

bool8 MovementAction_UnusedAcroActionRight_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    StartSpriteAnimInDirection(eventObject, sprite, DIR_EAST, GetAcroUnusedActionDirectionAnimNum(DIR_EAST));
    return FALSE;
}

void sub_8095AF0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8097750(sprite);
    sprite->animPaused = FALSE;
}

bool8 sub_8095B0C(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (sub_8097758(sprite))
    {
        ShiftStillEventObjectCoords(eventObject);
        eventObject->triggerGroundEffectsOnStop = TRUE;
        sprite->animPaused = TRUE;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_Figure8_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8095AF0(eventObject, sprite);
    sprite->data[2] = 1;
    return MovementAction_Figure8_Step1(eventObject, sprite);
}

bool8 MovementAction_Figure8_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (sub_8095B0C(eventObject, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

void sub_8095B84(struct EventObject *eventObject, struct Sprite *sprite, u8 direction, u8 speed, u8 a4)
{
    sub_8093FC4(eventObject, sprite, direction, speed, a4);
    StartSpriteAnimIfDifferent(sprite, GetAcroWheelieDirectionAnimNum(direction));
    DoShadowFieldEffect(eventObject);
}

bool8 MovementAction_AcroWheelieHopFaceDown_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8095B84(eventObject, sprite, DIR_SOUTH, 0, 1);
    return MovementAction_AcroWheelieHopFaceDown_Step1(eventObject, sprite);
}

bool8 MovementAction_AcroWheelieHopFaceDown_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (sub_80941B0(eventObject, sprite))
    {
        eventObject->hasShadow = FALSE;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_AcroWheelieHopFaceUp_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8095B84(eventObject, sprite, DIR_NORTH, 0, 1);
    return MovementAction_AcroWheelieHopFaceUp_Step1(eventObject, sprite);
}

bool8 MovementAction_AcroWheelieHopFaceUp_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (sub_80941B0(eventObject, sprite))
    {
        eventObject->hasShadow = FALSE;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_AcroWheelieHopFaceLeft_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8095B84(eventObject, sprite, DIR_WEST,  0, 1);
    return MovementAction_AcroWheelieHopFaceLeft_Step1(eventObject, sprite);
}

bool8 MovementAction_AcroWheelieHopFaceLeft_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (sub_80941B0(eventObject, sprite))
    {
        eventObject->hasShadow = FALSE;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_AcroWheelieHopFaceRight_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8095B84(eventObject, sprite, DIR_EAST,  0, 1);
    return MovementAction_AcroWheelieHopFaceRight_Step1(eventObject, sprite);
}

bool8 MovementAction_AcroWheelieHopFaceRight_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (sub_80941B0(eventObject, sprite))
    {
        eventObject->hasShadow = FALSE;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_AcroWheelieHopDown_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8095B84(eventObject, sprite, DIR_SOUTH, 1, 1);
    return MovementAction_AcroWheelieHopDown_Step1(eventObject, sprite);
}

bool8 MovementAction_AcroWheelieHopDown_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (sub_80941B0(eventObject, sprite))
    {
        eventObject->hasShadow = FALSE;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_AcroWheelieHopUp_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8095B84(eventObject, sprite, DIR_NORTH, 1, 1);
    return MovementAction_AcroWheelieHopUp_Step1(eventObject, sprite);
}

bool8 MovementAction_AcroWheelieHopUp_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (sub_80941B0(eventObject, sprite))
    {
        eventObject->hasShadow = FALSE;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_AcroWheelieHopLeft_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8095B84(eventObject, sprite, DIR_WEST,  1, 1);
    return MovementAction_AcroWheelieHopLeft_Step1(eventObject, sprite);
}

bool8 MovementAction_AcroWheelieHopLeft_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (sub_80941B0(eventObject, sprite))
    {
        eventObject->hasShadow = FALSE;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_AcroWheelieHopRight_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8095B84(eventObject, sprite, DIR_EAST,  1, 1);
    return MovementAction_AcroWheelieHopRight_Step1(eventObject, sprite);
}

bool8 MovementAction_AcroWheelieHopRight_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (sub_80941B0(eventObject, sprite))
    {
        eventObject->hasShadow = FALSE;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_AcroWheelieJumpDown_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8095B84(eventObject, sprite, DIR_SOUTH, 2, 0);
    return MovementAction_AcroWheelieJumpDown_Step1(eventObject, sprite);
}

bool8 MovementAction_AcroWheelieJumpDown_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (sub_80941B0(eventObject, sprite))
    {
        eventObject->hasShadow = FALSE;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_AcroWheelieJumpUp_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8095B84(eventObject, sprite, DIR_NORTH, 2, 0);
    return MovementAction_AcroWheelieJumpUp_Step1(eventObject, sprite);
}

bool8 MovementAction_AcroWheelieJumpUp_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (sub_80941B0(eventObject, sprite))
    {
        eventObject->hasShadow = FALSE;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_AcroWheelieJumpLeft_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8095B84(eventObject, sprite, DIR_WEST,  2, 0);
    return MovementAction_AcroWheelieJumpLeft_Step1(eventObject, sprite);
}

bool8 MovementAction_AcroWheelieJumpLeft_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (sub_80941B0(eventObject, sprite))
    {
        eventObject->hasShadow = FALSE;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_AcroWheelieJumpRight_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8095B84(eventObject, sprite, DIR_EAST,  2, 0);
    return MovementAction_AcroWheelieJumpRight_Step1(eventObject, sprite);
}

bool8 MovementAction_AcroWheelieJumpRight_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (sub_80941B0(eventObject, sprite))
    {
        eventObject->hasShadow = FALSE;
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_AcroWheelieInPlaceDown_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8094554(eventObject, sprite, DIR_SOUTH, GetAcroWheeliePedalDirectionAnimNum(DIR_SOUTH), 8);
    return MovementAction_WalkInPlace_Step1(eventObject, sprite);
}

bool8 MovementAction_AcroWheelieInPlaceUp_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8094554(eventObject, sprite, DIR_NORTH, GetAcroWheeliePedalDirectionAnimNum(DIR_NORTH), 8);
    return MovementAction_WalkInPlace_Step1(eventObject, sprite);
}

bool8 MovementAction_AcroWheelieInPlaceLeft_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8094554(eventObject, sprite, DIR_WEST, GetAcroWheeliePedalDirectionAnimNum(DIR_WEST), 8);
    return MovementAction_WalkInPlace_Step1(eventObject, sprite);
}

bool8 MovementAction_AcroWheelieInPlaceRight_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8094554(eventObject, sprite, DIR_EAST, GetAcroWheeliePedalDirectionAnimNum(DIR_EAST), 8);
    return MovementAction_WalkInPlace_Step1(eventObject, sprite);
}

void sub_80960C8(struct EventObject *eventObject, struct Sprite *sprite, u8 direction, u8 speed)
{
    npc_apply_direction(eventObject, sprite, direction, speed);
    StartSpriteAnim(sprite, GetAcroWheelieDirectionAnimNum(eventObject->facingDirection));
    SeekSpriteAnim(sprite, 0);
}

bool8 MovementAction_AcroPopWheelieMoveDown_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_80960C8(eventObject, sprite, DIR_SOUTH, 1);
    return MovementAction_AcroPopWheelieMoveDown_Step1(eventObject, sprite);
}

bool8 MovementAction_AcroPopWheelieMoveDown_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (npc_obj_ministep_stop_on_arrival(eventObject, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_AcroPopWheelieMoveUp_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_80960C8(eventObject, sprite, DIR_NORTH, 1);
    return MovementAction_AcroPopWheelieMoveUp_Step1(eventObject, sprite);
}

bool8 MovementAction_AcroPopWheelieMoveUp_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (npc_obj_ministep_stop_on_arrival(eventObject, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_AcroPopWheelieMoveLeft_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_80960C8(eventObject, sprite, DIR_WEST,  1);
    return MovementAction_AcroPopWheelieMoveLeft_Step1(eventObject, sprite);
}

bool8 MovementAction_AcroPopWheelieMoveLeft_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (npc_obj_ministep_stop_on_arrival(eventObject, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_AcroPopWheelieMoveRight_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_80960C8(eventObject, sprite, DIR_EAST,  1);
    return MovementAction_AcroPopWheelieMoveRight_Step1(eventObject, sprite);
}

bool8 MovementAction_AcroPopWheelieMoveRight_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (npc_obj_ministep_stop_on_arrival(eventObject, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

void sub_8096200(struct EventObject *eventObject, struct Sprite *sprite, u8 direction, u8 speed)
{
    npc_apply_direction(eventObject, sprite, direction, speed);
    npc_apply_anim_looping(eventObject, sprite, GetAcroWheeliePedalDirectionAnimNum(eventObject->facingDirection));
}

bool8 MovementAction_AcroWheelieMoveDown_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8096200(eventObject, sprite, DIR_SOUTH, 1);
    return MovementAction_AcroWheelieMoveDown_Step1(eventObject, sprite);
}

bool8 MovementAction_AcroWheelieMoveDown_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (npc_obj_ministep_stop_on_arrival(eventObject, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_AcroWheelieMoveUp_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8096200(eventObject, sprite, DIR_NORTH, 1);
    return MovementAction_AcroWheelieMoveUp_Step1(eventObject, sprite);
}

bool8 MovementAction_AcroWheelieMoveUp_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (npc_obj_ministep_stop_on_arrival(eventObject, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_AcroWheelieMoveLeft_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8096200(eventObject, sprite, DIR_WEST,  1);
    return MovementAction_AcroWheelieMoveLeft_Step1(eventObject, sprite);
}

bool8 MovementAction_AcroWheelieMoveLeft_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (npc_obj_ministep_stop_on_arrival(eventObject, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_AcroWheelieMoveRight_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8096200(eventObject, sprite, DIR_EAST, 1);
    return MovementAction_AcroWheelieMoveRight_Step1(eventObject, sprite);
}

bool8 MovementAction_AcroWheelieMoveRight_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (npc_obj_ministep_stop_on_arrival(eventObject, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

void sub_8096330(struct EventObject *eventObject, struct Sprite *sprite, u8 direction, u8 speed)
{
    npc_apply_direction(eventObject, sprite, direction, speed);
    StartSpriteAnim(sprite, GetAcroEndWheelieDirectionAnimNum(eventObject->facingDirection));
    SeekSpriteAnim(sprite, 0);
}

bool8 MovementAction_AcroEndWheelieMoveDown_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8096330(eventObject, sprite, DIR_SOUTH, 1);
    return MovementAction_AcroEndWheelieMoveDown_Step1(eventObject, sprite);
}

bool8 MovementAction_AcroEndWheelieMoveDown_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (npc_obj_ministep_stop_on_arrival(eventObject, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_AcroEndWheelieMoveUp_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8096330(eventObject, sprite, DIR_NORTH, 1);
    return MovementAction_AcroEndWheelieMoveUp_Step1(eventObject, sprite);
}

bool8 MovementAction_AcroEndWheelieMoveUp_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (npc_obj_ministep_stop_on_arrival(eventObject, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_AcroEndWheelieMoveLeft_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8096330(eventObject, sprite, DIR_WEST, 1);
    return MovementAction_AcroEndWheelieMoveLeft_Step1(eventObject, sprite);
}

bool8 MovementAction_AcroEndWheelieMoveLeft_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (npc_obj_ministep_stop_on_arrival(eventObject, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_AcroEndWheelieMoveRight_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8096330(eventObject, sprite, DIR_EAST, 1);
    return MovementAction_AcroEndWheelieMoveRight_Step1(eventObject, sprite);
}

bool8 MovementAction_AcroEndWheelieMoveRight_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (npc_obj_ministep_stop_on_arrival(eventObject, sprite))
    {
        sprite->data[2] = 2;
        return TRUE;
    }
    return FALSE;
}

bool8 MovementAction_Levitate_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    CreateLevitateMovementTask(eventObject);
    sprite->data[2] = 1;
    return TRUE;
}

bool8 MovementAction_StopLevitate_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    DestroyExtraMovementTask(eventObject->warpArrowSpriteId);
    sprite->pos2.y = 0;
    sprite->data[2] = 1;
    return TRUE;
}

bool8 MovementAction_DestroyExtraTaskIfAtTop_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (sprite->pos2.y == 0)
    {
        DestroyExtraMovementTask(eventObject->warpArrowSpriteId);
        sprite->data[2] = 1;
        return TRUE;
    }
    return FALSE;
}

u8 MovementAction_Finish(struct EventObject *eventObject, struct Sprite *sprite)
{
    return TRUE;
}

bool8 MovementAction_PauseSpriteAnim(struct EventObject *eventObject, struct Sprite *sprite)
{
    sprite->animPaused = TRUE;
    return TRUE;
}

static void UpdateEventObjectSpriteAnimPause(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (eventObject->disableAnim)
    {
        sprite->animPaused = TRUE;
    }
}

static void TryEnableEventObjectAnim(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (eventObject->enableAnim)
    {
        sprite->animPaused = FALSE;
        eventObject->disableAnim = FALSE;
        eventObject->enableAnim = FALSE;
    }
}

static void UpdateEventObjectVisibility(struct EventObject *eventObject, struct Sprite *sprite)
{
    sub_8096530(eventObject, sprite);
    UpdateEventObjSpriteVisibility(eventObject, sprite);
}

static void sub_8096530(struct EventObject *eventObject, struct Sprite *sprite)
{
    u16 x, y;
    u16 x2, y2;
    const struct EventObjectGraphicsInfo *graphicsInfo;

    eventObject->offScreen = FALSE;
    graphicsInfo = GetEventObjectGraphicsInfo(eventObject->graphicsId);
    if (sprite->coordOffsetEnabled)
    {
        x = sprite->pos1.x + sprite->pos2.x + sprite->centerToCornerVecX + gSpriteCoordOffsetX;
        y = sprite->pos1.y + sprite->pos2.y + sprite->centerToCornerVecY + gSpriteCoordOffsetY;
    }
    else
    {
        x = sprite->pos1.x + sprite->pos2.x + sprite->centerToCornerVecX;
        y = sprite->pos1.y + sprite->pos2.y + sprite->centerToCornerVecY;
    }
    x2 = graphicsInfo->width;
    x2 += x;
    y2 = y;
    y2 += graphicsInfo->height;
    if ((s16)x >= 0x100 || (s16)x2 < -0x10)
    {
        eventObject->offScreen = TRUE;
    }
    if ((s16)y >= 0xB0 || (s16)y2 < -0x10)
    {
        eventObject->offScreen = TRUE;
    }
}

static void UpdateEventObjSpriteVisibility(struct EventObject *eventObject, struct Sprite *sprite)
{
    sprite->invisible = FALSE;
    if (eventObject->invisible || eventObject->offScreen)
    {
        sprite->invisible = TRUE;
    }
}

static void GetAllGroundEffectFlags_OnSpawn(struct EventObject *eventObj, u32 *flags)
{
    EventObjectUpdateMetatileBehaviors(eventObj);
    GetGroundEffectFlags_Reflection(eventObj, flags);
    GetGroundEffectFlags_TallGrassOnSpawn(eventObj, flags);
    GetGroundEffectFlags_LongGrassOnSpawn(eventObj, flags);
    GetGroundEffectFlags_SandHeap(eventObj, flags);
    GetGroundEffectFlags_ShallowFlowingWater(eventObj, flags);
    GetGroundEffectFlags_ShortGrass(eventObj, flags);
    GetGroundEffectFlags_HotSprings(eventObj, flags);
}

static void GetAllGroundEffectFlags_OnBeginStep(struct EventObject *eventObj, u32 *flags)
{
    EventObjectUpdateMetatileBehaviors(eventObj);
    GetGroundEffectFlags_Reflection(eventObj, flags);
    GetGroundEffectFlags_TallGrassOnBeginStep(eventObj, flags);
    GetGroundEffectFlags_LongGrassOnBeginStep(eventObj, flags);
    GetGroundEffectFlags_Tracks(eventObj, flags);
    GetGroundEffectFlags_SandHeap(eventObj, flags);
    GetGroundEffectFlags_ShallowFlowingWater(eventObj, flags);
    GetGroundEffectFlags_Puddle(eventObj, flags);
    GetGroundEffectFlags_ShortGrass(eventObj, flags);
    GetGroundEffectFlags_HotSprings(eventObj, flags);
}

static void GetAllGroundEffectFlags_OnFinishStep(struct EventObject *eventObj, u32 *flags)
{
    EventObjectUpdateMetatileBehaviors(eventObj);
    GetGroundEffectFlags_ShallowFlowingWater(eventObj, flags);
    GetGroundEffectFlags_SandHeap(eventObj, flags);
    GetGroundEffectFlags_Puddle(eventObj, flags);
    GetGroundEffectFlags_Ripple(eventObj, flags);
    GetGroundEffectFlags_ShortGrass(eventObj, flags);
    GetGroundEffectFlags_HotSprings(eventObj, flags);
    GetGroundEffectFlags_Seaweed(eventObj, flags);
    GetGroundEffectFlags_JumpLanding(eventObj, flags);
}

static void EventObjectUpdateMetatileBehaviors(struct EventObject *eventObj)
{
    eventObj->previousMetatileBehavior = MapGridGetMetatileBehaviorAt(eventObj->previousCoords.x, eventObj->previousCoords.y);
    eventObj->currentMetatileBehavior = MapGridGetMetatileBehaviorAt(eventObj->currentCoords.x, eventObj->currentCoords.y);
}

static void GetGroundEffectFlags_Reflection(struct EventObject *eventObj, u32 *flags)
{
    u32 reflectionFlags[2] = { GROUND_EFFECT_FLAG_REFLECTION, GROUND_EFFECT_FLAG_ICE_REFLECTION };
    u8 type = EventObjectCheckForReflectiveSurface(eventObj);

    if (type)
    {
        if (!eventObj->hasReflection)
        {
            eventObj->hasReflection = 0;
            eventObj->hasReflection = 1;
            *flags |= reflectionFlags[type - 1];
        }
    }
    else
    {
        eventObj->hasReflection = 0;
    }
}

static void GetGroundEffectFlags_TallGrassOnSpawn(struct EventObject *eventObj, u32 *flags)
{
    if (MetatileBehavior_IsTallGrass(eventObj->currentMetatileBehavior))
        *flags |= GROUND_EFFECT_FLAG_TALL_GRASS_ON_SPAWN;
}

static void GetGroundEffectFlags_TallGrassOnBeginStep(struct EventObject *eventObj, u32 *flags)
{
    if (MetatileBehavior_IsTallGrass(eventObj->currentMetatileBehavior))
        *flags |= GROUND_EFFECT_FLAG_TALL_GRASS_ON_MOVE;
}

static void GetGroundEffectFlags_LongGrassOnSpawn(struct EventObject *eventObj, u32 *flags)
{
    if (MetatileBehavior_IsLongGrass(eventObj->currentMetatileBehavior))
        *flags |= GROUND_EFFECT_FLAG_LONG_GRASS_ON_SPAWN;
}

static void GetGroundEffectFlags_LongGrassOnBeginStep(struct EventObject *eventObj, u32 *flags)
{
    if (MetatileBehavior_IsLongGrass(eventObj->currentMetatileBehavior))
        *flags |= GROUND_EFFECT_FLAG_LONG_GRASS_ON_MOVE;
}

static void GetGroundEffectFlags_Tracks(struct EventObject *eventObj, u32 *flags)
{
    if (MetatileBehavior_IsDeepSand(eventObj->previousMetatileBehavior))
    {
        *flags |= GROUND_EFFECT_FLAG_DEEP_SAND;
    }
    else if (MetatileBehavior_IsSandOrDeepSand(eventObj->previousMetatileBehavior)
             || MetatileBehavior_IsFootprints(eventObj->previousMetatileBehavior))
    {
        *flags |= GROUND_EFFECT_FLAG_SAND;
    }
}

static void GetGroundEffectFlags_SandHeap(struct EventObject *eventObj, u32 *flags)
{
    if (MetatileBehavior_IsDeepSand(eventObj->currentMetatileBehavior)
        && MetatileBehavior_IsDeepSand(eventObj->previousMetatileBehavior))
    {
        if (!eventObj->inSandPile)
        {
            eventObj->inSandPile = 0;
            eventObj->inSandPile = 1;
            *flags |= GROUND_EFFECT_FLAG_SAND_PILE;
        }
    }
    else
    {
        eventObj->inSandPile = 0;
    }
}

static void GetGroundEffectFlags_ShallowFlowingWater(struct EventObject *eventObj, u32 *flags)
{
    if ((MetatileBehavior_IsShallowFlowingWater(eventObj->currentMetatileBehavior)
         && MetatileBehavior_IsShallowFlowingWater(eventObj->previousMetatileBehavior))
        || (MetatileBehavior_IsPacifidlogLog(eventObj->currentMetatileBehavior)
            && MetatileBehavior_IsPacifidlogLog(eventObj->previousMetatileBehavior)))
    {
        if (!eventObj->inShallowFlowingWater)
        {
            eventObj->inShallowFlowingWater = 0;
            eventObj->inShallowFlowingWater = 1;
            *flags |= GROUND_EFFECT_FLAG_SHALLOW_FLOWING_WATER;
        }
    }
    else
    {
        eventObj->inShallowFlowingWater = 0;
    }
}

static void GetGroundEffectFlags_Puddle(struct EventObject *eventObj, u32 *flags)
{
    if (MetatileBehavior_IsPuddle(eventObj->currentMetatileBehavior)
        && MetatileBehavior_IsPuddle(eventObj->previousMetatileBehavior))
    {
        *flags |= GROUND_EFFECT_FLAG_PUDDLE;
    }
}

static void GetGroundEffectFlags_Ripple(struct EventObject *eventObj, u32 *flags)
{
    if (MetatileBehavior_HasRipples(eventObj->currentMetatileBehavior))
        *flags |= GROUND_EFFECT_FLAG_RIPPLES;
}

static void GetGroundEffectFlags_ShortGrass(struct EventObject *eventObj, u32 *flags)
{
    if (MetatileBehavior_IsShortGrass(eventObj->currentMetatileBehavior)
        && MetatileBehavior_IsShortGrass(eventObj->previousMetatileBehavior))
    {
        if (!eventObj->inShortGrass)
        {
            eventObj->inShortGrass = 0;
            eventObj->inShortGrass = 1;
            *flags |= GROUND_EFFECT_FLAG_SHORT_GRASS;
        }
    }
    else
    {
        eventObj->inShortGrass = 0;
    }
}

static void GetGroundEffectFlags_HotSprings(struct EventObject *eventObj, u32 *flags)
{
    if (MetatileBehavior_IsHotSprings(eventObj->currentMetatileBehavior)
        && MetatileBehavior_IsHotSprings(eventObj->previousMetatileBehavior))
    {
        if (!eventObj->inHotSprings)
        {
            eventObj->inHotSprings = 0;
            eventObj->inHotSprings = 1;
            *flags |= GROUND_EFFECT_FLAG_HOT_SPRINGS;
        }
    }
    else
    {
        eventObj->inHotSprings = 0;
    }
}

static void GetGroundEffectFlags_Seaweed(struct EventObject *eventObj, u32 *flags)
{
    if (MetatileBehavior_IsSeaweed(eventObj->currentMetatileBehavior))
        *flags |= GROUND_EFFECT_FLAG_SEAWEED;
}

static void GetGroundEffectFlags_JumpLanding(struct EventObject *eventObj, u32 *flags)
{
    typedef bool8 (*MetatileFunc)(u8);

    static const MetatileFunc metatileFuncs[] = {
        MetatileBehavior_IsTallGrass,
        MetatileBehavior_IsLongGrass,
        MetatileBehavior_IsPuddle,
        MetatileBehavior_IsSurfableWaterOrUnderwater,
        MetatileBehavior_IsShallowFlowingWater,
        MetatileBehavior_IsATile,
    };

    static const u32 jumpLandingFlags[] = {
        GROUND_EFFECT_FLAG_LAND_IN_TALL_GRASS,
        GROUND_EFFECT_FLAG_LAND_IN_LONG_GRASS,
        GROUND_EFFECT_FLAG_LAND_IN_SHALLOW_WATER,
        GROUND_EFFECT_FLAG_LAND_IN_DEEP_WATER,
        GROUND_EFFECT_FLAG_LAND_IN_SHALLOW_WATER,
        GROUND_EFFECT_FLAG_LAND_ON_NORMAL_GROUND,
    };

    if (eventObj->landingJump && !eventObj->disableJumpLandingGroundEffect)
    {
        u8 i;

        for (i = 0; i < ARRAY_COUNT(metatileFuncs); i++)
        {
            if (metatileFuncs[i](eventObj->currentMetatileBehavior))
            {
                *flags |= jumpLandingFlags[i];
                return;
            }
        }
    }
}

static u8 EventObjectCheckForReflectiveSurface(struct EventObject *eventObj)
{
    const struct EventObjectGraphicsInfo *info = GetEventObjectGraphicsInfo(eventObj->graphicsId);

    // ceil div by tile width?
    s16 width = (info->width + 8) >> 4;
    s16 height = (info->height + 8) >> 4;
    s16 i;
    s16 j;
    u8 result;
    u8 b;
    s16 one;

#define RETURN_REFLECTION_TYPE_AT(x, y)              \
    b = MapGridGetMetatileBehaviorAt(x, y);          \
    result = GetReflectionTypeByMetatileBehavior(b); \
    if (result != 0)                                 \
        return result;

    for (i = 0, one = 1; i < height; i++)
    {
        RETURN_REFLECTION_TYPE_AT(eventObj->currentCoords.x, eventObj->currentCoords.y + one + i)
        RETURN_REFLECTION_TYPE_AT(eventObj->previousCoords.x, eventObj->previousCoords.y + one + i)
        for (j = 1; j < width; j++)
        {
            RETURN_REFLECTION_TYPE_AT(eventObj->currentCoords.x + j, eventObj->currentCoords.y + one + i)
            RETURN_REFLECTION_TYPE_AT(eventObj->currentCoords.x - j, eventObj->currentCoords.y + one + i)
            RETURN_REFLECTION_TYPE_AT(eventObj->previousCoords.x + j, eventObj->previousCoords.y + one + i)
            RETURN_REFLECTION_TYPE_AT(eventObj->previousCoords.x - j, eventObj->previousCoords.y + one + i)
        }
    }
    return 0;

#undef RETURN_REFLECTION_TYPE_AT
}

static u8 GetReflectionTypeByMetatileBehavior(u32 behavior)
{
    if (MetatileBehavior_IsIce(behavior))
        return 1;
    else if (MetatileBehavior_IsReflective(behavior))
        return 2;
    else
        return 0;
}

u8 GetLedgeJumpDirection(s16 x, s16 y, u8 z)
{
    static bool8 (*const unknown_08376040[])(u8) = {
        MetatileBehavior_IsJumpSouth,
        MetatileBehavior_IsJumpNorth,
        MetatileBehavior_IsJumpWest,
        MetatileBehavior_IsJumpEast,
    };

    u8 b;
    u8 index = z;

    if (index == 0)
        return 0;
    else if (index > 4)
        index -= 4;

    index--;
    b = MapGridGetMetatileBehaviorAt(x, y);

    if (unknown_08376040[index](b) == 1)
        return index + 1;

    return 0;
}

static void SetEventObjectSpriteOamTableForLongGrass(struct EventObject *eventObj, struct Sprite *sprite)
{
    if (eventObj->disableCoveringGroundEffects)
        return;

    if (!MetatileBehavior_IsLongGrass(eventObj->currentMetatileBehavior))
        return;

    if (!MetatileBehavior_IsLongGrass(eventObj->previousMetatileBehavior))
        return;

    sprite->subspriteTableNum = 4;

    if (ZCoordToPriority(eventObj->previousElevation) == 1)
        sprite->subspriteTableNum = 5;
}

bool8 IsZCoordMismatchAt(u8 z, s16 x, s16 y)
{
    u8 mapZ;

    if (z == 0)
        return FALSE;

    mapZ = MapGridGetZCoordAt(x, y);

    if (mapZ == 0 || mapZ == 0xF)
        return FALSE;

    if (mapZ != z)
        return TRUE;

    return FALSE;
}

static const u8 sUnknown_08376050[] = {
    0x73, 0x73, 0x53, 0x73, 0x53, 0x73, 0x53, 0x73, 0x53, 0x73, 0x53, 0x73, 0x53, 0x00, 0x00, 0x73
};

// Each byte corresponds to a sprite priority for an event object.
// This is directly the inverse of gEventObjectPriorities_08376070.
static const u8 sEventObjectPriorities_08376060[] = {
    2, 2, 2, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 0, 0, 2
};

// Each byte corresponds to a sprite priority for an event object.
// This is the inverse of gEventObjectPriorities_08376060.
// 1 = Above player sprite
// 2 = Below player sprite
static const u8 sEventObjectPriorities_08376070[] = {
    1, 1, 1, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 0, 0, 1,
};

void UpdateEventObjectZCoordAndPriority(struct EventObject *eventObj, struct Sprite *sprite)
{
    if (eventObj->fixedPriority)
        return;

    EventObjectUpdateZCoord(eventObj);

    sprite->subspriteTableNum = sEventObjectPriorities_08376070[eventObj->previousElevation];
    sprite->oam.priority = sEventObjectPriorities_08376060[eventObj->previousElevation];
}

static void InitObjectPriorityByZCoord(struct Sprite *sprite, u8 z)
{
    sprite->subspriteTableNum = sEventObjectPriorities_08376070[z];
    sprite->oam.priority = sEventObjectPriorities_08376060[z];
}

u8 ZCoordToPriority(u8 z)
{
    return sEventObjectPriorities_08376060[z];
}

void EventObjectUpdateZCoord(struct EventObject *eventObj)
{
    u8 z = MapGridGetZCoordAt(eventObj->currentCoords.x, eventObj->currentCoords.y);
    u8 z2 = MapGridGetZCoordAt(eventObj->previousCoords.x, eventObj->previousCoords.y);

    if (z == 0xF || z2 == 0xF)
        return;

    eventObj->currentElevation = z;

    if (z != 0 && z != 0xF)
        eventObj->previousElevation = z;
}

void SetObjectSubpriorityByZCoord(u8 a, struct Sprite *sprite, u8 b)
{
    s32 tmp = sprite->centerToCornerVecY;
    u32 tmpa = *(u16 *)&sprite->pos1.y;
    u32 tmpb = *(u16 *)&gSpriteCoordOffsetY;
    s32 tmp2 = (tmpa - tmp) + tmpb;
    u16 tmp3 = (0x10 - ((((u32)tmp2 + 8) & 0xFF) >> 4)) * 2;
    sprite->subpriority = tmp3 + sUnknown_08376050[a] + b;
}

static void EventObjectUpdateSubpriority(struct EventObject *eventObj, struct Sprite *sprite)
{
    if (eventObj->fixedPriority)
        return;

    SetObjectSubpriorityByZCoord(eventObj->previousElevation, sprite, 1);
}

bool8 AreZCoordsCompatible(u8 a, u8 b)
{
    if (a == 0 || b == 0)
        return TRUE;

    if (a != b)
        return FALSE;

    return TRUE;
}

void GroundEffect_SpawnOnTallGrass(struct EventObject *eventObj, struct Sprite *sprite)
{
    gFieldEffectArguments[0] = eventObj->currentCoords.x;
    gFieldEffectArguments[1] = eventObj->currentCoords.y;
    gFieldEffectArguments[2] = eventObj->previousElevation;
    gFieldEffectArguments[3] = 2;
    gFieldEffectArguments[4] = eventObj->localId << 8 | eventObj->mapNum;
    gFieldEffectArguments[5] = eventObj->mapGroup;
    gFieldEffectArguments[6] = (u8)gSaveBlock1Ptr->location.mapNum << 8 | (u8)gSaveBlock1Ptr->location.mapGroup;
    gFieldEffectArguments[7] = 1;
    FieldEffectStart(FLDEFF_TALL_GRASS);
}

void GroundEffect_StepOnTallGrass(struct EventObject *eventObj, struct Sprite *sprite)
{
    gFieldEffectArguments[0] = eventObj->currentCoords.x;
    gFieldEffectArguments[1] = eventObj->currentCoords.y;
    gFieldEffectArguments[2] = eventObj->previousElevation;
    gFieldEffectArguments[3] = 2;
    gFieldEffectArguments[4] = eventObj->localId << 8 | eventObj->mapNum;
    gFieldEffectArguments[5] = eventObj->mapGroup;
    gFieldEffectArguments[6] = (u8)gSaveBlock1Ptr->location.mapNum << 8 | (u8)gSaveBlock1Ptr->location.mapGroup;
    gFieldEffectArguments[7] = 0;
    FieldEffectStart(FLDEFF_TALL_GRASS);
}

void GroundEffect_SpawnOnLongGrass(struct EventObject *eventObj, struct Sprite *sprite)
{
    gFieldEffectArguments[0] = eventObj->currentCoords.x;
    gFieldEffectArguments[1] = eventObj->currentCoords.y;
    gFieldEffectArguments[2] = eventObj->previousElevation;
    gFieldEffectArguments[3] = 2;
    gFieldEffectArguments[4] = eventObj->localId << 8 | eventObj->mapNum;
    gFieldEffectArguments[5] = eventObj->mapGroup;
    gFieldEffectArguments[6] = (u8)gSaveBlock1Ptr->location.mapNum << 8 | (u8)gSaveBlock1Ptr->location.mapGroup;
    gFieldEffectArguments[7] = 1;
    FieldEffectStart(FLDEFF_LONG_GRASS);
}

void GroundEffect_StepOnLongGrass(struct EventObject *eventObj, struct Sprite *sprite)
{
    gFieldEffectArguments[0] = eventObj->currentCoords.x;
    gFieldEffectArguments[1] = eventObj->currentCoords.y;
    gFieldEffectArguments[2] = eventObj->previousElevation;
    gFieldEffectArguments[3] = 2;
    gFieldEffectArguments[4] = (eventObj->localId << 8) | eventObj->mapNum;
    gFieldEffectArguments[5] = eventObj->mapGroup;
    gFieldEffectArguments[6] = (u8)gSaveBlock1Ptr->location.mapNum << 8 | (u8)gSaveBlock1Ptr->location.mapGroup;
    gFieldEffectArguments[7] = 0;
    FieldEffectStart(FLDEFF_LONG_GRASS);
}

void GroundEffect_WaterReflection(struct EventObject *eventObj, struct Sprite *sprite)
{
    SetUpReflection(eventObj, sprite, FALSE);
}

void GroundEffect_IceReflection(struct EventObject *eventObj, struct Sprite *sprite)
{
    SetUpReflection(eventObj, sprite, TRUE);
}

void GroundEffect_FlowingWater(struct EventObject *eventObj, struct Sprite *sprite)
{
    StartFieldEffectForEventObject(FLDEFF_FEET_IN_FLOWING_WATER, eventObj);
}

static void (*const sGroundEffectTracksFuncs[])(struct EventObject *eventObj, struct Sprite *sprite, u8 a) = {
    DoTracksGroundEffect_None,
    DoTracksGroundEffect_Footprints,
    DoTracksGroundEffect_BikeTireTracks,
};

void GroundEffect_SandTracks(struct EventObject *eventObj, struct Sprite *sprite)
{
    const struct EventObjectGraphicsInfo *info = GetEventObjectGraphicsInfo(eventObj->graphicsId);
    sGroundEffectTracksFuncs[info->tracks](eventObj, sprite, 0);
}

void GroundEffect_DeepSandTracks(struct EventObject *eventObj, struct Sprite *sprite)
{
    const struct EventObjectGraphicsInfo *info = GetEventObjectGraphicsInfo(eventObj->graphicsId);
    sGroundEffectTracksFuncs[info->tracks](eventObj, sprite, 1);
}

static void DoTracksGroundEffect_None(struct EventObject *eventObj, struct Sprite *sprite, u8 a)
{
}

static void DoTracksGroundEffect_Footprints(struct EventObject *eventObj, struct Sprite *sprite, u8 a)
{
    // First half-word is a Field Effect script id. (gFieldEffectScriptPointers)
    u16 sandFootprints_FieldEffectData[2] = {
        FLDEFF_SAND_FOOTPRINTS,
        FLDEFF_DEEP_SAND_FOOTPRINTS
    };

    gFieldEffectArguments[0] = eventObj->previousCoords.x;
    gFieldEffectArguments[1] = eventObj->previousCoords.y;
    gFieldEffectArguments[2] = 149;
    gFieldEffectArguments[3] = 2;
    gFieldEffectArguments[4] = eventObj->facingDirection;
    FieldEffectStart(sandFootprints_FieldEffectData[a]);
}

static void DoTracksGroundEffect_BikeTireTracks(struct EventObject *eventObj, struct Sprite *sprite, u8 a)
{
    //  Specifies which bike track shape to show next.
    //  For example, when the bike turns from up to right, it will show
    //  a track that curves to the right.
    //  Each 4-byte row corresponds to the initial direction of the bike, and
    //  each byte in that row is for the next direction of the bike in the order
    //  of down, up, left, right.
    static const u8 bikeTireTracks_Transitions[4][4] = {
        1, 2, 7, 8,
        1, 2, 6, 5,
        5, 8, 3, 4,
        6, 7, 3, 4,
    };

    if (eventObj->currentCoords.x != eventObj->previousCoords.x || eventObj->currentCoords.y != eventObj->previousCoords.y)
    {
        gFieldEffectArguments[0] = eventObj->previousCoords.x;
        gFieldEffectArguments[1] = eventObj->previousCoords.y;
        gFieldEffectArguments[2] = 149;
        gFieldEffectArguments[3] = 2;
        gFieldEffectArguments[4] =
            bikeTireTracks_Transitions[eventObj->previousMovementDirection][eventObj->facingDirection - 5];
        FieldEffectStart(FLDEFF_BIKE_TIRE_TRACKS);
    }
}

void GroundEffect_Ripple(struct EventObject *eventObj, struct Sprite *sprite)
{
    DoRippleFieldEffect(eventObj, sprite);
}

void GroundEffect_StepOnPuddle(struct EventObject *eventObj, struct Sprite *sprite)
{
    StartFieldEffectForEventObject(FLDEFF_SPLASH, eventObj);
}

void GroundEffect_SandHeap(struct EventObject *eventObj, struct Sprite *sprite)
{
    StartFieldEffectForEventObject(FLDEFF_SAND_PILE, eventObj);
}

void GroundEffect_JumpOnTallGrass(struct EventObject *eventObj, struct Sprite *sprite)
{
    u8 spriteId;

    gFieldEffectArguments[0] = eventObj->currentCoords.x;
    gFieldEffectArguments[1] = eventObj->currentCoords.y;
    gFieldEffectArguments[2] = eventObj->previousElevation;
    gFieldEffectArguments[3] = 2;
    FieldEffectStart(FLDEFF_JUMP_TALL_GRASS);

    spriteId = FindTallGrassFieldEffectSpriteId(
        eventObj->localId,
        eventObj->mapNum,
        eventObj->mapGroup,
        eventObj->currentCoords.x,
        eventObj->currentCoords.y);

    if (spriteId == MAX_SPRITES)
        GroundEffect_SpawnOnTallGrass(eventObj, sprite);
}

void GroundEffect_JumpOnLongGrass(struct EventObject *eventObj, struct Sprite *sprite)
{
    gFieldEffectArguments[0] = eventObj->currentCoords.x;
    gFieldEffectArguments[1] = eventObj->currentCoords.y;
    gFieldEffectArguments[2] = eventObj->previousElevation;
    gFieldEffectArguments[3] = 2;
    FieldEffectStart(FLDEFF_JUMP_LONG_GRASS);
}

void GroundEffect_JumpOnShallowWater(struct EventObject *eventObj, struct Sprite *sprite)
{
    gFieldEffectArguments[0] = eventObj->currentCoords.x;
    gFieldEffectArguments[1] = eventObj->currentCoords.y;
    gFieldEffectArguments[2] = eventObj->previousElevation;
    gFieldEffectArguments[3] = sprite->oam.priority;
    FieldEffectStart(FLDEFF_JUMP_SMALL_SPLASH);
}

void GroundEffect_JumpOnWater(struct EventObject *eventObj, struct Sprite *sprite)
{
    gFieldEffectArguments[0] = eventObj->currentCoords.x;
    gFieldEffectArguments[1] = eventObj->currentCoords.y;
    gFieldEffectArguments[2] = eventObj->previousElevation;
    gFieldEffectArguments[3] = sprite->oam.priority;
    FieldEffectStart(FLDEFF_JUMP_BIG_SPLASH);
}

void GroundEffect_JumpLandingDust(struct EventObject *eventObj, struct Sprite *sprite)
{
    gFieldEffectArguments[0] = eventObj->currentCoords.x;
    gFieldEffectArguments[1] = eventObj->currentCoords.y;
    gFieldEffectArguments[2] = eventObj->previousElevation;
    gFieldEffectArguments[3] = sprite->oam.priority;
    FieldEffectStart(FLDEFF_DUST);
}

void GroundEffect_ShortGrass(struct EventObject *eventObj, struct Sprite *sprite)
{
    StartFieldEffectForEventObject(FLDEFF_SHORT_GRASS, eventObj);
}

void GroundEffect_HotSprings(struct EventObject *eventObj, struct Sprite *sprite)
{
    StartFieldEffectForEventObject(FLDEFF_HOT_SPRINGS_WATER, eventObj);
}

void GroundEffect_Seaweed(struct EventObject *eventObj, struct Sprite *sprite)
{
    gFieldEffectArguments[0] = eventObj->currentCoords.x;
    gFieldEffectArguments[1] = eventObj->currentCoords.y;
    FieldEffectStart(FLDEFF_BUBBLES);
}

static void (*const sGroundEffectFuncs[])(struct EventObject *eventObj, struct Sprite *sprite) = {
    GroundEffect_SpawnOnTallGrass,
    GroundEffect_StepOnTallGrass,
    GroundEffect_SpawnOnLongGrass,
    GroundEffect_StepOnLongGrass,
    GroundEffect_WaterReflection,
    GroundEffect_IceReflection,
    GroundEffect_FlowingWater,
    GroundEffect_SandTracks,
    GroundEffect_DeepSandTracks,
    GroundEffect_Ripple,
    GroundEffect_StepOnPuddle,
    GroundEffect_SandHeap,
    GroundEffect_JumpOnTallGrass,
    GroundEffect_JumpOnLongGrass,
    GroundEffect_JumpOnShallowWater,
    GroundEffect_JumpOnWater,
    GroundEffect_JumpLandingDust,
    GroundEffect_ShortGrass,
    GroundEffect_HotSprings,
    GroundEffect_Seaweed
};

static void DoFlaggedGroundEffects(struct EventObject *eventObj, struct Sprite *sprite, u32 flags)
{
    u8 i;

    if (EventObjectIsFarawayIslandMew(eventObj) == TRUE && !sub_81D4A58(eventObj))
        return;

    for (i = 0; i < ARRAY_COUNT(sGroundEffectFuncs); i++, flags >>= 1)
        if (flags & 1)
            sGroundEffectFuncs[i](eventObj, sprite);
}

void filters_out_some_ground_effects(struct EventObject *eventObj, u32 *flags)
{
    if (eventObj->disableCoveringGroundEffects)
    {
        eventObj->inShortGrass = 0;
        eventObj->inSandPile = 0;
        eventObj->inShallowFlowingWater = 0;
        eventObj->inHotSprings = 0;
        *flags &= ~(GROUND_EFFECT_FLAG_HOT_SPRINGS
                  | GROUND_EFFECT_FLAG_SHORT_GRASS
                  | GROUND_EFFECT_FLAG_SAND_PILE
                  | GROUND_EFFECT_FLAG_SHALLOW_FLOWING_WATER
                  | GROUND_EFFECT_FLAG_TALL_GRASS_ON_MOVE);
    }
}

void FilterOutStepOnPuddleGroundEffectIfJumping(struct EventObject *eventObj, u32 *flags)
{
    if (eventObj->landingJump)
        *flags &= ~GROUND_EFFECT_FLAG_PUDDLE;
}

static void DoGroundEffects_OnSpawn(struct EventObject *eventObj, struct Sprite *sprite)
{
    u32 flags;

    if (eventObj->triggerGroundEffectsOnMove)
    {
        flags = 0;
        UpdateEventObjectZCoordAndPriority(eventObj, sprite);
        GetAllGroundEffectFlags_OnSpawn(eventObj, &flags);
        SetEventObjectSpriteOamTableForLongGrass(eventObj, sprite);
        DoFlaggedGroundEffects(eventObj, sprite, flags);
        eventObj->triggerGroundEffectsOnMove = 0;
        eventObj->disableCoveringGroundEffects = 0;
    }
}

static void DoGroundEffects_OnBeginStep(struct EventObject *eventObj, struct Sprite *sprite)
{
    u32 flags;

    if (eventObj->triggerGroundEffectsOnMove)
    {
        flags = 0;
        UpdateEventObjectZCoordAndPriority(eventObj, sprite);
        GetAllGroundEffectFlags_OnBeginStep(eventObj, &flags);
        SetEventObjectSpriteOamTableForLongGrass(eventObj, sprite);
        filters_out_some_ground_effects(eventObj, &flags);
        DoFlaggedGroundEffects(eventObj, sprite, flags);
        eventObj->triggerGroundEffectsOnMove = 0;
        eventObj->disableCoveringGroundEffects = 0;
    }
}

static void DoGroundEffects_OnFinishStep(struct EventObject *eventObj, struct Sprite *sprite)
{
    u32 flags;

    if (eventObj->triggerGroundEffectsOnStop)
    {
        flags = 0;
        UpdateEventObjectZCoordAndPriority(eventObj, sprite);
        GetAllGroundEffectFlags_OnFinishStep(eventObj, &flags);
        SetEventObjectSpriteOamTableForLongGrass(eventObj, sprite);
        FilterOutStepOnPuddleGroundEffectIfJumping(eventObj, &flags);
        DoFlaggedGroundEffects(eventObj, sprite, flags);
        eventObj->triggerGroundEffectsOnStop = 0;
        eventObj->landingJump = 0;
    }
}

bool8 FreezeEventObject(struct EventObject *eventObject)
{
    if (eventObject->heldMovementActive || eventObject->frozen)
    {
        return TRUE;
    }
    else
    {
        eventObject->frozen = 1;
        eventObject->spriteAnimPausedBackup = gSprites[eventObject->spriteId].animPaused;
        eventObject->spriteAffineAnimPausedBackup = gSprites[eventObject->spriteId].affineAnimPaused;
        gSprites[eventObject->spriteId].animPaused = 1;
        gSprites[eventObject->spriteId].affineAnimPaused = 1;
        return FALSE;
    }
}

void FreezeEventObjects(void)
{
    u8 i;
    for (i = 0; i < EVENT_OBJECTS_COUNT; i++)
        if (gEventObjects[i].active && i != gPlayerAvatar.eventObjectId)
            FreezeEventObject(&gEventObjects[i]);
}

void FreezeEventObjectsExceptOne(u8 eventObjectId)
{
    u8 i;
    for (i = 0; i < EVENT_OBJECTS_COUNT; i++)
        if (i != eventObjectId && gEventObjects[i].active && i != gPlayerAvatar.eventObjectId)
            FreezeEventObject(&gEventObjects[i]);
}

void UnfreezeEventObject(struct EventObject *eventObject)
{
    if (eventObject->active && eventObject->frozen)
    {
        eventObject->frozen = 0;
        gSprites[eventObject->spriteId].animPaused = eventObject->spriteAnimPausedBackup;
        gSprites[eventObject->spriteId].affineAnimPaused = eventObject->spriteAffineAnimPausedBackup;
    }
}

void UnfreezeEventObjects(void)
{
    u8 i;
    for (i = 0; i < EVENT_OBJECTS_COUNT; i++)
        if (gEventObjects[i].active)
            UnfreezeEventObject(&gEventObjects[i]);
}

static void Step1(struct Sprite *sprite, u8 dir)
{
    sprite->pos1.x += sDirectionToVectors[dir].x;
    sprite->pos1.y += sDirectionToVectors[dir].y;
}

static void Step2(struct Sprite *sprite, u8 dir)
{
    sprite->pos1.x += 2 * (u16) sDirectionToVectors[dir].x;
    sprite->pos1.y += 2 * (u16) sDirectionToVectors[dir].y;
}

static void Step3(struct Sprite *sprite, u8 dir)
{
    sprite->pos1.x += 2 * (u16) sDirectionToVectors[dir].x + (u16) sDirectionToVectors[dir].x;
    sprite->pos1.y += 2 * (u16) sDirectionToVectors[dir].y + (u16) sDirectionToVectors[dir].y;
}

static void Step4(struct Sprite *sprite, u8 dir)
{
    sprite->pos1.x += 4 * (u16) sDirectionToVectors[dir].x;
    sprite->pos1.y += 4 * (u16) sDirectionToVectors[dir].y;
}

static void Step8(struct Sprite *sprite, u8 dir)
{
    sprite->pos1.x += 8 * (u16) sDirectionToVectors[dir].x;
    sprite->pos1.y += 8 * (u16) sDirectionToVectors[dir].y;
}

static void oamt_npc_ministep_reset(struct Sprite *sprite, u8 direction, u8 a3)
{
    sprite->data[3] = direction;
    sprite->data[4] = a3;
    sprite->data[5] = 0;
}

typedef void (*SpriteStepFunc)(struct Sprite *sprite, u8 direction);

static const SpriteStepFunc gUnknown_0850E6C4[] = {
    Step1,
    Step1,
    Step1,
    Step1,
    Step1,
    Step1,
    Step1,
    Step1,
    Step1,
    Step1,
    Step1,
    Step1,
    Step1,
    Step1,
    Step1,
    Step1,
};

static const SpriteStepFunc gUnknown_0850E704[] = {
    Step2,
    Step2,
    Step2,
    Step2,
    Step2,
    Step2,
    Step2,
    Step2,
};

static const SpriteStepFunc gUnknown_0850E724[] = {
    Step2,
    Step3,
    Step3,
    Step2,
    Step3,
    Step3,
};

static const SpriteStepFunc gUnknown_0850E73C[] = {
    Step4,
    Step4,
    Step4,
    Step4,
};

static const SpriteStepFunc gUnknown_0850E74C[] = {
    Step8,
    Step8,
};

static const SpriteStepFunc *const gUnknown_0850E754[] = {
    gUnknown_0850E6C4,
    gUnknown_0850E704,
    gUnknown_0850E724,
    gUnknown_0850E73C,
    gUnknown_0850E74C,
};

static const s16 gUnknown_0850E768[] = {
    16, 8, 6, 4, 2
};

bool8 obj_npc_ministep(struct Sprite *sprite)
{
    if (sprite->data[5] >= gUnknown_0850E768[sprite->data[4]])
        return FALSE;

    gUnknown_0850E754[sprite->data[4]][sprite->data[5]](sprite, sprite->data[3]);

    sprite->data[5]++;

    if (sprite->data[5] < gUnknown_0850E768[sprite->data[4]])
        return FALSE;

    return TRUE;
}

void sub_80976DC(struct Sprite *sprite, u8 direction)
{
    sprite->data[3] = direction;
    sprite->data[4] = 0;
    sprite->data[5] = 0;
}

bool8 sub_80976EC(struct Sprite *sprite)
{
    if (!(sprite->data[4] & 1))
    {
        Step1(sprite, sprite->data[3]);
        sprite->data[5]++;
    }

    sprite->data[4]++;

    if (sprite->data[5] > 15)
        return TRUE;
    else
        return FALSE;
}

static const s8 gUnknown_0850E772[] = {
    1, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 1, 2, 2, 1, 2,
    2, 1, 2, 2, 1, 2, 1, 1,
    2, 1, 1, 2, 1, 1, 2, 1,
    1, 2, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    0, 1, 1, 1, 0, 1, 1, 0,
    1, 0, 1, 0, 1, 0, 0, 0,
    0, 1, 0, 0, 0, 0, 0, 0,
};

static const s8 gUnknown_0850E7BA[] = {
     0,  0,  1,  0,  0,  1,  0,  0,
     1,  0,  1,  1,  0,  1,  1,  0,
     1,  1,  0,  1,  1,  0,  1,  1,
     0,  0,  1,  0,  0,  1,  0,  0,
     1,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,
     0,  0, -1,  0,  0, -1,  0,  0,
    -1,  0, -1, -1,  0, -1, -1,  0,
    -1, -1, -1, -1, -1, -1, -1, -2,
};

s16 sub_8097728(s16 a1)
{
    return gUnknown_0850E7BA[a1];
}

s16 sub_809773C(s16 a1)
{
    return gUnknown_0850E772[a1];
}

void sub_8097750(struct Sprite *sprite)
{
    sprite->data[6] = 0;
    sprite->data[7] = 0;
}

bool8 sub_8097758(struct Sprite *sprite)
{
    bool8 result = FALSE;

    switch(sprite->data[7])
    {
        case 0:
            sprite->pos2.x += sub_809773C(sprite->data[6]);
            sprite->pos2.y += sub_8097728(sprite->data[6]);
            break;
        case 1:
            sprite->pos2.x -= sub_809773C(0x47 - sprite->data[6]);
            sprite->pos2.y += sub_8097728(0x47 - sprite->data[6]);
            break;
        case 2:
            sprite->pos2.x -= sub_809773C(sprite->data[6]);
            sprite->pos2.y += sub_8097728(sprite->data[6]);
            break;
        case 3:
            sprite->pos2.x += sub_809773C(0x47 - sprite->data[6]);
            sprite->pos2.y += sub_8097728(0x47 - sprite->data[6]);
            break;
    }
    if(++sprite->data[6] == 0x48)
    {
        sprite->data[6] = 0;
        sprite->data[7]++;
    }
    if(sprite->data[7] == 0x4)
    {
        sprite->pos2.y = 0;
        sprite->pos2.x = 0;
        result = TRUE;
    }
    return result;
}

static const s8 gUnknown_0850E802[] = {
    -4,  -6,  -8, -10, -11, -12, -12, -12, -11, -10,  -9,  -8,  -6,  -4,   0,   0
};

static const s8 gUnknown_0850E812[] = {
    0,  -2,  -3,  -4,  -5,  -6,  -6,  -6,  -5,  -5,  -4,  -3,  -2,   0,   0,   0
};

static const s8 gUnknown_0850E822[] = {
    -2,  -4,  -6,  -8,  -9, -10, -10, -10,  -9,  -8,  -6,  -5,  -3,  -2,   0,   0
};

static const s8 *const gUnknown_0850E834[] = {
    gUnknown_0850E802,
    gUnknown_0850E812,
    gUnknown_0850E822
};

s16 sub_8097820(s16 a1, u8 a2)
{
    return gUnknown_0850E834[a2][a1];
}

void sub_809783C(struct Sprite *sprite, u8 a2, u8 a3, u8 a4)
{
    sprite->data[3] = a2;
    sprite->data[4] = a3;
    sprite->data[5] = a4;
    sprite->data[6] = 0;
}

static const s16 gUnknown_0850E840[] = {
    16, 16, 32,
};

static const u8 gUnknown_0850E846[] = {
    0, 0, 1,
};

u8 sub_809785C(struct Sprite *sprite)
{
    s16 v5[3];
    u8 v6[3];
    u8 v2;

    memcpy(v5, gUnknown_0850E840, 6); // TODO: get rid of memcpy
    memcpy(v6, gUnknown_0850E846, 3);
    v2 = 0;

    if (sprite->data[4])
        Step1(sprite, sprite->data[3]);

    sprite->pos2.y = sub_8097820(sprite->data[6] >> v6[sprite->data[4]], sprite->data[5]);

    sprite->data[6]++;

    if (sprite->data[6] == (v5[sprite->data[4]] >> 1))
        v2 = 1;

    if (sprite->data[6] >= v5[sprite->data[4]])
    {
        sprite->pos2.y = 0;
        v2 = -1;
    }

    return v2;
}

static const s16 gUnknown_0850E84A[] = {
    32, 32, 64,
};

static const u8 gUnknown_0850E850[] = {
    1, 1, 2,
};

u8 sub_80978E4(struct Sprite *sprite)
{
    s16 v5[3];
    u8 v6[3];
    u8 v2;

    memcpy(v5, gUnknown_0850E84A, 6);
    memcpy(v6, gUnknown_0850E850, 3);
    v2 = 0;

    if (sprite->data[4] && !(sprite->data[6] & 1))
        Step1(sprite, sprite->data[3]);

    sprite->pos2.y = sub_8097820(sprite->data[6] >> v6[sprite->data[4]], sprite->data[5]);

    sprite->data[6]++;

    if (sprite->data[6] == (v5[sprite->data[4]] >> 1))
        v2 = 1;

    if (sprite->data[6] >= v5[sprite->data[4]])
    {
        sprite->pos2.y = 0;
        v2 = -1;
    }

    return v2;
}

static void SetMovementDelay(struct Sprite *sprite, s16 timer)
{
    sprite->data[3] = timer;
}

static bool8 WaitForMovementDelay(struct Sprite *sprite)
{
    sprite->data[3]--;

    if (sprite->data[3] == 0)
        return TRUE;
    else
        return FALSE;
}

void SetAndStartSpriteAnim(struct Sprite *sprite, u8 animNum, u8 animCmdIndex)
{
    sprite->animNum = animNum;
    sprite->animPaused = FALSE;
    SeekSpriteAnim(sprite, animCmdIndex);
}

bool8 SpriteAnimEnded(struct Sprite *sprite)
{
    if (sprite->animEnded)
        return TRUE;
    else
        return FALSE;
}

void UpdateEventObjectSpriteVisibility(struct Sprite *sprite, bool8 invisible)
{
    u16 x, y;
    s16 x2, y2;

    sprite->invisible = invisible;

    if (sprite->coordOffsetEnabled)
    {
        x = sprite->pos1.x + sprite->pos2.x + sprite->centerToCornerVecX + gSpriteCoordOffsetX;
        y = sprite->pos1.y + sprite->pos2.y + sprite->centerToCornerVecY + gSpriteCoordOffsetY;
    }
    else
    {
        x = sprite->pos1.x + sprite->pos2.x + sprite->centerToCornerVecX;
        y = sprite->pos1.y + sprite->pos2.y + sprite->centerToCornerVecY;
    }

    x2 = x - (sprite->centerToCornerVecX >> 1);
    y2 = y - (sprite->centerToCornerVecY >> 1);

    if ((s16)x > 255 || x2 < -16)
        sprite->invisible = TRUE;
    if ((s16)y > 175 || y2 < -16)
        sprite->invisible = TRUE;
}

static void UpdateEventObjectSpriteSubpriorityAndVisibility(struct Sprite *sprite)
{
    sub_8097D68(sprite);
    SetObjectSubpriorityByZCoord(sprite->data[1], sprite, 1);
    UpdateEventObjectSpriteVisibility(sprite, sprite->data[2]);
}

void sub_8097AF0(void)
{
    int i;

    for(i = 0; i < MAX_SPRITES; i++)
    {
        struct Sprite *sprite = &gSprites[i];
        if(sprite->inUse && sprite->callback == UpdateEventObjectSpriteSubpriorityAndVisibility)
            DestroySprite(sprite);
    }
}

int sub_8097B2C(u8 var) // this should return a u8, because all that call this shifts to u8, but it wont match because it doesnt shift u8 at the end.
{
    int i;

    for(i = 0; i < MAX_SPRITES; i++)
    {
        struct Sprite *sprite = &gSprites[i];
        if(sprite->inUse && sprite->callback == UpdateEventObjectSpriteSubpriorityAndVisibility && (u8)sprite->data[0] == var)
            return i;
    }
    return MAX_SPRITES;
}

void sub_8097B78(u8 var1, u8 var2)
{
    u8 spriteId = sub_8097B2C(var1);

    if(spriteId != MAX_SPRITES)
        StartSpriteAnim(&gSprites[spriteId], GetFaceDirectionAnimNum(var2));
}

void sub_8097BB4(u8 var1, u16 graphicsId)
{
    int spriteId = sub_8097B2C(var1);

    if(spriteId != MAX_SPRITES)
    {
        struct Sprite *sprite = &gSprites[spriteId];
        const struct EventObjectGraphicsInfo *graphicsInfo = GetEventObjectGraphicsInfo(graphicsId);
        u16 tileNum = sprite->oam.tileNum;

        sprite->oam = *graphicsInfo->oam;
        sprite->oam.tileNum = tileNum;
        sprite->oam.paletteNum = graphicsInfo->paletteSlot;
        sprite->images = graphicsInfo->images;

        if(graphicsInfo->subspriteTables == NULL)
        {
            sprite->subspriteTables = NULL;
            sprite->subspriteTableNum = 0;
            sprite->subspriteMode = 0;
        }
        else
        {
            SetSubspriteTables(sprite, graphicsInfo->subspriteTables);
            sprite->subspriteMode = 2;
        }
        StartSpriteAnim(sprite, 0);
    }
}

void sub_8097C44(u8 var, bool32 var2)
{
    u8 spriteId = sub_8097B2C(var);

    if(spriteId == MAX_SPRITES)
        return;

    if(var2)
        gSprites[spriteId].data[2] = 1;
    else
        gSprites[spriteId].data[2] = 0;
}

bool32 sub_8097C8C(u8 var)
{
    u8 spriteId = sub_8097B2C(var);

    if(spriteId == MAX_SPRITES)
        return FALSE;

    return (gSprites[spriteId].data[2] == TRUE);
}

void sub_8097CC4(u8 var1, u8 var2)
{
    u8 spriteId = sub_8097B2C(var1);

    if(spriteId != MAX_SPRITES)
    {
        gSprites[spriteId].data[3] = var2;
        gSprites[spriteId].data[4] = 0;
    }
}

void sub_8097CF4(struct Sprite *sprite)
{
    switch(sprite->data[4])
    {
        case 0:
            sprite->pos2.y = 0;
            sprite->data[4]++;
        case 1:
            sprite->pos2.y -= 8;
            if(sprite->pos2.y == -160)
            {
                sprite->pos2.y = 0;
                sprite->data[2] = 1;
                sprite->data[3] = 0;
                sprite->data[4] = 0;
            }
    }
}

void sub_8097D30(struct Sprite *sprite)
{
    switch(sprite->data[4])
    {
        case 0:
            sprite->pos2.y = -160;
            sprite->data[4]++;
        case 1:
            sprite->pos2.y += 8;
            if(sprite->pos2.y == 0)
            {
                sprite->data[3] = 0;
                sprite->data[4] = 0;
            }
    }
}

static void sub_8097D68(struct Sprite *sprite)
{
    switch(sprite->data[3])
    {
        case 1:
            sub_8097D30(sprite);
            break;
        case 2:
            sub_8097CF4(sprite);
            break;
        case 0:
            break;
        default:
            sprite->data[3] = 0;
            break;
    }
}

bool32 sub_8097D9C(u8 var)
{
    u8 spriteId = sub_8097B2C(var);

    if(spriteId == MAX_SPRITES)
        return FALSE;

    if(gSprites[spriteId].data[3] != FALSE)
        return TRUE;

    return FALSE;
}

u32 StartFieldEffectForEventObject(u8 fieldEffectId, struct EventObject *eventObject)
{
    EventObjectGetLocalIdAndMap(eventObject, &gFieldEffectArguments[0], &gFieldEffectArguments[1], &gFieldEffectArguments[2]);
    return FieldEffectStart(fieldEffectId);
}

void DoShadowFieldEffect(struct EventObject *eventObject)
{
    if (!eventObject->hasShadow)
    {
        eventObject->hasShadow = 1;
        StartFieldEffectForEventObject(FLDEFF_SHADOW, eventObject);
    }
}

static void DoRippleFieldEffect(struct EventObject *eventObject, struct Sprite *sprite)
{
    const struct EventObjectGraphicsInfo *graphicsInfo = GetEventObjectGraphicsInfo(eventObject->graphicsId);
    gFieldEffectArguments[0] = sprite->pos1.x;
    gFieldEffectArguments[1] = sprite->pos1.y + (graphicsInfo->height >> 1) - 2;
    gFieldEffectArguments[2] = 151;
    gFieldEffectArguments[3] = 3;
    FieldEffectStart(FLDEFF_RIPPLE);
}

u8 (*const gMovementActionFuncs_StoreAndLockAnim[])(struct EventObject *, struct Sprite *) = {
    MovementAction_StoreAndLockAnim_Step0,
    MovementAction_Finish,
};

u8 (*const gMovementActionFuncs_FreeAndUnlockAnim[])(struct EventObject *, struct Sprite *) = {
    MovementAction_FreeAndUnlockAnim_Step0,
    MovementAction_Finish,
};

u8 (*const gMovementActionFuncs_FlyUp[])(struct EventObject *, struct Sprite *) = {
    MovementAction_FlyUp_Step0,
    MovementAction_FlyUp_Step1,
    MovementAction_Fly_Finish,
};

u8 (*const gMovementActionFuncs_FlyDown[])(struct EventObject *, struct Sprite *) = {
    MovementAction_FlyDown_Step0,
    MovementAction_FlyDown_Step1,
    MovementAction_Fly_Finish,
};

u8 MovementAction_StoreAndLockAnim_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    u32 one;
    bool32 ableToStore = FALSE;
    if (gLockedAnimEventObjects == NULL)
    {
        gLockedAnimEventObjects = AllocZeroed(sizeof(struct LockedAnimEventObjects));
        gLockedAnimEventObjects->eventObjectIds[0] = eventObject->localId;
        // needed to match
        gLockedAnimEventObjects->count = (one = 1);
        ableToStore = one;
    }
    else
    {
        u8 i;
        u8 firstFreeSlot;
        bool32 found;
        for (firstFreeSlot = 16, found = FALSE, i = 0; i < 16; i++)
        {
            if (firstFreeSlot == 16 && gLockedAnimEventObjects->eventObjectIds[i] == 0)
                firstFreeSlot = i;

            if (gLockedAnimEventObjects->eventObjectIds[i] == eventObject->localId)
            {
                found = TRUE;
                break;
            }
        }

        if (!found && firstFreeSlot != 16)
        {
            gLockedAnimEventObjects->eventObjectIds[firstFreeSlot] = eventObject->localId;
            gLockedAnimEventObjects->count++;
            ableToStore = TRUE;
        }
    }

    if (ableToStore == TRUE)
    {
        eventObject->inanimate = TRUE;
        eventObject->facingDirectionLocked = TRUE;
    }

    sprite->data[2] = 1;
    return TRUE;
}

u8 MovementAction_FreeAndUnlockAnim_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    bool32 ableToStore;
    u8 index;

    sprite->data[2] = 1;
    if (gLockedAnimEventObjects != NULL)
    {
        ableToStore = FALSE;
        index = FindLockedEventObjectIndex(eventObject);
        if (index != 16)
        {
            gLockedAnimEventObjects->eventObjectIds[index] = 0;
            gLockedAnimEventObjects->count--;
            ableToStore = TRUE;
        }
        if (gLockedAnimEventObjects->count == 0)
            FREE_AND_SET_NULL(gLockedAnimEventObjects);
        if (ableToStore == TRUE)
        {
            eventObject->inanimate = GetEventObjectGraphicsInfo(eventObject->graphicsId)->inanimate;
            eventObject->facingDirectionLocked = FALSE;
            sprite->animPaused = 0;
        }
    }

    return TRUE;
}

u8 FindLockedEventObjectIndex(struct EventObject *eventObject)
{
    u8 i;

    for (i = 0; i < EVENT_OBJECTS_COUNT; i++)
    {
        if (gLockedAnimEventObjects->eventObjectIds[i] == eventObject->localId)
            return i;
    }
    return EVENT_OBJECTS_COUNT;
}

void CreateLevitateMovementTask(struct EventObject *eventObject)
{
    u8 taskId = CreateTask(ApplyLevitateMovement, 0xFF);
    struct Task *task = &gTasks[taskId];

    StoreWordInTwoHalfwords(&task->data[0], (u32)eventObject);
    eventObject->warpArrowSpriteId = taskId;
    task->data[3] = 0xFFFF;
}

static void ApplyLevitateMovement(u8 taskId)
{
    struct EventObject *eventObject;
    struct Sprite *sprite;
    struct Task *task = &gTasks[taskId];

    LoadWordFromTwoHalfwords(&task->data[0], (u32 *)&eventObject); // load the map object pointer.
    sprite = &gSprites[eventObject->spriteId];

    if(!(task->data[2] & 0x3))
        sprite->pos2.y += task->data[3];

    if(!(task->data[2] & 0xF))
        task->data[3] = -task->data[3];

    task->data[2]++;
}

void DestroyExtraMovementTask(u8 taskId)
{
    struct EventObject *eventObject;
    struct Task *task = &gTasks[taskId];

    LoadWordFromTwoHalfwords(&task->data[0], (u32 *)&eventObject); // unused eventObject
    DestroyTask(taskId);
}

void sub_8098074(u8 var1, u8 var2)
{
    u8 i;

    for(i = 0; i < EVENT_OBJECTS_COUNT; i++)
    {
        if(i != var1 && i != var2 &&
            gEventObjects[i].active && i != gPlayerAvatar.eventObjectId)
                FreezeEventObject(&gEventObjects[i]);
    }
}

u8 MovementAction_FlyUp_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sprite->pos2.y = 0;
    sprite->data[2]++;
    return FALSE;
}

u8 MovementAction_FlyUp_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    sprite->pos2.y -= 8;

    if(sprite->pos2.y == -160)
        sprite->data[2]++;
    return FALSE;
}

u8 MovementAction_FlyDown_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    sprite->pos2.y = -160;
    sprite->data[2]++;
    return FALSE;
}

u8 MovementAction_FlyDown_Step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    sprite->pos2.y += 8;

    if(!sprite->pos2.y)
        sprite->data[2]++;
    return FALSE;
}

// though this function returns TRUE without doing anything, this header is required due to being in an array of functions which needs it.
u8 MovementAction_Fly_Finish(struct EventObject *eventObject, struct Sprite *sprite)
{
    return TRUE;
}
