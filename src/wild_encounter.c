#include "global.h"
#include "wild_encounter.h"
#include "pokemon.h"
#include "metatile_behavior.h"
#include "fieldmap.h"
#include "random.h"
#include "field_player_avatar.h"
#include "event_data.h"
#include "safari_zone.h"
#include "overworld.h"
#include "pokeblock.h"
#include "pokedex.h"
#include "battle_setup.h"
#include "roamer.h"
#include "tv.h"
#include "link.h"
#include "palette.h"
#include "rtc.h"
#include "script.h"
#include "battle_debug.h"
#include "battle_pike.h"
#include "battle_pyramid.h"
#include "constants/abilities.h"
#include "constants/game_stat.h"
#include "constants/items.h"
#include "constants/layouts.h"
#include "constants/maps.h"
#include "constants/species.h"




extern const u8 EventScript_RepelWoreOff[];

#define NUM_FEEBAS_SPOTS    6

// this file's functions
static u16 FeebasRandom(void);
static void FeebasSeedRng(u16 seed);
static bool8 IsWildLevelAllowedByRepel(u8 level);
static void ApplyFluteEncounterRateMod(u32 *encRate);
static void ApplyCleanseTagEncounterRateMod(u32 *encRate);
static bool8 TryGetAbilityInfluencedWildMonIndex(const struct WildPokemon *wildMon, u8 type, u8 ability, u8 *monIndex);
static bool8 IsAbilityAllowingEncounter(u8 level);

//SWSB
static u8 GetWildCurveFactor(void);
static u16 GetEvoSpecies(u16 species, u8 level);
static u16 SeedGenerateSpeciesLand(u8 headerid, u8 rarity, u8 level);
static u16 SeedGenerateSpeciesRockSmash(u8 headerid, u8 rarity, u8 level);
static u16 SeedGenerateSpeciesWater(u8 headerid, u8 rarity, u8 level);
static bool8 TryGetAbilityInfluencedWildMonIndexSWSB(u8 headerID, u8 type, u8 ability, u8 *monIndex);

// EWRAM vars
EWRAM_DATA static u8 sWildEncountersDisabled = 0;
EWRAM_DATA bool8 gIsFishingEncounter = 0;
EWRAM_DATA static u32 sFeebasRngValue = 0;

#include "data/wild_encounters.h"

//Special Feebas-related data.
const struct WildPokemon gWildFeebasRoute119Data = {20, 25, SPECIES_FEEBAS};

const u16 gRoute119WaterTileData[] =
{
    0, 0x2D, 0,
    0x2E, 0x5B, 0x83,
    0x5C, 0x8B, 0x12A,
};

// code
void DisableWildEncounters(bool8 disabled)
{
    sWildEncountersDisabled = disabled;
}

static u16 GetRoute119WaterTileNum(s16 x, s16 y, u8 section)
{
    u16 xCur;
    u16 yCur;
    u16 yMin = gRoute119WaterTileData[section * 3 + 0];
    u16 yMax = gRoute119WaterTileData[section * 3 + 1];
    u16 tileNum = gRoute119WaterTileData[section * 3 + 2];

    for (yCur = yMin; yCur <= yMax; yCur++)
    {
        for (xCur = 0; xCur < gMapHeader.mapLayout->width; xCur++)
        {
            u8 tileBehaviorId = MapGridGetMetatileBehaviorAt(xCur + 7, yCur + 7);
            if (MetatileBehavior_IsSurfableAndNotWaterfall(tileBehaviorId) == TRUE)
            {
                tileNum++;
                if (x == xCur && y == yCur)
                    return tileNum;
            }
        }
    }
    return tileNum + 1;
}

static bool8 CheckFeebas(void)
{
    u8 i;
    u16 feebasSpots[NUM_FEEBAS_SPOTS];
    s16 x;
    s16 y;
    u8 route119Section = 0;
    u16 waterTileNum;

    if (gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(ROUTE119)
     && gSaveBlock1Ptr->location.mapNum == MAP_NUM(ROUTE119))
    {
        GetXYCoordsOneStepInFrontOfPlayer(&x, &y);
        x -= 7;
        y -= 7;

        if (y >= gRoute119WaterTileData[3 * 0 + 0] && y <= gRoute119WaterTileData[3 * 0 + 1])
            route119Section = 0;
        if (y >= gRoute119WaterTileData[3 * 1 + 0] && y <= gRoute119WaterTileData[3 * 1 + 1])
            route119Section = 1;
        if (y >= gRoute119WaterTileData[3 * 2 + 0] && y <= gRoute119WaterTileData[3 * 2 + 1])
            route119Section = 2;

        if (Random() % 100 > 49) // 50% chance of encountering Feebas
            return FALSE;

        FeebasSeedRng(gSaveBlock1Ptr->easyChatPairs[0].unk2);
        for (i = 0; i != NUM_FEEBAS_SPOTS;)
        {
            feebasSpots[i] = FeebasRandom() % 447;
            if (feebasSpots[i] == 0)
                feebasSpots[i] = 447;
            if (feebasSpots[i] < 1 || feebasSpots[i] >= 4)
                i++;
        }
        waterTileNum = GetRoute119WaterTileNum(x, y, route119Section);
        for (i = 0; i < NUM_FEEBAS_SPOTS; i++)
        {
            if (waterTileNum == feebasSpots[i])
                return TRUE;
        }
    }
    return FALSE;
}

// The number 1103515245 comes from the example implementation of rand and srand
// in the ISO C standard.

static u16 FeebasRandom(void)
{
    sFeebasRngValue = (1103515245 * sFeebasRngValue) + 12345;
    return sFeebasRngValue >> 16;
}

static void FeebasSeedRng(u16 seed)
{
    sFeebasRngValue = seed;
}

static u8 ChooseWildMonIndex_Land(void)
{
    u8 rand = Random() % 100;

    if (rand < 20)                  // 20% chance
        return 0;
    else if (rand >= 20 && rand < 40)    // 20% chance
        return 1;
    else if (rand >= 40 && rand < 50)    // 10% chance
        return 2;
    else if (rand >= 50 && rand < 60)    // 10% chance
        return 3;
    else if (rand >= 60 && rand < 70)    // 10% chance
        return 1;
    else if (rand >= 70 && rand < 80)    // 10% chance
        return 2;
    else if (rand >= 80 && rand < 85)    // 5% chance
        return 6;
    else if (rand >= 85 && rand < 90)    // 5% chance
        return 7;
    else if (rand >= 90 && rand < 94)    // 4% chance
        return 8;
    else if (rand >= 94 && rand < 98)    // 4% chance
        return 9;
    else if (rand == 98)                 // 1% chance
        return 10;
    else                            // 1% chance
        return 11;
}

static u8 ChooseWildMonIndex_WaterRock(void)
{
    u8 rand = Random() % 100;

    if (rand < 60)                  // 60% chance
        return 0;
    else if (rand >= 60 && rand < 90)    // 30% chance
        return 1;
    else if (rand >= 90 && rand < 95)    // 5% chance
        return 2;
    else if (rand >= 95 && rand < 99)    // 4% chance
        return 3;
    else                            // 1% chance
        return 4;
}

static u8 ChooseWildMonIndex_WaterRockSWSB(void)
{
    u8 rand = Random() % 100;

    if (rand < 60)                  // 60% chance
        return 1;
    else if (rand >= 60 && rand < 90)    // 30% chance
        return 1;
    else if (rand >= 90 && rand < 95)    // 5% chance
        return 2;
    else if (rand >= 95 && rand < 99)    // 4% chance
        return 3;
    else                            // 1% chance
        return 3;
}

enum
{
    OLD_ROD,
    GOOD_ROD,
    SUPER_ROD
};

static u8 ChooseWildMonIndex_Fishing(u8 rod)
{
    u8 wildMonIndex = 0;
    u8 rand = Random() % 100;

    switch (rod)
    {
    case OLD_ROD:
        if (rand < 70)  // 70% chance
            wildMonIndex = 0;
        else            // 30% chance
            wildMonIndex = 1;
        break;
    case GOOD_ROD:
        if (rand < 60)                  // 60% chance
            wildMonIndex = 2;
        if (rand >= 60 && rand < 80)    // 20% chance
            wildMonIndex = 3;
        if (rand >= 80 && rand < 100)   // 20% chance
            wildMonIndex = 4;
        break;
    case SUPER_ROD:
        if (rand < 40)                  // 40% chance
            wildMonIndex = 5;
        if (rand >= 40 && rand < 80)    // 40% chance
            wildMonIndex = 6;
        if (rand >= 80 && rand < 95)    // 15% chance
            wildMonIndex = 7;
        if (rand >= 95 && rand < 99)    // 4% chance
            wildMonIndex = 8;
        if (rand == 99)                 // 1% chance
            wildMonIndex = 9;
        break;
    }
    return wildMonIndex;
}

