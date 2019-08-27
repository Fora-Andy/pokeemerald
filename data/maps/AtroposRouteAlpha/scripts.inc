AtroposRouteAlpha_MapScripts::
	.byte 0

AtroposRouteAlpha_EventScript1::
 lock
 delay 50
 applymovement 4, movement_AtroposRouteAlpha1
 waitmovement 0
 getplayerxy 0x8004,0x8005
 compare_var_to_value VAR_0x8004, 6
 goto_if_eq AtroposRouteAlpha_EventScript2
 compare_var_to_value VAR_0x8004, 7
 goto_if_eq AtroposRouteAlpha_EventScript3
 compare_var_to_value VAR_0x8004, 8
 goto_if_eq AtroposRouteAlpha_EventScript4
 applymovement 4, movement_AtroposRouteAlpha5
 waitmovement 0
 goto AtroposRouteAlpha_EventScript5
 
AtroposRouteAlpha_EventScript2::
 applymovement 4, movement_AtroposRouteAlpha2
 waitmovement 0
 goto AtroposRouteAlpha_EventScript5

AtroposRouteAlpha_EventScript3::
 applymovement 4, movement_AtroposRouteAlpha3
 waitmovement 0
 goto AtroposRouteAlpha_EventScript5
 
AtroposRouteAlpha_EventScript4::
 applymovement 4, movement_AtroposRouteAlpha4
 waitmovement 0
 goto AtroposRouteAlpha_EventScript5

AtroposRouteAlpha_EventScript5::
 applymovement 4, movement_AtroposRouteAlpha6
 waitmovement 0
 msgbox Text_AtroposRouteAlpha_1, MSGBOX_AUTOCLOSE
 applymovement 4, movement_AtroposRouteAlpha7
 waitmovement 0
 removeobject 4
 setflag FLAG_HIDE_VIVIAN_ROUTE_ALPHA
 setvar VAR_MEET_PROF_TUCKER, 1
 release
 end
 
 
AtroposRouteAlpha_TrainerScript1::
	trainerbattle_single TRAINER_GUBEI, AtroposRouteAlpha_Trainer_Text_1, AtroposRouteAlpha_Trainer_Text_2
	msgbox AtroposRouteAlpha_Trainer_Text_2, MSGBOX_AUTOCLOSE
	end

AtroposRouteAlpha_TrainerScript2::
	trainerbattle_single TRAINER_FURUOLA, AtroposRouteAlpha_Trainer_Text_3, AtroposRouteAlpha_Trainer_Text_4
	msgbox AtroposRouteAlpha_Trainer_Text_4, MSGBOX_AUTOCLOSE
	end
 
movement_AtroposRouteAlpha1:
	face_left
	delay_8
	face_down
	delay_8
	face_left
	delay_8
	face_right
	delay_8
	face_up
	emote_exclamation_mark
	delay_16
	step_end
	
movement_AtroposRouteAlpha2:
	walk_right
	walk_right
	walk_right
	step_end

movement_AtroposRouteAlpha3:
	walk_right
	walk_right
	walk_right
	walk_right
	step_end
	
movement_AtroposRouteAlpha4:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end
	
movement_AtroposRouteAlpha5:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

movement_AtroposRouteAlpha6:
	walk_up
	walk_up
	step_end

movement_AtroposRouteAlpha7:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

Text_AtroposRouteAlpha_1:
	.string "薇薇安: {PLAYER},博士的研究所就在前面。\l"
	.string "我们快点过去吧！$"

AtroposRouteAlpha_Trainer_Text_1:
	.string "1$"
	
AtroposRouteAlpha_Trainer_Text_2:
	.string "2$"
	
AtroposRouteAlpha_Trainer_Text_3:
	.string "3$"
	
AtroposRouteAlpha_Trainer_Text_4:
	.string "4$"