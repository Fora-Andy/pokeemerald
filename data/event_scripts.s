#include "constants/global.h"
#include "constants/battle_frontier.h"
#include "constants/battle_setup.h"
#include "constants/contest.h"
#include "constants/easy_chat.h"
#include "constants/event_objects.h"
#include "constants/event_object_movement_constants.h"
#include "constants/field_effects.h"
#include "constants/flags.h"
#include "constants/decorations.h"
#include "constants/items.h"
#include "constants/heal_locations.h"
#include "constants/layouts.h"
#include "constants/map_scripts.h"
#include "constants/maps.h"
#include "constants/moves.h"
#include "constants/songs.h"
#include "constants/species.h"
#include "constants/trainers.h"
#include "constants/vars.h"
#include "constants/weather.h"
#include "constants/trainer_hill.h"
#include "constants/lilycove_lady.h"
#include "constants/battle.h"
#include "constants/metatile_labels.h"
	.include "asm/macros.inc"
	.include "asm/macros/event.inc"
	.include "constants/constants.inc"

	.section script_data, "aw", %progbits

@ 81DB67C
	.include "data/script_cmd_table.inc"

gSpecialVars:: @ 81DBA0C
	.4byte gSpecialVar_0x8000
	.4byte gSpecialVar_0x8001
	.4byte gSpecialVar_0x8002
	.4byte gSpecialVar_0x8003
	.4byte gSpecialVar_0x8004
	.4byte gSpecialVar_0x8005
	.4byte gSpecialVar_0x8006
	.4byte gSpecialVar_0x8007
	.4byte gSpecialVar_0x8008
	.4byte gSpecialVar_0x8009
	.4byte gSpecialVar_0x800A
	.4byte gSpecialVar_0x800B
	.4byte gSpecialVar_Facing
	.4byte gSpecialVar_Result
	.4byte gSpecialVar_ItemId
	.4byte gSpecialVar_LastTalked
	.4byte gSpecialVar_ContestRank
	.4byte gSpecialVar_ContestCategory
	.4byte gSpecialVar_MonBoxId
	.4byte gSpecialVar_MonBoxPos
	.4byte gSpecialVar_Unused_0x8014
	.4byte gTrainerBattleOpponent_A

	.include "data/specials.inc"

gStdScripts:: @ 81DC2A0
	.4byte Std_ObtainItem
	.4byte Std_FindItem
	.4byte Std_MsgboxNPC
	.4byte Std_MsgboxSign
	.4byte Std_MsgboxDefault
	.4byte Std_MsgboxYesNo
	.4byte Std_MsgboxAutoclose
	.4byte Std_ObtainDecoration
	.4byte Std_RegisteredInMatchCall
	.4byte Std_9
	.4byte Std_10
gStdScripts_End:: @ 81DC2CC

	.include "data/maps/PetalburgCity/scripts.inc"
	.include "data/maps/SlateportCity/scripts.inc"
	.include "data/maps/MauvilleCity/scripts.inc"
	.include "data/maps/RustboroCity/scripts.inc"
	.include "data/maps/FortreeCity/scripts.inc"
	.include "data/maps/LilycoveCity/scripts.inc"
	.include "data/maps/MossdeepCity/scripts.inc"
	.include "data/maps/SootopolisCity/scripts.inc"
	.include "data/maps/EverGrandeCity/scripts.inc"
	.include "data/maps/LittlerootTown/scripts.inc"
	.include "data/maps/OldaleTown/scripts.inc"
	.include "data/maps/DewfordTown/scripts.inc"
	.include "data/maps/LavaridgeTown/scripts.inc"
	.include "data/maps/FallarborTown/scripts.inc"
	.include "data/maps/VerdanturfTown/scripts.inc"
	.include "data/maps/PacifidlogTown/scripts.inc"
	.include "data/maps/Route101/scripts.inc"
	.include "data/maps/Route102/scripts.inc"
	.include "data/maps/Route103/scripts.inc"
	.include "data/maps/Route104/scripts.inc"
	.include "data/maps/Route105/scripts.inc"
	.include "data/maps/Route106/scripts.inc"
	.include "data/maps/Route107/scripts.inc"
	.include "data/maps/Route108/scripts.inc"
	.include "data/maps/Route109/scripts.inc"
	.include "data/maps/Route110/scripts.inc"
	.include "data/maps/Route111/scripts.inc"
	.include "data/maps/Route112/scripts.inc"
	.include "data/maps/Route113/scripts.inc"
	.include "data/maps/Route114/scripts.inc"
	.include "data/maps/Route115/scripts.inc"
	.include "data/maps/Route116/scripts.inc"
	.include "data/maps/Route117/scripts.inc"
	.include "data/maps/Route118/scripts.inc"
	.include "data/maps/Route119/scripts.inc"
	.include "data/maps/Route120/scripts.inc"
	.include "data/maps/Route121/scripts.inc"
	.include "data/maps/Route122/scripts.inc"
	.include "data/maps/Route123/scripts.inc"
	.include "data/maps/Route124/scripts.inc"
	.include "data/maps/Route125/scripts.inc"
	.include "data/maps/Route126/scripts.inc"
	.include "data/maps/Route127/scripts.inc"
	.include "data/maps/Route128/scripts.inc"
	.include "data/maps/Route129/scripts.inc"
	.include "data/maps/Route130/scripts.inc"
	.include "data/maps/Route131/scripts.inc"
	.include "data/maps/Route132/scripts.inc"
	.include "data/maps/Route133/scripts.inc"
	.include "data/maps/Route134/scripts.inc"
	.include "data/maps/Underwater1/scripts.inc"
	.include "data/maps/Underwater2/scripts.inc"
	.include "data/maps/Underwater3/scripts.inc"
	.include "data/maps/Underwater4/scripts.inc"
	.include "data/maps/Underwater5/scripts.inc"
	.include "data/maps/Underwater6/scripts.inc"
	.include "data/maps/Underwater7/scripts.inc"
	.include "data/maps/LittlerootTown_BrendansHouse_1F/scripts.inc"
	.include "data/maps/LittlerootTown_BrendansHouse_2F/scripts.inc"
	.include "data/maps/LittlerootTown_MaysHouse_1F/scripts.inc"
	.include "data/maps/LittlerootTown_MaysHouse_2F/scripts.inc"
	.include "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.inc"
	.include "data/maps/OldaleTown_House1/scripts.inc"
	.include "data/maps/OldaleTown_House2/scripts.inc"
	.include "data/maps/OldaleTown_PokemonCenter_1F/scripts.inc"
	.include "data/maps/OldaleTown_PokemonCenter_2F/scripts.inc"
	.include "data/maps/OldaleTown_Mart/scripts.inc"
	.include "data/maps/DewfordTown_House1/scripts.inc"
	.include "data/maps/DewfordTown_PokemonCenter_1F/scripts.inc"
	.include "data/maps/DewfordTown_PokemonCenter_2F/scripts.inc"
	.include "data/maps/DewfordTown_Gym/scripts.inc"
	.include "data/maps/DewfordTown_Hall/scripts.inc"
	.include "data/maps/DewfordTown_House2/scripts.inc"
	.include "data/maps/LavaridgeTown_HerbShop/scripts.inc"
	.include "data/maps/LavaridgeTown_Gym_1F/scripts.inc"
	.include "data/maps/LavaridgeTown_Gym_B1F/scripts.inc"
	.include "data/maps/LavaridgeTown_House/scripts.inc"
	.include "data/maps/LavaridgeTown_Mart/scripts.inc"
	.include "data/maps/LavaridgeTown_PokemonCenter_1F/scripts.inc"
	.include "data/maps/LavaridgeTown_PokemonCenter_2F/scripts.inc"
	.include "data/maps/FallarborTown_Mart/scripts.inc"
	.include "data/maps/FallarborTown_BattleTentLobby/scripts.inc"
	.include "data/maps/FallarborTown_BattleTentCorridor/scripts.inc"
	.include "data/maps/FallarborTown_BattleTentBattleRoom/scripts.inc"
	.include "data/maps/FallarborTown_PokemonCenter_1F/scripts.inc"
	.include "data/maps/FallarborTown_PokemonCenter_2F/scripts.inc"
	.include "data/maps/FallarborTown_House1/scripts.inc"
	.include "data/maps/FallarborTown_House2/scripts.inc"
	.include "data/maps/VerdanturfTown_BattleTentLobby/scripts.inc"
	.include "data/maps/VerdanturfTown_BattleTentCorridor/scripts.inc"
	.include "data/maps/VerdanturfTown_BattleTentBattleRoom/scripts.inc"
	.include "data/maps/VerdanturfTown_Mart/scripts.inc"
	.include "data/maps/VerdanturfTown_PokemonCenter_1F/scripts.inc"
	.include "data/maps/VerdanturfTown_PokemonCenter_2F/scripts.inc"
	.include "data/maps/VerdanturfTown_WandasHouse/scripts.inc"
	.include "data/maps/VerdanturfTown_FriendshipRatersHouse/scripts.inc"
	.include "data/maps/VerdanturfTown_House/scripts.inc"
	.include "data/maps/PacifidlogTown_PokemonCenter_1F/scripts.inc"
	.include "data/maps/PacifidlogTown_PokemonCenter_2F/scripts.inc"
	.include "data/maps/PacifidlogTown_House1/scripts.inc"
	.include "data/maps/PacifidlogTown_House2/scripts.inc"
	.include "data/maps/PacifidlogTown_House3/scripts.inc"
	.include "data/maps/PacifidlogTown_House4/scripts.inc"
	.include "data/maps/PacifidlogTown_House5/scripts.inc"
	.include "data/maps/PetalburgCity_WallysHouse/scripts.inc"
	.include "data/maps/PetalburgCity_Gym/scripts.inc"
	.include "data/maps/PetalburgCity_House1/scripts.inc"
	.include "data/maps/PetalburgCity_House2/scripts.inc"
	.include "data/maps/PetalburgCity_PokemonCenter_1F/scripts.inc"
	.include "data/maps/PetalburgCity_PokemonCenter_2F/scripts.inc"
	.include "data/maps/PetalburgCity_Mart/scripts.inc"
	.include "data/maps/SlateportCity_SternsShipyard_1F/scripts.inc"
	.include "data/maps/SlateportCity_SternsShipyard_2F/scripts.inc"
	.include "data/maps/SlateportCity_BattleTentLobby/scripts.inc"
	.include "data/maps/SlateportCity_BattleTentCorridor/scripts.inc"
	.include "data/maps/SlateportCity_BattleTentBattleRoom/scripts.inc"
	.include "data/maps/SlateportCity_House1/scripts.inc"
	.include "data/maps/SlateportCity_PokemonFanClub/scripts.inc"
	.include "data/maps/SlateportCity_OceanicMuseum_1F/scripts.inc"
	.include "data/maps/SlateportCity_OceanicMuseum_2F/scripts.inc"
	.include "data/maps/SlateportCity_Harbor/scripts.inc"
	.include "data/maps/SlateportCity_House2/scripts.inc"
	.include "data/maps/SlateportCity_PokemonCenter_1F/scripts.inc"
	.include "data/maps/SlateportCity_PokemonCenter_2F/scripts.inc"
	.include "data/maps/SlateportCity_Mart/scripts.inc"
	.include "data/maps/MauvilleCity_Gym/scripts.inc"
	.include "data/maps/MauvilleCity_BikeShop/scripts.inc"
	.include "data/maps/MauvilleCity_House1/scripts.inc"
	.include "data/maps/MauvilleCity_GameCorner/scripts.inc"
	.include "data/maps/MauvilleCity_House2/scripts.inc"
	.include "data/maps/MauvilleCity_PokemonCenter_1F/scripts.inc"
	.include "data/maps/MauvilleCity_PokemonCenter_2F/scripts.inc"
	.include "data/maps/MauvilleCity_Mart/scripts.inc"
	.include "data/maps/RustboroCity_DevonCorp_1F/scripts.inc"
	.include "data/maps/RustboroCity_DevonCorp_2F/scripts.inc"
	.include "data/maps/RustboroCity_DevonCorp_3F/scripts.inc"
	.include "data/maps/RustboroCity_Gym/scripts.inc"
	.include "data/maps/RustboroCity_PokemonSchool/scripts.inc"
	.include "data/maps/RustboroCity_PokemonCenter_1F/scripts.inc"
	.include "data/maps/RustboroCity_PokemonCenter_2F/scripts.inc"
	.include "data/maps/RustboroCity_Mart/scripts.inc"
	.include "data/maps/RustboroCity_Flat1_1F/scripts.inc"
	.include "data/maps/RustboroCity_Flat1_2F/scripts.inc"
	.include "data/maps/RustboroCity_House1/scripts.inc"
	.include "data/maps/RustboroCity_CuttersHouse/scripts.inc"
	.include "data/maps/RustboroCity_House2/scripts.inc"
	.include "data/maps/RustboroCity_Flat2_1F/scripts.inc"
	.include "data/maps/RustboroCity_Flat2_2F/scripts.inc"
	.include "data/maps/RustboroCity_Flat2_3F/scripts.inc"
	.include "data/maps/RustboroCity_House3/scripts.inc"
	.include "data/maps/FortreeCity_House1/scripts.inc"
	.include "data/maps/FortreeCity_Gym/scripts.inc"
	.include "data/maps/FortreeCity_PokemonCenter_1F/scripts.inc"
	.include "data/maps/FortreeCity_PokemonCenter_2F/scripts.inc"
	.include "data/maps/FortreeCity_Mart/scripts.inc"
	.include "data/maps/FortreeCity_House2/scripts.inc"
	.include "data/maps/FortreeCity_House3/scripts.inc"
	.include "data/maps/FortreeCity_House4/scripts.inc"
	.include "data/maps/FortreeCity_House5/scripts.inc"
	.include "data/maps/FortreeCity_DecorationShop/scripts.inc"
	.include "data/maps/LilycoveCity_CoveLilyMotel_1F/scripts.inc"
	.include "data/maps/LilycoveCity_CoveLilyMotel_2F/scripts.inc"
	.include "data/maps/LilycoveCity_LilycoveMuseum_1F/scripts.inc"
	.include "data/maps/LilycoveCity_LilycoveMuseum_2F/scripts.inc"
	.include "data/maps/LilycoveCity_ContestLobby/scripts.inc"
	.include "data/maps/LilycoveCity_ContestHall/scripts.inc"
	.include "data/maps/LilycoveCity_PokemonCenter_1F/scripts.inc"
	.include "data/maps/LilycoveCity_PokemonCenter_2F/scripts.inc"
	.include "data/maps/LilycoveCity_UnusedMart/scripts.inc"
	.include "data/maps/LilycoveCity_PokemonTrainerFanClub/scripts.inc"
	.include "data/maps/LilycoveCity_Harbor/scripts.inc"
	.include "data/maps/LilycoveCity_MoveDeletersHouse/scripts.inc"
	.include "data/maps/LilycoveCity_House1/scripts.inc"
	.include "data/maps/LilycoveCity_House2/scripts.inc"
	.include "data/maps/LilycoveCity_House3/scripts.inc"
	.include "data/maps/LilycoveCity_House4/scripts.inc"
	.include "data/maps/LilycoveCity_DepartmentStore_1F/scripts.inc"
	.include "data/maps/LilycoveCity_DepartmentStore_2F/scripts.inc"
	.include "data/maps/LilycoveCity_DepartmentStore_3F/scripts.inc"
	.include "data/maps/LilycoveCity_DepartmentStore_4F/scripts.inc"
	.include "data/maps/LilycoveCity_DepartmentStore_5F/scripts.inc"
	.include "data/maps/LilycoveCity_DepartmentStoreRooftop/scripts.inc"
	.include "data/maps/LilycoveCity_DepartmentStoreElevator/scripts.inc"
	.include "data/maps/MossdeepCity_Gym/scripts.inc"
	.include "data/maps/MossdeepCity_House1/scripts.inc"
	.include "data/maps/MossdeepCity_House2/scripts.inc"
	.include "data/maps/MossdeepCity_PokemonCenter_1F/scripts.inc"
	.include "data/maps/MossdeepCity_PokemonCenter_2F/scripts.inc"
	.include "data/maps/MossdeepCity_Mart/scripts.inc"
	.include "data/maps/MossdeepCity_House3/scripts.inc"
	.include "data/maps/MossdeepCity_StevensHouse/scripts.inc"
	.include "data/maps/MossdeepCity_House4/scripts.inc"
	.include "data/maps/MossdeepCity_SpaceCenter_1F/scripts.inc"
	.include "data/maps/MossdeepCity_SpaceCenter_2F/scripts.inc"
	.include "data/maps/MossdeepCity_GameCorner_1F/scripts.inc"
	.include "data/maps/MossdeepCity_GameCorner_B1F/scripts.inc"
	.include "data/maps/SootopolisCity_Gym_1F/scripts.inc"
	.include "data/maps/SootopolisCity_Gym_B1F/scripts.inc"
	.include "data/maps/SootopolisCity_PokemonCenter_1F/scripts.inc"
	.include "data/maps/SootopolisCity_PokemonCenter_2F/scripts.inc"
	.include "data/maps/SootopolisCity_Mart/scripts.inc"
	.include "data/maps/SootopolisCity_House1/scripts.inc"
	.include "data/maps/SootopolisCity_House2/scripts.inc"
	.include "data/maps/SootopolisCity_House3/scripts.inc"
	.include "data/maps/SootopolisCity_House4/scripts.inc"
	.include "data/maps/SootopolisCity_House5/scripts.inc"
	.include "data/maps/SootopolisCity_House6/scripts.inc"
	.include "data/maps/SootopolisCity_House7/scripts.inc"
	.include "data/maps/SootopolisCity_LotadAndSeedotHouse/scripts.inc"
	.include "data/maps/SootopolisCity_MysteryEventsHouse_1F/scripts.inc"
	.include "data/maps/SootopolisCity_MysteryEventsHouse_B1F/scripts.inc"
	.include "data/maps/EverGrandeCity_SidneysRoom/scripts.inc"
	.include "data/maps/EverGrandeCity_PhoebesRoom/scripts.inc"
	.include "data/maps/EverGrandeCity_GlaciasRoom/scripts.inc"
	.include "data/maps/EverGrandeCity_DrakesRoom/scripts.inc"
	.include "data/maps/EverGrandeCity_ChampionsRoom/scripts.inc"
	.include "data/maps/EverGrandeCity_Hall1/scripts.inc"
	.include "data/maps/EverGrandeCity_Hall2/scripts.inc"
	.include "data/maps/EverGrandeCity_Hall3/scripts.inc"
	.include "data/maps/EverGrandeCity_Hall4/scripts.inc"
	.include "data/maps/EverGrandeCity_Hall5/scripts.inc"
	.include "data/maps/EverGrandeCity_PokemonLeague_1F/scripts.inc"
	.include "data/maps/EverGrandeCity_HallOfFame/scripts.inc"
	.include "data/maps/EverGrandeCity_PokemonCenter_1F/scripts.inc"
	.include "data/maps/EverGrandeCity_PokemonCenter_2F/scripts.inc"
	.include "data/maps/EverGrandeCity_PokemonLeague_2F/scripts.inc"
	.include "data/maps/Route104_MrBrineysHouse/scripts.inc"
	.include "data/maps/Route104_PrettyPetalFlowerShop/scripts.inc"
	.include "data/maps/Route111_WinstrateFamilysHouse/scripts.inc"
	.include "data/maps/Route111_OldLadysRestStop/scripts.inc"
	.include "data/maps/Route112_CableCarStation/scripts.inc"
	.include "data/maps/MtChimney_CableCarStation/scripts.inc"
	.include "data/maps/Route114_FossilManiacsHouse/scripts.inc"
	.include "data/maps/Route114_FossilManiacsTunnel/scripts.inc"
	.include "data/maps/Route114_LanettesHouse/scripts.inc"
	.include "data/maps/Route116_TunnelersRestHouse/scripts.inc"
	.include "data/maps/Route117_PokemonDayCare/scripts.inc"
	.include "data/maps/Route121_SafariZoneEntrance/scripts.inc"
	.include "data/maps/MeteorFalls_1F_1R/scripts.inc"
	.include "data/maps/MeteorFalls_1F_2R/scripts.inc"
	.include "data/maps/MeteorFalls_B1F_1R/scripts.inc"
	.include "data/maps/MeteorFalls_B1F_2R/scripts.inc"
	.include "data/maps/RusturfTunnel/scripts.inc"
	.include "data/maps/Underwater_SootopolisCity/scripts.inc"
	.include "data/maps/DesertRuins/scripts.inc"
	.include "data/maps/GraniteCave_1F/scripts.inc"
	.include "data/maps/GraniteCave_B1F/scripts.inc"
	.include "data/maps/GraniteCave_B2F/scripts.inc"
	.include "data/maps/GraniteCave_StevensRoom/scripts.inc"
	.include "data/maps/PetalburgWoods/scripts.inc"
	.include "data/maps/MtChimney/scripts.inc"
	.include "data/maps/JaggedPass/scripts.inc"
	.include "data/maps/FieryPath/scripts.inc"
	.include "data/maps/MtPyre_1F/scripts.inc"
	.include "data/maps/MtPyre_2F/scripts.inc"
	.include "data/maps/MtPyre_3F/scripts.inc"
	.include "data/maps/MtPyre_4F/scripts.inc"
	.include "data/maps/MtPyre_5F/scripts.inc"
	.include "data/maps/MtPyre_6F/scripts.inc"
	.include "data/maps/MtPyre_Exterior/scripts.inc"
	.include "data/maps/MtPyre_Summit/scripts.inc"
	.include "data/maps/AquaHideout_1F/scripts.inc"
	.include "data/maps/AquaHideout_B1F/scripts.inc"
	.include "data/maps/AquaHideout_B2F/scripts.inc"
	.include "data/maps/Underwater_SeafloorCavern/scripts.inc"
	.include "data/maps/SeafloorCavern_Entrance/scripts.inc"
	.include "data/maps/SeafloorCavern_Room1/scripts.inc"
	.include "data/maps/SeafloorCavern_Room2/scripts.inc"
	.include "data/maps/SeafloorCavern_Room3/scripts.inc"
	.include "data/maps/SeafloorCavern_Room4/scripts.inc"
	.include "data/maps/SeafloorCavern_Room5/scripts.inc"
	.include "data/maps/SeafloorCavern_Room6/scripts.inc"
	.include "data/maps/SeafloorCavern_Room7/scripts.inc"
	.include "data/maps/SeafloorCavern_Room8/scripts.inc"
	.include "data/maps/SeafloorCavern_Room9/scripts.inc"
	.include "data/maps/CaveOfOrigin_Entrance/scripts.inc"
	.include "data/maps/CaveOfOrigin_1F/scripts.inc"
	.include "data/maps/CaveOfOrigin_UnusedRubySapphireMap1/scripts.inc"
	.include "data/maps/CaveOfOrigin_UnusedRubySapphireMap2/scripts.inc"
	.include "data/maps/CaveOfOrigin_UnusedRubySapphireMap3/scripts.inc"
	.include "data/maps/CaveOfOrigin_B1F/scripts.inc"
	.include "data/maps/VictoryRoad_1F/scripts.inc"
	.include "data/maps/VictoryRoad_B1F/scripts.inc"
	.include "data/maps/VictoryRoad_B2F/scripts.inc"
	.include "data/maps/ShoalCave_LowTideEntranceRoom/scripts.inc"
	.include "data/maps/ShoalCave_LowTideInnerRoom/scripts.inc"
	.include "data/maps/ShoalCave_LowTideStairsRoom/scripts.inc"
	.include "data/maps/ShoalCave_LowTideLowerRoom/scripts.inc"
	.include "data/maps/ShoalCave_HighTideEntranceRoom/scripts.inc"
	.include "data/maps/ShoalCave_HighTideInnerRoom/scripts.inc"
	.include "data/maps/NewMauville_Entrance/scripts.inc"
	.include "data/maps/NewMauville_Inside/scripts.inc"
	.include "data/maps/AbandonedShip_Deck/scripts.inc"
	.include "data/maps/AbandonedShip_Corridors_1F/scripts.inc"
	.include "data/maps/AbandonedShip_Rooms_1F/scripts.inc"
	.include "data/maps/AbandonedShip_Corridors_B1F/scripts.inc"
	.include "data/maps/AbandonedShip_Rooms_B1F/scripts.inc"
	.include "data/maps/AbandonedShip_Rooms2_B1F/scripts.inc"
	.include "data/maps/AbandonedShip_Underwater1/scripts.inc"
	.include "data/maps/AbandonedShip_Room_B1F/scripts.inc"
	.include "data/maps/AbandonedShip_Rooms2_1F/scripts.inc"
	.include "data/maps/AbandonedShip_CaptainsOffice/scripts.inc"
	.include "data/maps/AbandonedShip_Underwater2/scripts.inc"
	.include "data/maps/AbandonedShip_HiddenFloorCorridors/scripts.inc"
	.include "data/maps/AbandonedShip_HiddenFloorRooms/scripts.inc"
	.include "data/maps/IslandCave/scripts.inc"
	.include "data/maps/AncientTomb/scripts.inc"
	.include "data/maps/Underwater_Route134/scripts.inc"
	.include "data/maps/Underwater_SealedChamber/scripts.inc"
	.include "data/maps/SealedChamber_OuterRoom/scripts.inc"
	.include "data/maps/SealedChamber_InnerRoom/scripts.inc"
	.include "data/maps/ScorchedSlab/scripts.inc"
	.include "data/maps/AquaHideout_UnusedRubyMap1/scripts.inc"
	.include "data/maps/AquaHideout_UnusedRubyMap2/scripts.inc"
	.include "data/maps/AquaHideout_UnusedRubyMap3/scripts.inc"
	.include "data/maps/SkyPillar_Entrance/scripts.inc"
	.include "data/maps/SkyPillar_Outside/scripts.inc"
	.include "data/maps/SkyPillar_1F/scripts.inc"
	.include "data/maps/SkyPillar_2F/scripts.inc"
	.include "data/maps/SkyPillar_3F/scripts.inc"
	.include "data/maps/SkyPillar_4F/scripts.inc"
	.include "data/maps/ShoalCave_LowTideIceRoom/scripts.inc"
	.include "data/maps/SkyPillar_5F/scripts.inc"
	.include "data/maps/SkyPillar_Top/scripts.inc"
	.include "data/maps/MagmaHideout_1F/scripts.inc"
	.include "data/maps/MagmaHideout_2F_1R/scripts.inc"
	.include "data/maps/MagmaHideout_2F_2R/scripts.inc"
	.include "data/maps/MagmaHideout_3F_1R/scripts.inc"
	.include "data/maps/MagmaHideout_3F_2R/scripts.inc"
	.include "data/maps/MagmaHideout_4F/scripts.inc"
	.include "data/maps/MagmaHideout_3F_3R/scripts.inc"
	.include "data/maps/MagmaHideout_2F_3R/scripts.inc"
	.include "data/maps/MirageTower_1F/scripts.inc"
	.include "data/maps/MirageTower_2F/scripts.inc"
	.include "data/maps/MirageTower_3F/scripts.inc"
	.include "data/maps/MirageTower_4F/scripts.inc"
	.include "data/maps/DesertUnderpass/scripts.inc"
	.include "data/maps/ArtisanCave_B1F/scripts.inc"
	.include "data/maps/ArtisanCave_1F/scripts.inc"
	.include "data/maps/Underwater_MarineCave/scripts.inc"
	.include "data/maps/MarineCave_Entrance/scripts.inc"
	.include "data/maps/MarineCave_End/scripts.inc"
	.include "data/maps/TerraCave_Entrance/scripts.inc"
	.include "data/maps/TerraCave_End/scripts.inc"
	.include "data/maps/AlteringCave/scripts.inc"
	.include "data/maps/MeteorFalls_StevensCave/scripts.inc"
	.include "data/maps/SecretBase_BlueCave1/scripts.inc"
	.include "data/maps/SecretBase_BlueCave2/scripts.inc"
	.include "data/maps/SecretBase_BlueCave3/scripts.inc"
	.include "data/maps/SecretBase_BlueCave4/scripts.inc"
	.include "data/maps/SecretBase_BrownCave1/scripts.inc"
	.include "data/maps/SecretBase_BrownCave2/scripts.inc"
	.include "data/maps/SecretBase_BrownCave3/scripts.inc"
	.include "data/maps/SecretBase_BrownCave4/scripts.inc"
	.include "data/maps/SecretBase_RedCave1/scripts.inc"
	.include "data/maps/SecretBase_RedCave2/scripts.inc"
	.include "data/maps/SecretBase_RedCave3/scripts.inc"
	.include "data/maps/SecretBase_RedCave4/scripts.inc"
	.include "data/maps/SecretBase_Shrub1/scripts.inc"
	.include "data/maps/SecretBase_Shrub2/scripts.inc"
	.include "data/maps/SecretBase_Shrub3/scripts.inc"
	.include "data/maps/SecretBase_Shrub4/scripts.inc"
	.include "data/maps/SecretBase_Tree1/scripts.inc"
	.include "data/maps/SecretBase_Tree2/scripts.inc"
	.include "data/maps/SecretBase_Tree3/scripts.inc"
	.include "data/maps/SecretBase_Tree4/scripts.inc"
	.include "data/maps/SecretBase_YellowCave1/scripts.inc"
	.include "data/maps/SecretBase_YellowCave2/scripts.inc"
	.include "data/maps/SecretBase_YellowCave3/scripts.inc"
	.include "data/maps/SecretBase_YellowCave4/scripts.inc"

EventScript_SecretBasePC:: @ 823B4BB
	lockall
	playse SE_PC_LOGIN
	message Text_SecretBaseBootUpPC
	dofieldeffect FLDEFF_PCTURN_ON
	waitstate
	waitmessage
	waitbuttonpress
	playse SE_SELECT
	goto EventScript_SecretBasePCShowMainMenu
	end

EventScript_SecretBasePCShowMainMenu:: @ 823B4D3
	message Text_SecretBasePCStartMenu
	waitmessage
	goto_if_set FLAG_SECRET_BASE_REGISTRY_ENABLED, EventScript_SecretBasePCMainMenuChoice
	goto EventScript_23B531
	end

gUnknown_0823B4E8:: @ 823B4E8 ;EventScript_SecretBasePCCancel?
	lockall
	goto EventScript_SecretBasePCShowMainMenu
	end

EventScript_SecretBasePCMainMenuChoice:: @ 823B4EF
	multichoice 0, 0, 6, 0
	switch VAR_RESULT
	case 0, EventScript_23B581
	case 1, EventScript_23B568
	case 2, EventScript_23B585
	case 3, EventScript_23B66E
	case 127, EventScript_23B66E
	end

EventScript_23B531:: @ 823B531
	multichoice 0, 0, 5, 0
	switch VAR_RESULT
	case 0, EventScript_23B581
	case 1, EventScript_23B568
	case 2, EventScript_23B66E
	case 127, EventScript_23B66E
	end

EventScript_23B568:: @ 823B568
	msgbox Text_2766AA, MSGBOX_YESNO
	compare VAR_RESULT, 0
	goto_if_eq EventScript_SecretBasePCShowMainMenu
	closemessage
	special MoveOutOfSecretBase
	releaseall
	end

EventScript_23B581:: @ 823B581
	special ShowSecretBaseDecorationMenu
	end

EventScript_23B585:: @ 823B585
	special ShowSecretBaseRegistryMenu
	end

EventScript_RecordMixingSecretBasePC:: @ 823B589
	lockall
	message Text_SecretBaseBootUpPC
	playse SE_PC_LOGIN
	dofieldeffect FLDEFF_PCTURN_ON
	waitstate
	waitmessage
	waitbuttonpress
	playse SE_SELECT
	goto EventScript_23B5A1
	end

EventScript_23B5A1:: @ 823B5A1
	message Text_SecretBasePCStartMenu
	waitmessage
	multichoice 0, 0, 7, 0
	switch VAR_RESULT
	case 0, EventScript_23B5F0
	case 1, EventScript_23B585
	case 2, EventScript_23B660
	case 3, EventScript_23B66E
	case 127, EventScript_23B66E
	end

gUnknown_0823B5E9:: @ 823B5E9
	lockall
	goto EventScript_23B5A1
	end

EventScript_23B5F0:: @ 823B5F0
	special GetCurSecretBaseRegistrationValidity
	compare VAR_RESULT, 1
	goto_if_eq EventScript_23B62F
	compare VAR_RESULT, 2
	goto_if_eq EventScript_CantRegisterTooManyBases
	special CopyCurSecretBaseOwnerName_StrVar1
	msgbox Text_WantToRegisterSecretBase, MSGBOX_YESNO
	compare VAR_RESULT, 0
	goto_if_eq EventScript_23B5A1
	msgbox Text_2767D1, MSGBOX_SIGN
	special ToggleCurSecretBaseRegistry
	special DoSecretBasePCTurnOffEffect
	releaseall
	end

EventScript_23B62F:: @ 823B62F
	msgbox Text_276731, MSGBOX_YESNO
	compare VAR_RESULT, 0
	goto_if_eq EventScript_23B5A1
	msgbox Text_2767E9, MSGBOX_SIGN
	special ToggleCurSecretBaseRegistry
	special DoSecretBasePCTurnOffEffect
	releaseall
	end

EventScript_CantRegisterTooManyBases:: @ 823B652
	msgbox Text_TooManyBasesDeleteSome, MSGBOX_SIGN
	special DoSecretBasePCTurnOffEffect
	closemessage
	releaseall
	end

EventScript_23B660:: @ 823B660
	msgbox Text_276835, MSGBOX_DEFAULT
	goto EventScript_23B5A1
	end

EventScript_23B66E:: @ 823B66E
	special DoSecretBasePCTurnOffEffect
	closemessage
	releaseall
	end

EventScript_23B674:: @ 823B674
	special SetSecretBaseSecretsTvFlags_Poster
	end

EventScript_23B678:: @ 823B678
	special SetSecretBaseSecretsTvFlags_MiscFurnature
	end

EventScript_23B67C:: @ 823B67C
	special SetSecretBaseSecretsTvFlags_LargeDecorationSpot
	end

EventScript_23B680:: @ 823B680
	special SetSecretBaseSecretsTvFlags_SmallDecorationSpot
	end

EventScript_SecretBaseSandOrnament:: @ 823B684
	special SetSecretBaseSecretsTvFlags_SandOrnament
	dofieldeffect FLDEFF_SAND_PILLAR
	waitstate
	end

EventScript_SecretBaseShieldOrToyTV:: @ 823B68C
	special GetShieldToyTVDecorationInfo
	compare VAR_RESULT, 0
	goto_if_eq EventScript_23B6BC
	compare VAR_RESULT, 1
	goto_if_eq EventScript_23B6C5
	compare VAR_RESULT, 2
	goto_if_eq EventScript_23B6CE
	compare VAR_RESULT, 3
	goto_if_eq EventScript_23B6D7
	end

EventScript_23B6BC:: @ 823B6BC
	msgbox Text_27692B, MSGBOX_SIGN
	end

EventScript_23B6C5:: @ 823B6C5
	msgbox Text_276974, MSGBOX_SIGN
	end

EventScript_23B6CE:: @ 823B6CE
	msgbox Text_2769B8, MSGBOX_SIGN
	end

EventScript_23B6D7:: @ 823B6D7
	msgbox Text_2769FF, MSGBOX_SIGN
	end

gText_23B6E0:: @ 823B6E0
	.string "墙上有个凹洞。$"

gText_23B704:: @ 823B704
	.string "墙上有个凹洞。\p"
	.string "要使用秘密之力吗?$"

gText_23B73E:: @ 823B73E
	.string "发现了一个小洞穴!$"

SecretBase_RedCave1_Text_23B759: @ 823B759
	.string "想在这里建造秘密基地吗?$"

	.include "data/maps/SingleBattleColosseum/scripts.inc"
	.include "data/maps/TradeCenter/scripts.inc"
	.include "data/maps/RecordCorner/scripts.inc"
	.include "data/maps/DoubleBattleColosseum/scripts.inc"
	.include "data/maps/LinkContestRoom1/scripts.inc"
	.include "data/maps/UnknownLinkContestRoom_25_29/scripts.inc"
	.include "data/maps/UnknownLinkContestRoom_25_30/scripts.inc"
	.include "data/maps/UnknownLinkContestRoom_25_31/scripts.inc"
	.include "data/maps/UnknownLinkContestRoom_25_32/scripts.inc"
	.include "data/maps/UnknownLinkContestRoom_25_33/scripts.inc"
	.include "data/maps/UnknownLinkContestRoom_25_34/scripts.inc"
	.include "data/maps/LinkContestRoom2/scripts.inc"
	.include "data/maps/LinkContestRoom3/scripts.inc"
	.include "data/maps/LinkContestRoom4/scripts.inc"
	.include "data/maps/LinkContestRoom5/scripts.inc"
	.include "data/maps/LinkContestRoom6/scripts.inc"
	.include "data/maps/InsideOfTruck/scripts.inc"
	.include "data/maps/SSTidalCorridor/scripts.inc"
	.include "data/maps/SSTidalLowerDeck/scripts.inc"
	.include "data/maps/SSTidalRooms/scripts.inc"
	.include "data/maps/BattlePyramidSquare01/scripts.inc"
	.include "data/maps/BattlePyramidSquare02/scripts.inc"
	.include "data/maps/BattlePyramidSquare03/scripts.inc"
	.include "data/maps/BattlePyramidSquare04/scripts.inc"
	.include "data/maps/BattlePyramidSquare05/scripts.inc"
	.include "data/maps/BattlePyramidSquare06/scripts.inc"
	.include "data/maps/BattlePyramidSquare07/scripts.inc"
	.include "data/maps/BattlePyramidSquare08/scripts.inc"
	.include "data/maps/BattlePyramidSquare09/scripts.inc"
	.include "data/maps/BattlePyramidSquare10/scripts.inc"
	.include "data/maps/BattlePyramidSquare11/scripts.inc"
	.include "data/maps/BattlePyramidSquare12/scripts.inc"
	.include "data/maps/BattlePyramidSquare13/scripts.inc"
	.include "data/maps/BattlePyramidSquare14/scripts.inc"
	.include "data/maps/BattlePyramidSquare15/scripts.inc"
	.include "data/maps/BattlePyramidSquare16/scripts.inc"
	.include "data/maps/UnionRoom/scripts.inc"
	.include "data/maps/SafariZone_Northwest/scripts.inc"
	.include "data/maps/SafariZone_North/scripts.inc"
	.include "data/maps/SafariZone_Southwest/scripts.inc"
	.include "data/maps/SafariZone_South/scripts.inc"
	.include "data/maps/BattleFrontier_OutsideWest/scripts.inc"
	.include "data/maps/BattleFrontier_BattleTowerLobby/scripts.inc"
	.include "data/maps/BattleFrontier_BattleTowerElevator/scripts.inc"
	.include "data/maps/BattleFrontier_BattleTowerCorridor/scripts.inc"
	.include "data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.inc"
	.include "data/maps/SouthernIsland_Exterior/scripts.inc"
	.include "data/maps/SouthernIsland_Interior/scripts.inc"
	.include "data/maps/SafariZone_RestHouse/scripts.inc"
	.include "data/maps/SafariZone_Northeast/scripts.inc"
	.include "data/maps/SafariZone_Southeast/scripts.inc"
	.include "data/maps/BattleFrontier_OutsideEast/scripts.inc"
	.include "data/maps/BattleFrontier_BattleTowerMultiBattleRoom/scripts.inc"
	.include "data/maps/BattleFrontier_BattleTowerCorridor2/scripts.inc"
	.include "data/maps/BattleFrontier_BattleTowerBattleRoom2/scripts.inc"
	.include "data/maps/BattleFrontier_BattleDomeLobby/scripts.inc"
	.include "data/maps/BattleFrontier_BattleDomeCorridor/scripts.inc"
	.include "data/maps/BattleFrontier_BattleDomePreBattleRoom/scripts.inc"
	.include "data/maps/BattleFrontier_BattleDomeBattleRoom/scripts.inc"
	.include "data/maps/BattleFrontier_BattlePalaceLobby/scripts.inc"
	.include "data/maps/BattleFrontier_BattlePalaceCorridor/scripts.inc"
	.include "data/maps/BattleFrontier_BattlePalaceBattleRoom/scripts.inc"
	.include "data/maps/BattleFrontier_BattlePyramidLobby/scripts.inc"
	.include "data/maps/BattleFrontier_BattlePyramidEmptySquare/scripts.inc"
	.include "data/maps/BattleFrontier_BattlePyramidTop/scripts.inc"
	.include "data/maps/BattleFrontier_BattleArenaLobby/scripts.inc"
	.include "data/maps/BattleFrontier_BattleArenaCorridor/scripts.inc"
	.include "data/maps/BattleFrontier_BattleArenaBattleRoom/scripts.inc"
	.include "data/maps/BattleFrontier_BattleFactoryLobby/scripts.inc"
	.include "data/maps/BattleFrontier_BattleFactoryPreBattleRoom/scripts.inc"
	.include "data/maps/BattleFrontier_BattleFactoryBattleRoom/scripts.inc"
	.include "data/maps/BattleFrontier_BattlePikeLobby/scripts.inc"
	.include "data/maps/BattleFrontier_BattlePikeCorridor/scripts.inc"
	.include "data/maps/BattleFrontier_BattlePikeThreePathRoom/scripts.inc"
	.include "data/maps/BattleFrontier_BattlePikeRandomRoom1/scripts.inc"
	.include "data/maps/BattleFrontier_BattlePikeRandomRoom2/scripts.inc"
	.include "data/maps/BattleFrontier_BattlePikeRandomRoom3/scripts.inc"
	.include "data/maps/BattleFrontier_RankingHall/scripts.inc"
	.include "data/maps/BattleFrontier_Lounge1/scripts.inc"
	.include "data/maps/BattleFrontier_BattlePointExchangeServiceCorner/scripts.inc"
	.include "data/maps/BattleFrontier_Lounge2/scripts.inc"
	.include "data/maps/BattleFrontier_Lounge3/scripts.inc"
	.include "data/maps/BattleFrontier_Lounge4/scripts.inc"
	.include "data/maps/BattleFrontier_ScottsHouse/scripts.inc"
	.include "data/maps/BattleFrontier_Lounge5/scripts.inc"
	.include "data/maps/BattleFrontier_Lounge6/scripts.inc"
	.include "data/maps/BattleFrontier_Lounge7/scripts.inc"
	.include "data/maps/BattleFrontier_ReceptionGate/scripts.inc"
	.include "data/maps/BattleFrontier_Lounge8/scripts.inc"
	.include "data/maps/BattleFrontier_Lounge9/scripts.inc"
	.include "data/maps/BattleFrontier_PokemonCenter_1F/scripts.inc"
	.include "data/maps/BattleFrontier_PokemonCenter_2F/scripts.inc"
	.include "data/maps/BattleFrontier_Mart/scripts.inc"
	.include "data/maps/FarawayIsland_Entrance/scripts.inc"
	.include "data/maps/FarawayIsland_Interior/scripts.inc"
	.include "data/maps/BirthIsland_Exterior/scripts.inc"
	.include "data/maps/BirthIsland_Harbor/scripts.inc"
	.include "data/maps/TrainerHill_Entrance/scripts.inc"
	.include "data/maps/TrainerHill_1F/scripts.inc"
	.include "data/maps/TrainerHill_2F/scripts.inc"
	.include "data/maps/TrainerHill_3F/scripts.inc"
	.include "data/maps/TrainerHill_4F/scripts.inc"
	.include "data/maps/TrainerHill_Roof/scripts.inc"
	.include "data/maps/NavelRock_Exterior/scripts.inc"
	.include "data/maps/NavelRock_Harbor/scripts.inc"
	.include "data/maps/NavelRock_Entrance/scripts.inc"
	.include "data/maps/NavelRock_B1F/scripts.inc"
	.include "data/maps/NavelRock_Fork/scripts.inc"
	.include "data/maps/NavelRock_Up1/scripts.inc"
	.include "data/maps/NavelRock_Up2/scripts.inc"
	.include "data/maps/NavelRock_Up3/scripts.inc"
	.include "data/maps/NavelRock_Up4/scripts.inc"
	.include "data/maps/NavelRock_Top/scripts.inc"
	.include "data/maps/NavelRock_Down01/scripts.inc"
	.include "data/maps/NavelRock_Down02/scripts.inc"
	.include "data/maps/NavelRock_Down03/scripts.inc"
	.include "data/maps/NavelRock_Down04/scripts.inc"
	.include "data/maps/NavelRock_Down05/scripts.inc"
	.include "data/maps/NavelRock_Down06/scripts.inc"
	.include "data/maps/NavelRock_Down07/scripts.inc"
	.include "data/maps/NavelRock_Down08/scripts.inc"
	.include "data/maps/NavelRock_Down09/scripts.inc"
	.include "data/maps/NavelRock_Down10/scripts.inc"
	.include "data/maps/NavelRock_Down11/scripts.inc"
	.include "data/maps/NavelRock_Bottom/scripts.inc"
	.include "data/maps/TrainerHill_Elevator/scripts.inc"
	.include "data/maps/Route104_Prototype/scripts.inc"
	.include "data/maps/Route104_PrototypePrettyPetalFlowerShop/scripts.inc"
	.include "data/maps/Route109_SeashoreHouse/scripts.inc"
	.include "data/maps/Route110_TrickHouseEntrance/scripts.inc"
	.include "data/maps/Route110_TrickHouseEnd/scripts.inc"
	.include "data/maps/Route110_TrickHouseCorridor/scripts.inc"
	.include "data/maps/Route110_TrickHousePuzzle1/scripts.inc"
	.include "data/maps/Route110_TrickHousePuzzle2/scripts.inc"
	.include "data/maps/Route110_TrickHousePuzzle3/scripts.inc"
	.include "data/maps/Route110_TrickHousePuzzle4/scripts.inc"
	.include "data/maps/Route110_TrickHousePuzzle5/scripts.inc"
	.include "data/maps/Route110_TrickHousePuzzle6/scripts.inc"
	.include "data/maps/Route110_TrickHousePuzzle7/scripts.inc"
	.include "data/maps/Route110_TrickHousePuzzle8/scripts.inc"
	.include "data/maps/Route110_SeasideCyclingRoadNorthEntrance/scripts.inc"
	.include "data/maps/Route110_SeasideCyclingRoadSouthEntrance/scripts.inc"
	.include "data/maps/Route113_GlassWorkshop/scripts.inc"
	.include "data/maps/Route123_BerryMastersHouse/scripts.inc"
	.include "data/maps/Route119_WeatherInstitute_1F/scripts.inc"
	.include "data/maps/Route119_WeatherInstitute_2F/scripts.inc"
	.include "data/maps/Route119_House/scripts.inc"
	.include "data/maps/Route124_DivingTreasureHuntersHouse/scripts.inc"

Std_MsgboxNPC: @ 8271315
	lock
	faceplayer
	message 0x0
	waitmessage
	waitbuttonpress
	release
	return

Std_MsgboxSign: @ 8271320
	lockall
	message 0x0
	waitmessage
	waitbuttonpress
	releaseall
	return

Std_MsgboxDefault: @ 827132A
	message 0x0
	waitmessage
	waitbuttonpress
	return

Std_MsgboxYesNo: @ 8271332
	message 0x0
	waitmessage
	yesnobox 20, 8
	return

Std_9: @ 827133C
	message 0x0
	playfanfare MUS_ME_POINTGET
	waitfanfare
	waitmessage
	return

Std_10: @ 8271347
	pokenavcall 0x0
	waitmessage
	return

EventScript_UnusedReturn: @ 827134E
	return

Common_EventScript_SaveGame:: @ 827134F
	special SaveGame
	waitstate
	return

EventScript_271354:: @ 8271354
	cmdD8
	cmdD9

	.include "data/scripts/trainer_battle.inc"

Std_MsgboxAutoclose:: @ 8271494
	message 0x0
	waitmessage
	waitbuttonpress
	release
	return

EventScript_ResetAllBerries:: @ 827149D
	setberrytree 2, ITEM_TO_BERRY(ITEM_ORAN_BERRY), 5
	setberrytree 1, ITEM_TO_BERRY(ITEM_PECHA_BERRY), 5
	setberrytree 11, ITEM_TO_BERRY(ITEM_ORAN_BERRY), 5
	setberrytree 13, ITEM_TO_BERRY(ITEM_PECHA_BERRY), 5
	setberrytree 4, ITEM_TO_BERRY(ITEM_ORAN_BERRY), 5
	setberrytree 76, ITEM_TO_BERRY(ITEM_CHERI_BERRY), 5
	setberrytree 8, ITEM_TO_BERRY(ITEM_CHERI_BERRY), 5
	setberrytree 10, ITEM_TO_BERRY(ITEM_LEPPA_BERRY), 5
	setberrytree 25, ITEM_TO_BERRY(ITEM_PINAP_BERRY), 5
	setberrytree 26, ITEM_TO_BERRY(ITEM_CHESTO_BERRY), 5
	setberrytree 66, ITEM_TO_BERRY(ITEM_CHESTO_BERRY), 5
	setberrytree 67, ITEM_TO_BERRY(ITEM_PINAP_BERRY), 5
	setberrytree 69, ITEM_TO_BERRY(ITEM_KELPSY_BERRY), 5
	setberrytree 70, ITEM_TO_BERRY(ITEM_KELPSY_BERRY), 5
	setberrytree 71, ITEM_TO_BERRY(ITEM_KELPSY_BERRY), 5
	setberrytree 55, ITEM_TO_BERRY(ITEM_BLUK_BERRY), 5
	setberrytree 56, ITEM_TO_BERRY(ITEM_BLUK_BERRY), 5
	setberrytree 5, ITEM_TO_BERRY(ITEM_CHERI_BERRY), 5
	setberrytree 6, ITEM_TO_BERRY(ITEM_LEPPA_BERRY), 5
	setberrytree 7, ITEM_TO_BERRY(ITEM_CHERI_BERRY), 5
	setberrytree 16, ITEM_TO_BERRY(ITEM_NANAB_BERRY), 5
	setberrytree 17, ITEM_TO_BERRY(ITEM_NANAB_BERRY), 5
	setberrytree 18, ITEM_TO_BERRY(ITEM_NANAB_BERRY), 5
	setberrytree 29, ITEM_TO_BERRY(ITEM_WEPEAR_BERRY), 5
	setberrytree 28, ITEM_TO_BERRY(ITEM_WEPEAR_BERRY), 5
	setberrytree 27, ITEM_TO_BERRY(ITEM_WEPEAR_BERRY), 5
	setberrytree 24, ITEM_TO_BERRY(ITEM_RAWST_BERRY), 5
	setberrytree 23, ITEM_TO_BERRY(ITEM_PECHA_BERRY), 5
	setberrytree 22, ITEM_TO_BERRY(ITEM_PECHA_BERRY), 5
	setberrytree 21, ITEM_TO_BERRY(ITEM_RAWST_BERRY), 5
	setberrytree 19, ITEM_TO_BERRY(ITEM_RAZZ_BERRY), 5
	setberrytree 20, ITEM_TO_BERRY(ITEM_RAZZ_BERRY), 5
	setberrytree 80, ITEM_TO_BERRY(ITEM_ORAN_BERRY), 5
	setberrytree 81, ITEM_TO_BERRY(ITEM_ORAN_BERRY), 5
	setberrytree 77, ITEM_TO_BERRY(ITEM_PERSIM_BERRY), 5
	setberrytree 78, ITEM_TO_BERRY(ITEM_PERSIM_BERRY), 5
	setberrytree 68, ITEM_TO_BERRY(ITEM_PERSIM_BERRY), 5
	setberrytree 31, ITEM_TO_BERRY(ITEM_SITRUS_BERRY), 5
	setberrytree 33, ITEM_TO_BERRY(ITEM_SITRUS_BERRY), 5
	setberrytree 34, ITEM_TO_BERRY(ITEM_POMEG_BERRY), 5
	setberrytree 35, ITEM_TO_BERRY(ITEM_POMEG_BERRY), 5
	setberrytree 36, ITEM_TO_BERRY(ITEM_POMEG_BERRY), 5
	setberrytree 83, ITEM_TO_BERRY(ITEM_HONDEW_BERRY), 5
	setberrytree 84, ITEM_TO_BERRY(ITEM_HONDEW_BERRY), 5
	setberrytree 85, ITEM_TO_BERRY(ITEM_SITRUS_BERRY), 5
	setberrytree 86, ITEM_TO_BERRY(ITEM_LEPPA_BERRY), 5
	setberrytree 37, ITEM_TO_BERRY(ITEM_ASPEAR_BERRY), 5
	setberrytree 38, ITEM_TO_BERRY(ITEM_ASPEAR_BERRY), 5
	setberrytree 39, ITEM_TO_BERRY(ITEM_ASPEAR_BERRY), 5
	setberrytree 40, ITEM_TO_BERRY(ITEM_PECHA_BERRY), 5
	setberrytree 41, ITEM_TO_BERRY(ITEM_PECHA_BERRY), 5
	setberrytree 42, ITEM_TO_BERRY(ITEM_PECHA_BERRY), 5
	setberrytree 46, ITEM_TO_BERRY(ITEM_WEPEAR_BERRY), 5
	setberrytree 45, ITEM_TO_BERRY(ITEM_PINAP_BERRY), 5
	setberrytree 44, ITEM_TO_BERRY(ITEM_NANAB_BERRY), 5
	setberrytree 43, ITEM_TO_BERRY(ITEM_RAZZ_BERRY), 5
	setberrytree 47, ITEM_TO_BERRY(ITEM_PERSIM_BERRY), 5
	setberrytree 48, ITEM_TO_BERRY(ITEM_ASPEAR_BERRY), 5
	setberrytree 49, ITEM_TO_BERRY(ITEM_RAWST_BERRY), 5
	setberrytree 50, ITEM_TO_BERRY(ITEM_CHESTO_BERRY), 5
	setberrytree 52, ITEM_TO_BERRY(ITEM_NANAB_BERRY), 5
	setberrytree 53, ITEM_TO_BERRY(ITEM_NANAB_BERRY), 5
	setberrytree 62, ITEM_TO_BERRY(ITEM_LEPPA_BERRY), 5
	setberrytree 64, ITEM_TO_BERRY(ITEM_LEPPA_BERRY), 5
	setberrytree 58, ITEM_TO_BERRY(ITEM_POMEG_BERRY), 5
	setberrytree 59, ITEM_TO_BERRY(ITEM_POMEG_BERRY), 5
	setberrytree 60, ITEM_TO_BERRY(ITEM_GREPA_BERRY), 5
	setberrytree 61, ITEM_TO_BERRY(ITEM_GREPA_BERRY), 5
	setberrytree 79, ITEM_TO_BERRY(ITEM_QUALOT_BERRY), 5
	setberrytree 14, ITEM_TO_BERRY(ITEM_QUALOT_BERRY), 5
	setberrytree 15, ITEM_TO_BERRY(ITEM_POMEG_BERRY), 5
	setberrytree 30, ITEM_TO_BERRY(ITEM_POMEG_BERRY), 5
	setberrytree 65, ITEM_TO_BERRY(ITEM_GREPA_BERRY), 5
	setberrytree 72, ITEM_TO_BERRY(ITEM_GREPA_BERRY), 5
	setberrytree 73, ITEM_TO_BERRY(ITEM_QUALOT_BERRY), 5
	setberrytree 74, ITEM_TO_BERRY(ITEM_QUALOT_BERRY), 5
	setberrytree 87, ITEM_TO_BERRY(ITEM_PECHA_BERRY), 5
	setberrytree 88, ITEM_TO_BERRY(ITEM_SITRUS_BERRY), 5
	setberrytree 89, ITEM_TO_BERRY(ITEM_RAWST_BERRY), 5
	setberrytree 82, ITEM_TO_BERRY(ITEM_LIECHI_BERRY), 5
	return

EventScript_ResetAllMapFlags:: @ 82715DE
	setflag FLAG_LINK_CONTEST_POKE_BALL
	setflag FLAG_HIDE_ROUTE_111_VICTORIA_WINSTRATE
	setflag FLAG_HIDE_ROUTE_111_VIVI_WINSTRATE
	setflag FLAG_HIDE_ROUTE_111_VICKY_WINSTRATE
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_BIRCH
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_RIVAL
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_POKEBALL_CYNDAQUIL
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_POKEBALL_TOTODILE
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_POKEBALL_CHIKORITA
	setflag FLAG_HIDE_PETALBURG_CITY_WALLY
	setflag FLAG_UNKNOWN_0x363
	setflag FLAG_HIDE_RUSTBORO_CITY_AQUA_GRUNT
	setflag FLAG_HIDE_RUSTBORO_CITY_DEVON_EMPLOYEE_1
	setflag FLAG_HIDE_RUSBORO_CITY_RIVAL
	setflag FLAG_HIDE_RUSTBORO_CITY_SCIENTIST
	setflag FLAG_HIDE_LITTLEROOT_TOWN_FAT_MAN
	setflag FLAG_HIDE_BRINEYS_HOUSE_MR_BRINEY
	setflag FLAG_HIDE_BRINEYS_HOUSE_PEEKO
	setflag FLAG_HIDE_ROUTE_104_MR_BRINEY
	setflag FLAG_HIDE_MR_BRINEY_DEWFORD_TOWN
	setflag FLAG_HIDE_ROUTE_108_MR_BRINEY
	setflag FLAG_HIDE_MR_BRINEY_BOAT_DEWFORD_TOWN
	setflag FLAG_HIDE_ROUTE_109_MR_BRINEY_BOAT
	setflag FLAG_HIDE_ROUTE_104_WHITE_HERB_FLORIST
	setflag FLAG_HIDE_ROUTE_110_BIRCH
	setflag FLAG_HIDE_LILYCOVE_CONTEST_HALL_CONTEST_ATTENDANT_1
	setflag FLAG_HIDE_LILYCOVE_CONTEST_HALL_CONTEST_ATTENDANT_2
	setflag FLAG_HIDE_LILYCOVE_MUSEUM_PATRON_1
	setflag FLAG_HIDE_LILYCOVE_MUSEUM_PATRON_2
	setflag FLAG_HIDE_LILYCOVE_MUSEUM_PATRON_3
	setflag FLAG_HIDE_LILYCOVE_MUSEUM_PATRON_4
	setflag FLAG_HIDE_LILYCOVE_MUSEUM_TOURISTS
	setflag FLAG_HIDE_PETALBURG_GYM_GREETER
	setflag FLAG_HIDE_PETALBURG_GYM_WALLYS_UNCLE
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_BRENDAN
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_BRENDAN
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_RIVAL_BEDROOM
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_RIVAL_BEDROOM
	setflag FLAG_HIDE_PLAYERS_HOUSE_DAD
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_2F_PICHU_DOLL
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F_SWABLU_DOLL
	setflag FLAG_HIDE_FANCLUB_OLD_LADY
	setflag FLAG_HIDE_FANCLUB_BOY
	setflag FLAG_HIDE_FANCLUB_LITTLE_BOY
	setflag FLAG_HIDE_FANCLUB_LADY
	setflag FLAG_HIDE_LILYCOVE_FAN_CLUB_INTERVIEWER
	setflag FLAG_HIDE_ROUTE_118_GABBY_AND_TY_1
	setflag FLAG_HIDE_ROUTE_120_GABBY_AND_TY_1
	setflag FLAG_HIDE_ROUTE_111_GABBY_AND_TY_3
	setflag FLAG_HIDE_ROUTE_118_GABBY_AND_TY_2
	setflag FLAG_HIDE_ROUTE_120_GABBY_AND_TY_2
	setflag FLAG_HIDE_ROUTE_111_GABBY_AND_TY_2
	setflag FLAG_HIDE_ROUTE_118_GABBY_AND_TY_3
	setflag FLAG_HIDE_SLATEPORT_CITY_CONTEST_REPORTER
	setflag FLAG_HIDE_LILYCOVE_CONTEST_HALL_REPORTER
	setflag FLAG_HIDE_VERDANTURF_TOWN_WANDAS_HOUSE_WALLY
	setflag FLAG_HIDE_VERDANTURF_TOWN_WANDAS_HOUSE_LOVER_MAN
	setflag FLAG_HIDE_VERDANTURF_TOWN_WANDAS_HOUSE_WALLYS_UNCLE
	setflag FLAG_HIDE_VERDANTURF_TOWN_WANDAS_HOUSE_LOVER_WOMAN
	setflag FLAG_HIDE_VERDANTURF_TOWN_SCOTT
	setflag FLAG_HIDE_PETALBURG_CITY_WALLYS_UNCLE
	setflag FLAG_HIDE_PETALBURG_GYM_WALLY
	setflag FLAG_HIDE_SLATEPORT_CITY_STERNS_SHIPYARD_MR_BRINEY
	setflag FLAG_HIDE_SEAFLOOR_CAVERN_ROOM_9_ARCHIE
	setflag FLAG_HIDE_SEAFLOOR_CAVERN_ROOM_9_MAXIE
	setflag FLAG_HIDE_SEAFLOOR_CAVERN_ROOM_9_MAGMA_GRUNTS
	setflag FLAG_HIDE_SEAFLOOR_CAVERN_ROOM_9_KYOGRE_1
	setflag FLAG_HIDE_MAGMA_HIDEOUT_4F_GROUDON_1
	setflag FLAG_HIDE_SLATEPORT_CITY_HARBOR_CAPTAIN_STERN
	setflag FLAG_HIDE_SLATEPORT_CITY_HARBOR_AQUA_GRUNT
	setflag FLAG_HIDE_SLATEPORT_CITY_HARBOR_ARCHIE
	setflag FLAG_HIDE_SLATEPORT_CITY_HARBOR_SS_TIDAL
	setflag FLAG_HIDE_LILYCOVE_HARBOR_SSTIDAL
	setflag FLAG_HIDE_SLATEPORT_CITY_GABBY_AND_TY
	setflag FLAG_HIDE_SLATEPORT_CITY_CAPTAIN_STERN
	setflag FLAG_HIDE_SLATEPORT_CITY_HARBOR_SUBMARINE_SHADOW
	setflag FLAG_HIDE_ROUTE_119_RIVAL
	setflag FLAG_HIDE_ROUTE_119_SCOTT
	setflag FLAG_HIDE_SOOTOPOLIS_CITY_STEVEN
	setflag FLAG_HIDE_SOOTOPOLIS_CITY_WALLACE
	setflag FLAG_HIDE_LANETTES_HOUSE_LANETTE
	setflag FLAG_HIDE_TRICK_HOUSE_ENTRANCE_MAN
	setflag FLAG_HIDE_MT_CHIMNEY_TRAINERS
	setflag FLAG_HIDE_MT_CHIMNEY_LAVA_COOKIE_LADY
	setflag FLAG_HIDE_RUSTURF_TUNNEL_OLD_MAN
	setflag FLAG_HIDE_ROUTE_116_MR_BRINEY
	setflag FLAG_HIDE_RUSTURF_TUNNEL_PEEKO
	setflag FLAG_HIDE_RUSTURF_TUNNEL_AQUA_GRUNT
	setflag FLAG_HIDE_RUSTURF_TUNNEL_LOVER_MAN
	setflag FLAG_HIDE_RUSTURF_TUNNEL_LOVER_WOMAN
	setflag FLAG_HIDE_SLATEPORT_CITY_OCEANIC_MUSEUM_2F_ARCHIE
	setflag FLAG_HIDE_SLATEPORT_CITY_OCEANIC_MUSEUM_2F_AQUA_GRUNT_1
	setflag FLAG_HIDE_SLATEPORT_CITY_OCEANIC_MUSEUM_2F_AQUA_GRUNT_2
	setflag FLAG_HIDE_SLATEPORT_MUSEUM_POPULATION
	setflag FLAG_HIDE_BATTLE_TOWER_OPPONENT
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MOM_OUTSIDE
	setflag FLAG_HIDE_LITTLE_ROOT_TOWN_PLAYERS_BEDROOM_MOM
	setflag FLAG_HIDE_LITTLEROOT_TOWN_RIVAL
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCH
	setflag FLAG_HIDE_WEATHER_INSTITUTE_1F_WORKERS
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_UNKNOWN_0x380
	setflag FLAG_HIDE_ROUTE_101_BIRCH
	setflag FLAG_HIDE_ROUTE_103_BIRCH
	setflag FLAG_HIDE_LILYCOVE_HARBOR_FERRY_SAILOR
	setflag FLAG_HIDE_LILYCOVE_HARBOR_EON_TICKET_TAKER
	setflag FLAG_HIDE_SOUTHERN_ISLAND_EON_STONE
	setflag FLAG_HIDE_SOUTHERN_ISLAND_UNCHOSEN_EON_DUO_MON
	setflag FLAG_UNKNOWN_0x393
	setflag FLAG_HIDE_MT_PYRE_SUMMIT_MAXIE
	setflag FLAG_HIDE_MAUVILLE_CITY_WATTSON
	setflag FLAG_HIDE_MAUVILLE_CITY_SCOTT
	setflag FLAG_HIDE_CHAMPIONS_ROOM_RIVAL
	setflag FLAG_HIDE_CHAMPIONS_ROOM_BIRCH
	setflag FLAG_HIDE_ROUTE_110_RIVAL_2
	setflag FLAG_HIDE_ROUTE_119_RIVAL_ON_BIKE
	setflag FLAG_HIDE_ROUTE_104_RIVAL
	setflag FLAG_HIDE_LILCOVE_MOTEL_GAME_DESIGNERS
	setflag FLAG_HIDE_LAVARIDGE_TOWN_RIVAL_1
	setflag FLAG_HIDE_LAVARIDGE_TOWN_RIVAL_2
	setflag FLAG_HIDE_MOSSDEEP_CITY_HOUSE_2_WINGULL
	setflag FLAG_HIDE_METEOR_FALLS_TEAM_AQUA
	setflag FLAG_HIDE_DEWFORD_HALL_SLUDGE_BOMB_MAN
	setflag FLAG_HIDE_FALLARBOR_HOUSE_1_PROF_COZMO
	setflag FLAG_HIDE_WEATHER_INSTITUTE_2F_AQUA_GRUNT_M
	setflag FLAG_HIDE_ROUTE_128_STEVEN
	setflag FLAG_HIDE_ROUTE_128_ARCHIE
	setflag FLAG_HIDE_ROUTE_128_MAXIE
	setflag FLAG_HIDE_ROUTE_116_DEVON_EMPLOYEE
	setflag FLAG_HIDE_SLATEPORT_CITY_TM_SALESMAN
	setflag FLAG_HIDE_SLATEPORT_CITY_SCOTT
	setflag FLAG_HIDE_VICTORY_ROAD_ENTRANCE_WALLY
	setflag FLAG_HIDE_VICTORY_ROAD_EXIT_WALLY
	setflag FLAG_HIDE_SS_TIDAL_CORRIDOR_MR_BRINEY
	setflag FLAG_HIDE_MOSSDEEP_CITY_STEVENS_HOUSE_STEVEN
	setflag FLAG_HIDE_MOSSDEEP_CITY_STEVENS_HOUSE_BELDUM_POKEBALL
	setflag FLAG_HIDE_MOSSDEEP_CITY_STEVENS_HOUSE_INVISIBLE_NINJA_BOY
	setflag FLAG_HIDE_OLDALE_TOWN_RIVAL
	setflag FLAG_HIDE_ROUTE_101_BOY
	setflag FLAG_HIDE_PETALBURG_CITY_SCOTT
	setflag FLAG_HIDE_SOOTOPOLIS_CITY_RAYQUAZA
	setflag FLAG_HIDE_SOOTOPOLIS_CITY_KYOGRE
	setflag FLAG_HIDE_SOOTOPOLIS_CITY_GROUDON
	setflag FLAG_HIDE_SOOTOPOLIS_CITY_RESIDENTS
	setflag FLAG_HIDE_SOOTOPOLIS_CITY_ARCHIE
	setflag FLAG_HIDE_SOOTOPOLIS_CITY_MAXIE
	setflag FLAG_HIDE_ROUTE_111_DESERT_FOSSIL
	setflag FLAG_HIDE_ROUTE_111_PLAYER_DESCENT
	setflag FLAG_HIDE_DESERT_UNDERPASS_FOSSIL
	setflag FLAG_HIDE_MOSSDEEP_CITY_TEAM_MAGMA
	setflag FLAG_HIDE_MOSSDEEP_CITY_SPACE_CENTER_1F_TEAM_MAGMA
	setflag FLAG_HIDE_MOSSDEEP_CITY_SPACE_CENTER_2F_TEAM_MAGMA
	setflag FLAG_HIDE_MOSSDEEP_CITY_SPACE_CENTER_2F_STEVEN
	setflag FLAG_HIDE_LILYCOVE_CONTEST_HALL_BLEND_MASTER_ONLOOKERS
	setflag FLAG_HIDE_DEOXYS
	setflag FLAG_HIDE_SAFARI_ZONE_SOUTH_EAST_EXPANSION
	setflag FLAG_HIDE_FALLORBOR_TOWN_BATTLE_TENT_SCOTT
	setflag FLAG_HIDE_EVER_GRANDE_POKEMON_CENTER_1F_SCOTT
	setflag FLAG_HIDE_SKY_PILLAR_WALLACE
	setflag FLAG_RAYQUAZA_ON_SKY_TOWER_SUMMIT
	call EventScript_ResetAllBerries
	end

EverGrandeCity_HallOfFame_EventScript_2717C1:: @ 82717C1
	special sub_81AFDD0
	setflag FLAG_IS_CHAMPION
	call EverGrandeCity_HallOfFame_EventScript_ResetDefeatedEventLegendaries
	compare VAR_FOSSIL_MANIAC_STATE, 0
	call_if_eq EverGrandeCity_HallOfFame_EventScript_271839
	clearflag FLAG_HIDE_LILCOVE_MOTEL_GAME_DESIGNERS
	call EverGrandeCity_HallOfFame_EventScript_ResetEliteFour
	setflag FLAG_HIDE_SLATEPORT_CITY_STERNS_SHIPYARD_MR_BRINEY
	clearflag FLAG_HIDE_SS_TIDAL_CORRIDOR_MR_BRINEY
	clearflag FLAG_HIDE_MOSSDEEP_CITY_STEVENS_HOUSE_INVISIBLE_NINJA_BOY
	setvar VAR_STEVENS_HOUSE_STATE, 2
	setflag FLAG_HIDE_VICTORY_ROAD_ENTRANCE_WALLY
	clearflag FLAG_HIDE_VICTORY_ROAD_EXIT_WALLY
	clearflag FLAG_HIDE_SLATEPORT_CITY_HARBOR_SS_TIDAL
	clearflag FLAG_HIDE_LILYCOVE_HARBOR_SSTIDAL
	setflag FLAG_HIDE_SAFARI_ZONE_SOUTH_CONSTRUCTION_WORKERS
	clearflag FLAG_HIDE_SAFARI_ZONE_SOUTH_EAST_EXPANSION
	setflag FLAG_HIDE_LILYCOVE_CITY_RIVAL
	special sub_813BA60
	call_if_unset FLAG_RECEIVED_SS_TICKET, EverGrandeCity_HallOfFame_EventScript_271843
	call_if_unset FLAG_RECEIVED_BELDUM, EverGrandeCity_HallOfFame_EventScript_27183F
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_RIVAL_BEDROOM
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_RIVAL_BEDROOM
	compare VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 0
	call_if_eq EverGrandeCity_HallOfFame_EventScript_271851
	return

EverGrandeCity_HallOfFame_EventScript_ResetDefeatedEventLegendaries:: @ 8271829
	clearflag FLAG_DEFEATED_MEW
	clearflag FLAG_DEFEATED_LATIAS_OR_LATIOS
	clearflag FLAG_DEFEATED_DEOXYS
	clearflag FLAG_DEFEATED_LUGIA
	clearflag FLAG_DEFEATED_HO_OH
	return

EverGrandeCity_HallOfFame_EventScript_271839:: @ 8271839
	setvar VAR_FOSSIL_MANIAC_STATE, 1
	return

EverGrandeCity_HallOfFame_EventScript_27183F:: @ 827183F
	clearflag FLAG_HIDE_MOSSDEEP_CITY_STEVENS_HOUSE_BELDUM_POKEBALL
	return

EverGrandeCity_HallOfFame_EventScript_271843:: @ 8271843
	setvar VAR_LITTLEROOT_HOUSES_STATE, 3
	setvar VAR_LITTLEROOT_HOUSES_STATE_2, 3
	clearflag FLAG_HIDE_PLAYERS_HOUSE_DAD
	return

EverGrandeCity_HallOfFame_EventScript_271851:: @ 8271851
	setvar VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 1
	return

EventScript_WhiteOut:: @ 8271857
	call EverGrandeCity_HallOfFame_EventScript_ResetEliteFour
	goto EventScript_ResetMrBriney
	end

EventScript_ResetMrBriney:: @ 8271862
	compare VAR_BRINEY_LOCATION, 1
	goto_if_eq EventScript_MoveMrBrineyToHouse
	compare VAR_BRINEY_LOCATION, 2
	goto_if_eq EventScript_MoveMrBrineyToDewford
	compare VAR_BRINEY_LOCATION, 3
	goto_if_eq EventScript_MoveMrBrineyToRoute108
	end

EventScript_MoveMrBrineyToHouse:: @ 8271884
	setflag FLAG_HIDE_MR_BRINEY_DEWFORD_TOWN
	setflag FLAG_HIDE_MR_BRINEY_BOAT_DEWFORD_TOWN
	setflag FLAG_HIDE_ROUTE_108_MR_BRINEY
	setflag FLAG_HIDE_ROUTE_109_MR_BRINEY_BOAT
	clearflag FLAG_HIDE_ROUTE_104_MR_BRINEY_BOAT
	clearflag FLAG_HIDE_BRINEYS_HOUSE_MR_BRINEY
	clearflag FLAG_HIDE_BRINEYS_HOUSE_PEEKO
	end

EventScript_MoveMrBrineyToDewford:: @ 827189A
	setflag FLAG_HIDE_ROUTE_108_MR_BRINEY
	setflag FLAG_HIDE_ROUTE_109_MR_BRINEY_BOAT
	setflag FLAG_HIDE_ROUTE_104_MR_BRINEY
	setflag FLAG_HIDE_ROUTE_104_MR_BRINEY_BOAT
	setflag FLAG_HIDE_BRINEYS_HOUSE_MR_BRINEY
	setflag FLAG_HIDE_BRINEYS_HOUSE_PEEKO
	clearflag FLAG_HIDE_MR_BRINEY_DEWFORD_TOWN
	clearflag FLAG_HIDE_MR_BRINEY_BOAT_DEWFORD_TOWN
	end

EventScript_MoveMrBrineyToRoute108:: @ 82718B3
	setflag FLAG_HIDE_ROUTE_104_MR_BRINEY
	setflag FLAG_HIDE_ROUTE_104_MR_BRINEY_BOAT
	setflag FLAG_HIDE_BRINEYS_HOUSE_MR_BRINEY
	setflag FLAG_HIDE_BRINEYS_HOUSE_PEEKO
	setflag FLAG_HIDE_MR_BRINEY_DEWFORD_TOWN
	setflag FLAG_HIDE_MR_BRINEY_BOAT_DEWFORD_TOWN
	clearflag FLAG_HIDE_ROUTE_108_MR_BRINEY
	clearflag FLAG_HIDE_ROUTE_109_MR_BRINEY_BOAT
	end

EverGrandeCity_HallOfFame_EventScript_ResetEliteFour:: @ 82718CC
	clearflag FLAG_DEFEATED_ELITE_4_SIDNEY
	clearflag FLAG_DEFEATED_ELITE_4_PHOEBE
	clearflag FLAG_DEFEATED_ELITE_4_GLACIA
	clearflag FLAG_DEFEATED_ELITE_4_DRAKE
	setvar VAR_ELITE_4_STATE, 0
	return

DewfordTown_PokemonCenter_1F_EventScript_2718DE:: @ 82718DE
FallarborTown_PokemonCenter_1F_EventScript_2718DE:: @ 82718DE
LavaridgeTown_PokemonCenter_1F_EventScript_2718DE:: @ 82718DE
MauvilleCity_PokemonCenter_1F_EventScript_2718DE:: @ 82718DE
OldaleTown_PokemonCenter_1F_EventScript_2718DE:: @ 82718DE
PetalburgCity_PokemonCenter_1F_EventScript_2718DE:: @ 82718DE
RustboroCity_PokemonCenter_1F_EventScript_2718DE:: @ 82718DE
SlateportCity_PokemonCenter_1F_EventScript_2718DE:: @ 82718DE
VerdanturfTown_PokemonCenter_1F_EventScript_2718DE:: @ 82718DE
	goto_if_unset FLAG_RECEIVED_POKENAV, Common_EventScript_NopReturn
	goto_if_set FLAG_DEFEATED_PETALBURG_GYM, Common_EventScript_NopReturn
	goto_if_unset FLAG_HIDE_ROUTE_104_MR_BRINEY_BOAT, OldaleTown_PokemonCenter_1F_EventScript_27190C
	goto_if_unset FLAG_HIDE_MR_BRINEY_DEWFORD_TOWN, OldaleTown_PokemonCenter_1F_EventScript_271912
	goto_if_unset FLAG_HIDE_ROUTE_108_MR_BRINEY, OldaleTown_PokemonCenter_1F_EventScript_271918
	return

OldaleTown_PokemonCenter_1F_EventScript_27190C:: @ 827190C
	setvar VAR_BRINEY_LOCATION, 1
	return

OldaleTown_PokemonCenter_1F_EventScript_271912:: @ 8271912
	setvar VAR_BRINEY_LOCATION, 2
	return

OldaleTown_PokemonCenter_1F_EventScript_271918:: @ 8271918
	setvar VAR_BRINEY_LOCATION, 3
	return

BattleFrontier_PokemonCenter_1F_EventScript_27191E:: @ 827191E
DewfordTown_PokemonCenter_1F_EventScript_27191E:: @ 827191E
EverGrandeCity_PokemonCenter_1F_EventScript_27191E:: @ 827191E
EverGrandeCity_PokemonLeague_1F_EventScript_27191E:: @ 827191E
FallarborTown_PokemonCenter_1F_EventScript_27191E:: @ 827191E
FortreeCity_PokemonCenter_1F_EventScript_27191E:: @ 827191E
LavaridgeTown_PokemonCenter_1F_EventScript_27191E:: @ 827191E
LilycoveCity_PokemonCenter_1F_EventScript_27191E:: @ 827191E
MauvilleCity_PokemonCenter_1F_EventScript_27191E:: @ 827191E
MossdeepCity_PokemonCenter_1F_EventScript_27191E:: @ 827191E
OldaleTown_PokemonCenter_1F_EventScript_27191E:: @ 827191E
PacifidlogTown_PokemonCenter_1F_EventScript_27191E:: @ 827191E
PetalburgCity_PokemonCenter_1F_EventScript_27191E:: @ 827191E
RustboroCity_PokemonCenter_1F_EventScript_27191E:: @ 827191E
SlateportCity_PokemonCenter_1F_EventScript_27191E:: @ 827191E
SootopolisCity_PokemonCenter_1F_EventScript_27191E:: @ 827191E
TrainerHill_Entrance_EventScript_27191E:: @ 827191E
VerdanturfTown_PokemonCenter_1F_EventScript_27191E:: @ 827191E
	lock
	faceplayer
	setvar VAR_0x8004, 0
	specialvar VAR_RESULT, CountPlayerTrainerStars
	compare VAR_RESULT, 4
	goto_if_eq OldaleTown_PokemonCenter_1F_EventScript_271A68
	msgbox gUnknown_082726EB, MSGBOX_YESNO
	compare VAR_RESULT, 1
	goto_if_eq OldaleTown_PokemonCenter_1F_EventScript_27195A
	compare VAR_RESULT, 0
	goto_if_eq OldaleTown_PokemonCenter_1F_EventScript_271954
	end

OldaleTown_PokemonCenter_1F_EventScript_271954:: @ 8271954
	message gUnknown_082727DB
	return

OldaleTown_PokemonCenter_1F_EventScript_27195A:: @ 827195A
	incrementgamestat 15
	compare VAR_0x8004, 0
	call_if_eq OldaleTown_PokemonCenter_1F_EventScript_271987
	compare VAR_0x8004, 1
	call_if_eq OldaleTown_PokemonCenter_1F_EventScript_27198D
	waitmessage
	call OldaleTown_PokemonCenter_1F_EventScript_271993
	goto_if_unset FLAG_POKERUS_EXPLAINED, OldaleTown_PokemonCenter_1F_EventScript_271A43
	goto OldaleTown_PokemonCenter_1F_EventScript_2719B1
	end

OldaleTown_PokemonCenter_1F_EventScript_271987:: @ 8271987
	message gUnknown_08272768
	return

OldaleTown_PokemonCenter_1F_EventScript_27198D:: @ 827198D
	message gUnknown_082729C0
	return

OldaleTown_PokemonCenter_1F_EventScript_271993:: @ 8271993
	applymovement VAR_0x800B, Common_Movement_WalkInPlaceLeft
	waitmovement 0
	dofieldeffect FLDEFF_POKECENTER_HEAL
	waitfieldeffect FLDEFF_POKECENTER_HEAL
	applymovement VAR_0x800B, Common_Movement_WalkInPlaceDown
	waitmovement 0
	special HealPlayerParty
	return

OldaleTown_PokemonCenter_1F_EventScript_2719B1:: @ 82719B1
	specialvar VAR_RESULT, sub_8139ED0
	compare VAR_RESULT, 0
	goto_if_eq OldaleTown_PokemonCenter_1F_EventScript_2719E2
	specialvar VAR_RESULT, sp182_move_string
	copyvar VAR_0x8008, VAR_RESULT
	compare VAR_0x8008, 0
	goto_if_eq OldaleTown_PokemonCenter_1F_EventScript_2719E2
	compare VAR_0x8008, 1
	goto_if_eq OldaleTown_PokemonCenter_1F_EventScript_271A19
	end

OldaleTown_PokemonCenter_1F_EventScript_2719E2:: @ 82719E2
	compare VAR_0x8004, 1
	goto_if_eq OldaleTown_PokemonCenter_1F_EventScript_271A03
	message gUnknown_08272798
	waitmessage
	applymovement VAR_0x800B, OldaleTown_PokemonCenter_1F_Movement_271AD0
	waitmovement 0
	message gUnknown_082727DB
	return

OldaleTown_PokemonCenter_1F_EventScript_271A03:: @ 8271A03
	message gUnknown_082729F0
	waitmessage
	applymovement VAR_0x800B, OldaleTown_PokemonCenter_1F_Movement_271AD0
	waitmovement 0
	message gUnknown_08272A07
	return

OldaleTown_PokemonCenter_1F_EventScript_271A19:: @ 8271A19
	goto_if_set FLAG_NURSE_UNION_ROOM_REMINDER, OldaleTown_PokemonCenter_1F_EventScript_2719E2
	msgbox gUnknown_08272798, MSGBOX_DEFAULT
	setflag FLAG_NURSE_UNION_ROOM_REMINDER
	message OldaleTown_PokemonCenter_1F_Text_278A48
	waitmessage
	applymovement VAR_0x800B, OldaleTown_PokemonCenter_1F_Movement_271AD0
	waitmovement 0
	message gUnknown_082727DB
	return

OldaleTown_PokemonCenter_1F_EventScript_271A43:: @ 8271A43
	specialvar VAR_RESULT, IsPokerusInParty
	compare VAR_RESULT, 1
	goto_if_eq OldaleTown_PokemonCenter_1F_EventScript_Explain_Pokerus
	compare VAR_RESULT, 0
	goto_if_eq OldaleTown_PokemonCenter_1F_EventScript_2719B1
	end

OldaleTown_PokemonCenter_1F_EventScript_Explain_Pokerus:: @ 8271A5F
	message gText_PokerusExplanation
	setflag FLAG_POKERUS_EXPLAINED
	return

OldaleTown_PokemonCenter_1F_EventScript_271A68:: @ 8271A68
	goto_if_set FLAG_OLDALE_NURSE_MENTIONS_GOLD_CARD, OldaleTown_PokemonCenter_1F_EventScript_271AAC
	setflag FLAG_OLDALE_NURSE_MENTIONS_GOLD_CARD
	msgbox gUnknown_082727F5, MSGBOX_DEFAULT
	playse SE_PIN
	applymovement VAR_0x800B, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement VAR_0x800B, Common_Movement_Delay48
	waitmovement 0
	msgbox gUnknown_08272860, MSGBOX_YESNO
	compare VAR_RESULT, 1
	goto_if_eq OldaleTown_PokemonCenter_1F_EventScript_271AC5
	message gUnknown_08272A07
	return

OldaleTown_PokemonCenter_1F_EventScript_271AAC:: @ 8271AAC
	msgbox gUnknown_08272982, MSGBOX_YESNO
	compare VAR_RESULT, 1
	goto_if_eq OldaleTown_PokemonCenter_1F_EventScript_271AC5
	message gUnknown_08272A07
	return

OldaleTown_PokemonCenter_1F_EventScript_271AC5:: @ 8271AC5
	setvar VAR_0x8004, 1
	goto OldaleTown_PokemonCenter_1F_EventScript_27195A
	end

OldaleTown_PokemonCenter_1F_Movement_271AD0: @ 8271AD0
	nurse_joy_bow
	delay_4
	step_end

Std_ObtainItem:: @ 8271AD3
	giveitem VAR_0x8000, VAR_0x8001
	copyvar VAR_0x8007, VAR_RESULT
	call EventScript_271AE3
	return

EventScript_271AE3:: @ 8271AE3
	bufferitemnameplural 1, VAR_0x8000, VAR_0x8001
	checkitemtype VAR_0x8000
	call EventScript_271B08
	compare VAR_0x8007, 1
	call_if_eq EventScript_271B95
	compare VAR_0x8007, 0
	call_if_eq EventScript_271BA9
	return

EventScript_271B08:: @ 8271B08
	switch VAR_RESULT
	case 1, EventScript_271B45 			@ITEMS
	case 2, EventScript_MedicinePocket
	case 3, EventScript_271B65 			@POKE BALLS
	case 4, EventScript_MegaStonePocket
	case 6, EventScript_ZCrystalPocket
	case 5, EventScript_271B85 			@BERRIES
	case 7, EventScript_271B75 			@TM & HMs
	case 8, EventScript_271B55 			@KEY ITEMS
	end

EventScript_MedicinePocket::
	bufferstdstring 2, 30
	compare VAR_0x8007, 1
	call_if_eq EventScript_271BAF
	return

 EventScript_MegaStonePocket::
	bufferstdstring 2, 31
	compare VAR_0x8007, 1
	call_if_eq EventScript_271BAF
	return

 EventScript_ZCrystalPocket::
	bufferstdstring 2, 32
	compare VAR_0x8007, 1
	call_if_eq EventScript_271BAF
	return

EventScript_271B45:: @ 8271B45
	bufferstdstring 2, 14
	compare VAR_0x8007, 1
	call_if_eq EventScript_271BAF
	return

EventScript_271B55:: @ 8271B55
	bufferstdstring 2, 15
	compare VAR_0x8007, 1
	call_if_eq EventScript_271BAF
	return

EventScript_271B65:: @ 8271B65
	bufferstdstring 2, 16
	compare VAR_0x8007, 1
	call_if_eq EventScript_271BAF
	return

EventScript_271B75:: @ 8271B75
	bufferstdstring 2, 17
	compare VAR_0x8007, 1
	call_if_eq EventScript_271BB3
	return

EventScript_271B85:: @ 8271B85
	bufferstdstring 2, 18
	compare VAR_0x8007, 1
	call_if_eq EventScript_271BAF
	return

EventScript_271B95:: @ 8271B95
	message gUnknown_08272A78
	waitfanfare
	msgbox gText_PutItemInPocket, MSGBOX_DEFAULT
	setvar VAR_RESULT, 1
	return

EventScript_271BA9:: @ 8271BA9
	setvar VAR_RESULT, 0
	return

EventScript_271BAF:: @ 8271BAF
	playfanfare MUS_FANFA4
	return

EventScript_271BB3:: @ 8271BB3
	playfanfare MUS_ME_WAZA
	return

Std_ObtainDecoration:: @ 8271BB7
	givedecoration VAR_0x8000
	copyvar VAR_0x8007, VAR_RESULT
	call EventScript_271BC5
	return

EventScript_271BC5:: @ 8271BC5
	bufferdecorationname 1, VAR_0x8000
	compare VAR_0x8007, 1
	call_if_eq EventScript_271BE0
	compare VAR_0x8007, 0
	call_if_eq EventScript_271BF7
	return

EventScript_271BE0:: @ 8271BE0
	playfanfare MUS_FANFA4
	message gUnknown_08272B09
	waitfanfare
	msgbox gUnknown_08272B48, MSGBOX_DEFAULT
	setvar VAR_RESULT, 1
	return

EventScript_271BF7:: @ 8271BF7
	setvar VAR_RESULT, 0
	return

Std_FindItem:: @ 8271BFD
	lock
	faceplayer
	waitse
	copyvar VAR_0x8004, VAR_0x8000
	copyvar VAR_0x8005, VAR_0x8001
	checkitemspace VAR_0x8000, VAR_0x8001
	copyvar VAR_0x8007, VAR_RESULT
	bufferitemnameplural 1, VAR_0x8000, VAR_0x8001
	checkitemtype VAR_0x8000
	call EventScript_271B08
	compare VAR_0x8007, 1
	call_if_eq EventScript_PickItemUp
	compare VAR_0x8007, 0
	call_if_eq EventScript_271CA1
	release
	return

EventScript_PickItemUp:: @ 8271C3A
	removeobject VAR_LAST_TALKED
	giveitem VAR_0x8004, VAR_0x8005
	specialvar VAR_RESULT, sub_81398C0
	copyvar VAR_0x8008, VAR_RESULT
	compare VAR_0x8008, 1
	call_if_eq EventScript_271C8F
	compare VAR_0x8008, 0
	call_if_eq EventScript_271C9B
	waitfanfare
	waitmessage
	bufferitemnameplural 1, VAR_0x8004, VAR_0x8005
	setvar VAR_0x8004, 12
	special CallBattlePyramidFunction
	compare VAR_RESULT, 1
	goto_if_eq EventScript_271C86
	msgbox gText_PutItemInPocket, MSGBOX_DEFAULT
	return

EventScript_271C86:: @ 8271C86
	msgbox gText_PlayerPutItemInBag, MSGBOX_DEFAULT
	return

EventScript_271C8F:: @ 8271C8F
	bufferitemnameplural 0, VAR_0x8004, VAR_0x8005
	message gText_PlayerFoundOneItemTwoLines
	return

EventScript_271C9B:: @ 8271C9B
	message gText_PlayerFoundOneItem
	return

EventScript_271CA1:: @ 8271CA1
	msgbox gUnknown_08272A78, MSGBOX_DEFAULT
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	setvar VAR_RESULT, 0
	return

EventScript_HiddenItemScript:: @ 8271CB7
	lockall
	waitse
	giveitem VAR_0x8005, 1
	copyvar VAR_0x8007, VAR_RESULT
	bufferitemnameplural 1, VAR_0x8005, 1
	checkitemtype VAR_0x8005
	call EventScript_271B08
	compare VAR_0x8007, 1
	goto_if_eq EventScript_271CE8
	compare VAR_0x8007, 0
	goto_if_eq EventScript_271D47
	end

EventScript_271CE8:: @ 8271CE8
	copyvar VAR_0x8008, VAR_0x8004
	copyvar VAR_0x8004, VAR_0x8005
	specialvar VAR_RESULT, sub_81398C0
	compare VAR_RESULT, 1
	goto_if_eq EventScript_271D0E
	compare VAR_RESULT, 0
	goto_if_eq EventScript_271D1F
	end

EventScript_271D0E:: @ 8271D0E
	bufferitemnameplural 0, VAR_0x8004, 1
	message gText_PlayerFoundOneItemTwoLines
	goto EventScript_271D2A
	end

EventScript_271D1F:: @ 8271D1F
	message gText_PlayerFoundOneItem
	goto EventScript_271D2A
	end

EventScript_271D2A:: @ 8271D2A
	waitmessage
	waitfanfare
	bufferitemnameplural 1, VAR_0x8004, 1
	copyvar VAR_0x8004, VAR_0x8008
	msgbox gText_PutItemInPocket, MSGBOX_DEFAULT
	special sub_80EDCE8
	special SetFlagInVar
	releaseall
	end

EventScript_271D47:: @ 8271D47
	msgbox gText_PlayerFoundOneItem, MSGBOX_DEFAULT
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	setvar VAR_RESULT, 0
	releaseall
	end

EventScript_271D5E:: @ 8271D5E
	lock
	faceplayer
	msgbox Text_WouldYouLikeToMixRecords, MSGBOX_YESNO
	compare VAR_RESULT, 1
	goto_if_eq EventScript_271D83
	compare VAR_RESULT, 0
	goto_if_eq EventScript_271D89
	goto EventScript_271D89

EventScript_271D83:: @ 8271D83
	special RecordMixingPlayerSpotTriggered
	waitstate
	lock
	faceplayer

EventScript_271D89:: @ 8271D89
	message Text_WouldNotLikeToMixRecords
	waitmessage
	waitbuttonpress
	release
	end

EventScript_PC:: @ 8271D92
	lockall
	setvar VAR_0x8004, 0
	special DoPCTurnOnEffect
	playse SE_PC_ON
	msgbox Text_BootUpPC, MSGBOX_DEFAULT
	goto EventScript_271DAC
	end

EventScript_271DAC:: @ 8271DAC
	message gText_WhichPCShouldBeAccessed
	waitmessage
	special ScrSpecial_CreatePCMenu
	waitstate
	goto EventScript_271DBC
	end

EventScript_271DBC:: @ 8271DBC
	switch VAR_RESULT
	case 0, EventScript_271E0E
	case 1, EventScript_271DF9
	case 2, EventScript_271E54
	case 3, EventScript_271E47
	case 127, EventScript_271E47
	end

EventScript_271DF9:: @ 8271DF9
	playse SE_PC_LOGIN
	msgbox gText_AccessedPlayersPC, MSGBOX_DEFAULT
	special PlayerPC
	waitstate
	goto EventScript_271DAC
	end

EventScript_271E0E:: @ 8271E0E
	playse SE_PC_LOGIN
	call_if_unset FLAG_SYS_PC_LANETTE, EventScript_271E35
	call_if_set FLAG_SYS_PC_LANETTE, EventScript_271E3E
	msgbox gText_StorageSystemOpened, MSGBOX_DEFAULT
	special ShowPokemonStorageSystemPC
	waitstate
	goto EventScript_271DAC
	end

EventScript_271E35:: @ 8271E35
	msgbox gText_AccessedSomeonesPC, MSGBOX_DEFAULT
	return

EventScript_271E3E:: @ 8271E3E
	msgbox gText_AccessedLanettesPC, MSGBOX_DEFAULT
	return

EventScript_271E47:: @ 8271E47
	setvar VAR_0x8004, 0
	playse SE_PC_OFF
	special DoPCTurnOffEffect
	releaseall
	end

EventScript_271E54:: @ 8271E54
	goto_if_unset FLAG_SYS_GAME_CLEAR, EventScript_271E47
	playse SE_PC_LOGIN
	special AccessHallOfFamePC
	waitstate
	goto EventScript_271DBC
	end

Common_EventScript_ShowPokemartSign:: @ 8271E6A
	msgbox gText_PokemartSign, MSGBOX_SIGN
	end

Common_EventScript_ShowPokemonCenterSign:: @ 8271E73
	msgbox gText_PokemonCenterSign, MSGBOX_SIGN
	end

Common_ShowEasyChatScreen:: @ 8271E7C
	fadescreen 1
	special ShowEasyChatScreen
	fadescreen 0
	return

DewfordTown_Gym_EventScript_271E84:: @ 8271E84
LavaridgeTown_Gym_1F_EventScript_271E84:: @ 8271E84
MauvilleCity_Gym_EventScript_271E84:: @ 8271E84
RustboroCity_Gym_EventScript_271E84:: @ 8271E84
	clearflag FLAG_HIDE_PETALBURG_GYM_GREETER
	setflag FLAG_PETALBURG_MART_EXPANDED_ITEMS
	return

DewfordTown_EventScript_271E8B:: @ 8271E8B
DewfordTown_Hall_EventScript_271E8B:: @ 8271E8B
	dotimebasedevents
	setvar VAR_0x8004, 0
	special BufferTrendyPhraseString
	return

DewfordTown_EventScript_271E95:: @ 8271E95
Route104_MrBrineysHouse_EventScript_271E95:: @ 8271E95
Route109_EventScript_271E95:: @ 8271E95
	copyvar VAR_0x8008, VAR_BRINEY_LOCATION
	setvar VAR_BRINEY_LOCATION, 0
	return

EventScript_UseSurf:: @ 8271EA0
	checkpartymove MOVE_SURF
	compare VAR_RESULT, 6
	goto_if_eq EventScript_CantSurf
	bufferpartymonnick 0, VAR_RESULT
	setfieldeffectargument 0, VAR_RESULT
	lockall
	msgbox gText_WantToUseSurf, MSGBOX_YESNO
	compare VAR_RESULT, 0
	goto_if_eq EventScript_CancelSurf
	msgbox gText_PlayerUsedSurf, MSGBOX_DEFAULT
	dofieldeffect FLDEFF_USE_SURF

EventScript_CancelSurf:: @ 8271ED5
	releaseall

EventScript_CantSurf:: @ 8271ED6
	end

Common_EventScript_SetupRivalGender:: @ 8271ED7
	checkplayergender
	compare VAR_RESULT, MALE
	goto_if_eq RustboroCity_EventScript_271EEF
	compare VAR_RESULT, FEMALE
	goto_if_eq RustboroCity_EventScript_271EF5
	end

RustboroCity_EventScript_271EEF:: @ 8271EEF
	setvar VAR_OBJ_GFX_ID_0, EVENT_OBJ_GFX_RIVAL_MAY_NORMAL
	return

RustboroCity_EventScript_271EF5:: @ 8271EF5
	setvar VAR_OBJ_GFX_ID_0, EVENT_OBJ_GFX_RIVAL_BRENDAN_NORMAL
	return

Common_EventScript_SetupRivalOnBikeGender:: @ 8271EFB
	checkplayergender
	compare VAR_RESULT, MALE
	goto_if_eq LavaridgeTown_EventScript_271F13
	compare VAR_RESULT, FEMALE
	goto_if_eq LavaridgeTown_EventScript_271F19
	end

LavaridgeTown_EventScript_271F13:: @ 8271F13
	setvar VAR_OBJ_GFX_ID_3, EVENT_OBJ_GFX_RIVAL_MAY_MACH_BIKE
	return

LavaridgeTown_EventScript_271F19:: @ 8271F19
	setvar VAR_OBJ_GFX_ID_3, EVENT_OBJ_GFX_RIVAL_BRENDAN_MACH_BIKE
	return

EventScript_271F1F:: @ 8271F1F
	checkplayergender
	compare VAR_RESULT, MALE
	goto_if_eq EventScript_271F37
	compare VAR_RESULT, FEMALE
	goto_if_eq EventScript_271F3D
	end

EventScript_271F37:: @ 8271F37
	setvar VAR_OBJ_GFX_ID_0, EVENT_OBJ_GFX_RIVAL_BRENDAN_NORMAL
	return

EventScript_271F3D:: @ 8271F3D
	setvar VAR_OBJ_GFX_ID_0, EVENT_OBJ_GFX_RIVAL_MAY_NORMAL
	return

DewfordTown_Gym_EventScript_271F43:: @ 8271F43
FortreeCity_Gym_EventScript_271F43:: @ 8271F43
LavaridgeTown_Gym_1F_EventScript_271F43:: @ 8271F43
MauvilleCity_Gym_EventScript_271F43:: @ 8271F43
MossdeepCity_Gym_EventScript_271F43:: @ 8271F43
PetalburgCity_Gym_EventScript_271F43:: @ 8271F43
RustboroCity_Gym_EventScript_271F43:: @ 8271F43
SootopolisCity_Gym_1F_EventScript_271F43:: @ 8271F43
	switch VAR_0x8008
	case 1, DewfordTown_Gym_EventScript_271FA1
	case 2, DewfordTown_Gym_EventScript_271FAB
	case 3, DewfordTown_Gym_EventScript_271FBE
	case 4, DewfordTown_Gym_EventScript_271FCE
	case 5, DewfordTown_Gym_EventScript_271FE7
	case 6, DewfordTown_Gym_EventScript_271FFD
	case 7, DewfordTown_Gym_EventScript_272010
	case 8, DewfordTown_Gym_EventScript_272035
	end

DewfordTown_Gym_EventScript_271FA1:: @ 8271FA1
	settrainerflag TRAINER_JOSH
	settrainerflag TRAINER_TOMMY
	settrainerflag TRAINER_MARC
	return

DewfordTown_Gym_EventScript_271FAB:: @ 8271FAB
	settrainerflag TRAINER_TAKAO
	settrainerflag TRAINER_JOCELYN
	settrainerflag TRAINER_LAURA
	settrainerflag TRAINER_BRENDEN
	settrainerflag TRAINER_CRISTIAN
	settrainerflag TRAINER_LILITH
	return

DewfordTown_Gym_EventScript_271FBE:: @ 8271FBE
	settrainerflag TRAINER_KIRK
	settrainerflag TRAINER_SHAWN
	settrainerflag TRAINER_BEN
	settrainerflag TRAINER_VIVIAN
	settrainerflag TRAINER_ANGELO
	return

DewfordTown_Gym_EventScript_271FCE:: @ 8271FCE
	settrainerflag TRAINER_COLE
	settrainerflag TRAINER_AXLE
	settrainerflag TRAINER_KEEGAN
	settrainerflag TRAINER_GERALD
	settrainerflag TRAINER_DANIELLE
	settrainerflag TRAINER_JACE
	settrainerflag TRAINER_JEFF
	settrainerflag TRAINER_ELI
	return

DewfordTown_Gym_EventScript_271FE7:: @ 8271FE7
	settrainerflag TRAINER_RANDALL
	settrainerflag TRAINER_PARKER
	settrainerflag TRAINER_GEORGE
	settrainerflag TRAINER_BERKE
	settrainerflag TRAINER_MARY
	settrainerflag TRAINER_ALEXIA
	settrainerflag TRAINER_JODY
	return

DewfordTown_Gym_EventScript_271FFD:: @ 8271FFD
	settrainerflag TRAINER_JARED
	settrainerflag TRAINER_FLINT
	settrainerflag TRAINER_ASHLEY
	settrainerflag TRAINER_EDWARDO
	settrainerflag TRAINER_HUMBERTO
	settrainerflag TRAINER_DARIUS
	return

DewfordTown_Gym_EventScript_272010:: @ 8272010
	settrainerflag TRAINER_PRESTON
	settrainerflag TRAINER_VIRGIL
	settrainerflag TRAINER_BLAKE
	settrainerflag TRAINER_HANNAH
	settrainerflag TRAINER_SAMANTHA
	settrainerflag TRAINER_MAURA
	settrainerflag TRAINER_SYLVIA
	settrainerflag TRAINER_NATE
	settrainerflag TRAINER_KATHLEEN
	settrainerflag TRAINER_CLIFFORD
	settrainerflag TRAINER_MACEY
	settrainerflag TRAINER_NICHOLAS
	return

DewfordTown_Gym_EventScript_272035:: @ 8272035
	settrainerflag TRAINER_ANDREA
	settrainerflag TRAINER_CRISSY
	settrainerflag TRAINER_BRIANNA
	settrainerflag TRAINER_CONNIE
	settrainerflag TRAINER_BRIDGET
	settrainerflag TRAINER_OLIVIA
	settrainerflag TRAINER_TIFFANY
	settrainerflag TRAINER_BETHANY
	settrainerflag TRAINER_ANNIKA
	settrainerflag TRAINER_DAPHNE
	return

Common_EventScript_ShowBagIsFull:: @ 8272054
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	release
	end

Common_EventScript_BagIsFull:: @ 827205E
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	return

Route114_LanettesHouse_EventScript_272067:: @ 8272067
	msgbox gText_NoRoomLeftForAnother, MSGBOX_DEFAULT
	release
	end

Common_EventScript_NoRoomLeftForAnother:: @ 8272071
	msgbox gText_NoRoomLeftForAnother, MSGBOX_DEFAULT
	return

Common_EventScript_SetWeather15:: @ 827207A
	setweather WEATHER_ALTERNATING
	return

Common_EventScript_PlayGymBadgeFanfare:: @ 827207E
	playfanfare MUS_ME_BACHI
	waitfanfare
	return

Common_EventScript_OutOfCenterPartyHeal:: @ 8272083
	fadescreen 1
	playfanfare MUS_ME_ASA
	waitfanfare
	special HealPlayerParty
	fadescreen 0
	return

EventScript_RegionMap:: @ 827208F
	lockall
	msgbox Common_Text_LookCloserAtMap, MSGBOX_DEFAULT
	fadescreen 1
	special FieldShowRegionMap
	waitstate
	releaseall
	end

DewfordTown_EventScript_2720A0:: @ 82720A0
Route104_EventScript_2720A0:: @ 82720A0
Route109_EventScript_2720A0:: @ 82720A0
	setflag FLAG_SPECIAL_FLAG_0x4001
	playbgm MUS_M_BOAT, 0
	return

DewfordTown_EventScript_2720A8:: @ 82720A8
Route104_EventScript_2720A8:: @ 82720A8
Route109_EventScript_2720A8:: @ 82720A8
	clearflag FLAG_SPECIAL_FLAG_0x4001
	fadedefaultbgm
	return

LittlerootTown_ProfessorBirchsLab_EventScript_2720AD:: @ 82720AD
Route101_EventScript_2720AD:: @ 82720AD
Route103_EventScript_2720AD:: @ 82720AD
	compare VAR_PETALBURG_GYM_STATE, 0
	goto_if_eq Common_EventScript_NopReturn
	goto_if_set FLAG_SYS_GAME_CLEAR, Route101_EventScript_27211A
	compare VAR_BIRCH_STATE, 0
	call_if_eq Route101_EventScript_27211A
	compare VAR_BIRCH_STATE, 1
	call_if_eq Route101_EventScript_27211A
	compare VAR_BIRCH_STATE, 2
	call_if_eq Route101_EventScript_272127
	compare VAR_BIRCH_STATE, 3
	call_if_eq Route101_EventScript_272127
	compare VAR_BIRCH_STATE, 4
	call_if_eq Route101_EventScript_272134
	compare VAR_BIRCH_STATE, 5
	call_if_eq Route101_EventScript_272134
	compare VAR_BIRCH_STATE, 6
	call_if_eq Route101_EventScript_27211A
	compare VAR_BIRCH_STATE, 7
	call_if_eq Route101_EventScript_27211A
	return

Route101_EventScript_27211A:: @ 827211A
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_BIRCH
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_UNKNOWN_0x380
	setflag FLAG_HIDE_ROUTE_101_BIRCH
	setflag FLAG_HIDE_ROUTE_103_BIRCH
	return

Route101_EventScript_272127:: @ 8272127
	clearflag FLAG_HIDE_ROUTE_101_BIRCH
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_BIRCH
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_UNKNOWN_0x380
	setflag FLAG_HIDE_ROUTE_103_BIRCH
	return

Route101_EventScript_272134:: @ 8272134
	clearflag FLAG_HIDE_ROUTE_103_BIRCH
	setflag FLAG_HIDE_ROUTE_101_BIRCH
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_BIRCH
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_UNKNOWN_0x380
	return

LittlerootTown_ProfessorBirchsLab_EventScript_272141:: @ 8272141
Route101_EventScript_272141:: @ 8272141
Route103_EventScript_272141:: @ 8272141
	lock
	faceplayer
	goto_if_unset FLAG_HAS_MATCH_CALL, Route101_EventScript_272155
	goto_if_unset FLAG_ENABLE_PROF_BIRCH_MATCH_CALL, Route101_EventScript_1FA2D2

Route101_EventScript_272155:: @ 8272155
	msgbox gUnknown_082A5C9C, MSGBOX_YESNO
	compare VAR_RESULT, 0
	goto_if_eq Route101_EventScript_27216F
	call Route101_EventScript_272184
	release
	end

Route101_EventScript_27216F:: @ 827216F
	msgbox Route101_Text_2A5CEB, MSGBOX_DEFAULT
	release
	end

Route101_EventScript_272179:: @ 8272179
	copyvar VAR_0x8004, VAR_0x8009
	special ShowPokedexRatingMessage
	waitmessage
	waitbuttonpress
	return

EverGrandeCity_ChampionsRoom_EventScript_272184:: @ 8272184
Route101_EventScript_272184:: @ 8272184
	setvar VAR_0x8004, 0
	specialvar VAR_RESULT, ScriptGetPokedexInfo
	copyvar VAR_0x8008, VAR_0x8005
	copyvar VAR_0x8009, VAR_0x8006
	copyvar VAR_0x800A, VAR_RESULT
	buffernumberstring 0, VAR_0x8008
	buffernumberstring 1, VAR_0x8009
	msgbox gUnknown_082A5D2C, MSGBOX_DEFAULT
	call Route101_EventScript_272179
	compare VAR_0x800A, 0
	goto_if_eq Common_EventScript_NopReturn
	setvar VAR_0x8004, 1
	specialvar VAR_RESULT, ScriptGetPokedexInfo
	copyvar VAR_0x8008, VAR_0x8005
	copyvar VAR_0x8009, VAR_0x8006
	buffernumberstring 0, VAR_0x8008
	buffernumberstring 1, VAR_0x8009
	msgbox gUnknown_082A633D, MSGBOX_DEFAULT
	return

BattleFrontier_OutsideWest_EventScript_2721E2:: @ 82721E2
LilycoveCity_Harbor_EventScript_2721E2:: @ 82721E2
SlateportCity_Harbor_EventScript_2721E2:: @ 82721E2
	delay 60
	applymovement VAR_0x8004, SlateportCity_Harbor_Movement_2721F0
	waitmovement 0
	return

SlateportCity_Harbor_Movement_2721F0: @ 82721F0
	walk_slow_right
	walk_slow_right
	walk_slow_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

PetalburgCity_Gym_EventScript_2721F8:: @ 82721F8
	setflag FLAG_HIDE_MR_BRINEY_DEWFORD_TOWN
	setflag FLAG_HIDE_MR_BRINEY_BOAT_DEWFORD_TOWN
	setflag FLAG_HIDE_ROUTE_108_MR_BRINEY
	setflag FLAG_HIDE_ROUTE_109_MR_BRINEY_BOAT
	setflag FLAG_HIDE_ROUTE_104_MR_BRINEY
	setflag FLAG_HIDE_ROUTE_104_MR_BRINEY_BOAT
	setflag FLAG_HIDE_BRINEYS_HOUSE_MR_BRINEY
	setflag FLAG_HIDE_BRINEYS_HOUSE_PEEKO
	setvar VAR_BRINEY_LOCATION, 0
	return

RusturfTunnel_EventScript_272216:: @ 8272216
	removeobject 1
	removeobject 10
	clearflag FLAG_HIDE_VERDANTURF_TOWN_WANDAS_HOUSE_LOVER_MAN
	clearflag FLAG_HIDE_VERDANTURF_TOWN_WANDAS_HOUSE_LOVER_WOMAN
	setvar VAR_RUSTURF_TUNNEL_STATE, 6
	setflag FLAG_RUSTURF_TUNNEL_OPENED
	return

EventScript_27222B:: @ 827222B
	delay 30
	applymovement EVENT_OBJ_ID_PLAYER, Common_Movement_WalkInPlaceUp
	waitmovement 0
	showobjectat 255, MAP_PETALBURG_CITY
	delay 30
	applymovement EVENT_OBJ_ID_PLAYER, Movement_27224E
	waitmovement 0
	delay 30
	return

Movement_27224E: @ 827224E
	walk_up
	step_end

BattleFrontier_OutsideWest_EventScript_272250:: @ 8272250
BirthIsland_Harbor_EventScript_272250:: @ 8272250
FarawayIsland_Entrance_EventScript_272250:: @ 8272250
NavelRock_Harbor_EventScript_272250:: @ 8272250
SouthernIsland_Exterior_EventScript_272250:: @ 8272250
	compare VAR_FACING, 1
	call_if_eq BattleFrontier_OutsideWest_EventScript_242A21
	compare VAR_FACING, 3
	call_if_eq BattleFrontier_OutsideWest_EventScript_242A2C
	delay 30
	hideobjectat 255, MAP_PETALBURG_CITY
	call BattleFrontier_OutsideWest_EventScript_2721E2
	return

EventScript_272274:: @ 8272274
	lockall
	waitse
	playmoncry SPECIES_KYOGRE, 2
	waitmoncry
	setvar VAR_TEMP_5, 1
	releaseall
	end

EventScript_272283:: @ 8272283
	lockall
	setvar VAR_TEMP_1, 1
	goto EventScript_2722A7
	end

EventScript_27228F:: @ 827228F
	lockall
	setvar VAR_TEMP_2, 1
	goto EventScript_2722A7
	end

EventScript_27229B:: @ 827229B
	lockall
	setvar VAR_TEMP_3, 1
	goto EventScript_2722A7
	end

EventScript_2722A7:: @ 82722A7
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 1
	setvar VAR_0x8006, 8
	setvar VAR_0x8007, 5
	special sub_8139560
	waitstate
	releaseall
	end

CaveOfOrigin_1F_EventScript_2722C1:: @ 82722C1
CaveOfOrigin_UnusedRubySapphireMap1_EventScript_2722C1:: @ 82722C1
CaveOfOrigin_UnusedRubySapphireMap2_EventScript_2722C1:: @ 82722C1
CaveOfOrigin_UnusedRubySapphireMap3_EventScript_2722C1:: @ 82722C1
	setvar VAR_TEMP_1, 1
	setvar VAR_TEMP_2, 1
	setvar VAR_TEMP_3, 1
	setvar VAR_TEMP_4, 1
	setvar VAR_TEMP_5, 1
	return

Route120_EventScript_2722DB:: @ 82722DB
	lock
	faceplayer
	setvar VAR_0x8009, 1
	goto Route120_EventScript_272336
	end

Route120_EventScript_2722E8:: @ 82722E8
	lock
	faceplayer
	setvar VAR_0x8009, 2
	goto Route120_EventScript_272336
	end

Route120_EventScript_2722F5:: @ 82722F5
	lock
	faceplayer
	setvar VAR_0x8009, 3
	goto Route120_EventScript_272336
	end

Route120_EventScript_272302:: @ 8272302
	lock
	faceplayer
	setvar VAR_0x8009, 4
	goto Route120_EventScript_272336
	end

Route120_EventScript_27230F:: @ 827230F
	lock
	faceplayer
	setvar VAR_0x8009, 5
	goto Route120_EventScript_272336
	end

Route119_EventScript_27231C:: @ 827231C
	lock
	faceplayer
	setvar VAR_0x8009, 6
	goto Route119_EventScript_272336
	end

Route119_EventScript_272329:: @ 8272329
	lock
	faceplayer
	setvar VAR_0x8009, 7
	goto Route119_EventScript_272336
	end

Route119_EventScript_272336:: @ 8272336
Route120_EventScript_272336:: @ 8272336
	checkitem ITEM_DEVON_SCOPE, 1
	compare VAR_RESULT, 1
	goto_if_eq Route119_EventScript_272350
	msgbox Route119_Text_1F5D00, MSGBOX_DEFAULT
	release
	end

Route119_EventScript_272350:: @ 8272350
	msgbox Route119_Text_1F5D23, MSGBOX_YESNO
	compare VAR_RESULT, 1
	goto_if_eq Route119_EventScript_272365
	release
	end

Route119_EventScript_272365:: @ 8272365
	msgbox Route119_Text_1F5D63, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FacePlayer
	waitmovement 0
	applymovement VAR_LAST_TALKED, Route119_Movement_2723C7
	waitmovement 0
	waitse
	playmoncry SPECIES_KECLEON, 2
	delay 40
	waitmoncry
	setwildbattle SPECIES_KECLEON, 30, ITEM_NONE
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, 1
	goto_if_eq Route119_EventScript_2723C1
	compare VAR_RESULT, 4
	goto_if_eq Route119_EventScript_2723C1
	compare VAR_RESULT, 5
	goto_if_eq Route119_EventScript_2723C1
	release
	end

Route119_EventScript_2723C1:: @ 82723C1
	goto Route119_EventScript_27376D
	end

FortreeCity_Movement_2723C7: @ 82723C7
Route119_Movement_2723C7: @ 82723C7
Route120_Movement_2723C7: @ 82723C7
	set_visible
	delay_4
	set_invisible
	delay_4
	set_visible
	delay_4
	set_invisible
	delay_4
	set_visible
	delay_8
	set_invisible
	delay_8
	set_visible
	delay_8
	set_invisible
	delay_8
	set_visible
	delay_16
	set_invisible
	delay_16
	set_visible
	step_end

Common_EventScript_NameReceivedPokemon:: @ 82723DD
	fadescreen 1
	special ChangePokemonNickname
	waitstate
	return

FallarborTown_House1_EventScript_2723E4:: @ 82723E4
GraniteCave_StevensRoom_EventScript_2723E4:: @ 82723E4
SlateportCity_OceanicMuseum_2F_EventScript_2723E4:: @ 82723E4
	bufferitemname 0, VAR_0x8004
	playfanfare MUS_ME_WAZA
	message gUnknown_08273161
	waitmessage
	waitfanfare
	takeitem VAR_0x8004, 1
	return

EverGrandeCity_DrakesRoom_EventScript_2723F8:: @ 82723F8
EverGrandeCity_GlaciasRoom_EventScript_2723F8:: @ 82723F8
EverGrandeCity_PhoebesRoom_EventScript_2723F8:: @ 82723F8
EverGrandeCity_SidneysRoom_EventScript_2723F8:: @ 82723F8
PokemonLeague_EliteFour_SetAdvanceToNextRoomMetatiles:: @ 82723F8
	applymovement EVENT_OBJ_ID_PLAYER, EverGrandeCity_SidneysRoom_Movement_2725C6
	waitmovement 0
	playse SE_DOOR
	setmetatile 6, 1, METATILE_EliteFour_OpenDoor_Frame, 0
	setmetatile 6, 2, METATILE_EliteFour_OpenDoor_Opening, 0
	setmetatile 0, 2, METATILE_EliteFour_RightSpotlightOff, 1
	setmetatile 1, 2, METATILE_EliteFour_LeftSpotlightOff, 1
	setmetatile 2, 2, METATILE_EliteFour_RightSpotlightOff, 1
	setmetatile 3, 2, METATILE_EliteFour_LeftSpotlightOff, 1
	setmetatile 4, 2, METATILE_EliteFour_RightSpotlightOff, 1
	setmetatile 8, 2, METATILE_EliteFour_LeftSpotlightOff, 1
	setmetatile 9, 2, METATILE_EliteFour_RightSpotlightOff, 1
	setmetatile 10, 2, METATILE_EliteFour_LeftSpotlightOff, 1
	setmetatile 11, 2, METATILE_EliteFour_RightSpotlightOff, 1
	setmetatile 12, 2, METATILE_EliteFour_LeftSpotlightOff, 1
	special DrawWholeMapView
	return

EverGrandeCity_DrakesRoom_EventScript_272475:: @ 8272475
EverGrandeCity_GlaciasRoom_EventScript_272475:: @ 8272475
EverGrandeCity_PhoebesRoom_EventScript_272475:: @ 8272475
EverGrandeCity_SidneysRoom_EventScript_272475:: @ 8272475
	applymovement EVENT_OBJ_ID_PLAYER, EverGrandeCity_SidneysRoom_Movement_2725BA
	waitmovement 0
	playse SE_TRACK_DOOR
	setmetatile 5, 12, METATILE_EliteFour_EntryDoor_ClosedTop, 1
	setmetatile 6, 12, METATILE_EliteFour_EntryDoor_ClosedTop, 1
	setmetatile 7, 12, METATILE_EliteFour_EntryDoor_ClosedTop, 1
	setmetatile 5, 13, METATILE_EliteFour_EntryDoor_ClosedBottom, 1
	setmetatile 6, 13, METATILE_EliteFour_EntryDoor_ClosedBottom, 1
	setmetatile 7, 13, METATILE_EliteFour_EntryDoor_ClosedBottom, 1
	special DrawWholeMapView
	return

EverGrandeCity_DrakesRoom_EventScript_2724BC:: @ 82724BC
EverGrandeCity_GlaciasRoom_EventScript_2724BC:: @ 82724BC
EverGrandeCity_PhoebesRoom_EventScript_2724BC:: @ 82724BC
EverGrandeCity_SidneysRoom_EventScript_2724BC:: @ 82724BC
	setmetatile 6, 1, METATILE_EliteFour_OpenDoor_Frame, 0
	setmetatile 6, 2, METATILE_EliteFour_OpenDoor_Opening, 0
	setmetatile 5, 12, METATILE_EliteFour_EntryDoor_ClosedTop, 1
	setmetatile 6, 12, METATILE_EliteFour_EntryDoor_ClosedTop, 1
	setmetatile 7, 12, METATILE_EliteFour_EntryDoor_ClosedTop, 1
	setmetatile 5, 13, METATILE_EliteFour_EntryDoor_ClosedBottom, 1
	setmetatile 6, 13, METATILE_EliteFour_EntryDoor_ClosedBottom, 1
	setmetatile 7, 13, METATILE_EliteFour_EntryDoor_ClosedBottom, 1
	setmetatile 0, 2, METATILE_EliteFour_RightSpotlightOff, 1
	setmetatile 1, 2, METATILE_EliteFour_LeftSpotlightOff, 1
	setmetatile 2, 2, METATILE_EliteFour_RightSpotlightOff, 1
	setmetatile 3, 2, METATILE_EliteFour_LeftSpotlightOff, 1
	setmetatile 4, 2, METATILE_EliteFour_RightSpotlightOff, 1
	setmetatile 8, 2, METATILE_EliteFour_LeftSpotlightOff, 1
	setmetatile 9, 2, METATILE_EliteFour_RightSpotlightOff, 1
	setmetatile 10, 2, METATILE_EliteFour_LeftSpotlightOff, 1
	setmetatile 11, 2, METATILE_EliteFour_RightSpotlightOff, 1
	setmetatile 12, 2, METATILE_EliteFour_LeftSpotlightOff, 1
	return

EverGrandeCity_DrakesRoom_EventScript_27255F:: @ 827255F
EverGrandeCity_GlaciasRoom_EventScript_27255F:: @ 827255F
EverGrandeCity_PhoebesRoom_EventScript_27255F:: @ 827255F
EverGrandeCity_SidneysRoom_EventScript_27255F:: @ 827255F
	setmetatile 5, 12, METATILE_EliteFour_EntryDoor_ClosedTop, 1
	setmetatile 6, 12, METATILE_EliteFour_EntryDoor_ClosedTop, 1
	setmetatile 7, 12, METATILE_EliteFour_EntryDoor_ClosedTop, 1
	setmetatile 5, 13, METATILE_EliteFour_EntryDoor_ClosedBottom, 1
	setmetatile 6, 13, METATILE_EliteFour_EntryDoor_ClosedBottom, 1
	setmetatile 7, 13, METATILE_EliteFour_EntryDoor_ClosedBottom, 1
	return

SlateportCity_Movement_272596: @ 8272596
	emote_question_mark
	step_end

Common_Movement_ExclamationMark: @ 8272598
	emote_exclamation_mark
	step_end

Common_Movement_Delay48: @ 827259A
	delay_16
	delay_16
	delay_16
	step_end

Common_Movement_FacePlayer: @ 827259E
	face_player
	step_end

Common_Movement_FaceAwayPlayer: @ 82725A0
	face_away_player
	step_end

Common_Movement_FaceOriginalDirection: @ 82725A2
	face_original_direction
	step_end

Common_Movement_WalkInPlaceLeft: @ 82725A4
	walk_in_place_fastest_left
	step_end

Common_Movement_WalkInPlaceUp: @ 82725A6
	walk_in_place_fastest_up
	step_end

Common_Movement_WalkInPlaceRight: @ 82725A8
	walk_in_place_fastest_right
	step_end

Common_Movement_WalkInPlaceDown: @ 82725AA
	walk_in_place_fastest_down
	step_end

RustboroCity_Movement_2725AC: @ 82725AC
	face_right
	step_end

RustboroCity_Movement_2725AE: @ 82725AE
	face_left
	step_end

Common_Movement_FaceDown: @ 82725B0
	face_down
	step_end

Common_Movement_FaceUp: @ 82725B2
	face_up
	step_end

BattleFrontier_BattleDomeBattleRoom_Movement_2725B4: @ 82725B4
MeteorFalls_1F_1R_Movement_2725B4: @ 82725B4
	walk_in_place_down
	step_end

BattleFrontier_BattlePalaceBattleRoom_Movement_2725B6: @ 82725B6
BattleFrontier_BattleTowerBattleRoom_Movement_2725B6: @ 82725B6
	walk_in_place_left
	step_end

Route121_Movement_2725B8: @ 82725B8
	walk_in_place_right
	step_end

EverGrandeCity_SidneysRoom_Movement_2725BA: @ 82725BA
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

EverGrandeCity_ChampionsRoom_Movement_2725C1: @ 82725C1
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

EverGrandeCity_SidneysRoom_Movement_2725C6: @ 82725C6
	delay_16
	delay_16
	step_end

Route110_TrickHouseEntrance_Movement_2725C9: @ 82725C9
	walk_up
	step_end

Movement_2725CB:: @ 82725CB
	walk_up
	walk_up
	step_end

EventScript_PictureBookShelf:: @ 82725CE
	msgbox Text_PictureBookShelf, MSGBOX_SIGN
	end

EventScript_BookShelf:: @ 82725D7
	msgbox Text_BookShelf, MSGBOX_SIGN
	end

EventScript_PokemonCenterBookShelf:: @ 82725E0
	msgbox Text_PokemonCenterBookShelf, MSGBOX_SIGN
	end

EventScript_Vase:: @ 82725E9
	msgbox Text_Vase, MSGBOX_SIGN
	end

EventScript_EmptyTrashCan:: @ 82725F2
	msgbox Text_EmptyTrashCan, MSGBOX_SIGN
	end

EventScript_ShopShelf:: @ 82725FB
	msgbox Text_ShopShelf, MSGBOX_SIGN
	end

EventScript_Blueprint:: @ 8272604
	msgbox Text_Blueprint, MSGBOX_SIGN
	end

Text_WouldYouLikeToMixRecords: @ 827260D
	.string "你想要与其他训练师\n"
	.string "混合记录吗?$"

Text_WouldNotLikeToMixRecords: @ 8272640
	.string "欢迎下次再来!$"

Text_BootUpPC: @ 827265A
	.string "{PLAYER}启动了电脑。$"

gText_WhichPCShouldBeAccessed:: @ 827266F
	.string "要连接哪个电脑?$"

gText_AccessedSomeonesPC:: @ 827268C
	.string "连接到某人的电脑。$"

gText_StorageSystemOpened:: @ 82726A3
	.string "打开宝可梦存储系统。$"

gText_AccessedPlayersPC:: @ 82726C2
	.string "连接到{PLAYER}的电脑$"

gText_AccessedLanettesPC:: @ 82726D4
	.string "连接到真由美的电脑。$"

gUnknown_082726EB:: @ 82726EB
	.string "您好,\n欢迎来到宝可梦中心，\p我们可以为疲劳的\n宝可梦恢复体力。\p要让您的宝可梦休息一下吗?$"

gUnknown_08272768:: @ 8272768
	.string "好的，\n您的宝可梦暂时由我保管。$"

gUnknown_08272798:: @ 8272798
	.string "让您久等了，\n宝可梦的体力已经都恢复了。$"

gUnknown_082727DB:: @ 82727DB
	.string "欢迎下次再来!$"

gUnknown_082727F5:: @ 82727F5
	.string "您好,\n欢迎来到宝可梦中心，\p我们可以为疲劳的\n宝可梦恢复体力。\p要让您的…$"

gUnknown_08272860:: @ 8272860
	.string "这个…\n这个难道是…金卡?!\p这金色好耀眼!\n上面4颗星星似乎在闪闪发光!\p我之前见过几个\n拥有银卡的训练师,但是, {PLAYER},\l你是我见过的第一个\l拥有金卡的训练师!\p {PLAYER}, 请允许我能有幸\n为您的宝可梦恢复体力!$"

gUnknown_08272982:: @ 8272982
	.string "很高兴见到您, {PLAYER}!\n跟平常的一样,对吗?$"

gUnknown_082729C0:: @ 82729C0
	.string "好的，\n您的宝可梦暂时由我保管。$"

gUnknown_082729F0:: @ 82729F0
	.string "让您久等了。$"

gUnknown_08272A07:: @ 8272A07
	.string "欢迎下次再来!$"

gUnknown_08272A21:: @ 8272A21
	.string "欢迎!\p我可以为您服务吗?$"

gUnknown_08272A3F:: @ 8272A3F
	.string "请下次再来!$"

gUnknown_08272A52:: @ 8272A52
	.string "{PLAYER}{STRING 5},欢迎!\p我可以为您服务吗?$"

gUnknown_08272A78:: @ 8272A78
	.string "获得了{STR_VAR_2}!$"

gUnknown_08272A89:: @ 8272A89
	.string "背包满了…$"

gText_PutItemInPocket:: @ 8272A9A
	.string "{PLAYER}将{STR_VAR_2}\n放进背包的{STR_VAR_3}口袋里。$"

gText_PlayerFoundOneItem:: @ 8272ABF
	.string "{PLAYER}发现了一个{STR_VAR_2}!$"

gText_TooBadBagIsFull:: @ 8272AD0
	.string "糟糕!\n背包满了…$"

gText_PlayerPutItemInBag:: @ 8272AEA
	.string "{PLAYER}将{STR_VAR_2}\n放进背包里。$"

gUnknown_08272B09:: @ 8272B09
	.string "获得了{STR_VAR_2}!$"

gText_NoRoomLeftForAnother:: @ 8272B1A
	.string "糟糕! 背包没有剩余的\n空间来存放{STR_VAR_2}…$"

gUnknown_08272B48:: @ 8272B48
	.string "{STR_VAR_2}被传送到了\n电脑上。$"

gText_PokemartSign:: @ 8272B6A
	.string "“来挑选一些便利的物品吧!”\n宝可梦商店$"

gText_PokemonCenterSign:: @ 8272B9E
	.string "“让您的伙伴们恢复活力!”\n宝可梦中心$"

gUnknown_08272BCF:: @ 8272BCF
	.string "{STR_VAR_1} 可能会喜欢这个节目\n… … … … … … … … … … … … … … … …\p我得走了!$"

gUnknown_08272C1D:: @ 8272C1D
	.string "欢迎来到水静百货公司。\p您想要去几楼?$"

gUnknown_08272C5F:: @ 8272C5F
	.string "沙尘暴太凶猛了，\n不能继续前行了。$"

gText_SelectWithoutRegisteredItem:: @ 8272C98
	.string "背包里的物品可以\n登录到SELECT上，方便使用。$"

gUnknown_08272CD5:: @ 8272CD5
	.string "这里有一封来自\n宝可梦训练师学校的邮件\p… … … … … …\p一只宝可梦最多可以学习4个技能。\p在为宝可梦选择技能配置也是对\n训练师的考验。\p… … … … … …$"

gText_PlayerHouseBootPC:: @ 8272D87
	.string "{PLAYER}启动了电脑$"

gUnknown_08272D9C:: @ 8272D9C
	.string "连接被取消了。$"

gUnknown_08272DB3:: @ 8272DB3
	.string "想要为您收到的\n{STR_VAR_2}取一个昵称吗?$"

gUnknown_08272DE3:: @ 8272DE3
	.string "{PLAYER}已经没有\n可以使用的宝可梦!\p{PLAYER}被击败了!$"

gText_RegisteredTrainerinPokeNav:: @ 8272E0F
	.string "将{STR_VAR_1} {STR_VAR_2}\n记录到宝可梦图鉴上。$"

gUnknown_08272E30:: @ 8272E30
	.string "你知道秘密之力吗?\p我们的团队都\n喜欢秘密之力。\p我们的一个成员会将它给你。\n如果你得到它请回来告诉我。\p我们会接受你成为团队的一员，\n并向你出售保密的好东西。$"

gText_PokerusExplanation:: @ 8272F07
	.string "你的宝可梦可能感染了\n宝可梦病毒。\p人们对宝可病毒了解不多,\n只知道它们是寄生在宝可梦\l身上的微生物。\p据说当感染病毒时, \n宝可梦会更好地成长。$"

	.include "data/text/surf.inc"

gUnknown_0827301B:: @ 827301B
	.string "听起来好像有一扇门\n在很远的地方打开了。$"

gUnknown_0827304E:: @ 827304E
	.string "墙上有一个大洞。$"

gUnknown_0827306F:: @ 827306F
	.string "非常抱歉。\n宝可梦无线俱乐部\l系统正在调整。$"

gUnknown_082730BC:: @ 82730BC
	.string "它似乎正在进行\n调整的样子…$"

gUnknown_082730E5:: @ 82730E5
	.string "非常抱歉。交易中心目前\n正在接受检查。$"

gUnknown_08273125:: @ 8273125
	.string "非常抱歉。报告角目前\n正在准备中。$"

gUnknown_08273161:: @ 8273161
	.string "{PLAYER}移交了\n{STR_VAR_1}.$"

gUnknown_08273178:: @ 8273178
	.string "感谢您访问\n神秘礼物系统。$"

gText_PlayerFoundOneItemTwoLines:: @ 82731A9
	.string "{PLAYER}找到了一个{STR_VAR_1}\n{STR_VAR_2}!$"

gText_Sudowoodo_Attacked:: @ 82731BD
	.string "奇怪的树不喜欢\n吼吼鲸喷壶!\p奇怪的树发起了攻击!$"

gText_LegendaryFlewAway:: @ 8273204
	.string "{STR_VAR_1}飞走了!$"

gText_PkmnTransferredSomeonesPC:: @ 8273216
	.string "{STR_VAR_2}已被传送到\n某人的电脑上。\p它被放置在\n盒子 “{STR_VAR_1}中。”$"

gText_PkmnTransferredLanettesPC:: @ 8273256
	.string "{STR_VAR_2}已被传送到\n真由美的电脑上。\p它被放置在\n盒子 “{STR_VAR_1}中。”$"

gText_PkmnBoxSomeonesPCFull:: @ 8273296
	.string "某人的电脑上的\n 盒子“{STR_VAR_3}” 已被装满。\p{STR_VAR_2} 已转移到\n盒子“{STR_VAR_1}中。”$"

gText_PkmnBoxLanettesPCFull:: @ 82732D9
	.string "真由美的电脑上的\n 盒子“{STR_VAR_3}” 已被装满。\p{STR_VAR_2} 已转移到\n盒子“{STR_VAR_1}中。””$"

gUnknown_0827331C:: @ 827331C
	.string "盒子装满了!\p已经没有剩余的空间\n来接受宝可梦了!$"

gText_NicknameThisPokemon:: @ 8273374
	.string "你想要为{STR_VAR_1}\n取个昵称吗?$"

gUnknown_0827339F:: @ 827339F
	.string "这里有份调查问卷。\n你想要填写吗?$"

gUnknown_082733D8:: @ 82733D8
	.string "感谢您抽出时间\n来填写我们的调查问卷。\p您的反馈意见\n将用于未来的参考。$"

gUnknown_08273446:: @ 8273446
	.string "你好!\n你知道神秘礼物吗?\p你必须要先了解\n什么是神秘礼物。\p从现在起，你可以收到\n很多神秘礼物!$"

gUnknown_082734CC:: @ 82734CC
	.string "保存游戏后，\n你可以接收神秘礼物。$"

gUnknown_08273506:: @ 8273506
	.string "你好!\n你知道神秘事件吗?\p你必须要先了解\n什么是神秘事件。$"

gUnknown_08273559:: @ 8273559
	.string "保存游戏后，\n你可以接收神秘事件。$"

gUnknown_08273594:: @ 8273594
	.string "感谢您使用\n神秘事件系统。\p您是{PLAYER}吧。\n这里有一张票给您。$"

gUnknown_082735F2:: @ 82735F2
	.string "它似乎可以在水静市的\n港口使用。\p为什么不去试下，\n看看它是去哪的?$"

gText_UnusualWeatherEnded_Rain:: @ 8273656
	.string "大暴雨似乎停止了…$"

gText_UnusualWeatherEnded_Sun:: @ 8273684
	.string "强烈的阳光似乎消退了…$"

EventScript_SelectWithoutRegisteredItem:: @ 82736B3
	msgbox gText_SelectWithoutRegisteredItem, MSGBOX_SIGN
	end

EventScript_Poison:: @ 82736BC
	lockall
	special ExecuteWhiteOut
	waitstate
	compare VAR_RESULT, 1
	goto_if_eq EventScript_2736D9
	compare VAR_RESULT, 2
	goto_if_eq EventScript_2736F8
	releaseall
	end

EventScript_2736D9:: @ 82736D9
	message gUnknown_08272DE3
	waitmessage
	waitbuttonpress
	special sub_80B05B4
	waitstate
	fadescreen 1
	call_if_set FLAG_FLANNERY_GIVES_BADGE_INFO, EventScript_2736F4
	special sp0C8_whiteout_maybe
	waitstate
	end

EventScript_2736F4:: @ 82736F4
	setrespawn HEAL_LOCATION_LAVARIDGE_TOWN
	return

EventScript_2736F8:: @ 82736F8
	message gUnknown_08272DE3
	waitmessage
	waitbuttonpress
	setvar VAR_0x8004, 16
	special CallBattlePikeFunction
	compare VAR_RESULT, 1
	goto_if_eq BattleFrontier_BattlePikeThreePathRoom_EventScript_2C4222
	setvar VAR_0x8004, 12
	special CallBattlePyramidFunction
	compare VAR_RESULT, 1
	goto_if_eq BattleFrontier_BattlePyramidTop_EventScript_252B42
	compare VAR_RESULT, 2
	goto_if_eq BattleFrontier_BattlePyramidTop_EventScript_252B42
	setvar VAR_0x8004, TRAINER_HILL_FUNC_10
	special CallTrainerHillFunction
	compare VAR_RESULT, 1
	goto_if_eq TrainerHill_1F_EventScript_2C83C9
	special sub_80B05B4
	waitstate
	fadescreen 1
	special sp0C8_whiteout_maybe
	waitstate
	end

Common_EventScript_NopReturn:: @ 827374E
	return

EventScript_UnusedSetVarResult1:: @ 827374F
	setvar VAR_RESULT, 1
	return

OldaleTown_PokemonCenter_2F_EventScript_273755:: @ 8273755
	setvar VAR_RESULT, 0
	return

BattleFrontier_PokemonCenter_2F_EventScript_27375B:: @ 827375B
DewfordTown_PokemonCenter_2F_EventScript_27375B:: @ 827375B
EverGrandeCity_PokemonCenter_2F_EventScript_27375B:: @ 827375B
EverGrandeCity_PokemonLeague_2F_EventScript_27375B:: @ 827375B
FallarborTown_PokemonCenter_2F_EventScript_27375B:: @ 827375B
FortreeCity_PokemonCenter_2F_EventScript_27375B:: @ 827375B
LavaridgeTown_PokemonCenter_2F_EventScript_27375B:: @ 827375B
LilycoveCity_PokemonCenter_2F_EventScript_27375B:: @ 827375B
MauvilleCity_PokemonCenter_2F_EventScript_27375B:: @ 827375B
MossdeepCity_PokemonCenter_2F_EventScript_27375B:: @ 827375B
OldaleTown_PokemonCenter_2F_EventScript_27375B:: @ 827375B
PacifidlogTown_PokemonCenter_2F_EventScript_27375B:: @ 827375B
PetalburgCity_PokemonCenter_2F_EventScript_27375B:: @ 827375B
RustboroCity_PokemonCenter_2F_EventScript_27375B:: @ 827375B
SlateportCity_PokemonCenter_2F_EventScript_27375B:: @ 827375B
SootopolisCity_PokemonCenter_2F_EventScript_27375B:: @ 827375B
VerdanturfTown_PokemonCenter_2F_EventScript_27375B:: @ 827375B
	call OldaleTown_PokemonCenter_2F_EventScript_27751B
	end

BattleFrontier_PokemonCenter_2F_EventScript_273761:: @ 8273761
DewfordTown_PokemonCenter_2F_EventScript_273761:: @ 8273761
EverGrandeCity_PokemonCenter_2F_EventScript_273761:: @ 8273761
EverGrandeCity_PokemonLeague_2F_EventScript_273761:: @ 8273761
FallarborTown_PokemonCenter_2F_EventScript_273761:: @ 8273761
FortreeCity_PokemonCenter_2F_EventScript_273761:: @ 8273761
LavaridgeTown_PokemonCenter_2F_EventScript_273761:: @ 8273761
LilycoveCity_PokemonCenter_2F_EventScript_273761:: @ 8273761
MauvilleCity_PokemonCenter_2F_EventScript_273761:: @ 8273761
MossdeepCity_PokemonCenter_2F_EventScript_273761:: @ 8273761
OldaleTown_PokemonCenter_2F_EventScript_273761:: @ 8273761
PacifidlogTown_PokemonCenter_2F_EventScript_273761:: @ 8273761
PetalburgCity_PokemonCenter_2F_EventScript_273761:: @ 8273761
RustboroCity_PokemonCenter_2F_EventScript_273761:: @ 8273761
SlateportCity_PokemonCenter_2F_EventScript_273761:: @ 8273761
SootopolisCity_PokemonCenter_2F_EventScript_273761:: @ 8273761
VerdanturfTown_PokemonCenter_2F_EventScript_273761:: @ 8273761
	call OldaleTown_PokemonCenter_2F_EventScript_277672
	end

BattleFrontier_PokemonCenter_2F_EventScript_273767:: @ 8273767
DewfordTown_PokemonCenter_2F_EventScript_273767:: @ 8273767
EverGrandeCity_PokemonCenter_2F_EventScript_273767:: @ 8273767
EverGrandeCity_PokemonLeague_2F_EventScript_273767:: @ 8273767
FallarborTown_PokemonCenter_2F_EventScript_273767:: @ 8273767
FortreeCity_PokemonCenter_2F_EventScript_273767:: @ 8273767
LavaridgeTown_PokemonCenter_2F_EventScript_273767:: @ 8273767
LilycoveCity_PokemonCenter_2F_EventScript_273767:: @ 8273767
MauvilleCity_PokemonCenter_2F_EventScript_273767:: @ 8273767
MossdeepCity_PokemonCenter_2F_EventScript_273767:: @ 8273767
OldaleTown_PokemonCenter_2F_EventScript_273767:: @ 8273767
PacifidlogTown_PokemonCenter_2F_EventScript_273767:: @ 8273767
PetalburgCity_PokemonCenter_2F_EventScript_273767:: @ 8273767
RustboroCity_PokemonCenter_2F_EventScript_273767:: @ 8273767
SlateportCity_PokemonCenter_2F_EventScript_273767:: @ 8273767
SootopolisCity_PokemonCenter_2F_EventScript_273767:: @ 8273767
VerdanturfTown_PokemonCenter_2F_EventScript_273767:: @ 8273767
	call OldaleTown_PokemonCenter_2F_EventScript_2776A4
	end

AncientTomb_EventScript_27376D:: @ 827376D
AquaHideout_B1F_EventScript_27376D:: @ 827376D
DesertRuins_EventScript_27376D:: @ 827376D
IslandCave_EventScript_27376D:: @ 827376D
MarineCave_End_EventScript_27376D:: @ 827376D
NewMauville_Inside_EventScript_27376D:: @ 827376D
Route119_EventScript_27376D:: @ 827376D
TerraCave_End_EventScript_27376D:: @ 827376D
	fadescreenswapbuffers 1
	removeobject VAR_LAST_TALKED
	fadescreenswapbuffers 0
	release
	end

AncientTomb_EventScript_273776:: @ 8273776
BirthIsland_Exterior_EventScript_273776:: @ 8273776
DesertRuins_EventScript_273776:: @ 8273776
FarawayIsland_Interior_EventScript_273776:: @ 8273776
IslandCave_EventScript_273776:: @ 8273776
MarineCave_End_EventScript_273776:: @ 8273776
NavelRock_Bottom_EventScript_273776:: @ 8273776
NavelRock_Top_EventScript_273776:: @ 8273776
SouthernIsland_Interior_EventScript_273776:: @ 8273776
TerraCave_End_EventScript_273776:: @ 8273776
	fadescreenswapbuffers 1
	removeobject VAR_LAST_TALKED
	fadescreenswapbuffers 0
	bufferspeciesname 0, VAR_0x8004
	msgbox gText_LegendaryFlewAway, MSGBOX_DEFAULT
	release
	end

LittlerootTown_ProfessorBirchsLab_EventScript_27378B:: @ 827378B
MossdeepCity_StevensHouse_EventScript_27378B:: @ 827378B
Route119_WeatherInstitute_2F_EventScript_27378B:: @ 827378B
RustboroCity_DevonCorp_2F_EventScript_27378B:: @ 827378B
	getpartysize
	subvar VAR_RESULT, 1
	copyvar VAR_0x8004, VAR_RESULT
	return

LittlerootTown_ProfessorBirchsLab_EventScript_273797:: @ 8273797
MossdeepCity_StevensHouse_EventScript_273797:: @ 8273797
Route119_WeatherInstitute_2F_EventScript_273797:: @ 8273797
RustboroCity_DevonCorp_2F_EventScript_273797:: @ 8273797
	fadescreen 1
	special ChangeBoxPokemonNickname
	waitstate
	lock
	faceplayer
	return

LittlerootTown_ProfessorBirchsLab_EventScript_2737A0:: @ 82737A0
MossdeepCity_StevensHouse_EventScript_2737A0:: @ 82737A0
Route119_WeatherInstitute_2F_EventScript_2737A0:: @ 82737A0
RustboroCity_DevonCorp_2F_EventScript_2737A0:: @ 82737A0
	bufferboxname 0, VAR_STORAGE_UNKNOWN
	bufferspeciesname 1, VAR_TEMP_1
	call_if_unset FLAG_SYS_PC_LANETTE, LittlerootTown_ProfessorBirchsLab_EventScript_2737BB
	call_if_set FLAG_SYS_PC_LANETTE, LittlerootTown_ProfessorBirchsLab_EventScript_2737E6
	return

LittlerootTown_ProfessorBirchsLab_EventScript_2737BB:: @ 82737BB
	specialvar VAR_RESULT, sub_813B21C
	compare VAR_RESULT, 1
	goto_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_2737D4
	msgbox gText_PkmnTransferredSomeonesPC, MSGBOX_DEFAULT
	return

LittlerootTown_ProfessorBirchsLab_EventScript_2737D4:: @ 82737D4
	specialvar VAR_RESULT, get_unknown_box_id
	bufferboxname 2, VAR_RESULT
	msgbox gText_PkmnBoxSomeonesPCFull, MSGBOX_DEFAULT
	return

LittlerootTown_ProfessorBirchsLab_EventScript_2737E6:: @ 82737E6
	specialvar VAR_RESULT, sub_813B21C
	compare VAR_RESULT, 1
	goto_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_2737FF
	msgbox gText_PkmnTransferredLanettesPC, MSGBOX_DEFAULT
	return

LittlerootTown_ProfessorBirchsLab_EventScript_2737FF:: @ 82737FF
	specialvar VAR_RESULT, get_unknown_box_id
	bufferboxname 2, VAR_RESULT
	msgbox gText_PkmnBoxLanettesPCFull, MSGBOX_DEFAULT
	return

LittlerootTown_ProfessorBirchsLab_EventScript_273811:: @ 8273811
MossdeepCity_StevensHouse_EventScript_273811:: @ 8273811
Route119_WeatherInstitute_2F_EventScript_273811:: @ 8273811
RustboroCity_DevonCorp_2F_EventScript_273811:: @ 8273811
	msgbox gUnknown_0827331C, MSGBOX_DEFAULT
	release
	end

EventScript_Questionnaire:: @ 827381B
	lockall
	msgbox gUnknown_0827339F, MSGBOX_YESNO
	compare VAR_RESULT, 0
	goto_if_eq EventScript_2738FD
	setvar VAR_0x8004, EASY_CHAT_TYPE_QUESTIONNAIRE
	call Common_ShowEasyChatScreen
	lock
	faceplayer
	specialvar VAR_0x8008, sub_813B490
	compare VAR_0x8004, 1
	goto_if_eq EventScript_27386D
	compare VAR_0x8004, 2
	goto_if_eq EventScript_2738B5
	compare VAR_RESULT, 0
	goto_if_eq EventScript_2738FD
	compare VAR_RESULT, 1
	goto_if_eq EventScript_2738FF
	end

EventScript_27386D:: @ 827386D
	goto_if_unset FLAG_SYS_POKEDEX_GET, EventScript_2738FF
	goto_if_set FLAG_SYS_MYSTERY_EVENT_ENABLE, EventScript_2738FF
	applymovement VAR_0x8008, Common_Movement_FaceDown
	waitmovement 0
	playse SE_PIN
	applymovement VAR_0x8008, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement VAR_0x8008, Common_Movement_Delay48
	waitmovement 0
	msgbox gUnknown_08273506, MSGBOX_DEFAULT
	setflag FLAG_SYS_MYSTERY_EVENT_ENABLE
	msgbox gUnknown_08273559, MSGBOX_DEFAULT
	releaseall
	end

EventScript_2738B5:: @ 82738B5
	goto_if_unset FLAG_SYS_POKEDEX_GET, EventScript_2738FF
	goto_if_set FLAG_SYS_MYSTERY_GIFT_ENABLE, EventScript_2738FF
	applymovement VAR_0x8008, Common_Movement_FaceDown
	waitmovement 0
	playse SE_PIN
	applymovement VAR_0x8008, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement VAR_0x8008, Common_Movement_Delay48
	waitmovement 0
	msgbox gUnknown_08273446, MSGBOX_DEFAULT
	setflag FLAG_SYS_MYSTERY_GIFT_ENABLE
	msgbox gUnknown_082734CC, MSGBOX_DEFAULT
	releaseall
	end

EventScript_2738FD:: @ 82738FD
	releaseall
	end

EventScript_2738FF:: @ 82738FF
	applymovement VAR_0x8008, Common_Movement_FaceDown
	waitmovement 0
	msgbox gUnknown_082733D8, MSGBOX_DEFAULT
	releaseall
	end

UnusualWeather_EventScript_PlaceTilesRoute114North:: @ 8273913
	setmetatile 7, 3, METATILE_Fallarbor_RedCaveEntrance_Top, 1
	setmetatile 7, 4, METATILE_Fallarbor_RedCaveEntrance_Bottom, 0
	return

UnusualWeather_EventScript_PlaceTilesRoute114South:: @ 8273926
	setmetatile 6, 45, METATILE_Fallarbor_BrownCaveEntrance_Top, 1
	setmetatile 6, 46, METATILE_Fallarbor_BrownCaveEntrance_Bottom, 0
	return

UnusualWeather_EventScript_PlaceTilesRoute115West:: @ 8273939
	setmetatile 21, 5, METATILE_Fallarbor_BrownCaveEntrance_Top, 1
	setmetatile 21, 6, METATILE_Fallarbor_BrownCaveEntrance_Bottom, 0
	return

UnusualWeather_EventScript_PlaceTilesRoute115East:: @ 827394C
	setmetatile 36, 9, METATILE_Fallarbor_BrownCaveEntrance_Top, 1
	setmetatile 36, 10, METATILE_Fallarbor_BrownCaveEntrance_Bottom, 0
	return

UnusualWeather_EventScript_PlaceTilesRoute116North:: @ 827395F
	setmetatile 59, 12, METATILE_General_CaveEntrance_Top, 1
	setmetatile 59, 13, METATILE_General_CaveEntrance_Bottom, 0
	return

UnusualWeather_EventScript_PlaceTilesRoute116South:: @ 8273972
	setmetatile 79, 5, METATILE_General_CaveEntrance_Top, 1
	setmetatile 79, 6, METATILE_General_CaveEntrance_Bottom, 0
	return

UnusualWeather_EventScript_PlaceTilesRoute118East:: @ 8273985
	setmetatile 42, 5, METATILE_General_CaveEntrance_Top, 1
	setmetatile 42, 6, METATILE_General_CaveEntrance_Bottom, 0
	return

UnusualWeather_EventScript_PlaceTilesRoute118West:: @ 8273998
	setmetatile 9, 5, METATILE_General_CaveEntrance_Top, 1
	setmetatile 9, 6, METATILE_General_CaveEntrance_Bottom, 0
	return

UnusualWeather_EventScript_PlaceTilesRoute105North:: @ 82739AB
	setmetatile 10, 28, METATILE_General_RoughWater, 0
	setmetatile 11, 28, METATILE_General_RoughWater, 0
	setmetatile 9, 29, METATILE_General_RoughWater, 0
	setmetatile 10, 29, METATILE_General_RoughDeepWater, 0
	setmetatile 11, 29, METATILE_General_RoughDeepWater, 0
	setmetatile 12, 29, METATILE_General_RoughWater, 0
	setmetatile 9, 30, METATILE_General_RoughWater, 0
	setmetatile 10, 30, METATILE_General_RoughDeepWater, 0
	setmetatile 11, 30, METATILE_General_RoughDeepWater, 0
	setmetatile 12, 30, METATILE_General_RoughWater, 0
	setmetatile 10, 31, METATILE_General_RoughWater, 0
	setmetatile 11, 31, METATILE_General_RoughWater, 0
	return

UnusualWeather_EventScript_PlaceTilesRoute105South:: @ 8273A18
	setmetatile 20, 53, METATILE_General_RoughWater, 0
	setmetatile 21, 53, METATILE_General_RoughWater, 0
	setmetatile 19, 54, METATILE_General_RoughWater, 0
	setmetatile 20, 54, METATILE_General_RoughDeepWater, 0
	setmetatile 21, 54, METATILE_General_RoughDeepWater, 0
	setmetatile 22, 54, METATILE_General_RoughWater, 0
	setmetatile 19, 55, METATILE_General_RoughWater, 0
	setmetatile 20, 55, METATILE_General_RoughDeepWater, 0
	setmetatile 21, 55, METATILE_General_RoughDeepWater, 0
	setmetatile 22, 55, METATILE_General_RoughWater, 0
	setmetatile 20, 56, METATILE_General_RoughWater, 0
	setmetatile 21, 56, METATILE_General_RoughWater, 0
	return

UnusualWeather_EventScript_PlaceTilesRoute125West:: @ 8273A85
	setmetatile 8, 16, METATILE_General_RoughWater, 0
	setmetatile 9, 16, METATILE_General_RoughWater, 0
	setmetatile 7, 17, METATILE_General_RoughWater, 0
	setmetatile 8, 17, METATILE_General_RoughDeepWater, 0
	setmetatile 9, 17, METATILE_General_RoughDeepWater, 0
	setmetatile 10, 17, METATILE_General_RoughWater, 0
	setmetatile 7, 18, METATILE_General_RoughWater, 0
	setmetatile 8, 18, METATILE_General_RoughDeepWater, 0
	setmetatile 9, 18, METATILE_General_RoughDeepWater, 0
	setmetatile 10, 18, METATILE_General_RoughWater, 0
	setmetatile 8, 19, METATILE_General_RoughWater, 0
	setmetatile 9, 19, METATILE_General_RoughWater, 0
	return

UnusualWeather_EventScript_PlaceTilesRoute125East:: @ 8273AF2
	setmetatile 53, 18, METATILE_General_RoughWater, 0
	setmetatile 54, 18, METATILE_General_RoughWater, 0
	setmetatile 52, 19, METATILE_General_RoughWater, 0
	setmetatile 53, 19, METATILE_General_RoughDeepWater, 0
	setmetatile 54, 19, METATILE_General_RoughDeepWater, 0
	setmetatile 55, 19, METATILE_General_RoughWater, 0
	setmetatile 52, 20, METATILE_General_RoughWater, 0
	setmetatile 53, 20, METATILE_General_RoughDeepWater, 0
	setmetatile 54, 20, METATILE_General_RoughDeepWater, 0
	setmetatile 55, 20, METATILE_General_RoughWater, 0
	setmetatile 53, 21, METATILE_General_RoughWater, 0
	setmetatile 54, 21, METATILE_General_RoughWater, 0
	return

UnusualWeather_EventScript_PlaceTilesRoute127North:: @ 8273B5F
	setmetatile 57, 9, METATILE_General_RoughWater, 0
	setmetatile 58, 9, METATILE_General_RoughWater, 0
	setmetatile 56, 10, METATILE_General_RoughWater, 0
	setmetatile 57, 10, METATILE_General_RoughDeepWater, 0
	setmetatile 58, 10, METATILE_General_RoughDeepWater, 0
	setmetatile 59, 10, METATILE_General_RoughWater, 0
	setmetatile 56, 11, METATILE_General_RoughWater, 0
	setmetatile 57, 11, METATILE_General_RoughDeepWater, 0
	setmetatile 58, 11, METATILE_General_RoughDeepWater, 0
	setmetatile 59, 11, METATILE_General_RoughWater, 0
	setmetatile 57, 12, METATILE_General_RoughWater, 0
	setmetatile 58, 12, METATILE_General_RoughWater, 0
	return

UnusualWeather_EventScript_PlaceTilesRoute127South:: @ 8273BCC
	setmetatile 61, 30, METATILE_General_RoughWater, 0
	setmetatile 62, 30, METATILE_General_RoughWater, 0
	setmetatile 60, 31, METATILE_General_RoughWater, 0
	setmetatile 61, 31, METATILE_General_RoughDeepWater, 0
	setmetatile 62, 31, METATILE_General_RoughDeepWater, 0
	setmetatile 63, 31, METATILE_General_RoughWater, 0
	setmetatile 60, 32, METATILE_General_RoughWater, 0
	setmetatile 61, 32, METATILE_General_RoughDeepWater, 0
	setmetatile 62, 32, METATILE_General_RoughDeepWater, 0
	setmetatile 63, 32, METATILE_General_RoughWater, 0
	setmetatile 61, 33, METATILE_General_RoughWater, 0
	setmetatile 62, 33, METATILE_General_RoughWater, 0
	return

UnusualWeather_EventScript_PlaceTilesRoute129West:: @ 8273C39
	setmetatile 16, 14, METATILE_General_RoughWater, 0
	setmetatile 17, 14, METATILE_General_RoughWater, 0
	setmetatile 15, 15, METATILE_General_RoughWater, 0
	setmetatile 16, 15, METATILE_General_RoughDeepWater, 0
	setmetatile 17, 15, METATILE_General_RoughDeepWater, 0
	setmetatile 18, 15, METATILE_General_RoughWater, 0
	setmetatile 15, 16, METATILE_General_RoughWater, 0
	setmetatile 16, 16, METATILE_General_RoughDeepWater, 0
	setmetatile 17, 16, METATILE_General_RoughDeepWater, 0
	setmetatile 18, 16, METATILE_General_RoughWater, 0
	setmetatile 16, 17, METATILE_General_RoughWater, 0
	setmetatile 17, 17, METATILE_General_RoughWater, 0
	return

UnusualWeather_EventScript_PlaceTilesRoute129East:: @ 8273CA6
	setmetatile 42, 19, METATILE_General_RoughWater, 0
	setmetatile 43, 19, METATILE_General_RoughWater, 0
	setmetatile 41, 20, METATILE_General_RoughWater, 0
	setmetatile 42, 20, METATILE_General_RoughDeepWater, 0
	setmetatile 43, 20, METATILE_General_RoughDeepWater, 0
	setmetatile 44, 20, METATILE_General_RoughWater, 0
	setmetatile 41, 21, METATILE_General_RoughWater, 0
	setmetatile 42, 21, METATILE_General_RoughDeepWater, 0
	setmetatile 43, 21, METATILE_General_RoughDeepWater, 0
	setmetatile 44, 21, METATILE_General_RoughWater, 0
	setmetatile 42, 22, METATILE_General_RoughWater, 0
	setmetatile 43, 22, METATILE_General_RoughWater, 0
	return

Route105_EventScript_273D13:: @ 8273D13
Route114_EventScript_273D13:: @ 8273D13
Route115_EventScript_273D13:: @ 8273D13
Route116_EventScript_273D13:: @ 8273D13
Route118_EventScript_273D13:: @ 8273D13
Route125_EventScript_273D13:: @ 8273D13
Route127_EventScript_273D13:: @ 8273D13
Route129_EventScript_273D13:: @ 8273D13
	setflag FLAG_HIDE_MAP_NAME_POPUP
	return

UnusualWeather_StartKyogreWeather:: @ 8273D17
	setweather WEATHER_RAIN_HEAVY
	return

UnusualWeather_StartGroudonWeather:: @ 8273D1B
	setweather WEATHER_DROUGHT
	return

UnusualWeather_EventScript_EndEventAndCleanup_1:: @ 8273D1F
	lockall
	compare VAR_UNUSUAL_WEATHER_LOCATION, UNUSUAL_WEATHER_KYOGRE_LOCATIONS_START
	goto_if_ge UnusualWeather_EventScript_ShowRainEndedMessage
	goto UnusualWeather_EventScript_ShowSunEndedMessage
	end

UnusualWeather_EventScript_EndEventAndCleanup_2:: @ 8273D31
	closemessage
	fadescreenswapbuffers 1
	setweather WEATHER_SUNNY
	doweather
	call UnusualWeather_EventScript_CleanupMapTiles
	special DrawWholeMapView
	setvar VAR_UNUSUAL_WEATHER_LOCATION, UNUSUAL_WEATHER_NONE
	setvar VAR_SHOULD_END_UNUSUAL_WEATHER, 0
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	fadescreenswapbuffers 0
	releaseall
	end

UnusualWeather_EventScript_ShowRainEndedMessage:: @ 8273D51
	msgbox gText_UnusualWeatherEnded_Rain, MSGBOX_DEFAULT
	goto UnusualWeather_EventScript_EndEventAndCleanup_2
	end

UnusualWeather_EventScript_ShowSunEndedMessage:: @ 8273D5F
	msgbox gText_UnusualWeatherEnded_Sun, MSGBOX_DEFAULT
	goto UnusualWeather_EventScript_EndEventAndCleanup_2
	end

UnusualWeather_EventScript_CleanupMapTiles:: @ 8273D6D
	switch VAR_UNUSUAL_WEATHER_LOCATION
	case UNUSUAL_WEATHER_ROUTE_114_NORTH, UnusualWeather_EventScript_CleanupRoute114North
	case UNUSUAL_WEATHER_ROUTE_114_SOUTH, UnusualWeather_EventScript_CleanupRoute114South
	case UNUSUAL_WEATHER_ROUTE_115_WEST, UnusualWeather_EventScript_CleanupRoute115West
	case UNUSUAL_WEATHER_ROUTE_115_EAST, UnusualWeather_EventScript_CleanupRoute115East
	case UNUSUAL_WEATHER_ROUTE_116_NORTH, UnusualWeather_EventScript_CleanupRoute116North
	case UNUSUAL_WEATHER_ROUTE_116_SOUTH, UnusualWeather_EventScript_CleanupRoute116South
	case UNUSUAL_WEATHER_ROUTE_118_EAST, UnusualWeather_EventScript_CleanupRoute118East
	case UNUSUAL_WEATHER_ROUTE_118_WEST, UnusualWeather_EventScript_CleanupRoute118West
	case UNUSUAL_WEATHER_ROUTE_105_NORTH, UnusualWeather_EventScript_CleanupRoute105North
	case UNUSUAL_WEATHER_ROUTE_105_SOUTH, UnusualWeather_EventScript_CleanupRoute105South
	case UNUSUAL_WEATHER_ROUTE_125_WEST, UnusualWeather_EventScript_CleanupRoute125West
	case UNUSUAL_WEATHER_ROUTE_125_EAST, UnusualWeather_EventScript_CleanupRoute125East
	case UNUSUAL_WEATHER_ROUTE_127_NORTH, UnusualWeather_EventScript_CleanupRoute127North
	case UNUSUAL_WEATHER_ROUTE_127_SOUTH, UnusualWeather_EventScript_CleanupRoute127South
	case UNUSUAL_WEATHER_ROUTE_129_WEST, UnusualWeather_EventScript_CleanupRoute129West
	case UNUSUAL_WEATHER_ROUTE_129_EAST, UnusualWeather_EventScript_CleanupRoute129East
	return

UnusualWeather_EventScript_CleanupRoute114North:: @ 8273E23
	setmetatile 7, 3, METATILE_Fallarbor_RedRockWall, 1
	setmetatile 7, 4, METATILE_Fallarbor_RedRockWall, 1
	return

UnusualWeather_EventScript_CleanupRoute114South:: @ 8273E36
	setmetatile 6, 45, METATILE_Fallarbor_BrownRockWall, 1
	setmetatile 6, 46, METATILE_Fallarbor_BrownRockWall, 1
	return

UnusualWeather_EventScript_CleanupRoute115West:: @ 8273E49
	setmetatile 21, 5, METATILE_Fallarbor_BrownRockWall, 1
	setmetatile 21, 6, METATILE_Fallarbor_BrownRockWall, 1
	return

UnusualWeather_EventScript_CleanupRoute115East:: @ 8273E5C
	setmetatile 36, 9, METATILE_Fallarbor_BrownRockWall, 1
	setmetatile 36, 10, METATILE_Fallarbor_BrownRockWall, 1
	return

UnusualWeather_EventScript_CleanupRoute116North:: @ 8273E6F
	setmetatile 59, 12, METATILE_General_RockWall_RockBase, 1
	setmetatile 59, 13, METATILE_General_RockWall_RockBase, 1
	return

UnusualWeather_EventScript_CleanupRoute116South:: @ 8273E82
	setmetatile 79, 5, METATILE_General_RockWall_RockBase, 1
	setmetatile 79, 6, METATILE_General_RockWall_RockBase, 1
	return

UnusualWeather_EventScript_CleanupRoute118East:: @ 8273E95
	setmetatile 42, 5, METATILE_General_RockWall_RockBase, 1
	setmetatile 42, 6, METATILE_General_RockWall_GrassBase, 1
	return

UnusualWeather_EventScript_CleanupRoute118West:: @ 8273EA8
	setmetatile 9, 5, METATILE_General_RockWall_RockBase, 1
	setmetatile 9, 6, METATILE_General_RockWall_GrassBase, 1
	return

UnusualWeather_EventScript_CleanupRoute105North:: @ 8273EBB
	setmetatile 10, 28, METATILE_General_CalmWater, 0
	setmetatile 11, 28, METATILE_General_CalmWater, 0
	setmetatile 9, 29, METATILE_General_CalmWater, 0
	setmetatile 10, 29, METATILE_General_CalmWater, 0
	setmetatile 11, 29, METATILE_General_CalmWater, 0
	setmetatile 12, 29, METATILE_General_CalmWater, 0
	setmetatile 9, 30, METATILE_General_CalmWater, 0
	setmetatile 10, 30, METATILE_General_CalmWater, 0
	setmetatile 11, 30, METATILE_General_CalmWater, 0
	setmetatile 12, 30, METATILE_General_CalmWater, 0
	setmetatile 10, 31, METATILE_General_CalmWater, 0
	setmetatile 11, 31, METATILE_General_CalmWater, 0
	return

UnusualWeather_EventScript_CleanupRoute105South:: @ 8273F28
	setmetatile 20, 53, METATILE_General_CalmWater, 0
	setmetatile 21, 53, METATILE_General_CalmWater, 0
	setmetatile 19, 54, METATILE_General_CalmWater, 0
	setmetatile 20, 54, METATILE_General_CalmWater, 0
	setmetatile 21, 54, METATILE_General_CalmWater, 0
	setmetatile 22, 54, METATILE_General_CalmWater, 0
	setmetatile 19, 55, METATILE_General_CalmWater, 0
	setmetatile 20, 55, METATILE_General_CalmWater, 0
	setmetatile 21, 55, METATILE_General_CalmWater, 0
	setmetatile 22, 55, METATILE_General_CalmWater, 0
	setmetatile 20, 56, METATILE_General_CalmWater, 0
	setmetatile 21, 56, METATILE_General_CalmWater, 0
	return

UnusualWeather_EventScript_CleanupRoute125West:: @ 8273F95
	setmetatile 8, 16, METATILE_General_CalmWater, 0
	setmetatile 9, 16, METATILE_General_CalmWater, 0
	setmetatile 7, 17, METATILE_General_CalmWater, 0
	setmetatile 8, 17, METATILE_General_CalmWater, 0
	setmetatile 9, 17, METATILE_General_CalmWater, 0
	setmetatile 10, 17, METATILE_General_CalmWater, 0
	setmetatile 7, 18, METATILE_General_CalmWater, 0
	setmetatile 8, 18, METATILE_General_CalmWater, 0
	setmetatile 9, 18, METATILE_General_CalmWater, 0
	setmetatile 10, 18, METATILE_General_CalmWater, 0
	setmetatile 8, 19, METATILE_General_CalmWater, 0
	setmetatile 9, 19, METATILE_General_CalmWater, 0
	return

UnusualWeather_EventScript_CleanupRoute125East:: @ 8274002
	setmetatile 53, 18, METATILE_General_CalmWater, 0
	setmetatile 54, 18, METATILE_General_CalmWater, 0
	setmetatile 52, 19, METATILE_General_CalmWater, 0
	setmetatile 53, 19, METATILE_General_CalmWater, 0
	setmetatile 54, 19, METATILE_General_CalmWater, 0
	setmetatile 55, 19, METATILE_General_CalmWater, 0
	setmetatile 52, 20, METATILE_General_CalmWater, 0
	setmetatile 53, 20, METATILE_General_CalmWater, 0
	setmetatile 54, 20, METATILE_General_CalmWater, 0
	setmetatile 55, 20, METATILE_General_CalmWater, 0
	setmetatile 53, 21, METATILE_General_CalmWater, 0
	setmetatile 54, 21, METATILE_General_CalmWater, 0
	return

UnusualWeather_EventScript_CleanupRoute127North:: @ 827406F
	setmetatile 57, 9, METATILE_General_CalmWater, 0
	setmetatile 58, 9, METATILE_General_CalmWater, 0
	setmetatile 56, 10, METATILE_General_CalmWater, 0
	setmetatile 57, 10, METATILE_General_CalmWater, 0
	setmetatile 58, 10, METATILE_General_CalmWater, 0
	setmetatile 59, 10, METATILE_General_CalmWater, 0
	setmetatile 56, 11, METATILE_General_CalmWater, 0
	setmetatile 57, 11, METATILE_General_CalmWater, 0
	setmetatile 58, 11, METATILE_General_CalmWater, 0
	setmetatile 59, 11, METATILE_General_CalmWater, 0
	setmetatile 57, 12, METATILE_General_CalmWater, 0
	setmetatile 58, 12, METATILE_General_CalmWater, 0
	return

UnusualWeather_EventScript_CleanupRoute127South:: @ 82740DC
	setmetatile 61, 30, METATILE_General_CalmWater, 0
	setmetatile 62, 30, METATILE_General_CalmWater, 0
	setmetatile 60, 31, METATILE_General_CalmWater, 0
	setmetatile 61, 31, METATILE_General_CalmWater, 0
	setmetatile 62, 31, METATILE_General_CalmWater, 0
	setmetatile 63, 31, METATILE_General_CalmWater, 0
	setmetatile 60, 32, METATILE_General_CalmWater, 0
	setmetatile 61, 32, METATILE_General_CalmWater, 0
	setmetatile 62, 32, METATILE_General_CalmWater, 0
	setmetatile 63, 32, METATILE_General_CalmWater, 0
	setmetatile 61, 33, METATILE_General_CalmWater, 0
	setmetatile 62, 33, METATILE_General_CalmWater, 0
	return

UnusualWeather_EventScript_CleanupRoute129West:: @ 8274149
	setmetatile 16, 14, METATILE_General_CalmWater, 0
	setmetatile 17, 14, METATILE_General_CalmWater, 0
	setmetatile 15, 15, METATILE_General_CalmWater, 0
	setmetatile 16, 15, METATILE_General_CalmWater, 0
	setmetatile 17, 15, METATILE_General_CalmWater, 0
	setmetatile 18, 15, METATILE_General_CalmWater, 0
	setmetatile 15, 16, METATILE_General_CalmWater, 0
	setmetatile 16, 16, METATILE_General_CalmWater, 0
	setmetatile 17, 16, METATILE_General_CalmWater, 0
	setmetatile 18, 16, METATILE_General_CalmWater, 0
	setmetatile 16, 17, METATILE_General_CalmWater, 0
	setmetatile 17, 17, METATILE_General_CalmWater, 0
	return

UnusualWeather_EventScript_CleanupRoute129East:: @ 82741B6
	setmetatile 42, 19, METATILE_General_CalmWater, 0
	setmetatile 43, 19, METATILE_General_CalmWater, 0
	setmetatile 41, 20, METATILE_General_CalmWater, 0
	setmetatile 42, 20, METATILE_General_CalmWater, 0
	setmetatile 43, 20, METATILE_General_CalmWater, 0
	setmetatile 44, 20, METATILE_General_CalmWater, 0
	setmetatile 41, 21, METATILE_General_CalmWater, 0
	setmetatile 42, 21, METATILE_General_CalmWater, 0
	setmetatile 43, 21, METATILE_General_CalmWater, 0
	setmetatile 44, 21, METATILE_General_CalmWater, 0
	setmetatile 42, 22, METATILE_General_CalmWater, 0
	setmetatile 43, 22, METATILE_General_CalmWater, 0
	return

UnusualWeather_Underwater_SetupEscapeWarp:: @ 8274223
	switch VAR_UNUSUAL_WEATHER_LOCATION
	case UNUSUAL_WEATHER_ROUTE_105_NORTH, UnusualWeather_Underwater_SetupEscapeWarpRoute105North
	case UNUSUAL_WEATHER_ROUTE_105_SOUTH, UnusualWeather_Underwater_SetupEscapeWarpRoute105South
	case UNUSUAL_WEATHER_ROUTE_125_WEST, UnusualWeather_Underwater_SetupEscapeWarpRoute125West
	case UNUSUAL_WEATHER_ROUTE_125_EAST, UnusualWeather_Underwater_SetupEscapeWarpRoute125East
	case UNUSUAL_WEATHER_ROUTE_127_NORTH, UnusualWeather_Underwater_SetupEscapeWarpRoute127North
	case UNUSUAL_WEATHER_ROUTE_127_SOUTH, UnusualWeather_Underwater_SetupEscapeWarpRoute127South
	case UNUSUAL_WEATHER_ROUTE_129_WEST, UnusualWeather_Underwater_SetupEscapeWarpRoute129West
	case UNUSUAL_WEATHER_ROUTE_129_EAST, UnusualWeather_Underwater_SetupEscapeWarpRoute129East
	return

UnusualWeather_Underwater_SetupEscapeWarpRoute105North:: @ 8274281
	setescapewarp MAP_ROUTE105, 255, 11, 29
	return

UnusualWeather_Underwater_SetupEscapeWarpRoute105South:: @ 827428A
	setescapewarp MAP_ROUTE105, 255, 21, 54
	return

UnusualWeather_Underwater_SetupEscapeWarpRoute125West:: @ 8274293
	setescapewarp MAP_ROUTE125, 255, 9, 17
	return

UnusualWeather_Underwater_SetupEscapeWarpRoute125East:: @ 827429C
	setescapewarp MAP_ROUTE125, 255, 54, 19
	return

UnusualWeather_Underwater_SetupEscapeWarpRoute127North:: @ 82742A5
	setescapewarp MAP_ROUTE127, 255, 58, 10
	return

UnusualWeather_Underwater_SetupEscapeWarpRoute127South:: @ 82742AE
	setescapewarp MAP_ROUTE127, 255, 62, 31
	return

UnusualWeather_Underwater_SetupEscapeWarpRoute129West:: @ 82742B7
	setescapewarp MAP_ROUTE129, 255, 17, 15
	return

UnusualWeather_Underwater_SetupEscapeWarpRoute129East:: @ 82742C0
	setescapewarp MAP_ROUTE129, 255, 43, 20
	return

Std_RegisteredInMatchCall:: @ 82742C9
	buffertrainerclassname 0, VAR_0x8000
	buffertrainername 1, VAR_0x8000
	closemessage
	delay 30
	playfanfare MUS_ME_TORE_EYE
	msgbox gText_RegisteredTrainerinPokeNav, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	return

EventScript_TryGetTrainerScript:: @ 82742E6
	special ShouldTryGetTrainerScript
	compare VAR_RESULT, 1
	goto_if_eq EventScript_GotoTrainerScript
	releaseall
	end

EventScript_GotoTrainerScript:: @ 82742F6
	gotobeatenscript
	releaseall
	end

	.include "data/scripts/berry_tree.inc"
	.include "data/scripts/secret_base.inc"
	.include "data/scripts/cable_club.inc"
	.include "data/scripts/contest_hall.inc"
	.include "data/text/contest_strings.inc"

gUnknown_0827E8CE:: @ 827E8CE
	.string "Missed turn$"

gText_LinkStandby4:: @ 827E8DA
	.string "连接等待中!$"

gUnknown_0827E8E8:: @ 827E8E8
	.string "优胜者是{STR_VAR_1}的{STR_VAR_2}!\n"
	.string "恭喜!$"

gUnknown_0827E910:: @ 827E910
	.string "优胜者是{STR_VAR_1}的{STR_VAR_2}!{PAUSE_UNTIL_PRESS}$"

gUnknown_0827E929:: @ 827E929
	.string "初步评判: No. {STR_VAR_1}{PAUSE_UNTIL_PRESS}$"

gUnknown_0827E943:: @ 827E943
	.string "二级评判: No. {STR_VAR_1}{PAUSE_UNTIL_PRESS}$"

gUnknown_0827E95F:: @ 827E95F
	.string "Set event: No. {STR_VAR_1}{PAUSE_UNTIL_PRESS}$"

gUnknown_0827E973:: @ 827E973
	.string "这个技能使用率最高:\n"
	.string "{STR_VAR_1}{PAUSE_UNTIL_PRESS}$"

gUnknown_0827E992:: @ 827E992
	.string "最引人注目的宝可梦:\n"
	.string "{STR_VAR_1}的{STR_VAR_2}{PAUSE_UNTIL_PRESS}$"

gUnknown_0827E9B9:: @ 827E9B9
	.string "Set event: No. {STR_VAR_1}{PAUSE_UNTIL_PRESS}$"

gUnknown_0827E9CD:: @ 827E9CD
	.string "由于训练师失败，\n"
	.string "将不会连接电视节目。{PAUSE_UNTIL_PRESS}$"

gUnknown_0827EA0C:: @ 827EA0C
	.string "{STR_VAR_1}\n"
	.string "{STR_VAR_2}的{STR_VAR_3}$"

gUnknown_0827EA17:: @ 827EA17
	.string "比赛$"

gContestRankNormal::
	.string "普通组$"

gContestRankSuper::
	.string "超级组$"

gContestRankHyper::
	.string "专家组$"

gContestRankMaster::
	.string "大师组$"

gContestLink::
	.string "进入$"

gContestCoolness::
	.string "帅气组$"

gContestBeauty::
	.string "美丽组$"

gContestCuteness::
	.string "可爱组$"

gContestSmartness::
	.string "聪明组$"

gContestToughness::
	.string "强壮组$"

gContestPaintingCool1::
	.string "Nonstop supercool--\n"
	.string "the inestimable {STR_VAR_1}$"

gContestPaintingCool2::
	.string "嘿!\n"
	.string "好看的宝可梦{STR_VAR_1}$"

gContestPaintingCool3::
	.string "奇妙，精彩，\n"
	.string "非常棒{STR_VAR_1}$"

gContestPaintingBeauty1::
	.string "本世纪的最后一颗新星--\n"
	.string "美丽的{STR_VAR_1}$"

gContestPaintingBeauty2::
	.string "{STR_VAR_1}的令人眼花缭乱,\n"
	.string "闪闪发光的笑容$"

gContestPaintingBeauty3::
	.string "宝可梦中心的超级偶像--\n"
	.string "无与伦比的{STR_VAR_1}$"

gContestPaintingCute1::
	.string "可爱又甜蜜的{STR_VAR_1}$"

gContestPaintingCute2::
	.string "美丽的{STR_VAR_1}的\n"
	.string "获奖照片$"

gContestPaintingCute3::
	.string "给我们眨个眼!\n"
	.string "可爱的宝可梦{STR_VAR_1}$"

gContestPaintingSmart1::
	.string "智慧大师--\n"
	.string "聪明的宝可梦{STR_VAR_1}$"

gContestPaintingSmart2::
	.string "{STR_VAR_1}，首先\n"
	.string "选择宝可梦$"

gContestPaintingSmart3::
	.string "优秀的{STR_VAR_1}的\n"
	.string "优雅时刻$"

gContestPaintingTough1::
	.string "强壮又\n"
	.string "敏捷的{STR_VAR_1}$"

gContestPaintingTough2::
	.string "The strong, stronger, and\n"
	.string "strongest {STR_VAR_1}$"

gContestPaintingTough3::
	.string "强壮的\n"
	.string "宝可梦{STR_VAR_1}$"

gUnknown_0827ECBC:: @ 27ECBC
	.string "走路草$"

gUnknown_0827ECC3:: @ 27ECC3
	.string "土狼犬$"

gUnknown_0827ECCD:: @ 27ECCD
	.string "傲骨燕$"

gUnknown_0827ECD5:: @ 27ECD5
	.string "露力丽$"

gUnknown_0827ECDD:: @ 27ECDD
	.string "莲叶童子$"

gUnknown_0827ECE3:: @ 27ECE3
	.string "长翅鸥$"

gUnknown_0827ECEB:: @ 27ECEB
	.string "毒粉蛾$"

gUnknown_0827ECF2:: @ 27ECF2
	.string "超音蝠$"

gUnknown_0827ECF8:: @ 27ECF8
	.string "土居忍士$"

gUnknown_0827ED00:: @ 27ED00
	.string "拉鲁拉丝$"

gUnknown_0827ED06:: @ 27ED06
	.string "蛇纹熊$"

gUnknown_0827ED10:: @ 27ED10
	.string "懒人獭$"

gUnknown_0827ED18:: @ 27ED18
	.string "土狼犬$"

gUnknown_0827ED22:: @ 27ED22
	.string "蘑蘑菇$"

gUnknown_0827ED2C:: @ 27ED2C
	.string "蛇纹熊$"

gUnknown_0827ED36:: @ 27ED36
	.string "土狼犬$"

gUnknown_0827ED40:: @ 27ED40
	.string "超音蝠$"

gUnknown_0827ED46:: @ 27ED46
	.string "利牙鱼$"

gUnknown_0827ED4F:: @ 27ED4F
	.string "灼伤药$"

gUnknown_0827ED59:: @ 27ED59
	.string "港口邮件$"

gUnknown_0827ED65:: @ 27ED65
	.string "同样的价格$"

gUnknown_0827ED70:: @ 27ED70
	.string "¥60$"

gUnknown_0827ED74:: @ 27ED74
	.string "¥55$"

gUnknown_0827ED78:: @ 27ED78
	.string "Nothing$"

gUnknown_0827ED80:: @ 27ED80
	.string "They will cost more.$"

gUnknown_0827ED95:: @ 27ED95
	.string "They will cost less.$"

gUnknown_0827EDAA:: @ 27EDAA
	.string "Same price$"

gUnknown_0827EDB5:: @ 27EDB5
	.string "Male$"

gUnknown_0827EDBA:: @ 27EDBA
	.string "Female$"

gUnknown_0827EDC1:: @ 27EDC1
	.string "Neither$"

gUnknown_0827EDC9:: @ 27EDC9
	.string "Elderly men$"

gUnknown_0827EDD5:: @ 27EDD5
	.string "Elderly ladies$"

gUnknown_0827EDE4:: @ 27EDE4
	.string "Same number$"

gUnknown_0827EDF0:: @ 27EDF0
	.string "None$"

gUnknown_0827EDF5:: @ 27EDF5
	.string "1$"

gUnknown_0827EDF7:: @ 27EDF7
	.string "2$"

gUnknown_0827EDF9:: @ 27EDF9
	.string "2$"

gUnknown_0827EDFB:: @ 27EDFB
	.string "3$"

gUnknown_0827EDFD:: @ 27EDFD
	.string "4$"

gUnknown_0827EDFF:: @ 27EDFF
	.string "6$"

gUnknown_0827EE01:: @ 27EE01
	.string "7$"

gUnknown_0827EE03:: @ 27EE03
	.string "8$"

gUnknown_0827EE05:: @ 27EE05
	.string "6$"

gUnknown_0827EE07:: @ 27EE07
	.string "7$"

gUnknown_0827EE09:: @ 27EE09
	.string "8$"

	.include "data/scripts/tv.inc"
	.include "data/text/tv.inc"

BattleFrontier_BattleTowerLobby_EventScript_28C7E9:: @ 828C7E9
LilycoveCity_ContestLobby_EventScript_28C7E9:: @ 828C7E9
SlateportCity_OceanicMuseum_1F_EventScript_28C7E9:: @ 828C7E9
SlateportCity_PokemonFanClub_EventScript_28C7E9:: @ 828C7E9
	special InterviewAfter
	incrementgamestat 6
	release
	end

SlateportCity_PokemonFanClub_EventScript_28C7F0:: @ 828C7F0
	setvar VAR_0x8005, 1
	special InterviewBefore
	compare VAR_RESULT, 1
	goto_if_eq SlateportCity_PokemonFanClub_EventScript_28C879
	copyvar VAR_0x8009, VAR_0x8006
	msgbox SlateportCity_PokemonFanClub_Text_280674, MSGBOX_YESNO
	compare VAR_RESULT, 1
	goto_if_eq SlateportCity_PokemonFanClub_EventScript_28C827
	compare VAR_RESULT, 0
	goto_if_eq SlateportCity_PokemonFanClub_EventScript_28C85C
	end

SlateportCity_PokemonFanClub_EventScript_28C827:: @ 828C827
	msgbox SlateportCity_PokemonFanClub_Text_28073B, MSGBOX_DEFAULT
	setvar VAR_0x8004, EASY_CHAT_TYPE_INTERVIEW
	copyvar VAR_0x8005, VAR_0x8009
	setvar VAR_0x8006, EASY_CHAT_PERSON_REPORTER_FEMALE
	call Common_ShowEasyChatScreen
	lock
	faceplayer
	compare VAR_RESULT, 1
	goto_if_eq SlateportCity_PokemonFanClub_EventScript_28C866
	compare VAR_RESULT, 0
	goto_if_eq SlateportCity_PokemonFanClub_EventScript_28C85C
	end

SlateportCity_PokemonFanClub_EventScript_28C85C:: @ 828C85C
	msgbox SlateportCity_PokemonFanClub_Text_2805E2, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_28C866:: @ 828C866
	msgbox SlateportCity_PokemonFanClub_Text_280789, MSGBOX_DEFAULT
	setvar VAR_0x8005, 1
	goto SlateportCity_PokemonFanClub_EventScript_28C7E9
	end

SlateportCity_PokemonFanClub_EventScript_28C879:: @ 828C879
	msgbox SlateportCity_PokemonFanClub_Text_28062E, MSGBOX_DEFAULT
	release
	end

SlateportCity_OceanicMuseum_1F_EventScript_28C883:: @ 828C883
	lock
	faceplayer
	setvar VAR_0x8005, 2
	special InterviewBefore
	compare VAR_RESULT, 1
	goto_if_eq SlateportCity_OceanicMuseum_1F_EventScript_28C939
	copyvar VAR_0x8009, VAR_0x8006
	goto_if_set FLAG_OCEANIC_MUSEUM_MET_REPORTER, SlateportCity_OceanicMuseum_1F_EventScript_28C8C8
	setflag FLAG_OCEANIC_MUSEUM_MET_REPORTER
	msgbox SlateportCity_OceanicMuseum_1F_Text_2811A0, MSGBOX_YESNO
	compare VAR_RESULT, 1
	goto_if_eq SlateportCity_OceanicMuseum_1F_EventScript_28C8E7
	compare VAR_RESULT, 0
	goto_if_eq SlateportCity_OceanicMuseum_1F_EventScript_28C91C
	end

SlateportCity_OceanicMuseum_1F_EventScript_28C8C8:: @ 828C8C8
	msgbox SlateportCity_OceanicMuseum_1F_Text_28126D, MSGBOX_YESNO
	compare VAR_RESULT, 1
	goto_if_eq SlateportCity_OceanicMuseum_1F_EventScript_28C8E7
	compare VAR_RESULT, 0
	goto_if_eq SlateportCity_OceanicMuseum_1F_EventScript_28C91C
	end

SlateportCity_OceanicMuseum_1F_EventScript_28C8E7:: @ 828C8E7
	msgbox SlateportCity_OceanicMuseum_1F_Text_2812F2, MSGBOX_DEFAULT
	setvar VAR_0x8004, EASY_CHAT_TYPE_INTERVIEW
	copyvar VAR_0x8005, VAR_0x8009
	setvar VAR_0x8006, EASY_CHAT_PERSON_REPORTER_MALE
	call Common_ShowEasyChatScreen
	lock
	faceplayer
	compare VAR_RESULT, 1
	goto_if_eq SlateportCity_OceanicMuseum_1F_EventScript_28C926
	compare VAR_RESULT, 0
	goto_if_eq SlateportCity_OceanicMuseum_1F_EventScript_28C91C
	end

SlateportCity_OceanicMuseum_1F_EventScript_28C91C:: @ 828C91C
	msgbox SlateportCity_OceanicMuseum_1F_Text_281367, MSGBOX_DEFAULT
	release
	end

SlateportCity_OceanicMuseum_1F_EventScript_28C926:: @ 828C926
	msgbox SlateportCity_OceanicMuseum_1F_Text_2813B9, MSGBOX_DEFAULT
	setvar VAR_0x8005, 2
	goto SlateportCity_OceanicMuseum_1F_EventScript_28C7E9
	end

SlateportCity_OceanicMuseum_1F_EventScript_28C939:: @ 828C939
	msgbox SlateportCity_OceanicMuseum_1F_Text_28144D, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_28C943:: @ 828C943
	lock
	faceplayer
	specialvar VAR_RESULT, sub_80EF8F8
	compare VAR_RESULT, 0
	goto_if_eq SlateportCity_PokemonFanClub_EventScript_28C7F0
	setvar VAR_0x8005, 3
	special InterviewBefore
	compare VAR_RESULT, 1
	goto_if_eq SlateportCity_PokemonFanClub_EventScript_28CA4F
	copyvar VAR_0x8009, VAR_0x8006
	msgbox SlateportCity_PokemonFanClub_Text_280270, MSGBOX_YESNO
	compare VAR_RESULT, 1
	goto_if_eq SlateportCity_PokemonFanClub_EventScript_28C98C
	compare VAR_RESULT, 0
	goto_if_eq SlateportCity_PokemonFanClub_EventScript_28CA45
	end

SlateportCity_PokemonFanClub_EventScript_28C98C:: @ 828C98C
	msgbox SlateportCity_PokemonFanClub_Text_28034F, MSGBOX_DEFAULT
	random 3
	copyvar VAR_0x800A, VAR_RESULT
	switch VAR_RESULT
	case 0, SlateportCity_PokemonFanClub_EventScript_28C9C3
	case 1, SlateportCity_PokemonFanClub_EventScript_28C9D1
	case 2, SlateportCity_PokemonFanClub_EventScript_28C9DF
	end

SlateportCity_PokemonFanClub_EventScript_28C9C3:: @ 828C9C3
	msgbox SlateportCity_PokemonFanClub_Text_280393, MSGBOX_DEFAULT
	goto SlateportCity_PokemonFanClub_EventScript_28C9ED
	end

SlateportCity_PokemonFanClub_EventScript_28C9D1:: @ 828C9D1
	msgbox SlateportCity_PokemonFanClub_Text_2803EF, MSGBOX_DEFAULT
	goto SlateportCity_PokemonFanClub_EventScript_28C9ED
	end

SlateportCity_PokemonFanClub_EventScript_28C9DF:: @ 828C9DF
	msgbox SlateportCity_PokemonFanClub_Text_280454, MSGBOX_DEFAULT
	goto SlateportCity_PokemonFanClub_EventScript_28C9ED
	end

SlateportCity_PokemonFanClub_EventScript_28C9ED:: @ 828C9ED
	setvar VAR_0x8004, EASY_CHAT_TYPE_FAN_CLUB
	copyvar VAR_0x8005, VAR_0x8009
	setvar VAR_0x8006, 0
	call Common_ShowEasyChatScreen
	lock
	faceplayer
	compare VAR_RESULT, 0
	goto_if_eq SlateportCity_PokemonFanClub_EventScript_28CA45
	msgbox SlateportCity_PokemonFanClub_Text_2804AC, MSGBOX_DEFAULT
	setvar VAR_0x8006, 1
	call Common_ShowEasyChatScreen
	lock
	faceplayer
	compare VAR_RESULT, 0
	goto_if_eq SlateportCity_PokemonFanClub_EventScript_28CA45
	msgbox SlateportCity_PokemonFanClub_Text_280523, MSGBOX_DEFAULT
	copyvar VAR_0x8007, VAR_0x800A
	setvar VAR_0x8005, 3
	goto SlateportCity_PokemonFanClub_EventScript_28C7E9
	end

SlateportCity_PokemonFanClub_EventScript_28CA45:: @ 828CA45
	msgbox SlateportCity_PokemonFanClub_Text_2805E2, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_28CA4F:: @ 828CA4F
	msgbox SlateportCity_PokemonFanClub_Text_28062E, MSGBOX_DEFAULT
	release
	end

LilycoveCity_ContestLobby_EventScript_28CA59:: @ 828CA59
	lock
	faceplayer
	goto_if_set FLAG_TEMP_2, LilycoveCity_ContestLobby_EventScript_28CB21
	setvar VAR_0x8005, 6
	special InterviewBefore
	compare VAR_RESULT, 1
	goto_if_eq LilycoveCity_ContestLobby_EventScript_28CB21
	copyvar VAR_0x8009, VAR_0x8006
	msgbox LilycoveCity_ContestLobby_Text_27EF15, MSGBOX_YESNO
	compare VAR_RESULT, 1
	goto_if_eq LilycoveCity_ContestLobby_EventScript_28CA9B
	compare VAR_RESULT, 0
	goto_if_eq LilycoveCity_ContestLobby_EventScript_28CAD0
	end

LilycoveCity_ContestLobby_EventScript_28CA9B:: @ 828CA9B
	msgbox LilycoveCity_ContestLobby_Text_27EFE7, MSGBOX_DEFAULT
	setvar VAR_0x8004, EASY_CHAT_TYPE_CONTEST_INTERVIEW
	copyvar VAR_0x8005, VAR_0x8009
	setvar VAR_0x8006, 0
	call Common_ShowEasyChatScreen
	lock
	faceplayer
	compare VAR_RESULT, 1
	goto_if_eq LilycoveCity_ContestLobby_EventScript_28CADA
	compare VAR_RESULT, 0
	goto_if_eq LilycoveCity_ContestLobby_EventScript_28CAD0
	end

LilycoveCity_ContestLobby_EventScript_28CAD0:: @ 828CAD0
	msgbox LilycoveCity_ContestLobby_Text_27F1EF, MSGBOX_DEFAULT
	release
	end

LilycoveCity_ContestLobby_EventScript_28CADA:: @ 828CADA
	setvar VAR_0x8004, 24
	special SetContestCategoryStringVarForInterview
	msgbox LilycoveCity_ContestLobby_Text_27F03E, MSGBOX_DEFAULT
	setvar VAR_0x8004, EASY_CHAT_TYPE_CONTEST_INTERVIEW
	copyvar VAR_0x8005, VAR_0x8009
	setvar VAR_0x8006, 1
	call Common_ShowEasyChatScreen
	lock
	faceplayer
	compare VAR_RESULT, 0
	goto_if_eq LilycoveCity_ContestLobby_EventScript_28CAD0
	msgbox LilycoveCity_ContestLobby_Text_27F0EC, MSGBOX_DEFAULT
	setflag FLAG_TEMP_2
	setvar VAR_0x8005, 6
	goto LilycoveCity_ContestLobby_EventScript_28C7E9
	end

LilycoveCity_ContestLobby_EventScript_28CB21:: @ 828CB21
	msgbox LilycoveCity_ContestLobby_Text_27F23F, MSGBOX_DEFAULT
	release
	end

LilycoveCity_ContestLobby_EventScript_28CB2B:: @ 828CB2B
	compare VAR_LINK_CONTEST_ROOM_STATE, 2
	goto_if_ne LilycoveCity_ContestLobby_EventScript_28CB95
	setvar VAR_0x8005, 6
	special InterviewBefore
	compare VAR_RESULT, 1
	goto_if_eq LilycoveCity_ContestLobby_EventScript_28CB95
	switch VAR_CONTEST_LOCATION
	case 0, LilycoveCity_ContestLobby_EventScript_28CB95
	case 2, LilycoveCity_ContestLobby_EventScript_28CB91
	case 1, LilycoveCity_ContestLobby_EventScript_28CB91
	case 3, LilycoveCity_ContestLobby_EventScript_28CB91
	case 4, LilycoveCity_ContestLobby_EventScript_28CB91
	case 5, LilycoveCity_ContestLobby_EventScript_28CB95
	end

LilycoveCity_ContestLobby_EventScript_28CB91:: @ 828CB91
	clearflag FLAG_HIDE_LILYCOVE_CONTEST_HALL_REPORTER
	return

LilycoveCity_ContestLobby_EventScript_28CB95:: @ 828CB95
	return

BattleFrontier_BattleTowerLobby_EventScript_28CB96:: @ 828CB96
	lock
	faceplayer
	goto_if_set FLAG_TEMP_2, BattleFrontier_BattleTowerLobby_EventScript_28CC7A
	setvar VAR_0x8005, 7
	special InterviewBefore
	compare VAR_RESULT, 1
	goto_if_eq BattleFrontier_BattleTowerLobby_EventScript_28CC7A
	copyvar VAR_0x8009, VAR_0x8006
	msgbox BattleFrontier_BattleTowerLobby_Text_27F704, MSGBOX_YESNO
	compare VAR_RESULT, 1
	goto_if_eq BattleFrontier_BattleTowerLobby_EventScript_28CBD8
	compare VAR_RESULT, 0
	goto_if_eq BattleFrontier_BattleTowerLobby_EventScript_28CC2E
	end

BattleFrontier_BattleTowerLobby_EventScript_28CBD8:: @ 828CBD8
	message BattleFrontier_BattleTowerLobby_Text_27F7BA
	waitmessage
	multichoice 20, 8, 45, 1
	copyvar VAR_0x8008, VAR_RESULT
	compare VAR_RESULT, 0
	call_if_eq BattleFrontier_BattleTowerLobby_EventScript_28CC38
	compare VAR_RESULT, 1
	call_if_eq BattleFrontier_BattleTowerLobby_EventScript_28CC41
	msgbox BattleFrontier_BattleTowerLobby_Text_27F97A, MSGBOX_DEFAULT
	setvar VAR_0x8004, EASY_CHAT_TYPE_BATTLE_TOWER_INTERVIEW
	copyvar VAR_0x8005, VAR_0x8009
	call Common_ShowEasyChatScreen
	lock
	faceplayer
	compare VAR_RESULT, 1
	goto_if_eq BattleFrontier_BattleTowerLobby_EventScript_28CC4A
	compare VAR_RESULT, 0
	goto_if_eq BattleFrontier_BattleTowerLobby_EventScript_28CC70
	end

BattleFrontier_BattleTowerLobby_EventScript_28CC2E:: @ 828CC2E
	msgbox BattleFrontier_BattleTowerLobby_Text_27F84C, MSGBOX_DEFAULT
	release
	end

BattleFrontier_BattleTowerLobby_EventScript_28CC38:: @ 828CC38
	msgbox BattleFrontier_BattleTowerLobby_Text_27F8AE, MSGBOX_DEFAULT
	return

BattleFrontier_BattleTowerLobby_EventScript_28CC41:: @ 828CC41
	msgbox BattleFrontier_BattleTowerLobby_Text_27F921, MSGBOX_DEFAULT
	return

BattleFrontier_BattleTowerLobby_EventScript_28CC4A:: @ 828CC4A
	compare VAR_RESULT, 0
	goto_if_eq BattleFrontier_BattleTowerLobby_EventScript_28CC70
	msgbox BattleFrontier_BattleTowerLobby_Text_27F9FD, MSGBOX_DEFAULT
	setflag FLAG_TEMP_2
	copyvar VAR_0x8004, VAR_0x8008
	setvar VAR_0x8005, 7
	goto BattleFrontier_BattleTowerLobby_EventScript_28C7E9
	end

BattleFrontier_BattleTowerLobby_EventScript_28CC70:: @ 828CC70
	msgbox BattleFrontier_BattleTowerLobby_Text_27FA6F, MSGBOX_DEFAULT
	release
	end

BattleFrontier_BattleTowerLobby_EventScript_28CC7A:: @ 828CC7A
	msgbox BattleFrontier_BattleTowerLobby_Text_27FAF3, MSGBOX_DEFAULT
	release
	end

BattleFrontier_BattleTowerLobby_EventScript_28CC84:: @ 828CC84
	compare VAR_BRAVO_TRAINER_BATTLE_TOWER_ON, 0
	goto_if_eq BattleFrontier_BattleTowerLobby_EventScript_28CCA6
	setvar VAR_0x8005, 7
	special InterviewBefore
	compare VAR_RESULT, 1
	goto_if_eq BattleFrontier_BattleTowerLobby_EventScript_28CCA6
	clearflag FLAG_HIDE_BATTLE_TOWER_REPORTER
	return

BattleFrontier_BattleTowerLobby_EventScript_28CCA6:: @ 828CCA6
	setflag FLAG_HIDE_BATTLE_TOWER_REPORTER
	return

	.include "data/scripts/gabby_and_ty.inc"
	.include "data/text/pokemon_news.inc"
	.include "data/scripts/mauville_man.inc"
	.include "data/scripts/field_move_scripts.inc"
	.include "data/scripts/item_ball_scripts.inc"
	.include "data/scripts/mystery_event_club.inc"
	.include "data/scripts/day_care.inc"

EventScript_2926F8:: @ 82926F8
	animateflash 1
	setflashradius 1
	end

	.include "data/scripts/players_house.inc"

EventScript_RunningShoesManual:: @ 8292DE5
	msgbox LittlerootTown_BrendansHouse_1F_Text_1F7F66, MSGBOX_SIGN
	end

	.include "data/scripts/pokeblocks.inc"

gText_SoPretty:: @ 8294295
	.string "真漂亮!$"

gText_SoDarling:: @ 82942A1
	.string "亲爱的!$"

gText_SoRelaxed:: @ 82942AE
	.string "太放松了!$"

gText_SoSunny:: @ 82942BB
	.string "太阳光了!$"

gText_SoDesirable:: @ 82942C6
	.string "非常可取!$"

gText_SoExciting:: @ 82942D5
	.string "如此令人兴奋!$"

gText_SoAmusing:: @ 82942E3
	.string "太有趣了!$"

gText_SoMagical:: @ 82942F0
	.string "太神奇了!$"

gOtherText_Is:: @ 82942FD
	.string "是$"

gOtherText_DontYouAgree:: @ 8294301
	.string "\n"
	.string "你不同意吗?$"

gMauvilleManText_ISoWantToGoOnAVacation:: @ 8294313
	.string "我很想去度假。\n"
	.string "你知道哪些好地方吗?$"

gMauvilleManText_IBoughtCrayonsWith120Colors:: @ 8294359
	.string "我买了120种颜色的蜡笔!\n"
	.string "难道你不觉得这很好吗?$"

gMauvilleManText_WouldntItBeNiceIfWeCouldFloat:: @ 8294398
	.string "如果我们可以漂浮在一团\n"
	.string "泡沫上，那不是很好?$"

gMauvilleManText_WhenYouWriteOnASandyBeach:: @ 82943DA
	.string "当你在沙滩上写字时,\n"
	.string "它们会被冲掉，这让我很难过。$"

gMauvilleManText_WhatsTheBottomOfTheSeaLike:: @ 829441C
	.string "海底是什么样的呢?\n"
	.string "我曾经看到过!$"

gMauvilleManText_WhenYouSeeTheSettingSunDoesIt:: @ 8294460
	.string "当你看到夕阳时，\n"
	.string "你会想回家吗?$"

gMauvilleManText_LyingBackInTheGreenGrass:: @ 82944A0
	.string "躺在草丛中…\n"
	.string "感觉真是太棒了!$"

gMauvilleManText_SecretBasesAreSoWonderful:: @ 82944D5
	.string "秘密基地太棒了!\n"
	.string "你能感受到我的这种兴奋吗?$"

	.include "data/text/trainers.inc"

EventScript_RepelWoreOff:: @ 82A4B2A
	msgbox Text_RepelWoreOff, MSGBOX_SIGN
	checkitem ITEM_REPEL, 1
	compare VAR_RESULT, TRUE
	goto_if_eq EventScript_RepelWoreOff_AskAnother
	checkitem ITEM_SUPER_REPEL, 1
	compare VAR_RESULT, TRUE
	goto_if_eq EventScript_RepelWoreOff_AskAnother
	checkitem ITEM_MAX_REPEL, 1
	compare VAR_RESULT, FALSE
	goto_if_eq EventScript_RepelWoreOff_End
EventScript_RepelWoreOff_AskAnother:
	msgbox Text_RepelAskAnother, MSGBOX_YESNO
	closemessage
	compare VAR_RESULT, 0
	goto_if_eq EventScript_RepelWoreOff_End
	callnative TryDrawRepelMenu
	compare VAR_RESULT, FALSE
	goto_if_eq EventScript_RepelWoreOff_Chose
	waitstate
	compare VAR_RESULT, 127
	goto_if_eq EventScript_RepelWoreOff_End
EventScript_RepelWoreOff_Chose:
	callnative HandleRepelMenuChoice
	bufferitemname 1, VAR_0x8004
	takeitem VAR_0x8004, 1
	playse SE_TU_SAA
	msgbox gText_PlayerUsedVar2, MSGBOX_SIGN
EventScript_RepelWoreOff_End:
	end

Text_RepelWoreOff: @ 82A4B33
	.string "除虫喷雾的效果消失了…$"
Text_RepelAskAnother:
	.string "使用另一个吗？$"

	.include "data/scripts/safari_zone.inc"

MauvilleCity_GameCorner_EventScript_2A5AB1:: @ 82A5AB1
	checkitem ITEM_COIN_CASE, 1
	compare VAR_RESULT, 0
	goto_if_eq MauvilleCity_GameCorner_EventScript_210456
	setvar VAR_0x8004, 0
	getpricereduction 2
	compare VAR_RESULT, 0
	goto_if_eq MauvilleCity_GameCorner_EventScript_2A5B0D
	addvar VAR_0x8004, 128
	goto MauvilleCity_GameCorner_EventScript_2A5B0D
	end

MauvilleCity_GameCorner_EventScript_2A5ADF:: @ 82A5ADF
	checkitem ITEM_COIN_CASE, 1
	compare VAR_RESULT, 0
	goto_if_eq MauvilleCity_GameCorner_EventScript_210456
	setvar VAR_0x8004, 1
	getpricereduction 2
	compare VAR_RESULT, 0
	goto_if_eq MauvilleCity_GameCorner_EventScript_2A5B0D
	addvar VAR_0x8004, 128
	goto MauvilleCity_GameCorner_EventScript_2A5B0D
	end

MauvilleCity_GameCorner_EventScript_2A5B0D:: @ 82A5B0D
	special PlayRoulette
	waitstate
	end

	.include "data/text/roulette.inc"
	.include "data/text/pokedex_rating.inc"
	.include "data/text/lottery_corner.inc"
	.include "data/text/eon_ticket.inc"
	.include "data/text/braille.inc"
	.include "data/text/berries.inc"
	.include "data/text/shoal_cave.inc"

Text_PictureBookShelf: @ 82A81E5
	.string "这里有一套宝可梦图画书。$"

Text_BookShelf: @ 82A820D
	.string "装满了各种各样的书籍。$"

Text_PokemonCenterBookShelf: @ 82A8232
	.string "宝可梦杂志!\n"
	.string "POKéMON PAL…\p"
	.string "宝可梦手册…\n"
	.string "可爱的宝可梦…$"

Text_Vase: @ 82A8276
	.string "这个花瓶看起来很贵重…\n"
	.string "查看下里面…\p"
	.string "它是空的。$"

Text_EmptyTrashCan: @ 82A82B3
	.string "它是空的。$"

Text_ShopShelf: @ 82A82BF
	.string "货架上摆满了各式各样的\n"
	.string "宝可梦商品。$"

Text_Blueprint: @ 82A82F7
	.string "好像是某种东西的图纸?\n"
	.string "这太复杂了!$"

GraniteCave_B1F_MapScript2_2A8327: @ 82A8327
MirageTower_2F_MapScript2_2A8327: @ 82A8327
MirageTower_3F_MapScript2_2A8327: @ 82A8327
MtPyre_2F_MapScript2_2A8327: @ 82A8327
SkyPillar_2F_MapScript2_2A8327: @ 82A8327
SkyPillar_4F_MapScript2_2A8327: @ 82A8327
	map_script_2 VAR_ICE_STEP_COUNT, 0, EventScript_FallDownHole
	.2byte 0

GraniteCave_B1F_MapScript1_2A8331: @ 82A8331
MirageTower_2F_MapScript1_2A8331: @ 82A8331
MirageTower_3F_MapScript1_2A8331: @ 82A8331
MtPyre_2F_MapScript1_2A8331: @ 82A8331
	copyvar VAR_ICE_STEP_COUNT, 0x1
	end

EventScript_FallDownHole:: @ 82A8337
	lockall
	delay 20
	applymovement EVENT_OBJ_ID_PLAYER, GraniteCave_B1F_Movement_2A8369
	waitmovement 0
	playse SE_RU_HYUU
	delay 60
	warphole MAP_UNDEFINED
	waitstate
	end

gUnknown_082A8350:: @ 82A8350
	lockall
	delay 20
	applymovement EVENT_OBJ_ID_PLAYER, GraniteCave_B1F_Movement_2A8369
	waitmovement 0
	playse SE_RU_HYUU
	delay 60
	special DoFallWarp
	waitstate
	end

GraniteCave_B1F_Movement_2A8369: @ 82A8369
	set_invisible
	step_end

LilycoveCity_PokemonCenter_1F_EventScript_2A836B:: @ 82A836B
	special Script_GetLilycoveLadyId
	switch VAR_RESULT
	case LILYCOVE_LADY_QUIZ, LilycoveCity_PokemonCenter_1F_EventScript_2A8554
	case LILYCOVE_LADY_FAVOR, LilycoveCity_PokemonCenter_1F_EventScript_2A8395
	case LILYCOVE_LADY_CONTEST, LilycoveCity_PokemonCenter_1F_EventScript_2A882A
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A8395:: @ 82A8395
	lock
	faceplayer
	msgbox LilycoveCity_PokemonCenter_1F_Text_2A8A69, MSGBOX_DEFAULT
	specialvar VAR_RESULT, GetFavorLadyState
	compare VAR_RESULT, LILYCOVE_LADY_STATE_READY
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A83D0
	compare VAR_RESULT, LILYCOVE_LADY_STATE_COMPLETED
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A83C6
	compare VAR_RESULT, LILYCOVE_LADY_STATE_PRIZE
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A8510
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A83C6:: @ 82A83C6
	msgbox LilycoveCity_PokemonCenter_1F_Text_2A8AB1, MSGBOX_DEFAULT
	release
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A83D0:: @ 82A83D0
	special BufferFavorLadyRequest
	msgbox LilycoveCity_PokemonCenter_1F_Text_2A8A7D, MSGBOX_DEFAULT
	specialvar VAR_RESULT, HasAnotherPlayerGivenFavorLadyItem
	compare VAR_RESULT, 0
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A8435
	compare VAR_RESULT, 1
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A83F7
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A83F7:: @ 82A83F7
	special BufferFavorLadyItemName
	special BufferFavorLadyPlayerName
	specialvar VAR_RESULT, DidFavorLadyLikeItem
	compare VAR_RESULT, 0
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A8419
	compare VAR_RESULT, 1
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A8427
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A8419:: @ 82A8419
	msgbox LilycoveCity_PokemonCenter_1F_Text_2A8ACE, MSGBOX_DEFAULT
	goto LilycoveCity_PokemonCenter_1F_EventScript_2A8435
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A8427:: @ 82A8427
	msgbox LilycoveCity_PokemonCenter_1F_Text_2A8B36, MSGBOX_DEFAULT
	goto LilycoveCity_PokemonCenter_1F_EventScript_2A8435
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A8435:: @ 82A8435
	msgbox LilycoveCity_PokemonCenter_1F_Text_2A8B69, MSGBOX_YESNO
	compare VAR_RESULT, 0
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A8454
	compare VAR_RESULT, 1
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A845E
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A8454:: @ 82A8454
	msgbox LilycoveCity_PokemonCenter_1F_Text_2A8BCD, MSGBOX_DEFAULT
	release
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A845E:: @ 82A845E
	msgbox LilycoveCity_PokemonCenter_1F_Text_2A8BAD, MSGBOX_DEFAULT
	goto LilycoveCity_PokemonCenter_1F_EventScript_2A846C
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A846C:: @ 82A846C
	fadescreen 1
	setvar VAR_RESULT, 0
	special Script_FavorLadyOpenBagMenu
	waitstate
	compare VAR_RESULT, 0
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A848E
	compare VAR_RESULT, 1
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A84AD
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A848E:: @ 82A848E
	msgbox LilycoveCity_PokemonCenter_1F_Text_2A8BEE, MSGBOX_YESNO
	compare VAR_RESULT, 1
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A8454
	compare VAR_RESULT, 0
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A846C
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A84AD:: @ 82A84AD
	specialvar VAR_RESULT, Script_DoesFavorLadyLikeItem
	compare VAR_RESULT, 0
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A84C9
	compare VAR_RESULT, 1
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A84D6
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A84C9:: @ 82A84C9
	special BufferFavorLadyRequest
	msgbox LilycoveCity_PokemonCenter_1F_Text_2A8C0F, MSGBOX_DEFAULT
	release
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A84D6:: @ 82A84D6
	specialvar VAR_RESULT, IsFavorLadyThresholdMet
	compare VAR_RESULT, 0
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A84F2
	compare VAR_RESULT, 1
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A84FF
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A84F2:: @ 82A84F2
	special BufferFavorLadyRequest
	msgbox LilycoveCity_PokemonCenter_1F_Text_2A8C6F, MSGBOX_DEFAULT
	release
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A84FF:: @ 82A84FF
	special BufferFavorLadyRequest
	msgbox LilycoveCity_PokemonCenter_1F_Text_2A8CC8, MSGBOX_DEFAULT
	goto LilycoveCity_PokemonCenter_1F_EventScript_2A8510
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A8510:: @ 82A8510
	setvar VAR_0x8004, 0
	specialvar VAR_0x8004, FavorLadyGetPrize
	msgbox LilycoveCity_PokemonCenter_1F_Text_2A8D5D, MSGBOX_DEFAULT
	giveitem_std VAR_0x8004
	compare VAR_RESULT, 0
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A8545
	compare VAR_RESULT, 1
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A854F
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A8545:: @ 82A8545
	msgbox LilycoveCity_PokemonCenter_1F_Text_2A8DBD, MSGBOX_DEFAULT
	release
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A854F:: @ 82A854F
	special SetFavorLadyState_Complete
	release
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A8554:: @ 82A8554
	lock
	faceplayer
	msgbox LilycoveCity_PokemonCenter_1F_Text_2A8E2B, MSGBOX_DEFAULT
	specialvar VAR_RESULT, GetQuizLadyState
	compare VAR_RESULT, LILYCOVE_LADY_STATE_READY
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A8585
	compare VAR_RESULT, LILYCOVE_LADY_STATE_COMPLETED
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A85AC
	compare VAR_RESULT, LILYCOVE_LADY_STATE_PRIZE
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A86EC
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A8585:: @ 82A8585
	specialvar VAR_RESULT, GetQuizAuthor
	compare VAR_RESULT, QUIZ_AUTHOR_PLAYER
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A85C8
	compare VAR_RESULT, QUIZ_AUTHOR_OTHER_PLAYER
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A85D2
	compare VAR_RESULT, QUIZ_AUTHOR_LADY
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A85E0
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A85AC:: @ 82A85AC
	specialvar VAR_RESULT, IsQuizLadyWaitingForChallenger
	compare VAR_RESULT, 0
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A8759
	compare VAR_RESULT, 1
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A85C8
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A85C8:: @ 82A85C8
	msgbox LilycoveCity_PokemonCenter_1F_Text_2A8E4E, MSGBOX_DEFAULT
	release
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A85D2:: @ 82A85D2
	msgbox LilycoveCity_PokemonCenter_1F_Text_2A8EAC, MSGBOX_DEFAULT
	goto LilycoveCity_PokemonCenter_1F_EventScript_2A85EE
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A85E0:: @ 82A85E0
	msgbox LilycoveCity_PokemonCenter_1F_Text_2A8EAC, MSGBOX_DEFAULT
	goto LilycoveCity_PokemonCenter_1F_EventScript_2A85EE
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A85EE:: @ 82A85EE
	setvar VAR_0x8004, 0
	msgbox LilycoveCity_PokemonCenter_1F_Text_2A8EEC, MSGBOX_YESNO
	compare VAR_RESULT, 1
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A861C
	compare VAR_RESULT, 0
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A8612
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A8612:: @ 82A8612
	msgbox LilycoveCity_PokemonCenter_1F_Text_2A8F65, MSGBOX_DEFAULT
	release
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A861C:: @ 82A861C
	special ClearQuizLadyPlayerAnswer
	compare VAR_0x8004, 0
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A864C
	compare VAR_0x8004, EASY_CHAT_TYPE_QUIZ_ANSWER
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A8656

LilycoveCity_PokemonCenter_1F_EventScript_2A8635:: @ 82A8635
	compare VAR_RESULT, 0
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A8660
	compare VAR_RESULT, 1
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A8689
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A864C:: @ 82A864C
	special QuizLadyShowQuizQuestion
	waitstate
	goto LilycoveCity_PokemonCenter_1F_EventScript_2A8635
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A8656:: @ 82A8656
	special QuizLadyGetPlayerAnswer
	waitstate
	goto LilycoveCity_PokemonCenter_1F_EventScript_2A8635
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A8660:: @ 82A8660
	msgbox LilycoveCity_PokemonCenter_1F_Text_2A8F7E, MSGBOX_YESNO
	compare VAR_RESULT, 1
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A867F
	compare VAR_RESULT, 0
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A861C
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A867F:: @ 82A867F
	msgbox LilycoveCity_PokemonCenter_1F_Text_2A8F9A, MSGBOX_DEFAULT
	release
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A8689:: @ 82A8689
	special SetQuizLadyState_Complete
	msgbox LilycoveCity_PokemonCenter_1F_Text_2A8F4D, MSGBOX_DEFAULT
	specialvar VAR_RESULT, IsQuizAnswerCorrect
	compare VAR_RESULT, 0
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A86C7
	compare VAR_RESULT, 1
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A86B0
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A86B0:: @ 82A86B0
	playse SE_SEIKAI
	delay 10
	playse SE_SEIKAI
	msgbox LilycoveCity_PokemonCenter_1F_Text_2A8FC7, MSGBOX_DEFAULT
	goto LilycoveCity_PokemonCenter_1F_EventScript_2A86EC
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A86C7:: @ 82A86C7
	special BufferQuizCorrectAnswer
	special BufferQuizPrizeName
	playse SE_HAZURE
	delay 10
	playse SE_HAZURE
	msgbox LilycoveCity_PokemonCenter_1F_Text_2A90A5, MSGBOX_DEFAULT
	msgbox LilycoveCity_PokemonCenter_1F_Text_2A90CD, MSGBOX_DEFAULT
	goto LilycoveCity_PokemonCenter_1F_EventScript_2A8759
	end

@ VAR_RESULT is essentially ignored, both jumps are identical
LilycoveCity_PokemonCenter_1F_EventScript_2A86EC:: @ 82A86EC
	specialvar VAR_RESULT, BufferQuizAuthorNameAndCheckIfLady
	compare VAR_RESULT, 1
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A8708
	compare VAR_RESULT, 0
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A8716
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A8708:: @ 82A8708
	msgbox LilycoveCity_PokemonCenter_1F_Text_2A9007, MSGBOX_DEFAULT
	goto LilycoveCity_PokemonCenter_1F_EventScript_2A8724
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A8716:: @ 82A8716
	msgbox LilycoveCity_PokemonCenter_1F_Text_2A9007, MSGBOX_DEFAULT
	goto LilycoveCity_PokemonCenter_1F_EventScript_2A8724
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A8724:: @ 82A8724
	setvar VAR_0x8005, 0
	special BufferQuizPrizeItem
	special SetQuizLadyState_Complete
	giveitem_std VAR_0x8005
	compare VAR_RESULT, 0
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A874C
	goto LilycoveCity_PokemonCenter_1F_EventScript_2A8759
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A874C:: @ 82A874C
	msgbox LilycoveCity_PokemonCenter_1F_Text_2A906A, MSGBOX_DEFAULT
	special SetQuizLadyState_GivePrize
	release
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A8759:: @ 82A8759
	msgbox LilycoveCity_PokemonCenter_1F_Text_2A90FB, MSGBOX_YESNO
	compare VAR_RESULT, 1
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A8785
	compare VAR_RESULT, 0
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A8778
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A8778:: @ 82A8778
	special QuizLadyPickNewQuestion
	msgbox LilycoveCity_PokemonCenter_1F_Text_2A9131, MSGBOX_DEFAULT
	release
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A8785:: @ 82A8785
	msgbox LilycoveCity_PokemonCenter_1F_Text_2A9153, MSGBOX_DEFAULT

LilycoveCity_PokemonCenter_1F_EventScript_2A878D:: @ 82A878D
	fadescreen 1
	setvar VAR_RESULT, 0
	special Script_QuizLadyOpenBagMenu
	waitstate
	compare VAR_RESULT, 0
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A87AF
	compare VAR_RESULT, 1
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A87CE
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A87AF:: @ 82A87AF
	msgbox LilycoveCity_PokemonCenter_1F_Text_2A9212, MSGBOX_YESNO
	compare VAR_RESULT, 1
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A8778
	compare VAR_RESULT, 0
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A878D
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A87CE:: @ 82A87CE
	msgbox LilycoveCity_PokemonCenter_1F_Text_2A9270, MSGBOX_DEFAULT
	special ClearQuizLadyQuestionAndAnswer
	special ClearQuizLadyPlayerAnswer
	setvar VAR_0x8004, EASY_CHAT_TYPE_QUIZ_QUESTION

LilycoveCity_PokemonCenter_1F_EventScript_2A87E1:: @ 82A87E1
	fadescreen 1
	special QuizLadySetCustomQuestion
	waitstate
	compare VAR_RESULT, 0
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A87F8
	goto LilycoveCity_PokemonCenter_1F_EventScript_2A8817
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A87F8:: @ 82A87F8
	msgbox LilycoveCity_PokemonCenter_1F_Text_2A92D3, MSGBOX_YESNO
	compare VAR_RESULT, 1
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A8778
	compare VAR_RESULT, 0
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A87E1
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A8817:: @ 82A8817
	special QuizLadyTakePrizeForCustomQuiz
	special QuizLadyRecordCustomQuizData
	special QuizLadySetWaitingForChallenger
	msgbox LilycoveCity_PokemonCenter_1F_Text_2A9336, MSGBOX_DEFAULT
	release
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A882A:: @ 82A882A
	lock
	faceplayer
	msgbox LilycoveCity_PokemonCenter_1F_Text_2A93A7, MSGBOX_DEFAULT
	specialvar VAR_RESULT, HasPlayerGivenContestLadyPokeblock
	compare VAR_RESULT, 0
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A8850
	compare VAR_RESULT, 1
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A886C
	end

@ Redundant with above script, VAR_RESULT will always be 0 here
LilycoveCity_PokemonCenter_1F_EventScript_2A8850:: @ 82A8850
	specialvar VAR_RESULT, ShouldContestLadyShowGoOnAir
	compare VAR_RESULT, 0
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A8876
	compare VAR_RESULT, 1
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A886C
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A886C:: @ 82A886C
	msgbox LilycoveCity_PokemonCenter_1F_Text_2A93D6, MSGBOX_DEFAULT
	release
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A8876:: @ 82A8876
	special Script_BufferContestLadyCategoryAndMonName
	msgbox LilycoveCity_PokemonCenter_1F_Text_2A93F4, MSGBOX_DEFAULT
	checkitem ITEM_POKEBLOCK_CASE, 1
	compare VAR_RESULT, 0
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A89AE
	msgbox LilycoveCity_PokemonCenter_1F_Text_2A94E8, MSGBOX_YESNO
	compare VAR_RESULT, 0
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A88B0
	compare VAR_RESULT, 1
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A88BA
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A88B0:: @ 82A88B0
	msgbox LilycoveCity_PokemonCenter_1F_Text_2A9556, MSGBOX_DEFAULT
	release
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A88BA:: @ 82A88BA
	fadescreen 1
	special OpenPokeblockCaseForContestLady
	waitstate
	compare VAR_RESULT, 65535
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A88D7
	compare VAR_RESULT, 65535
	goto_if_ne LilycoveCity_PokemonCenter_1F_EventScript_2A88F6
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A88D7:: @ 82A88D7
	msgbox LilycoveCity_PokemonCenter_1F_Text_2A9537, MSGBOX_YESNO
	compare VAR_RESULT, 1
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A88B0
	compare VAR_RESULT, 0
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A88BA
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A88F6:: @ 82A88F6
	msgbox LilycoveCity_PokemonCenter_1F_Text_2A9571, MSGBOX_DEFAULT
	special SetContestLadyGivenPokeblock
	special GetContestLadyMonSpecies
	goto LilycoveCity_PokemonCenter_1F_EventScript_2A890A
	end

@ VAR_0x8004 here is the return value from GivePokeblockToContestLady
LilycoveCity_PokemonCenter_1F_EventScript_2A890A:: @ 82A890A
	applymovement 4, LilycoveCity_PokemonCenter_1F_Movement_2A89B8
	waitmovement 0
	delay 60
	applymovement 5, LilycoveCity_PokemonCenter_1F_Movement_2A89BB
	waitmovement 0
	delay 60
	waitse
	playmoncry VAR_0x8005, 0
	delay 120
	waitmoncry
	compare VAR_0x8004, 1
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A893F
	goto LilycoveCity_PokemonCenter_1F_EventScript_2A894C
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A893F:: @ 82A893F
	applymovement 5, LilycoveCity_PokemonCenter_1F_Movement_2A89C2
	waitmovement 0
	delay 60

@ VAR_0x8004 here is the return value from GivePokeblockToContestLady
LilycoveCity_PokemonCenter_1F_EventScript_2A894C:: @ 82A894C
	applymovement 4, LilycoveCity_PokemonCenter_1F_Movement_2A89C0
	waitmovement 0
	delay 60
	compare VAR_0x8004, 0
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A8970
	compare VAR_0x8004, 1
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A897E
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A8970:: @ 82A8970
	msgbox LilycoveCity_PokemonCenter_1F_Text_2A95AD, MSGBOX_DEFAULT
	goto LilycoveCity_PokemonCenter_1F_EventScript_2A898F
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A897E:: @ 82A897E
	special Script_BufferContestLadyCategoryAndMonName
	msgbox LilycoveCity_PokemonCenter_1F_Text_2A9605, MSGBOX_DEFAULT
	goto LilycoveCity_PokemonCenter_1F_EventScript_2A898F
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A898F:: @ 82A898F
	specialvar VAR_RESULT, ShouldContestLadyShowGoOnAir
	compare VAR_RESULT, 1
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A89A1
	release
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A89A1:: @ 82A89A1
	msgbox LilycoveCity_PokemonCenter_1F_Text_2A9669, MSGBOX_DEFAULT
	special PutLilycoveContestLadyShowOnTheAir
	release
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A89AE:: @ 82A89AE
	msgbox LilycoveCity_PokemonCenter_1F_Text_2A9451, MSGBOX_DEFAULT
	release
	end

LilycoveCity_PokemonCenter_1F_Movement_2A89B8: @ 82A89B8
	face_right
	delay_8
	step_end

LilycoveCity_PokemonCenter_1F_Movement_2A89BB: @ 82A89BB
	face_left
	delay_8
	step_end

LilycoveCity_PokemonCenter_1F_Movement_2A89BE: @ 82A89BE
	face_down
	step_end

LilycoveCity_PokemonCenter_1F_Movement_2A89C0: @ 82A89C0
	face_player
	step_end

LilycoveCity_PokemonCenter_1F_Movement_2A89C2: @ 82A89C2
	disable_jump_landing_ground_effect
	jump_in_place_left
	disable_jump_landing_ground_effect
	jump_in_place_left
	step_end

LilycoveCity_PokemonCenter_1F_EventScript_2A89C7:: @ 82A89C7
	specialvar VAR_RESULT, GetContestLadyCategory
	special Script_BufferContestLadyCategoryAndMonName
	special GetContestLadyMonSpecies
	compare VAR_RESULT, CONTEST_CATEGORY_COOL
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A8A0A
	compare VAR_RESULT, CONTEST_CATEGORY_BEAUTY
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A8A1D
	compare VAR_RESULT, CONTEST_CATEGORY_CUTE
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A8A30
	compare VAR_RESULT, CONTEST_CATEGORY_SMART
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A8A43
	compare VAR_RESULT, CONTEST_CATEGORY_TOUGH
	goto_if_eq LilycoveCity_PokemonCenter_1F_EventScript_2A8A56
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A8A0A:: @ 82A8A0A
	lock
	faceplayer
	waitse
	playmoncry VAR_0x8005, 0
	msgbox LilycoveCity_PokemonCenter_1F_Text_2A96DA, MSGBOX_DEFAULT
	waitmoncry
	release
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A8A1D:: @ 82A8A1D
	lock
	faceplayer
	waitse
	playmoncry VAR_0x8005, 0
	msgbox LilycoveCity_PokemonCenter_1F_Text_2A970E, MSGBOX_DEFAULT
	waitmoncry
	release
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A8A30:: @ 82A8A30
	lock
	faceplayer
	waitse
	playmoncry VAR_0x8005, 0
	msgbox LilycoveCity_PokemonCenter_1F_Text_2A96F6, MSGBOX_DEFAULT
	waitmoncry
	release
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A8A43:: @ 82A8A43
	lock
	faceplayer
	waitse
	playmoncry VAR_0x8005, 0
	msgbox LilycoveCity_PokemonCenter_1F_Text_2A96E6, MSGBOX_DEFAULT
	waitmoncry
	release
	end

LilycoveCity_PokemonCenter_1F_EventScript_2A8A56:: @ 82A8A56
	lock
	faceplayer
	waitse
	playmoncry VAR_0x8005, 0
	msgbox LilycoveCity_PokemonCenter_1F_Text_2A9703, MSGBOX_DEFAULT
	waitmoncry
	release
	end

LilycoveCity_PokemonCenter_1F_Text_2A8A69: @ 82A8A69
	.string "I'm the FAVOR LADY…$"

LilycoveCity_PokemonCenter_1F_Text_2A8A7D: @ 82A8A7D
	.string "我最近很痴迷于\n"
	.string "有关{STR_VAR_1}的事情…$"

LilycoveCity_PokemonCenter_1F_Text_2A8AB1: @ 82A8AB1
	.string "噢…\n"
	.string "最后再感谢你一次…$"

LilycoveCity_PokemonCenter_1F_Text_2A8ACE: @ 82A8ACE
	.string "以前，我认为它是{STR_VAR_3}…\p"
	.string "后来，{STR_VAR_3}给了我{STR_VAR_2},\n"
	.string "说它是{STR_VAR_1}。\p"
	.string "但它不是{STR_VAR_1}。\n"
	.string "绝对不是。$"

LilycoveCity_PokemonCenter_1F_Text_2A8B36: @ 82A8B36
	.string "以前, {STR_VAR_3}给了我一个非常\n"
	.string "{STR_VAR_1}{STR_VAR_2}。\p"
	.string "我现在很珍惜它。$"

LilycoveCity_PokemonCenter_1F_Text_2A8B69: @ 82A8B69
	.string "如果你有任何有关于\n"
	.string "{STR_VAR_1}的事情，你都\l"
	.string "可以与我分享吗?$"

LilycoveCity_PokemonCenter_1F_Text_2A8BAD: @ 82A8BAD
	.string "…真的吗?\n"
	.string "你会给我什么?$"

LilycoveCity_PokemonCenter_1F_Text_2A8BCD: @ 82A8BCD
	.string "是这样吗?\n"
	.string "那再见…$"

LilycoveCity_PokemonCenter_1F_Text_2A8BEE: @ 82A8BEE
	.string "噢…\n"
	.string "你不愿意分享吗?$"

LilycoveCity_PokemonCenter_1F_Text_2A8C0F: @ 82A8C0F
	.string "哦?\n"
	.string "{STR_VAR_2}是{STR_VAR_1}?\p"
	.string "…哦，是这样子的吗?\p"
	.string "好吧，无论如何我都要感谢您。\n"
	.string "我会尽力珍惜它…$"

LilycoveCity_PokemonCenter_1F_Text_2A8C6F: @ 82A8C6F
	.string "哦…\p"
	.string "这是一个非常{STR_VAR_1}的\n"
	.string "{STR_VAR_2}…\p"
	.string "它很好吗?\n"
	.string "真是太棒了…\p"
	.string "谢谢你…\n"
	.string "我会珍惜它的…$"

LilycoveCity_PokemonCenter_1F_Text_2A8CC8: @ 82A8CC8
	.string "…哦，哦，哦…\p"
	.string "这简直太棒了!\n"
	.string "这真的是{STR_VAR_1}!\p"
	.string "我从来不知道{STR_VAR_2}\n"
	.string "可以这样的{STR_VAR_1}!\p"
	.string "谢谢你!\p"
	.string "以后我会好好\n"
	.string "珍惜它的!$"

LilycoveCity_PokemonCenter_1F_Text_2A8D5D: @ 82A8D5D
	.string "我会给你这个神奇的道具，\n"
	.string "用来回报你珍贵的礼物。\p"
	.string "我希望你会珍惜它…$"

LilycoveCity_PokemonCenter_1F_Text_2A8DBD: @ 82A8DBD
	.string "哦，你包里没有空间了，\n"
	.string "因此你现在不能接收。\p"
	.string "请整理完你的背包后\n"
	.string "再来见我…$"

LilycoveCity_PokemonCenter_1F_Text_2A8E2B: @ 82A8E2B
	.string "我是测验女士!\n"
	.string "我喜欢测验!$"

LilycoveCity_PokemonCenter_1F_Text_2A8E4E: @ 82A8E4E
	.string "哦?\p"
	.string "我正在等待挑战者来\n"
	.string "回答你所做的测验。\p"
	.string "我们可以下次再聊，可以吗?$"

LilycoveCity_PokemonCenter_1F_Text_2A8EAC: @ 82A8EAC
	.string "我正在等待有人来挑战\n"
	.string "这个由{STR_VAR_1}提出的问答!$"

LilycoveCity_PokemonCenter_1F_Text_2A8EEC: @ 82A8EEC
	.string "如果你可以回答正确，\n"
	.string "你将会获得精美的奖品!\p"
	.string "你要尝试挑战\n"
	.string "这个问答吗?$"

LilycoveCity_PokemonCenter_1F_Text_2A8F4D: @ 82A8F4D
	.string "… … … … … …\n"
	.string "… … … … … …$"

LilycoveCity_PokemonCenter_1F_Text_2A8F65: @ 82A8F65
	.string "哦,多么的无聊!\n"
	.string "再见!$"

LilycoveCity_PokemonCenter_1F_Text_2A8F7E: @ 82A8F7E
	.string "噢!\n"
	.string "你要放弃吗?$"

LilycoveCity_PokemonCenter_1F_Text_2A8F9A: @ 82A8F9A
	.string "请下次再来接受\n"
	.string "这个挑战!$"

LilycoveCity_PokemonCenter_1F_Text_2A8FC7: @ 82A8FC7
	.string "你太令人吃惊了!你回答正确了!\n"
	.string "你真是太聪明了!$"

LilycoveCity_PokemonCenter_1F_Text_2A9007: @ 82A9007
	.string "恭喜!\n"
	.string "这个问题你已经回答正确了!\p"
	.string "你获得了这个由{STR_VAR_1}\n"
	.string "提供的奖品!$"

LilycoveCity_PokemonCenter_1F_Text_2A9056: @ 82A9056
	.string "{STR_VAR_1}获得了\n"
	.string "一个{STR_VAR_2}!$"

LilycoveCity_PokemonCenter_1F_Text_2A906A: @ 82A906A
	.string "哦?你的背包满了!\n"
	.string "等你整理完背包再来找我吧。$"

LilycoveCity_PokemonCenter_1F_Text_2A90A5: @ 82A90A5
	.string "嗯… 错误!\n"
	.string "正确答案是“{STR_VAR_3}”!$"

LilycoveCity_PokemonCenter_1F_Text_2A90CD: @ 82A90CD
	.string "太糟糕了!\p"
	.string "我现在只能保留测验\n"
	.string "的奖项{STR_VAR_1}了!$"

LilycoveCity_PokemonCenter_1F_Text_2A90FB: @ 82A90FB
	.string "听好了!\n"
	.string "你想做一个自己的测验吗?$"

LilycoveCity_PokemonCenter_1F_Text_2A9131: @ 82A9131
	.string "哦, 我看看…\n"
	.string "好吧，可能得下一次了!$"

LilycoveCity_PokemonCenter_1F_Text_2A9153: @ 82A9153
	.string "好的,首先你需要做的\n"
	.string "事情是为正确回答你\l"
	.string "问题的人设置奖品。\p"
	.string "但你要注意,如果参与测验\n"
	.string "的人都无法回答正确，\l"
	.string "我会保留奖品!$"

LilycoveCity_PokemonCenter_1F_Text_2A9212: @ 82A9212
	.string "如果你没有选择奖品,\n"
	.string "你的测验将无法完成。\p"
	.string "你要放弃完成你的\n"
	.string "测验吗?$"

LilycoveCity_PokemonCenter_1F_Text_2A9270: @ 82A9270
	.string "哦，真是太棒了!\n"
	.string "这真是个很好的奖品!\p"
	.string "接下来，你需要编辑你的\n"
	.string "问题以及答案。$"

LilycoveCity_PokemonCenter_1F_Text_2A92D3: @ 82A92D3
	.string "你要放弃编辑你的\n"
	.string "测验问题吗?$"

LilycoveCity_PokemonCenter_1F_Text_2A9305: @ 82A9305
	.string "你要放弃选择你的\n"
	.string "测验答案吗?$"

LilycoveCity_PokemonCenter_1F_Text_2A9336: @ 82A9336
	.string "谢谢!\n"
	.string "你已经设置完一个很好的测验。\p"
	.string "我会去寻找一个能马上\n"
	.string "接受你的测验挑战的人。$"

LilycoveCity_PokemonCenter_1F_Text_2A93A7: @ 82A93A7
	.string "我是华丽大赛女士!\n"
	.string "我确实很喜欢华丽大赛!$"

LilycoveCity_PokemonCenter_1F_Text_2A93D6: @ 82A93D6
	.string "感谢你之前的{POKEBLOCK}!$"

LilycoveCity_PokemonCenter_1F_Text_2A93F4: @ 82A93F4
	.string "这是我的伙伴{STR_VAR_1}!\n"
	.string "这是{STR_VAR_2}的缩影!\p"
	.string "但我认为他会显示\n"
	.string "更多的{STR_VAR_2}!$"

LilycoveCity_PokemonCenter_1F_Text_2A9451: @ 82A9451
	.string "我需要你的帮助!\p"
	.string "拜托，我可以有一个{POKEBLOCK}吗?\n"
	.string "我所要求的只有一个!\p"
	.string "…哦, 但是…\n"
	.string "你有没有一个{POKEBLOCK}盒?\l"
	.string "那不好，下一次吧!$"

LilycoveCity_PokemonCenter_1F_Text_2A94E8: @ 82A94E8
	.string "我需要你的帮助!\p"
	.string "拜托，我可以有一个{POKEBLOCK}吗?\n"
	.string "我所要求的只有一个!$"

LilycoveCity_PokemonCenter_1F_Text_2A9537: @ 82A9537
	.string "噢!\n"
	.string "我不能有{POKEBLOCK}?!$"

LilycoveCity_PokemonCenter_1F_Text_2A9556: @ 82A9556
	.string "啧!\n"
	.string "太小气了!$"

LilycoveCity_PokemonCenter_1F_Text_2A9571: @ 82A9571
	.string "耶!\n"
	.string "谢谢你!\p"
	.string "我会马上用你给的{POKEBLOCK}\n"
	.string "来喂我的宝可梦。$"

LilycoveCity_PokemonCenter_1F_Text_2A95AD: @ 82A95AD
	.string "…它似乎没有发生\n"
	.string "任何的改变…\p"
	.string "嗯…\p"
	.string "那好吧!\n"
	.string "非常感谢你!$"

LilycoveCity_PokemonCenter_1F_Text_2A9605: @ 82A9605
	.string "耶!\n"
	.string "真的很高兴!\p"
	.string "我认为它确实提高了\n"
	.string "{STR_VAR_1}的{STR_VAR_2}。\p"
	.string "非常感谢你!$"

LilycoveCity_PokemonCenter_1F_Text_2A9669: @ 82A9669
	.string "嗯…\p"
	.string "我想我们已经准备好\n"
	.string "参加比赛了。\p"
	.string "如果下次你看到我们,\n"
	.string "我希望你可以为我们加油。$"

LilycoveCity_PokemonCenter_1F_Text_2A96DA: @ 82A96DA
	.string "{STR_VAR_1}: Guguuh!$"

LilycoveCity_PokemonCenter_1F_Text_2A96E6: @ 82A96E6
	.string "{STR_VAR_1}: Igigigiiih!$"

LilycoveCity_PokemonCenter_1F_Text_2A96F6: @ 82A96F6
	.string "{STR_VAR_1}: Baaarun…$"

LilycoveCity_PokemonCenter_1F_Text_2A9703: @ 82A9703
	.string "{STR_VAR_1}: Pikka!$"

LilycoveCity_PokemonCenter_1F_Text_2A970E: @ 82A970E
	.string "{STR_VAR_1}: Umyaaaan!$"

	.include "data/text/match_call.inc"
	.include "data/scripts/apprentice.inc"

gBattleDomeOpponentPotentialText1::
	.string "成为冠军的最佳人选!$"

gBattleDomeOpponentPotentialText2::
	.string "一支确定能进决赛的队伍。$"

gBattleDomeOpponentPotentialText3::
	.string "可能是前三名的终结者。$"

gBattleDomeOpponentPotentialText4::
	.string "获得第一的候选人。$"

gBattleDomeOpponentPotentialText5::
	.string "拥有一流潜力的队伍。$"

gBattleDomeOpponentPotentialText6::
	.string "这场锦标赛的黑马。$"

gBattleDomeOpponentPotentialText7::
	.string "一支平均水平以上的队伍。$"

gBattleDomeOpponentPotentialText8::
	.string "这场锦标赛的平均水平。$"

gBattleDomeOpponentPotentialText9::
	.string "拥有平均水平潜力的一支队伍。$"

gBattleDomeOpponentPotentialText10::
	.string "弱于平均水平的队伍。$"

gBattleDomeOpponentPotentialText11::
	.string "还在寻找第一场胜利的队伍。$"

gBattleDomeOpponentPotentialText12::
	.string "一场胜利足以让这支队伍感到自豪。$"

gBattleDomeOpponentPotentialText13::
	.string "总体而言，一支弱队。$"

gBattleDomeOpponentPotentialText14::
	.string "拥有非常低潜力的队伍。$"

gBattleDomeOpponentPotentialText15::
	.string "一支不太可能赢得比赛的队伍。$"

gBattleDomeOpponentPotentialText16::
	.string "最不可能获胜的队伍。$"

gBattleDomeOpponentPotentialText17::
	.string "完美又无敌的超级巨星!$"

gBattleDomeOpponentStyleText1::
	.string "有时会愿意去冒险。$"

gBattleDomeOpponentStyleText2::
	.string "熟练于长时间的战斗。$"

gBattleDomeOpponentStyleText3::
	.string "经常改变战略去应对不同的对手。$"

gBattleDomeOpponentStyleText4::
	.string "有一场艰难的胜利。$"

gBattleDomeOpponentStyleText5::
	.string "偶尔会使用非常少见的技能。$"

gBattleDomeOpponentStyleText6::
	.string "使用破坏力惊人的技能。$"

gBattleDomeOpponentStyleText7::
	.string "在战斗过程中会盯着HP。$"

gBattleDomeOpponentStyleText8::
	.string "擅于先储存然后再释放力量。$"

gBattleDomeOpponentStyleText9::
	.string "能够熟练的与对手战斗。$"

gBattleDomeOpponentStyleText10::
	.string "更喜欢使用依靠运气的战术。$"

gBattleDomeOpponentStyleText11::
	.string "使用华丽的技能攻击。$"

gBattleDomeOpponentStyleText12::
	.string "使用PP值低威力大的技能攻击。$"

gBattleDomeOpponentStyleText13::
	.string "擅长先进行蓄力然后在攻击。$"

gBattleDomeOpponentStyleText14::
	.string "会在忍受所有攻击的同时进行战斗。$"

gBattleDomeOpponentStyleText15::
	.string "擅于扰乱对手的情绪。$"

gBattleDomeOpponentStyleText16::
	.string "使用强大而又直接的技能。$"

gBattleDomeOpponentStyleText17::
	.string "经常使用强大的技能。$"

gBattleDomeOpponentStyleText18::
	.string "在巧妙地躲避对手攻击的同时进行战斗。$"

gBattleDomeOpponentStyleText19::
	.string "擅于使用干扰对手的攻击。$"

gBattleDomeOpponentStyleText20::
	.string "会使用许多受欢迎的技能。$"

gBattleDomeOpponentStyleText21::
	.string "有强大的技能组合。$"

gBattleDomeOpponentStyleText22::
	.string "使用命中率高的技能攻击。$"

gBattleDomeOpponentStyleText23::
	.string "经常使用看起来很壮观的技能。$"

gBattleDomeOpponentStyleText24::
	.string "比起防守更注重于进攻。$"

gBattleDomeOpponentStyleText25::
	.string "比起进攻更注重于防守。$"

gBattleDomeOpponentStyleText26::
	.string "使用强大的技能快速地进攻。$"

gBattleDomeOpponentStyleText27::
	.string "经常使用带有特效的技能。$"

gBattleDomeOpponentStyleText28::
	.string "使用均衡的技能配置。$"

gBattleDomeOpponentStyleTextUnused1::
	.string "这是消息示例1.$"

gBattleDomeOpponentStyleTextUnused2::
	.string "这是消息示例2.$"

gBattleDomeOpponentStyleTextUnused3::
	.string "这是消息示例3.$"

gBattleDomeOpponentStyleTextUnused4::
	.string "这是消息示例4.$"

gBattleDomeOpponentStatsText1::
	.string "注重HP和物攻。$"

gBattleDomeOpponentStatsText2::
	.string "注重HP和物防。$"

gBattleDomeOpponentStatsText3::
	.string "注重HP和速度。$"

gBattleDomeOpponentStatsText4::
	.string "注重HP和特攻。$"

gBattleDomeOpponentStatsText5::
	.string "注重HP和特防。$"

gBattleDomeOpponentStatsText6::
	.string "注重物攻和物防。$"

gBattleDomeOpponentStatsText7::
	.string "注重物攻和速度。$"

gBattleDomeOpponentStatsText8::
	.string "注重物攻和特攻。$"

gBattleDomeOpponentStatsText9::
	.string "注重物攻和特防。$"

gBattleDomeOpponentStatsText10::
	.string "注重物防和速度。$"

gBattleDomeOpponentStatsText11::
	.string "注重物防和特攻。$"

gBattleDomeOpponentStatsText12::
	.string "注重物防和特防。$"

gBattleDomeOpponentStatsText13::
	.string "注重速度和特攻。$"

gBattleDomeOpponentStatsText14::
	.string "注重速度和特防。$"

gBattleDomeOpponentStatsText15::
	.string "注重特攻和特防。$"

gBattleDomeOpponentStatsText16::
	.string "注重HP。$"

gBattleDomeOpponentStatsText17::
	.string "注重物攻。$"

gBattleDomeOpponentStatsText18::
	.string "注重物防。$"

gBattleDomeOpponentStatsText19::
	.string "注重速度。$"

gBattleDomeOpponentStatsText20::
	.string "注重特攻。$"

gBattleDomeOpponentStatsText21::
	.string "注重特防。$"

gBattleDomeOpponentStatsText22::
	.string "忽视HP和物攻。$"

gBattleDomeOpponentStatsText23::
	.string "忽视HP和物防。$"

gBattleDomeOpponentStatsText24::
	.string "忽视HP和速度。$"

gBattleDomeOpponentStatsText25::
	.string "忽视HP和特攻。$"

gBattleDomeOpponentStatsText26::
	.string "忽视HP和特防。$"

gBattleDomeOpponentStatsText27::
	.string "忽视物攻和物防。$"

gBattleDomeOpponentStatsText28::
	.string "忽视物攻和速度。$"

gBattleDomeOpponentStatsText29::
	.string "忽视物攻和特攻。$"

gBattleDomeOpponentStatsText30::
	.string "忽视物攻和特防。$"

gBattleDomeOpponentStatsText31::
	.string "忽视物防和速度。$"

gBattleDomeOpponentStatsText32::
	.string "忽视物防和特攻。$"

gBattleDomeOpponentStatsText33::
	.string "忽视物防和特防。$"

gBattleDomeOpponentStatsText34::
	.string "忽视速度和特攻。$"

gBattleDomeOpponentStatsText35::
	.string "忽视速度和特防。$"

gBattleDomeOpponentStatsText36::
	.string "忽视特攻和特防。$"

gBattleDomeOpponentStatsText37::
	.string "忽视HP。$"

gBattleDomeOpponentStatsText38::
	.string "忽视物攻。$"

gBattleDomeOpponentStatsText39::
	.string "忽视物防。$"

gBattleDomeOpponentStatsText40::
	.string "忽视速度。$"

gBattleDomeOpponentStatsText41::
	.string "忽视特攻。$"

gBattleDomeOpponentStatsText42::
	.string "忽视特防。$"

gBattleDomeOpponentStatsText43::
	.string "以均衡的方式培养宝可梦。$"

gBattleDomeWinText1::
	.string "让我们开始战斗吧!$"

gBattleDomeWinText2::
	.string "{STR_VAR_1}使用{STR_VAR_2}赢得胜利!$"

gBattleDomeWinText3::
	.string "{STR_VAR_1}成为冠军$"

gBattleDomeWinText4::
	.string "{STR_VAR_1}默认获得胜利!$"

gBattleDomeWinText5::
	.string "{STR_VAR_1}默认情况完全赢得胜利!$"

gBattleDomeWinText6::
	.string "{STR_VAR_1}没有使用技能赢了!$"

gBattleDomeWinText7::
	.string "{STR_VAR_1}没有行动就获得完全胜利!$"

gBattleDomeMatchNumberText1::
	.string "第1轮,第1场比赛$"

gBattleDomeMatchNumberText2::
	.string "第1轮,第2场比赛$"

gBattleDomeMatchNumberText3::
	.string "第1轮,第3场比赛$"

gBattleDomeMatchNumberText4::
	.string "第1轮,第4场比赛$"

gBattleDomeMatchNumberText5::
	.string "第1轮,第5场比赛$"

gBattleDomeMatchNumberText6::
	.string "第1轮,第6场比赛$"

gBattleDomeMatchNumberText7::
	.string "第1轮,第7场比赛$"

gBattleDomeMatchNumberText8::
	.string "第1轮,第8场比赛$"

gBattleDomeMatchNumberText9::
	.string "第2轮,第1场比赛$"

gBattleDomeMatchNumberText10::
	.string "第2轮,第2场比赛$"

gBattleDomeMatchNumberText11::
	.string "第2轮,第3场比赛$"

gBattleDomeMatchNumberText12::
	.string "第2轮,第4场比赛$"

gBattleDomeMatchNumberText13::
	.string "半决赛第1场$"

gBattleDomeMatchNumberText14::
	.string "半决赛第2场$"

gBattleDomeMatchNumberText15::
	.string "决赛$"

BattleFrontier_BattlePikeRandomRoom1_MapScripts_2C3E1B: @ 82C3E1B
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_BattlePikeRandomRoom1_MapScript1_2C3E25
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattlePikeRandomRoom1_MapScript2_2C3EDE

BattleFrontier_BattlePikeRandomRoom1_MapScript1_2C3E25: @ 82C3E25
	setvar VAR_0x8004, 4
	special CallBattlePikeFunction
	setvar VAR_0x8004, 5
	special CallBattlePikeFunction
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePikeRandomRoom1_EventScript_2C3EB1
	case 1, BattleFrontier_BattlePikeRandomRoom1_EventScript_2C3EB1
	case 2, BattleFrontier_BattlePikeRandomRoom1_EventScript_2C3EC0
	case 3, BattleFrontier_BattlePikeRandomRoom1_EventScript_2C3EA2
	case 4, BattleFrontier_BattlePikeRandomRoom1_EventScript_2C3EB1
	case 7, BattleFrontier_BattlePikeRandomRoom1_EventScript_2C3E93
	case 6, BattleFrontier_BattlePikeRandomRoom1_EventScript_2C3EA2
	case 8, BattleFrontier_BattlePikeRandomRoom1_EventScript_2C3ECF
	end

BattleFrontier_BattlePikeRandomRoom1_EventScript_2C3E93:: @ 82C3E93
	setobjectxyperm 1, 2, 5
	setobjectxyperm 2, 6, 5
	end

BattleFrontier_BattlePikeRandomRoom1_EventScript_2C3EA2:: @ 82C3EA2
	setobjectxyperm 1, 4, 4
	setobjectxyperm 2, 3, 4
	end

BattleFrontier_BattlePikeRandomRoom1_EventScript_2C3EB1:: @ 82C3EB1
	setobjectxyperm 1, 4, 4
	setobjectxyperm 2, 0, 0
	end

BattleFrontier_BattlePikeRandomRoom1_EventScript_2C3EC0:: @ 82C3EC0
	setobjectxyperm 1, 5, 5
	setobjectxyperm 2, 0, 0
	end

BattleFrontier_BattlePikeRandomRoom1_EventScript_2C3ECF:: @ 82C3ECF
	setobjectxyperm 1, 4, 3
	setobjectxyperm 2, 4, 4
	end

BattleFrontier_BattlePikeRandomRoom1_MapScript2_2C3EDE: @ 82C3EDE
	map_script_2 VAR_TEMP_4, 0, BattleFrontier_BattlePikeRandomRoom1_EventScript_2C3EE8
	.2byte 0

BattleFrontier_BattlePikeRandomRoom1_EventScript_2C3EE8:: @ 82C3EE8
	setvar VAR_OBJ_GFX_ID_1, EVENT_OBJ_GFX_LINK_RECEPTIONIST
	setvar VAR_OBJ_GFX_ID_0, EVENT_OBJ_GFX_LINK_RECEPTIONIST
	setvar VAR_0x8004, 5
	special CallBattlePikeFunction
	compare VAR_RESULT, 3
	goto_if_eq BattleFrontier_BattlePikeRandomRoom1_EventScript_2C3F35
	compare VAR_RESULT, 6
	goto_if_eq BattleFrontier_BattlePikeRandomRoom1_EventScript_2C3F35
	compare VAR_RESULT, 7
	goto_if_eq BattleFrontier_BattlePikeRandomRoom1_EventScript_2C3F35
	compare VAR_RESULT, 8
	goto_if_eq BattleFrontier_BattlePikeRandomRoom1_EventScript_2C3F3F
	hideobjectat 2, MAP_BATTLE_FRONTIER_BATTLE_PIKE_RANDOM_ROOM1
	setvar VAR_TEMP_4, 1
	turnobject 255, 2
	end

BattleFrontier_BattlePikeRandomRoom1_EventScript_2C3F35:: @ 82C3F35
	setvar VAR_TEMP_4, 1
	turnobject 255, 2
	end

BattleFrontier_BattlePikeRandomRoom1_EventScript_2C3F3F:: @ 82C3F3F
	setvar VAR_TEMP_4, 1
	turnobject 255, 2
	hideobjectat 1, MAP_BATTLE_FRONTIER_BATTLE_PIKE_RANDOM_ROOM1
	end

BattleFrontier_BattlePikeThreePathRoom_EventScript_2C3F4E:: @ 82C3F4E
	setvar VAR_0x8007, 0
	goto BattleFrontier_BattlePikeThreePathRoom_EventScript_2C3F6F
	end

BattleFrontier_BattlePikeThreePathRoom_EventScript_2C3F59:: @ 82C3F59
	setvar VAR_0x8007, 1
	goto BattleFrontier_BattlePikeThreePathRoom_EventScript_2C3F6F
	end

BattleFrontier_BattlePikeThreePathRoom_EventScript_2C3F64:: @ 82C3F64
	setvar VAR_0x8007, 2
	goto BattleFrontier_BattlePikeThreePathRoom_EventScript_2C3F6F
	end

BattleFrontier_BattlePikeThreePathRoom_EventScript_2C3F6F:: @ 82C3F6F
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 1
	special CallBattlePikeFunction
	addvar VAR_RESULT, 1
	setvar VAR_0x8004, 2
	setvar VAR_0x8005, 1
	copyvar VAR_0x8006, VAR_RESULT
	special CallBattlePikeFunction
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 2
	special CallFrontierUtilFunc
	addvar VAR_RESULT, 1
	setvar VAR_0x8004, 2
	setvar VAR_0x8005, 2
	copyvar VAR_0x8006, VAR_RESULT
	special CallFrontierUtilFunc
	setvar VAR_0x8004, 0
	special CallBattlePikeFunction
	setvar VAR_0x8004, 5
	special CallBattlePikeFunction
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePikeThreePathRoom_EventScript_2C4030
	case 1, BattleFrontier_BattlePikeThreePathRoom_EventScript_2C4030
	case 2, BattleFrontier_BattlePikeThreePathRoom_EventScript_2C4030
	case 3, BattleFrontier_BattlePikeThreePathRoom_EventScript_2C4030
	case 4, BattleFrontier_BattlePikeThreePathRoom_EventScript_2C4030
	case 5, BattleFrontier_BattlePikeThreePathRoom_EventScript_2C4049
	case 6, BattleFrontier_BattlePikeThreePathRoom_EventScript_2C4030
	case 7, BattleFrontier_BattlePikeThreePathRoom_EventScript_2C4030
	case 8, BattleFrontier_BattlePikeThreePathRoom_EventScript_2C4030
	end

BattleFrontier_BattlePikeThreePathRoom_EventScript_2C4030:: @ 82C4030
	applymovement EVENT_OBJ_ID_PLAYER, BattleFrontier_BattlePikeThreePathRoom_Movement_2C427A
	waitmovement 0
	call BattleFrontier_BattlePikeThreePathRoom_EventScript_25BB49
	warpsilent MAP_BATTLE_FRONTIER_BATTLE_PIKE_RANDOM_ROOM1, 255, 4, 7
	waitstate
	end

BattleFrontier_BattlePikeThreePathRoom_EventScript_2C4049:: @ 82C4049
	applymovement EVENT_OBJ_ID_PLAYER, BattleFrontier_BattlePikeThreePathRoom_Movement_2C427A
	waitmovement 0
	call BattleFrontier_BattlePikeThreePathRoom_EventScript_25BB49
	warpsilent MAP_BATTLE_FRONTIER_BATTLE_PIKE_RANDOM_ROOM3, 255, 4, 19
	waitstate
	end

BattleFrontier_BattlePikeThreePathRoom_EventScript_2C4062:: @ 82C4062
	setvar VAR_TEMP_3, 1
	setvar VAR_TEMP_2, 1
	end

BattleFrontier_BattlePikeThreePathRoom_EventScript_2C406D:: @ 82C406D
	setvar VAR_TEMP_3, 0
	setvar VAR_TEMP_2, 0
	lockall
	msgbox BattleFrontier_BattlePikeThreePathRoom_Text_25CE36, MSGBOX_DEFAULT
	closemessage
	end

BattleFrontier_BattlePikeRandomRoom1_EventScript_2C4082:: @ 82C4082
	setvar VAR_TEMP_3, 1
	setvar VAR_TEMP_2, 1
	end

BattleFrontier_BattlePikeRandomRoom1_EventScript_2C408D:: @ 82C408D
	setvar VAR_TEMP_3, 0
	setvar VAR_TEMP_2, 0
	lockall
	msgbox BattleFrontier_BattlePikeRandomRoom1_Text_25CE36, MSGBOX_DEFAULT
	closemessage
	end

BattleFrontier_BattlePikeRandomRoom1_EventScript_2C40A2:: @ 82C40A2
	setvar VAR_0x8004, 25
	special CallBattlePikeFunction
	compare VAR_RESULT, 1
	call_if_eq BattleFrontier_BattlePikeRandomRoom1_EventScript_2C4128
	compare VAR_RESULT, 1
	call_if_ne BattleFrontier_BattlePikeRandomRoom1_EventScript_2C4136
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 1
	special CallBattlePikeFunction
	addvar VAR_RESULT, 1
	setvar VAR_0x8004, 2
	setvar VAR_0x8005, 1
	copyvar VAR_0x8006, VAR_RESULT
	special CallBattlePikeFunction
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 2
	special CallFrontierUtilFunc
	addvar VAR_RESULT, 1
	setvar VAR_0x8004, 2
	setvar VAR_0x8005, 2
	copyvar VAR_0x8006, VAR_RESULT
	special CallFrontierUtilFunc
	setvar VAR_0x8004, 3
	special CallBattlePikeFunction
	compare VAR_RESULT, 1
	call_if_eq BattleFrontier_BattlePikeRandomRoom1_EventScript_2C4144
	compare VAR_RESULT, 0
	call_if_eq BattleFrontier_BattlePikeRandomRoom1_EventScript_2C415C
	waitstate
	end

BattleFrontier_BattlePikeRandomRoom1_EventScript_2C4128:: @ 82C4128
BattleFrontier_BattlePikeRandomRoom3_EventScript_2C4128:: @ 82C4128
	setvar VAR_0x8004, 24
	setvar VAR_0x8005, 1
	special CallBattlePikeFunction
	return

BattleFrontier_BattlePikeRandomRoom1_EventScript_2C4136:: @ 82C4136
BattleFrontier_BattlePikeRandomRoom3_EventScript_2C4136:: @ 82C4136
	setvar VAR_0x8004, 24
	setvar VAR_0x8005, 0
	special CallBattlePikeFunction
	return

BattleFrontier_BattlePikeRandomRoom1_EventScript_2C4144:: @ 82C4144
BattleFrontier_BattlePikeRandomRoom3_EventScript_2C4144:: @ 82C4144
	applymovement EVENT_OBJ_ID_PLAYER, BattleFrontier_BattlePikeRandomRoom1_Movement_2C427A
	waitmovement 0
	call BattleFrontier_BattlePikeRandomRoom1_EventScript_25BB49
	warpsilent MAP_BATTLE_FRONTIER_BATTLE_PIKE_RANDOM_ROOM2, 255, 2, 7
	return

BattleFrontier_BattlePikeRandomRoom1_EventScript_2C415C:: @ 82C415C
BattleFrontier_BattlePikeRandomRoom3_EventScript_2C415C:: @ 82C415C
	applymovement EVENT_OBJ_ID_PLAYER, BattleFrontier_BattlePikeRandomRoom1_Movement_2C427A
	waitmovement 0
	call BattleFrontier_BattlePikeRandomRoom1_EventScript_25BB49
	warpsilent MAP_BATTLE_FRONTIER_BATTLE_PIKE_THREE_PATH_ROOM, 255, 6, 10
	return

BattleFrontier_BattlePikeRandomRoom3_EventScript_2C4174:: @ 82C4174
	setvar VAR_0x8004, 7
	special CallBattlePikeFunction
	setvar VAR_0x8004, 25
	special CallBattlePikeFunction
	compare VAR_RESULT, 1
	call_if_eq BattleFrontier_BattlePikeRandomRoom3_EventScript_2C4128
	compare VAR_RESULT, 1
	call_if_ne BattleFrontier_BattlePikeRandomRoom3_EventScript_2C4136
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 1
	special CallBattlePikeFunction
	addvar VAR_RESULT, 1
	setvar VAR_0x8004, 2
	setvar VAR_0x8005, 1
	copyvar VAR_0x8006, VAR_RESULT
	special CallBattlePikeFunction
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 2
	special CallFrontierUtilFunc
	addvar VAR_RESULT, 1
	setvar VAR_0x8004, 2
	setvar VAR_0x8005, 2
	copyvar VAR_0x8006, VAR_RESULT
	special CallFrontierUtilFunc
	setvar VAR_0x8004, 3
	special CallBattlePikeFunction
	compare VAR_RESULT, 1
	call_if_eq BattleFrontier_BattlePikeRandomRoom3_EventScript_2C4144
	compare VAR_RESULT, 0
	call_if_eq BattleFrontier_BattlePikeRandomRoom3_EventScript_2C415C
	waitstate
	end

BattleFrontier_BattlePikeRandomRoom3_EventScript_2C4202:: @ 82C4202
	setvar VAR_TEMP_3, 1
	setvar VAR_TEMP_2, 1
	end

BattleFrontier_BattlePikeRandomRoom3_EventScript_2C420D:: @ 82C420D
	setvar VAR_TEMP_3, 0
	setvar VAR_TEMP_2, 0
	lockall
	msgbox BattleFrontier_BattlePikeRandomRoom3_Text_25CE36, MSGBOX_DEFAULT
	closemessage
	end

BattleFrontier_BattlePikeThreePathRoom_EventScript_2C4222:: @ 82C4222
	setvar VAR_0x8004, 2
	setvar VAR_0x8005, 0
	setvar VAR_0x8006, 4
	special CallFrontierUtilFunc
	warp MAP_BATTLE_FRONTIER_BATTLE_PIKE_LOBBY, 255, 5, 6
	waitstate
	end

BattleFrontier_BattlePikeRandomRoom1_MapScript1_2C423E: @ 82C423E
BattleFrontier_BattlePikeThreePathRoom_MapScript1_2C423E: @ 82C423E
	setorcopyvar VAR_0x8006, VAR_RESULT
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 0
	special CallFrontierUtilFunc
	compare VAR_RESULT, 2
	goto_if_eq BattleFrontier_BattlePikeThreePathRoom_EventScript_2C426B
	compare VAR_RESULT, 1
	goto_if_eq BattleFrontier_BattlePikeThreePathRoom_EventScript_2C426B
	call BattleFrontier_BattlePikeThreePathRoom_EventScript_2C4271

BattleFrontier_BattlePikeThreePathRoom_EventScript_2C426B:: @ 82C426B
	setorcopyvar VAR_RESULT, VAR_0x8006
	end

BattleFrontier_BattlePikeRandomRoom3_EventScript_2C4271:: @ 82C4271
BattleFrontier_BattlePikeThreePathRoom_EventScript_2C4271:: @ 82C4271
	setvar VAR_0x8004, 21
	special CallFrontierUtilFunc
	return

BattleFrontier_BattlePikeRandomRoom1_Movement_2C427A: @ 82C427A
BattleFrontier_BattlePikeThreePathRoom_Movement_2C427A: @ 82C427A
	set_invisible
	step_end

LilycoveCity_ContestLobby_Text_2C427C: @ 82C427C
	.string "混合大师: 我确实是!\n"
	.string "我是混合大师!\p"
	.string "与我一起混合树果，你将\n"
	.string "见证我对混合树果的精通!$"

LilycoveCity_ContestLobby_Text_2C42F4: @ 82C42F4
	.string "混合大师: 嗯! 所以你是想\n"
	.string "看我在混合时的动作吗?$"

LilycoveCity_ContestLobby_Text_2C4332: @ 82C4332
	.string "嗯!\p"
	.string "所以，你现在太忙了，我明白了！!\p"
	.string "但不要担心!\n"
	.string "我会待在这里一整天!\l"
	.string "快点完成你的事情吧!$"

LilycoveCity_ContestLobby_Text_2C439D: @ 82C439D
	.string "嗯!\p"
	.string "你没有树果!\p"
	.string "我会待在这里一整天!\n"
	.string "快带一些树果过来!$"

LilycoveCity_ContestLobby_Text_2C43FA: @ 82C43FA
	.string "嗯!\n"
	.string "很好!\p"
	.string "顺便问下…\n"
	.string "你现在知道如何用树果来\l"
	.string "混合{POKEBLOCK}吗?$"

LilycoveCity_ContestLobby_Text_2C444C: @ 82C444C
	.string "嗯!\p"
	.string "啊，但这是一个简单的过程!\p"
	.string "当混合的箭头指向你的标记时，\n"
	.string "只需要按下A键就可以。\p"
	.string "这就是所有你需要做的事情。\p"
	.string "当你看到我按下A键的\n"
	.string "精确程度时，你会明白的的。$"

LilycoveCity_ContestLobby_Text_2C451B: @ 82C451B
	.string "很好!\p"
	.string "那我们开始吧!\p"
	.string "与树果混合大师一起,\n"
	.string "开始树果混合!$"

LilycoveCity_ContestLobby_Text_2C4573: @ 82C4573
	.string "嗯!\p"
	.string "你似乎还没有得到\n"
	.string "{POKEBLOCK}盒!\p"
	.string "我会待在这里一整天!\n"
	.string "去取得{POKEBLOCK}盒然后快点回来!$"

LilycoveCity_ContestLobby_Text_2C45E8: @ 82C45E8
	.string "嗯!\p"
	.string "你的{POKEBLOCK}盒似乎已经满了!\p"
	.string "我会待在这里一整天!\n"
	.string "去用掉一些{POKEBLOCK}然后快点回来!$"

LilycoveCity_ContestLobby_Text_2C464B: @ 82C464B
	.string "哇!\n"
	.string "真棒!$"

LilycoveCity_ContestLobby_Text_2C465A: @ 82C465A
	.string "坏透了!$"

LilycoveCity_ContestLobby_Text_2C4669: @ 82C4669
	.string "真是个专家!$"

LilycoveCity_ContestLobby_Text_2C4679: @ 82C4679
	.string "当我与大师一起混合时，\n"
	.string "我们做出了惊人的{POKEBLOCK}!$"

LilycoveCity_ContestLobby_Text_2C46B1: @ 82C46B1
	.string "机器般跟踪箭头\n"
	.string "的眼睛…\p"
	.string "按下A键的手拥有着\n"
	.string "犹如钟表般的精确度…\p"
	.string "拥有这些品质的混合大师\n"
	.string "真是太了不起了。$"

LilycoveCity_ContestLobby_Text_2C4763: @ 82C4763
	.string "混合大师应该在\n"
	.string "练习他的技能。\p"
	.string "有时候，他会来到水静市，\n"
	.string "并待上一整天混合树果。$"

FallarborTown_BattleTentLobby_Text_2C47EB: @ 82C47EB
	.string "欢迎来到对战帐篷\n"
	.string "秋叶镇分址!\p"
	.string "由我向您说明比赛的相关!$"

FallarborTown_BattleTentLobby_Text_2C4843: @ 82C4843
	.string "现在，您想要挑战\n"
	.string "这个比赛了吗?$"

FallarborTown_BattleTentLobby_Text_2C487F: @ 82C487F
	.string "我们期待您下次\n"
	.string "前来挑战!$"

FallarborTown_BattleTentLobby_Text_2C48AC: @ 82C48AC
	.string "在对战帐篷秋叶镇分址,\n"
	.string "我们采取的是淘汰KO赛。\p"
	.string "所有的参赛队伍\n"
	.string "由3只宝可梦组成。\p"
	.string "3只宝可梦必须按照\n"
	.string "它们的出场顺序排列。\p"
	.string "在战斗中,宝可梦将按照\n"
	.string "预先设定好的顺序依次出场。\p"
	.string "宝可梦出场后,直到比赛\n"
	.string "结束前它必须一直战斗。\p"
	.string "如果比赛在3回合内未能分出\n"
	.string "胜负，将由裁判来判定输赢。\p"
	.string "如果您想要发起挑战,\n"
	.string "请先保存游戏进度，\p"
	.string "如果您不保存游戏，\n"
	.string "就无法继续挑战。\p"
	.string "如果您连续战胜\n"
	.string "3名训练师的话，\l"
	.string "我们将给您精美的礼品。$"

FallarborTown_BattleTentLobby_Text_2C4B35: @ 82C4B35
	.string "在您挑战对战帐篷之前，必须\n"
	.string "保存游戏进度，现在记录吗?$"

FallarborTown_BattleTentLobby_Text_2C4B77: @ 82C4B77
	.string "我们提供了两个级别的挑战,\n"
	.string "分别是50级和自由级别。\l"
	.string "您想要挑战那个级别?$"

FallarborTown_BattleTentLobby_Text_2C4BC8: @ 82C4BC8
	.string "好的,现在请您挑选\n"
	.string "3只宝可梦。$"

FallarborTown_BattleTentLobby_Text_2C4BFA: @ 82C4BFA
	.string "亲爱的挑战者!\p"
	.string "您没有挑战所要求\n"
	.string "的3只宝可梦。\p"
	.string "同时，它们不能携带\n"
	.string "相同的道具。\p"
	.string "不允许携带蛋{STR_VAR_1}。\p"
	.string "请在做好相关准备后,\n"
	.string "再回来挑战。$"

FallarborTown_BattleTentLobby_Text_2C4CC0: @ 82C4CC0
	.string "亲爱的挑战者!\p"
	.string "您没有挑战所要求\n"
	.string "的3只宝可梦。\p"
	.string "您必须要携带3只\n"
	.string "不同种类的宝可梦。\p"
	.string "同时，它们不能携带\n"
	.string "相同的道具。\p"
	.string "不允许携带蛋{STR_VAR_1}。\p"
	.string "请在做好相关准备后,\n"
	.string "再回来挑战。$"

FallarborTown_BattleTentLobby_Text_2C4DC3: @ 82C4DC3
	.string "我现在将指引您\n"
	.string "进入对战帐篷。$"

FallarborTown_BattleTentLobby_Text_2C4DED: @ 82C4DED
	.string "亲爱的挑战者!\p"
	.string "在关闭游戏之前您没有\n"
	.string "保存游戏进度,是吗?\p"
	.string "很不幸,因为这导致\n"
	.string "您被取消继续挑战\l"
	.string "的资格了。\p"
	.string "当然,您可以选择重新\n"
	.string "开始挑战。$"

FallarborTown_BattleTentLobby_Text_2C4EC3: @ 82C4EC3
	.string "真是太棒了!您已经连续\n"
	.string "战胜了3名训练师!$"

FallarborTown_BattleTentLobby_Text_2C4EFF: @ 82C4EFF
	.string "请稍等下，需要保存下游戏记录。$"

FallarborTown_BattleTentLobby_Text_2C4F22: @ 82C4F22
	.string "为了奖励您达成3连胜,\n"
	.string "我们将为您颁发礼品。$"

FallarborTown_BattleTentLobby_Text_2C4F69: @ 82C4F69
	.string "{PLAYER}收到了奖品\n"
	.string "{STR_VAR_1}。$"

FallarborTown_BattleTentLobby_Text_2C4F83: @ 82C4F83
	.string "哦?\n"
	.string "您的背包好像装满了。\p"
	.string "希望您清理下背包，\n"
	.string "然后返回领取奖品。$"

FallarborTown_BattleTentLobby_Text_2C4FD7: @ 82C4FD7
	.string "非常感谢您的参与!\p"
	.string "请稍等下，需要保存下游戏记录。$"

FallarborTown_BattleTentLobby_Text_2C501F: @ 82C501F
	.string "我们期待您的\n"
	.string "下次挑战!$"

FallarborTown_BattleTentLobby_Text_2C504C: @ 82C504C
	.string "我们一直在期待着\n"
	.string "您的到来。\p"
	.string "在您开始挑战对战帐篷之前,\n"
	.string "必须要保存下游戏记录，请稍等。$"

VerdanturfTown_BattleTentLobby_Text_2C50C3: @ 82C50C3
	.string "欢迎来到对战帐篷\n"
	.string "绿荫镇分址!\p"
	.string "在这里,将考验训练师与\n"
	.string "宝可梦之间的默契。$"

VerdanturfTown_BattleTentLobby_Text_2C5129: @ 82C5129
	.string "您现在想要参与绿荫镇\n"
	.string "对战帐篷的挑战吗?$"

VerdanturfTown_BattleTentLobby_Text_2C5163: @ 82C5163
	.string "在挑战绿荫镇对战帐篷\n"
	.string "时,有一条规则必须要\l"
	.string "遵守。\p"
	.string "参赛的训练师只允许\n"
	.string "收回或者放出宝可梦。\p"
	.string "训练师不能对他们的\n"
	.string "宝可梦下其他指令。\p"
	.string "而宝可梦仅会根据自己的性格，\n"
	.string "并且凭自己的力量战斗。\p"
	.string "您必须要十分信任您的\n"
	.string "宝可梦，并在旁守护它。\p"
	.string "如果您连续战胜\n"
	.string "3名训练师的话，\l"
	.string "我们将给您精美的礼品。\p"
	.string "如果您想要中断您的挑战，\n"
	.string "请先保存游戏进度。\p"
	.string "如果您在保存之前中断的话,\n"
	.string "您将失去这场比赛的资格。$"

VerdanturfTown_BattleTentLobby_Text_2C539A: @ 82C539A
	.string "当您与您的宝可梦之间的\n"
	.string "羁绊加深时，你再回来。$"

VerdanturfTown_BattleTentLobby_Text_2C53DB: @ 82C53DB
	.string "这里有两个难度级别,\n"
	.string "50级和自由级别。\l"
	.string "您想要参加哪个级别的挑战?$"

VerdanturfTown_BattleTentLobby_Text_2C543D: @ 82C543D
	.string "唉…\p"
	.string "您没有挑战所要求\n"
	.string "的3只宝可梦。\p"
	.string "您必须要携带3只\n"
	.string "不同种类的宝可梦。\p"
	.string "同时，它们不能携带\n"
	.string "相同的道具。\p"
	.string "不允许携带蛋{STR_VAR_1}。\p"
	.string "在您组织好队伍后\n"
	.string "再回来挑战吧。$"

VerdanturfTown_BattleTentLobby_Text_2C5538: @ 82C5538
	.string "唉…\p"
	.string "您没有挑战所要求\n"
	.string "的3只宝可梦。\p"
	.string "您必须要携带3只\n"
	.string "不同种类的宝可梦。\p"
	.string "同时，它们不能携带\n"
	.string "相同的道具。\p"
	.string "不允许携带蛋{STR_VAR_1}。\p"
	.string "在您组织好队伍后\n"
	.string "再回来挑战吧。$"

VerdanturfTown_BattleTentLobby_Text_2C5633: @ 82C5633
	.string "好的,现在请您挑选\n"
	.string "3只宝可梦。$"

VerdanturfTown_BattleTentLobby_Text_2C5662: @ 82C5662
	.string "在您挑战对战帐篷之前，必须\n"
	.string "保存游戏进度，现在记录吗?$"

VerdanturfTown_BattleTentLobby_Text_2C56A2: @ 82C56A2
	.string "好的，\n"
	.string "现在跟我来。$"

VerdanturfTown_BattleTentLobby_Text_2C56B8: @ 82C56B8
	.string "我感到很荣幸可以见证您的\n"
	.string "宝可梦取得如此好的成绩。\p"
	.string "请您稍等一下，我需要\n"
	.string "记录一下这个结果。$"

VerdanturfTown_BattleTentLobby_Text_2C5731: @ 82C5731
	.string "取得了3连胜…\p"
	.string "您与宝可梦之间的羁绊\n"
	.string "似乎更加坚定和真实。$"

VerdanturfTown_BattleTentLobby_Text_2C5791: @ 82C5791
	.string "请您稍微等一下，\n"
	.string "我需要记录一下您的成绩。$"

VerdanturfTown_BattleTentLobby_Text_2C57CD: @ 82C57CD
	.string "为了奖励您达成3连胜,\n"
	.string "我们将为您颁发礼品。$"

SlateportCity_BattleTentLobby_Text_2C5810: @ 82C5810
	.string "欢迎来到对战帐篷\n"
	.string "凯那市分址!\p"
	.string "我将向您介绍交换对战\n"
	.string "锦标赛的相关事宜。$"

SlateportCity_BattleTentLobby_Text_2C586A: @ 82C586A
	.string "你现在想要挑战交换对战\n"
	.string "锦标赛的相关事宜?$"

SlateportCity_BattleTentLobby_Text_2C589C: @ 82C589C
	.string "这里是对战帐篷凯那市分址,\n"
	.string "我们使用租借的宝可梦\l"
	.string "进行交换对战。\p"
	.string "首先,您将租借专门为此\n"
	.string "活动提供的3只宝可梦。\p"
	.string "您需要使用租借的宝可梦\n"
	.string "进行单人对战。\p"
	.string "如果您获得胜利,您可以交换\n"
	.string "其中1只租借的宝可梦。\p"
	.string "重复这样战斗和交换的循环--\n"
	.string "如果您连续获得3次胜利， \l"
	.string "您将可以获得精美的礼品。\p"
	.string "如果您想要中断您的挑战，\n"
	.string "请先保存游戏进度。\p"
	.string "如果您在保存之前中断的话,\n"
	.string "您将失去这场比赛的资格。$"

SlateportCity_BattleTentLobby_Text_2C5AA5: @ 82C5AA5
	.string "我们期待您的下次光临。$"

SlateportCity_BattleTentLobby_Text_2C5AC9: @ 82C5AC9
	.string "您想要挑战哪个级别?\n"
	.string "50级的还是100级?$"

SlateportCity_BattleTentLobby_Text_2C5B06: @ 82C5B06
	.string "在您挑战对战帐篷之前，必须\n"
	.string "保存游戏进度，现在记录吗?$"

SlateportCity_BattleTentLobby_Text_2C5B4A: @ 82C5B4A
	.string "好的,在您的比赛期间，\n"
	.string "我将会暂时保管您的宝可梦。$"

SlateportCity_BattleTentLobby_Text_2C5B8C: @ 82C5B8C
	.string "请走这边。$"

SlateportCity_BattleTentLobby_Text_2C5BA2: @ 82C5BA2
	.string "感谢您的参与!\p"
	.string "我将把保管的宝可梦归还给您，\n"
	.string "同时收回租借的宝可梦。\p"
	.string "我还必须要记录这次比赛结果，\n"
	.string "请您稍等一下。$"

SlateportCity_BattleTentLobby_Text_2C5C30: @ 82C5C30
	.string "我将把保管的宝可梦归还给您，\n"
	.string "同时收回租借的宝可梦。$"

SlateportCity_BattleTentLobby_Text_2C5C6F: @ 82C5C6F
	.string "恭喜!\n"
	.string "您已经连续取得了3场胜利!\p"
	.string "我将把保管的宝可梦归还给您，\n"
	.string "同时收回租借的宝可梦。\p"
	.string "我还必须要记录这次比赛结果，\n"
	.string "请您稍等一下。$"

SlateportCity_BattleTentLobby_Text_2C5D14: @ 82C5D14
	.string "为了奖励您达成3连胜,\n"
	.string "我们将为您颁发礼品。$"

SlateportCity_BattleTentLobby_Text_2C5D52: @ 82C5D52
	.string "哦?\n"
	.string "您似乎没有空间来装这个了。\p"
	.string "请先为您的背包腾出空间，\n"
	.string "然后再来领取礼品。$"

SlateportCity_BattleTentLobby_Text_2C5DA7: @ 82C5DA7
	.string "我们一直在等您!\p"
	.string "在您开始挑战之前,\n"
	.string "必须保存游戏进度。$"

SlateportCity_BattleTentLobby_Text_2C5DFA: @ 82C5DFA
	.string "很抱歉的告诉您,由于您在关闭\n"
	.string "游戏之前没有保存游戏进度，\p "
	.string "因此，您被取消继续挑战的\n"
	.string "资格了。$"

SlateportCity_BattleTentLobby_Text_2C5E85: @ 82C5E85
	.string "我们将把您的宝可梦归还给您。$"

SlateportCity_BattleTentLobby_Text_2C5EA9: @ 82C5EA9
	.string "{PLAYER}获得了奖品\n"
	.string "{STR_VAR_1}。$"

SlateportCity_BattleTentLobby_Text_2C5EC3: @ 82C5EC3
	.string "列出了交换对战的规则。$"

SlateportCity_BattleTentLobby_Text_2C5EE5: @ 82C5EE5
	.string "您想阅读哪个部分?$"

SlateportCity_BattleTentLobby_Text_2C5F08: @ 82C5F08
	.string "在交换对战比赛中,您只能\n"
	.string "使用3只宝可梦。\p"
	.string "无论您是租借还是交换,\n"
	.string "您的队伍中都不能同时有\l"
	.string "两只或以上相同的宝可梦。$"

SlateportCity_BattleTentLobby_Text_2C5F9D: @ 82C5F9D
	.string "您仅能与刚才战胜的训练师\n"
	.string "交换租借的宝可梦。\p"
	.string "您所能交换到的宝可梦为\n"
	.string "该训练师使用的宝可梦。$"

SlateportCity_BattleTentLobby_Text_2C6020: @ 82C6020
	.string "在您赢得每场胜利后, \n"
	.string "您可以与您战胜的\l"
	.string "训练师交换宝可梦。\p"
	.string "您无法与第三名训练师\n"
	.string "交换宝可梦。$"

SlateportCity_BattleTentLobby_Text_2C60C0: @ 82C60C0
	.string "在交换宝可梦时，\n"
	.string "有两点需要注意的。\p"
	.string "首先,在交换过程中, \n"
	.string "您无法查看要交换的\l"
	.string "宝可梦的状态\p"
	.string "第二,您队伍中的宝可梦\n"
	.string "将按照您租用它们时的\l"
	.string "顺序排列。\p"
	.string "即使进行宝可梦的交换，\n"
	.string "该顺序也不会改变。$"

SlateportCity_BattleTentLobby_Text_2C61FE: @ 82C61FE
	.string "凯那市对战帐篷使用\n"
	.string "的宝可梦都是租借的。\p"
	.string "所有租借的宝可梦的\n"
	.string "等级都为30级。$"

VerdanturfTown_BattleTentLobby_Text_2C6261: @ 82C6261
	.string "这里列出了绿荫镇\n"
	.string "对战帐篷的规则。$"

VerdanturfTown_BattleTentLobby_Text_2C628E: @ 82C628E
	.string "您想要阅读哪个部分?$"

VerdanturfTown_BattleTentLobby_Text_2C62B1: @ 82C62B1
	.string "这里是绿荫镇对战帐篷,\n"
	.string "宝可梦在这里将会自己\l"
	.string "思考以及对战。\p"
	.string "不同于在野外生活的宝可梦, \n"
	.string "与人生活的宝可梦会依据它们\l"
	.string "的性格展现出不同的行为。$"

VerdanturfTown_BattleTentLobby_Text_2C636D: @ 82C636D
	.string "依据它们的性格,一些宝可梦\n"
	.string "可能更喜欢战斗。\p"
	.string "另一些宝可梦更喜欢躲避起来\n"
	.string "防止受到伤害。\p"
	.string "还有一些宝可梦可能会使它们\n"
	.string "的对手混乱或者发怒。\p"
	.string "依据它们的性格, 宝可梦\n"
	.string "会有喜欢或者很擅长\l"
	.string "使用的技能。\p"
	.string "同时可能会有不擅长或者\n"
	.string "不喜欢使用的技能。$"

VerdanturfTown_BattleTentLobby_Text_2C64BA: @ 82C64BA
	.string "有可以对敌人直接造成\n"
	.string "伤害的攻击技能。\p"
	.string "也有可以用来抵抗对手\n"
	.string "攻击的防守技能，或者\l"
	.string "恢复HP的技能。\p"
	.string "还有一些具有特殊效果\n"
	.string "的技能，会让对手陷入\l"
	.string "异常状态，比如中毒或者\l"
	.string "麻痹等。\p"
	.string "宝可梦将会考虑使用\n"
	.string "这3个类别的技能。$"

VerdanturfTown_BattleTentLobby_Text_2C6612: @ 82C6612
	.string "如果没有训练师下达指令,\n"
	.string "宝可梦可能无法很好地\l"
	.string "使用某些技能。\p"
	.string "宝可梦不擅长使用自己\n"
	.string "不喜欢的技能。\p"
	.string "如果宝可梦学会的技能\n"
	.string "不符合自己的性格，那么\l"
	.string "它将无法发回出潜力。$"

VerdanturfTown_BattleTentLobby_Text_2C671E: @ 82C671E
	.string "根据它们的性格,在遇到麻烦后，\n"
	.string "宝可梦可能会使用与其性格\l"
	.string "不相符的技能。\p"
	.string "如果宝可梦开始有奇怪的行为，\n"
	.string "请注意观察它的状态。$"

FallarborTown_BattleTentLobby_Text_2C67CD: @ 82C67CD
VerdanturfTown_BattleTentLobby_Text_2C67CD: @ 82C67CD
	.string "在这个对战帐篷中,对手使用的\n"
	.string "宝可梦的等级将根据您的宝可梦\l"
	.string "等级来调整。\p"
	.string "然而,您所遇到的训练师宝可梦\n"
	.string "等级不会低于30级。$"

VerdanturfTown_BattleTentLobby_Text_2C6878: @ 82C6878
	.string "这里列出了绿荫镇\n"
	.string "对战帐篷的规则。$"

LilycoveCity_Harbor_Text_2C68A5: @ 82C68A5
	.string "有什么事吗,年轻人?\p"
	.string "什么,你有一张破旧\n"
	.string "的航海图?\p"
	.string "让我看下。\n"
	.string "… … … … … …\p"
	.string "孩子,这我恐怕帮不了你，\n"
	.string "这太远了…$"

LilycoveCity_Harbor_Text_2C6951: @ 82C6951
	.string "哈奇老人: 请稍等下!\p"
	.string "为什么要拒绝帮我\n"
	.string "那么多的人?$"

LilycoveCity_Harbor_Text_2C69AA: @ 82C69AA
	.string "{PLAYER}{KUN},我真的很抱歉。\p"
	.string "你来寻求我的帮助,\n"
	.string "我却几乎把你拒之门外。\p"
	.string "来吧,让我来帮助你一次。\p"
	.string "我的意思是我们马上开航!\p"
	.string "让我们去这张古航海图上\n"
	.string "的岛屿吧!$"

LilycoveCity_Harbor_Text_2C6A71: @ 82C6A71
	.string "是谁带过来了那张\n"
	.string "奇怪的船票?\p"
	.string "你要去的地方是一个\n"
	.string "遥远的岛屿。\p"
	.string "没人知道那里有什么等待我们…\p"
	.string "这燃起了我身为一名水手\n"
	.string "的激情!\p"
	.string "出发吧,年轻人!$"

FarawayIsland_Entrance_Text_2C6B42: @ 82C6B42
	.string "哈奇老人可以如此\n"
	.string "变幻无常…\p"
	.string "你要返回水静市吗?$"

BirthIsland_Harbor_Text_2C6B90: @ 82C6B90
	.string "真是奇怪的岛屿，嗯?\n"
	.string "你想要返回水静市吗?$"

LilycoveCity_Harbor_Text_2C6BD4: @ 82C6BD4
	.string "是谁带过来了那些\n"
	.string "奇怪的船票?\p"
	.string "… … …嗯.\p"
	.string "这些船票会带领你前往\n"
	.string "很遥远的岛屿。\p"
	.string "没有人知道那里有什么,\n"
	.string "或者会发生什么。\p"
	.string "这燃起了我身为一名水手\n"
	.string "的激情!\p"
	.string "出发吧,年轻人!\n"
	.string "你想要先去那里呢?$"

NavelRock_Harbor_Text_2C6CE6: @ 82C6CE6
	.string "你…你听到了那个声音吗?\n"
	.string "我好像听到了深处传来了声音。\p"
	.string "你确定这里安全吗?\n"
	.string "你认为我们应该离开吗?$"

FarawayIsland_Entrance_Text_2C6D5A: @ 82C6D5A
	.string "好像是很久远之前留下\n"
	.string "的字迹，看不太清楚…\p"
	.string "“…月6日\n"
	.string "如果有…再次踏足…里，\l"
	.string "我希…他是个…善…\l"
	.string "的人…”$"

FarawayIsland_Interior_Text_2C6DFF: @ 82C6DFF
	.string "嗯…$"

MauvilleCity_Text_2C6E05: @ 82C6E05
	.string "This move can be learned only\n"
	.string "once. Is that okay?$"

SlateportCity_PokemonFanClub_Text_2C6E37: @ 82C6E37
	.string "Heh! My POKéMON totally rules!\n"
	.string "It's cooler than any POKéMON!\p"
	.string "I was lipping off with a swagger in\n"
	.string "my step like that when the CHAIRMAN\l"
	.string "chewed me out.\p"
	.string "That took the swagger out of my step.\p"
	.string "If you'd like, I'll teach the move\n"
	.string "SWAGGER to a POKéMON of yours.$"

SlateportCity_PokemonFanClub_Text_2C6F33: @ 82C6F33
	.string "What, no? Can't you get into\n"
	.string "the spirit of things?$"

SlateportCity_PokemonFanClub_Text_2C6F66: @ 82C6F66
	.string "All right, which POKéMON wants to\n"
	.string "learn how to SWAGGER?$"

SlateportCity_PokemonFanClub_Text_2C6F9E: @ 82C6F9E
	.string "I'll just praise my POKéMON from now\n"
	.string "on without the swagger.$"

MauvilleCity_Text_2C6FDB: @ 82C6FDB
	.string "Did you know that you can go from\n"
	.string "here a long way in that direction\l"
	.string "without changing direction?\p"
	.string "I might even be able to roll\n"
	.string "that way.\p"
	.string "Do you think your POKéMON will\n"
	.string "want to roll, too?\p"
	.string "I can teach one the move ROLLOUT\n"
	.string "if you'd like.$"

MauvilleCity_Text_2C70C4: @ 82C70C4
	.string "You don't need to be shy about it.\n"
	.string "Let's roll!$"

MauvilleCity_Text_2C70F3: @ 82C70F3
	.string "Ehehe, sure thing! It'd be great if\n"
	.string "the POKéMON looked like me.$"

MauvilleCity_Text_2C7133: @ 82C7133
	.string "Rolling around in the grass makes me\n"
	.string "happy. Come on, let's roll!$"

VerdanturfTown_PokemonCenter_1F_Text_2C7174: @ 82C7174
	.string "There's a move that gets stronger\n"
	.string "when you keep using it in a row.\p"
	.string "It's a BUG-type move, and it is\n"
	.string "wickedly cool.\p"
	.string "It's called FURY CUTTER.\n"
	.string "Want me to teach it to a POKéMON?$"

VerdanturfTown_PokemonCenter_1F_Text_2C7221: @ 82C7221
	.string "We're not on the same wavelength.$"

VerdanturfTown_PokemonCenter_1F_Text_2C7243: @ 82C7243
	.string "Yay!\n"
	.string "Show me which POKéMON I should teach.$"

VerdanturfTown_PokemonCenter_1F_Text_2C726E: @ 82C726E
	.string "I get a thrill watching to see if\n"
	.string "the move keeps hitting in succession!$"

LavaridgeTown_House_Text_2C72B6: @ 82C72B6
	.string "Ah, young one!\p"
	.string "I am also a young one, but I mimic\n"
	.string "the styles and speech of the elderly\l"
	.string "folks of this town.\p"
	.string "What do you say, young one?\n"
	.string "Would you agree to it if I were to\l"
	.string "offer to teach the move MIMIC?$"

LavaridgeTown_House_Text_2C737F: @ 82C737F
	.string "Oh, boo! I wanted to teach MIMIC\n"
	.string "to your POKéMON!$"

LavaridgeTown_House_Text_2C73B1: @ 82C73B1
	.string "Fwofwo! And so I shall!\n"
	.string "Let me see the POKéMON\l"
	.string "you wish me to teach.$"

LavaridgeTown_House_Text_2C73F6: @ 82C73F6
	.string "MIMIC is a move of great depth.\p"
	.string "Could you execute it to perfection\n"
	.string "as well as me…?$"

FallarborTown_Mart_Text_2C7449: @ 82C7449
	.string "I want all sorts of things!\n"
	.string "But I used up my allowance…\p"
	.string "Wouldn't it be nice if there were\n"
	.string "a spell that made money appear when\l"
	.string "you waggle a finger?\p"
	.string "If you want, I can teach your POKéMON\n"
	.string "the move METRONOME.\p"
	.string "Money won't appear, but your POKéMON\n"
	.string "will waggle a finger. Yes?$"

FallarborTown_Mart_Text_2C7556: @ 82C7556
	.string "Okay. I'll be here if you change\n"
	.string "your mind.$"

FallarborTown_Mart_Text_2C7582: @ 82C7582
	.string "Okay! I'll teach it!\n"
	.string "Which POKéMON should I teach?$"

FallarborTown_Mart_Text_2C75B5: @ 82C75B5
	.string "When a POKéMON waggles its finger\n"
	.string "like a METRONOME, all sorts of nice\l"
	.string "things happen.\p"
	.string "Wouldn't it be nice if we could\n"
	.string "use it, too?$"

FortreeCity_House2_Text_2C7637: @ 82C7637
	.string "Humph! My wife relies on HIDDEN\n"
	.string "POWER to stay awake.\p"
	.string "She should just take a nap like I do,\n"
	.string "and SLEEP TALK.\p"
	.string "I can teach your POKéMON how to\n"
	.string "SLEEP TALK instead. Interested?$"

FortreeCity_House2_Text_2C76E2: @ 82C76E2
	.string "Oh, fine, fine. You want to stay awake\n"
	.string "with HIDDEN POWER, too…$"

FortreeCity_House2_Text_2C7721: @ 82C7721
	.string "Ah, an appreciative child!\n"
	.string "Which POKéMON should I teach?$"

FortreeCity_House2_Text_2C775A: @ 82C775A
	.string "I've never once gotten my wife's\n"
	.string "coin trick right.\p"
	.string "I would be happy if I got it right\n"
	.string "even as I SLEEP TALK…$"

LilycoveCity_DepartmentStoreRooftop_Text_2C77C6: @ 82C77C6
	.string "When I see the wide world from up\n"
	.string "here on the roof…\p"
	.string "I think about how nice it would be\n"
	.string "if there were more than just one me\l"
	.string "so I could enjoy all sorts of lives.\p"
	.string "Of course it's not possible.\n"
	.string "Giggle…\p"
	.string "I know! Would you be interested in\n"
	.string "having a POKéMON learn SUBSTITUTE?$"

LilycoveCity_DepartmentStoreRooftop_Text_2C78D1: @ 82C78D1
	.string "Oh, no?\p"
	.string "A POKéMON can make a copy of\n"
	.string "itself using it, you know.$"

LilycoveCity_DepartmentStoreRooftop_Text_2C7911: @ 82C7911
	.string "Giggle…\n"
	.string "Which POKéMON do you want me to\l"
	.string "teach SUBSTITUTE?$"

LilycoveCity_DepartmentStoreRooftop_Text_2C794B: @ 82C794B
	.string "We human beings should enjoy our\n"
	.string "own lives to the utmost!\p"
	.string "I hope you'll get that way, too!$"

MossdeepCity_Text_2C79A6: @ 82C79A6
	.string "I can't do this anymore!\p"
	.string "It's utterly hopeless!\p"
	.string "I'm a FIGHTING-type TRAINER,\n"
	.string "so I can't win at the MOSSDEEP GYM\l"
	.string "no matter how hard I try!\p"
	.string "Argh! Punch! Punch! Punch!\n"
	.string "Punch! Punch! Punch!\p"
	.string "What, don't look at me that way!\n"
	.string "I'm only hitting the ground!\p"
	.string "Or do you want me to teach your\n"
	.string "POKéMON DYNAMICPUNCH?$"

MossdeepCity_Text_2C7AD4: @ 82C7AD4
	.string "Darn! You're even making fun of me?\n"
	.string "Punch! Punch! Punch!$"

MossdeepCity_Text_2C7B0D: @ 82C7B0D
	.string "What? You do? You're a good person!\n"
	.string "Which POKéMON should I teach?$"

MossdeepCity_Text_2C7B4F: @ 82C7B4F
	.string "我希望你使用爆裂拳\n"
	.string "来赢得绿岭道馆!$"

SootopolisCity_PokemonCenter_1F_Text_2C7B8E: @ 82C7B8E
	.string "唉…\p"
	.string "琉璃市道馆馆主真是\n"
	.string "太令人钦佩了。\p"
	.string "但这也意味着，要引起\n"
	.string "他的注意，我会有很多竞争对手。\p"
	.string "他之前对舍身冲撞感兴趣，\n"
	.string "而我完全不能引起他的注意。\p"
	.string "拜托了，让我教你的宝可梦\n"
	.string "学会舍身冲撞。$"

SootopolisCity_PokemonCenter_1F_Text_2C7C7E: @ 82C7C7E
	.string "哦…\n"
	.string "你竟然拒绝了我…$"

SootopolisCity_PokemonCenter_1F_Text_2C7C98: @ 82C7C98
	.string "好的，你要让哪只宝可梦学\n"
	.string "舍身冲撞呢?$"

SootopolisCity_PokemonCenter_1F_Text_2C7CC8: @ 82C7CC8
	.string "我不会再为爱而活!\n"
	.string "我会变得更坚强!$"

PacifidlogTown_PokemonCenter_1F_Text_2C7CFA: @ 82C7CFA
	.string "我根本就没打算一直\n"
	.string "待在这乡下。\p"
	.string "等着瞧吧，总有一天\n"
	.string "我会离开这去大干一番。\p"
	.string "说真的,到时候我会到城里面，\n"
	.string "而且会引起爆炸性的轰动!\p"
	.string "如果你相信我,我会很乐意\n"
	.string "教你的宝可梦学会大爆炸!$"

PacifidlogTown_PokemonCenter_1F_Text_2C7E04: @ 82C7E04
	.string "什么!因为我住在乡下， \n"
	.string "所以你拒绝我?$"

PacifidlogTown_PokemonCenter_1F_Text_2C7E40: @ 82C7E40
	.string "很好!这是大爆炸!\n"
	.string "你的哪只宝可梦想要爆炸?$"

PacifidlogTown_PokemonCenter_1F_Text_2C7E7A: @ 82C7E7A
	.string "我已经教宝可梦如何使用\n"
	.string "大爆炸很长一段时间了，\l"
	.string "但我自己还没有使用过…\p"
	.string "可能在我的内心深处,\n"
	.string "我宁愿留在这里…$"

SlateportCity_PokemonFanClub_EventScript_2C7F16:: @ 82C7F16
	lock
	faceplayer
	goto_if_set FLAG_MOVE_TUTOR_TAUGHT_SWAGGER, SlateportCity_PokemonFanClub_EventScript_2C7F74
	msgbox SlateportCity_PokemonFanClub_Text_2C6E37, MSGBOX_YESNO
	compare VAR_RESULT, 0
	goto_if_eq SlateportCity_PokemonFanClub_EventScript_2C7F6A
	call SlateportCity_PokemonFanClub_EventScript_2C832D
	compare VAR_RESULT, 0
	goto_if_eq SlateportCity_PokemonFanClub_EventScript_2C7F6A
	msgbox SlateportCity_PokemonFanClub_Text_2C6F66, MSGBOX_DEFAULT
	setvar VAR_0x8005, 23
	call EventScript_ShowPartyMenu
	compare VAR_RESULT, 0
	goto_if_eq SlateportCity_PokemonFanClub_EventScript_2C7F6A
	setflag FLAG_MOVE_TUTOR_TAUGHT_SWAGGER
	goto SlateportCity_PokemonFanClub_EventScript_2C7F74
	end

SlateportCity_PokemonFanClub_EventScript_2C7F6A:: @ 82C7F6A
	msgbox SlateportCity_PokemonFanClub_Text_2C6F33, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_2C7F74:: @ 82C7F74
	msgbox SlateportCity_PokemonFanClub_Text_2C6F9E, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_2C7F7E:: @ 82C7F7E
	lock
	faceplayer
	goto_if_set FLAG_MOVE_TUTOR_TAUGHT_ROLLOUT, MauvilleCity_EventScript_2C7FDC
	msgbox MauvilleCity_Text_2C6FDB, MSGBOX_YESNO
	compare VAR_RESULT, 0
	goto_if_eq MauvilleCity_EventScript_2C7FD2
	call MauvilleCity_EventScript_2C832D
	compare VAR_RESULT, 0
	goto_if_eq MauvilleCity_EventScript_2C7FD2
	msgbox MauvilleCity_Text_2C70F3, MSGBOX_DEFAULT
	setvar VAR_0x8005, 16
	call EventScript_ShowPartyMenu
	compare VAR_RESULT, 0
	goto_if_eq MauvilleCity_EventScript_2C7FD2
	setflag FLAG_MOVE_TUTOR_TAUGHT_ROLLOUT
	goto MauvilleCity_EventScript_2C7FDC
	end

MauvilleCity_EventScript_2C7FD2:: @ 82C7FD2
	msgbox MauvilleCity_Text_2C70C4, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_2C7FDC:: @ 82C7FDC
	msgbox MauvilleCity_Text_2C7133, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_PokemonCenter_1F_EventScript_2C7FE6:: @ 82C7FE6
	lock
	faceplayer
	goto_if_set FLAG_MOVE_TUTOR_TAUGHT_FURY_CUTTER, VerdanturfTown_PokemonCenter_1F_EventScript_2C8044
	msgbox VerdanturfTown_PokemonCenter_1F_Text_2C7174, MSGBOX_YESNO
	compare VAR_RESULT, 0
	goto_if_eq VerdanturfTown_PokemonCenter_1F_EventScript_2C803A
	call VerdanturfTown_PokemonCenter_1F_EventScript_2C832D
	compare VAR_RESULT, 0
	goto_if_eq VerdanturfTown_PokemonCenter_1F_EventScript_2C803A
	msgbox VerdanturfTown_PokemonCenter_1F_Text_2C7243, MSGBOX_DEFAULT
	setvar VAR_0x8005, 29
	call EventScript_ShowPartyMenu
	compare VAR_RESULT, 0
	goto_if_eq VerdanturfTown_PokemonCenter_1F_EventScript_2C803A
	setflag FLAG_MOVE_TUTOR_TAUGHT_FURY_CUTTER
	goto VerdanturfTown_PokemonCenter_1F_EventScript_2C8044
	end

VerdanturfTown_PokemonCenter_1F_EventScript_2C803A:: @ 82C803A
	msgbox VerdanturfTown_PokemonCenter_1F_Text_2C7221, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_PokemonCenter_1F_EventScript_2C8044:: @ 82C8044
	msgbox VerdanturfTown_PokemonCenter_1F_Text_2C726E, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_House_EventScript_2C804E:: @ 82C804E
	lock
	faceplayer
	goto_if_set FLAG_MOVE_TUTOR_TAUGHT_MIMIC, LavaridgeTown_House_EventScript_2C80AC
	msgbox LavaridgeTown_House_Text_2C72B6, MSGBOX_YESNO
	compare VAR_RESULT, 0
	goto_if_eq LavaridgeTown_House_EventScript_2C80A2
	call LavaridgeTown_House_EventScript_2C832D
	compare VAR_RESULT, 0
	goto_if_eq LavaridgeTown_House_EventScript_2C80A2
	msgbox LavaridgeTown_House_Text_2C73B1, MSGBOX_DEFAULT
	setvar VAR_0x8005, 7
	call EventScript_ShowPartyMenu
	compare VAR_RESULT, 0
	goto_if_eq LavaridgeTown_House_EventScript_2C80A2
	setflag FLAG_MOVE_TUTOR_TAUGHT_MIMIC
	goto LavaridgeTown_House_EventScript_2C80AC
	end

LavaridgeTown_House_EventScript_2C80A2:: @ 82C80A2
	msgbox LavaridgeTown_House_Text_2C737F, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_House_EventScript_2C80AC:: @ 82C80AC
	msgbox LavaridgeTown_House_Text_2C73F6, MSGBOX_DEFAULT
	release
	end

FallarborTown_Mart_EventScript_2C80B6:: @ 82C80B6
	lock
	faceplayer
	goto_if_set FLAG_MOVE_TUTOR_TAUGHT_METRONOME, FallarborTown_Mart_EventScript_2C8114
	msgbox FallarborTown_Mart_Text_2C7449, MSGBOX_YESNO
	compare VAR_RESULT, 0
	goto_if_eq FallarborTown_Mart_EventScript_2C810A
	call FallarborTown_Mart_EventScript_2C832D
	compare VAR_RESULT, 0
	goto_if_eq FallarborTown_Mart_EventScript_2C810A
	msgbox FallarborTown_Mart_Text_2C7582, MSGBOX_DEFAULT
	setvar VAR_0x8005, 8
	call EventScript_ShowPartyMenu
	compare VAR_RESULT, 0
	goto_if_eq FallarborTown_Mart_EventScript_2C810A
	setflag FLAG_MOVE_TUTOR_TAUGHT_METRONOME
	goto FallarborTown_Mart_EventScript_2C8114
	end

FallarborTown_Mart_EventScript_2C810A:: @ 82C810A
	msgbox FallarborTown_Mart_Text_2C7556, MSGBOX_DEFAULT
	release
	end

FallarborTown_Mart_EventScript_2C8114:: @ 82C8114
	msgbox FallarborTown_Mart_Text_2C75B5, MSGBOX_DEFAULT
	release
	end

FortreeCity_House2_EventScript_2C811E:: @ 82C811E
	lock
	faceplayer
	goto_if_set FLAG_MOVE_TUTOR_TAUGHT_SLEEP_TALK, FortreeCity_House2_EventScript_2C817C
	msgbox FortreeCity_House2_Text_2C7637, MSGBOX_YESNO
	compare VAR_RESULT, 0
	goto_if_eq FortreeCity_House2_EventScript_2C8172
	call FortreeCity_House2_EventScript_2C832D
	compare VAR_RESULT, 0
	goto_if_eq FortreeCity_House2_EventScript_2C8172
	msgbox FortreeCity_House2_Text_2C7721, MSGBOX_DEFAULT
	setvar VAR_0x8005, 24
	call EventScript_ShowPartyMenu
	compare VAR_RESULT, 0
	goto_if_eq FortreeCity_House2_EventScript_2C8172
	setflag FLAG_MOVE_TUTOR_TAUGHT_SLEEP_TALK
	goto FortreeCity_House2_EventScript_2C817C
	end

FortreeCity_House2_EventScript_2C8172:: @ 82C8172
	msgbox FortreeCity_House2_Text_2C76E2, MSGBOX_DEFAULT
	release
	end

FortreeCity_House2_EventScript_2C817C:: @ 82C817C
	msgbox FortreeCity_House2_Text_2C775A, MSGBOX_DEFAULT
	release
	end

LilycoveCity_DepartmentStoreRooftop_EventScript_2C8186:: @ 82C8186
	lock
	faceplayer
	goto_if_set FLAG_MOVE_TUTOR_TAUGHT_SUBSTITUTE, LilycoveCity_DepartmentStoreRooftop_EventScript_2C81E4
	msgbox LilycoveCity_DepartmentStoreRooftop_Text_2C77C6, MSGBOX_YESNO
	compare VAR_RESULT, 0
	goto_if_eq LilycoveCity_DepartmentStoreRooftop_EventScript_2C81DA
	call LilycoveCity_DepartmentStoreRooftop_EventScript_2C832D
	compare VAR_RESULT, 0
	goto_if_eq LilycoveCity_DepartmentStoreRooftop_EventScript_2C81DA
	msgbox LilycoveCity_DepartmentStoreRooftop_Text_2C7911, MSGBOX_DEFAULT
	setvar VAR_0x8005, 14
	call EventScript_ShowPartyMenu
	compare VAR_RESULT, 0
	goto_if_eq LilycoveCity_DepartmentStoreRooftop_EventScript_2C81DA
	setflag FLAG_MOVE_TUTOR_TAUGHT_SUBSTITUTE
	goto LilycoveCity_DepartmentStoreRooftop_EventScript_2C81E4
	end

LilycoveCity_DepartmentStoreRooftop_EventScript_2C81DA:: @ 82C81DA
	msgbox LilycoveCity_DepartmentStoreRooftop_Text_2C78D1, MSGBOX_DEFAULT
	release
	end

LilycoveCity_DepartmentStoreRooftop_EventScript_2C81E4:: @ 82C81E4
	msgbox LilycoveCity_DepartmentStoreRooftop_Text_2C794B, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_2C81EE:: @ 82C81EE
	lock
	faceplayer
	goto_if_set FLAG_MOVE_TUTOR_TAUGHT_DYNAMICPUNCH, MossdeepCity_EventScript_2C824C
	msgbox MossdeepCity_Text_2C79A6, MSGBOX_YESNO
	compare VAR_RESULT, 0
	goto_if_eq MossdeepCity_EventScript_2C8242
	call MossdeepCity_EventScript_2C832D
	compare VAR_RESULT, 0
	goto_if_eq MossdeepCity_EventScript_2C8242
	msgbox MossdeepCity_Text_2C7B0D, MSGBOX_DEFAULT
	setvar VAR_0x8005, 15
	call EventScript_ShowPartyMenu
	compare VAR_RESULT, 0
	goto_if_eq MossdeepCity_EventScript_2C8242
	setflag FLAG_MOVE_TUTOR_TAUGHT_DYNAMICPUNCH
	goto MossdeepCity_EventScript_2C824C
	end

MossdeepCity_EventScript_2C8242:: @ 82C8242
	msgbox MossdeepCity_Text_2C7AD4, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_2C824C:: @ 82C824C
	msgbox MossdeepCity_Text_2C7B4F, MSGBOX_DEFAULT
	release
	end

SootopolisCity_PokemonCenter_1F_EventScript_2C8256:: @ 82C8256
	lock
	faceplayer
	goto_if_set FLAG_MOVE_TUTOR_TAUGHT_DOUBLE_EDGE, SootopolisCity_PokemonCenter_1F_EventScript_2C82B4
	msgbox SootopolisCity_PokemonCenter_1F_Text_2C7B8E, MSGBOX_YESNO
	compare VAR_RESULT, 0
	goto_if_eq SootopolisCity_PokemonCenter_1F_EventScript_2C82AA
	call SootopolisCity_PokemonCenter_1F_EventScript_2C832D
	compare VAR_RESULT, 0
	goto_if_eq SootopolisCity_PokemonCenter_1F_EventScript_2C82AA
	msgbox SootopolisCity_PokemonCenter_1F_Text_2C7C98, MSGBOX_DEFAULT
	setvar VAR_0x8005, 4
	call EventScript_ShowPartyMenu
	compare VAR_RESULT, 0
	goto_if_eq SootopolisCity_PokemonCenter_1F_EventScript_2C82AA
	setflag FLAG_MOVE_TUTOR_TAUGHT_DOUBLE_EDGE
	goto SootopolisCity_PokemonCenter_1F_EventScript_2C82B4
	end

SootopolisCity_PokemonCenter_1F_EventScript_2C82AA:: @ 82C82AA
	msgbox SootopolisCity_PokemonCenter_1F_Text_2C7C7E, MSGBOX_DEFAULT
	release
	end

SootopolisCity_PokemonCenter_1F_EventScript_2C82B4:: @ 82C82B4
	msgbox SootopolisCity_PokemonCenter_1F_Text_2C7CC8, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_PokemonCenter_1F_EventScript_2C82BE:: @ 82C82BE
	lock
	faceplayer
	goto_if_set FLAG_MOVE_TUTOR_TAUGHT_EXPLOSION, PacifidlogTown_PokemonCenter_1F_EventScript_2C831C
	msgbox PacifidlogTown_PokemonCenter_1F_Text_2C7CFA, MSGBOX_YESNO
	compare VAR_RESULT, 0
	goto_if_eq PacifidlogTown_PokemonCenter_1F_EventScript_2C8312
	call PacifidlogTown_PokemonCenter_1F_EventScript_2C832D
	compare VAR_RESULT, 0
	goto_if_eq PacifidlogTown_PokemonCenter_1F_EventScript_2C8312
	msgbox PacifidlogTown_PokemonCenter_1F_Text_2C7E40, MSGBOX_DEFAULT
	setvar VAR_0x8005, 12
	call EventScript_ShowPartyMenu
	compare VAR_RESULT, 0
	goto_if_eq PacifidlogTown_PokemonCenter_1F_EventScript_2C8312
	setflag FLAG_MOVE_TUTOR_TAUGHT_EXPLOSION
	goto PacifidlogTown_PokemonCenter_1F_EventScript_2C831C
	end

PacifidlogTown_PokemonCenter_1F_EventScript_2C8312:: @ 82C8312
	msgbox PacifidlogTown_PokemonCenter_1F_Text_2C7E04, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_PokemonCenter_1F_EventScript_2C831C:: @ 82C831C
	msgbox PacifidlogTown_PokemonCenter_1F_Text_2C7E7A, MSGBOX_DEFAULT
	release
	end

EventScript_ShowPartyMenu:: @ 82C8326
	special sub_81B892C
	waitstate
	lock
	faceplayer
	return

FallarborTown_Mart_EventScript_2C832D:: @ 82C832D
FortreeCity_House2_EventScript_2C832D:: @ 82C832D
LavaridgeTown_House_EventScript_2C832D:: @ 82C832D
LilycoveCity_DepartmentStoreRooftop_EventScript_2C832D:: @ 82C832D
MauvilleCity_EventScript_2C832D:: @ 82C832D
MossdeepCity_EventScript_2C832D:: @ 82C832D
PacifidlogTown_PokemonCenter_1F_EventScript_2C832D:: @ 82C832D
SlateportCity_PokemonFanClub_EventScript_2C832D:: @ 82C832D
SootopolisCity_PokemonCenter_1F_EventScript_2C832D:: @ 82C832D
VerdanturfTown_PokemonCenter_1F_EventScript_2C832D:: @ 82C832D
	msgbox MauvilleCity_Text_2C6E05, MSGBOX_YESNO
	return

TrainerHill_1F_MapScript1_2C8336: @ 82C8336
TrainerHill_2F_MapScript1_2C8336: @ 82C8336
TrainerHill_3F_MapScript1_2C8336: @ 82C8336
TrainerHill_4F_MapScript1_2C8336: @ 82C8336
TrainerHill_Roof_MapScript1_2C8336: @ 82C8336
	setvar VAR_TEMP_2, 0
	setvar VAR_0x8004, TRAINER_HILL_FUNC_RESUME_TIMER
	special CallTrainerHillFunction
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 5
	special CallFrontierUtilFunc
	compare VAR_RESULT, B_OUTCOME_LOST
	goto_if_eq TrainerHill_1F_EventScript_2C83C9
	compare VAR_RESULT, B_OUTCOME_DREW
	goto_if_eq TrainerHill_1F_EventScript_2C83C9
	compare VAR_RESULT, B_OUTCOME_FORFEITED
	goto_if_eq TrainerHill_1F_EventScript_2C83C9
	end

TrainerHill_1F_MapScript2_2C8372: @ 82C8372
TrainerHill_2F_MapScript2_2C8372: @ 82C8372
	map_script_2 VAR_TEMP_3, 0, TrainerHill_1F_EventScript_2C837C
	.2byte 0

TrainerHill_1F_EventScript_2C837C:: @ 82C837C
	setvar VAR_TEMP_3, 1
@ forced stop

TrainerHill_1F_MapScript2_2C8381: @ 82C8381
TrainerHill_2F_MapScript2_2C8381: @ 82C8381
TrainerHill_3F_MapScript2_2C8381: @ 82C8381
TrainerHill_4F_MapScript2_2C8381: @ 82C8381
TrainerHill_Roof_MapScript2_2C8381: @ 82C8381
	map_script_2 VAR_TEMP_2, 0, TrainerHill_1F_EventScript_2C83A6
	map_script_2 VAR_TEMP_1, 1, TrainerHill_1F_EventScript_2C83DF
	.2byte 0

EventScript_TrainerHillTimer:: @ 82C8393
	lockall
	setvar VAR_0x8004, TRAINER_HILL_FUNC_7
	special CallTrainerHillFunction
	msgbox TrainerHill_Entrance_Text_268D47, MSGBOX_DEFAULT
	releaseall
	end

TrainerHill_1F_EventScript_2C83A6:: @ 82C83A6
	setvar VAR_TEMP_2, 1
	setvar VAR_0x8004, TRAINER_HILL_FUNC_9
	special CallTrainerHillFunction
	compare VAR_RESULT, 1
	goto_if_eq TrainerHill_1F_EventScript_2C83BF
	end

TrainerHill_1F_EventScript_2C83BF:: @ 82C83BF
	warpsilent MAP_TRAINER_HILL_ENTRANCE, 255, 9, 6
	waitstate
	end

TrainerHill_1F_EventScript_2C83C9:: @ 82C83C9
	setvar VAR_0x8004, TRAINER_HILL_FUNC_12
	special CallTrainerHillFunction
	setvar VAR_0x8004, TRAINER_HILL_FUNC_SET_LOST
	special CallTrainerHillFunction
	setvar VAR_TEMP_1, 1
	end

TrainerHill_1F_EventScript_2C83DF:: @ 82C83DF
TrainerHill_Entrance_EventScript_2C83DF:: @ 82C83DF
	setvar VAR_TEMP_1, 0
	warp MAP_TRAINER_HILL_ENTRANCE, 255, 9, 6
	waitstate
	end

TrainerHill_1F_Movement_2C83EE:: @ 82C83EE
	set_invisible
	step_end

EventScript_2C83F0:: @ 82C83F0
	trainerbattle TRAINER_BATTLE_12, TRAINER_PHILLIP, 0, BattleFacility_TrainerBattle_PlaceholderText, BattleFacility_TrainerBattle_PlaceholderText
	setvar VAR_0x8004, TRAINER_HILL_FUNC_11
	special CallTrainerHillFunction
	waitmessage
	waitbuttonpress
	closemessage
	end

Text_ThisIsATestSignpostMsg:: @ 82C840A
	.string "这是一条用来测试的消息。\n"
	.string "这是一个标牌。$"

EventScript_TestSignpostMsg:: @ 82C8436
	msgbox Text_ThisIsATestSignpostMsg, MSGBOX_SIGN
	end

gText_082C843F:: @ 82C843F
	.string "这真的是太遗憾了…$"

gText_082C8458:: @ 82C8458
	.string "好的,我明白了…$"

gText_082C846C:: @ 82C846C
	.string "我真的很抱歉…$"

gText_082C8480:: @ 82C8480
	.string "谢谢…$"

gText_082C848B:: @ 82C848B
	.string "啊哈哈!你觉得尴尬吗?\n"
	.string "大家都在看我们!$"

gText_082C84C1:: @ 82C84C1
	.string "嗯…\n"
	.string "这是…$"

gText_082C84D0:: @ 82C84D0
	.string "我巨蛋超级巨星的称号可不只是用来唬人的!$"

gText_082C84F7:: @ 82C84F7
	.string "啊哈哈!\n"
	.string "你太振奋人心了!$"

gText_082C8512:: @ 82C8512
	.string "上班的路上!\n"
	.string "上了一堂好课,嗯?$"

gText_082C853B:: @ 82C853B
	.string "干得好!\n"
	.string "你很清楚自己在做什么!$"

gText_082C8561:: @ 82C8561
	.string "嘿,嘿,嘿!\n"
	.string "你已经完成了吗?$"

gText_082C8589:: @ 82C8589
	.string "这里发生了什么?$"

gText_082C859D:: @ 82C859D
	.string "Humph…$"

gText_082C85A4:: @ 82C85A4
	.string "Urk…$"

gText_082C85A9:: @ 82C85A9
	.string "Hah!$"

gText_082C85AE:: @ 82C85AE
	.string "Darn!$"

gText_082C85B4:: @ 82C85B4
	.string "哦!\n"
	.string "你必须更加努力才行!$"

gText_082C85E3:: @ 82C85E3
	.string "没门!\n"
	.string "干得好!$"

gText_082C85F5:: @ 82C85F5
	.string "呵呵呵!\n"
	.string "你在期待什么?$"

gText_082C8611:: @ 82C8611
	.string "哈?\n"
	.string "你是认真的吗?!$"

gText_082C8628:: @ 82C8628
	.string "你的宝可梦很弱，\n"
	.string "因为它的训练师很弱!$"

gText_082C8662:: @ 82C8662
	.string "啊…\n"
	.string "现在这是另外一回事…$"

gText_082C8682:: @ 82C8682
	.string "哈哈哈!\n"
	.string "我的弟兄们,我们没有什么可担心的!$"

gText_082C86B3:: @ 82C86B3
	.string "哇!\n"
	.string "哈哈哈!$"

gText_082C86C3:: @ 82C86C3
	.string "嘿! 你怎么了!\n"
	.string "让我们看看! 继续努力!$"

gText_082C86FE:: @ 82C86FE
	.string "你做的很棒!\n"
	.string "你有为此努力了吧!$"

gText_082C8739:: @ 82C8739
	.string "嘿!现在不要放弃!\n"
	.string "振作点!不要对自己失去信心!$"

gText_082C877B:: @ 82C877B
	.string "你已经完成它了!\n"
	.string "你一直在为这个好好努力了吧!$"

@debug use
EventScript_BufferChainCount::
	bufferspeciesname 0, VAR_CHAIN_SPECIES
	buffernumberstring 1, VAR_CHAIN_COUNT
	msgbox tEXTchainbuffer, MSGBOX_NPC
	release
	end
	
EventScript_SetWildBattle::
	scrollingmultichoice 0, 1, 1, 6, TRUE
	copyvar VAR_DEBUG_USE, VAR_RESULT
	bufferspeciesname 0, VAR_DEBUG_USE
	msgbox tEXTtestbuffer, MSGBOX_NPC
	release
	end
	
tEXTtestbuffer:
	.string "{STR_VAR_1}$"
	
tEXTchainbuffer:
	.string "{STR_VAR_1}\n"
	.string "{STR_VAR_2}$"

	.align 2
	.include "data/text/save.inc"
	.include "data/text/birch_speech.inc"

	.include "data/maps/AtroposKohlrabiGarden/scripts.inc"

	.include "data/maps/AtroposQuiteTown/scripts.inc"

	.include "data/maps/AtroposGinkgoCity/scripts.inc"

	.include "data/maps/AtroposMacarangaTown/scripts.inc"

	.include "data/maps/AtroposCurvifoliaTown/scripts.inc"

	.include "data/maps/AtroposCycasCity/scripts.inc"

	.include "data/maps/AtroposTheGoldenBay/scripts.inc"

	.include "data/maps/AtroposBanabaTown/scripts.inc"

	.include "data/maps/AtroposPlatiniumCity/scripts.inc"

	.include "data/maps/AtroposHuperTown/scripts.inc"

	.include "data/maps/AtroposDavidiaCity/scripts.inc"

	.include "data/maps/AtroposBubbleIsland/scripts.inc"

	.include "data/maps/AtroposDidaVillage/scripts.inc"

	.include "data/maps/AtroposRouteAlpha/scripts.inc"

	.include "data/maps/AtroposRouteBeta/scripts.inc"

	.include "data/maps/AtroposRouteGamma/scripts.inc"

	.include "data/maps/AtroposRouteDelta/scripts.inc"

	.include "data/maps/AtroposRouteEpsilon/scripts.inc"

	.include "data/maps/AtroposRouteZeta/scripts.inc"

	.include "data/maps/AtroposRouteEta/scripts.inc"

	.include "data/maps/AtroposRouteTheta/scripts.inc"

	.include "data/maps/AtroposRouteIota/scripts.inc"

	.include "data/maps/AtroposRouteKappa/scripts.inc"

	.include "data/maps/AtroposPrideRoad/scripts.inc"

	.include "data/maps/AtroposKohlrabiBeach/scripts.inc"

	.include "data/maps/AtroposKohlrabiSecretGarden/scripts.inc"

	.include "data/maps/AtroposVivianHouse1F/scripts.inc"

	.include "data/maps/AtroposVivianHouse2F/scripts.inc"

	.include "data/maps/AtroposKohlrabiIndoor1/scripts.inc"

	.include "data/maps/LachesisBattleDome/scripts.inc"

	.include "data/maps/AtroposQuitePC/scripts.inc"

	.include "data/maps/AtroposQuitePC2/scripts.inc"

	.include "data/maps/Darkness/scripts.inc"

	.include "data/maps/LachesisBattleDomeHouse/scripts.inc"

	.include "data/maps/AtroposQuiteIndoor1/scripts.inc"

	.include "data/maps/AtroposProfTuckersLab/scripts.inc"

	.include "data/maps/AtroposGinkgoIndoor1/scripts.inc"

	.include "data/maps/AtroposGinkgoIndoor2/scripts.inc"

	.include "data/maps/AtroposGinkgoIndoor3/scripts.inc"

	.include "data/maps/AtroposGinkgoPC/scripts.inc"

	.include "data/maps/AtroposGinkgoPC2/scripts.inc"
