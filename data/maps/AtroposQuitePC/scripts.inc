AtroposQuitePC_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, AtroposQuitePC_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, OldaleTown_PokemonCenter_1F_MapScript1_277C30
	.byte 0

AtroposQuitePC_1F_OnTransition: @ 81FC011
	setrespawn HEAL_LOCATION_ATROPOS_QUITE_TOWN
	call OldaleTown_PokemonCenter_1F_EventScript_2718DE
	end
	
AtroposQuitePC_EventScript_1::
	lock
	faceplayer
	message Message_Pokemart
	waitmessage
	pokemart AtroposQuitePC_Pokemart
	msgbox Message_Pokemart_end, MSGBOX_DEFAULT
	release
	end

	.align 2
AtroposQuitePC_Pokemart:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_NONE
	release
	end

AtroposQuitePC_EventScript_2::
	msgbox AtroposQuitePC_text1, MSGBOX_NPC
	end

AtroposQuitePC_EventScript_3::
	msgbox AtroposQuitePC_text2, MSGBOX_NPC
	end

AtroposQuitePC_EventScript_4::
	msgbox AtroposQuitePC_text3, MSGBOX_NPC
	end
	
Message_Pokemart:
	.string "欢迎!\p请问要购买什么?$"
	
Message_Pokemart_end:
	.string "谢谢!\p请再次光临!$"
	
AtroposQuitePC_text1:
	.string "1$"
	
AtroposQuitePC_text2:
	.string "2$"

AtroposQuitePC_text3:
	.string "3$"
