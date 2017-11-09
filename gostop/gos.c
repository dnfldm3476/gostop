#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"set.h"
#include"play.h"
#include"gos.h"
#include"save.h"

void draw()
{
    Hawtoo *pae;
    Hawtoo *handpae;
    Hawtoo *eatpae;
    printf("\n");
    printf("-------------------------------------------------------\n");
    printf("\n");
    for(int i=0;i<3;i++){
	handpae = player[i].hand_Pae;
	eatpae = player[i].eat_Pae; 

	if(i==0){
	    if(player[0].myTurn == true)
		printf("*");
	    else
		printf(" ");
	    printf("A ");
	    if(player[0].wave ==true)
		printf("흔듦");
	    else
		printf("    ");

	    printf("  : 패) ");
	}
	else if(i==1){
	    if(player[1].myTurn == true)
		printf("*");
	    else
		printf(" ");
	    printf("B ");
	    if(player[1].wave ==true)
		printf("흔듦");
	    else
		printf("    ");
	    printf("  : 패) ");
	}
	else if (i==2){
	    if(player[2].myTurn == true)
		printf("*");
	    else
		printf(" ");
	    printf("C ");
	    if(player[2].wave ==true)
		printf("흔듦");
	    else
		printf("    ");
	    printf("  : 패) ");
	}

	while(handpae != NULL){
	    if(handpae->data == -1)
		break;
	    printf("%s ",pae_stat[handpae->data]);
	    handpae = handpae -> next;
	}
	printf("\n(점수 : %d) 딴 화투) ",player[i].score);
	while(eatpae != NULL){
	    if(eatpae->data == -1)
		break;
	    printf("%s ",pae_stat[eatpae->data]);
	    eatpae = eatpae -> next;
	}
	printf("\n\n");
    }

    printf("깔린 패) ");

    pae = spread_Pae;
    while(pae != NULL){
	if(pae->data == -1)
	    break;
	printf("%s ",pae_stat[pae->data]);
	pae = pae -> next;
    }

    printf("\n");
    printf("더미 패 ) ");
    pae = dummy_Pae;
    while(pae != NULL){
	if(pae->data == -1)
	    break;
	printf("%s ",pae_stat[pae->data]);
	pae = pae -> next;
    }
    printf("\n");
    printf("명령 : ");
}


void show_Help()
{
    system("clear");
    printf(" **************************************************************************************\n");
    printf("  >                                     도   움   말                                  \n");
    printf("  > 1 - 7 : 자신이 가지고 있는 카드 내기                                                  \n");
    printf("  > 1 - 2 : 다 가져가 버리면 짝이 맞지 않을 때 먹을 카드 한 장 선택                        \n");
    printf("  > g : 고                                                                          \n");
    printf("  > s : 스톱                                                                         \n");
    printf("  > 9 : 9월 쌍피를 열끗으로 전환. (한 번만 가능)                                           \n");
    printf("  > b : 플레이어들의 잔고 보기                                                           \n");
    printf("  > save : 게임 저장                                                                  \n");
    printf("  > load : 게임 불러오기                                                               \n");
    printf("  > e : 게임 종료                                                                     \n");
    printf("****************************************************************************************\n");
}

void command_Interface(char *command)
{


    if(strcmp(command, "1")==0  || strcmp(command, "2")==0 ||strcmp(command, "3") ==0 ||strcmp(command, "4")==0 ||strcmp(command, "5") ==0 ||strcmp(command, "6") ==0 ||strcmp(command, "7")==0)
    {
	play_Game(command);
    }
    else if(strcmp(command, "g") ==0 ||strcmp(command, "go")==0)
	printf("고\n");

    else if(strcmp(command, "s") ==0 ||strcmp(command, "stop")==0)
	printf("멈추기\n");

    else if(strcmp(command, "b") ==0 ||strcmp(command, "balance")==0){
	printf("A : %d \n",player[0].money);
	printf("B : %d \n",player[1].money);
	printf("C : %d \n",player[2].money);
	printf("잔고\n");
    }
    else if(strcmp(command, "save") ==0){
	printf("저장\n");
	save_Game();
    }
    else if(strcmp(command, "load") ==0){
	printf("불러오기\n");
	load_Game();
    }
    else if(strcmp(command, "e") ==0){
	printf("종료\n");
	exit(0);
    }

    else if(strcmp(command, "h") ==0 ||strcmp(command, "help")==0)
	show_Help();

    else
	printf("설정되지 않은 명령입니다.\n");

}
