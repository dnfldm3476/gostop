#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"set.h"
#include"play.h"
#include"gos.h"
#include"cal.h"
// player 초기설정
char pae_stat[48][10] = {"1광","1오","1피1","1피2","2십","2오","2피1","2피2"
    ,"3광","3오","3피1","3피2","4십","4오","4피1","4피2"
	,"5십","5오","5피1","5피2","6십","6오","6피1","6피2"
	,"7십","7오","7피1","7피2","8광","8십","8피1","8피2"
	,"9십","9오","9피1","9피2","10십","10오","10피1","10피2"
	,"11광","11쌍피","11피1","11피2","12광","12십","12오","12쌍피"};
//초기 설정, 화투설정
void game_Setting(bool check){
    if(check ==true){
	player[0].money = 100000;
	player[1].money = 100000;
	player[2].money = 100000;
    }
    set_Player(); // player 정보 초기화
    give_Pae();// 패섞기
    check_Chong();
    // 패 나눠주기
    // 점수 초기화
}
bool count_Pae(Hawtoo *pae, int hand,int *d)
{ 
    int data;
    int count = 0;

    while(pae!=NULL){
	data = pae->data;
	if(hand/4 == data/4){
	    d[count] = data;
	    count ++;
	}
	pae = pae->next;
    }
    if(count == 2)
	return true;
    return false;
}
bool check_Num(Hawtoo *pae, int turn)  // 흔들기나 총통을 위해 패에 몇개가 같은게 있는지 검사
{
    Hawtoo *head= pae;
    int num[7];
    int count = 0;
    for(int i=0;i<7;i++){     
	printf("head->data %d\n",head->data);
	num[i] = (head->data) / 4;
	head = head->next;
    }

    for(int i=0;i<7;i++){
	count = 0;
	for(int k=i+1;k<7;k++){
	    if(num[i] == num[k])
		count++;
	    if(count ==3)
		return true;
	    else if(count ==2){
		player[turn].wave = true;
		return false;
	    }
	}
    }
    return false;
}
void check_Chong()
{
    int turn = 0;
    for(int i=0;i<3;i++){
	turn = get_Turn();
	if( check_Num(player[turn].hand_Pae,turn) == true){
	    get_Money(turn);
	    new_Game();
	}
	hand_Turn(turn);
    }
}


void set_Player(){
    for(int i=0; i<3; i++){
	// Player *player = (Player*)malloc(sizeof(Player)*3);
	player[i].go = 0;
	player[i].gobak = false;
	player[i].chongtong = false;
	player[i].score = 0;
	player[i].myTurn = false;
	player[i].gwang = false;
	player[i].pi = false;
    }

    player[0].myTurn = true;
}

void give_Pae(){
    Hawtoo *all_Pae = (Hawtoo *)malloc(sizeof(Hawtoo)*48);
    Hawtoo *player_Pae = (Hawtoo *)malloc(sizeof(Hawtoo)*3);

    Hawtoo *dummy = (Hawtoo *)malloc(sizeof(Hawtoo));
    Hawtoo *spread = (Hawtoo *)malloc(sizeof(Hawtoo));
    Hawtoo  *pae;
    for(int i=0;i<48;i++)
    {
	all_Pae[i].data = i;
	all_Pae[i].next =NULL;
    }
    for(int i=0;i<3;i++){
	player[i].eat_Pae = (Hawtoo *)malloc(sizeof(Hawtoo));
	player[i].eat_Pae->data = -1;
	player[i].eat_Pae->next = NULL;
    }
    //suffle
    shuffle_Pae(all_Pae);

    pae = &player_Pae[0];
    for(int i=0;i<7;i++){
	pae->data = all_Pae[i].data;
	if(i!=6)
	    pae->next = &all_Pae[i+1];
	else
	    pae->next = NULL;
	pae= pae->next;
    }

    pae = &player_Pae[1];
    for(int i=7;i<14;i++){
	pae->data = all_Pae[i].data;
	if(i!=13)
	    pae->next = &all_Pae[i+1];
	else
	    pae->next = NULL;
	pae = pae->next;
    }

    pae = &player_Pae[2];
    for(int i=14;i<21;i++){
	pae->data = all_Pae[i].data;
	if(i!=20)
	    pae->next = &all_Pae[i+1];
	else
	    pae->next = NULL;
	pae =pae->next;
    }
    player[0].hand_Pae = &player_Pae[0];
    player[1].hand_Pae = &player_Pae[1];
    player[2].hand_Pae = &player_Pae[2];

    pae = spread;
    for(int i=21;i<27;i++){
	pae->data = all_Pae[i].data;
	if(i!=26)
	    pae->next = &all_Pae[i+1];
	else
	    pae->next = NULL;
	pae = pae->next;
    }


    pae = dummy;
    for(int i=27;i<48;i++){
	pae->data = all_Pae[i].data;
	if(i!=47)
	    pae->next = &all_Pae[i+1];
	else
	    pae->next = NULL;
	pae = pae->next;
    }
    dummy_Pae = dummy;
    spread_Pae = spread;

    //나눠주기, 정렬하기
    order_Pae(player[0].hand_Pae);
    order_Pae(player[1].hand_Pae);
    order_Pae(player[2].hand_Pae);
    order_Pae(spread_Pae);
}
void shuffle_Pae(Hawtoo *pae){
    srand(time(NULL));

    int array[48];
    for(int i=0;i<48;i++){ //배열 초기화
	array[i] =i;
    }

    for(int i=0;i<48;i++){  // 배열 셔플
	int x= random()%48;
	int y= random()%48;
	int z= array[x];
	array[x] = array[y];
	array[y] = z;
    }

    for(int i=0;i<48;i++){   // 셔플한 값을 패에 집어넣기
	pae[i].data=array[i];
    }
}