static u8 ChooseWildMonIndex_Land_SWSB(void)
{
    u8 rand = Random() % 100;

    if (rand < 20)                  // 20% chance
        return 1;
    else if (rand >= 20 && rand < 40)    // 20% chance
        return 2;
    else if (rand >= 40 && rand < 50)    // 10% chance
        return 3;
    else if (rand >= 50 && rand < 60)    // 10% chance
        return 1;
    else if (rand >= 60 && rand < 70)    // 10% chance
        return 2;
    else if (rand >= 70 && rand < 80)    // 10% chance
        return 3;
    else if (rand >= 80 && rand < 85)    // 5% chance
        return 4;
    else if (rand >= 85 && rand < 90)    // 5% chance
        return 4;
    else if (rand >= 90 && rand < 94)    // 4% chance
        return 5;
    else if (rand >= 94 && rand < 98)    // 4% chance
        return 5;
    else if (rand == 98)                 // 1% chance
        return 6;
    else                            // 1% chance
        return 6;
}

static u8 ChooseWildMonLevel(const struct WildPokemon *wildPokemon)
{
    u8 min;
    u8 max;
    u8 range;
    u8 rand;

    // Make sure minimum level is less than maximum level
    if (wildPokemon->maxLevel >= wildPokemon->minLevel)
    {
        min = wildPokemon->minLevel;
        max = wildPokemon->maxLevel;
    }
    else
    {
        min = wildPokemon->maxLevel;
        max = wildPokemon->minLevel;
    }
    range = max - min + 1;
    rand = Random() % range;

    // check ability for max level mon
    if (!GetMonData(&gPlayerParty[0], MON_DATA_SANITY_IS_EGG))
    {
        u8 ability = GetMonAbility(&gPlayerParty[0]);
        if (ability == ABILITY_HUSTLE || ability == ABILITY_VITAL_SPIRIT || ability == ABILITY_PRESSURE)
        {
            if (Random() % 2 == 0)
                return max;

            if (rand != 0)
                rand--;
        }
    }

    return min + rand;
}

static u16 GetCurrentMapWildMonHeaderId(void)
{
    u16 i;

    for (i = 0; ; i++)
    {
        const struct WildPokemonHeader *wildHeader = &gWildMonHeaders[i];
        if (wildHeader->mapGroup == 0xFF)
            break;

        if (gWildMonHeaders[i].mapGroup == gSaveBlock1Ptr->location.mapGroup &&
            gWildMonHeaders[i].mapNum == gSaveBlock1Ptr->location.mapNum)
        {
            if (gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(ALTERING_CAVE) &&
                gSaveBlock1Ptr->location.mapNum == MAP_NUM(ALTERING_CAVE))
            {
                u16 alteringCaveId = VarGet(VAR_ALTERING_CAVE_WILD_SET);
                if (alteringCaveId > 8)
                    alteringCaveId = 0;

                i += alteringCaveId;
            }

            return i;
        }
    }

    return -1;
}

static u8 PickWildMonNature(void)
{
    u8 i;
    u8 j;
    struct Pokeblock *safariPokeblock;
    u8 natures[25];

    if (GetSafariZoneFlag() == TRUE && Random() % 100 < 80)
    {
        safariPokeblock = SafariZoneGetActivePokeblock();
        if (safariPokeblock != NULL)
        {
            for (i = 0; i < 25; i++)
                natures[i] = i;
            for (i = 0; i < 24; i++)
            {
                for (j = i + 1; j < 25; j++)
                {
                    if (Random() & 1)
                    {
                        u8 temp = natures[i];

                        natures[i] = natures[j];
                        natures[j] = temp;
                    }
                }
            }
            for (i = 0; i < 25; i++)
            {
                if (PokeblockGetGain(natures[i], safariPokeblock) > 0)
                    return natures[i];
            }
        }
    }
    // check synchronize for a pokemon with the same ability
    if (!GetMonData(&gPlayerParty[0], MON_DATA_SANITY_IS_EGG)
        && GetMonAbility(&gPlayerParty[0]) == ABILITY_SYNCHRONIZE
        && Random() % 2 == 0)
    {
        return GetMonData(&gPlayerParty[0], MON_DATA_PERSONALITY) % 25;
    }

    // random nature
    return Random() % 25;
}

void CreateWildMon(u16 species, u8 level)
{
    bool32 checkCuteCharm;
    u16 monData;

    ZeroEnemyPartyMons();
    checkCuteCharm = TRUE;

    switch (gBaseStats[species].genderRatio)
    {
    case MON_MALE:
    case MON_FEMALE:
    case MON_GENDERLESS:
        checkCuteCharm = FALSE;
        break;
    }

    if (checkCuteCharm
        && !GetMonData(&gPlayerParty[0], MON_DATA_SANITY_IS_EGG)
        && GetMonAbility(&gPlayerParty[0]) == ABILITY_CUTE_CHARM
        && Random() % 3 != 0)
    {
        u16 leadingMonSpecies = GetMonData(&gPlayerParty[0], MON_DATA_SPECIES);
        u32 leadingMonPersonality = GetMonData(&gPlayerParty[0], MON_DATA_PERSONALITY);
        u8 gender = GetGenderFromSpeciesAndPersonality(leadingMonSpecies, leadingMonPersonality);

        // misses mon is genderless check, although no genderless mon can have cute charm as ability
        if (gender == MON_FEMALE)
            gender = MON_MALE;
        else
            gender = MON_FEMALE;

        CreateMonWithGenderNatureLetter(&gEnemyParty[0], species, level, 32, gender, PickWildMonNature(), 0);
        return;
    }

    CreateMonWithNature(&gEnemyParty[0], species, level, 32, PickWildMonNature());
}


enum
{
    WILD_AREA_LAND,
    WILD_AREA_WATER,
    WILD_AREA_ROCKS,
    WILD_AREA_FISHING,
};

#define WILD_CHECK_REPEL    0x1
#define WILD_CHECK_KEEN_EYE 0x2

static bool8 TryGenerateWildMon(const struct WildPokemonInfo *wildMonInfo, u8 area, u8 flags)
{
  u8 wildMonIndex = 0;
  u8 level;

  switch (area)
  {
  case WILD_AREA_LAND:
      if (TryGetAbilityInfluencedWildMonIndex(wildMonInfo->wildPokemon, TYPE_STEEL, ABILITY_MAGNET_PULL, &wildMonIndex))
          break;
      if (TryGetAbilityInfluencedWildMonIndex(wildMonInfo->wildPokemon, TYPE_ELECTRIC, ABILITY_STATIC, &wildMonIndex))
          break;

      wildMonIndex = ChooseWildMonIndex_Land();
      break;
  case WILD_AREA_WATER:
      if (TryGetAbilityInfluencedWildMonIndex(wildMonInfo->wildPokemon, TYPE_ELECTRIC, ABILITY_STATIC, &wildMonIndex))
          break;

      wildMonIndex = ChooseWildMonIndex_WaterRock();
      break;
  case WILD_AREA_ROCKS:
      wildMonIndex = ChooseWildMonIndex_WaterRock();
      break;
  }

  level = ChooseWildMonLevel(&wildMonInfo->wildPokemon[wildMonIndex]);
  if (flags & WILD_CHECK_REPEL && !IsWildLevelAllowedByRepel(level))
      return FALSE;
  if (gMapHeader.mapLayoutId != LAYOUT_BATTLE_FRONTIER_BATTLE_PIKE_RANDOM_ROOM3 && flags & WILD_CHECK_KEEN_EYE && !IsAbilityAllowingEncounter(level))
      return FALSE;

  CreateWildMon(wildMonInfo->wildPokemon[wildMonIndex].species, level);
  return TRUE;
}

