#include<stdio.h>
#include<stdlib.h>
#include"save.h"
void save_Game(){
    Hawtoo *pae;
    FILE *fp;
    fp = fopen("savefile.txt","w+");
    if(fp==NULL){
        printf("실패\n");
    }

    for(int i=0;i<3;i++){
        fprintf(fp,"%d ",player[i].myTurn);
        fprintf(fp,"%d ",player[i].wave);
        fprintf(fp,"%d ",player[i].chongtong);
        fprintf(fp,"%d ",player[i].mungtung);
        fprintf(fp,"%d ",player[i].gobak);
        fprintf(fp,"%d ",player[i].pi);
        fprintf(fp,"%d ",player[i].score);
        fprintf(fp,"%d ",player[i].go);
        fprintf(fp,"%d\n ",player[i].money);
    }
    for(int i=0;i<3; i++){
        pae = player[i].hand_Pae;
        while(pae != NULL){
            if(pae->data == -1)
                break;
            fprintf(fp,"%d ",pae->data);
            pae = pae->next;
        }
        fprintf(fp,"%d", -1);
        fprintf(fp,"\n");

        pae = player[i].eat_Pae;
        while(pae != NULL){
            if(pae->data == -1)
                break;
            fprintf(fp,"%d ",pae->data);
            pae = pae->next;
        }
        fprintf(fp,"%d", -1);
        fprintf(fp,"\n");
    }
    pae = spread_Pae;
    while(pae != NULL){
        if(pae->data == -1)
            break;
        fprintf(fp,"%d ",pae->data);
        pae = pae->next;
    }
    fprintf(fp,"%d", -1);
    fprintf(fp,"\n");
    pae = dummy_Pae;
    while(pae != NULL){
        if(pae->data == -1)
            break;
        fprintf(fp,"%d ",pae->data);
        pae = pae->next;
    }
    fprintf(fp,"%d", -2);
    fprintf(fp,"\n");


    fclose(fp);


    printf("완료\n");
}
void load_Game()
{
    FILE *fp;
    fp = fopen("savefile.txt","r");

    if(fp==NULL){
        printf("save파일이 없습니다!\n");
    }

    Hawtoo *player_Pae = (Hawtoo *)malloc(sizeof(Hawtoo) *8);
    Hawtoo *all_Pae = (Hawtoo *)malloc(sizeof(Hawtoo) *58);
    Hawtoo *pae;

    for(int i=0;i<3;i++){
        int cmt = 0;
        fscanf(fp,"%d",&cmt);
        if(cmt == 0)
            player[i].myTurn = false;
        else
            player[i].myTurn = true;

        fscanf(fp,"%d",&cmt);
        if(cmt == 0)
            player[i].wave = false;
        else
            player[i].wave = true;

        fscanf(fp,"%d",&cmt);
        if(cmt == 0)
            player[i].chongtong = false;
        else
            player[i].chongtong = true;

        fscanf(fp,"%d",&cmt);
        if(cmt == 0)
            player[i].mungtung = false;
        else
            player[i].mungtung = true;

        fscanf(fp,"%d",&cmt);
        if(cmt == 0)
            player[i].gobak = false;
        else
            player[i].gobak = true;

        fscanf(fp,"%d",&cmt);
        if(cmt == 0)
            player[i].pi = false;
        else
            player[i].pi = true;

        fscanf(fp,"%d",&player[i].score);
        fscanf(fp,"%d",&player[i].go);
        fscanf(fp,"%d",&player[i].money);
    }
    int k;
    for(int i = 0 ;i<58;i++)
    {
        fscanf(fp,"%d",&k);
        if(k !=-2){
            all_Pae[i].data = k;
            all_Pae[i].next = NULL; 
        }
        else if(k == -2){
            all_Pae[i].data = k;
            all_Pae[i].next = NULL;
            break;
        }
    }
    pae = &player_Pae[0];
    int i=0;
    k=0;
    pae = &player_Pae[k];
    while(1){

        pae->data = all_Pae[i].data;
        if(all_Pae[i].data == -2){
            pae->next =NULL;
            break;
        }
        else if(all_Pae[i].data == -1){
            pae->next =NULL;
            k++;
            pae = &player_Pae[k];
        }
        else if(all_Pae[i].data != -1){
            pae->next = &all_Pae[i+1];
            pae = pae->next;
        }
        i++;
    }
    player[0].hand_Pae = &player_Pae[0];
    player[0].eat_Pae = &player_Pae[1];
    player[1].hand_Pae = &player_Pae[2];
    player[1].eat_Pae = &player_Pae[3];
    player[2].hand_Pae = &player_Pae[4];
    player[2].eat_Pae = &player_Pae[5];
    spread_Pae = &player_Pae[6];
    dummy_Pae = &player_Pae[7];


    fclose(fp);


    printf("완료\n");
}
