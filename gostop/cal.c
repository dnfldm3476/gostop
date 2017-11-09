
#include<stdio.h>
#include<stdlib.h>

#include"set.h"
#include"play.h"
#include"gos.h"



int cal_Pi(Hawtoo *pae, int i)
{
    int data ;
    int pi = 0;
    while(pae != NULL){
        data =pae->data;
        if((data % 4 ==2 || data %4==3) && (data /4 != 11)){
            pi++;
        }
        else if(data == 47 || data ==41)
            pi =pi+2;
        pae = pae->next;
    }
    if(pi >= 5)
        player[i].pi = true;
    else
        player[i].pi = false;

    return pi;
}
int cal_Wo(Hawtoo *pae)
{
    int data;
    int wo = 0;
    int score = 0;
    int hong = 0;
    int chung =0;
    int cho = 0;
    while(pae != NULL){
        data =pae->data;
        if(((data % 4 ==1) && (data /4 != 11) && (data /4 != 10) && (data /4 !=7))||(data == 46)){
            wo++;
        }
        if(data == 1 || data ==5 || data == 9) // 홍단
            hong ++;
        else if(data ==21 || data ==33 || data == 37)
            chung ++;
        else if(data ==13 || data == 17 || data == 25)
            cho ++;
        pae = pae->next;
    }

    if(wo>=5)
        score = wo-4;
    if(chung ==3)
        score = score + 3;
    if(hong == 3)
        score = score + 3;
    if(cho == 3)
        score = score + 3;


    return score;
}
int cal_Sib(Hawtoo *pae, int turn)
{
    int data;
    int sib = 0;
    int score = 0;
    int godori = 0;
    while(pae != NULL){
        data = pae->data;
        if(data == 4|| data ==12 || data == 29){
            godori ++;
            sib ++;
        }
        else if(data ==16||data ==20||data ==24||data ==36||data ==45){
            sib++;}
        pae = pae->next;
    }
    if (sib >= 7)
        player[turn].mungtung = true;
    if(sib >=5)
        score = sib -4;
    if(godori == 3)
        score = score +5;
    return score;
}
int cal_Gwang(Hawtoo *pae, int i)
{
    int data ;
    int gwang = 0;
    int bi_gwang = 0;
    int score = 0;
    while(pae != NULL){
        data =pae->data;
        if(data ==0 || data ==8 || data ==28 || data == 40){
            gwang++;
        }
        else if(data == 44)
            bi_gwang = 1;
        pae = pae->next;
    }
    if(bi_gwang == 1)
    {
        if(gwang ==4)
            score = 15;
        else if( gwang == 3)
            score = 4;
        else if (gwang ==2 )
            score = 2;
        else 
            score = 0;
    }
    else
    {
        if(gwang == 4)
            score  = 4;
        else if (gwang == 3)
            score = 3;
        else 
            score = 0;
    }
    if(gwang !=0 || bi_gwang == 1)
        player[i].gwang = true;

    return score;
}
int cal_Score(Hawtoo *pae, int turn)
{
    int pi= cal_Pi(pae, turn) ;
    int sib = cal_Sib(pae, turn);
    int wo = cal_Wo(pae);
    int gwang = cal_Gwang(pae,turn);
    int sum = 0;
    if(pi>=10){
        pi = pi-9;
        sum = pi+sib+wo+gwang;
    }
    else
        sum = sib+wo+gwang;
    printf("pi %d\n",pi);
    printf("sib %d\n",sib);
    printf("wo %d\n",wo);
    printf("gwang %d\n",gwang);
    return sum;
}
int cal_Money(Player player)
{
    int point = player.score;
    if(player.chongtong ==true){
        point = 10;
        return point;
    }
    if(player.go !=0)
    {
        if(player.go == 1)
            point +=1;
        else if(player.go == 2)
            point +=2;
        else if(player.go == 3)
            point = point *2;
        else if(player.go == 4)
            point = point *4;
        else
            point = point *8;
    }
    if(player.mungtung == true)
        point = point  *2;
    if(player.wave == true)
        point = point *2;
    if(player.mungtung == true)
        point = point *2;
    // 광박, 고박, 피박 계산
    return point;
}
void get_Money(int turn)
{
    int check_gwang = cal_Gwang(player[turn].eat_Pae, turn);
    int check_pi = cal_Pi(player[turn].eat_Pae, turn);
    check_pi = check_pi - 9;
    int point =  cal_Money(player[turn]);
    int loser[2] = {0,0};
    int money[2] = {0,0};
    int k =0;

    for(int i=0;i<3;i++){
        if(i == turn)
            continue;
        else
        {
          //  cmt =  cal_Pi(player[i].eat_Pae,i);
          //  cmt = cal_Gwang(player[i].eat_Pae,i);
            loser[k] = i;
            k++;
        }
    }
        // 광박 피박 계산함
    if(player[turn].chongtong == false){
        for(int i=0;i<2;i++){
            money[i] = point;
            if(check_pi > 0) // 피로 점수가 나옴
            {
                if(player[loser[i]].pi == false)
                    money[i]  = money[i] *2;
            }

            if(check_gwang != 0) // 광으로 점수가 나옴
            {
                if(player[loser[i]].gwang == false)
                    money[i]  = money[i] *2;

            }
            if(player[loser[i]].gobak == true) // go를 했던 기록이 있으면 고박
            {
                money[i] =money[i] *2;
            }
            money[i] = money[i] *100;
        }
    }

    player[turn].money = player[turn].money + money[0] +money[1] ;
    player[loser[0]].money = player[loser[0]].money - money[0];
    player[loser[1]].money = player[loser[1]].money - money[1];

}