static bool8 TryGenerateWildMonSWSB(const struct WildPokemonInfo *wildMonInfo, u8 area, u8 flags, u8 headerID)
{
    u8 wildMonIndex = 0;
    u8 level;
    u16 speciesID;
    u8 hour = Rtc_GetCurrentHour();
    level = GetWildCurveFactor();

    switch (area)
    {
    case WILD_AREA_LAND:
        if (TryGetAbilityInfluencedWildMonIndexSWSB(headerID, TYPE_STEEL, ABILITY_MAGNET_PULL, &wildMonIndex))
            break;
        if (TryGetAbilityInfluencedWildMonIndexSWSB(headerID, TYPE_ELECTRIC, ABILITY_STATIC, &wildMonIndex))
            break;

        wildMonIndex = ChooseWildMonIndex_Land_SWSB();
        speciesID = SeedGenerateSpeciesLand(headerID, wildMonIndex, level);
        break;
    case WILD_AREA_WATER:
        if (TryGetAbilityInfluencedWildMonIndexSWSB(headerID, TYPE_ELECTRIC, ABILITY_STATIC, &wildMonIndex))
            break;
        wildMonIndex = ChooseWildMonIndex_WaterRockSWSB();
        speciesID = SeedGenerateSpeciesWater(headerID, wildMonIndex, level);
        break;
    case WILD_AREA_ROCKS:
        wildMonIndex = ChooseWildMonIndex_WaterRockSWSB();
        speciesID = SeedGenerateSpeciesRockSmash(headerID, wildMonIndex, level);
        break;
    }

    if (flags & WILD_CHECK_REPEL && !IsWildLevelAllowedByRepel(level))
        return FALSE;
    if (gMapHeader.mapLayoutId != LAYOUT_BATTLE_FRONTIER_BATTLE_PIKE_RANDOM_ROOM3 && flags & WILD_CHECK_KEEN_EYE && !IsAbilityAllowingEncounter(level))
        return FALSE;


    //夜间限定
    if (gBaseStats[speciesID].type1 == TYPE_GHOST || gBaseStats[speciesID].type2 == TYPE_GHOST)
    {
        if (GetTimeLapse(hour) == TIME_MIDNIGHT
        || GetTimeLapse(hour) == TIME_NIGHT
        || GetTimeLapse(hour) == TIME_NIGHTFALL)
        {
          CreateWildMon(speciesID, level);
          return TRUE;
        }
        return FALSE;
    }

    //记录连锁
    if (VarGet(VAR_CHAIN_SPECIES) == speciesID)
    {
      VarSet(VAR_CHAIN_COUNT, (VarGet(VAR_CHAIN_COUNT)+1));
    }
    else
    {
      VarSet(VAR_CHAIN_COUNT, 0);
    }
    VarSet(VAR_CHAIN_SPECIES, speciesID);

    CreateWildMon(speciesID, level);
    return TRUE;
}

static u16 GenerateFishingWildMon(const struct WildPokemonInfo *wildMonInfo, u8 rod)
{
    u8 wildMonIndex = ChooseWildMonIndex_Fishing(rod);
    u8 level = ChooseWildMonLevel(&wildMonInfo->wildPokemon[wildMonIndex]);

    CreateWildMon(wildMonInfo->wildPokemon[wildMonIndex].species, level);
    return wildMonInfo->wildPokemon[wildMonIndex].species;
}

static bool8 SetUpMassOutbreakEncounter(u8 flags)
{
    u16 i;

    if (flags & WILD_CHECK_REPEL && !IsWildLevelAllowedByRepel(gSaveBlock1Ptr->outbreakPokemonLevel))
        return FALSE;

    CreateWildMon(gSaveBlock1Ptr->outbreakPokemonSpecies, gSaveBlock1Ptr->outbreakPokemonLevel);
    for (i = 0; i < 4; i++)
        SetMonMoveSlot(&gEnemyParty[0], gSaveBlock1Ptr->outbreakPokemonMoves[i], i);

    return TRUE;
}

static bool8 DoMassOutbreakEncounterTest(void)
{
    if (gSaveBlock1Ptr->outbreakPokemonSpecies != 0
     && gSaveBlock1Ptr->location.mapNum == gSaveBlock1Ptr->outbreakLocationMapNum
     && gSaveBlock1Ptr->location.mapGroup == gSaveBlock1Ptr->outbreakLocationMapGroup)
    {
        if (Random() % 100 < gSaveBlock1Ptr->outbreakPokemonProbability)
            return TRUE;
    }
    return FALSE;
}

static bool8 DoWildEncounterRateDiceRoll(u16 encounterRate)
{
    if (Random() % 2880 < encounterRate)
        return TRUE;
    else
        return FALSE;
}

static bool8 DoWildEncounterRateTest(u32 encounterRate, bool8 ignoreAbility)
{
    encounterRate *= 16;
    if (TestPlayerAvatarFlags(PLAYER_AVATAR_FLAG_MACH_BIKE | PLAYER_AVATAR_FLAG_ACRO_BIKE))
        encounterRate = encounterRate * 80 / 100;
    ApplyFluteEncounterRateMod(&encounterRate);
    ApplyCleanseTagEncounterRateMod(&encounterRate);
    if (!ignoreAbility && !GetMonData(&gPlayerParty[0], MON_DATA_SANITY_IS_EGG))
    {
        u32 ability = GetMonAbility(&gPlayerParty[0]);

        if (ability == ABILITY_STENCH && gMapHeader.mapLayoutId == LAYOUT_BATTLE_FRONTIER_BATTLE_PYRAMID_EMPTY_SQUARE)
            encounterRate = encounterRate * 3 / 4;
        else if (ability == ABILITY_STENCH)
            encounterRate /= 2;
        else if (ability == ABILITY_ILLUMINATE)
            encounterRate *= 2;
        else if (ability == ABILITY_WHITE_SMOKE)
            encounterRate /= 2;
        else if (ability == ABILITY_ARENA_TRAP)
            encounterRate *= 2;
        else if (ability == ABILITY_SAND_VEIL && gSaveBlock1Ptr->weather == 8)
            encounterRate /= 2;
    }
    if (encounterRate > 2880)
        encounterRate = 2880;
    return DoWildEncounterRateDiceRoll(encounterRate);
}

static bool8 DoGlobalWildEncounterDiceRoll(void)
{
    if (Random() % 100 >= 60)
        return FALSE;
    else
        return TRUE;
}

static bool8 AreLegendariesInSootopolisPreventingEncounters(void)
{
    if (gSaveBlock1Ptr->location.mapGroup != MAP_GROUP(SOOTOPOLIS_CITY)
     || gSaveBlock1Ptr->location.mapNum != MAP_NUM(SOOTOPOLIS_CITY))
    {
        return FALSE;
    }

    return FlagGet(FLAG_LEGENDARIES_IN_SOOTOPOLIS);
}

