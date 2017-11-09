#ifndef _PLAY_H_
#define _PLAY_H_
#include"set.h"
int get_Size(Hawtoo *pae);
void play_Game(char *command);
int get_Turn(); // 현재 turn인 사람 가져오기
void hand_Turn(int turn); // turn 넘기기
void new_Game();
void end_Game(int turn);
#endif
