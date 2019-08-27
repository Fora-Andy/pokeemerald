AtroposProfTuckersLab_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, AtroposProfTuckersLab_MapScript1
	.byte 0

AtroposProfTuckersLab_MapScript1:
	map_script_2 VAR_MEET_PROF_TUCKER, 1, AtroposProfTuckersLab_EventScript1
	.2byte 0

AtroposProfTuckersLab_EventScript1::
 lock
 delay 30
 applymovement EVENT_OBJ_ID_PLAYER, movement_question_mark_global
 waitmovement 0
 delay 30
 special SpawnCameraObject
 applymovement EVENT_OBJ_ID_CAMERA, movement_AtroposProfTuckersLab1
 waitmovement 0
 msgbox Text_AtroposProfTuckersLab_1, MSGBOX_AUTOCLOSE
 applymovement 1, movement_exclamation_mark_global
 waitmovement 0
 turnobject 2, 3
 msgbox Text_AtroposProfTuckersLab_2, MSGBOX_AUTOCLOSE
 applymovement EVENT_OBJ_ID_CAMERA, movement_AtroposProfTuckersLab2
 waitmovement 0
 delay 30
 special RemoveCameraObject
 applymovement EVENT_OBJ_ID_PLAYER, movement_AtroposProfTuckersLab3
 waitmovement 0
 delay 30
 turnobject 2, 1
 turnobject 1, 1
 msgbox Text_AtroposProfTuckersLab_3, MSGBOX_AUTOCLOSE
 applymovement 2, movement_AtroposProfTuckersLab4
 waitmovement 0
 msgbox Text_AtroposProfTuckersLab_4, MSGBOX_AUTOCLOSE
 applymovement 2, movement_AtroposProfTuckersLab5
 waitmovement 0
 delay 30
 msgbox Text_AtroposProfTuckersLab_5, MSGBOX_AUTOCLOSE
 trainerbattle_no_intro TRAINER_MARLIN, Text_AtroposProfTuckersLab_6
 msgbox Text_AtroposProfTuckersLab_7, MSGBOX_AUTOCLOSE
 delay 30
 playfanfare MUS_FANFA4
 msgbox Text_AtroposProfTuckersLab_8, MSGBOX_AUTOCLOSE
 waitfanfare
 setflag FLAG_SYS_POKEDEX_GET
 setflag FLAG_RECEIVED_POKEDEX_FROM_BIRCH
 setflag FLAG_SYS_NATIONAL_DEX
 special EnableNationalPokedex
 msgbox Text_AtroposProfTuckersLab_9, MSGBOX_AUTOCLOSE
 applymovement 2, movement_AtroposProfTuckersLab6
 waitmovement 0
 turnobject EVENT_OBJ_ID_PLAYER, 3
 msgbox Text_AtroposProfTuckersLab_10, MSGBOX_AUTOCLOSE
 setvar VAR_MEET_PROF_TUCKER, 2
 setflag FLAG_HIDE_VIVIAN_LAB
 setflag FLAG_TEXTBOX_MIDDLE_BLACK
 clearflag FLAG_HIDE_VIVIAN
 setflag FLAG_TOGGLE_LVL_CURVE
 warpsilent MAP_DARKNESS, 255, -1, -1
 release
 end
 
movement_question_mark_global:
	emote_question_mark
	step_end
	
movement_exclamation_mark_global:
	emote_exclamation_mark
	step_end
	
movement_AtroposProfTuckersLab1:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

movement_AtroposProfTuckersLab2:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	step_end
	
movement_AtroposProfTuckersLab3:
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	face_up
	step_end
	
movement_AtroposProfTuckersLab4:
	face_right
	step_end
	
movement_AtroposProfTuckersLab5:
	face_down
	step_end
	
movement_AtroposProfTuckersLab6:
	walk_down
	face_right
	step_end

Text_AtroposProfTuckersLab_1:
	.string "塔克：容我拒绝，薇薇安...\l"
	.string "薇薇安：塔克博士，\n"
	.string "你难道不相信我吗？\p"
	.string "塔克：那个男人来路不明，\n"
	.string "你最好离他远点...\p"
	.string "... ... ... ...\l"
	.string "薇薇安：塔克博士...\l"
	.string "但我想报答他救了我，\l"
	.string "他在我最危险的时候\n"
	.string "对我伸出了温暖的手心。\p"
	.string "即使他过去发生了什么...\n"
	.string "我很肯定，他不是坏人...$"
	
Text_AtroposProfTuckersLab_2:
	.string "塔克：是谁！？$"

Text_AtroposProfTuckersLab_3:
	.string "塔克：{PLAYER}就是你吗？\l"
	.string "薇薇安：{PLAYER}！\l"
	.string "塔克：我都听说了\n"
	.string "你似乎有宝可梦训练的经验，\p"
	.string "很可惜我不知道你是谁。\l"
	.string "虽然薇薇安喜欢你，\n"
	.string "但我不相信你...$"
	
Text_AtroposProfTuckersLab_4:
	.string "薇薇安：不...不，才不是呢！\n"
	.string "塔克博士，别拿我开玩笑了！\p"
	.string "既然说的没用，那就对战吧！\n"
	.string "用你们男人解决问题的方式。$"

Text_AtroposProfTuckersLab_5:
	.string "塔克：咳咳，{PLAYER}害怕了吗？\l"
	.string "既然都说到这份上了，\n"
	.string "我可不会放水呢。$"

Text_AtroposProfTuckersLab_6:
	.string "塔克：不可思议，你确实有才能。\l"
	.string "你和宝可梦之间的配合及羁绊，\n"
	.string "或许让我暂时相信你。$"

Text_AtroposProfTuckersLab_7:
	.string "塔克：那么我就直说了，\l"
	.string "你如果要找出你是谁，在阿特波斯\n"
	.string "最好的方法就是变得出名。\p"
	.string "利用你的才能，成为冠军吧。\l"
	.string "到时候认识你的人一定会出现，\l"
	.string "无论是对你好的，\n"
	.string "还是陷害你的，\l"
	.string "所以在这之前，变得更强吧，\p"
	.string "薇薇安：{PLAYER}，我会支持你的！\l"
	.string "塔克：嗯，首先我先提醒你，\n"
	.string "『阿特波斯联盟』不是省油的灯，\p"
	.string "现在的你是无法完成试炼的！\l"
	.string "你要挑战试炼,首先要收集\n"
	.string "７个代提印记，\l"
	.string "这里最靠近的道馆在『银杏市』，\l"
	.string "那里的馆主是『奈奈』，\l"
	.string "是当中最麻烦的一个，\p"
	.string "当然你也可以从其他道馆\n"
	.string "开始挑战，但我警告你，\p"
	.string "这些馆主会随着时间\n"
	.string "越来越棘手。\p"
	.string "在那之前，没有能依靠的伙伴，\n"
	.string "你是不可能挑战成功的。\l"
	.string "你必须去收服更多的宝可梦$"

Text_AtroposProfTuckersLab_8:
	.string "{PLAYER}获得了『图鉴』\n"
	.string "及１０个『精灵球』！$"

Text_AtroposProfTuckersLab_9:
	.string "我给你的图鉴，\n"
	.string "可以记录你收服了什么。\l"
	.string "到时候我可以根据信息给你好的建议。$"

Text_AtroposProfTuckersLab_10:
	.string "薇薇安：太好了{PLAYER}，\l"
	.string "你获得了塔克博士的肯定\l"
	.string "这么一来你之后都会在外奔波\l"
	.string "所以今天回去必须好好休息，\l"
	.string "明天早上再出发吧。\l"
	.string "塔克：那么，我祝你好运！$"

