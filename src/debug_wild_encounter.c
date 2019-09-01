#if DEBUG

#include "global.h"
#include "battle_setup.h"
#include "event_data.h"
#include "item.h"
#include "list_menu.h"
#include "main.h"
#include "map_name_popup.h"
#include "menu.h"
#include "pokedex.h"
#include "random.h"
#include "event_scripts.h"
#include "script.h"
#include "script_pokemon_80F8.h"
#include "sound.h"
#include "strings.h"
#include "task.h"
#include "wild_encounter.h"
#include "constants/items.h"
#include "constants/songs.h"
#define DEBUG_MAIN_MENU_HEIGHT 7
#define DEBUG_MAIN_MENU_WIDTH 13

void DebugWE_ShowMainMenu(void);
static void Debug_DestroyMainMenu(u8);
static void DebugAction_ChainCount(u8);
static void DebugAction_SetWildBattle(u8);
static void DebugAction_DoWildBattle(u8);
static void DebugAction_ShinyFlag(u8);
static void DebugAction_HiddenAbilityFlag(u8);
static void DebugAction_Cancel(u8);
static void DebugTask_HandleMainMenuInput(u8);

enum {
    DEBUG_MENU_CHAIN_COUNT,
    DEBUG_MENU_SETWILDBATTLE,
    DEBUG_MENU_DOWILDBATTLE,
  	DEBUG_MENU_SHINYFLAG,
    DEBUG_MENU_HIDDENABILITYFLAG,
    DEBUG_MENU_ITEM_CANCEL,
};

static const u8 gDebugText_ChainCount[] = _("连锁信息");
static const u8 gDebugText_SetWildBattle[] = _("设置野生");
static const u8 gDebugText_DoWildBattle[] = _("野生对战");
static const u8 gDebugText_ShinyFlag[] = _("闪光FLAG");
static const u8 gDebugText_HiddenAbilityFlag[] = _("梦特性FLAG");
static const u8 gDebugText_Cancel[] = _("退出");

static const struct ListMenuItem sDebugMenuItems[] =
{
  [DEBUG_MENU_CHAIN_COUNT] = {gDebugText_ChainCount, DEBUG_MENU_CHAIN_COUNT},
  [DEBUG_MENU_SETWILDBATTLE] = {gDebugText_SetWildBattle, DEBUG_MENU_SETWILDBATTLE},
	[DEBUG_MENU_DOWILDBATTLE] = {gDebugText_DoWildBattle, DEBUG_MENU_DOWILDBATTLE},
	[DEBUG_MENU_SHINYFLAG] = {gDebugText_ShinyFlag, DEBUG_MENU_SHINYFLAG},
	[DEBUG_MENU_HIDDENABILITYFLAG] = {gDebugText_HiddenAbilityFlag, DEBUG_MENU_HIDDENABILITYFLAG},
  [DEBUG_MENU_ITEM_CANCEL] = {gDebugText_Cancel, DEBUG_MENU_ITEM_CANCEL}
};

static void (*const sDebugMenuActions[])(u8) =
{
  [DEBUG_MENU_CHAIN_COUNT] = DebugAction_ChainCount,
  [DEBUG_MENU_SETWILDBATTLE] = DebugAction_SetWildBattle,
	[DEBUG_MENU_DOWILDBATTLE] = DebugAction_DoWildBattle,
	[DEBUG_MENU_SHINYFLAG] = DebugAction_ShinyFlag,
	[DEBUG_MENU_HIDDENABILITYFLAG] = DebugAction_HiddenAbilityFlag,
  [DEBUG_MENU_ITEM_CANCEL] = DebugAction_Cancel
};

static const struct WindowTemplate sDebugMenuWindowTemplate =
{
    .bg = 0,
    .tilemapLeft = 2,
    .tilemapTop = 1,
    .width = DEBUG_MAIN_MENU_WIDTH,
    .height = 2 * DEBUG_MAIN_MENU_HEIGHT,
    .paletteNum = 15,
    .baseBlock = 1,
};

