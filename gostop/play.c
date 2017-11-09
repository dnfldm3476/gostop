#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include"play.h"
#include"gos.h"
#include"cal.h"
#include"set.h"
#include"save.h"

void new_Game()
{
    int turn = get_Turn();  
    game_Setting(false);
    for(int i=0;i<3;i++)
        player[i].myTurn = false;
    player[turn].myTurn = true; // 승자 턴 셋팅ㅁ
    system("clear");
    printf("새게임 시작!!!\n");

    while(1){
        char *command;
        char buf[10];
        command = buf;
        draw();
        scanf("%s",command);
        command_Interface(command);
    }
}

int get_Turn(){
    for(int i=0;i<3;i++)
    {
        if(player[i].myTurn == true)
            return i;
    }
    printf("turn이 리턴안됨");
    return 0;
}

void hand_Turn(int turn)
{
    player[turn].myTurn =false;
    turn ++;
    if(turn !=3)
        player[turn].myTurn = true;
    else
        player[0].myTurn = true;
}
// 손에 든 패의 값 가져오기
int get_Handpae(int turn ,int num){
    Hawtoo *pae = player[turn].hand_Pae;
    while(num !=1)
    {
        pae = pae->next;
        num--;
    }
    return pae->data;
}
int get_Size(Hawtoo *pae)
{
    int num = 0;
    while(pae !=NULL)
    {
        pae = pae->next;
        num++;
    }
    return num;
}
void end_Game(int turn)
{
    int check_gwang=cal_Gwang(player[turn].eat_Pae,turn);
    int check_pi=cal_Pi(player[turn].eat_Pae,turn) - 9;
    printf("\n\n*******게임종료 되었습니다********\n");
   if( dummy_Pae->data != -1){
    printf("승자는 : .\n");
    if(turn == 0)
        printf(" A \n");
    else if(turn == 1)
        printf(" B \n");
    else if(turn == 2)
        printf(" C \n");

    printf("점수 : %d\n",player[turn].score);
    for(int i =0;i<3;i++){
        if(i == turn)
            continue;
        if(i == 0)
            printf(" 패자 A : \n");
        else if( i ==1)
            printf(" 패자 B : \n");
        else if( i ==2)
            printf(" 패자 C : \n");
        if(player[i].gobak == true)
            printf("고박\n");
        if(check_pi>0){
            if(player[i].pi == false)
                printf("피박\n");
        }
        if(check_gwang !=0){
            if(player[i].gwang == false)
                printf("광박\n");
        }
    }
   

    printf("게임종료 되었습니다.\n");
   } 
   printf("--------------------\n");
    printf("잔고 : A  %d\n",player[0].money);
    printf("잔고 : B  %d\n",player[1].money);
    printf("잔고 : C  %d\n\n",player[2].money);

    printf("게임을 계속하시겠습니까? (y/n)\n");
    while(1){
        char *command;
        char buf[10];
        command = buf;
        scanf("%s",command);
        if(strcmp(command,"y") == 0 || strcmp(command,"yes") ==0)
        {
            new_Game(); // 새게임 시작
        }
        else if(strcmp(command,"n") == 0 || strcmp(command,"no") ==0)
            exit(0);
        else
            command_Interface(command);
    }
}
void play_Game(char *command)
{
    int turn = get_Turn();
    int num = atoi(command);
    int size = get_Size(player[turn].hand_Pae);
    int score = 0;
    char *com;
    char buf[10];
    com = buf;
    if(num >size && size !=0){
        printf("벗어난 숫자입니다 다시 입력하세요 \n");
        scanf("%s",com);       
        command_Interface(com);
    }
    else{
        int data = get_Handpae(turn, num);
        if(data != -1)
            delete_Pae(player[turn].hand_Pae,data);
        compare_Spread(turn,data);

        score =cal_Score(player[turn].eat_Pae,turn);
        if(dummy_Pae ->data == -1){
            printf("승자가 없습니다.\n");
            end_Game(turn);
        }
        if(score >=3){
            if(player[turn].go ==0 ||(player[turn].go !=0 && player[turn].score < score && score >= 3)){
                while(1){
                    printf("go 하시겠습니까? \n");
                    scanf("%s",com);
                    if((strcmp(com,"g") ==0)|| (strcmp(com,"go") == 0))
                    {
                        player[turn].gobak = true;
                        player[turn].go ++;
                        player[turn].score = score;
                        break;
                    }
                    else if((strcmp(com,"s") == 0) || (strcmp(com,"stop") ==0))
                    {
                        player[turn].score = score; // 새게임 시작
                        get_Money(turn);
                        end_Game(turn);// 점수 계산 돈 계산
                    }
                    else
                        printf("다시 입력하세요 g/s\n");

                }
            }
        }

        hand_Turn(turn);
    }
    // 점수계산
}

