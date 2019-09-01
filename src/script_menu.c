#include "global.h"
#include "main.h"
#include "event_data.h"
#include "field_effect.h"
#include "field_specials.h"
#include "item.h"
#include "list_menu.h"
#include "menu.h"
#include "palette.h"
#include "script.h"
#include "script_menu.h"
#include "sound.h"
#include "string_util.h"
#include "strings.h"
#include "task.h"
#include "text.h"
#include "constants/items.h"
#include "constants/songs.h"

// multichoice lists
const struct MenuAction MultichoiceList_000[] =
{
    {gUnknown_085EAD37, NULL},
    {gUnknown_085EAD41, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_002[] =
{
    {gUnknown_085EAD67, NULL},
    {gUnknown_085EAD6D, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_003[] =
{
    {gUnknown_085EAD72, NULL},
    {gUnknown_085EAD84, NULL},
    {gUnknown_085EAD96, NULL},
    {gText_Cancel2, NULL},
};

const struct MenuAction MultichoiceList_004[] =
{
    {gText_CoolnessContest, NULL},
    {gText_BeautyContest, NULL},
    {gText_CutenessContest, NULL},
    {gText_SmartnessContest, NULL},
    {gText_ToughnessContest, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_006[] =
{
    {gUnknown_085EADF9, NULL},
    {gUnknown_085EAE04, NULL},
    {gUnknown_085EAE12, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_005[] =
{
    {gUnknown_085EADF9, NULL},
    {gUnknown_085EAE04, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_007[] =
{
    {gMenuText_Register, NULL},
    {gUnknown_085EAE12, NULL},
    {gUnknown_085EAE1B, NULL},
    {gText_Cancel2, NULL},
};

const struct MenuAction MultichoiceList_012[] =
{
    {gUnknown_085EAE27, NULL},
    {gUnknown_085EAE2C, NULL},
};

const struct MenuAction MultichoiceList_013[] =
{
    {gUnknown_085EAE31, NULL},
    {gUnknown_085EAE35, NULL},
    {gUnknown_085EAE39, NULL},
    {gUnknown_085EAE3D, NULL},
    {gUnknown_085EAE41, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_014[] =
{
    {gUnknown_085EAD5F, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_016[] =
{
    {gUnknown_085EAE53, NULL},
    {gUnknown_085EAE5A, NULL},
};

const struct MenuAction MultichoiceList_020[] =
{
    {gText_Yes, NULL},
    {gText_No, NULL},
    {gUnknown_085EAD6D, NULL},
};

const struct MenuAction MultichoiceList_023[] =
{
    {gUnknown_085EAEA2, NULL},
    {gUnknown_085EAEAC, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_024[] =
{
    {gText_Lv50, NULL},
    {gText_OpenLevel, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_025[] =
{
    {gUnknown_0827ECBC, NULL},
    {gUnknown_0827ECC3, NULL},
    {gUnknown_0827ECCD, NULL},
};

const struct MenuAction MultichoiceList_026[] =
{
    {gUnknown_0827ECD5, NULL},
    {gUnknown_0827ECDD, NULL},
    {gUnknown_0827ECE3, NULL},
};

const struct MenuAction MultichoiceList_027[] =
{
    {gUnknown_0827ECEB, NULL},
    {gUnknown_0827ECF2, NULL},
    {gUnknown_0827ECF8, NULL},
};

const struct MenuAction MultichoiceList_028[] =
{
    {gUnknown_0827ED00, NULL},
    {gUnknown_0827ED06, NULL},
    {gUnknown_0827ED10, NULL},
};

const struct MenuAction MultichoiceList_029[] =
{
    {gUnknown_0827ED18, NULL},
    {gUnknown_0827ED22, NULL},
    {gUnknown_0827ED2C, NULL},
};

const struct MenuAction MultichoiceList_030[] =
{
    {gUnknown_0827ED36, NULL},
    {gUnknown_0827ED40, NULL},
    {gUnknown_0827ED46, NULL},
};

const struct MenuAction MultichoiceList_031[] =
{
    {gUnknown_0827ED4F, NULL},
    {gUnknown_0827ED59, NULL},
    {gUnknown_0827ED65, NULL},
};

const struct MenuAction MultichoiceList_032[] =
{
    {gUnknown_0827ED70, NULL},
    {gUnknown_0827ED74, NULL},
    {gUnknown_0827ED78, NULL},
};

const struct MenuAction MultichoiceList_033[] =
{
    {gUnknown_0827ED80, NULL},
    {gUnknown_0827ED95, NULL},
    {gUnknown_0827EDAA, NULL},
};

const struct MenuAction MultichoiceList_034[] =
{
    {gUnknown_0827EDB5, NULL},
    {gUnknown_0827EDBA, NULL},
    {gUnknown_0827EDC1, NULL},
};

const struct MenuAction MultichoiceList_035[] =
{
    {gUnknown_0827EDC9, NULL},
    {gUnknown_0827EDD5, NULL},
    {gUnknown_0827EDE4, NULL},
};

const struct MenuAction MultichoiceList_036[] =
{
    {gUnknown_0827EDF0, NULL},
    {gUnknown_0827EDF5, NULL},
    {gUnknown_0827EDF7, NULL},
};

const struct MenuAction MultichoiceList_037[] =
{
    {gUnknown_0827EDF9, NULL},
    {gUnknown_0827EDFB, NULL},
    {gUnknown_0827EDFD, NULL},
};

const struct MenuAction MultichoiceList_038[] =
{
    {gUnknown_0827EDFF, NULL},
    {gUnknown_0827EE01, NULL},
    {gUnknown_0827EE03, NULL},
};

const struct MenuAction MultichoiceList_039[] =
{
    {gUnknown_0827EE05, NULL},
    {gUnknown_0827EE07, NULL},
    {gUnknown_0827EE09, NULL},
};

const struct MenuAction MultichoiceList_042[] =
{
    {gUnknown_085EAEC3, NULL},
    {gUnknown_085EAED6, NULL},
    {gUnknown_085EAEE6, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_043[] =
{
    {gUnknown_085EAEF6, NULL},
    {gUnknown_085EAF02, NULL},
    {gUnknown_085EAF0E, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_044[] =
{
    {gUnknown_085EAF1B, NULL},
    {gUnknown_085EAF24, NULL},
    {gUnknown_085EAF2F, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_045[] =
{
    {gUnknown_085EAF34, NULL},
    {gUnknown_085EAF3E, NULL},
};

const struct MenuAction MultichoiceList_046[] =
{
    {gUnknown_085EAF4B, NULL},
    {gUnknown_085EAF58, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_047[] =
{
    {gUnknown_085EAF65, NULL},
    {gUnknown_085EAF70, NULL},
    {gUnknown_085EAF7D, NULL},
    {gUnknown_085EAF87, NULL},
    {gUnknown_085EAF93, NULL},
    {gUnknown_085EAF9F, NULL},
    {gUnknown_085EAFAB, NULL},
    {gText_Cancel2, NULL},
};

const struct MenuAction MultichoiceList_048[] =
{
    {gUnknown_085EAFB6, NULL},
    {gUnknown_085EAFCF, NULL},
    {gUnknown_085EAFE8, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_055[] =
{
    {gUnknown_085EB089, NULL},
    {gUnknown_085EB09C, NULL},
    {gUnknown_085EB0AF, NULL},
    {gUnknown_085EB0C2, NULL},
    {gUnknown_085EB0D5, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_049[] =
{
    {gUnknown_085EB002, NULL},
    {gUnknown_085EB017, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_050[] =
{
    {gUnknown_085EB02A, NULL},
    {gUnknown_085EB034, NULL},
};

const struct MenuAction MultichoiceList_052[] =
{
    {gText_LilycoveCity, NULL},
    {gText_BattleFrontier, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_053[] =
{
    {gText_SlateportCity, NULL},
    {gText_LilycoveCity, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_054[] =
{
    {gUnknown_085EB07E, NULL},
    {gUnknown_085EB084, NULL},
};

const struct MenuAction MultichoiceList_056[] =
{
    {gText_LilycoveCity, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_057[] =
{
    {gText_5F, NULL},
    {gText_4F, NULL},
    {gText_3F, NULL},
    {gText_2F, NULL},
    {gText_1F, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_058[] =
{
    {gUnknown_085EB040, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_059[] =
{
    {gUnknown_085EB04A, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_060[] =
{
    {gUnknown_085EB040, NULL},
    {gUnknown_085EB04A, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_061[] =
{
    {gUnknown_085EB057, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_062[] =
{
    {gUnknown_085EB040, NULL},
    {gUnknown_085EB057, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_063[] =
{
    {gUnknown_085EB04A, NULL},
    {gUnknown_085EB057, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_064[] =
{
    {gUnknown_085EB040, NULL},
    {gUnknown_085EB04A, NULL},
    {gUnknown_085EB057, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_065[] =
{
    {gUnknown_085EB062, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_066[] =
{
    {gUnknown_085EB040, NULL},
    {gUnknown_085EB062, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_067[] =
{
    {gUnknown_085EB04A, NULL},
    {gUnknown_085EB062, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_068[] =
{
    {gUnknown_085EB040, NULL},
    {gUnknown_085EB04A, NULL},
    {gUnknown_085EB062, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_069[] =
{
    {gUnknown_085EB057, NULL},
    {gUnknown_085EB062, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_070[] =
{
    {gUnknown_085EB040, NULL},
    {gUnknown_085EB057, NULL},
    {gUnknown_085EB062, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_071[] =
{
    {gUnknown_085EB04A, NULL},
    {gUnknown_085EB057, NULL},
    {gUnknown_085EB062, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_072[] =
{
    {gUnknown_085EB040, NULL},
    {gUnknown_085EB04A, NULL},
    {gUnknown_085EB057, NULL},
    {gUnknown_085EB062, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_073[] =
{
    {gText_Opponent, NULL},
    {gText_Tourney_Tree, NULL},
    {gText_ReadyToStart, NULL},
    {gUnknown_085EB5BC, NULL},
    {gUnknown_085EB5C3, NULL},
    {gUnknown_085EB5C8, NULL},
};

const struct MenuAction MultichoiceList_107[] =
{
    {gText_Opponent, NULL},
    {gText_Tourney_Tree, NULL},
    {gText_ReadyToStart, NULL},
    {gUnknown_085EB5C3, NULL},
    {gUnknown_085EB5C8, NULL},
};

const struct MenuAction MultichoiceList_088[] =
{
    {gUnknown_085EB29A, NULL},
    {gUnknown_085EB2A3, NULL},
};

const struct MenuAction MultichoiceList_076[] =
{
    {gUnknown_085EB372, NULL},
    {gUnknown_085EB37F, NULL},
    {gUnknown_085EB389, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_017[] =
{
    {gText_Yes, NULL},
    {gText_No, NULL},
    {gUnknown_085EAD6D, NULL},
};

const struct MenuAction MultichoiceList_018[] =
{
    {gUnknown_085EAE6E, NULL},
    {gUnknown_085EAE7C, NULL},
    {gUnknown_085EAE8A, NULL},
    {gUnknown_085EAD6D, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_078[] =
{
    {gUnknown_085EB372, NULL},
    {gUnknown_085EB37F, NULL},
    {gUnknown_085EB397, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_079[] =
{
    {gUnknown_085EB372, NULL},
    {gUnknown_085EB37F, NULL},
    {gUnknown_085EB389, NULL},
    {gUnknown_085EB397, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_074[] =
{
    {gUnknown_085EB372, NULL},
    {gUnknown_085EB37F, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_080[] =
{
    {gUnknown_085EB3A4, NULL},
    {gUnknown_085EB3B1, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_081[] =
{
    {gUnknown_085EB3D4, NULL},
    {gUnknown_085EB3C6, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_082[] =
{
    {gText_NormalRank, NULL},
    {gText_SuperRank, NULL},
    {gText_HyperRank, NULL},
    {gText_MasterRank, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_083[] =
{
    {gText_BattleBag, NULL},
    {gText_HeldItem, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_084[] =
{
    {gText_LinkContest, NULL},
    {gText_AboutE_Mode, NULL},
    {gText_AboutG_Mode, NULL},
    {gText_Cancel2, NULL},
};

const struct MenuAction MultichoiceList_085[] =
{
    {gText_E_Mode, NULL},
    {gText_G_Mode, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_086[] =
{
    {gText_MenuOptionPokedex, NULL},
    {gText_MenuOptionPokemon, NULL},
    {gText_MenuOptionBag, NULL},
    {gText_MenuOptionPokenav, NULL},
    {gUnknown_085EB278, NULL},
    {gText_MenuOptionSave, NULL},
    {gText_MenuOptionOption, NULL},
    {gText_MenuOptionExit, NULL},
};

const struct MenuAction MultichoiceList_087[] =
{
    {gUnknown_085EB28A, NULL},
    {gUnknown_085EB290, NULL},
    {gUnknown_085EB295, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_089[] =
{
    {gText_SouthernIsland, NULL},
    {gText_BirthIsland, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_090[] =
{
    {gText_SouthernIsland, NULL},
    {gText_FarawayIsland, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_091[] =
{
    {gText_BirthIsland, NULL},
    {gText_FarawayIsland, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_092[] =
{
    {gText_SouthernIsland, NULL},
    {gText_BirthIsland, NULL},
    {gText_FarawayIsland, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_093[] =
{
    {gUnknown_085EB2E4, NULL},
    {gUnknown_085EB2F0, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_094[] =
{
    {gText_Yes, NULL},
    {gUnknown_085EB2FC, NULL},
};

const struct MenuAction MultichoiceList_095[] =
{
    {gUnknown_085EB3DF, NULL},
    {gUnknown_085EB3EA, NULL},
    {gUnknown_085EB3F1, NULL},
    {gUnknown_085EB3FC, NULL},
    {gUnknown_085EB40A, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_011[] =
{
    {gUnknown_085EB415, NULL},
    {gUnknown_085EB41D, NULL},
    {gUnknown_085EB424, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_096[] =
{
    {gUnknown_085EB45C, NULL},
    {gUnknown_085EB469, NULL},
    {gUnknown_085EB475, NULL},
    {gUnknown_085EB482, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_097[] =
{
    {gUnknown_085EB42F, NULL},
    {gUnknown_085EB43A, NULL},
    {gUnknown_085EB444, NULL},
    {gUnknown_085EB451, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_098[] =
{
    {gUnknown_085EB48E, NULL},
    {gUnknown_085EB496, NULL},
    {gUnknown_085EB4A3, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_099[] =
{
    {gUnknown_085EB4AD, NULL},
    {gUnknown_085EB4B9, NULL},
    {gUnknown_085EB4C7, NULL},
    {gUnknown_085EB4D4, NULL},
    {gUnknown_085EB4E0, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_100[] =
{
    {gText_BattleBasics, NULL},
    {gText_PokemonNature, NULL},
    {gText_PokemonMoves, NULL},
    {gText_Underpowered, NULL},
    {gText_WhenInDanger, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_101[] =
{
    {gUnknown_085EB532, NULL},
    {gUnknown_085EB543, NULL},
    {gUnknown_085EB555, NULL},
    {gUnknown_085EB563, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_102[] =
{
    {gUnknown_085EB56E, NULL},
    {gUnknown_085EB57E, NULL},
    {gUnknown_085EB589, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_103[] =
{
    {gUnknown_085EB5B6, NULL},
    {gUnknown_085EB5BC, NULL},
    {gUnknown_085EB5C3, NULL},
    {gUnknown_085EB5C8, NULL},
};

const struct MenuAction MultichoiceList_104[] =
{
    {gUnknown_085EB5B6, NULL},
    {gUnknown_085EB5C3, NULL},
    {gUnknown_085EB5C8, NULL},
};

const struct MenuAction MultichoiceList_105[] =
{
    {gUnknown_085EB5B6, NULL},
    {gUnknown_085EB5BC, NULL},
    {gUnknown_085EB5C8, NULL},
};

const struct MenuAction MultichoiceList_106[] =
{
    {gUnknown_085EB5B6, NULL},
    {gUnknown_085EB5C8, NULL},
};

const struct MenuAction MultichoiceList_108[] =
{
    {gUnknown_085EE14B, NULL},
    {gUnknown_085EE14F, NULL},
};

const struct MenuAction MultichoiceList_109[] =
{
    {gUnknown_085EB2FF, NULL},
    {gUnknown_085EB310, NULL},
    {gUnknown_085EB317, NULL},
    {gUnknown_085EB31F, NULL},
};

const struct MenuAction MultichoiceList_110[] =
{
    {gText_CaveOfOrigin, NULL},
    {gText_MtPyre, NULL},
    {gText_SkyPillar, NULL},
    {gText_DontRemember, NULL},
};

const struct MenuAction MultichoiceList_111[] =
{
    {gUnknown_085EB4AD, NULL},
    {gUnknown_085EB4B9, NULL},
    {gUnknown_085EB4C7, NULL},
    {gUnknown_085EB4D4, NULL},
    {gUnknown_085EB597, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_112[] =
{
    {gText_BattleTrainers, NULL},
    {gUnknown_085EB45C, NULL},
    {gUnknown_085EB469, NULL},
    {gUnknown_085EB475, NULL},
    {gUnknown_085EB482, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_113[] =
{
    {gText_NormalTagMatch, NULL},
    {gText_VarietyTagMatch, NULL},
    {gText_UniqueTagMatch, NULL},
    {gText_ExpertTagMatch, NULL},
    {gText_Exit, NULL},
};

const struct MenuAction MultichoiceList_001[] =
{
    {gText_Exit, NULL},
};

struct MultichoiceListStruct
{
    const struct MenuAction *list;
    u8 count;
};

const struct MultichoiceListStruct gMultichoiceLists[] =
{
    {MultichoiceList_000, ARRAY_COUNT(MultichoiceList_000)},
    {MultichoiceList_001, ARRAY_COUNT(MultichoiceList_001)},
    {MultichoiceList_002, ARRAY_COUNT(MultichoiceList_002)},
    {MultichoiceList_003, ARRAY_COUNT(MultichoiceList_003)},
    {MultichoiceList_004, ARRAY_COUNT(MultichoiceList_004)},
    {MultichoiceList_005, ARRAY_COUNT(MultichoiceList_005)},
    {MultichoiceList_006, ARRAY_COUNT(MultichoiceList_006)},
    {MultichoiceList_007, ARRAY_COUNT(MultichoiceList_007)},
    {MultichoiceList_001, ARRAY_COUNT(MultichoiceList_001)},
    {MultichoiceList_001, ARRAY_COUNT(MultichoiceList_001)},
    {MultichoiceList_001, ARRAY_COUNT(MultichoiceList_001)},
    {MultichoiceList_011, ARRAY_COUNT(MultichoiceList_011)},
    {MultichoiceList_012, ARRAY_COUNT(MultichoiceList_012)},
    {MultichoiceList_013, ARRAY_COUNT(MultichoiceList_013)},
    {MultichoiceList_014, ARRAY_COUNT(MultichoiceList_014)},
    {MultichoiceList_001, ARRAY_COUNT(MultichoiceList_001)},
    {MultichoiceList_016, ARRAY_COUNT(MultichoiceList_016)},
    {MultichoiceList_017, ARRAY_COUNT(MultichoiceList_017)},
    {MultichoiceList_018, ARRAY_COUNT(MultichoiceList_018)},
    {MultichoiceList_001, ARRAY_COUNT(MultichoiceList_001)},
    {MultichoiceList_020, ARRAY_COUNT(MultichoiceList_020)},
    {MultichoiceList_001, ARRAY_COUNT(MultichoiceList_001)},
    {MultichoiceList_001, ARRAY_COUNT(MultichoiceList_001)},
    {MultichoiceList_023, ARRAY_COUNT(MultichoiceList_023)},
    {MultichoiceList_024, ARRAY_COUNT(MultichoiceList_024)},
    {MultichoiceList_025, ARRAY_COUNT(MultichoiceList_025)},
    {MultichoiceList_026, ARRAY_COUNT(MultichoiceList_026)},
    {MultichoiceList_027, ARRAY_COUNT(MultichoiceList_027)},
    {MultichoiceList_028, ARRAY_COUNT(MultichoiceList_028)},
    {MultichoiceList_029, ARRAY_COUNT(MultichoiceList_029)},
    {MultichoiceList_030, ARRAY_COUNT(MultichoiceList_030)},
    {MultichoiceList_031, ARRAY_COUNT(MultichoiceList_031)},
    {MultichoiceList_032, ARRAY_COUNT(MultichoiceList_032)},
    {MultichoiceList_033, ARRAY_COUNT(MultichoiceList_033)},
    {MultichoiceList_034, ARRAY_COUNT(MultichoiceList_034)},
    {MultichoiceList_035, ARRAY_COUNT(MultichoiceList_035)},
    {MultichoiceList_036, ARRAY_COUNT(MultichoiceList_036)},
    {MultichoiceList_037, ARRAY_COUNT(MultichoiceList_037)},
    {MultichoiceList_038, ARRAY_COUNT(MultichoiceList_038)},
    {MultichoiceList_039, ARRAY_COUNT(MultichoiceList_039)},
    {MultichoiceList_001, ARRAY_COUNT(MultichoiceList_001)},
    {MultichoiceList_001, ARRAY_COUNT(MultichoiceList_001)},
    {MultichoiceList_042, ARRAY_COUNT(MultichoiceList_042)},
    {MultichoiceList_043, ARRAY_COUNT(MultichoiceList_043)},
    {MultichoiceList_044, ARRAY_COUNT(MultichoiceList_044)},
    {MultichoiceList_045, ARRAY_COUNT(MultichoiceList_045)},
    {MultichoiceList_046, ARRAY_COUNT(MultichoiceList_046)},
    {MultichoiceList_047, ARRAY_COUNT(MultichoiceList_047)},
    {MultichoiceList_048, ARRAY_COUNT(MultichoiceList_048)},
    {MultichoiceList_049, ARRAY_COUNT(MultichoiceList_049)},
    {MultichoiceList_050, ARRAY_COUNT(MultichoiceList_050)},
    {MultichoiceList_001, ARRAY_COUNT(MultichoiceList_001)},
    {MultichoiceList_052, ARRAY_COUNT(MultichoiceList_052)},
    {MultichoiceList_053, ARRAY_COUNT(MultichoiceList_053)},
    {MultichoiceList_054, ARRAY_COUNT(MultichoiceList_054)},
    {MultichoiceList_055, ARRAY_COUNT(MultichoiceList_055)},
    {MultichoiceList_056, ARRAY_COUNT(MultichoiceList_056)},
    {MultichoiceList_057, ARRAY_COUNT(MultichoiceList_057)},
    {MultichoiceList_058, ARRAY_COUNT(MultichoiceList_058)},
    {MultichoiceList_059, ARRAY_COUNT(MultichoiceList_059)},
    {MultichoiceList_060, ARRAY_COUNT(MultichoiceList_060)},
    {MultichoiceList_061, ARRAY_COUNT(MultichoiceList_061)},
    {MultichoiceList_062, ARRAY_COUNT(MultichoiceList_062)},
    {MultichoiceList_063, ARRAY_COUNT(MultichoiceList_063)},
    {MultichoiceList_064, ARRAY_COUNT(MultichoiceList_064)},
    {MultichoiceList_065, ARRAY_COUNT(MultichoiceList_065)},
    {MultichoiceList_066, ARRAY_COUNT(MultichoiceList_066)},
    {MultichoiceList_067, ARRAY_COUNT(MultichoiceList_067)},
    {MultichoiceList_068, ARRAY_COUNT(MultichoiceList_068)},
    {MultichoiceList_069, ARRAY_COUNT(MultichoiceList_069)},
    {MultichoiceList_070, ARRAY_COUNT(MultichoiceList_070)},
    {MultichoiceList_071, ARRAY_COUNT(MultichoiceList_071)},
    {MultichoiceList_072, ARRAY_COUNT(MultichoiceList_072)},
    {MultichoiceList_073, ARRAY_COUNT(MultichoiceList_073)},
    {MultichoiceList_074, ARRAY_COUNT(MultichoiceList_074)},
    {MultichoiceList_074, ARRAY_COUNT(MultichoiceList_074)},
    {MultichoiceList_076, ARRAY_COUNT(MultichoiceList_076)},
    {MultichoiceList_076, ARRAY_COUNT(MultichoiceList_076)},
    {MultichoiceList_078, ARRAY_COUNT(MultichoiceList_078)},
    {MultichoiceList_079, ARRAY_COUNT(MultichoiceList_079)},
    {MultichoiceList_080, ARRAY_COUNT(MultichoiceList_080)},
    {MultichoiceList_081, ARRAY_COUNT(MultichoiceList_081)},
    {MultichoiceList_082, ARRAY_COUNT(MultichoiceList_082)},
    {MultichoiceList_083, ARRAY_COUNT(MultichoiceList_083)},
    {MultichoiceList_084, ARRAY_COUNT(MultichoiceList_084)},
    {MultichoiceList_085, ARRAY_COUNT(MultichoiceList_085)},
    {MultichoiceList_086, ARRAY_COUNT(MultichoiceList_086)},
    {MultichoiceList_087, ARRAY_COUNT(MultichoiceList_087)},
    {MultichoiceList_088, ARRAY_COUNT(MultichoiceList_088)},
    {MultichoiceList_089, ARRAY_COUNT(MultichoiceList_089)},
    {MultichoiceList_090, ARRAY_COUNT(MultichoiceList_090)},
    {MultichoiceList_091, ARRAY_COUNT(MultichoiceList_091)},
    {MultichoiceList_092, ARRAY_COUNT(MultichoiceList_092)},
    {MultichoiceList_093, ARRAY_COUNT(MultichoiceList_093)},
    {MultichoiceList_094, ARRAY_COUNT(MultichoiceList_094)},
    {MultichoiceList_095, ARRAY_COUNT(MultichoiceList_095)},
    {MultichoiceList_096, ARRAY_COUNT(MultichoiceList_096)},
    {MultichoiceList_097, ARRAY_COUNT(MultichoiceList_097)},
    {MultichoiceList_098, ARRAY_COUNT(MultichoiceList_098)},
    {MultichoiceList_099, ARRAY_COUNT(MultichoiceList_099)},
    {MultichoiceList_100, ARRAY_COUNT(MultichoiceList_100)},
    {MultichoiceList_101, ARRAY_COUNT(MultichoiceList_101)},
    {MultichoiceList_102, ARRAY_COUNT(MultichoiceList_102)},
    {MultichoiceList_103, ARRAY_COUNT(MultichoiceList_103)},
    {MultichoiceList_104, ARRAY_COUNT(MultichoiceList_104)},
    {MultichoiceList_105, ARRAY_COUNT(MultichoiceList_105)},
    {MultichoiceList_106, ARRAY_COUNT(MultichoiceList_106)},
    {MultichoiceList_107, ARRAY_COUNT(MultichoiceList_107)},
    {MultichoiceList_108, ARRAY_COUNT(MultichoiceList_108)},
    {MultichoiceList_109, ARRAY_COUNT(MultichoiceList_109)},
    {MultichoiceList_110, ARRAY_COUNT(MultichoiceList_110)},
    {MultichoiceList_111, ARRAY_COUNT(MultichoiceList_111)},
    {MultichoiceList_112, ARRAY_COUNT(MultichoiceList_112)},
    {MultichoiceList_113, ARRAY_COUNT(MultichoiceList_113)},
};

const u8 *const gUnknown_0858BAF0[] =
{
    gText_Cool,
    gText_Beauty,
    gText_Cute,
    gText_Smart,
    gText_Tough,
    gText_Normal,
    gText_Super,
    gText_Hyper,
    gText_Master,
    gText_Cool2,
    gText_Beauty2,
    gText_Cute2,
    gText_Smart2,
    gText_Tough2,
    gText_Items,
    gText_Key_Items,
    gText_Poke_Balls,
    gText_TMs_Hms,
    gText_Berries2,
    gText_Single2,
    gText_Double2,
    gText_Multi,
    gText_MultiLink,
    gText_BattleTower2,
    gText_BattleDome,
    gText_BattleFactory,
    gText_BattlePalace,
    gText_BattleArena,
    gText_BattlePike,
    gText_BattlePyramid,
    gText_Medicine,
    gText_MegaStone,
    gText_ZCrystal,
};

const u8 gUnknown_0858BB68[] = { 74, 75, 76, 77, 78, 79 };

const u8 *const sPCNameStrings[] =
{
    gText_SomeonesPC,
    gText_LanettesPC,
    gText_PlayersPC,
    gText_LogOff,
};

const u8 *const gUnknown_0858BB80[] =
{
    gText_SlateportCity,
    gText_BattleFrontier,
    gText_SouthernIsland,
    gText_NavelRock,
    gText_BirthIsland,
    gText_FarawayIsland,
    gText_Exit,
};

const u8 *const gUnknown_0858BB9C[] =
{
    OldaleTown_PokemonCenter_2F_Text_277F1B,
    OldaleTown_PokemonCenter_2F_Text_277F5A,
    OldaleTown_PokemonCenter_2F_Text_277F96,
    OldaleTown_PokemonCenter_2F_Text_27889C,
};
const u8 *const gUnknown_0858BBAC[] =
{
    OldaleTown_PokemonCenter_2F_Text_27879F,
    OldaleTown_PokemonCenter_2F_Text_2787D5,
    OldaleTown_PokemonCenter_2F_Text_278831,
    OldaleTown_PokemonCenter_2F_Text_27889C,
};
const u8 *const gUnknown_0858BBBC[] =
{
    OldaleTown_PokemonCenter_2F_Text_27879F,
    OldaleTown_PokemonCenter_2F_Text_2787D5,
    OldaleTown_PokemonCenter_2F_Text_2787FC,
    OldaleTown_PokemonCenter_2F_Text_27889C,
};
const u8 *const gUnknown_0858BBCC[] =
{
    OldaleTown_PokemonCenter_2F_Text_27879F,
    OldaleTown_PokemonCenter_2F_Text_2787D5,
    OldaleTown_PokemonCenter_2F_Text_278831,
    OldaleTown_PokemonCenter_2F_Text_2787FC,
    OldaleTown_PokemonCenter_2F_Text_27889C,
};
const u8 *const gUnknown_0858BBE0[] =
{
    OldaleTown_PokemonCenter_2F_Text_277F1B,
    OldaleTown_PokemonCenter_2F_Text_277F5A,
    OldaleTown_PokemonCenter_2F_Text_27889C,
};
const u8 *const gUnknown_0858BBEC[] =
{
    OldaleTown_PokemonCenter_2F_Text_27879F,
    OldaleTown_PokemonCenter_2F_Text_2787D5,
    OldaleTown_PokemonCenter_2F_Text_27889C,
};

EWRAM_DATA u8 gUnknown_02039F90 = 0;

static u8 gUnknown_03001124[7];
static u32 filler_0300112c;

static void Task_HandleMultichoiceInput(u8);
static void Task_HandleYesNoInput(u8);
static void Task_HandleMultichoiceGridInput(u8);
static void DrawMultichoiceMenu(u8, u8, u8, bool8, u8);
static void sub_80E1FBC(u8, u8, u8, u8);
static void sub_80E2A94(u8);
static void CreatePCMenu(void);
static void sub_80E2578(void);
static bool8 IsPicboxClosed(void);
static void CreateStartMenu(void);
static void sub_80E2CC4(u8, u8, u8, u8);

bool8 ScriptMenu_Multichoice(u8 left, u8 top, u8 multichoiceId, u8 ignoreBPress)
{
    if (FuncIsActiveTask(Task_HandleMultichoiceInput) == TRUE)
    {
        return FALSE;
    }
    else
    {
        gSpecialVar_Result = 0xFF;
        DrawMultichoiceMenu(left, top, multichoiceId, ignoreBPress, 0);
        return TRUE;
    }
}

bool8 ScriptMenu_MultichoiceWithDefault(u8 left, u8 top, u8 multichoiceId, bool8 ignoreBPress, u8 defaultChoice)
{
    if (FuncIsActiveTask(Task_HandleMultichoiceInput) == TRUE)
    {
        return FALSE;
    }
    else
    {
        gSpecialVar_Result = 0xFF;
        DrawMultichoiceMenu(left, top, multichoiceId, ignoreBPress, defaultChoice);
        return TRUE;
    }
}

static u16 sub_80E1EB8(const u8 *str)
{
    u16 length = 0;

    while (*str != EOS)
    {
        if (*str == PLACEHOLDER_BEGIN)
        {
            str++;
            if (*str == 1)
            {
                length += StringLength(gSaveBlock2Ptr->playerName);
                str++;
            }
        }
        else
        {
            str++;
            length++;
        }
    }

    return length;
}

static void DrawMultichoiceMenuCustom(u8 left, u8 top, u8 multichoiceId, u8 ignoreBPress, u8 cursorPos, const struct MenuAction *actions, int count)
{
    int i;
    u8 windowId;
    int width = 0;
    u8 newWidth;

    for (i = 0; i < count; i++)
    {
        width = display_text_and_get_width(actions[i].text, width);
    }

    newWidth = convert_pixel_width_to_tile_width(width);
    left = sub_80E2D5C(left, newWidth);
    windowId = CreateWindowFromRect(left, top, newWidth, count * 2);
    SetStandardWindowBorderStyle(windowId, 0);
    PrintMenuTable(windowId, count, actions);
    InitMenuInUpperLeftCornerPlaySoundWhenAPressed(windowId, count, cursorPos);
    schedule_bg_copy_tilemap_to_vram(0);
    sub_80E1FBC(ignoreBPress, count, windowId, multichoiceId);
}

static void DrawMultichoiceMenu(u8 left, u8 top, u8 multichoiceId, u8 ignoreBPress, u8 cursorPos)
{
    DrawMultichoiceMenuCustom(left, top, multichoiceId, ignoreBPress, cursorPos, gMultichoiceLists[multichoiceId].list, gMultichoiceLists[multichoiceId].count);
}

void TryDrawRepelMenu(void)
{
    static const u16 repelItems[] = {ITEM_REPEL, ITEM_SUPER_REPEL, ITEM_MAX_REPEL};
    struct MenuAction menuItems[4] = {NULL};
    int i, count = 0;

    for (i = 0; i < ARRAY_COUNT(repelItems); i++)
    {
        if (CheckBagHasItem(repelItems[i], 1))
        {
            VarSet(VAR_0x8004 + count, repelItems[i]);
            menuItems[count].text = ItemId_GetName(repelItems[i]);
            count++;
        }
    }

    if (count > 1)
        DrawMultichoiceMenuCustom(0, 0, 0, FALSE, 0, menuItems, count);

    gSpecialVar_Result = (count > 1);
}

void HandleRepelMenuChoice(void)
{
    gSpecialVar_0x8004 = VarGet(VAR_0x8004 + gSpecialVar_Result); // Get item Id;
    VarSet(VAR_REPEL_STEP_COUNT, ItemId_GetHoldEffectParam(gSpecialVar_0x8004));
}

#define tLeft           data[0]
#define tTop            data[1]
#define tRight          data[2]
#define tBottom         data[3]
#define tIgnoreBPress   data[4]
#define tDoWrap         data[5]
#define tWindowId       data[6]
#define tMultichoiceId  data[7]

static void sub_80E1FBC(u8 ignoreBPress, u8 count, u8 windowId, u8 multichoiceId)
{
    u8 i;
    u8 taskId;
    gUnknown_02039F90 = 2;

    for (i = 0; i < 6; i++)
    {
        if (gUnknown_0858BB68[i] == multichoiceId)
        {
            gUnknown_02039F90 = 12;
        }
    }

    taskId = CreateTask(Task_HandleMultichoiceInput, 80);

    gTasks[taskId].tIgnoreBPress = ignoreBPress;

    if (count > 3)
        gTasks[taskId].tDoWrap = TRUE;
    else
        gTasks[taskId].tDoWrap = FALSE;

    gTasks[taskId].tWindowId = windowId;
    gTasks[taskId].tMultichoiceId = multichoiceId;

    sub_80E2A94(multichoiceId);
}

static void Task_HandleMultichoiceInput(u8 taskId)
{
    s8 selection;
    s16 *data = gTasks[taskId].data;

    if (!gPaletteFade.active)
    {
        if (gUnknown_02039F90)
        {
            gUnknown_02039F90--;
        }
        else
        {
            if (!tDoWrap)
                selection = Menu_ProcessInputNoWrap();
            else
                selection = Menu_ProcessInput();

            if (gMain.newKeys & (DPAD_UP | DPAD_DOWN))
            {
                sub_80E2A94(tMultichoiceId);
            }

            if (selection != MENU_NOTHING_CHOSEN)
            {
                if (selection == MENU_B_PRESSED)
                {
                    if (tIgnoreBPress)
                        return;
                    PlaySE(SE_SELECT);
                    gSpecialVar_Result = 127;
                }
                else
                {
                    gSpecialVar_Result = selection;
                }
                ClearToTransparentAndRemoveWindow(tWindowId);
                DestroyTask(taskId);
                EnableBothScriptContexts();
            }
        }
    }
}

bool8 ScriptMenu_YesNo(u8 left, u8 top)
{
    u8 taskId;

    if (FuncIsActiveTask(Task_HandleYesNoInput) == TRUE)
    {
        return FALSE;
    }
    else
    {
        gSpecialVar_Result = 0xFF;
        DisplayYesNoMenuDefaultYes();
        taskId = CreateTask(Task_HandleYesNoInput, 0x50);
        return TRUE;
    }
}

// unused
bool8 IsScriptActive(void)
{
    if (gSpecialVar_Result == 0xFF)
        return FALSE;
    else
        return TRUE;
}

static void Task_HandleYesNoInput(u8 taskId)
{
    if (gTasks[taskId].tRight < 5)
    {
        gTasks[taskId].tRight++;
        return;
    }

    switch (Menu_ProcessInputNoWrapClearOnChoose())
    {
    case MENU_NOTHING_CHOSEN:
        return;
    case MENU_B_PRESSED:
    case 1:
        PlaySE(SE_SELECT);
        gSpecialVar_Result = 0;
        break;
    case 0:
        gSpecialVar_Result = 1;
        break;
    }

    DestroyTask(taskId);
    EnableBothScriptContexts();
}

bool8 ScriptMenu_MultichoiceGrid(u8 left, u8 top, u8 multichoiceId, u8 ignoreBPress, u8 columnCount)
{
    if (FuncIsActiveTask(Task_HandleMultichoiceGridInput) == TRUE)
    {
        return FALSE;
    }
    else
    {
        u8 taskId;
        u8 rowCount, newWidth;
        int i, width;

        gSpecialVar_Result = 0xFF;
        width = 0;

        for (i = 0; i < gMultichoiceLists[multichoiceId].count; i++)
        {
            width = display_text_and_get_width(gMultichoiceLists[multichoiceId].list[i].text, width);
        }

        newWidth = convert_pixel_width_to_tile_width(width);

        left = sub_80E2D5C(left, columnCount * newWidth);
        rowCount = gMultichoiceLists[multichoiceId].count / columnCount;

        taskId = CreateTask(Task_HandleMultichoiceGridInput, 80);

        gTasks[taskId].tIgnoreBPress = ignoreBPress;
        gTasks[taskId].tWindowId = CreateWindowFromRect(left, top, columnCount * newWidth, rowCount * 2);
        SetStandardWindowBorderStyle(gTasks[taskId].tWindowId, 0);
        PrintMenuGridTable(gTasks[taskId].tWindowId, newWidth * 8, columnCount, rowCount, gMultichoiceLists[multichoiceId].list);
        sub_8199944(gTasks[taskId].tWindowId, newWidth * 8, columnCount, rowCount, 0);
        CopyWindowToVram(gTasks[taskId].tWindowId, 3);
        return TRUE;
    }
}

static void Task_HandleMultichoiceGridInput(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    s8 selection = Menu_ProcessInputGridLayout();

    switch (selection)
    {
    case MENU_NOTHING_CHOSEN:
        return;
    case MENU_B_PRESSED:
        if (tIgnoreBPress)
            return;
        PlaySE(SE_SELECT);
        gSpecialVar_Result = 0x7F;
        break;
    default:
        gSpecialVar_Result = selection;
        break;
    }

    ClearToTransparentAndRemoveWindow(tWindowId);
    DestroyTask(taskId);
    EnableBothScriptContexts();
}

#undef tWindowId

bool16 ScrSpecial_CreatePCMenu(void)
{
    if (FuncIsActiveTask(Task_HandleMultichoiceInput) == TRUE)
    {
        return FALSE;
    }
    else
    {
        gSpecialVar_Result = 0xFF;
        CreatePCMenu();
        return TRUE;
    }
}

static void CreatePCMenu(void)
{
    u8 y = 8;
    u32 pixelWidth = 0;
    u8 width;
    u8 numChoices;
    u8 windowId;
    int i;

    for (i = 0; i < ARRAY_COUNT(sPCNameStrings); i++)
    {
        pixelWidth = display_text_and_get_width(sPCNameStrings[i], pixelWidth);
    }

    if (FlagGet(FLAG_SYS_GAME_CLEAR))
    {
        pixelWidth = display_text_and_get_width(gText_HallOfFame, pixelWidth);
    }

    width = convert_pixel_width_to_tile_width(pixelWidth);

    if (FlagGet(FLAG_SYS_GAME_CLEAR)) // player has cleared game?
    {
        numChoices = 4;
        windowId = CreateWindowFromRect(0, 0, width, 8);
        SetStandardWindowBorderStyle(windowId, 0);
        AddTextPrinterParameterized(windowId, 1, gText_HallOfFame, y, 33, TEXT_SPEED_FF, NULL);
        AddTextPrinterParameterized(windowId, 1, gText_LogOff, y, 49, TEXT_SPEED_FF, NULL);
    }
    else
    {
        numChoices = 3;
        windowId = CreateWindowFromRect(0, 0, width, 6);
        SetStandardWindowBorderStyle(windowId, 0);
        AddTextPrinterParameterized(windowId, 1, gText_LogOff, y, 33, TEXT_SPEED_FF, NULL);
    }

    if (FlagGet(FLAG_SYS_PC_LANETTE)) // player met lanette?
        AddTextPrinterParameterized(windowId, 1, gText_LanettesPC, y, 1, TEXT_SPEED_FF, NULL);
    else
        AddTextPrinterParameterized(windowId, 1, gText_SomeonesPC, y, 1, TEXT_SPEED_FF, NULL);

    StringExpandPlaceholders(gStringVar4, gText_PlayersPC);
    PrintPlayerNameOnWindow(windowId, gStringVar4, y, 17);
    InitMenuInUpperLeftCornerPlaySoundWhenAPressed(windowId, numChoices, 0);
    CopyWindowToVram(windowId, 3);
    sub_80E1FBC(FALSE, numChoices, windowId, 1);
}

void ScriptMenu_DisplayPCStartupPrompt(void)
{
    sub_819786C(0, TRUE);
    AddTextPrinterParameterized2(0, 1, gText_WhichPCShouldBeAccessed, 0, NULL, 2, 1, 3);
}

bool8 sub_80E2548(void)
{
    if (FuncIsActiveTask(Task_HandleMultichoiceInput) == TRUE)
    {
        return FALSE;
    }
    else
    {
        gSpecialVar_Result = 0xFF;
        sub_80E2578();
        return TRUE;
    }
}

static void sub_80E2578(void)
{
    u8 temp = 0;
    u8 count;
    u32 pixelWidth;
    u8 width;
    u8 windowId;
    u8 i;
    u32 j;

    for (i = 0; i < ARRAY_COUNT(gUnknown_03001124); i++)
    {
        gUnknown_03001124[i] = 0xFF;
    }

    GetFontAttribute(1, FONTATTR_MAX_LETTER_WIDTH);

    if (gSpecialVar_0x8004 == 0)
    {
        gUnknown_03001124[temp] = 0;
        temp++;
        if (FlagGet(FLAG_MET_SCOTT_ON_SS_TIDAL) == TRUE)
        {
            gUnknown_03001124[temp] = 1;
            temp++;
        }
    }

    if (CheckBagHasItem(ITEM_EON_TICKET, 1) == TRUE && FlagGet(FLAG_SYS_HAS_EON_TICKET) == TRUE)
    {
        if (gSpecialVar_0x8004 == 0)
        {
            gUnknown_03001124[temp] = 2;
            temp++;
        }

        if (gSpecialVar_0x8004 == 1 && FlagGet(FLAG_HAS_EON_TICKET) == FALSE)
        {
            gUnknown_03001124[temp] = 2;
            temp++;
            FlagSet(FLAG_HAS_EON_TICKET);
        }
    }

    if (CheckBagHasItem(ITEM_MYSTIC_TICKET, 1) == TRUE && FlagGet(FLAG_ENABLE_SHIP_NAVEL_ROCK) == TRUE)
    {
        if (gSpecialVar_0x8004 == 0)
        {
            gUnknown_03001124[temp] = 3;
            temp++;
        }

        if (gSpecialVar_0x8004 == 1 && FlagGet(FLAG_HAS_MYSTIC_TICKET) == FALSE)
        {
            gUnknown_03001124[temp] = 3;
            temp++;
            FlagSet(FLAG_HAS_MYSTIC_TICKET);
        }
    }

    if (CheckBagHasItem(ITEM_AURORA_TICKET, 1) == TRUE && FlagGet(FLAG_ENABLE_SHIP_BIRTH_ISLAND) == TRUE)
    {
        if (gSpecialVar_0x8004 == 0)
        {
            gUnknown_03001124[temp] = 4;
            temp++;
        }

        if (gSpecialVar_0x8004 == 1 && FlagGet(FLAG_HAS_AURORA_TICKET) == FALSE)
        {
            gUnknown_03001124[temp] = 4;
            temp++;
            FlagSet(FLAG_HAS_AURORA_TICKET);
        }
    }

    if (CheckBagHasItem(ITEM_OLD_SEA_MAP, 1) == TRUE && FlagGet(FLAG_ENABLE_SHIP_FARAWAY_ISLAND) == TRUE)
    {
        if (gSpecialVar_0x8004 == 0)
        {
            gUnknown_03001124[temp] = 5;
            temp++;
        }

        if (gSpecialVar_0x8004 == 1 && FlagGet(FLAG_HAS_OLD_SEA_MAP) == FALSE)
        {
            gUnknown_03001124[temp] = 5;
            temp++;
            FlagSet(FLAG_HAS_OLD_SEA_MAP);
        }
    }

    gUnknown_03001124[temp] = 6;
    temp++;

    if (gSpecialVar_0x8004 == 0 && FlagGet(FLAG_MET_SCOTT_ON_SS_TIDAL) == TRUE)
    {
        count = temp;
    }

    count = temp;
    if (count == 7)
    {
        gSpecialVar_0x8004 = 11;
        sub_813A128();
    }
    else
    {
        pixelWidth = 0;

        for (j = 0; j < ARRAY_COUNT(gUnknown_0858BB80); j++)
        {
            u8 test = gUnknown_03001124[j];
            if (test != 0xFF)
            {
                pixelWidth = display_text_and_get_width(gUnknown_0858BB80[test], pixelWidth);
            }
        }

        width = convert_pixel_width_to_tile_width(pixelWidth);
        windowId = CreateWindowFromRect(28 - width, (6 - count) * 2, width, count * 2);
        SetStandardWindowBorderStyle(windowId, 0);

        for (temp = 0, i = 0; i < ARRAY_COUNT(gUnknown_0858BB80); i++)
        {
            if (gUnknown_03001124[i] != 0xFF)
            {
                AddTextPrinterParameterized(windowId, 1, gUnknown_0858BB80[gUnknown_03001124[i]], 8, temp * 16 + 1, TEXT_SPEED_FF, NULL);
                temp++;
            }
        }

        InitMenuInUpperLeftCornerPlaySoundWhenAPressed(windowId, count, count - 1);
        CopyWindowToVram(windowId, 3);
        sub_80E1FBC(FALSE, count, windowId, 8);
    }
}

void sub_80E2878(void)
{
    if (gSpecialVar_Result != 0x7F)
    {
        gSpecialVar_Result = gUnknown_03001124[gSpecialVar_Result];
    }
}

#define tState       data[0]
#define tMonSpecies  data[1]
#define tMonSpriteId data[2]
#define tWindowX     data[3]
#define tWindowY     data[4]
#define tWindowId    data[5]

static void Task_PokemonPicWindow(u8 taskId)
{
    struct Task *task = &gTasks[taskId];

    switch (task->tState)
    {
    case 0:
        task->tState++;
        break;
    case 1:
        break;
    case 2:
        FreeResourcesAndDestroySprite(&gSprites[task->tMonSpriteId], task->tMonSpriteId);
        task->tState++;
        break;
    case 3:
        ClearToTransparentAndRemoveWindow(task->tWindowId);
        DestroyTask(taskId);
        break;
    }
}

bool8 ScriptMenu_ShowPokemonPic(u16 species, u8 x, u8 y)
{
    u8 taskId;
    u8 spriteId;

    if (FindTaskIdByFunc(Task_PokemonPicWindow) != 0xFF)
    {
        return FALSE;
    }
    else
    {
        spriteId = CreateMonSprite_PicBox(species, x * 8 + 40, y * 8 + 40, 0);
        taskId = CreateTask(Task_PokemonPicWindow, 0x50);
        gTasks[taskId].tWindowId = CreateWindowFromRect(x, y, 8, 8);
        gTasks[taskId].tState = 0;
        gTasks[taskId].tMonSpecies = species;
        gTasks[taskId].tMonSpriteId = spriteId;
        gSprites[spriteId].callback = SpriteCallbackDummy;
        gSprites[spriteId].oam.priority = 0;
        SetStandardWindowBorderStyle(gTasks[taskId].tWindowId, 1);
        schedule_bg_copy_tilemap_to_vram(0);
        return TRUE;
    }
}

bool8 (*ScriptMenu_GetPicboxWaitFunc(void))(void)
{
    u8 taskId = FindTaskIdByFunc(Task_PokemonPicWindow);

    if (taskId == 0xFF)
        return NULL;
    gTasks[taskId].tState++;
    return IsPicboxClosed;
}

static bool8 IsPicboxClosed(void)
{
    if (FindTaskIdByFunc(Task_PokemonPicWindow) == 0xFF)
        return TRUE;
    else
        return FALSE;
}

#undef tState
#undef tMonSpecies
#undef tMonSpriteId
#undef tWindowX
#undef tWindowY
#undef tWindowId

u8 CreateWindowFromRect(u8 x, u8 y, u8 width, u8 height)
{
    struct WindowTemplate template = CreateWindowTemplate(0, x + 1, y + 1, width, height, 15, 100);
    u8 windowId = AddWindow(&template);
    PutWindowTilemap(windowId);
    return windowId;
}

void ClearToTransparentAndRemoveWindow(u8 windowId)
{
    ClearStdWindowAndFrameToTransparent(windowId, TRUE);
    RemoveWindow(windowId);
}

static void sub_80E2A94(u8 multichoiceId)
{
    switch (multichoiceId)
    {
    case 77:
        FillWindowPixelBuffer(0, PIXEL_FILL(1));
        AddTextPrinterParameterized2(0, 1, gUnknown_0858BBAC[Menu_GetCursorPos()], 0, NULL, 2, 1, 3);
        break;
    case 76:
        FillWindowPixelBuffer(0, PIXEL_FILL(1));
        AddTextPrinterParameterized2(0, 1, gUnknown_0858BB9C[Menu_GetCursorPos()], 0, NULL, 2, 1, 3);
        break;
    case 78:
        FillWindowPixelBuffer(0, PIXEL_FILL(1));
        AddTextPrinterParameterized2(0, 1, gUnknown_0858BBBC[Menu_GetCursorPos()], 0, NULL, 2, 1, 3);
        break;
    case 79:
        FillWindowPixelBuffer(0, PIXEL_FILL(1));
        AddTextPrinterParameterized2(0, 1, gUnknown_0858BBCC[Menu_GetCursorPos()], 0, NULL, 2, 1, 3);
        break;
    case 75:
        FillWindowPixelBuffer(0, PIXEL_FILL(1));
        AddTextPrinterParameterized2(0, 1, gUnknown_0858BBEC[Menu_GetCursorPos()], 0, NULL, 2, 1, 3);
        break;
    case 74:
        FillWindowPixelBuffer(0, PIXEL_FILL(1));
        AddTextPrinterParameterized2(0, 1, gUnknown_0858BBE0[Menu_GetCursorPos()], 0, NULL, 2, 1, 3);
        break;
    }
}

bool16 sp106_CreateStartMenu(void)
{
    if (FuncIsActiveTask(Task_HandleMultichoiceInput) == TRUE)
    {
        return FALSE;
    }

    gSpecialVar_Result = 0xFF;
    CreateStartMenu();
    return TRUE;
}

static void CreateStartMenu(void)
{
    u8 windowId = CreateWindowFromRect(21, 0, 7, 18);
    SetStandardWindowBorderStyle(windowId, 0);
    AddTextPrinterParameterized(windowId, 1, gText_MenuOptionPokedex, 8, 9, TEXT_SPEED_FF, NULL);
    AddTextPrinterParameterized(windowId, 1, gText_MenuOptionPokemon, 8, 25, TEXT_SPEED_FF, NULL);
    AddTextPrinterParameterized(windowId, 1, gText_MenuOptionBag, 8, 41, TEXT_SPEED_FF, NULL);
    AddTextPrinterParameterized(windowId, 1, gText_MenuOptionPokenav, 8, 57, TEXT_SPEED_FF, NULL);
    AddTextPrinterParameterized(windowId, 1, gSaveBlock2Ptr->playerName, 8, 73, TEXT_SPEED_FF, NULL);
    AddTextPrinterParameterized(windowId, 1, gText_MenuOptionSave, 8, 89, TEXT_SPEED_FF, NULL);
    AddTextPrinterParameterized(windowId, 1, gText_MenuOptionOption, 8, 105, TEXT_SPEED_FF, NULL);
    AddTextPrinterParameterized(windowId, 1, gText_MenuOptionExit, 8, 121, TEXT_SPEED_FF, NULL);
    sub_81983AC(windowId, 1, 0, 9, 16, 8, 0);
    sub_80E2CC4(0, 8, windowId, 86);
    CopyWindowToVram(windowId, 3);
}

#define tWindowId       data[6]

static void sub_80E2CC4(bool8 ignoreBPress, u8 unused, u8 windowId, u8 multichoiceId)
{
    u8 taskId;
    gUnknown_02039F90 = 2;
    taskId = CreateTask(Task_HandleMultichoiceInput, 80);
    gTasks[taskId].tIgnoreBPress = ignoreBPress;
    gTasks[taskId].tDoWrap = 0;
    gTasks[taskId].tWindowId = windowId;
    gTasks[taskId].tMultichoiceId = multichoiceId;
}

#undef tLeft
#undef tTop
#undef tRight
#undef tBottom
#undef tIgnoreBPress
#undef tDoWrap
#undef tWindowId
#undef tMultichoiceId

static int display_text_and_get_width_internal(const u8 *str)
{
    u8 temp[64];
    StringExpandPlaceholders(temp, str);
    return GetStringWidth(1, temp, 0);
}

int display_text_and_get_width(const u8 *str, int prevMaxWidth)
{
    int len = display_text_and_get_width_internal(str);
    if (len < prevMaxWidth)
    {
        len = prevMaxWidth;
    }
    return len;
}

int convert_pixel_width_to_tile_width(int width)
{
    return (((width + 9) / 8) + 1) > 28 ? 28 : (((width + 9) / 8) + 1);
}

int sub_80E2D5C(int a0, int a1)
{
    int ret = a0;

    if (a0 + a1 > 28)
    {
        if (28 - a1 < 0)
        {
            ret = 0;
        }
        else
        {
            ret = 28 - a1;
        }
    }
    else
    {
        ret = a0;
    }

    return ret;
}

// Text displayed as options.
static const u8 sText_pkmn1[] = _("妙蛙种子");
static const u8 sText_pkmn2[] = _("妙蛙草");
static const u8 sText_pkmn3[] = _("妙蛙花");
static const u8 sText_pkmn4[] = _("小火龙");
static const u8 sText_pkmn5[] = _("火恐龙");
static const u8 sText_pkmn6[] = _("喷火龙");
static const u8 sText_pkmn7[] = _("杰尼龟");
static const u8 sText_pkmn8[] = _("卡咪龟");
static const u8 sText_pkmn9[] = _("水箭龟");
static const u8 sText_pkmn10[] = _("绿毛虫");
static const u8 sText_pkmn11[] = _("铁甲蛹");
static const u8 sText_pkmn12[] = _("巴大蝶");
static const u8 sText_pkmn13[] = _("独角虫");
static const u8 sText_pkmn14[] = _("铁壳蛹");
static const u8 sText_pkmn15[] = _("大针蜂");
static const u8 sText_pkmn16[] = _("波波");
static const u8 sText_pkmn17[] = _("比比鸟");
static const u8 sText_pkmn18[] = _("大比鸟");
static const u8 sText_pkmn19[] = _("小拉达");
static const u8 sText_pkmn20[] = _("拉达");
static const u8 sText_pkmn21[] = _("烈雀");
static const u8 sText_pkmn22[] = _("大嘴雀");
static const u8 sText_pkmn23[] = _("阿柏蛇");
static const u8 sText_pkmn24[] = _("阿柏怪");
static const u8 sText_pkmn25[] = _("皮卡丘");
static const u8 sText_pkmn26[] = _("雷丘");
static const u8 sText_pkmn27[] = _("穿山鼠");
static const u8 sText_pkmn28[] = _("穿山王");
static const u8 sText_pkmn29[] = _("尼多兰");
static const u8 sText_pkmn30[] = _("尼多娜");
static const u8 sText_pkmn31[] = _("尼多后");
static const u8 sText_pkmn32[] = _("尼多朗");
static const u8 sText_pkmn33[] = _("尼多力诺");
static const u8 sText_pkmn34[] = _("尼多王");
static const u8 sText_pkmn35[] = _("皮皮");
static const u8 sText_pkmn36[] = _("皮可西");
static const u8 sText_pkmn37[] = _("六尾");
static const u8 sText_pkmn38[] = _("九尾");
static const u8 sText_pkmn39[] = _("胖丁");
static const u8 sText_pkmn40[] = _("胖可丁");
static const u8 sText_pkmn41[] = _("超音蝠");
static const u8 sText_pkmn42[] = _("大嘴蝠");
static const u8 sText_pkmn43[] = _("走路草");
static const u8 sText_pkmn44[] = _("臭臭花");
static const u8 sText_pkmn45[] = _("霸王花");
static const u8 sText_pkmn46[] = _("派拉斯");
static const u8 sText_pkmn47[] = _("派拉斯特");
static const u8 sText_pkmn48[] = _("毛球");
static const u8 sText_pkmn49[] = _("摩鲁蛾");
static const u8 sText_pkmn50[] = _("地鼠");
static const u8 sText_pkmn51[] = _("三地鼠");
static const u8 sText_pkmn52[] = _("喵喵");
static const u8 sText_pkmn53[] = _("猫老大");
static const u8 sText_pkmn54[] = _("可达鸭");
static const u8 sText_pkmn55[] = _("哥达鸭");
static const u8 sText_pkmn56[] = _("猴怪");
static const u8 sText_pkmn57[] = _("火暴猴");
static const u8 sText_pkmn58[] = _("卡蒂狗");
static const u8 sText_pkmn59[] = _("风速狗");
static const u8 sText_pkmn60[] = _("蚊香蝌蚪");
static const u8 sText_pkmn61[] = _("蚊香君");
static const u8 sText_pkmn62[] = _("蚊香泳士");
static const u8 sText_pkmn63[] = _("凯西");
static const u8 sText_pkmn64[] = _("勇基拉");
static const u8 sText_pkmn65[] = _("胡地");
static const u8 sText_pkmn66[] = _("腕力");
static const u8 sText_pkmn67[] = _("豪力");
static const u8 sText_pkmn68[] = _("怪力");
static const u8 sText_pkmn69[] = _("喇叭芽");
static const u8 sText_pkmn70[] = _("口呆花");
static const u8 sText_pkmn71[] = _("大食花");
static const u8 sText_pkmn72[] = _("玛瑙水母");
static const u8 sText_pkmn73[] = _("毒刺水母");
static const u8 sText_pkmn74[] = _("小拳石");
static const u8 sText_pkmn75[] = _("隆隆石");
static const u8 sText_pkmn76[] = _("隆隆岩");
static const u8 sText_pkmn77[] = _("小火马");
static const u8 sText_pkmn78[] = _("烈焰马");
static const u8 sText_pkmn79[] = _("呆呆兽");
static const u8 sText_pkmn80[] = _("呆壳兽");
static const u8 sText_pkmn81[] = _("小磁怪");
static const u8 sText_pkmn82[] = _("三合一磁怪");
static const u8 sText_pkmn83[] = _("大葱鸭");
static const u8 sText_pkmn84[] = _("嘟嘟");
static const u8 sText_pkmn85[] = _("嘟嘟利");
static const u8 sText_pkmn86[] = _("小海狮");
static const u8 sText_pkmn87[] = _("白海狮");
static const u8 sText_pkmn88[] = _("臭泥");
static const u8 sText_pkmn89[] = _("臭臭泥");
static const u8 sText_pkmn90[] = _("大舌贝");
static const u8 sText_pkmn91[] = _("刺甲贝");
static const u8 sText_pkmn92[] = _("鬼斯");
static const u8 sText_pkmn93[] = _("鬼斯通");
static const u8 sText_pkmn94[] = _("耿鬼");
static const u8 sText_pkmn95[] = _("大岩蛇");
static const u8 sText_pkmn96[] = _("催眠貘");
static const u8 sText_pkmn97[] = _("引梦貘人");
static const u8 sText_pkmn98[] = _("大钳蟹");
static const u8 sText_pkmn99[] = _("巨钳蟹");
static const u8 sText_pkmn100[] = _("霹雳电球");
static const u8 sText_pkmn101[] = _("顽皮雷弹");
static const u8 sText_pkmn102[] = _("蛋蛋");
static const u8 sText_pkmn103[] = _("椰蛋树");
static const u8 sText_pkmn104[] = _("卡拉卡拉");
static const u8 sText_pkmn105[] = _("嘎啦嘎啦");
static const u8 sText_pkmn106[] = _("飞腿郎");
static const u8 sText_pkmn107[] = _("快拳郎");
static const u8 sText_pkmn108[] = _("大舌头");
static const u8 sText_pkmn109[] = _("瓦斯弹");
static const u8 sText_pkmn110[] = _("双弹瓦斯");
static const u8 sText_pkmn111[] = _("独角犀牛");
static const u8 sText_pkmn112[] = _("钻角犀兽");
static const u8 sText_pkmn113[] = _("吉利蛋");
static const u8 sText_pkmn114[] = _("蔓藤怪");
static const u8 sText_pkmn115[] = _("袋兽");
static const u8 sText_pkmn116[] = _("墨海马");
static const u8 sText_pkmn117[] = _("海刺龙");
static const u8 sText_pkmn118[] = _("角金鱼");
static const u8 sText_pkmn119[] = _("金鱼王");
static const u8 sText_pkmn120[] = _("海星星");
static const u8 sText_pkmn121[] = _("宝石海星");
static const u8 sText_pkmn122[] = _("魔墙人偶");
static const u8 sText_pkmn123[] = _("飞天螳螂");
static const u8 sText_pkmn124[] = _("迷唇姐");
static const u8 sText_pkmn125[] = _("电击兽");
static const u8 sText_pkmn126[] = _("鸭嘴火兽");
static const u8 sText_pkmn127[] = _("凯罗斯");
static const u8 sText_pkmn128[] = _("肯泰罗");
static const u8 sText_pkmn129[] = _("鲤鱼王");
static const u8 sText_pkmn130[] = _("暴鲤龙");
static const u8 sText_pkmn131[] = _("拉普拉斯");
static const u8 sText_pkmn132[] = _("百变怪");
static const u8 sText_pkmn133[] = _("伊布");
static const u8 sText_pkmn134[] = _("水伊布");
static const u8 sText_pkmn135[] = _("雷伊布");
static const u8 sText_pkmn136[] = _("火伊布");
static const u8 sText_pkmn137[] = _("多边兽");
static const u8 sText_pkmn138[] = _("菊石兽");
static const u8 sText_pkmn139[] = _("多刺菊石兽");
static const u8 sText_pkmn140[] = _("化石盔");
static const u8 sText_pkmn141[] = _("镰刀盔");
static const u8 sText_pkmn142[] = _("化石翼龙");
static const u8 sText_pkmn143[] = _("卡比兽");
static const u8 sText_pkmn144[] = _("急冻鸟");
static const u8 sText_pkmn145[] = _("闪电鸟");
static const u8 sText_pkmn146[] = _("火焰鸟");
static const u8 sText_pkmn147[] = _("迷你龙");
static const u8 sText_pkmn148[] = _("哈克龙");
static const u8 sText_pkmn149[] = _("快龙");
static const u8 sText_pkmn150[] = _("超梦");
static const u8 sText_pkmn151[] = _("梦幻");
static const u8 sText_pkmn152[] = _("菊草叶");
static const u8 sText_pkmn153[] = _("月桂叶");
static const u8 sText_pkmn154[] = _("大竺葵");
static const u8 sText_pkmn155[] = _("火球鼠");
static const u8 sText_pkmn156[] = _("火岩鼠");
static const u8 sText_pkmn157[] = _("火暴兽");
static const u8 sText_pkmn158[] = _("小锯鳄");
static const u8 sText_pkmn159[] = _("蓝鳄");
static const u8 sText_pkmn160[] = _("大力鳄");
static const u8 sText_pkmn161[] = _("尾立");
static const u8 sText_pkmn162[] = _("大尾立");
static const u8 sText_pkmn163[] = _("咕咕");
static const u8 sText_pkmn164[] = _("猫头夜鹰");
static const u8 sText_pkmn165[] = _("芭瓢虫");
static const u8 sText_pkmn166[] = _("安瓢虫");
static const u8 sText_pkmn167[] = _("圆丝蛛");
static const u8 sText_pkmn168[] = _("阿利多斯");
static const u8 sText_pkmn169[] = _("叉字蝠");
static const u8 sText_pkmn170[] = _("灯笼鱼");
static const u8 sText_pkmn171[] = _("电灯怪");
static const u8 sText_pkmn172[] = _("皮丘");
static const u8 sText_pkmn173[] = _("皮宝宝");
static const u8 sText_pkmn174[] = _("宝宝丁");
static const u8 sText_pkmn175[] = _("波克比");
static const u8 sText_pkmn176[] = _("波克基古");
static const u8 sText_pkmn177[] = _("天然雀");
static const u8 sText_pkmn178[] = _("天然鸟");
static const u8 sText_pkmn179[] = _("咩利羊");
static const u8 sText_pkmn180[] = _("茸茸羊");
static const u8 sText_pkmn181[] = _("电龙");
static const u8 sText_pkmn182[] = _("美丽花");
static const u8 sText_pkmn183[] = _("玛力露");
static const u8 sText_pkmn184[] = _("玛力露丽");
static const u8 sText_pkmn185[] = _("树才怪");
static const u8 sText_pkmn186[] = _("蚊香蛙皇");
static const u8 sText_pkmn187[] = _("毽子草");
static const u8 sText_pkmn188[] = _("毽子花");
static const u8 sText_pkmn189[] = _("毽子棉");
static const u8 sText_pkmn190[] = _("长尾怪手");
static const u8 sText_pkmn191[] = _("向日种子");
static const u8 sText_pkmn192[] = _("向日花怪");
static const u8 sText_pkmn193[] = _("蜻蜻蜓");
static const u8 sText_pkmn194[] = _("乌波");
static const u8 sText_pkmn195[] = _("沼王");
static const u8 sText_pkmn196[] = _("太阳伊布");
static const u8 sText_pkmn197[] = _("月亮伊布");
static const u8 sText_pkmn198[] = _("黑暗鸦");
static const u8 sText_pkmn199[] = _("呆呆王");
static const u8 sText_pkmn200[] = _("梦妖");
static const u8 sText_pkmn201[] = _("未知图腾");
static const u8 sText_pkmn202[] = _("果然翁");
static const u8 sText_pkmn203[] = _("麒麟奇");
static const u8 sText_pkmn204[] = _("榛果球");
static const u8 sText_pkmn205[] = _("佛烈托斯");
static const u8 sText_pkmn206[] = _("土龙弟弟");
static const u8 sText_pkmn207[] = _("天蝎");
static const u8 sText_pkmn208[] = _("大钢蛇");
static const u8 sText_pkmn209[] = _("布鲁");
static const u8 sText_pkmn210[] = _("布鲁皇");
static const u8 sText_pkmn211[] = _("千针鱼");
static const u8 sText_pkmn212[] = _("巨钳螳螂");
static const u8 sText_pkmn213[] = _("壶壶");
static const u8 sText_pkmn214[] = _("赫拉克罗斯");
static const u8 sText_pkmn215[] = _("狃拉");
static const u8 sText_pkmn216[] = _("熊宝宝");
static const u8 sText_pkmn217[] = _("圈圈熊");
static const u8 sText_pkmn218[] = _("熔岩虫");
static const u8 sText_pkmn219[] = _("熔岩蜗牛");
static const u8 sText_pkmn220[] = _("小山猪");
static const u8 sText_pkmn221[] = _("长毛猪");
static const u8 sText_pkmn222[] = _("太阳珊瑚");
static const u8 sText_pkmn223[] = _("铁炮鱼");
static const u8 sText_pkmn224[] = _("章鱼桶");
static const u8 sText_pkmn225[] = _("信使鸟");
static const u8 sText_pkmn226[] = _("巨翅飞鱼");
static const u8 sText_pkmn227[] = _("盔甲鸟");
static const u8 sText_pkmn228[] = _("戴鲁比");
static const u8 sText_pkmn229[] = _("黑鲁加");
static const u8 sText_pkmn230[] = _("刺龙王");
static const u8 sText_pkmn231[] = _("小小象");
static const u8 sText_pkmn232[] = _("顿甲");
static const u8 sText_pkmn233[] = _("多边兽2");
static const u8 sText_pkmn234[] = _("惊角鹿");
static const u8 sText_pkmn235[] = _("图图犬");
static const u8 sText_pkmn236[] = _("无畏小子");
static const u8 sText_pkmn237[] = _("战舞郎");
static const u8 sText_pkmn238[] = _("迷唇娃");
static const u8 sText_pkmn239[] = _("电击怪");
static const u8 sText_pkmn240[] = _("鸭嘴宝宝");
static const u8 sText_pkmn241[] = _("大奶罐");
static const u8 sText_pkmn242[] = _("幸福蛋");
static const u8 sText_pkmn243[] = _("雷公");
static const u8 sText_pkmn244[] = _("炎帝");
static const u8 sText_pkmn245[] = _("水君");
static const u8 sText_pkmn246[] = _("幼基拉斯");
static const u8 sText_pkmn247[] = _("沙基拉斯");
static const u8 sText_pkmn248[] = _("班基拉斯");
static const u8 sText_pkmn249[] = _("洛奇亚");
static const u8 sText_pkmn250[] = _("凤王");
static const u8 sText_pkmn251[] = _("时拉比");
static const u8 sText_pkmn252[] = _("木守宫");
static const u8 sText_pkmn253[] = _("森林蜥蜴");
static const u8 sText_pkmn254[] = _("蜥蜴王");
static const u8 sText_pkmn255[] = _("火稚鸡");
static const u8 sText_pkmn256[] = _("力壮鸡");
static const u8 sText_pkmn257[] = _("火焰鸡");
static const u8 sText_pkmn258[] = _("水跃鱼");
static const u8 sText_pkmn259[] = _("沼跃鱼");
static const u8 sText_pkmn260[] = _("巨沼怪");
static const u8 sText_pkmn261[] = _("土狼犬");
static const u8 sText_pkmn262[] = _("大狼犬");
static const u8 sText_pkmn263[] = _("蛇纹熊");
static const u8 sText_pkmn264[] = _("直冲熊");
static const u8 sText_pkmn265[] = _("刺尾虫");
static const u8 sText_pkmn266[] = _("甲壳茧");
static const u8 sText_pkmn267[] = _("狩猎凤蝶");
static const u8 sText_pkmn268[] = _("盾甲茧");
static const u8 sText_pkmn269[] = _("毒粉蛾");
static const u8 sText_pkmn270[] = _("莲叶童子");
static const u8 sText_pkmn271[] = _("莲帽小童");
static const u8 sText_pkmn272[] = _("乐天河童");
static const u8 sText_pkmn273[] = _("橡实果");
static const u8 sText_pkmn274[] = _("长鼻叶");
static const u8 sText_pkmn275[] = _("狡猾天狗");
static const u8 sText_pkmn276[] = _("傲骨燕");
static const u8 sText_pkmn277[] = _("大王燕");
static const u8 sText_pkmn278[] = _("长翅鸥");
static const u8 sText_pkmn279[] = _("大嘴鸥");
static const u8 sText_pkmn280[] = _("拉鲁拉丝");
static const u8 sText_pkmn281[] = _("奇鲁莉安");
static const u8 sText_pkmn282[] = _("沙奈朵");
static const u8 sText_pkmn283[] = _("溜溜糖球");
static const u8 sText_pkmn284[] = _("雨翅蛾");
static const u8 sText_pkmn285[] = _("蘑蘑菇");
static const u8 sText_pkmn286[] = _("斗笠菇");
static const u8 sText_pkmn287[] = _("懒人獭");
static const u8 sText_pkmn288[] = _("过动猿");
static const u8 sText_pkmn289[] = _("请假王");
static const u8 sText_pkmn290[] = _("土居忍士");
static const u8 sText_pkmn291[] = _("铁面忍者");
static const u8 sText_pkmn292[] = _("脱壳忍者");
static const u8 sText_pkmn293[] = _("咕妞妞");
static const u8 sText_pkmn294[] = _("吼爆弹");
static const u8 sText_pkmn295[] = _("爆音怪");
static const u8 sText_pkmn296[] = _("幕下力士");
static const u8 sText_pkmn297[] = _("铁掌力士");
static const u8 sText_pkmn298[] = _("露力丽");
static const u8 sText_pkmn299[] = _("朝北鼻");
static const u8 sText_pkmn300[] = _("向尾喵");
static const u8 sText_pkmn301[] = _("优雅猫");
static const u8 sText_pkmn302[] = _("勾魂眼");
static const u8 sText_pkmn303[] = _("大嘴娃");
static const u8 sText_pkmn304[] = _("可可多拉");
static const u8 sText_pkmn305[] = _("可多拉");
static const u8 sText_pkmn306[] = _("波士可多拉");
static const u8 sText_pkmn307[] = _("玛沙那");
static const u8 sText_pkmn308[] = _("恰雷姆");
static const u8 sText_pkmn309[] = _("落雷兽");
static const u8 sText_pkmn310[] = _("雷电兽");
static const u8 sText_pkmn311[] = _("正电拍拍");
static const u8 sText_pkmn312[] = _("负电拍拍");
static const u8 sText_pkmn313[] = _("电萤虫");
static const u8 sText_pkmn314[] = _("甜甜萤");
static const u8 sText_pkmn315[] = _("毒蔷薇");
static const u8 sText_pkmn316[] = _("溶食兽");
static const u8 sText_pkmn317[] = _("吞食兽");
static const u8 sText_pkmn318[] = _("利牙鱼");
static const u8 sText_pkmn319[] = _("巨牙鲨");
static const u8 sText_pkmn320[] = _("吼吼鲸");
static const u8 sText_pkmn321[] = _("吼鲸王");
static const u8 sText_pkmn322[] = _("呆火驼");
static const u8 sText_pkmn323[] = _("喷火驼");
static const u8 sText_pkmn324[] = _("煤炭龟");
static const u8 sText_pkmn325[] = _("跳跳猪");
static const u8 sText_pkmn326[] = _("噗噗猪");
static const u8 sText_pkmn327[] = _("晃晃斑");
static const u8 sText_pkmn328[] = _("大颚蚁");
static const u8 sText_pkmn329[] = _("超音波幼虫");
static const u8 sText_pkmn330[] = _("沙漠蜻蜓");
static const u8 sText_pkmn331[] = _("刺球仙人掌");
static const u8 sText_pkmn332[] = _("梦歌仙人掌");
static const u8 sText_pkmn333[] = _("青绵鸟");
static const u8 sText_pkmn334[] = _("七夕青鸟");
static const u8 sText_pkmn335[] = _("猫鼬斩");
static const u8 sText_pkmn336[] = _("饭匙蛇");
static const u8 sText_pkmn337[] = _("月石");
static const u8 sText_pkmn338[] = _("太阳岩");
static const u8 sText_pkmn339[] = _("泥泥鳅");
static const u8 sText_pkmn340[] = _("鲶鱼王");
static const u8 sText_pkmn341[] = _("龙虾小兵");
static const u8 sText_pkmn342[] = _("铁螯龙虾");
static const u8 sText_pkmn343[] = _("天秤偶");
static const u8 sText_pkmn344[] = _("念力土偶");
static const u8 sText_pkmn345[] = _("触手百合");
static const u8 sText_pkmn346[] = _("摇篮百合");
static const u8 sText_pkmn347[] = _("太古羽虫");
static const u8 sText_pkmn348[] = _("太古盔甲");
static const u8 sText_pkmn349[] = _("丑丑鱼");
static const u8 sText_pkmn350[] = _("美纳斯");
static const u8 sText_pkmn351[] = _("飘浮泡泡");
static const u8 sText_pkmn352[] = _("变隐龙");
static const u8 sText_pkmn353[] = _("怨影娃娃");
static const u8 sText_pkmn354[] = _("诅咒娃娃");
static const u8 sText_pkmn355[] = _("夜巡灵");
static const u8 sText_pkmn356[] = _("彷徨夜灵");
static const u8 sText_pkmn357[] = _("热带龙");
static const u8 sText_pkmn358[] = _("风铃铃");
static const u8 sText_pkmn359[] = _("阿勃梭鲁");
static const u8 sText_pkmn360[] = _("小果然");
static const u8 sText_pkmn361[] = _("雪童子");
static const u8 sText_pkmn362[] = _("冰鬼护");
static const u8 sText_pkmn363[] = _("海豹球");
static const u8 sText_pkmn364[] = _("海魔狮");
static const u8 sText_pkmn365[] = _("帝牙海狮");
static const u8 sText_pkmn366[] = _("珍珠贝");
static const u8 sText_pkmn367[] = _("猎斑鱼");
static const u8 sText_pkmn368[] = _("樱花鱼");
static const u8 sText_pkmn369[] = _("古空棘鱼");
static const u8 sText_pkmn370[] = _("爱心鱼");
static const u8 sText_pkmn371[] = _("宝贝龙");
static const u8 sText_pkmn372[] = _("甲壳龙");
static const u8 sText_pkmn373[] = _("暴飞龙");
static const u8 sText_pkmn374[] = _("铁哑铃");
static const u8 sText_pkmn375[] = _("金属怪");
static const u8 sText_pkmn376[] = _("巨金怪");
static const u8 sText_pkmn377[] = _("雷吉洛克");
static const u8 sText_pkmn378[] = _("雷吉艾斯");
static const u8 sText_pkmn379[] = _("雷吉斯奇鲁");
static const u8 sText_pkmn380[] = _("拉帝亚斯");
static const u8 sText_pkmn381[] = _("拉帝欧斯");
static const u8 sText_pkmn382[] = _("盖欧卡");
static const u8 sText_pkmn383[] = _("固拉多");
static const u8 sText_pkmn384[] = _("烈空坐");
static const u8 sText_pkmn385[] = _("基拉祈");
static const u8 sText_pkmn386[] = _("代欧奇希斯");
static const u8 sText_pkmn387[] = _("草苗龟");
static const u8 sText_pkmn388[] = _("树林龟");
static const u8 sText_pkmn389[] = _("土台龟");
static const u8 sText_pkmn390[] = _("小火焰猴");
static const u8 sText_pkmn391[] = _("猛火猴");
static const u8 sText_pkmn392[] = _("烈焰猴");
static const u8 sText_pkmn393[] = _("波加曼");
static const u8 sText_pkmn394[] = _("波皇子");
static const u8 sText_pkmn395[] = _("帝王拿波");
static const u8 sText_pkmn396[] = _("姆克儿");
static const u8 sText_pkmn397[] = _("姆克鸟");
static const u8 sText_pkmn398[] = _("姆克鹰");
static const u8 sText_pkmn399[] = _("大牙狸");
static const u8 sText_pkmn400[] = _("大尾狸");
static const u8 sText_pkmn401[] = _("圆法师");
static const u8 sText_pkmn402[] = _("音箱蟀");
static const u8 sText_pkmn403[] = _("小猫怪");
static const u8 sText_pkmn404[] = _("勒克猫");
static const u8 sText_pkmn405[] = _("伦琴猫");
static const u8 sText_pkmn406[] = _("含羞苞");
static const u8 sText_pkmn407[] = _("罗丝雷朵");
static const u8 sText_pkmn408[] = _("头盖龙");
static const u8 sText_pkmn409[] = _("战槌龙");
static const u8 sText_pkmn410[] = _("盾甲龙");
static const u8 sText_pkmn411[] = _("护城龙");
static const u8 sText_pkmn412[] = _("结草儿");
static const u8 sText_pkmn413[] = _("结草贵妇");
static const u8 sText_pkmn414[] = _("绅士蛾");
static const u8 sText_pkmn415[] = _("三蜜蜂");
static const u8 sText_pkmn416[] = _("蜂女王");
static const u8 sText_pkmn417[] = _("帕奇利兹");
static const u8 sText_pkmn418[] = _("泳圈鼬");
static const u8 sText_pkmn419[] = _("浮潜鼬");
static const u8 sText_pkmn420[] = _("樱花宝");
static const u8 sText_pkmn421[] = _("樱花儿");
static const u8 sText_pkmn422[] = _("无壳海兔");
static const u8 sText_pkmn423[] = _("海兔兽");
static const u8 sText_pkmn424[] = _("双尾怪手");
static const u8 sText_pkmn425[] = _("飘飘球");
static const u8 sText_pkmn426[] = _("随风球");
static const u8 sText_pkmn427[] = _("卷卷耳");
static const u8 sText_pkmn428[] = _("长耳兔");
static const u8 sText_pkmn429[] = _("梦妖魔");
static const u8 sText_pkmn430[] = _("乌鸦头头");
static const u8 sText_pkmn431[] = _("魅力喵");
static const u8 sText_pkmn432[] = _("东施喵");
static const u8 sText_pkmn433[] = _("铃铛响");
static const u8 sText_pkmn434[] = _("臭鼬噗");
static const u8 sText_pkmn435[] = _("坦克臭鼬");
static const u8 sText_pkmn436[] = _("铜镜怪");
static const u8 sText_pkmn437[] = _("青铜钟");
static const u8 sText_pkmn438[] = _("盆才怪");
static const u8 sText_pkmn439[] = _("魔尼尼");
static const u8 sText_pkmn440[] = _("小福蛋");
static const u8 sText_pkmn441[] = _("聒噪鸟");
static const u8 sText_pkmn442[] = _("花岩怪");
static const u8 sText_pkmn443[] = _("圆陆鲨");
static const u8 sText_pkmn444[] = _("尖牙陆鲨");
static const u8 sText_pkmn445[] = _("烈咬陆鲨");
static const u8 sText_pkmn446[] = _("小卡比兽");
static const u8 sText_pkmn447[] = _("利欧路");
static const u8 sText_pkmn448[] = _("路卡利欧");
static const u8 sText_pkmn449[] = _("沙河马");
static const u8 sText_pkmn450[] = _("河马兽");
static const u8 sText_pkmn451[] = _("钳尾蝎");
static const u8 sText_pkmn452[] = _("龙王蝎");
static const u8 sText_pkmn453[] = _("不良蛙");
static const u8 sText_pkmn454[] = _("毒骷蛙");
static const u8 sText_pkmn455[] = _("尖牙笼");
static const u8 sText_pkmn456[] = _("荧光鱼");
static const u8 sText_pkmn457[] = _("霓虹鱼");
static const u8 sText_pkmn458[] = _("小球飞鱼");
static const u8 sText_pkmn459[] = _("雪笠怪");
static const u8 sText_pkmn460[] = _("暴雪王");
static const u8 sText_pkmn461[] = _("玛狃拉");
static const u8 sText_pkmn462[] = _("自爆磁怪");
static const u8 sText_pkmn463[] = _("大舌舔");
static const u8 sText_pkmn464[] = _("超甲狂犀");
static const u8 sText_pkmn465[] = _("巨蔓藤");
static const u8 sText_pkmn466[] = _("电击魔兽");
static const u8 sText_pkmn467[] = _("鸭嘴炎兽");
static const u8 sText_pkmn468[] = _("波克基斯");
static const u8 sText_pkmn469[] = _("远古巨蜓");
static const u8 sText_pkmn470[] = _("叶伊布");
static const u8 sText_pkmn471[] = _("冰伊布");
static const u8 sText_pkmn472[] = _("天蝎王");
static const u8 sText_pkmn473[] = _("象牙猪");
static const u8 sText_pkmn474[] = _("多边兽Ｚ");
static const u8 sText_pkmn475[] = _("艾路雷朵");
static const u8 sText_pkmn476[] = _("大朝北鼻");
static const u8 sText_pkmn477[] = _("黑夜魔灵");
static const u8 sText_pkmn478[] = _("雪妖女");
static const u8 sText_pkmn479[] = _("洛托姆");
static const u8 sText_pkmn480[] = _("由克希");
static const u8 sText_pkmn481[] = _("艾姆利多");
static const u8 sText_pkmn482[] = _("亚克诺姆");
static const u8 sText_pkmn483[] = _("帝牙卢卡");
static const u8 sText_pkmn484[] = _("帕路奇亚");
static const u8 sText_pkmn485[] = _("席多蓝恩");
static const u8 sText_pkmn486[] = _("雷吉奇卡斯");
static const u8 sText_pkmn487[] = _("骑拉帝纳");
static const u8 sText_pkmn488[] = _("克雷色利亚");
static const u8 sText_pkmn489[] = _("霏欧纳");
static const u8 sText_pkmn490[] = _("玛纳霏");
static const u8 sText_pkmn491[] = _("达克莱伊");
static const u8 sText_pkmn492[] = _("谢米");
static const u8 sText_pkmn493[] = _("阿尔宙斯");
static const u8 sText_pkmn494[] = _("比克提尼");
static const u8 sText_pkmn495[] = _("藤藤蛇");
static const u8 sText_pkmn496[] = _("青藤蛇");
static const u8 sText_pkmn497[] = _("君主蛇");
static const u8 sText_pkmn498[] = _("暖暖猪");
static const u8 sText_pkmn499[] = _("炒炒猪");
static const u8 sText_pkmn500[] = _("炎武王");
static const u8 sText_pkmn501[] = _("水水獭");
static const u8 sText_pkmn502[] = _("双刃丸");
static const u8 sText_pkmn503[] = _("大剑鬼");
static const u8 sText_pkmn504[] = _("探探鼠");
static const u8 sText_pkmn505[] = _("步哨鼠");
static const u8 sText_pkmn506[] = _("小约克");
static const u8 sText_pkmn507[] = _("哈约克");
static const u8 sText_pkmn508[] = _("长毛狗");
static const u8 sText_pkmn509[] = _("扒手猫");
static const u8 sText_pkmn510[] = _("酷豹");
static const u8 sText_pkmn511[] = _("花椰猴");
static const u8 sText_pkmn512[] = _("花椰猿");
static const u8 sText_pkmn513[] = _("爆香猴");
static const u8 sText_pkmn514[] = _("爆香猿");
static const u8 sText_pkmn515[] = _("冷水猴");
static const u8 sText_pkmn516[] = _("冷水猿");
static const u8 sText_pkmn517[] = _("食梦梦");
static const u8 sText_pkmn518[] = _("梦梦蚀");
static const u8 sText_pkmn519[] = _("豆豆鸽");
static const u8 sText_pkmn520[] = _("咕咕鸽");
static const u8 sText_pkmn521[] = _("高傲雉鸡");
static const u8 sText_pkmn522[] = _("斑斑马");
static const u8 sText_pkmn523[] = _("雷电斑马");
static const u8 sText_pkmn524[] = _("石丸子");
static const u8 sText_pkmn525[] = _("地幔岩");
static const u8 sText_pkmn526[] = _("庞岩怪");
static const u8 sText_pkmn527[] = _("滚滚蝙蝠");
static const u8 sText_pkmn528[] = _("心蝙蝠");
static const u8 sText_pkmn529[] = _("螺钉地鼠");
static const u8 sText_pkmn530[] = _("龙头地鼠");
static const u8 sText_pkmn531[] = _("差不多娃娃");
static const u8 sText_pkmn532[] = _("搬运小匠");
static const u8 sText_pkmn533[] = _("铁骨土人");
static const u8 sText_pkmn534[] = _("修建老匠");
static const u8 sText_pkmn535[] = _("圆蝌蚪");
static const u8 sText_pkmn536[] = _("蓝蟾蜍");
static const u8 sText_pkmn537[] = _("蟾蜍王");
static const u8 sText_pkmn538[] = _("投摔鬼");
static const u8 sText_pkmn539[] = _("打击鬼");
static const u8 sText_pkmn540[] = _("虫宝包");
static const u8 sText_pkmn541[] = _("宝包茧");
static const u8 sText_pkmn542[] = _("保姆虫");
static const u8 sText_pkmn543[] = _("百足蜈蚣");
static const u8 sText_pkmn544[] = _("车轮球");
static const u8 sText_pkmn545[] = _("蜈蚣王");
static const u8 sText_pkmn546[] = _("木棉球");
static const u8 sText_pkmn547[] = _("风妖精");
static const u8 sText_pkmn548[] = _("百合根娃娃");
static const u8 sText_pkmn549[] = _("裙儿小姐");
static const u8 sText_pkmn550[] = _("野蛮鲈鱼");
static const u8 sText_pkmn551[] = _("黑眼鳄");
static const u8 sText_pkmn552[] = _("混混鳄");
static const u8 sText_pkmn553[] = _("流氓鳄");
static const u8 sText_pkmn554[] = _("火红不倒翁");
static const u8 sText_pkmn555[] = _("达摩狒狒");
static const u8 sText_pkmn556[] = _("沙铃仙人掌");
static const u8 sText_pkmn557[] = _("石居蟹");
static const u8 sText_pkmn558[] = _("岩殿居蟹");
static const u8 sText_pkmn559[] = _("滑滑小子");
static const u8 sText_pkmn560[] = _("头巾混混");
static const u8 sText_pkmn561[] = _("象征鸟");
static const u8 sText_pkmn562[] = _("哭哭面具");
static const u8 sText_pkmn563[] = _("死神棺");
static const u8 sText_pkmn564[] = _("原盖海龟");
static const u8 sText_pkmn565[] = _("肋骨海龟");
static const u8 sText_pkmn566[] = _("始祖小鸟");
static const u8 sText_pkmn567[] = _("始祖大鸟");
static const u8 sText_pkmn568[] = _("破破袋");
static const u8 sText_pkmn569[] = _("灰尘山");
static const u8 sText_pkmn570[] = _("索罗亚");
static const u8 sText_pkmn571[] = _("索罗亚克");
static const u8 sText_pkmn572[] = _("泡沫栗鼠");
static const u8 sText_pkmn573[] = _("奇诺栗鼠");
static const u8 sText_pkmn574[] = _("哥德宝宝");
static const u8 sText_pkmn575[] = _("哥德小童");
static const u8 sText_pkmn576[] = _("哥德小姐");
static const u8 sText_pkmn577[] = _("单卵细胞球");
static const u8 sText_pkmn578[] = _("双卵细胞球");
static const u8 sText_pkmn579[] = _("人造细胞卵");
static const u8 sText_pkmn580[] = _("鸭宝宝");
static const u8 sText_pkmn581[] = _("舞天鹅");
static const u8 sText_pkmn582[] = _("迷你冰");
static const u8 sText_pkmn583[] = _("多多冰");
static const u8 sText_pkmn584[] = _("双倍多多冰");
static const u8 sText_pkmn585[] = _("四季鹿");
static const u8 sText_pkmn586[] = _("萌芽鹿");
static const u8 sText_pkmn587[] = _("电飞鼠");
static const u8 sText_pkmn588[] = _("盖盖虫");
static const u8 sText_pkmn589[] = _("骑士蜗牛");
static const u8 sText_pkmn590[] = _("哎呀球菇");
static const u8 sText_pkmn591[] = _("败露球菇");
static const u8 sText_pkmn592[] = _("轻飘飘");
static const u8 sText_pkmn593[] = _("胖嘟嘟");
static const u8 sText_pkmn594[] = _("保姆曼波");
static const u8 sText_pkmn595[] = _("电电虫");
static const u8 sText_pkmn596[] = _("电蜘蛛");
static const u8 sText_pkmn597[] = _("种子铁球");
static const u8 sText_pkmn598[] = _("坚果哑铃");
static const u8 sText_pkmn599[] = _("齿轮儿");
static const u8 sText_pkmn600[] = _("齿轮组");
static const u8 sText_pkmn601[] = _("齿轮怪");
static const u8 sText_pkmn602[] = _("麻麻小鱼");
static const u8 sText_pkmn603[] = _("麻麻鳗");
static const u8 sText_pkmn604[] = _("麻麻鳗鱼王");
static const u8 sText_pkmn605[] = _("小灰怪");
static const u8 sText_pkmn606[] = _("大宇怪");
static const u8 sText_pkmn607[] = _("烛光灵");
static const u8 sText_pkmn608[] = _("灯火幽灵");
static const u8 sText_pkmn609[] = _("水晶灯火灵");
static const u8 sText_pkmn610[] = _("牙牙");
static const u8 sText_pkmn611[] = _("斧牙龙");
static const u8 sText_pkmn612[] = _("双斧战龙");
static const u8 sText_pkmn613[] = _("喷嚏熊");
static const u8 sText_pkmn614[] = _("冻原熊");
static const u8 sText_pkmn615[] = _("几何雪花");
static const u8 sText_pkmn616[] = _("小嘴蜗");
static const u8 sText_pkmn617[] = _("敏捷虫");
static const u8 sText_pkmn618[] = _("泥巴鱼");
static const u8 sText_pkmn619[] = _("功夫鼬");
static const u8 sText_pkmn620[] = _("师父鼬");
static const u8 sText_pkmn621[] = _("赤面龙");
static const u8 sText_pkmn622[] = _("泥偶小人");
static const u8 sText_pkmn623[] = _("泥偶巨人");
static const u8 sText_pkmn624[] = _("驹刀小兵");
static const u8 sText_pkmn625[] = _("劈斩司令");
static const u8 sText_pkmn626[] = _("爆炸头水牛");
static const u8 sText_pkmn627[] = _("毛头小鹰");
static const u8 sText_pkmn628[] = _("勇士雄鹰");
static const u8 sText_pkmn629[] = _("秃鹰丫头");
static const u8 sText_pkmn630[] = _("秃鹰娜");
static const u8 sText_pkmn631[] = _("熔蚁兽");
static const u8 sText_pkmn632[] = _("铁蚁");
static const u8 sText_pkmn633[] = _("单首龙");
static const u8 sText_pkmn634[] = _("双首暴龙");
static const u8 sText_pkmn635[] = _("三首恶龙");
static const u8 sText_pkmn636[] = _("燃烧虫");
static const u8 sText_pkmn637[] = _("火神蛾");
static const u8 sText_pkmn638[] = _("勾帕路翁");
static const u8 sText_pkmn639[] = _("代拉基翁");
static const u8 sText_pkmn640[] = _("毕力吉翁");
static const u8 sText_pkmn641[] = _("龙卷云");
static const u8 sText_pkmn642[] = _("雷电云");
static const u8 sText_pkmn643[] = _("莱希拉姆");
static const u8 sText_pkmn644[] = _("捷克罗姆");
static const u8 sText_pkmn645[] = _("土地云");
static const u8 sText_pkmn646[] = _("酋雷姆");
static const u8 sText_pkmn647[] = _("凯路迪欧");
static const u8 sText_pkmn648[] = _("美洛耶塔");
static const u8 sText_pkmn649[] = _("盖诺赛克特");
static const u8 sText_pkmn650[] = _("哈力栗");
static const u8 sText_pkmn651[] = _("胖胖哈力");
static const u8 sText_pkmn652[] = _("布里卡隆");
static const u8 sText_pkmn653[] = _("火狐狸");
static const u8 sText_pkmn654[] = _("长尾火狐");
static const u8 sText_pkmn655[] = _("妖火红狐");
static const u8 sText_pkmn656[] = _("呱呱泡蛙");
static const u8 sText_pkmn657[] = _("呱头蛙");
static const u8 sText_pkmn658[] = _("甲贺忍蛙");
static const u8 sText_pkmn659[] = _("掘掘兔");
static const u8 sText_pkmn660[] = _("掘地兔");
static const u8 sText_pkmn661[] = _("小箭雀");
static const u8 sText_pkmn662[] = _("火箭雀");
static const u8 sText_pkmn663[] = _("烈箭鹰");
static const u8 sText_pkmn664[] = _("粉蝶虫");
static const u8 sText_pkmn665[] = _("粉蝶蛹");
static const u8 sText_pkmn666[] = _("彩粉蝶");
static const u8 sText_pkmn667[] = _("小狮狮");
static const u8 sText_pkmn668[] = _("火炎狮");
static const u8 sText_pkmn669[] = _("花蓓蓓");
static const u8 sText_pkmn670[] = _("花叶蒂");
static const u8 sText_pkmn671[] = _("花洁夫人");
static const u8 sText_pkmn672[] = _("坐骑小羊");
static const u8 sText_pkmn673[] = _("坐骑山羊");
static const u8 sText_pkmn674[] = _("顽皮熊猫");
static const u8 sText_pkmn675[] = _("流氓熊猫");
static const u8 sText_pkmn676[] = _("多丽米亚");
static const u8 sText_pkmn677[] = _("妙喵");
static const u8 sText_pkmn678[] = _("超能妙喵");
static const u8 sText_pkmn679[] = _("独剑鞘");
static const u8 sText_pkmn680[] = _("双剑鞘");
static const u8 sText_pkmn681[] = _("坚盾剑怪");
static const u8 sText_pkmn682[] = _("粉香香");
static const u8 sText_pkmn683[] = _("芳香精");
static const u8 sText_pkmn684[] = _("绵绵泡芙");
static const u8 sText_pkmn685[] = _("胖甜妮");
static const u8 sText_pkmn686[] = _("好啦鱿");
static const u8 sText_pkmn687[] = _("乌贼王");
static const u8 sText_pkmn688[] = _("龟脚脚");
static const u8 sText_pkmn689[] = _("龟足巨铠");
static const u8 sText_pkmn690[] = _("垃垃藻");
static const u8 sText_pkmn691[] = _("毒藻龙");
static const u8 sText_pkmn692[] = _("铁臂枪虾");
static const u8 sText_pkmn693[] = _("钢炮臂虾");
static const u8 sText_pkmn694[] = _("伞电蜥");
static const u8 sText_pkmn695[] = _("光电伞蜥");
static const u8 sText_pkmn696[] = _("宝宝暴龙");
static const u8 sText_pkmn697[] = _("怪颚龙");
static const u8 sText_pkmn698[] = _("冰雪龙");
static const u8 sText_pkmn699[] = _("冰雪巨龙");
static const u8 sText_pkmn700[] = _("仙子伊布");
static const u8 sText_pkmn701[] = _("摔角鹰人");
static const u8 sText_pkmn702[] = _("咚咚鼠");
static const u8 sText_pkmn703[] = _("小碎钻");
static const u8 sText_pkmn704[] = _("黏黏宝");
static const u8 sText_pkmn705[] = _("黏美儿");
static const u8 sText_pkmn706[] = _("黏美龙");
static const u8 sText_pkmn707[] = _("钥圈儿");
static const u8 sText_pkmn708[] = _("小木灵");
static const u8 sText_pkmn709[] = _("朽木妖");
static const u8 sText_pkmn710[] = _("南瓜精");
static const u8 sText_pkmn711[] = _("南瓜怪人");
static const u8 sText_pkmn712[] = _("冰宝");
static const u8 sText_pkmn713[] = _("冰岩怪");
static const u8 sText_pkmn714[] = _("嗡蝠");
static const u8 sText_pkmn715[] = _("音波龙");
static const u8 sText_pkmn716[] = _("哲尔尼亚斯");
static const u8 sText_pkmn717[] = _("伊裴尔塔尔");
static const u8 sText_pkmn718[] = _("基格尔德");
static const u8 sText_pkmn719[] = _("蒂安希");
static const u8 sText_pkmn720[] = _("胡帕");
static const u8 sText_pkmn721[] = _("波尔凯尼恩");
static const u8 sText_pkmn722[] = _("木木枭");
static const u8 sText_pkmn723[] = _("投羽枭");
static const u8 sText_pkmn724[] = _("狙射树枭");
static const u8 sText_pkmn725[] = _("火斑喵");
static const u8 sText_pkmn726[] = _("炎热喵");
static const u8 sText_pkmn727[] = _("炽焰咆哮虎");
static const u8 sText_pkmn728[] = _("球球海狮");
static const u8 sText_pkmn729[] = _("花漾海狮");
static const u8 sText_pkmn730[] = _("西狮海壬");
static const u8 sText_pkmn731[] = _("小笃儿");
static const u8 sText_pkmn732[] = _("喇叭啄鸟");
static const u8 sText_pkmn733[] = _("铳嘴大鸟");
static const u8 sText_pkmn734[] = _("猫鼬少");
static const u8 sText_pkmn735[] = _("猫鼬探长");
static const u8 sText_pkmn736[] = _("强颚鸡母虫");
static const u8 sText_pkmn737[] = _("虫电宝");
static const u8 sText_pkmn738[] = _("锹农炮虫");
static const u8 sText_pkmn739[] = _("好胜蟹");
static const u8 sText_pkmn740[] = _("好胜毛蟹");
static const u8 sText_pkmn741[] = _("花舞鸟");
static const u8 sText_pkmn742[] = _("萌虻");
static const u8 sText_pkmn743[] = _("蝶结萌虻");
static const u8 sText_pkmn744[] = _("岩狗狗");
static const u8 sText_pkmn745[] = _("鬃岩狼人");
static const u8 sText_pkmn746[] = _("弱丁鱼");
static const u8 sText_pkmn747[] = _("好坏星");
static const u8 sText_pkmn748[] = _("超坏星");
static const u8 sText_pkmn749[] = _("泥驴仔");
static const u8 sText_pkmn750[] = _("重泥挽马");
static const u8 sText_pkmn751[] = _("滴蛛");
static const u8 sText_pkmn752[] = _("滴蛛霸");
static const u8 sText_pkmn753[] = _("伪螳草");
static const u8 sText_pkmn754[] = _("兰螳花");
static const u8 sText_pkmn755[] = _("睡睡菇");
static const u8 sText_pkmn756[] = _("灯罩夜菇");
static const u8 sText_pkmn757[] = _("夜盗火蜥");
static const u8 sText_pkmn758[] = _("焰后蜥");
static const u8 sText_pkmn759[] = _("童偶熊");
static const u8 sText_pkmn760[] = _("穿着熊");
static const u8 sText_pkmn761[] = _("甜竹竹");
static const u8 sText_pkmn762[] = _("甜舞妮");
static const u8 sText_pkmn763[] = _("甜冷美后");
static const u8 sText_pkmn764[] = _("花疗环环");
static const u8 sText_pkmn765[] = _("智挥猩");
static const u8 sText_pkmn766[] = _("投掷猴");
static const u8 sText_pkmn767[] = _("胆小虫");
static const u8 sText_pkmn768[] = _("具甲武者");
static const u8 sText_pkmn769[] = _("沙丘娃");
static const u8 sText_pkmn770[] = _("噬沙堡爷");
static const u8 sText_pkmn771[] = _("拳海参");
static const u8 sText_pkmn772[] = _("属性：空");
static const u8 sText_pkmn773[] = _("银伴战兽");
static const u8 sText_pkmn774[] = _("小陨星");
static const u8 sText_pkmn775[] = _("树枕尾熊");
static const u8 sText_pkmn776[] = _("爆焰龟兽");
static const u8 sText_pkmn777[] = _("托戈德玛尔");
static const u8 sText_pkmn778[] = _("谜拟Ｑ");
static const u8 sText_pkmn779[] = _("磨牙彩皮鱼");
static const u8 sText_pkmn780[] = _("老翁龙");
static const u8 sText_pkmn781[] = _("破破舵轮");
static const u8 sText_pkmn782[] = _("心鳞宝");
static const u8 sText_pkmn783[] = _("鳞甲龙");
static const u8 sText_pkmn784[] = _("杖尾鳞甲龙");
static const u8 sText_pkmn785[] = _("卡璞.鸣鸣");
static const u8 sText_pkmn786[] = _("卡璞.蝶蝶");
static const u8 sText_pkmn787[] = _("卡璞.哞哞");
static const u8 sText_pkmn788[] = _("卡璞.鳍鳍");
static const u8 sText_pkmn789[] = _("科斯莫古");
static const u8 sText_pkmn790[] = _("科斯莫姆");
static const u8 sText_pkmn791[] = _("索尔迦雷欧");
static const u8 sText_pkmn792[] = _("露奈雅拉");
static const u8 sText_pkmn793[] = _("虚吾伊德");
static const u8 sText_pkmn794[] = _("爆肌蚊");
static const u8 sText_pkmn795[] = _("费洛美螂");
static const u8 sText_pkmn796[] = _("电束木");
static const u8 sText_pkmn797[] = _("铁火辉夜");
static const u8 sText_pkmn798[] = _("纸御剑");
static const u8 sText_pkmn799[] = _("恶食大王");
static const u8 sText_pkmn800[] = _("奈克洛兹玛");
static const u8 sText_pkmn801[] = _("玛机雅娜");
static const u8 sText_pkmn802[] = _("玛夏多");
static const u8 sText_pkmn803[] = _("毒贝比");
static const u8 sText_pkmn804[] = _("四颚针龙");
static const u8 sText_pkmn805[] = _("垒磊石");
static const u8 sText_pkmn806[] = _("砰头小丑");
static const u8 sText_pkmn807[] = _("捷拉奥拉");

// Sets of multichoices.
static const struct ListMenuItem sSet1[] =
{
  {sText_pkmn1, 1},
  {sText_pkmn2, 2},
  {sText_pkmn3, 3},
  {sText_pkmn4, 4},
  {sText_pkmn5, 5},
  {sText_pkmn6, 6},
  {sText_pkmn7, 7},
  {sText_pkmn8, 8},
  {sText_pkmn9, 9},
  {sText_pkmn10, 10},
  {sText_pkmn11, 11},
  {sText_pkmn12, 12},
  {sText_pkmn13, 13},
  {sText_pkmn14, 14},
  {sText_pkmn15, 15},
  {sText_pkmn16, 16},
  {sText_pkmn17, 17},
  {sText_pkmn18, 18},
  {sText_pkmn19, 19},
  {sText_pkmn20, 20},
  {sText_pkmn21, 21},
  {sText_pkmn22, 22},
  {sText_pkmn23, 23},
  {sText_pkmn24, 24},
  {sText_pkmn25, 25},
  {sText_pkmn26, 26},
  {sText_pkmn27, 27},
  {sText_pkmn28, 28},
  {sText_pkmn29, 29},
  {sText_pkmn30, 30},
  {sText_pkmn31, 31},
  {sText_pkmn32, 32},
  {sText_pkmn33, 33},
  {sText_pkmn34, 34},
  {sText_pkmn35, 35},
  {sText_pkmn36, 36},
  {sText_pkmn37, 37},
  {sText_pkmn38, 38},
  {sText_pkmn39, 39},
  {sText_pkmn40, 40},
  {sText_pkmn41, 41},
  {sText_pkmn42, 42},
  {sText_pkmn43, 43},
  {sText_pkmn44, 44},
  {sText_pkmn45, 45},
  {sText_pkmn46, 46},
  {sText_pkmn47, 47},
  {sText_pkmn48, 48},
  {sText_pkmn49, 49},
  {sText_pkmn50, 50},
  {sText_pkmn51, 51},
  {sText_pkmn52, 52},
  {sText_pkmn53, 53},
  {sText_pkmn54, 54},
  {sText_pkmn55, 55},
  {sText_pkmn56, 56},
  {sText_pkmn57, 57},
  {sText_pkmn58, 58},
  {sText_pkmn59, 59},
  {sText_pkmn60, 60},
  {sText_pkmn61, 61},
  {sText_pkmn62, 62},
  {sText_pkmn63, 63},
  {sText_pkmn64, 64},
  {sText_pkmn65, 65},
  {sText_pkmn66, 66},
  {sText_pkmn67, 67},
  {sText_pkmn68, 68},
  {sText_pkmn69, 69},
  {sText_pkmn70, 70},
  {sText_pkmn71, 71},
  {sText_pkmn72, 72},
  {sText_pkmn73, 73},
  {sText_pkmn74, 74},
  {sText_pkmn75, 75},
  {sText_pkmn76, 76},
  {sText_pkmn77, 77},
  {sText_pkmn78, 78},
  {sText_pkmn79, 79},
  {sText_pkmn80, 80},
  {sText_pkmn81, 81},
  {sText_pkmn82, 82},
  {sText_pkmn83, 83},
  {sText_pkmn84, 84},
  {sText_pkmn85, 85},
  {sText_pkmn86, 86},
  {sText_pkmn87, 87},
  {sText_pkmn88, 88},
  {sText_pkmn89, 89},
  {sText_pkmn90, 90},
  {sText_pkmn91, 91},
  {sText_pkmn92, 92},
  {sText_pkmn93, 93},
  {sText_pkmn94, 94},
  {sText_pkmn95, 95},
  {sText_pkmn96, 96},
  {sText_pkmn97, 97},
  {sText_pkmn98, 98},
  {sText_pkmn99, 99},
  {sText_pkmn100, 100},
  {sText_pkmn101, 101},
  {sText_pkmn102, 102},
  {sText_pkmn103, 103},
  {sText_pkmn104, 104},
  {sText_pkmn105, 105},
  {sText_pkmn106, 106},
  {sText_pkmn107, 107},
  {sText_pkmn108, 108},
  {sText_pkmn109, 109},
  {sText_pkmn110, 110},
  {sText_pkmn111, 111},
  {sText_pkmn112, 112},
  {sText_pkmn113, 113},
  {sText_pkmn114, 114},
  {sText_pkmn115, 115},
  {sText_pkmn116, 116},
  {sText_pkmn117, 117},
  {sText_pkmn118, 118},
  {sText_pkmn119, 119},
  {sText_pkmn120, 120},
  {sText_pkmn121, 121},
  {sText_pkmn122, 122},
  {sText_pkmn123, 123},
  {sText_pkmn124, 124},
  {sText_pkmn125, 125},
  {sText_pkmn126, 126},
  {sText_pkmn127, 127},
  {sText_pkmn128, 128},
  {sText_pkmn129, 129},
  {sText_pkmn130, 130},
  {sText_pkmn131, 131},
  {sText_pkmn132, 132},
  {sText_pkmn133, 133},
  {sText_pkmn134, 134},
  {sText_pkmn135, 135},
  {sText_pkmn136, 136},
  {sText_pkmn137, 137},
  {sText_pkmn138, 138},
  {sText_pkmn139, 139},
  {sText_pkmn140, 140},
  {sText_pkmn141, 141},
  {sText_pkmn142, 142},
  {sText_pkmn143, 143},
  {sText_pkmn144, 144},
  {sText_pkmn145, 145},
  {sText_pkmn146, 146},
  {sText_pkmn147, 147},
  {sText_pkmn148, 148},
  {sText_pkmn149, 149},
  {sText_pkmn150, 150},
  {sText_pkmn151, 151},
  {sText_pkmn152, 152},
  {sText_pkmn153, 153},
  {sText_pkmn154, 154},
  {sText_pkmn155, 155},
  {sText_pkmn156, 156},
  {sText_pkmn157, 157},
  {sText_pkmn158, 158},
  {sText_pkmn159, 159},
  {sText_pkmn160, 160},
  {sText_pkmn161, 161},
  {sText_pkmn162, 162},
  {sText_pkmn163, 163},
  {sText_pkmn164, 164},
  {sText_pkmn165, 165},
  {sText_pkmn166, 166},
  {sText_pkmn167, 167},
  {sText_pkmn168, 168},
  {sText_pkmn169, 169},
  {sText_pkmn170, 170},
  {sText_pkmn171, 171},
  {sText_pkmn172, 172},
  {sText_pkmn173, 173},
  {sText_pkmn174, 174},
  {sText_pkmn175, 175},
  {sText_pkmn176, 176},
  {sText_pkmn177, 177},
  {sText_pkmn178, 178},
  {sText_pkmn179, 179},
  {sText_pkmn180, 180},
  {sText_pkmn181, 181},
  {sText_pkmn182, 182},
  {sText_pkmn183, 183},
  {sText_pkmn184, 184},
  {sText_pkmn185, 185},
  {sText_pkmn186, 186},
  {sText_pkmn187, 187},
  {sText_pkmn188, 188},
  {sText_pkmn189, 189},
  {sText_pkmn190, 190},
  {sText_pkmn191, 191},
  {sText_pkmn192, 192},
  {sText_pkmn193, 193},
  {sText_pkmn194, 194},
  {sText_pkmn195, 195},
  {sText_pkmn196, 196},
  {sText_pkmn197, 197},
  {sText_pkmn198, 198},
  {sText_pkmn199, 199},
  {sText_pkmn200, 200},
  {sText_pkmn201, 201},
  {sText_pkmn202, 202},
  {sText_pkmn203, 203},
  {sText_pkmn204, 204},
  {sText_pkmn205, 205},
  {sText_pkmn206, 206},
  {sText_pkmn207, 207},
  {sText_pkmn208, 208},
  {sText_pkmn209, 209},
  {sText_pkmn210, 210},
  {sText_pkmn211, 211},
  {sText_pkmn212, 212},
  {sText_pkmn213, 213},
  {sText_pkmn214, 214},
  {sText_pkmn215, 215},
  {sText_pkmn216, 216},
  {sText_pkmn217, 217},
  {sText_pkmn218, 218},
  {sText_pkmn219, 219},
  {sText_pkmn220, 220},
  {sText_pkmn221, 221},
  {sText_pkmn222, 222},
  {sText_pkmn223, 223},
  {sText_pkmn224, 224},
  {sText_pkmn225, 225},
  {sText_pkmn226, 226},
  {sText_pkmn227, 227},
  {sText_pkmn228, 228},
  {sText_pkmn229, 229},
  {sText_pkmn230, 230},
  {sText_pkmn231, 231},
  {sText_pkmn232, 232},
  {sText_pkmn233, 233},
  {sText_pkmn234, 234},
  {sText_pkmn235, 235},
  {sText_pkmn236, 236},
  {sText_pkmn237, 237},
  {sText_pkmn238, 238},
  {sText_pkmn239, 239},
  {sText_pkmn240, 240},
  {sText_pkmn241, 241},
  {sText_pkmn242, 242},
  {sText_pkmn243, 243},
  {sText_pkmn244, 244},
  {sText_pkmn245, 245},
  {sText_pkmn246, 246},
  {sText_pkmn247, 247},
  {sText_pkmn248, 248},
  {sText_pkmn249, 249},
  {sText_pkmn250, 250},
  {sText_pkmn251, 251},
  {sText_pkmn252, 252},
  {sText_pkmn253, 253},
  {sText_pkmn254, 254},
  {sText_pkmn255, 255},
  {sText_pkmn256, 256},
  {sText_pkmn257, 257},
  {sText_pkmn258, 258},
  {sText_pkmn259, 259},
  {sText_pkmn260, 260},
  {sText_pkmn261, 261},
  {sText_pkmn262, 262},
  {sText_pkmn263, 263},
  {sText_pkmn264, 264},
  {sText_pkmn265, 265},
  {sText_pkmn266, 266},
  {sText_pkmn267, 267},
  {sText_pkmn268, 268},
  {sText_pkmn269, 269},
  {sText_pkmn270, 270},
  {sText_pkmn271, 271},
  {sText_pkmn272, 272},
  {sText_pkmn273, 273},
  {sText_pkmn274, 274},
  {sText_pkmn275, 275},
  {sText_pkmn276, 276},
  {sText_pkmn277, 277},
  {sText_pkmn278, 278},
  {sText_pkmn279, 279},
  {sText_pkmn280, 280},
  {sText_pkmn281, 281},
  {sText_pkmn282, 282},
  {sText_pkmn283, 283},
  {sText_pkmn284, 284},
  {sText_pkmn285, 285},
  {sText_pkmn286, 286},
  {sText_pkmn287, 287},
  {sText_pkmn288, 288},
  {sText_pkmn289, 289},
  {sText_pkmn290, 290},
  {sText_pkmn291, 291},
  {sText_pkmn292, 292},
  {sText_pkmn293, 293},
  {sText_pkmn294, 294},
  {sText_pkmn295, 295},
  {sText_pkmn296, 296},
  {sText_pkmn297, 297},
  {sText_pkmn298, 298},
  {sText_pkmn299, 299},
  {sText_pkmn300, 300},
  {sText_pkmn301, 301},
  {sText_pkmn302, 302},
  {sText_pkmn303, 303},
  {sText_pkmn304, 304},
  {sText_pkmn305, 305},
  {sText_pkmn306, 306},
  {sText_pkmn307, 307},
  {sText_pkmn308, 308},
  {sText_pkmn309, 309},
  {sText_pkmn310, 310},
  {sText_pkmn311, 311},
  {sText_pkmn312, 312},
  {sText_pkmn313, 313},
  {sText_pkmn314, 314},
  {sText_pkmn315, 315},
  {sText_pkmn316, 316},
  {sText_pkmn317, 317},
  {sText_pkmn318, 318},
  {sText_pkmn319, 319},
  {sText_pkmn320, 320},
  {sText_pkmn321, 321},
  {sText_pkmn322, 322},
  {sText_pkmn323, 323},
  {sText_pkmn324, 324},
  {sText_pkmn325, 325},
  {sText_pkmn326, 326},
  {sText_pkmn327, 327},
  {sText_pkmn328, 328},
  {sText_pkmn329, 329},
  {sText_pkmn330, 330},
  {sText_pkmn331, 331},
  {sText_pkmn332, 332},
  {sText_pkmn333, 333},
  {sText_pkmn334, 334},
  {sText_pkmn335, 335},
  {sText_pkmn336, 336},
  {sText_pkmn337, 337},
  {sText_pkmn338, 338},
  {sText_pkmn339, 339},
  {sText_pkmn340, 340},
  {sText_pkmn341, 341},
  {sText_pkmn342, 342},
  {sText_pkmn343, 343},
  {sText_pkmn344, 344},
  {sText_pkmn345, 345},
  {sText_pkmn346, 346},
  {sText_pkmn347, 347},
  {sText_pkmn348, 348},
  {sText_pkmn349, 349},
  {sText_pkmn350, 350},
  {sText_pkmn351, 351},
  {sText_pkmn352, 352},
  {sText_pkmn353, 353},
  {sText_pkmn354, 354},
  {sText_pkmn355, 355},
  {sText_pkmn356, 356},
  {sText_pkmn357, 357},
  {sText_pkmn358, 358},
  {sText_pkmn359, 359},
  {sText_pkmn360, 360},
  {sText_pkmn361, 361},
  {sText_pkmn362, 362},
  {sText_pkmn363, 363},
  {sText_pkmn364, 364},
  {sText_pkmn365, 365},
  {sText_pkmn366, 366},
  {sText_pkmn367, 367},
  {sText_pkmn368, 368},
  {sText_pkmn369, 369},
  {sText_pkmn370, 370},
  {sText_pkmn371, 371},
  {sText_pkmn372, 372},
  {sText_pkmn373, 373},
  {sText_pkmn374, 374},
  {sText_pkmn375, 375},
  {sText_pkmn376, 376},
  {sText_pkmn377, 377},
  {sText_pkmn378, 378},
  {sText_pkmn379, 379},
  {sText_pkmn380, 380},
  {sText_pkmn381, 381},
  {sText_pkmn382, 382},
  {sText_pkmn383, 383},
  {sText_pkmn384, 384},
  {sText_pkmn385, 385},
  {sText_pkmn386, 386},
  {sText_pkmn387, 387},
  {sText_pkmn388, 388},
  {sText_pkmn389, 389},
  {sText_pkmn390, 390},
  {sText_pkmn391, 391},
  {sText_pkmn392, 392},
  {sText_pkmn393, 393},
  {sText_pkmn394, 394},
  {sText_pkmn395, 395},
  {sText_pkmn396, 396},
  {sText_pkmn397, 397},
  {sText_pkmn398, 398},
  {sText_pkmn399, 399},
  {sText_pkmn400, 400},
  {sText_pkmn401, 401},
  {sText_pkmn402, 402},
  {sText_pkmn403, 403},
  {sText_pkmn404, 404},
  {sText_pkmn405, 405},
  {sText_pkmn406, 406},
  {sText_pkmn407, 407},
  {sText_pkmn408, 408},
  {sText_pkmn409, 409},
  {sText_pkmn410, 410},
  {sText_pkmn411, 411},
  {sText_pkmn412, 412},
  {sText_pkmn413, 413},
  {sText_pkmn414, 414},
  {sText_pkmn415, 415},
  {sText_pkmn416, 416},
  {sText_pkmn417, 417},
  {sText_pkmn418, 418},
  {sText_pkmn419, 419},
  {sText_pkmn420, 420},
  {sText_pkmn421, 421},
  {sText_pkmn422, 422},
  {sText_pkmn423, 423},
  {sText_pkmn424, 424},
  {sText_pkmn425, 425},
  {sText_pkmn426, 426},
  {sText_pkmn427, 427},
  {sText_pkmn428, 428},
  {sText_pkmn429, 429},
  {sText_pkmn430, 430},
  {sText_pkmn431, 431},
  {sText_pkmn432, 432},
  {sText_pkmn433, 433},
  {sText_pkmn434, 434},
  {sText_pkmn435, 435},
  {sText_pkmn436, 436},
  {sText_pkmn437, 437},
  {sText_pkmn438, 438},
  {sText_pkmn439, 439},
  {sText_pkmn440, 440},
  {sText_pkmn441, 441},
  {sText_pkmn442, 442},
  {sText_pkmn443, 443},
  {sText_pkmn444, 444},
  {sText_pkmn445, 445},
  {sText_pkmn446, 446},
  {sText_pkmn447, 447},
  {sText_pkmn448, 448},
  {sText_pkmn449, 449},
  {sText_pkmn450, 450},
  {sText_pkmn451, 451},
  {sText_pkmn452, 452},
  {sText_pkmn453, 453},
  {sText_pkmn454, 454},
  {sText_pkmn455, 455},
  {sText_pkmn456, 456},
  {sText_pkmn457, 457},
  {sText_pkmn458, 458},
  {sText_pkmn459, 459},
  {sText_pkmn460, 460},
  {sText_pkmn461, 461},
  {sText_pkmn462, 462},
  {sText_pkmn463, 463},
  {sText_pkmn464, 464},
  {sText_pkmn465, 465},
  {sText_pkmn466, 466},
  {sText_pkmn467, 467},
  {sText_pkmn468, 468},
  {sText_pkmn469, 469},
  {sText_pkmn470, 470},
  {sText_pkmn471, 471},
  {sText_pkmn472, 472},
  {sText_pkmn473, 473},
  {sText_pkmn474, 474},
  {sText_pkmn475, 475},
  {sText_pkmn476, 476},
  {sText_pkmn477, 477},
  {sText_pkmn478, 478},
  {sText_pkmn479, 479},
  {sText_pkmn480, 480},
  {sText_pkmn481, 481},
  {sText_pkmn482, 482},
  {sText_pkmn483, 483},
  {sText_pkmn484, 484},
  {sText_pkmn485, 485},
  {sText_pkmn486, 486},
  {sText_pkmn487, 487},
  {sText_pkmn488, 488},
  {sText_pkmn489, 489},
  {sText_pkmn490, 490},
  {sText_pkmn491, 491},
  {sText_pkmn492, 492},
  {sText_pkmn493, 493},
  {sText_pkmn494, 494},
  {sText_pkmn495, 495},
  {sText_pkmn496, 496},
  {sText_pkmn497, 497},
  {sText_pkmn498, 498},
  {sText_pkmn499, 499},
  {sText_pkmn500, 500},
  {sText_pkmn501, 501},
  {sText_pkmn502, 502},
  {sText_pkmn503, 503},
  {sText_pkmn504, 504},
  {sText_pkmn505, 505},
  {sText_pkmn506, 506},
  {sText_pkmn507, 507},
  {sText_pkmn508, 508},
  {sText_pkmn509, 509},
  {sText_pkmn510, 510},
  {sText_pkmn511, 511},
  {sText_pkmn512, 512},
  {sText_pkmn513, 513},
  {sText_pkmn514, 514},
  {sText_pkmn515, 515},
  {sText_pkmn516, 516},
  {sText_pkmn517, 517},
  {sText_pkmn518, 518},
  {sText_pkmn519, 519},
  {sText_pkmn520, 520},
  {sText_pkmn521, 521},
  {sText_pkmn522, 522},
  {sText_pkmn523, 523},
  {sText_pkmn524, 524},
  {sText_pkmn525, 525},
  {sText_pkmn526, 526},
  {sText_pkmn527, 527},
  {sText_pkmn528, 528},
  {sText_pkmn529, 529},
  {sText_pkmn530, 530},
  {sText_pkmn531, 531},
  {sText_pkmn532, 532},
  {sText_pkmn533, 533},
  {sText_pkmn534, 534},
  {sText_pkmn535, 535},
  {sText_pkmn536, 536},
  {sText_pkmn537, 537},
  {sText_pkmn538, 538},
  {sText_pkmn539, 539},
  {sText_pkmn540, 540},
  {sText_pkmn541, 541},
  {sText_pkmn542, 542},
  {sText_pkmn543, 543},
  {sText_pkmn544, 544},
  {sText_pkmn545, 545},
  {sText_pkmn546, 546},
  {sText_pkmn547, 547},
  {sText_pkmn548, 548},
  {sText_pkmn549, 549},
  {sText_pkmn550, 550},
  {sText_pkmn551, 551},
  {sText_pkmn552, 552},
  {sText_pkmn553, 553},
  {sText_pkmn554, 554},
  {sText_pkmn555, 555},
  {sText_pkmn556, 556},
  {sText_pkmn557, 557},
  {sText_pkmn558, 558},
  {sText_pkmn559, 559},
  {sText_pkmn560, 560},
  {sText_pkmn561, 561},
  {sText_pkmn562, 562},
  {sText_pkmn563, 563},
  {sText_pkmn564, 564},
  {sText_pkmn565, 565},
  {sText_pkmn566, 566},
  {sText_pkmn567, 567},
  {sText_pkmn568, 568},
  {sText_pkmn569, 569},
  {sText_pkmn570, 570},
  {sText_pkmn571, 571},
  {sText_pkmn572, 572},
  {sText_pkmn573, 573},
  {sText_pkmn574, 574},
  {sText_pkmn575, 575},
  {sText_pkmn576, 576},
  {sText_pkmn577, 577},
  {sText_pkmn578, 578},
  {sText_pkmn579, 579},
  {sText_pkmn580, 580},
  {sText_pkmn581, 581},
  {sText_pkmn582, 582},
  {sText_pkmn583, 583},
  {sText_pkmn584, 584},
  {sText_pkmn585, 585},
  {sText_pkmn586, 586},
  {sText_pkmn587, 587},
  {sText_pkmn588, 588},
  {sText_pkmn589, 589},
  {sText_pkmn590, 590},
  {sText_pkmn591, 591},
  {sText_pkmn592, 592},
  {sText_pkmn593, 593},
  {sText_pkmn594, 594},
  {sText_pkmn595, 595},
  {sText_pkmn596, 596},
  {sText_pkmn597, 597},
  {sText_pkmn598, 598},
  {sText_pkmn599, 599},
  {sText_pkmn600, 600},
  {sText_pkmn601, 601},
  {sText_pkmn602, 602},
  {sText_pkmn603, 603},
  {sText_pkmn604, 604},
  {sText_pkmn605, 605},
  {sText_pkmn606, 606},
  {sText_pkmn607, 607},
  {sText_pkmn608, 608},
  {sText_pkmn609, 609},
  {sText_pkmn610, 610},
  {sText_pkmn611, 611},
  {sText_pkmn612, 612},
  {sText_pkmn613, 613},
  {sText_pkmn614, 614},
  {sText_pkmn615, 615},
  {sText_pkmn616, 616},
  {sText_pkmn617, 617},
  {sText_pkmn618, 618},
  {sText_pkmn619, 619},
  {sText_pkmn620, 620},
  {sText_pkmn621, 621},
  {sText_pkmn622, 622},
  {sText_pkmn623, 623},
  {sText_pkmn624, 624},
  {sText_pkmn625, 625},
  {sText_pkmn626, 626},
  {sText_pkmn627, 627},
  {sText_pkmn628, 628},
  {sText_pkmn629, 629},
  {sText_pkmn630, 630},
  {sText_pkmn631, 631},
  {sText_pkmn632, 632},
  {sText_pkmn633, 633},
  {sText_pkmn634, 634},
  {sText_pkmn635, 635},
  {sText_pkmn636, 636},
  {sText_pkmn637, 637},
  {sText_pkmn638, 638},
  {sText_pkmn639, 639},
  {sText_pkmn640, 640},
  {sText_pkmn641, 641},
  {sText_pkmn642, 642},
  {sText_pkmn643, 643},
  {sText_pkmn644, 644},
  {sText_pkmn645, 645},
  {sText_pkmn646, 646},
  {sText_pkmn647, 647},
  {sText_pkmn648, 648},
  {sText_pkmn649, 649},
  {sText_pkmn650, 650},
  {sText_pkmn651, 651},
  {sText_pkmn652, 652},
  {sText_pkmn653, 653},
  {sText_pkmn654, 654},
  {sText_pkmn655, 655},
  {sText_pkmn656, 656},
  {sText_pkmn657, 657},
  {sText_pkmn658, 658},
  {sText_pkmn659, 659},
  {sText_pkmn660, 660},
  {sText_pkmn661, 661},
  {sText_pkmn662, 662},
  {sText_pkmn663, 663},
  {sText_pkmn664, 664},
  {sText_pkmn665, 665},
  {sText_pkmn666, 666},
  {sText_pkmn667, 667},
  {sText_pkmn668, 668},
  {sText_pkmn669, 669},
  {sText_pkmn670, 670},
  {sText_pkmn671, 671},
  {sText_pkmn672, 672},
  {sText_pkmn673, 673},
  {sText_pkmn674, 674},
  {sText_pkmn675, 675},
  {sText_pkmn676, 676},
  {sText_pkmn677, 677},
  {sText_pkmn678, 678},
  {sText_pkmn679, 679},
  {sText_pkmn680, 680},
  {sText_pkmn681, 681},
  {sText_pkmn682, 682},
  {sText_pkmn683, 683},
  {sText_pkmn684, 684},
  {sText_pkmn685, 685},
  {sText_pkmn686, 686},
  {sText_pkmn687, 687},
  {sText_pkmn688, 688},
  {sText_pkmn689, 689},
  {sText_pkmn690, 690},
  {sText_pkmn691, 691},
  {sText_pkmn692, 692},
  {sText_pkmn693, 693},
  {sText_pkmn694, 694},
  {sText_pkmn695, 695},
  {sText_pkmn696, 696},
  {sText_pkmn697, 697},
  {sText_pkmn698, 698},
  {sText_pkmn699, 699},
  {sText_pkmn700, 700},
  {sText_pkmn701, 701},
  {sText_pkmn702, 702},
  {sText_pkmn703, 703},
  {sText_pkmn704, 704},
  {sText_pkmn705, 705},
  {sText_pkmn706, 706},
  {sText_pkmn707, 707},
  {sText_pkmn708, 708},
  {sText_pkmn709, 709},
  {sText_pkmn710, 710},
  {sText_pkmn711, 711},
  {sText_pkmn712, 712},
  {sText_pkmn713, 713},
  {sText_pkmn714, 714},
  {sText_pkmn715, 715},
  {sText_pkmn716, 716},
  {sText_pkmn717, 717},
  {sText_pkmn718, 718},
  {sText_pkmn719, 719},
  {sText_pkmn720, 720},
  {sText_pkmn721, 721},
  {sText_pkmn722, 722},
  {sText_pkmn723, 723},
  {sText_pkmn724, 724},
  {sText_pkmn725, 725},
  {sText_pkmn726, 726},
  {sText_pkmn727, 727},
  {sText_pkmn728, 728},
  {sText_pkmn729, 729},
  {sText_pkmn730, 730},
  {sText_pkmn731, 731},
  {sText_pkmn732, 732},
  {sText_pkmn733, 733},
  {sText_pkmn734, 734},
  {sText_pkmn735, 735},
  {sText_pkmn736, 736},
  {sText_pkmn737, 737},
  {sText_pkmn738, 738},
  {sText_pkmn739, 739},
  {sText_pkmn740, 740},
  {sText_pkmn741, 741},
  {sText_pkmn742, 742},
  {sText_pkmn743, 743},
  {sText_pkmn744, 744},
  {sText_pkmn745, 745},
  {sText_pkmn746, 746},
  {sText_pkmn747, 747},
  {sText_pkmn748, 748},
  {sText_pkmn749, 749},
  {sText_pkmn750, 750},
  {sText_pkmn751, 751},
  {sText_pkmn752, 752},
  {sText_pkmn753, 753},
  {sText_pkmn754, 754},
  {sText_pkmn755, 755},
  {sText_pkmn756, 756},
  {sText_pkmn757, 757},
  {sText_pkmn758, 758},
  {sText_pkmn759, 759},
  {sText_pkmn760, 760},
  {sText_pkmn761, 761},
  {sText_pkmn762, 762},
  {sText_pkmn763, 763},
  {sText_pkmn764, 764},
  {sText_pkmn765, 765},
  {sText_pkmn766, 766},
  {sText_pkmn767, 767},
  {sText_pkmn768, 768},
  {sText_pkmn769, 769},
  {sText_pkmn770, 770},
  {sText_pkmn771, 771},
  {sText_pkmn772, 772},
  {sText_pkmn773, 773},
  {sText_pkmn774, 774},
  {sText_pkmn775, 775},
  {sText_pkmn776, 776},
  {sText_pkmn777, 777},
  {sText_pkmn778, 778},
  {sText_pkmn779, 779},
  {sText_pkmn780, 780},
  {sText_pkmn781, 781},
  {sText_pkmn782, 782},
  {sText_pkmn783, 783},
  {sText_pkmn784, 784},
  {sText_pkmn785, 785},
  {sText_pkmn786, 786},
  {sText_pkmn787, 787},
  {sText_pkmn788, 788},
  {sText_pkmn789, 789},
  {sText_pkmn790, 790},
  {sText_pkmn791, 791},
  {sText_pkmn792, 792},
  {sText_pkmn793, 793},
  {sText_pkmn794, 794},
  {sText_pkmn795, 795},
  {sText_pkmn796, 796},
  {sText_pkmn797, 797},
  {sText_pkmn798, 798},
  {sText_pkmn799, 799},
  {sText_pkmn800, 800},
  {sText_pkmn801, 801},
  {sText_pkmn802, 802},
  {sText_pkmn803, 803},
  {sText_pkmn804, 804},
  {sText_pkmn805, 805},
  {sText_pkmn806, 806},
  {sText_pkmn807, 807},
};

static const struct ListMenuItem sSet2[] =
{
  {sText_pkmn807, 807},
  {sText_pkmn807, 807},
};

// Table of your multichoice sets.
struct
{
    const struct ListMenuItem *set;
    int count;
} static const sScrollingSets[] =
{
    {sSet1, ARRAY_COUNT(sSet1)},
    {sSet2, ARRAY_COUNT(sSet2)},
};

static void Task_ScrollingMultichoiceInput(u8 taskId);

static const struct ListMenuTemplate sMultichoiceListTemplate =
{
    .header_X = 0,
    .item_X = 8,
    .cursor_X = 0,
    .upText_Y = 1,
    .cursorPal = 2,
    .fillValue = 1,
    .cursorShadowPal = 3,
    .lettersSpacing = 1,
    .itemVerticalPadding = 0,
    .scrollMultiple = LIST_NO_MULTIPLE_SCROLL,
    .fontId = 1,
    .cursorKind = 0
};

// 0x8004 = set id
// 0x8005 = window X
// 0x8006 = window y
// 0x8007 = showed at once
// 0x8008 = Allow B press
void ScriptMenu_ScrollingMultichoice(void)
{
    int i, windowId, taskId, width = 0;
    int setId = gSpecialVar_0x8004;
    int left = gSpecialVar_0x8005;
    int top = gSpecialVar_0x8006;
    int maxShowed = gSpecialVar_0x8007;

    for (i = 0; i < sScrollingSets[setId].count; i++)
        width = display_text_and_get_width(sScrollingSets[setId].set[i].name, width);

    width = convert_pixel_width_to_tile_width(width);
    left = sub_80E2D5C(left, width);
    windowId = CreateWindowFromRect(left, top, width, maxShowed * 2);
    SetStandardWindowBorderStyle(windowId, 0);
    CopyWindowToVram(windowId, 3);

    gMultiuseListMenuTemplate = sMultichoiceListTemplate;
    gMultiuseListMenuTemplate.windowId = windowId;
    gMultiuseListMenuTemplate.items = sScrollingSets[setId].set;
    gMultiuseListMenuTemplate.totalItems = sScrollingSets[setId].count;
    gMultiuseListMenuTemplate.maxShowed = maxShowed;

    taskId = CreateTask(Task_ScrollingMultichoiceInput, 0);
    gTasks[taskId].data[0] = ListMenuInit(&gMultiuseListMenuTemplate, 0, 0);
    gTasks[taskId].data[1] = gSpecialVar_0x8008;
    gTasks[taskId].data[2] = windowId;
}

static void Task_ScrollingMultichoiceInput(u8 taskId)
{
    bool32 done = FALSE;
    s32 input = ListMenu_ProcessInput(gTasks[taskId].data[0]);

    switch (input)
    {
    case LIST_HEADER:
    case LIST_NOTHING_CHOSEN:
        break;
    case LIST_CANCEL:
        if (gTasks[taskId].data[1])
        {
            gSpecialVar_Result = 0x7F;
            done = TRUE;
        }
        break;
    default:
        gSpecialVar_Result = input;
        done = TRUE;
        break;
    }

    if (done)
    {
        DestroyListMenuTask(gTasks[taskId].data[0], NULL, NULL);
        ClearStdWindowAndFrame(gTasks[taskId].data[2], TRUE);
        RemoveWindow(gTasks[taskId].data[2]);
        EnableBothScriptContexts();
        DestroyTask(taskId);
    }
}