bool8 StandardWildEncounter(u16 currMetaTileBehavior, u16 previousMetaTileBehavior)
{
    u16 headerId;
    struct Roamer *roamer;

    if (sWildEncountersDisabled == TRUE)
        return FALSE;

    headerId = GetCurrentMapWildMonHeaderId();
    if (headerId == 0xFFFF)
    {
        if (gMapHeader.mapLayoutId == LAYOUT_BATTLE_FRONTIER_BATTLE_PIKE_RANDOM_ROOM3)
        {
            headerId = GetBattlePikeWildMonHeaderId();
            if (previousMetaTileBehavior != currMetaTileBehavior && !DoGlobalWildEncounterDiceRoll())
                return FALSE;
            else if (DoWildEncounterRateTest(gBattlePikeWildMonHeaders[headerId].landMonsInfo->encounterRate, FALSE) != TRUE)
                return FALSE;
            else if (TryGenerateWildMon(gBattlePikeWildMonHeaders[headerId].landMonsInfo, WILD_AREA_LAND, WILD_CHECK_KEEN_EYE) != TRUE)
                return FALSE;
            else if (!TryGenerateBattlePikeWildMon(TRUE))
                return FALSE;

            BattleSetup_StartBattlePikeWildBattle();
            return TRUE;
        }
        if (gMapHeader.mapLayoutId == LAYOUT_BATTLE_FRONTIER_BATTLE_PYRAMID_EMPTY_SQUARE)
        {
            headerId = gSaveBlock2Ptr->frontier.curChallengeBattleNum;
            if (previousMetaTileBehavior != currMetaTileBehavior && !DoGlobalWildEncounterDiceRoll())
                return FALSE;
            else if (DoWildEncounterRateTest(gBattlePyramidWildMonHeaders[headerId].landMonsInfo->encounterRate, FALSE) != TRUE)
                return FALSE;
            else if (TryGenerateWildMon(gBattlePyramidWildMonHeaders[headerId].landMonsInfo, WILD_AREA_LAND, WILD_CHECK_KEEN_EYE) != TRUE)
                return FALSE;

            GenerateBattlePyramidWildMon();
            BattleSetup_StartWildBattle();
            return TRUE;
        }
    }
    else
    {
        if (MetatileBehavior_IsLandWildEncounter(currMetaTileBehavior) == TRUE)
        {
            if (gWildMonHeaders[headerId].landMonsInfo == NULL)
                return FALSE;
            else if (previousMetaTileBehavior != currMetaTileBehavior && !DoGlobalWildEncounterDiceRoll())
                return FALSE;
            else if (DoWildEncounterRateTest(gWildMonHeaders[headerId].landMonsInfo->encounterRate, FALSE) != TRUE)
                return FALSE;

            if (TryStartRoamerEncounter() == TRUE)
            {
                roamer = &gSaveBlock1Ptr->roamer;
                if (!IsWildLevelAllowedByRepel(roamer->level))
                    return FALSE;

                BattleSetup_StartRoamerBattle();
                return TRUE;
            }
            else
            {
                if (DoMassOutbreakEncounterTest() == TRUE && SetUpMassOutbreakEncounter(WILD_CHECK_REPEL | WILD_CHECK_KEEN_EYE) == TRUE)
                {
                    BattleSetup_StartWildBattle();
                    return TRUE;
                }

                //assign hidden ability
                if (MetatileBehavior_IsTallGrass(currMetaTileBehavior) == TRUE &&  Random() % 100 < 15 )
                    FlagSet(HIDDEN_ABILITY_FLAG);
                // try a regular wild land encounter

                if (TryGenerateWildMonSWSB(gWildMonHeaders[headerId].landMonsInfo, WILD_AREA_LAND, WILD_CHECK_REPEL | WILD_CHECK_KEEN_EYE, headerId) == TRUE)
                {
                    if (MetatileBehavior_IsTallGrass(currMetaTileBehavior) == TRUE &&  Random() % 100 < 40 && !GetSafariZoneFlag() && GetMonsStateToDoubles() == PLAYER_HAS_TWO_USABLE_MONS)
                    {
          						struct Pokemon mon1 = gEnemyParty[0];
                      if (MetatileBehavior_IsTallGrass(currMetaTileBehavior) == TRUE &&  Random() % 100 < 50 )
                          FlagSet(HIDDEN_ABILITY_FLAG);
          						TryGenerateWildMonSWSB(gWildMonHeaders[headerId].landMonsInfo, WILD_AREA_LAND, WILD_CHECK_KEEN_EYE, headerId);
          						gEnemyParty[1] = mon1;
          						BattleSetup_StartDoubleWildBattle();
                    }
                    else
                    {
                      BattleSetup_StartWildBattle();
                    }
                    return TRUE;
                }

                return FALSE;
            }
        }
        else if (MetatileBehavior_IsWaterWildEncounter(currMetaTileBehavior) == TRUE
                 || (TestPlayerAvatarFlags(PLAYER_AVATAR_FLAG_SURFING) && MetatileBehavior_IsBridge(currMetaTileBehavior) == TRUE))
        {
            if (AreLegendariesInSootopolisPreventingEncounters() == TRUE)
                return FALSE;
            else if (gWildMonHeaders[headerId].waterMonsInfo == NULL)
                return FALSE;
            else if (previousMetaTileBehavior != currMetaTileBehavior && !DoGlobalWildEncounterDiceRoll())
                return FALSE;
            else if (DoWildEncounterRateTest(gWildMonHeaders[headerId].waterMonsInfo->encounterRate, FALSE) != TRUE)
                return FALSE;

            if (TryStartRoamerEncounter() == TRUE)
            {
                roamer = &gSaveBlock1Ptr->roamer;
                if (!IsWildLevelAllowedByRepel(roamer->level))
                    return FALSE;

                BattleSetup_StartRoamerBattle();
                return TRUE;
            }
            else // try a regular surfing encounter
            {
                if (TryGenerateWildMonSWSB(gWildMonHeaders[headerId].waterMonsInfo, WILD_AREA_WATER, WILD_CHECK_REPEL | WILD_CHECK_KEEN_EYE, headerId) == TRUE)
                {
                    BattleSetup_StartWildBattle();
                    return TRUE;
                }

                return FALSE;
            }
        }
    }

    return FALSE;
}

void RockSmashWildEncounter(void)
{
    u16 headerId = GetCurrentMapWildMonHeaderId();

    if (headerId != 0xFFFF)
    {
        const struct WildPokemonInfo *wildPokemonInfo = gWildMonHeaders[headerId].rockSmashMonsInfo;

        if (wildPokemonInfo == NULL)
        {
            gSpecialVar_Result = FALSE;
        }
        else if (DoWildEncounterRateTest(wildPokemonInfo->encounterRate, 1) == TRUE
         && TryGenerateWildMonSWSB(wildPokemonInfo, 2, WILD_CHECK_REPEL | WILD_CHECK_KEEN_EYE, headerId) == TRUE)
        {
            BattleSetup_StartWildBattle();
            gSpecialVar_Result = TRUE;
        }
        else
        {
            gSpecialVar_Result = FALSE;
        }
    }
    else
    {
        gSpecialVar_Result = FALSE;
    }
}

bool8 SweetScentWildEncounter(void)
{
    s16 x, y;
    u16 headerId;

    PlayerGetDestCoords(&x, &y);
    headerId = GetCurrentMapWildMonHeaderId();
    if (headerId == 0xFFFF)
    {
        if (gMapHeader.mapLayoutId == LAYOUT_BATTLE_FRONTIER_BATTLE_PIKE_RANDOM_ROOM3)
        {
            headerId = GetBattlePikeWildMonHeaderId();
            if (TryGenerateWildMon(gBattlePikeWildMonHeaders[headerId].landMonsInfo, WILD_AREA_LAND, 0) != TRUE)
                return FALSE;

            TryGenerateBattlePikeWildMon(FALSE);
            BattleSetup_StartBattlePikeWildBattle();
            return TRUE;
        }
        if (gMapHeader.mapLayoutId == LAYOUT_BATTLE_FRONTIER_BATTLE_PYRAMID_EMPTY_SQUARE)
        {
            headerId = gSaveBlock2Ptr->frontier.curChallengeBattleNum;
            if (TryGenerateWildMon(gBattlePyramidWildMonHeaders[headerId].landMonsInfo, WILD_AREA_LAND, 0) != TRUE)
                return FALSE;

            GenerateBattlePyramidWildMon();
            BattleSetup_StartWildBattle();
            return TRUE;
        }
    }
    else
    {
        if (MetatileBehavior_IsLandWildEncounter(MapGridGetMetatileBehaviorAt(x, y)) == TRUE)
        {
            if (gWildMonHeaders[headerId].landMonsInfo == NULL)
                return FALSE;

            if (TryStartRoamerEncounter() == TRUE)
            {
                BattleSetup_StartRoamerBattle();
                return TRUE;
            }

            if (DoMassOutbreakEncounterTest() == TRUE)
                SetUpMassOutbreakEncounter(0);
            else
                TryGenerateWildMonSWSB(gWildMonHeaders[headerId].landMonsInfo, WILD_AREA_LAND, 0, headerId);

            BattleSetup_StartWildBattle();
            return TRUE;
        }
        else if (MetatileBehavior_IsWaterWildEncounter(MapGridGetMetatileBehaviorAt(x, y)) == TRUE)
        {
            if (AreLegendariesInSootopolisPreventingEncounters() == TRUE)
                return FALSE;
            if (gWildMonHeaders[headerId].waterMonsInfo == NULL)
                return FALSE;

            if (TryStartRoamerEncounter() == TRUE)
            {
                BattleSetup_StartRoamerBattle();
                return TRUE;
            }

            TryGenerateWildMonSWSB(gWildMonHeaders[headerId].waterMonsInfo, WILD_AREA_WATER, 0, headerId);
            BattleSetup_StartWildBattle();
            return TRUE;
        }
    }

    return FALSE;
}