// 낸카드 비교하기

//패를 내면 깔린패와 비교하기, 1. 한개가 같은경우 쌀수도 잇음 2. 두개가 같은경우 둘중 고르기, 3. 세개가 같은경우 다가져오기 뺏기
//void compare_Spread(Hawtoo *dummyPae, Hawtoo *spread, Hawtoo *eatPae, int hand)
void compare_Spread(int turn,int hand)
{

    int count[3] = {50,50,50};
    int d[2];
    int choice;
    bool check_sul = false;
    bool check_shot = false;

    Hawtoo *dummy = dummy_Pae;
    Hawtoo *spreadNew = spread_Pae;
    Hawtoo *eatPae = player[turn].eat_Pae;
    if(hand != -1){
	compare_Pae(spreadNew, hand, count); // 내가 낸 hand패와 몇개가 겹치는지

	if(count[2] != 50) // 쌓여있는 세개의 패를 먹을때
	{ 
	    add_Pae(eatPae, count[0]);
	    add_Pae(eatPae, count[1]);
	    add_Pae(eatPae, count[2]);
	    add_Pae(eatPae, hand);
	    delete_Pae(spreadNew, count[0]);
	    delete_Pae(spreadNew, count[1]);
	    delete_Pae(spreadNew, count[2]);
	    take_Pi(turn); //피 뺏어오기
	    // take_Pi();
	}
	else if(count[1] != 50) // 두개있을 때 고르기, 여기도 쪽 체크해야함
	{
	    printf("1 or 2\n");
	    while(1){
		scanf("%d",&choice);

		if(choice == 1){              // 골라서 가져오기, 그 후 뒤집기
		    add_Pae(eatPae,count[0]);
		    add_Pae(eatPae,hand);
		    delete_Pae(spreadNew,count[0]);
		    break;
		}
		else if(choice == 2){
		    add_Pae(eatPae,count[1]);
		    add_Pae(eatPae,hand);
		    delete_Pae(spreadNew,count[1]);
		    break;
		}
		else
		    printf("다시 고르세요\n");
	    }
	}

	else if(count[0] != 50) // 한개
	{ 
	    if(dummy->data/4 == hand /4){
		check_sul = true;
		add_Pae(spreadNew,hand);
	    }// 뒤집을 패와 같다면 설사
	    else if(count_Pae( player[turn].hand_Pae,hand,d) == true)  // 흔든 패를 냈을때 하나 잇는경우
	    {

		add_Pae(eatPae,d[0]);
		add_Pae(eatPae,d[1]);
		add_Pae(eatPae,hand);
		add_Pae(eatPae,count[0]);
		delete_Pae(player[turn].hand_Pae,d[0]);
		delete_Pae(player[turn].hand_Pae,d[1]);
		delete_Pae(spreadNew,count[0]);
		take_Pi(turn);
	    }
	    else{ // 
		add_Pae(eatPae,hand);
		add_Pae(eatPae,count[0]);
		// printf("count 0 : %d \n",count[0]);
		delete_Pae(spreadNew, count[0]);
	    }
	}
	else // 같은게 없음
	{
	    if(dummy->data/4 == hand /4) {//쪽이라면
		check_shot = true;
		add_Pae(spreadNew, hand);
	    }
	    else
		add_Pae(spreadNew, hand);  // 깔린패에 추가 여기서 쪽을 처리해야함
	}
    }
    // 이제 뒤집은 패를 깔린패와 비교
    for(int k=0;k<3;k++)
	count[k] = 50;

    compare_Pae(spreadNew, dummy->data, count);

    if(count[2] != 50) // 뒤집기로 설사 먹음
    {
	add_Pae(eatPae,count[0]);
	add_Pae(eatPae,count[1]);
	add_Pae(eatPae,count[2]);
	add_Pae(eatPae,dummy->data);

	delete_Pae(spreadNew,count[0]);
	delete_Pae(spreadNew,count[1]);
	delete_Pae(spreadNew,count[2]);
	take_Pi(turn); //피 뺏어오기
    } 
    else if(count[1] != 50) // 뒤집기로 둘중 하나 고르기
    {
	if(check_sul == true){
	    add_Pae(spreadNew, dummy->data);
	}
	else{
	    printf("1 or 2\n");
	    while(1){
		scanf("%d",&choice);

		if(choice == 1){              // 골라서 가져오기
		    add_Pae(eatPae,count[0]);
		    add_Pae(eatPae,dummy->data);
		    delete_Pae(spreadNew,count[0]);
		    break;
		}
		else if(choice == 2){
		    add_Pae(eatPae,count[1]);
		    add_Pae(eatPae,dummy->data);
		    delete_Pae(spreadNew,count[1]);
		    break;
		}
		else
		    printf("다시 고르세요\n");
	    }
	}

    }
    else if(count[0] != 50)
    {
	if(check_shot ==true)
	{
	    printf("쪽!!!\n");
	    add_Pae(eatPae,dummy->data);
	    add_Pae(eatPae,count[0]);
	    take_Pi(turn); //피 뺏어오기
	    // 패 뺏어오기
	    delete_Pae(spreadNew,count[0]);
	}
	else
	{
	    add_Pae(eatPae,dummy->data);
	    add_Pae(eatPae,count[0]);
	    delete_Pae(spreadNew,count[0]);
	    if(spreadNew ->data == -1) //싹쓸이
		take_Pi(turn);
	}   
    }
    else // 뒤집은것이 맞는게 없음
	add_Pae(spreadNew,dummy->data);

    delete_Pae(dummy, dummy->data); //더미에서 하나 제거
    order_Pae(spreadNew);
    order_Pae(eatPae);
}

