#ifndef _SET_H_
#define _SET_H_
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>


#define PLAYER_MAX 3
#define GWANG "광"
#define PI "피"
#define WO "오"
#define SIB "십"

typedef struct hawtoo {
    int data;
    struct hawtoo *next; // 다음패 가리킴
}Hawtoo;
Hawtoo *dummy_Pae;
Hawtoo *spread_Pae;

typedef struct Player{

    bool myTurn; // 차례확인
    bool wave; // 흔들기 유무
    bool chongtong;  // 총통 유무

    bool mungtung;  
    bool gobak;
    bool gwang;
    bool pi;
    int score;

    int go;  // go Count
    int money; // 가진 잔고

    Hawtoo *eat_Pae; // 먹은 패
    Hawtoo *hand_Pae; // 가진 패    
}Player;
Player player[PLAYER_MAX];


void game_Setting(bool check);
void compare_Pae(Hawtoo *target, int data, int *count);
void order_Pae(Hawtoo *pae);  // Pae를 순서대로 정
void hawtoo_Pae();
void give_Pae();
void shuffle_Pae(Hawtoo *pae);
void delete_Pae(Hawtoo *pae, int data);
void add_Pae(Hawtoo *pae, int data);
void take_Pi(int turn); // 같은무늬 4장먹으면 다른사람 피 가져오기
void compare_Spread(int turn, int hand);
bool check_Num(Hawtoo *pae, int turn);
void check_Chong();
void set_Player();

void Chongtong();

char pae_stat[48][10];
//초기 설정, 화투설정

#endif