bool8 DoesCurrentMapHaveFishingMons(void)
{
    u16 headerId = GetCurrentMapWildMonHeaderId();

    if (headerId != 0xFFFF && gWildMonHeaders[headerId].fishingMonsInfo != NULL)
        return TRUE;
    else
        return FALSE;
}

void FishingWildEncounter(u8 rod)
{
    u16 species;

    if (CheckFeebas() == TRUE)
    {
        u8 level = ChooseWildMonLevel(&gWildFeebasRoute119Data);

        species = gWildFeebasRoute119Data.species;
        CreateWildMon(species, level);
    }
    else
    {
        species = GenerateFishingWildMon(gWildMonHeaders[GetCurrentMapWildMonHeaderId()].fishingMonsInfo, rod);
    }
    IncrementGameStat(GAME_STAT_FISHING_CAPTURES);
    SetPokemonAnglerSpecies(species);
    gIsFishingEncounter = TRUE;
    BattleSetup_StartWildBattle();
}

u16 GetLocalWildMon(bool8 *isWaterMon)
{
    u16 headerId;
    const struct WildPokemonInfo *landMonsInfo;
    const struct WildPokemonInfo *waterMonsInfo;

    *isWaterMon = FALSE;
    headerId = GetCurrentMapWildMonHeaderId();
    if (headerId == 0xFFFF)
        return SPECIES_NONE;
    landMonsInfo = gWildMonHeaders[headerId].landMonsInfo;
    waterMonsInfo = gWildMonHeaders[headerId].waterMonsInfo;
    // Neither
    if (landMonsInfo == NULL && waterMonsInfo == NULL)
        return SPECIES_NONE;
    // Land Pokemon
    else if (landMonsInfo != NULL && waterMonsInfo == NULL)
        return landMonsInfo->wildPokemon[ChooseWildMonIndex_Land()].species;
    // Water Pokemon
    else if (landMonsInfo == NULL && waterMonsInfo != NULL)
    {
        *isWaterMon = TRUE;
        return waterMonsInfo->wildPokemon[ChooseWildMonIndex_WaterRock()].species;
    }
    // Either land or water Pokemon
    if ((Random() % 100) < 80)
    {
        return landMonsInfo->wildPokemon[ChooseWildMonIndex_Land()].species;
    }
    else
    {
        *isWaterMon = TRUE;
        return waterMonsInfo->wildPokemon[ChooseWildMonIndex_WaterRock()].species;
    }
}

u16 GetLocalWaterMon(void)
{
    u16 headerId = GetCurrentMapWildMonHeaderId();

    if (headerId != 0xFFFF)
    {
        const struct WildPokemonInfo *waterMonsInfo = gWildMonHeaders[headerId].waterMonsInfo;

        if (waterMonsInfo)
            return waterMonsInfo->wildPokemon[ChooseWildMonIndex_WaterRock()].species;
    }
    return SPECIES_NONE;
}

bool8 UpdateRepelCounter(void)
{
    u16 steps;

    if (InBattlePike() || InBattlePyramid())
        return FALSE;
    if (InUnionRoom() == TRUE)
        return FALSE;

    steps = VarGet(VAR_REPEL_STEP_COUNT);

    if (steps != 0)
    {
        steps--;
        VarSet(VAR_REPEL_STEP_COUNT, steps);
        if (steps == 0)
        {
            ScriptContext1_SetupScript(EventScript_RepelWoreOff);
            return TRUE;
        }
    }
    return FALSE;
}

static bool8 IsWildLevelAllowedByRepel(u8 wildLevel)
{
    u8 i;

    if (!VarGet(VAR_REPEL_STEP_COUNT))
        return TRUE;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (GetMonData(&gPlayerParty[i], MON_DATA_HP) && !GetMonData(&gPlayerParty[i], MON_DATA_IS_EGG))
        {
            u8 ourLevel = GetMonData(&gPlayerParty[i], MON_DATA_LEVEL);

            if (wildLevel < ourLevel)
                return FALSE;
            else
                return TRUE;
        }
    }

    return FALSE;
}

static bool8 IsAbilityAllowingEncounter(u8 level)
{
    u8 ability;

    if (GetMonData(&gPlayerParty[0], MON_DATA_SANITY_IS_EGG))
        return TRUE;

    ability = GetMonAbility(&gPlayerParty[0]);
    if (ability == ABILITY_KEEN_EYE || ability == ABILITY_INTIMIDATE)
    {
        u8 playerMonLevel = GetMonData(&gPlayerParty[0], MON_DATA_LEVEL);
        if (playerMonLevel > 5 && level <= playerMonLevel - 5 && !(Random() % 2))
            return FALSE;
    }

    return TRUE;
}

static bool8 TryGetRandomWildMonIndexByType(const struct WildPokemon *wildMon, u8 type, u8 numMon, u8 *monIndex)
{
    u8 validIndexes[numMon]; // variable length array, an interesting feature
    u8 i, validMonCount;

    for (i = 0; i < numMon; i++)
        validIndexes[i] = 0;

    for (validMonCount = 0, i = 0; i < numMon; i++)
    {
        if (gBaseStats[wildMon[i].species].type1 == type || gBaseStats[wildMon[i].species].type2 == type)
            validIndexes[validMonCount++] = i;
    }

    if (validMonCount == 0 || validMonCount == numMon)
        return FALSE;

    *monIndex = validIndexes[Random() % validMonCount];
    return TRUE;
}

static bool8 TryGetAbilityInfluencedWildMonIndex(const struct WildPokemon *wildMon, u8 type, u8 ability, u8 *monIndex)
{
    if (GetMonData(&gPlayerParty[0], MON_DATA_SANITY_IS_EGG))
        return FALSE;
    else if (GetMonAbility(&gPlayerParty[0]) != ability)
        return FALSE;
    else if (Random() % 2 != 0)
        return FALSE;

    return TryGetRandomWildMonIndexByType(wildMon, type, LAND_WILD_COUNT, monIndex);
}

static bool8 TryGetRandomWildMonIndexByTypeSWSB(u8 headerID, u8 type, u8 numMon, u8 *monIndex)
{
    u8 validIndexes[numMon]; // variable length array, an interesting feature
    u8 i, validMonCount;
    u8 level;
    level = GetWildCurveFactor();

    for (i = 0; i < numMon; i++)
        validIndexes[i] = 0;

    for (validMonCount = 0, i = 0; i < numMon; i++)
    {

        if (gBaseStats[SeedGenerateSpeciesLand(headerID, i, level)].type1 == type || gBaseStats[SeedGenerateSpeciesLand(headerID, i, level)].type2 == type)
            validIndexes[validMonCount++] = i;
    }

    if (validMonCount == 0 || validMonCount == numMon)
        return FALSE;

    *monIndex = validIndexes[Random() % validMonCount];
    return TRUE;
}

static bool8 TryGetAbilityInfluencedWildMonIndexSWSB(u8 headerID, u8 type, u8 ability, u8 *monIndex)
{
    if (GetMonData(&gPlayerParty[0], MON_DATA_SANITY_IS_EGG))
        return FALSE;
    else if (GetMonAbility(&gPlayerParty[0]) != ability)
        return FALSE;
    else if (Random() % 2 != 0)
        return FALSE;

    return TryGetRandomWildMonIndexByTypeSWSB(headerID, type, 5, monIndex);
}

static void ApplyFluteEncounterRateMod(u32 *encRate)
{
    if (FlagGet(FLAG_SYS_ENC_UP_ITEM) == TRUE)
        *encRate += *encRate / 2;
    else if (FlagGet(FLAG_SYS_ENC_DOWN_ITEM) == TRUE)
        *encRate = *encRate / 2;
}

static void ApplyCleanseTagEncounterRateMod(u32 *encRate)
{
    if (GetMonData(&gPlayerParty[0], MON_DATA_HELD_ITEM) == ITEM_CLEANSE_TAG)
        *encRate = *encRate * 2 / 3;
}