static const struct ListMenuTemplate sDebugMenuListTemplate =
{
    .items = sDebugMenuItems,
    .moveCursorFunc = ListMenuDefaultCursorMoveFunc,
    .totalItems = ARRAY_COUNT(sDebugMenuItems),
    .maxShowed = DEBUG_MAIN_MENU_HEIGHT,
    .windowId = 0,
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

void DebugWE_ShowMainMenu(void) {
    struct ListMenuTemplate menuTemplate;
    u8 windowId;
    u8 menuTaskId;
    u8 inputTaskId;

    HideMapNamePopUpWindow();
    sub_81973A4();

	// create window
    windowId = AddWindow(&sDebugMenuWindowTemplate);
    DrawStdWindowFrame(windowId, FALSE);

    // create list menu
    menuTemplate = sDebugMenuListTemplate;
    menuTemplate.windowId = windowId;
    menuTaskId = ListMenuInit(&menuTemplate, 0, 0);

    // draw everything
    CopyWindowToVram(windowId, 3);

    // create input handler task
    inputTaskId = CreateTask(DebugTask_HandleMainMenuInput, 3);
    gTasks[inputTaskId].data[0] = menuTaskId;
    gTasks[inputTaskId].data[1] = windowId;
}

static void Debug_DestroyMainMenu(u8 taskId)
{
    DestroyListMenuTask(gTasks[taskId].data[0], NULL, NULL);
    ClearStdWindowAndFrame(gTasks[taskId].data[1], TRUE);
    RemoveWindow(gTasks[taskId].data[1]);
    DestroyTask(taskId);
    EnableBothScriptContexts();
}

static void DebugTask_HandleMainMenuInput(u8 taskId)
{
    void (*func)(u8);
    u32 input = ListMenu_ProcessInput(gTasks[taskId].data[0]);

    if (gMain.newKeys & A_BUTTON)
    {
        PlaySE(SE_SELECT);
        if ((func = sDebugMenuActions[input]) != NULL)
            func(taskId);
    }
    else if (gMain.newKeys & B_BUTTON)
    {
        PlaySE(SE_SELECT);
        Debug_DestroyMainMenu(taskId);
    }
}

static void DebugAction_ChainCount(u8 taskId)
{
  Debug_DestroyMainMenu(taskId);
  ScriptContext1_SetupScript(EventScript_BufferChainCount);
}

static void DebugAction_SetWildBattle(u8 taskId)
{
  Debug_DestroyMainMenu(taskId);
  ScriptContext1_SetupScript(EventScript_SetWildBattle);
}

static void DebugAction_DoWildBattle(u8 taskId)
{
  u16 species = SpeciesToNationalPokedexNum(VarGet(VAR_DEBUG_USE));
  u8 level = 1;

  //记录连锁
  if (VarGet(VAR_CHAIN_SPECIES) == species)
  {
    VarSet(VAR_CHAIN_COUNT, (VarGet(VAR_CHAIN_COUNT)+1));
  }
  else
  {
    VarSet(VAR_CHAIN_COUNT, 0);
  }
  VarSet(VAR_CHAIN_SPECIES, species);

	CreateWildMon(species, level);
  BattleSetup_StartScriptedWildBattle();
}

static void DebugAction_ShinyFlag(u8 taskId)
{
	if (FlagGet(SHINY_CREATION_FLAG) == TRUE)
		FlagClear(SHINY_CREATION_FLAG);
	else
		FlagSet(SHINY_CREATION_FLAG);
}

static void DebugAction_HiddenAbilityFlag(u8 taskId)
{
	if (FlagGet(HIDDEN_ABILITY_FLAG) == TRUE)
		FlagClear(HIDDEN_ABILITY_FLAG);
	else
		FlagSet(HIDDEN_ABILITY_FLAG);
}

static void DebugAction_Cancel(u8 taskId)
{
    Debug_DestroyMainMenu(taskId);
}

#endif
