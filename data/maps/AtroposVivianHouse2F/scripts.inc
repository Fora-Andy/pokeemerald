AtroposVivianHouse2F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, AtroposVivianHouse2F_MapScript1
	.byte 0

AtroposVivianHouse2F_MapScript1:
	map_script_2 VAR_OPENING_STATE, 4, AtroposVivianHouse2F_EventScript1
	map_script_2 VAR_OPENING_STATE, 5, AtroposVivianHouse2F_EventScript2
	.2byte 0

AtroposVivianHouse2F_EventScript1::
	lockall
	msgbox Text_AtroposVivianHouse2F_1, MSGBOX_AUTOCLOSE
	delay 50
	setflag FLAG_TEXTBOX_MIDDLE_BLACK
	setvar VAR_OPENING_STATE 5
	delay 80
	hideobjectat 2, MAP_ATROPOS_VIVIAN_HOUSE2F
	hideobjectat 3, MAP_ATROPOS_VIVIAN_HOUSE2F
	setflag FLAG_HIDE_DOCTOR_ABRAHAM
	warpsilent MAP_DARKNESS, 255, -1, -1
	waitstate
	releaseall
	end

AtroposVivianHouse2F_EventScript2::
	delay 80
	msgbox Text_AtroposVivianHouse2F_2, MSGBOX_AUTOCLOSE
	applymovement 1, movement_AtroposVivianHouse2F
	waitmovement 0
	playse SE_PIN
	delay 30
	applymovement EVENT_OBJ_ID_PLAYER, movement_AtroposVivianHouse2F_2
	waitmovement 0
	msgbox Text_AtroposVivianHouse2F_3, MSGBOX_AUTOCLOSE
	setvar VAR_OPENING_STATE 6
	setflag FLAG_HIDE_VIVIAN_OP
	warpsilent MAP_DARKNESS, 255, -1, -1
	waitstate
	releaseall
	end

movement_AtroposVivianHouse2F:
	emote_exclamation_mark
	step_end

movement_AtroposVivianHouse2F_2:
	face_right
	step_end

/*
Text_AtroposVivianHouse2F_1:
	.string "Doctor: He's stable now...\l"
	.string "if Vivian found him late,\n"
	.string "his life could be in danger\p"
	.string "Abraham: Thanks doctor,\l"
	.string "Hope this young man wake up soon...{PAUSE 0x20} \p"
	.string "Vivian: Father, how did him\n"
	.string "get into the water?\p"
	.string "Abraham: No idea, \n"
	.string "strange things happened.\l"
	.string "Hmm...\l"
	.string "He wears like foreigner...\l"
	.string "...{PAUSE 0x30} ...{PAUSE 0x30} ...{PAUSE 0x30} ...{PAUSE 0x30}$"
		
Text_AtroposVivianHouse2F_2:
	.string "White: Ahh!$"
	
Text_AtroposVivianHouse2F_3:
	.string "Vivian: Ah you wake up!\l"
	.string "It has been three month...\l"
	.string "Three...{PAUSE 0x30} month?\n"
	.string "... {PAUSE 0x30} ...{PAUSE 0x30}Who...{PAUSE 0x50}am I?...\p"
	.string "Vivian: You...\n"
	.string "You don't remember your name?\l"
	.string "...{PAUSE 0x30} ...{PAUSE 0x30} ...{PAUSE 0x30} ...{PAUSE 0x30}$"
*/

Text_AtroposVivianHouse2F_1:
	.string "医生: 他的脉象稳定下来了...\l"
	.string "如果再迟点发现他,\n"
	.string "就危险了...\p"
	.string "亚伯汗: 谢谢医生。\l"
	.string "希望他能早点醒来...{PAUSE 0x20} \p"
	.string "薇薇安: 爸爸, 他为什么\n"
	.string "会差点溺毙?\p"
	.string "亚伯汗: 不知道呢, \n"
	.string "奇怪的事总是发生.\l"
	.string "哼...\l"
	.string "他的穿着不像本地人...\l"
	.string "...{PAUSE 0x30} ...{PAUSE 0x30} ...{PAUSE 0x30} ...{PAUSE 0x30}$"
		
Text_AtroposVivianHouse2F_2:
	.string "怀特: 啊!$"
	
Text_AtroposVivianHouse2F_3:
	.string "薇薇安: 啊,你终于醒了!\l"
	.string "你睡了足足三个月...\l"
	.string "三...{PAUSE 0x30} 个月?\n"
	.string "... {PAUSE 0x30} ...{PAUSE 0x30}我...{PAUSE 0x50}是谁?...\p"
	.string "薇薇安: 你...\n"
	.string "难道不记得自己的名字了?\l"
	.string "...{PAUSE 0x30} ...{PAUSE 0x30} ...{PAUSE 0x30} ...{PAUSE 0x30}$"