static const u32 gLevelCurveTimeTable[];
static const u32 gLevelCurveTimeTable[] =
{
    0,
    720,
    1080,
    1440,
    1800,
    2160,
    2520,
    2880,
    3240,
    3600,
    4620,
    5040,
    5460,
    5880,
    6300,
    6720,
    7140,
    7560,
    7980,
    8400,
    10080,
    10560,
    11040,
    11520,
    12000,
    12480,
    12960,
    13440,
    13920,
    14400,
    16740,
    17280,
    17820,
    18360,
    18900,
    19440,
    19980,
    20520,
    21060,
    21600,
    24600,
    25200,
    25800,
    26400,
    27000,
    30360,
    31020,
    31680,
    32340,
    33000,
    33660,
    34320
};

static u8 GetWildCurveFactor(void)
{
    u8 i = 0;
		u32 PlaySeconds;
		u8 CountBadge = 0;
		u8 value;

		if (FlagGet(FLAG_BADGE01_GET))
			CountBadge++;
		if (FlagGet(FLAG_BADGE02_GET))
			CountBadge++;
		if (FlagGet(FLAG_BADGE03_GET))
			CountBadge++;
		if (FlagGet(FLAG_BADGE04_GET))
			CountBadge++;
		if (FlagGet(FLAG_BADGE05_GET))
			CountBadge++;
		if (FlagGet(FLAG_BADGE06_GET))
			CountBadge++;
		if (FlagGet(FLAG_BADGE07_GET))
			CountBadge++;

		PlaySeconds = (gSaveBlock2Ptr->playTimeHours * 60 + gSaveBlock2Ptr->playTimeMinutes) * 60 + gSaveBlock2Ptr->playTimeSeconds;
    do {
      i++;
    } while(gLevelCurveTimeTable[i] < PlaySeconds);

        value = i + Random() % 1 + CountBadge*3/2;

		return value;
}

//New wild Encounter Override
ALIGNED(2) const u16 Rarity1_list[] =
{
  SPECIES_CATERPIE,
  SPECIES_WEEDLE,
  SPECIES_PARAS,
  SPECIES_VENONAT,
  SPECIES_PINSIR,
  SPECIES_LEDYBA,
  SPECIES_SPINARAK,
  SPECIES_PINECO,
  SPECIES_WURMPLE,
  SPECIES_VOLBEAT,
  SPECIES_ILLUMISE,
  SPECIES_PIDGEY,
  SPECIES_RATTATA,
  SPECIES_SPEAROW,
  SPECIES_BELLSPROUT,
  SPECIES_SENTRET,
  SPECIES_HOOTHOOT,
  SPECIES_POOCHYENA,
  SPECIES_ZIGZAGOON,
  SPECIES_TAILLOW,
  SPECIES_WINGULL,
  SPECIES_ODDISH,
  SPECIES_KRICKETOT,
  SPECIES_BURMY,
  SPECIES_COMBEE,
  SPECIES_SEWADDLE,
  SPECIES_STARLY,
  SPECIES_BIDOOF,
  SPECIES_BUNEARY,
  SPECIES_GLAMEOW,
  SPECIES_PATRAT,
  SPECIES_LILLIPUP,
  SPECIES_AUDINO,
  SPECIES_MINCCINO,
  SPECIES_BOUFFALANT,
  SPECIES_RUFFLET,
  SPECIES_FLETCHLING,
  SPECIES_SCATTERBUG,
  SPECIES_PIKIPEK,
  SPECIES_YUNGOOS,
  SPECIES_GRUBBIN
};

ALIGNED(2) const u16 Rarity2_list[] =
{
  SPECIES_CLEFFA,
  SPECIES_MEOWTH,
  SPECIES_FARFETCHD,
  SPECIES_DODUO,
  SPECIES_LICKITUNG,
  SPECIES_HAPPINY,
  SPECIES_KANGASKHAN,
  SPECIES_TAUROS,
  SPECIES_DITTO,
  SPECIES_EEVEE,
  SPECIES_PORYGON,
  SPECIES_MUNCHLAX,
  SPECIES_IGGLYBUFF,
  SPECIES_AIPOM,
  SPECIES_DUNSPARCE,
  SPECIES_TEDDIURSA,
  SPECIES_STANTLER,
  SPECIES_SMEARGLE,
  SPECIES_MILTANK,
  SPECIES_SLAKOTH,
  SPECIES_WHISMUR,
  SPECIES_AZURILL,
  SPECIES_SKITTY,
  SPECIES_SPINDA,
  SPECIES_HIPPOPOTAS,
  SPECIES_CASTFORM,
  SPECIES_KECLEON,
  SPECIES_MANKEY,
  SPECIES_MACHOP,
  SPECIES_HERACROSS,
  SPECIES_TYROGUE,
  SPECIES_MAKUHITA,
  SPECIES_MEDITITE,
  SPECIES_GRIMER,
  SPECIES_MURKROW,
  SPECIES_SNEASEL,
  SPECIES_PURRLOIN,
  SPECIES_PIDOVE,
  SPECIES_CARVANHA,
  SPECIES_ABSOL,
  SPECIES_SANDSHREW,
  SPECIES_DIGLETT,
  SPECIES_GEODUDE,
  SPECIES_ONIX,
  SPECIES_CUBONE,
  SPECIES_RHYHORN,
  SPECIES_PHANPY,
  SPECIES_NINCADA,
  SPECIES_DRILBUR,
  SPECIES_TIMBURR,
  SPECIES_THROH,
  SPECIES_SAWK,
  SPECIES_SANDILE,
  SPECIES_SCRAGGY,
  SPECIES_ZORUA,
  SPECIES_STUNFISK,
  SPECIES_MIENFOO,
  SPECIES_VULLABY,
  SPECIES_BUNNELBY,
  SPECIES_PANCHAM,
  SPECIES_FURFROU,
  SPECIES_CRABRAWLER,
  SPECIES_MUDBRAY,
  SPECIES_STUFFUL,
  SPECIES_KOMALA
};

ALIGNED(2) const u16 Rarity3_list[] =
{
  SPECIES_ZUBAT,
  SPECIES_SCYTHER,
  SPECIES_HOPPIP,
  SPECIES_YANMA,
  SPECIES_DELIBIRD,
  SPECIES_GLIGAR,
  SPECIES_SKARMORY,
  SPECIES_SWABLU,
  SPECIES_TROPIUS,
  SPECIES_VULPIX,
  SPECIES_GROWLITHE,
  SPECIES_PONYTA,
  SPECIES_SLUGMA,
  SPECIES_HOUNDOUR,
  SPECIES_MAGBY,
  SPECIES_TORKOAL,
  SPECIES_EXEGGCUTE,
  SPECIES_TANGELA,
  SPECIES_SUNKERN,
  SPECIES_LOTAD,
  SPECIES_SHROOMISH,
  SPECIES_CACNEA,
  SPECIES_LILEEP,
  SPECIES_OMANYTE,
  SPECIES_KABUTO,
  SPECIES_BONSLY,
  SPECIES_SHUCKLE,
  SPECIES_CORSOLA,
  SPECIES_NOSEPASS,
  SPECIES_POLIWAG,
  SPECIES_PSYDUCK,
  SPECIES_SLOWPOKE,
  SPECIES_WOOPER,
  SPECIES_BARBOACH,
  SPECIES_CASTFORM,
  SPECIES_BUDEW,
  SPECIES_CRANIDOS,
  SPECIES_BUIZEL,
  SPECIES_CHERUBI,
  SPECIES_SHELLOS,
  SPECIES_CHATOT,
  SPECIES_CARNIVINE,
  SPECIES_MANTYKE,
  SPECIES_PANSAGE,
  SPECIES_PANSEAR,
  SPECIES_PANPOUR,
  SPECIES_ROGGENROLA,
  SPECIES_COTTONEE,
  SPECIES_PETILIL,
  SPECIES_DARUMAKA,
  SPECIES_MARACTUS,
  SPECIES_DWEBBLE,
  SPECIES_TIRTOUGA,
  SPECIES_ARCHEN,
  SPECIES_DUCKLETT,
  SPECIES_DEERLING,
  SPECIES_FOONGUS,
  SPECIES_FERROSEED,
  SPECIES_HEATMOR,
  SPECIES_LARVESTA,
  SPECIES_LITLEO,
  SPECIES_SKIDDO,
  SPECIES_BINACLE,
  SPECIES_HAWLUCHA,
  SPECIES_ORICORIO,
  SPECIES_ROCKRUFF,
  SPECIES_FOMANTIS,
  SPECIES_SALANDIT,
  SPECIES_BOUNSWEET,
  SPECIES_WIMPOD,
  SPECIES_MINIOR
};