void compare_Pae(Hawtoo *target, int data, int *count)
{
    Hawtoo *head;
    head = target;
    int i=0;
    while(head != NULL)
    {
	if(head->data/4 == data/4){
	    count[i]=head->data;
	    i++;
	}
	head = head->next;
    }
}
void take_Pi(int turn){
    Hawtoo *pae = NULL;
    int data;
    int check=0;
    for(int i=0;i<3;i++){
	if(player[i].eat_Pae->data == -1){ //먹은패가 없는경우
	    continue;
	}
	if(player[i].myTurn == true){
	    continue;
	}
	pae = player[i].eat_Pae;
	while(pae !=NULL){
	    data = pae->data;
	    if((data % 4 ==2 || data %4 == 3) && (data /4 !=11)){
		add_Pae(player[turn].eat_Pae, data);
		delete_Pae(player[i].eat_Pae,data);
		check = 1;
		break;
		// 먹은패가 있는경우
	    }
	    pae = pae->next;
	}
	if(check == 0)
	{
	    while(pae !=NULL){
		data = pae->data;
		if(data  ==41 || data == 47){
		    add_Pae(player[turn].eat_Pae, data);
		    delete_Pae(player[i].eat_Pae,data);
		    check = 1;
		    break;
		}
		pae = pae->next;

	    }

	}
    }
}
void order_Pae(Hawtoo *pae)  // Pae를 순서대로 정
{
    Hawtoo *A;
    Hawtoo *B;
    int i;
    if( pae ==NULL){
	printf("정렬하려는 패가 비었습니다.");
	exit(0);
    }
    for(A = pae; A->next !=NULL; A = A->next )
    {
	for( B = pae; B->next !=NULL; B = B->next)
	{
	    if(B->data > B->next->data)
	    {
		i = B->data;
		B->data = B->next->data;
		B->next->data = i;
	    }
	}

    }

}
void add_Pae(Hawtoo *pae, int data){
    Hawtoo *head = pae;
    Hawtoo *new = (Hawtoo *)malloc(sizeof(Hawtoo));  // 추가할 하나의 Hawtoo 구조체
    new->data = data;
    new->next = NULL;
    if(head ->data == -1){
	head->data = data;
	head->next=  NULL;
	return;
    }
    while(head->next !=NULL){  // 끝부분 도달
	head = head->next;
    }
    head->next = new;  // 화투패 추가
}


void delete_Pae(Hawtoo *pae, int data){
    Hawtoo *head = pae;
    Hawtoo *prev = NULL;

    if(head->next ==NULL){
	head ->data = -1;
	return;
    }
    if (head !=NULL && head->data == data){ // 더미에서 패를 빼는 경우
	head->data = head->next->data;
	head->next = head->next->next;
	return;
    }
    while(head !=NULL){
	if(head->data == data){
	    prev->next = head->next;
	    head ->next = head;
	    return;
	}
	else
	{
	    prev = head;
	    head = head->next;
	}


    }
}