ALIGNED(2) const u16 Rarity4_list[] =
{
  SPECIES_ABRA,
  SPECIES_SLOWPOKE,
  SPECIES_DROWZEE,
  SPECIES_GIRAFARIG,
  SPECIES_SMOOCHUM,
  SPECIES_RALTS,
  SPECIES_SPOINK,
  SPECIES_LUNATONE,
  SPECIES_SOLROCK,
  SPECIES_BALTOY,
  SPECIES_CHINGLING,
  SPECIES_WYNAUT,
  SPECIES_RIOLU,
  SPECIES_MAWILE,
  SPECIES_ARON,
  SPECIES_SNUBBULL,
  SPECIES_EKANS,
  SPECIES_NIDORAN_F,
  SPECIES_NIDORAN_M,
  SPECIES_ZANGOOSE,
  SPECIES_SEVIPER,
  SPECIES_SKORUPI,
  SPECIES_KARRABLAST,
  SPECIES_VENIPEDE,
  SPECIES_SHELMET,
  SPECIES_DURANT,
  SPECIES_STUNKY,
  SPECIES_BRONZOR,
  SPECIES_CROAGUNK,
  SPECIES_MUNNA,
  SPECIES_WOOBAT,
  SPECIES_SIGILYPH,
  SPECIES_TRUBBISH,
  SPECIES_GOTHITA,
  SPECIES_SOLOSIS,
  SPECIES_KLINK,
  SPECIES_ELGYEM,
  SPECIES_PAWNIARD,
  SPECIES_FLABEBE,
  SPECIES_ESPURR,
  SPECIES_HONEDGE,
  SPECIES_SPRITZEE,
  SPECIES_SWIRLIX,
  SPECIES_INKAY,
  SPECIES_SKRELP,
  SPECIES_DEDENNE,
  SPECIES_CARBINK,
  SPECIES_KLEFKI,
  SPECIES_CUTIEFLY,
  SPECIES_MORELULL,
  SPECIES_COMFEY,
  SPECIES_ORANGURU,
  SPECIES_PASSIMIAN,
  SPECIES_TOGEDEMARU,
  SPECIES_BRUXISH
};

ALIGNED(2) const u16 Rarity5_list[] =
{
  SPECIES_AERODACTYL,
  SPECIES_GASTLY,
  SPECIES_SHUPPET,
  SPECIES_DUSKULL,
  SPECIES_MISDREAVUS,
  SPECIES_SABLEYE,
  SPECIES_DRIFLOON,
  SPECIES_SPIRITOMB,
  SPECIES_YAMASK,
  SPECIES_FRILLISH,
  SPECIES_LITWICK,
  SPECIES_AXEW,
  SPECIES_DRUDDIGON,
  SPECIES_GOLETT,
  SPECIES_TYRUNT,
  SPECIES_AMAURA,
  SPECIES_PHANTUMP,
  SPECIES_PUMPKABOO,
  SPECIES_NOIBAT,
  SPECIES_SANDYGAST,
  SPECIES_TURTONATOR,
  SPECIES_MIMIKYU,
  SPECIES_DRAMPA,
  SPECIES_DHELMISE
};

ALIGNED(2) const u16 Rarity6_list[] =
{
  SPECIES_BULBASAUR,
  SPECIES_CHARMANDER,
  SPECIES_SQUIRTLE,
  SPECIES_DRATINI,
  SPECIES_CHIKORITA,
  SPECIES_CYNDAQUIL,
  SPECIES_TOTODILE,
  SPECIES_LARVITAR,
  SPECIES_TREECKO,
  SPECIES_TORCHIC,
  SPECIES_MUDKIP,
  SPECIES_BAGON,
  SPECIES_TURTWIG,
  SPECIES_CHIMCHAR,
  SPECIES_PIPLUP,
  SPECIES_GIBLE,
  SPECIES_SNIVY,
  SPECIES_TEPIG,
  SPECIES_OSHAWOTT,
  SPECIES_DEINO,
  SPECIES_CHESPIN,
  SPECIES_FENNEKIN,
  SPECIES_FROAKIE,
  SPECIES_GOOMY,
  SPECIES_ROWLET,
  SPECIES_LITTEN,
  SPECIES_POPPLIO,
  SPECIES_JANGMO_O,
  SPECIES_BELDUM,
  SPECIES_TYPE_NULL,
  SPECIES_TOGEPI
};

ALIGNED(2) const u16 Rarity1_rs_list[] =
{
  SPECIES_GEODUDE,
  SPECIES_GEODUDE,
  SPECIES_GEODUDE,
  SPECIES_GEODUDE,
  SPECIES_GEODUDE,
  SPECIES_GEODUDE,
  SPECIES_GEODUDE,
  SPECIES_GEODUDE,
  SPECIES_ROGGENROLA,
  SPECIES_ROGGENROLA,
  SPECIES_ROGGENROLA,
  SPECIES_ROGGENROLA,
  SPECIES_ROGGENROLA,
  SPECIES_ROGGENROLA,
  SPECIES_ROGGENROLA,
  SPECIES_ROGGENROLA,
  SPECIES_ROGGENROLA,
  SPECIES_ROGGENROLA,
  SPECIES_DWEBBLE,
  SPECIES_DWEBBLE,
  SPECIES_DWEBBLE,
  SPECIES_DWEBBLE,
  SPECIES_DWEBBLE,
  SPECIES_DWEBBLE,
  SPECIES_DWEBBLE,
  SPECIES_DWEBBLE,
  SPECIES_DWEBBLE,
  SPECIES_DWEBBLE,
  SPECIES_BALTOY,
  SPECIES_BALTOY,
  SPECIES_BALTOY,
  SPECIES_BALTOY,
  SPECIES_BALTOY,
  SPECIES_BALTOY,
  SPECIES_BALTOY,
  SPECIES_BALTOY,
  SPECIES_BALTOY,
  SPECIES_BALTOY
};

ALIGNED(2) const u16 Rarity2_rs_list[] =
{
  SPECIES_SHUCKLE,
  SPECIES_SHUCKLE,
  SPECIES_SHUCKLE,
  SPECIES_SHUCKLE,
  SPECIES_SHUCKLE,
  SPECIES_SHUCKLE,
  SPECIES_SHUCKLE,
  SPECIES_SHUCKLE,
  SPECIES_BINACLE,
  SPECIES_BINACLE,
  SPECIES_BINACLE,
  SPECIES_BINACLE,
  SPECIES_BINACLE,
  SPECIES_BINACLE,
  SPECIES_BINACLE,
  SPECIES_BINACLE,
  SPECIES_BINACLE,
  SPECIES_BINACLE,
  SPECIES_LUNATONE,
  SPECIES_LUNATONE,
  SPECIES_LUNATONE,
  SPECIES_LUNATONE,
  SPECIES_LUNATONE,
  SPECIES_LUNATONE,
  SPECIES_LUNATONE,
  SPECIES_LUNATONE,
  SPECIES_LUNATONE,
  SPECIES_LUNATONE,
  SPECIES_SOLROCK,
  SPECIES_SOLROCK,
  SPECIES_SOLROCK,
  SPECIES_SOLROCK,
  SPECIES_SOLROCK,
  SPECIES_SOLROCK,
  SPECIES_SOLROCK,
  SPECIES_SOLROCK,
  SPECIES_SOLROCK,
  SPECIES_SOLROCK
};

ALIGNED(2) const u16 Rarity3_rs_list[] =
{
  SPECIES_NOSEPASS,
  SPECIES_NOSEPASS,
  SPECIES_NOSEPASS,
  SPECIES_NOSEPASS,
  SPECIES_NOSEPASS,
  SPECIES_NOSEPASS,
  SPECIES_NOSEPASS,
  SPECIES_DITTO,
  SPECIES_NOSEPASS,
  SPECIES_NOSEPASS,
  SPECIES_NOSEPASS,
  SPECIES_NOSEPASS,
  SPECIES_NOSEPASS,
  SPECIES_NOSEPASS,
  SPECIES_NOSEPASS,
  SPECIES_NOSEPASS,
  SPECIES_NOSEPASS,
  SPECIES_DITTO,
  SPECIES_NOSEPASS,
  SPECIES_NOSEPASS,
  SPECIES_NOSEPASS,
  SPECIES_NOSEPASS,
  SPECIES_NOSEPASS,
  SPECIES_NOSEPASS,
  SPECIES_NOSEPASS,
  SPECIES_NOSEPASS,
  SPECIES_NOSEPASS,
  SPECIES_NOSEPASS,
  SPECIES_NOSEPASS,
  SPECIES_DITTO,
  SPECIES_NOSEPASS,
  SPECIES_NOSEPASS,
  SPECIES_NOSEPASS,
  SPECIES_NOSEPASS,
  SPECIES_NOSEPASS,
  SPECIES_NOSEPASS,
  SPECIES_NOSEPASS,
  SPECIES_DITTO
};

ALIGNED(2) const u16 Rarity1_w_list[] =
{
  SPECIES_PSYDUCK,
  SPECIES_PSYDUCK,
  SPECIES_PSYDUCK,
  SPECIES_BUIZEL,
  SPECIES_BUIZEL,
  SPECIES_BUIZEL,
  SPECIES_BUIZEL,
  SPECIES_BUIZEL,
  SPECIES_BUIZEL,
  SPECIES_WINGULL,
  SPECIES_WINGULL,
  SPECIES_WINGULL,
  SPECIES_MARILL,
  SPECIES_MARILL,
  SPECIES_MARILL,
  SPECIES_WINGULL,
  SPECIES_WINGULL,
  SPECIES_WINGULL,
  SPECIES_SHELLOS,
  SPECIES_SHELLOS,
  SPECIES_SHELLOS,
  SPECIES_DUCKLETT,
  SPECIES_DUCKLETT,
  SPECIES_DUCKLETT
};

ALIGNED(2) const u16 Rarity2_w_list[] =
{
  SPECIES_HORSEA,
  SPECIES_HORSEA,
  SPECIES_HORSEA,
  SPECIES_WOOPER,
  SPECIES_WOOPER,
  SPECIES_WOOPER,
  SPECIES_MANTYKE,
  SPECIES_MANTYKE,
  SPECIES_MANTYKE,
  SPECIES_WOOPER,
  SPECIES_WOOPER,
  SPECIES_WOOPER,
  SPECIES_FRILLISH,
  SPECIES_FRILLISH,
  SPECIES_FRILLISH,
  SPECIES_CLAUNCHER,
  SPECIES_CLAUNCHER,
  SPECIES_CLAUNCHER,
  SPECIES_TENTACOOL,
  SPECIES_TENTACOOL,
  SPECIES_TENTACOOL,
  SPECIES_KRABBY,
  SPECIES_KRABBY,
  SPECIES_KRABBY
};

ALIGNED(2) const u16 Rarity3_w_list[] =
{
  SPECIES_LAPRAS,
  SPECIES_SEEL,
  SPECIES_SPHEAL,
  SPECIES_SLOWPOKE,
  SPECIES_SURSKIT,
  SPECIES_SURSKIT,
  SPECIES_SURSKIT,
  SPECIES_SURSKIT,
  SPECIES_SURSKIT,
  SPECIES_SURSKIT,
  SPECIES_SURSKIT,
  SPECIES_SURSKIT,
  SPECIES_SURSKIT,
  SPECIES_LAPRAS,
  SPECIES_SEEL,
  SPECIES_SPHEAL,
  SPECIES_SLOWPOKE,
  SPECIES_SURSKIT,
  SPECIES_SURSKIT,
  SPECIES_SURSKIT,
  SPECIES_SURSKIT,
  SPECIES_SURSKIT,
  SPECIES_SURSKIT,
  SPECIES_SURSKIT
};

static u16 GetEvoSpecies(u16 species, u8 level)
{
  u32 i;
  for (i = 0; i < EVOS_PER_MON; i++)
  {
      if (gEvolutionTable[species][i].method == EVO_LEVEL && level >= gEvolutionTable[species][i].param)
        return gEvolutionTable[species][i].targetSpecies;
  }
  return SPECIES_NONE;
}


static u16 SeedGenerateSpeciesLand(u8 headerid, u8 rarity, u8 level)
{
  u8 pos;
  u16 index;

  //GenerateSeedFirstTime();
  switch (rarity)
  {
  case 1:
    pos = (gSaveBlock2Ptr->SeedID[0] + headerid) % 41;
    index = Rarity1_list[pos];
    break;
  case 2:
    pos = (gSaveBlock2Ptr->SeedID[1] + headerid) % 65;
    index = Rarity2_list[pos];
    break;
  case 3:
    pos = (gSaveBlock2Ptr->SeedID[2] + headerid) % 71;
    index = Rarity3_list[pos];
    break;
  case 4:
    pos = (gSaveBlock2Ptr->SeedID[3] + headerid) % 55;
    index = Rarity4_list[pos];
    break;
  case 5:
    pos = (gSaveBlock2Ptr->SeedID[4] + headerid) % 24;
    index = Rarity5_list[pos];
    break;
  case 6:
    pos = (gSaveBlock2Ptr->SeedID[5] + headerid) % 31;
    index = Rarity6_list[pos];
    //Increment if detect caught flag
    if (GetSetPokedexFlag(SpeciesToNationalPokedexNum(index), FLAG_GET_CAUGHT) == TRUE)
        pos = (gSaveBlock2Ptr->SeedID[4] + headerid) % 24;
        index = Rarity5_list[pos];
    break;
  default:
    index = 0; //to troubleshoot overflow
  }
  //force evolution under chances
  if(GetEvoSpecies(index, level) != SPECIES_NONE)
    if (Random() % 5 == 0) //chance of 20%
      index = GetEvoSpecies(index, level);
      if(GetEvoSpecies(index, level) != SPECIES_NONE)
        if (Random() % 4 == 0) //chance of 20% * 25% = 5%
          index = GetEvoSpecies(index, level);
  return index;
}

static u16 SeedGenerateSpeciesRockSmash(u8 headerid, u8 rarity, u8 level)
{
  u8 pos;
  u16 index;

  //GenerateSeedFirstTime();
  switch (rarity)
  {
  case 1:
    pos = (gSaveBlock2Ptr->SeedID[0] + headerid) % 38;
    index = Rarity1_rs_list[pos];
    break;
  case 2:
    pos = (gSaveBlock2Ptr->SeedID[1] + headerid) % 38;
    index = Rarity2_rs_list[pos];
    break;
  case 3:
    pos = (gSaveBlock2Ptr->SeedID[2] + headerid) % 38;
    index = Rarity3_rs_list[pos];
    break;
  default:
    index = 0; //to troubleshoot overflow
  }
  //force evolution under chances
  if(GetEvoSpecies(index, level) != SPECIES_NONE)
    if (Random() % 5 == 0) //chance of 20%
      index = GetEvoSpecies(index, level);
      if(GetEvoSpecies(index, level) != SPECIES_NONE)
        if (Random() % 4 == 0) //chance of 20% * 25% = 5%
          index = GetEvoSpecies(index, level);
  return index;
}

static u16 SeedGenerateSpeciesWater(u8 headerid, u8 rarity, u8 level)
{
  u8 pos;
  u16 index;

  //GenerateSeedFirstTime();
  switch (rarity)
  {
  case 1:
    pos = (gSaveBlock2Ptr->SeedID[3] + headerid) % 24;
    index = Rarity1_w_list[pos];
    break;
  case 2:
    pos = (gSaveBlock2Ptr->SeedID[4] + headerid) % 24;
    index = Rarity2_w_list[pos];
    break;
  case 3:
    pos = (gSaveBlock2Ptr->SeedID[5] + headerid) % 24;
    index = Rarity3_w_list[pos];
    break;
  default:
    index = 0; //to troubleshoot overflow
  }
  //force evolution under chances
  if(GetEvoSpecies(index, level) != SPECIES_NONE)
    if (Random() % 5 == 0) //chance of 20%
      index = GetEvoSpecies(index, level);
      if(GetEvoSpecies(index, level) != SPECIES_NONE)
        if (Random() % 4 == 0) //chance of 20% * 25% = 5%
          index = GetEvoSpecies(index, level);
  return index;
}
