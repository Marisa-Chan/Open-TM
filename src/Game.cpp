#include "res.h"
#include <vector>



Pole pole[6][6]; //Игровое поле
//[x][x][0]: это тип занимаемой карты
//Type 100-Border
//Type 99 - Blocked 1
//Type 98 - Blocked 2
//Type 0 - Clear
//Type 1(BlueTp)-Blue
//Type 2(RedTp)-Red
//
//[x][x][1]:ссылка на карту
//[x][x][2]:чья изначально 1B и 2R
//[x][x][3]:номер в стопке

uint8_t Sel_Slot=0;
bool Pl_Half_End=false;////   ; Половина хода игрока
bool Pl_Turn_End=false;////   ;2-я Половина хода

uint8_t Turn=0; //Колличество ходов, при достижении 10 или более, выходим.

uint8_t WhoGo=0; //;Чей ход? 0-синий, 1 красный

uint8_t PPdx=1,PPdy=1;




uint32_t enemyScore,MyScore;



bool Game_Local_May_Exit=false;

uint8_t  InGameRed=0;
uint8_t InGameBlue=0;

uint8_t KtoFight[9][2];
uint8_t KtoOkup[9][2];
uint8_t SkFight,SkOkup;

uint8_t NotDraw[2][2]; //две карты, которые не будем рисовать


void ClearPole() // Чистим Поле и ставим границы
{
    memset(pole,0,6*6*sizeof(Pole));
    for (uint8_t i=0;i<6;i++)
    {
        pole[i][0].tip=100;
        pole[i][5].tip=100;
        pole[0][i].tip=100;
        pole[5][i].tip=100;
    }
}

void FlushCards()
{
    for (uint8_t i= 0; i<5; i++)
    {
        MyCards[i].used=false;
        EnemyCards[i].used=false;
    }

}





void DrawPlayerCards(SDL_Surface *scr)// Рисуем карты игрока(справа)
{
    for (uint8_t i=0;i<5;i++)
    {
        if (!MyCards[i].used)
        {
            if (MyCards[i].crd)
                DrawCard2(MyCards[i].crd,  0,264,-1+i*48,scr);
        }
    }
}


void DrawPlayercardsGrayed(uint8_t Crome,SDL_Surface *scr) //Рисуем карты игрока(справа), затемненные кроме выбранной карты.
{
    for (uint8_t i=0;i<5;i++)
    {
        if (!MyCards[i].used)
            if (i!=Crome)   DrawAImage(blk_crd_img,264,-1+i*48,160,scr);
    }
}


uint32_t LXtoSX(uint8_t x) //Из координат сетки в координаты экрана X
{
    return 71+(x-1)*(43);
}

uint32_t LYtoSY(uint8_t y) //Из координат сетки в координаты экрана Y
{
    return 8+(y-1)*(52);
}


void DrawEnemyCards(SDL_Surface *scr)//Рисуем вражеские карты, задник.
{
    for (uint8_t i=0;i<5;i++)
    {
        if (!EnemyCards[i].used)
            if (EnemyCards[i].crd)
                DrawImage(enm_Card,16,26+i*14,scr);
    }
}

void Global_Draw_Game_scrn(SDL_Surface *scr) //Рисуем задник и все все все. Чтобы не писать много раз.
{
    DrawBkg(BKG_GAME,scr);
    DrawPolyCards(scr);
    DrawPlayerCards(scr);
    DrawEnemyCards(scr);
    DrawSlash(scr);
    Skolko_Kakogo();
    Draw_Skolko_Kakogo(scr);
}

void RandomBlocked(SDL_Surface *scr) //Заполняем поле блокираторами от 0 до 6 штук
{
    uint8_t dx,dy;
    uint8_t vi;
    uint8_t dii;
    uint8_t trnd;
    trnd=rand()%6;
    for (uint8_t i=0;i<trnd;i++)
    {
        while (true)
        {
            dx=rand()%4+1;
            dy=rand()%4+1;
            if (pole[dx][dy].tip==0) break;
        }

        dii=(rand() & 1)+98;

        for (vi=0;vi<8;vi++)
        {
            Global_Draw_Game_scrn(scr);
            if (dii==98) DrawImage(Blockedcrd_1_hlp[vi],LXtoSX(dx)-10.5+1.3125*vi,LYtoSY(dy)-12.75+1.59375*vi,scr);
            if (dii==99) DrawImage(Blockedcrd_2_hlp[vi],LXtoSX(dx)-10.5+1.3125*vi,LYtoSY(dy)-12.75+1.59375*vi,scr);
            SDL_Flip(scr);
            SDL_Delay(11*fpsmul);
        }
        pole[dx][dy].tip=dii;
        Global_Draw_Game_scrn(scr);
        SPU(sBlock);
        SDL_Flip(scr);
        SDL_Delay(8*fpsmul);

    }
}





void DrawPolyCards(SDL_Surface *scr)//Рисуем Поле со всеми картами.
{
    bool dpcd=true;
    for (uint8_t dy=1;dy<5;dy++)
        for (uint8_t dx=1;dx<5;dx++)
        {
            dpcd=true;

            for (uint8_t i=0;i<2;i++)
                if (NotDraw[i][0]==dx && NotDraw[i][1]==dy) dpcd=false;

            if (dpcd)
            {
                if ((pole[dx][dy].tip)==98)
                    DrawImage(Blockedcrd_1,LXtoSX(dx),LYtoSY(dy),scr);

                if ((pole[dx][dy].tip)==99)
                    DrawImage(Blockedcrd_2,LXtoSX(dx),LYtoSY(dy),scr);


                if (pole[dx][dy].tip==1 || pole[dx][dy].tip==2)
                    if (pole[dx][dy].crd)
                        DrawCard2(pole[dx][dy].crd,pole[dx][dy].tip-1,LXtoSX(dx),LYtoSY(dy),scr);
            }

        }
}

void Draw_Skolko_Kakogo(SDL_Surface *scr) //;Рисуем сколько чьих карт
{
    if (InGameRed<10)
        DrawAnimImage(Slash_Red_Numbers,27,152,InGameRed,scr);
    else
    {
        DrawAnimImage(Slash_Red_Numbers,20,152,1,scr);
        DrawAnimImage(Slash_Red_Numbers,37,152,0,scr);
    }

    if (InGameBlue<10)
        DrawAnimImage(Slash_Blue_Numbers,41,189,InGameBlue,scr);
    else
    {
        DrawAnimImage(Slash_Blue_Numbers,34,189,1,scr);
        DrawAnimImage(Slash_Blue_Numbers,51,189,0,scr);
    }
}

void DrawSlash(SDL_Surface *scr) //Рисуем слеш
{
    DrawImage(Slash_img,17,172,scr);
}

void Skolko_Kakogo()//Подсчитываем сколько чьих карт.
{
    InGameBlue=0;
    InGameRed=0;
    for (uint8_t dy=1;dy<5;dy++)
        for (uint8_t dx=1;dx<5;dx++)
        {
            if (pole[dx][dy].tip==1) InGameBlue++;
            if (pole[dx][dy].tip==2) InGameRed++;
        }
}



void EnemyVibor(uint8_t Who)
{
    enemy_ssortirovka(Who);
    enemy_spodshet(Who);


    if (EnemiesNumCards[Who]<5)
        for (uint8_t i=0; i<5; i++)
            enemy_addy(Who);


    for (uint8_t q=0;q<5;q++)
    {
        int32_t sil=-1;
        uint8_t sslot=0;
        for (uint8_t i=0; i<EnemiesNumCards[Who];i++)
        {

            card *tc=EnemiesCards[Who][i];
            if (sil < int32_t(tc->Attack+tc->MDefence + tc->PDefence))
            {
                sil = tc->Attack+tc->MDefence + tc->PDefence;
                sslot=i;
            }
        }

        EnemyCards[q].used=false;
        EnemyCards[q].crd=EnemiesCards[Who][sslot];

        EnemiesNumCards[Who]--;
        EnemiesCards[Who][sslot]=NULL;

        enemy_ssortirovka(Who);
        enemy_spodshet(Who);
    }
}

uint32_t EnemyCardsAllScore()
{
    uint32_t Score=0;
    for (uint8_t i=0;i<5;i++)
    {
        card *temp=EnemyCards[i].crd;
        Score+=temp->Attack+temp->PDefence+temp->MDefence;
    }
    return Score;
}

uint32_t PlayerCardsAllScore()
{
    uint32_t Score=0;
    for (uint8_t i=0;i<5;i++)
    {
        card *temp=MyCards[i].crd;
        Score+=temp->Attack+temp->PDefence+temp->MDefence;
    }
    return Score;
}

void Init_Game(SDL_Surface *scr) //;Инициализируем переменные игры, которые обязательны.
{

    EnemyVibor(WhoNow);

    FlushCards();
    ClearPole();
    Turn=0;
    InGameRed=0;
    InGameBlue=0;
    Game_Local_May_Exit=false;
    Pl_Half_End=false;
    Pl_Turn_End=false;
    PPdx=1;
    PPdy=1;
    delKilList();
    clearStrelList();

    enemyScore=EnemyCardsAllScore();
    MyScore=PlayerCardsAllScore();

    if  (ExtendMusic)
    {
        if (enemyScore<=(MyScore-20))
            spuMusic(2);


        if (enemyScore>=(MyScore+20))
            spuMusic(3);


        if (enemyScore>(MyScore-20) && enemyScore<(MyScore+20))
            spuMusic(4);

    }
    else
        spuMusic(1);

    ToFight(scr);
    RandomBlocked(scr);
    RandomFirstTurn(scr);

    DrawGame_LocalScreen(scr);
    SDL_Delay(500);
}


void ToFight(SDL_Surface *scr)
{

    DrawBkg(BKG_GAME,scr);
    DrawPlayerCards(scr);
    DrawSlash(scr);
    Skolko_Kakogo();
    Draw_Skolko_Kakogo(scr);
    SDL_Flip(scr);
    SDL_Delay(100);

    for (uint8_t i=0;i<43;i++)
    {
        DrawBkg(BKG_GAME,scr);
        DrawPlayerCards(scr);
        DrawSlash(scr);
        Draw_Skolko_Kakogo(scr);

        if (i<13)
            DrawImage(enm_Card,16,26+cos(i*0.12083)*214,scr);
        else
            DrawImage(enm_Card,16,26,scr);


        if (i>6 && i<20)
            DrawImage(enm_Card,16,26+14+cos((i-6)*0.12083)*214,scr);
        else if (i>19)
            DrawImage(enm_Card,16,26+14,scr);


        if (i>13 && i<27)
            DrawImage(enm_Card,16,26+28+cos((i-13)*0.12083)*214,scr);
        else if (i>26)
            DrawImage(enm_Card,16,26+28,scr);

        if (i>20 && i<34)
            DrawImage(enm_Card,16,26+42+cos((i-20)*0.12083)*214,scr);
        else if (i>33)
            DrawImage(enm_Card,16,26+42,scr);


        if (i>27 && i<41)
            DrawImage(enm_Card,16,26+56+cos((i-27)*0.12083)*214,scr);
        else if (i>40)
            DrawImage(enm_Card,16,26+56,scr);


        if ((i==13) || (i==20) || (i==27) || (i==34) || (i==41))
            SPU(sChif);


        SDL_Flip(scr);
#ifdef DINGOO
        SDL_Delay(10);
#else
        SDL_Delay(1000/50);
#endif
    }
    SDL_Delay(300);
}

void RandomFirstTurn(SDL_Surface *scr) //; Первый ход чей?
{
    WhoGo=rand()&1;
    uint32_t MonTime=millisec();
    uint32_t msecs=millisec();
    while (!(millisec()>msecs+800))
    {
        Global_Draw_Game_scrn(scr);
        DrawCoin(scr);
        SDL_Flip(scr);
        if (millisec()>MonTime+83)
        {
            SPU(sMonetka);
            MonTime=millisec();
        }
    }
    Global_Draw_Game_scrn(scr);
    DrawCoinF(WhoGo,scr);
    SDL_Flip(scr);
    SDL_Delay(500);

    switch (WhoGo)
    {
    case 0:
        DrawCoinMove(0,scr);
        break;
    case 1:
        DrawCoinMove(1,scr);
    }
}


void DrawCoinMove(uint8_t Who,SDL_Surface *scr) //;Рисуем перемещение монетки.
{
    uint32_t Nmtime=millisec();
    switch (Who)
    {
    case 0:
        while (millisec()<Nmtime+250)
        {
            float param;
            param=((Nmtime+250)-millisec())/2.5f;
            Global_Draw_Game_scrn(scr);
            DrawAImage(Coin[0],(274-1.37f*param),0.925f*param,1.27*param,scr);
            SDL_Flip(scr);
        }
        break;
    case 1:
        while (millisec()<Nmtime+250)
        {
            float param;
            param=((Nmtime+250)-millisec())/2.5f;
            Global_Draw_Game_scrn(scr);
            DrawAImage(Coin[4],1.37f*param,0.925f*param,1.27*param,scr);
            SDL_Flip(scr);
        }
    }
}

void PlayerTurn(SDL_Surface *scr)
{

    for (uint32_t i=0;i<5;i++)
        if (!MyCards[i].used)
        {
            Sel_Slot=i;
            break;
        }


    card * Pltemp;

    bool NameUbr=false;
    uint32_t NameMil=0;

viborkarti:
    Pl_Half_End=false;
    Pl_Turn_End=false;

    while (!Pl_Half_End)
    {
        Global_Draw_Game_scrn(scr);

        if (input_GetState(Ki_DOWN))
        {
            SPU(sKlik2);
            Sel_Slot++;
            Sel_Slot%=5;

            for (uint32_t i=0;i<4;i++)
            {
                if (MyCards[Sel_Slot].used)
                    Sel_Slot++;
                else
                    break;
                Sel_Slot%=5;
            }
        }

        if (input_GetState(Ki_UP))
        {
            SPU(sKlik2);
            if (Sel_Slot>0)
                Sel_Slot--;
            else
                Sel_Slot=4;
            Sel_Slot%=5;

            for (uint32_t i=0;i<4;i++)
            {
                if (MyCards[Sel_Slot].used)
                {
                    if (Sel_Slot>0)
                        Sel_Slot--;
                    else
                        Sel_Slot=4;
                }
                else
                    break;
                Sel_Slot%=5;
            }
        }

        if (input_GetState(Ki_X))
        {
            Pl_Half_End=true;
            SPU(sChif);
        }

        DrawStrelka(252,13+(Sel_Slot)*48,scr);

        DrawAnimImage(Buttons_img,16,8,5,scr);
        DrawImage(Imia,28,11,scr);

        Pltemp=MyCards[Sel_Slot].crd;

        if (input_GetState(Ki_R))
        {
            NameUbr=true;
            NameMil=millisec();
        }

        if (millisec()>NameMil+200)
            NameUbr=false;

        if (NameUbr)
        {
            CreateWindowText(320-(GetFFWidth(cardName[Pltemp->Number])+10),(Sel_Slot*48 - 1 +15),cardName[Pltemp->Number],scr);
        };

        SDL_Flip(scr);//flip2d()
        SDL_Delay(5);
    } // Выбираем карту

    Pl_Half_End=false;
    Pl_Turn_End=false;
    uint8_t dx,dy;

    dx=PPdx;
    dy=PPdy;



    while (!Pl_Turn_End)
    {
        Global_Draw_Game_scrn(scr);
        DrawPlayercardsGrayed(Sel_Slot,scr);

        //;If KeyDown(10) Then testprint()

        if (input_GetState(Ki_DOWN))
        {
            dy++;
            SPU(sKlik2);
        };
        if (input_GetState(Ki_UP))
        {
            dy--;
            SPU(sKlik2);
        };
        if (input_GetState(Ki_LEFT))
        {
            dx--;
            SPU(sKlik2);
        };
        if (input_GetState(Ki_RIGHT))
        {
            dx++;
            SPU(sKlik2);
        };

        if (dx<1) dx=1;
        if (dx>4) dx=4;
        if (dy<1) dy=1;
        if (dy>4) dy=4;

        if (input_GetState(Ki_O))
        {
            SPU(sOtmen);
            goto viborkarti;
        }

        if (input_GetState(Ki_X) && pole[dx][dy].tip==0)
        {
            SPU(sChif);
            Pl_Turn_End=true;
            MyCards[Sel_Slot].used=true;
            pole[dx][dy].tip=1;
            pole[dx][dy].crd=MyCards[Sel_Slot].crd;
            pole[dx][dy].wse=1;
        }

        DrawStrelka(LXtoSX(dx)-12,LYtoSY(dy)+13,scr);

        SDL_Flip(scr);//flip2d()
        SDL_Delay(5);
    }//Ставим её на поле

    skolko(dx,dy);
    GoFight(dx,dy,1,scr);
    PPdx=dx;
    PPdy=dy;

    Pl_Turn_End=false;
    Pl_Half_End=false;

}
void EnemyTurn(SDL_Surface *scr)
{
    SDL_Delay(400);
    if (Turn==0)
        Bot_PutItDefendedIfFirst(Bot_FindDefencedCard(),scr);
    else
        Bot_FindAndAttack(scr);
}

void Bot_FindAndAttack(SDL_Surface *scr)
{
    Func1();
    Func2();

    if (Bot_Finking(scr)==0)
        Bot_PutItDefendedIfFirst(Bot_FindDefencedCard(),scr);
}


uint8_t FindMinDef(card * s)
{
    return s->MDefence > s->PDefence ? s->PDefence : s->MDefence;
}

uint8_t FindMinDef2(card * s)
{
    uint8_t loc;
    loc= s->MDefence > s->PDefence ? s->PDefence : s->MDefence;
    return loc > s->Attack ? s->Attack : loc;
}

uint8_t GetTypeElement(uint8_t x,uint8_t y,uint8_t z)
{
    return pole[GetXFromIndex(x,y,z)][GetYFromIndex(x,y,z)].tip;
}


uint8_t GetXFromIndex(uint8_t x,uint8_t y,uint8_t z)
{
    switch (z)
    {
    case 1:
        return x-1;

    case 2:
        return x;

    case 3:
        return x+1;

    case 4:
        return x+1;

    case 5:
        return x+1;

    case 6:
        return x;

    case 7:
        return x-1;

    case 8:
        return x-1;
    }

    return 0;
}

uint8_t GetYFromIndex(uint8_t x,uint8_t y,uint8_t z)
{
    switch (z)
    {
    case 1:
        return y-1;

    case 2:
        return y-1;

    case 3:
        return y-1;

    case 4:
        return y;

    case 5:
        return y+1;

    case 6:
        return y+1;

    case 7:
        return y+1;

    case 8:
        return y;
    }

    return 0;
}


uint8_t InvertIndex(uint8_t z)
{
    return (z+3)%8+1;
}



int8_t dim1[6][6];// ;лЮЯЯХБ ЯЙНКЭЙН БЕЯ С ЙЮПРШ
void Func1()
{
    memset(dim1,0,6*6);

    for (uint8_t i=0;i<6;i++)
    {
        dim1[i][0]=-100;
        dim1[i][5]=-100;
        dim1[0][i]=-100;
        dim1[5][i]=-100;
    }

    uint8_t Skollko;
    for (uint8_t y=1;y<5;y++)
        for (uint8_t x=1;x<5;x++)
        {
            Skollko=0;
            if (pole[x][y].tip==1)
            {
                Skollko=1;
                for (uint8_t z=1;z<9;z++)
                    if ((pole[x][y].crd->Arr >> (z-1)) & 1)
                        if (GetTypeElement(x,y,z)==1)
                            Skollko++;
            }
            dim1[x][y]=Skollko;
        }
}

int8_t dim2[6][6];//лЮЯЯХБ 0, 1 Х 2
void Func2()
{
    memset(dim2,0,6*6);

    for (uint8_t i=0;i<6;i++)
    {
        dim2[i][0]=-100;
        dim2[i][5]=-100;
        dim2[0][i]=-100;
        dim2[5][i]=-100;
    }


    for (uint8_t y=1;y<5;y++)
        for (uint8_t x=1;x<5;x++)
            if (dim1[x][y]>0)
            {
                dim2[x][y]=2;
                for (uint8_t z=1;z<9;z++)
                    if (GetTypeElement(x,y,z)==0)
                        dim2[GetXFromIndex(x,y,z)][GetYFromIndex(x,y,z)]=1;

            }
}

void Bot_PutItDefendedIfFirst(uint8_t Slot,SDL_Surface *scr)
{

    Make_Select(Slot,scr);

    card *temp=EnemyCards[Slot].crd;
    uint8_t Array=temp->Arr;

    uint8_t Arrr[16];
    memset(Arrr,0,16);
    uint8_t Skolko;
    for (uint8_t y=1;y<5;y++)
        for (uint8_t x=1;x<5;x++)
        {
            Skolko=0;
            if (pole[x][y].tip==0)
            {
                Skolko=1;
                for (uint8_t z=1;z<9;z++)
                {
                    if ((Array>>(z-1)) & 1)
                        if (GetTypeElement(x,y,z)==0)
                            Skolko++;

                    if (!((Array>>(z-1)) & 1))  //// 1 xor 1 = 1 !!   1 xor 0 = 1!!!
                        if ((GetTypeElement(x,y,z)==99) ||\
                                (GetTypeElement(x,y,z)==98) ||\
                                (GetTypeElement(x,y,z)==100)||\
                                (GetTypeElement(x,y,z)==1))
                            Skolko++;
                }
            }
            Arrr[(x-1)+(y-1)*4]=Skolko;
        }


    uint8_t Arrb[16];
    for (uint8_t i=0;i<16;i++)
        Arrb[i]=i;

    uint8_t tempi;
    for (uint8_t h=0;h<15;h++)
        for (uint8_t i=0;i<15;i++)
            if (Arrr[Arrb[i]]<Arrr[Arrb[i+1]])
            {
                tempi=Arrb[i];
                Arrb[i]=Arrb[i+1];
                Arrb[i+1]=tempi;
            }


    tempi=Arrr[Arrb[0]];
    for (uint8_t i=1;i<16;i++)
        if (!(tempi==Arrr[Arrb[i]]))
        {
            tempi=(i-1);
            break;
        }


    if (tempi>0)
        tempi=rand()%(tempi+1);
    else
        tempi=0;

    tempi=Arrb[tempi];

    SPU(sChif);

    uint8_t dx=((tempi % 4)+1);
    uint8_t dy=(tempi/4 + 1);

    pole[dx][dy].tip=2;
    pole[dx][dy].crd=EnemyCards[Slot].crd;
    pole[dx][dy].wse=2;
    EnemyCards[Slot].used=true;
    skolko(dx,dy);
    GoFight(dx,dy,2,scr);

}

uint8_t Bot_FindDefencedCard()
{
    uint8_t Def=0,Sel=0;
    for (uint8_t i=0;i<5;i++)
        if (!EnemyCards[i].used)
        {
            Def=EnemyCards[i].crd->MDefence+EnemyCards[i].crd->PDefence;
            Sel=i;
            break;
        }

    for (uint8_t i=Sel;i<5;i++)
        if (!EnemyCards[i].used)
            if  (Def<(EnemyCards[i].crd->MDefence+EnemyCards[i].crd->PDefence))
            {
                Def=EnemyCards[i].crd->MDefence+EnemyCards[i].crd->PDefence;
                Sel=i;
            }
    return Sel;
}

bool Bot_Finking(SDL_Surface *scr)
{

    struct BotBrain
    {
        uint8_t Slot;
        uint8_t wes;
        uint8_t x;
        uint8_t y;
    };

    uint8_t Many;
    BotBrain * listt[80];
    bool Selects;
    uint8_t wsel;

    memset(listt,0,80*sizeof(BotBrain *));
    Many=0;

    for (uint8_t i=0;i<5;i++)
        for (uint8_t y=1;y<5;y++)
            for (uint8_t x=1;x<5;x++)
            {
                Selects=false;
                wsel=0;

                if (!EnemyCards[i].used)
                    if (dim2[x][y]==1)
                    {
                        wsel=1;

                        for (uint8_t z=1;z<9;z++)
                            if (GetTypeElement(x,y,z)==1)
                            {
                                if (((pole[GetXFromIndex(x,y,z)][GetYFromIndex(x,y,z)].crd->Arr) >> (InvertIndex(z)-1)) & 1)
                                {
                                    if ((EnemyCards[i].crd->Arr >> (z-1)) & 1)
                                        switch (EnemyCards[i].crd->Atype)
                                        {
                                        case aT_P:
                                            if (EnemyCards[i].crd->Attack>=pole[GetXFromIndex(x,y,z)][GetYFromIndex(x,y,z)].crd->PDefence)
                                                wsel+=dim1[GetXFromIndex(x,y,z)][GetYFromIndex(x,y,z)];
                                            else
                                                Selects=true;
                                            break;
                                        case aT_M:
                                            if (EnemyCards[i].crd->Attack>=pole[GetXFromIndex(x,y,z)][GetYFromIndex(x,y,z)].crd->MDefence)
                                                wsel+=dim1[GetXFromIndex(x,y,z)][GetYFromIndex(x,y,z)];
                                            else
                                                Selects=true;
                                            break;
                                        case aT_X:
                                            if (EnemyCards[i].crd->Attack>=FindMinDef(pole[GetXFromIndex(x,y,z)][GetYFromIndex(x,y,z)].crd))
                                                wsel+=dim1[GetXFromIndex(x,y,z)][GetYFromIndex(x,y,z)];
                                            else
                                                Selects=true;
                                            break;
                                        case aT_A:
                                            if (EnemyCards[i].crd->Attack>=FindMinDef2(pole[GetXFromIndex(x,y,z)][GetYFromIndex(x,y,z)].crd))
                                                wsel+=dim1[GetXFromIndex(x,y,z)][GetYFromIndex(x,y,z)];
                                            else
                                                Selects=true;
                                        }
                                }
                                else
                                {
                                    if ((EnemyCards[i].crd->Arr >> (z-1)) & 1)
                                        wsel++;
                                }
                            }
                    }
                if (Selects==false && wsel>0)
                {
                    listt[Many]=new BotBrain;
                    listt[Many]->Slot=i;
                    listt[Many]->wes=wsel;
                    listt[Many]->x=x;
                    listt[Many]->y=y;
                    Many++;
                }
            }
    if (Many>0)
    {
        for (uint8_t j=0;j<Many-1;j++)
            for (uint8_t i=0;i<Many-1;i++)
            {
                if (listt[i]->wes<listt[i+1]->wes)
                {
                    BotBrain *tmp=listt[i];
                    listt[i]=listt[i+1];
                    listt[i+1]=tmp;
                }
            }


        //temp.BotBrain=Object.BotBrain(listt[0])
        Make_Select(listt[0]->Slot,scr);
        SPU(sChif);
        pole [listt[0]->x] [listt[0]->y] .tip=2;
        pole [listt[0]->x] [listt[0]->y] .crd=EnemyCards[listt[0]->Slot].crd;
        pole [listt[0]->x] [listt[0]->y] .wse=2;
        EnemyCards[listt[0]->Slot].used=true;
        skolko(listt[0]->x,listt[0]->y);
        GoFight(listt[0]->x,listt[0]->y,2,scr);


        for (uint8_t j=0;j<Many;j++)
            if (listt[j])
                delete listt[j];

        return 1;
    }
    else
    {
        for (uint8_t j=0;j<Many;j++)
            if (listt[j])
                delete listt[j];

        return 0;
    }


}

void Make_Select(uint8_t indx, SDL_Surface *scr)  //Vizualise card selection by enemy
{
    for (uint8_t i=0; i<5;i++)
    {
        if (!EnemyCards[i].used)
        {
            DrawBkg(BKG_GAME,scr);
            DrawPolyCards(scr);
            DrawPlayerCards(scr);
            for (uint8_t j=0; j<5;j++)
                if (!EnemyCards[j].used)
                {
                    if (j!=i)
                        DrawImage(enm_Card,16,26+j*14,scr);
                    else
                        DrawImage(enm_Card,38,26+j*14,scr);
                }
            DrawSlash(scr);
            Skolko_Kakogo();
            Draw_Skolko_Kakogo(scr);
            SDL_Flip(scr);
            SPU(sChif);
            SDL_Delay(100);
        }

    }

    DrawBkg(BKG_GAME,scr);
    DrawPolyCards(scr);
    DrawPlayerCards(scr);
    for (uint8_t j=0; j<5;j++)
        if (!EnemyCards[j].used)
        {
            if (j!=indx)
                DrawImage(enm_Card,16,26+j*14,scr);
            else
                DrawImage(enm_Card,38,26+j*14,scr);
        }
    DrawSlash(scr);
    Skolko_Kakogo();
    Draw_Skolko_Kakogo(scr);
    SDL_Flip(scr);
    SDL_Delay(400);
}

void Game_Turn(SDL_Surface *scr)//;Распределитель ходов
{
    switch (WhoGo)
    {
    case 0:
        PlayerTurn(scr);
        break;
    case 1:
        EnemyTurn(scr);
    }

    WhoGo++;
    WhoGo&=1;

    Turn++;
}


void Draw_State_Of_End(uint8_t index, uint8_t alphas,SDL_Surface *scr)
{
    SDL_Surface *surf;
    switch (index)
    {
    case 0:
        surf=Win_Scrn_Game;
        break;

    case 1:
        surf=Lose_Scrn_Game;
        break;

    case 2:
        surf=Super_Scrn_Game;
        break;

    case 3:
        surf=NoWho_Scrn_Game;
    }

    DrawAImage(surf,156-surf->w/2,105-surf->h/2,alphas,scr);
}



void DrawGame_LocalScreen(SDL_Surface *scr)
{
    while (!Game_Local_May_Exit)
    {
        Global_Draw_Game_scrn(scr);

        Game_Turn(scr);

        Global_Draw_Game_scrn(scr);

        if (Turn>=10) Game_Local_May_Exit=true;

        SDL_Flip(scr);
    }
    Game_Local_May_Exit=false;


    if (InGameRed>InGameBlue)
        vPlayer.Pl_winLose++;

    if (InGameRed<InGameBlue)
    {
        if (enemyScore<=(MyScore-20))
            vPlayer.Pl_v_Gil+=50;

        if (enemyScore>=(MyScore+20))
            vPlayer.Pl_v_Gil+=125;

        if (enemyScore>(MyScore-20) && enemyScore<(MyScore+20))
            vPlayer.Pl_v_Gil+=75;

        vPlayer.Pl_winWIn++;
    }

    if (InGameRed==InGameBlue)
        vPlayer.Pl_winBoth++;

    if (ExtendMusic)
    {
        if (InGameRed>InGameBlue)
            spuMusic(6);
        else if (InGameRed==InGameBlue)
            spuMusic(7);
        else if (InGameRed<InGameBlue)
            spuMusic(5);
    }
    else
    {
        if (InGameRed>InGameBlue)
            SPU(sLose);
        else if (InGameBlue==10)
            SPU(sSuper);
        else if (InGameRed==InGameBlue)
            SPU(sBoth);
        else if (InGameRed<InGameBlue)
            SPU(sWin);
    }


    uint8_t EndAlphaEnd=0;
    uint32_t eae_tik=millisec();

    while (EndAlphaEnd<249)
    {
        if (millisec()>eae_tik+6)
        {
            eae_tik=millisec();
            EndAlphaEnd+=6;
        }

        Global_Draw_Game_scrn(scr);
        if (InGameRed>InGameBlue)
            Draw_State_Of_End(1,EndAlphaEnd,scr);
        else if (InGameBlue==10)
            Draw_State_Of_End(2,EndAlphaEnd,scr);
        else if (InGameRed==InGameBlue)
            Draw_State_Of_End(3,EndAlphaEnd,scr);
        else if (InGameRed<InGameBlue)
            Draw_State_Of_End(0,EndAlphaEnd,scr);
        SDL_Flip(scr);
        #ifdef DINGOO
        SDL_Delay(10);
        #else
        SDL_Delay(20);
        #endif
    }

    while (!(input_GetState(Ki_X) || input_GetState(Ki_O) || input_GetState(Ki_D) || input_GetState(Ki_4)))
    {
        Global_Draw_Game_scrn(scr);
        if (InGameRed>InGameBlue)
            Draw_State_Of_End(1,255,scr);
        else if (InGameBlue==10)
            Draw_State_Of_End(2,255,scr);
        else if (InGameRed==InGameBlue)
            Draw_State_Of_End(3,255,scr);
        else if (InGameRed<InGameBlue)
            Draw_State_Of_End(0,255,scr);
        SDL_Flip(scr);
    }

    //FlushKeys()
    //FlushJoy()
    Finalize_Game(scr);

    DrawBkg(BKG_MENU,scr);
    DrawEndCards(scr);
    SDL_Flip(scr);
    DrawBkg(BKG_MENU,scr);
    DrawEndCards(scr);
    SDL_Flip(scr);
    if (DrawTrueOrNo2(GetLangString(11),scr)) //Сыграть еще?
        NextScreen(scrSelect);
    else
        NextScreen(scrMain);

    SPU(sChif);

}// Здесь собственно и идёт вся игра.


void ClearObaSpiska()
{
    memset(KtoFight,0,9*2);
    memset(KtoOkup,0,9*2);
    SkFight=0;
    SkOkup=0;
}


int32_t sgn(int32_t x)
{
    if (x!=0)
        return x<0? -1 : 1;
    else
        return 0;
}


void InBOOMCARDS(uint8_t x,uint8_t y,uint8_t x2,uint8_t y2,uint8_t Cadr,uint32_t ldx1,uint32_t ldx2,SDL_Surface *scr)
{

    card * tmp1=pole[x][y].crd;
    card * tmp2=pole[x2][y2].crd;

    int32_t dx=LXtoSX(x);
    int32_t dx2=LXtoSX(x2);
    int32_t dy=LYtoSY(y);
    int32_t dy2=LYtoSY(y2);
    int8_t  dparam=0;

    switch (Cadr)
    {
    case 0:
        dparam=0;
        break;
    case 1:
        dparam=1;
        break;
    case 2:
        dparam=2;
        break;
    case 3:
        dparam=3;
        break;
    case 4:
        dparam=5;
        break;
    case 5:
        dparam=9;
        break;
    case 6:
        dparam=7;
        break;
    case 7:
        dparam=5;
        break;
    case 8:
        dparam=3;
        break;
    case 9:
        dparam=2;
        break;
    case 10:
        dparam=1;
        break;
    case 11:
        dparam=0;
        break;
    }
    DrawCard2(tmp1,(pole[x][y].tip-1),(dx+(sgn(dx2-dx))*dparam),\
              (dy+(sgn(dy2-dy))*dparam),scr);
    DrawCard2(tmp2,(pole[x2][y2].tip-1),(dx2+(sgn(dx-dx2))*dparam),\
              (dy2+(sgn(dy-dy2))*dparam),scr);

    DrawOnCardsNumb(dx+(sgn(dx2-dx))*dparam,dy+(sgn(dy2-dy))*dparam,ldx1,scr);
    DrawOnCardsNumb(dx2+(sgn(dx-dx2))*dparam,dy2+(sgn(dy-dy2))*dparam,ldx2,scr);
}




void DrawSelect(SDL_Surface *scr)
{
    for (uint8_t i=1;i<=SkFight;i++)
    {

        DrawImage(Select_img,LXtoSX(KtoFight[i][0])+5,LYtoSY(KtoFight[i][1])+21,scr);

    }
}

uint8_t ViborPlayer(SDL_Surface * scr)
{
    bool Maya=false;
    uint8_t dx,dy;
    dx=KtoFight[1][0];
    dy=KtoFight[1][1];

    while (!Maya)
    {
        Global_Draw_Game_scrn(scr);
        DrawSelect(scr);

        if (input_GetState(Ki_DOWN))
        {
            dy++;
            SPU(sKlik2);
        }
        if (input_GetState(Ki_UP))
        {
            dy--;
            SPU(sKlik2);
        }
        if (input_GetState(Ki_LEFT))
        {
            dx--;
            SPU(sKlik2);
        }
        if (input_GetState(Ki_RIGHT))
        {
            dx++;
            SPU(sKlik2);
        }

        if (dx<1) dx=4;
        if (dx>4) dx=1;
        if (dy<1) dy=4;
        if (dy>4) dy=1;

        if (input_GetState(Ki_X))
            for (uint8_t i=1;i<=SkFight;i++)
                if (dx==KtoFight[i][0] && dy==KtoFight[i][1])
                {
                    return i;
                    Maya=true;
                    break;
                }


        Draw_Vibor_Grayed(scr);
        DrawStrelka(LXtoSX(dx)-12,LYtoSY(dy)+13,scr);
        SDL_Flip(scr);
    }
    return 0;
}


void Draw_Vibor_Grayed(SDL_Surface *scr)
{
    uint8_t Gr[5][5];
    memset(Gr,0,5*5);

    for (uint8_t y=1;y<5;y++)
        for (uint8_t x=1;x<5;x++)
        {
            if ((pole[x][y].tip==1) || (pole[x][y].tip==2))
                Gr[x][y]=1;

            for (uint8_t i=1;i<=SkFight;i++)
                if ((x==KtoFight[i][0]) && (y==KtoFight[i][1]))
                    Gr[x][y]=0;


            if (Gr[x][y]) DrawAImage(blk_crd_img,LXtoSX(x),LYtoSY(y),160,scr);

        }



}

uint8_t KKil[10][3];
uint8_t StrelList[8];

void clearStrelList()
{
    memset(StrelList,0,8);
}

void DrawStrelkus(uint8_t x, uint8_t y,SDL_Surface *scr)
{
    uint8_t podSS=0;
    for (uint8_t i=0;i<8;i++)
        if (StrelList[i]) podSS++;

    uint32_t mms;
    bool what=true;
    uint8_t mmd=0;
    mms=millisec();

    if (podSS>0)
        while (mmd<12)
        {
            Global_Draw_Game_scrn(scr);
            if (millisec()>(mms+45))
            {
                what=!what;
                mms=millisec();
                mmd++;
            }


            if (what)
            {
                if (StrelList[0])   DrawAnimImage(Arrows,x,y+1,0,scr);
                if (StrelList[1])   DrawAnimImage(Arrows,x+17,y,1,scr);
                if (StrelList[2])   DrawAnimImage(Arrows,x+34,y+1,2,scr);
                if (StrelList[3])   DrawAnimImage(Arrows,x+35,y+21,3,scr);
                if (StrelList[4])   DrawAnimImage(Arrows,x+34,y+44,4,scr);
                if (StrelList[5])   DrawAnimImage(Arrows,x+17,y+45,5,scr);
                if (StrelList[6])   DrawAnimImage(Arrows,x,y+44,6,scr);
                if (StrelList[7])   DrawAnimImage(Arrows,x-1,y+21,7,scr);
            }
            else
            {
                if (StrelList[0])   DrawAnimImage(whArrows,x,y+1,0,scr);
                if (StrelList[1])   DrawAnimImage(whArrows,x+17,y,1,scr);
                if (StrelList[2])   DrawAnimImage(whArrows,x+34,y+1,2,scr);
                if (StrelList[3])   DrawAnimImage(whArrows,x+35,y+21,3,scr);
                if (StrelList[4])   DrawAnimImage(whArrows,x+34,y+44,4,scr);
                if (StrelList[5])   DrawAnimImage(whArrows,x+17,y+45,5,scr);
                if (StrelList[6])   DrawAnimImage(whArrows,x,y+44,6,scr);
                if (StrelList[7])   DrawAnimImage(whArrows,x-1,y+21,7,scr);
            }
            SDL_Flip(scr);
        }

    memset(StrelList,0,8);
}


void addKKilList(uint8_t x,uint8_t y,uint8_t ind)
{
    KKil[0][0]++;
    KKil[KKil[0][0]] [0]=x;
    KKil[KKil[0][0]] [1]=y;
    KKil[KKil[0][0]] [2]=ind;
}

void delKilList()
{
    memset(KKil,0,10*3);
}

void DrawCARDasd(uint8_t x,uint8_t y,uint8_t i,uint8_t frame,SDL_Surface *scr)
{
    switch (i)
    {
    case 1:
        DrawImageARect(wht_crd_img,LXtoSX(x)+40.0-1.5*frame,LYtoSY(y)+49.0-1.821428572*frame,\
                       4,(53.0/28.0)*frame,255.0-frame*8,scr);

        DrawImageARect(wht_crd_img,LXtoSX(x)+40.0-1.5*frame,LYtoSY(y)+49.0-1.821428572*frame,\
                       (46.0/28.0)*frame,4,255.0-frame*8,scr);
        break;
    case 2:
        DrawImageARect(wht_crd_img,LXtoSX(x),LYtoSY(y)+49.0-1.82143*frame,\
                       42,4,255.0-frame*8,scr);
        break;
    case 3:
        DrawImageARect(wht_crd_img,LXtoSX(x)-4.0+1.5714*frame,LYtoSY(y)+49.0-1.821428572*frame,\
                       4,(53.0/28.0)*frame,255.0-frame*8,scr);
        DrawImageARect(wht_crd_img,LXtoSX(x),LYtoSY(y)+49.0-1.821428572*frame,\
                       (46.0/28.0)*frame,4,255.0-frame*8,scr);
        break;
    case 4:
        DrawImageARect(wht_crd_img,LXtoSX(x)-4.0+1.5714*frame,LYtoSY(y),\
                       4,51,255.0-frame*8,scr);
        break;
    case 5:
        DrawImageARect(wht_crd_img,LXtoSX(x)-4.0+1.5714*frame,LYtoSY(y),\
                       4,(53.0/28.0)*frame,255.0-frame*8,scr);

        DrawImageARect(wht_crd_img,LXtoSX(x),LYtoSY(y)-2.0+1.821428572*frame,\
                       (44.0/28.0)*frame,4,255.0-frame*8,scr);
        break;
    case 6:
        DrawImageARect(wht_crd_img,LXtoSX(x),LYtoSY(y)-2.0+1.82143*frame,\
                       42,4,255.0-frame*8,scr);
        break;
    case 7:
        DrawImageARect(wht_crd_img,LXtoSX(x)+40.0-1.5*frame,LYtoSY(y),\
                       4,(53.0/28.0)*frame,255.0-frame*8,scr);

        DrawImageARect(wht_crd_img,LXtoSX(x)+40.0-1.5*frame,LYtoSY(y)-2.0+1.821428572*frame,\
                       (46.0/28.0)*frame,4,255.0-frame*8,scr);
        break;
    case 8:
        DrawImageARect(wht_crd_img,LXtoSX(x)+40.0-1.5*frame,LYtoSY(y),\
                       4,51,255.0-frame*8,scr);
    }

}

void AllKilList(uint8_t HB,bool dRawC,SDL_Surface * scr)
{
    if (KKil[0][0]>0)
    {
        if (dRawC)
        {
            if (KKil[0][0]>0)
                SPU(sCombo);
        }
        else
        {
            if (KKil[0][0]==1)
                SPU(sDzin);
            else
                SPU(sCombo);

        }

        for (uint8_t i=0;i<=9;i++)
        {
            Global_Draw_Game_scrn(scr);
            for (uint8_t tmpcrd=1;tmpcrd<=KKil[0][0];tmpcrd++)
                if (dRawC || KKil[tmpcrd][2])
                    DrawCARDasd(KKil[tmpcrd][0],KKil[tmpcrd][1],KKil[tmpcrd][2],i,scr);
                else
                    DrawAImage(wht_crd_img,LXtoSX(KKil[tmpcrd][0]),LYtoSY(KKil[tmpcrd][1]),i*28,scr);

            if (dRawC) Draw_COMBOL(scr);
            SDL_Flip(scr);
#ifndef DINGOO
            SDL_Delay(5*fpsmul);
#endif
        }

        for (uint8_t i=1;i<=KKil[0][0];i++)
            pole[KKil[i][0]] [KKil[i][1]] .tip=HB;


        for (uint8_t i=10;i<=28;i++)
        {
            Global_Draw_Game_scrn(scr);
            for (uint8_t tmpcrd=1;tmpcrd<=KKil[0][0];tmpcrd++)
                if (dRawC || KKil[tmpcrd][2])
                    DrawCARDasd(KKil[tmpcrd][0],KKil[tmpcrd][1],KKil[tmpcrd][2],i,scr);
                else
                    DrawAImage(wht_crd_img,LXtoSX(KKil[tmpcrd][0]),LYtoSY(KKil[tmpcrd][1]),255-((i-10)*14),scr);

            if (dRawC) Draw_COMBOL(scr);
            SDL_Flip(scr);
#ifndef DINGOO
            SDL_Delay(5*fpsmul);
#endif
        }

    }
    delKilList();
}


uint8_t CPX,CPY,CPN;
void Combo_Podshet(uint8_t x,uint8_t y)
{
    uint8_t howmanY=0;

    for (uint8_t z=0;z<8;z++)
        switch (pole[x][y].tip)
        {
        case 1:
            if ((pole[x][y].crd->Arr >> z) & 1)
                if (pole[GetXFromIndex(x,y,z+1)] [GetYFromIndex(x,y,z+1)] .tip == 2)
                    howmanY++;
            break;
        case 2:
            if ((pole[x][y].crd->Arr >> z) & 1)
                if (pole[GetXFromIndex(x,y,z+1)] [GetYFromIndex(x,y,z+1)] .tip == 1)
                    howmanY++;
        }

    CPX=x;
    CPY=y;
    CPN=howmanY;
}

void Draw_COMBOL(SDL_Surface * scr)
{
    if  (CPN>0)
    {
        DrawImage(Combo,LXtoSX(CPX)+9,LYtoSY(CPY)+18,scr);
        DrawAnimImage(Combo_Numb,LXtoSX(CPX)-7,LYtoSY(CPY)+18,CPN+1,scr);
    }
}

void Kilnut(uint8_t x,uint8_t y,SDL_Surface * scr)
{
    Combo_Podshet(x,y);
    Draw_COMBOL(scr);
    clearStrelList();

    switch (pole[x][y].tip)
    {
    case 1:
        for (uint8_t i=0;i<8;i++)
            if ((pole[x][y].crd->Arr >> i ) & 1)
                if (pole[GetXFromIndex(x,y,i+1)][GetYFromIndex(x,y,i+1)].tip==2)
                {
                    addKKilList(GetXFromIndex(x,y,i+1),GetYFromIndex(x,y,i+1),i+1);
                    StrelList[i]=1;

                }
        DrawStrelkus(LXtoSX(x),LYtoSY(y),scr);
        AllKilList(1,1,scr);
        break;

    case 2:
        for (uint8_t i=0;i<8;i++)
            if ((pole[x][y].crd->Arr >> i )& 1)
                if (pole[GetXFromIndex(x,y,i+1)][GetYFromIndex(x,y,i+1)].tip==1)
                {
                    addKKilList(GetXFromIndex(x,y,i+1),GetYFromIndex(x,y,i+1),i+1);
                    StrelList[i]=1;
                }

        DrawStrelkus(LXtoSX(x),LYtoSY(y),scr);
        AllKilList(2,1,scr);

    }
    Global_Draw_Game_scrn(scr);
    SDL_Flip(scr);//flip2d()
    SDL_Delay(500);//*/
}






bool MayNext=true;
void GoFight(uint8_t x,uint8_t y,uint8_t Who,SDL_Surface * scr) //;Пошел на сражение.
{
    MayNext=true;

    uint8_t fp=SkFight;

    if (SkFight!=0)
        switch (Who)
        {
        case 1:
            for (uint8_t i=1;i<=fp;i++)
            {
                skolko(x,y);
                if (SkFight==0) break;
                if (SkFight>1) //Если есть варианты сражения более 1
                {
                    uint8_t tmp=ViborPlayer(scr);
                    if (Fight(x,y, KtoFight[tmp][0] , KtoFight[tmp][1] , scr) ==1)
                    {
                        Kilnut ( KtoFight[tmp][0] , KtoFight[tmp][1] ,scr );
                        DeleteSpisk(tmp);
                        skolko(x,y);
                    }
                    else
                    {
                        Kilnut(x,y,scr);
                        MayNext=false;
                        ClearObaSpiska();
                        break;
                    }
                }
                else
                {
                    if (SkFight==1)
                    {
                        if (Fight(x,y, KtoFight[1][0] , KtoFight[1][1] , scr)==1)
                        {
                            Kilnut( KtoFight[1][0] , KtoFight[1][1] ,scr );
                            skolko(x,y);
                        }
                        else
                        {
                            Kilnut(x,y,scr);
                            MayNext=false;
                            break;
                        }
                    }
                }
            }

            break;
        case 2:
            for (uint8_t i=1;i<=SkFight;i++)
            {
                if (pole [KtoFight[i][0]] [KtoFight[i][1]] .tip!=Who)
                {
                    if (Fight(x,y, KtoFight[i][0] , KtoFight[i][1] , scr)==1)
                        Kilnut(KtoFight[i][0],KtoFight[i][1],scr);
                    else
                    {
                        Kilnut(x,y,scr);
                        MayNext=false;
                        break;
                    }
                }
            }
        }



    if (MayNext)
    {
        if (SkOkup!=0)
        {
            for (uint8_t t=1;t<=SkOkup;t++)
            {
                if (pole [KtoOkup[t][0]] [KtoOkup[t][1]] .tip!=Who)
                {
                    addKKilList(KtoOkup[t][0],KtoOkup[t][1],0);
                }
            }
            AllKilList(Who,0,scr);
        }
    }


}


void DeleteSpisk(uint8_t i)
{
    if ((i+1)<=SkFight)
    {
        for (uint8_t ii=i;ii<=(SkFight-1);ii++)
        {
            KtoFight[ii][0]=KtoFight[ii+1][0];
            KtoFight[ii][1]=KtoFight[ii+1][1];
        }
        KtoFight[SkFight][0]=0;
        KtoFight[SkFight][1]=0;
        SkFight--;

    }
    else
    {
        SkFight--;
        KtoFight[i][0]=0;
        KtoFight[i][1]=0;
    }
}

uint32_t Boom_Tik=0;
uint8_t Boom_Cadr=0;
uint8_t DD_Cadr=0;
uint32_t DD_Tik=0;

void DrawBoom(uint32_t x,uint32_t y,SDL_Surface *scr)
{
    DrawAAnimImage(Boom_img,x-20,y-24,Boom_Cadr,175,scr);

    if (millisec()>Boom_Tik+62)
    {
        Boom_Tik=millisec();
        Boom_Cadr++;
    }

}//;Рисуем Взрыв



void ToWhite(uint32_t x,uint32_t y,SDL_Surface *scr)
{
    uint8_t dss=rand() & 1;
    for ( uint8_t i=1; i<=15;i++)
    {
        if ((i % 5)==1) dss=1-dss;
        Global_Draw_Game_scrn(scr);
        if (dss==0)
            DrawAImage(wht_crd_img,x,y,150,scr);
        else
            DrawAImage(wht_crd_img,x,y,80,scr);

        SDL_Flip(scr);//Flip2D()
#ifdef DINGOO
        SDL_Delay(5);
#else
        SDL_Delay(1000/60);
#endif
    }
} //Карту в белый

void ToWhite2(uint32_t x,uint32_t y,SDL_Surface *scr)
{
    for (uint8_t i=0;i<=255;i+=30)
    {
        Global_Draw_Game_scrn(scr);
        Draw_COMBOL(scr);
        DrawAImage(wht_crd_img,x,y,i,scr);
        SDL_Flip(scr);
    }
}// ; Карту в белый

void FromWhite(uint32_t x,uint32_t y,SDL_Surface *scr)
{
    uint8_t dss=rand() & 1;
    for ( uint8_t i=1; i<=15;i++)
    {
        if ((i % 5)==1) dss=1-dss;
        Global_Draw_Game_scrn(scr);
        if (dss==0)
            DrawAImage(wht_crd_img,x,y,150,scr);
        else
            DrawAImage(wht_crd_img,x,y,80,scr);

        SDL_Flip(scr);//Flip2D()
#ifdef DINGOO
        SDL_Delay(5);
#else
        SDL_Delay(1000/60);
#endif
    }
}// ;Карту из белого

void FromWhite2(uint32_t x,uint32_t y,SDL_Surface *scr)
{
    for (uint8_t i=255;i>0;i-=30)
    {
        Global_Draw_Game_scrn(scr);
        Draw_COMBOL(scr);
        DrawAImage(wht_crd_img,x,y,i,scr);
        SDL_Flip(scr);
    }
}//;Карту из белого


uint8_t Fight(uint32_t x,uint32_t  y,uint8_t x2,uint8_t y2,SDL_Surface * scr) //;Само сражение
{

    bool win,lose;
    win=false;
    lose=false;


    card *temp = pole[x][y].crd;
    card *temp2= pole[x2][y2].crd;

    uint8_t Part_1_X1=0,Part_1_X2=0;
//;#Region Первая часть боя
    uint8_t TempMax,TempMin;

    if (temp->Atype==aT_A)
    {
        TempMax=temp->Attack;
        if (TempMax<temp->PDefence) TempMax=temp->PDefence;
        if (TempMax<temp->MDefence) TempMax=temp->MDefence;
        Part_1_X1=TempMax*16 + rand()%16;
    }
    else
        Part_1_X1= temp->Attack*16 + rand()%16;


    switch (temp->Atype)
    {
    case aT_P:
        Part_1_X2=temp2->PDefence*16+rand()%16;  // Rand(LetterToNumber(pdef2$)*16,((LetterToNumber(pdef2$)+1)*16)-1)
        break;
    case aT_M:
        Part_1_X2=temp2->MDefence*16+rand()%16; //Part_1_X2=Rand(LetterToNumber(mdef2$)*16,((LetterToNumber(mdef2$)+1)*16)-1)
        break;
    case aT_X:
        TempMin=temp2->MDefence;
        if (TempMin>temp2->PDefence) TempMin=temp2->PDefence;
        Part_1_X2=TempMin*16 + rand()%16;
        break;
    case aT_A:
        TempMin=temp2->Attack;
        if (TempMin>temp2->PDefence) TempMin=temp2->PDefence;
        if (TempMin>temp2->MDefence) TempMin=temp2->MDefence;
        Part_1_X2=TempMin*16 + rand()%16;
    }

//;#End Region

    Global_Draw_Game_scrn(scr);

    DrawOnCardsNumb(LXtoSX(x),LYtoSY(y),Part_1_X1,scr);
    DrawOnCardsNumb(LXtoSX(x2),LYtoSY(y2),Part_1_X2,scr);
    SDL_Flip(scr);
    SDL_Delay(500);

//;#Region Рисуем Boom
    Boom_Cadr=0;
    SPU(sBoom);
    DD_Cadr=0;
    DD_Tik=millisec();
    Boom_Tik=millisec();
    NotDraw[0][0]=x;
    NotDraw[0][1]=y;
    NotDraw[1][0]=x2;
    NotDraw[1][1]=y2;

    while (Boom_Cadr<8)
    {
        Global_Draw_Game_scrn(scr);

        if (Boom_Cadr>=1)
            if (millisec()>=DD_Tik+12)
            {
                DD_Tik=millisec();
                DD_Cadr++;
            }

        if (DD_Cadr>11) DD_Cadr=11;
        InBOOMCARDS(x,y,x2,y2,DD_Cadr,Part_1_X1,Part_1_X2,scr);
        DrawBoom(((LXtoSX(x)+21)+(LXtoSX(x2)+21))/2,((LYtoSY(y)+25)+(LYtoSY(y2)+25))/2,scr);
        SDL_Flip(scr);
    }

    memset(NotDraw,0,4);
//END OF PART1

    uint8_t Part_2_X1,Part_2_X2;

//;#Region Вторая часть боя
    Part_2_X1=rand() % (Part_1_X1+1);
    Part_2_X2=rand() % (Part_1_X2+1);
    if (Part_2_X2==Part_2_X1) Part_2_X2++;

    float SD1,SD2;
    SD1=(Part_1_X1-Part_2_X1)/500.0f;
    SD2=(Part_1_X2-Part_2_X2)/500.0f;

    uint32_t timer_local=millisec()+500;
    while (millisec()<timer_local)
    {
        uint32_t local_time=500-(timer_local-millisec());
        Global_Draw_Game_scrn(scr);
        DrawOnCardsNumb(LXtoSX(x),LYtoSY(y),(Part_1_X1-(SD1*local_time)),scr);
        DrawOnCardsNumb(LXtoSX(x2),LYtoSY(y2),(Part_1_X2-(SD2*local_time)),scr);
        SDL_Flip(scr);
    } //;Проматываем
//END PART2

    Global_Draw_Game_scrn(scr);
    DrawOnCardsNumb(LXtoSX(x),LYtoSY(y),Part_2_X1,scr);
    DrawOnCardsNumb(LXtoSX(x2),LYtoSY(y2),Part_2_X2,scr);
    SDL_Flip(scr);
    SDL_Delay(400);

    if (Part_2_X1>Part_2_X2)
    {
        ToWhite(LXtoSX(x2),LYtoSY(y2),scr);
        pole[x2][y2].tip=pole[x][y].tip;
        SPU(sDzin);
        FromWhite(LXtoSX(x2),LYtoSY(y2),scr);
        return 1;
    }
    else
    {
        ToWhite(LXtoSX(x),LYtoSY(y),scr);
        pole[x][y].tip=pole[x2][y2].tip;
        SPU(sDzin);
        FromWhite(LXtoSX(x),LYtoSY(y),scr);
        return 0;
    }
}

void DrawOnCardsNumb(uint8_t x,uint8_t y,uint8_t Numb,SDL_Surface *scr) //;Рисуем числа на картах(атака или защита)
{
    char pss[5];
    memset(pss,0,5);
    sprintf(pss,"%d",Numb);

    uint8_t L=strlen(pss);
    switch (L)
    {
    case 1:
        DrawAnimImage(Card_ANumb,x+16,y+18,(uint8_t)pss[0]-0x30,scr);
        break;
    case 2:
        DrawAnimImage(Card_ANumb,x+11,y+18,(uint8_t)pss[0]-0x30,scr);
        DrawAnimImage(Card_ANumb,x+22,y+18,(uint8_t)pss[1]-0x30,scr);
        break;
    case 3:
        DrawAnimImage(Card_ANumb,x+6,y+18,(uint8_t)pss[0]-0x30,scr);
        DrawAnimImage(Card_ANumb,x+17,y+18,(uint8_t)pss[1]-0x30,scr);
        DrawAnimImage(Card_ANumb,x+28,y+18,(uint8_t)pss[2]-0x30,scr);
        break;
    }
}



void skolko(uint8_t x,uint8_t y)
{
    ClearObaSpiska();

    for (uint8_t i=1;i<9;i++)
    {
        uint8_t dx=GetXFromIndex(x,y,i);
        uint8_t dy=GetYFromIndex(x,y,i);
        uint8_t t_tp=pole[dx][dy].tip;
        if ((pole[x][y].crd->Arr >> (i-1)) & 1)
            if ((t_tp!=pole[x][y].tip) && ((t_tp==1) || (t_tp==2)))
            {
                if ((pole[dx][dy].crd->Arr >> (InvertIndex(i)-1)) & 1)
                {
                    SkFight++;
                    KtoFight[SkFight][0]=dx;
                    KtoFight[SkFight][1]=dy;
                }
                else
                {
                    SkOkup++;
                    KtoOkup[SkOkup][0]=dx;
                    KtoOkup[SkOkup][1]=dy;
                }
            }
    }
}





void DeletePlayerCard(card * crd)
{
    for (uint32_t i=0; i<playercards.size();i++)
        if (playercards[i]==crd)
        {
            playercards.erase(playercards.begin()+i);
            break;
        }
}


crd_end_pl eEndCards[5];
crd_end_pl pEndCards[5];

int16_t fpmP[5][2];
int16_t fpmE[5][2];


void FindInMassIV()
{


    for (uint8_t i=0;i<5;i++)
    {
        bool lfixed=false;

        for (uint8_t y=1;y<5;y++)
        {
            for (uint8_t x=1;x<5;x++)
            {
                if (pole[x][y].crd==EnemyCards[i].crd)
                {
                    eEndCards[i].crd=pole[x][y].crd;
                    eEndCards[i].cl=pole[x][y].tip;
                    fpmE[i][0]=LXtoSX(x);
                    fpmE[i][1]=LYtoSY(y);
                    lfixed=true;
                    break;
                }

            }
            if (lfixed)
                break;
        }
    }


    for (uint8_t i=0;i<5;i++)
    {
        bool lfixed=false;

        for (uint8_t y=1;y<5;y++)
        {
            for (uint8_t x=1;x<5;x++)
            {
                if (pole[x][y].crd==MyCards[i].crd)
                {
                    pEndCards[i].crd=pole[x][y].crd;
                    pEndCards[i].cl=pole[x][y].tip;
                    fpmP[i][0]=LXtoSX(x);
                    fpmP[i][1]=LYtoSY(y);
                    lfixed=true;
                    break;
                }

            }
            if (lfixed)
                break;
        }
    }

}



uint8_t attonumber(uint8_t typ)
{
    if (typ==aT_A)
        return 3;
    if (typ==aT_X)
        return 2;

    return 1;
}

void Prokachka(card *crd)
{
    if (crd->Expirience>((crd->Attack-defAtack[crd->Number])*200+500))
    {
        crd->Expirience=0;
        if (crd->Attack!=15)
        {
            crd->Attack++;

            if (rand() % 3 == 1)
            {
                if (rand() & 1 == 1)
                {
                    if (crd->MDefence!=15)
                        crd->MDefence++;
                    else if (crd->PDefence<15)
                        crd->PDefence++;
                }
                else
                {
                    if (crd->PDefence!=15)
                        crd->PDefence++;
                    else if (crd->MDefence<15)
                        crd->MDefence++;
                }
            }
        }
        else
        {
            if (rand() & 1 == 1)
            {
                if (crd->MDefence!=15)
                    crd->MDefence++;
                else if (crd->PDefence<15)
                    crd->PDefence++;
            }
            else
            {
                if (crd->PDefence!=15)
                    crd->PDefence++;
                else if (crd->MDefence<15)
                    crd->MDefence++;
            }
        }
    }


    if (crd->Atype==aT_X)
        if (rand() % 100 == 0)
            crd->Atype=aT_A;
    if (crd->Atype == aT_M || crd->Atype == aT_P)
        if (rand() % 100 < 3)
            crd->Atype=aT_X;


}


void Finalize_Game(SDL_Surface *scr)
{
    memset(eEndCards,0,5*sizeof(crd_end_pl));
    memset(pEndCards,0,5*sizeof(crd_end_pl));


    FindInMassIV();

    FinPereMesh(scr);
    SDL_Delay(20);
    DrawEPERem(scr);
    SDL_Delay(100);


    bool End_End_Game=false;
    int8_t ssslot=0;
    uint8_t ending_Game_scrn=0;

    if (InGameBlue==10)
        ending_Game_scrn=2;

    if (InGameRed==10)
        ending_Game_scrn=3;


    if ((InGameRed>InGameBlue) && (InGameRed!=10))
        ending_Game_scrn=0;


    if ((InGameBlue>InGameRed) && (InGameBlue!=10))
    {
        ending_Game_scrn=1;
        for (uint8_t i=0;i<5;i++)
            if (eEndCards[i].cl==1)
            {
                ssslot=i;
                break;
            }
    }

    if (InGameBlue==InGameRed)
        ending_Game_scrn=4;



    card *temp2;
    card *temp;
    card *tempaddr;

    int8_t sil;
    int8_t sselslot;
    int8_t sselslot2;


    ExSelect();

    switch (ending_Game_scrn)
    {
    case 0:
        for (uint8_t i=0;i<5;i++)
            AddCardToEnemy(WhoNow,eEndCards[i].crd);


        sil=-1;
        for (uint8_t i=0;i<5;i++)                                                                   ////Find best card of player
            if (pEndCards[i].cl==2)
            {
                temp=pEndCards[i].crd;
                if (sil<(temp->Attack+temp->PDefence+temp->MDefence + attonumber(temp->Atype)*3))
                {
                    sil=temp->Attack+temp->PDefence+temp->MDefence + attonumber(temp->Atype)*3;
                    sselslot=i;
                }
            }

        temp=pEndCards[sselslot].crd;

        if (EnemiesNumCards[WhoNow]==30)                                                            ////Find weaknes card of enemy
        {
            temp2=EnemiesCards[WhoNow][0];
            sil= temp2->Attack + temp2->PDefence + temp2->MDefence + attonumber(temp2->Atype)*3;
            sselslot2=1;
            for (uint8_t i=1;i<30;i++)
            {
                temp2=EnemiesCards[WhoNow][i];
                if (sil>(temp2->Attack + temp2->PDefence + temp2->MDefence + attonumber(temp2->Atype)*3))
                {
                    sil=temp2->Attack + temp2->PDefence + temp2->MDefence + attonumber(temp2->Atype)*3;
                    sselslot2=i;
                }
            }

            temp2=EnemiesCards[WhoNow][sselslot2];

            if ((temp->Attack + temp->PDefence + temp->MDefence + attonumber(temp->Atype)*3) >\
                    (temp2->Attack + temp2->PDefence + temp2->MDefence + attonumber(temp2->Atype)*3))
            {
                delete temp2;
                EnemiesCards[WhoNow][sselslot2]=NULL;
                enemy_ssortirovka(WhoNow);
                enemy_spodshet(WhoNow);
            }
        }

        for (uint8_t i=0;i<5;i++)
        {
            temp2=eEndCards[i].crd;
            temp2->Expirience+=100;
            Prokachka(temp2);
        }

        FromPlayer(sselslot,false,scr);

        break;

    case 1:

        while (!End_End_Game)
        {
            DrawBkg(BKG_MENU,scr);
            tempaddr=eEndCards[ssslot].crd;
            eEndCards[ssslot].crd=NULL;                   ////Make it for drawning slided card
            DrawEndCards(scr);
            eEndCards[ssslot].crd=tempaddr;

            temp2=eEndCards[ssslot].crd;
            DrawCard2(temp2,eEndCards[ssslot].cl-1,20,25+ssslot*33,scr);

            uint8_t Dx=temp2->Number % 10;
            uint8_t Dy=temp2->Number / 10;

            DrawiStrelka(53,ssslot*33+43,scr);

            sprintf(s_buf,GetLangString(24),nCardGrid[Dx][Dy]);   //Всего: %d
            CreateWindowText(58,ssslot*33+30,s_buf,scr);// Всего :

            if (input_GetState(Ki_UP))
            {
                SPU(sKlik2);
                for (uint8_t zzz=0; zzz<6; zzz++)
                {
                    ssslot--;
                    if (ssslot<0)
                        ssslot=4;
                    if (eEndCards[ssslot].cl==1)
                        break;
                }
            }
            if (input_GetState(Ki_DOWN))
            {
                SPU(sKlik2);
                for (uint8_t zzz=0; zzz<6; zzz++)
                {
                    ssslot++;
                    if (ssslot>4)
                        ssslot=0;
                    if (eEndCards[ssslot].cl==1)
                        break;
                }
            }

            if (input_GetState(Ki_X))
            {
                SPU(sChif);
                End_End_Game=true;
                FromEnemy(ssslot,false,scr);
            }

            SDL_Flip(scr);
        }
        for (uint8_t i=0;i<5;i++)
            if (eEndCards[i].crd)
                AddCardToEnemy(WhoNow,eEndCards[i].crd);

        for (uint8_t i=0;i<5;i++)
        {
            temp=pEndCards[i].crd;
            temp->Expirience+=100;
            Prokachka(temp);
        }
        break;





    case 2:                     //Player wins with 10 cards
        for (uint8_t i=0;i<5;i++)
            FromEnemy(i,true,scr);

        for (uint8_t i=0;i<5;i++)
        {
            temp=pEndCards[i].crd;
            temp->Expirience+=250;
            Prokachka(temp);
        }
        break;


    case 3:                     //Player wins with 10 cards

        for (uint8_t i=0;i<5;i++)
            AddCardToEnemy(WhoNow,eEndCards[i].crd);

        for (uint8_t ii=0;ii<5;ii++)
        {
            temp=pEndCards[ii].crd;

            if (EnemiesNumCards[WhoNow]==30)                                                            ////Find weaknes card of enemy
            {
                temp2=EnemiesCards[WhoNow][0];
                sil= temp2->Attack + temp2->PDefence + temp2->MDefence + attonumber(temp2->Atype)*3;
                sselslot2=1;
                for (uint8_t i=1;i<30;i++)
                {
                    temp2=EnemiesCards[WhoNow][i];
                    if (sil>(temp2->Attack + temp2->PDefence + temp2->MDefence + attonumber(temp2->Atype)*3))
                    {
                        sil=temp2->Attack + temp2->PDefence + temp2->MDefence + attonumber(temp2->Atype)*3;
                        sselslot2=i;
                    }
                }

                temp2=EnemiesCards[WhoNow][sselslot2];

                if ((temp->Attack + temp->PDefence + temp->MDefence + attonumber(temp->Atype)*3) >\
                        (temp2->Attack + temp2->PDefence + temp2->MDefence + attonumber(temp2->Atype)*3))
                {
                    delete temp2;
                    EnemiesCards[WhoNow][sselslot2]=NULL;
                    enemy_ssortirovka(WhoNow);
                    enemy_spodshet(WhoNow);
                }
            }

            FromPlayer(ii,true,scr);
        }

        for (uint8_t i=0;i<5;i++)
        {
            temp2=eEndCards[i].crd;
            temp2->Expirience+=250;
            Prokachka(temp2);
        }
        break;



    case 4:
        for (uint8_t i=0;i<5;i++)
            AddCardToEnemy(WhoNow,eEndCards[i].crd);

        for (uint8_t i=0;i<5;i++)
        {
            temp=eEndCards[i].crd;
            temp->Expirience+=50;
            Prokachka(temp);

            temp=pEndCards[i].crd;
            temp->Expirience+=50;
            Prokachka(temp);
        }
    }

}


void DrawEPERem(SDL_Surface *scr)
{

    for (uint8_t i=0;i<19;i++)
    {
        DrawBkg(BKG_MENU,scr);
        for (uint8_t j=0;j<5;j++)
        {
            if (eEndCards[j].crd)
                DrawCard2(eEndCards[j].crd,eEndCards[j].cl-1,16+((fpmE[j][0]-16)/18.0)*(18.0-i),(25+j*33)+((fpmE[j][1]-(25+j*33))/18.0)*(18.0-i),scr);

            if (pEndCards[j].crd)
                DrawCard2(pEndCards[j].crd,pEndCards[j].cl-1,260+((fpmP[j][0]-260)/18.0)*(18.0-i),(25+j*33)+((fpmP[j][1]-(25+j*33))/18.0)*(18.0-i),scr);
        }
        SDL_Flip(scr);
        #ifdef DINGOO
        SDL_Delay(10);
        #else
        SDL_Delay(1000/50);
        #endif
    }

}

void DrawEndCards(SDL_Surface *scr)
{
    for (uint8_t i=0;i<5;i++)
    {
        if (eEndCards[i].crd)
            DrawCard2(eEndCards[i].crd,eEndCards[i].cl-1,16,25+i*33,scr);

        if (pEndCards[i].crd)
            DrawCard2(pEndCards[i].crd,pEndCards[i].cl-1,260,25+i*33,scr);
    }
}

void FinPereMesh(SDL_Surface *scr)
{
    DrawBkg(BKG_MENU,scr);
    for (uint8_t dy=1;dy<5;dy++)
        for (uint8_t dx=1;dx<5;dx++)
            if (pole[dx][dy].crd)
                DrawCard2(pole[dx][dy].crd,pole[dx][dy].tip-1,LXtoSX(dx),LYtoSY(dy),scr);

    SDL_Flip(scr);
}

void DrawPereRash(uint8_t Slot, uint8_t Who, SDL_Surface *scr)
{
    for (uint16_t j=0;j<255;j+=30)
    {
        DrawBkg(BKG_MENU,scr);

        for (uint8_t i=0; i<5;i++)
        {
            if (eEndCards[i].crd)
            {

                DrawCard2(eEndCards[i].crd,eEndCards[i].cl-1,16,25+i*33,scr);
                if (eEndCards[i].cl==1)
                {
                    if (Slot!=i)
                        DrawAImage(wht_crd_img,16,25+i*33,j,scr);
                    else if (Who==1)
                        DrawAImage(wht_crd_img,16,25+i*33,j,scr);
                }
            }
            if (pEndCards[i].crd)
            {
                DrawCard2(pEndCards[i].crd,pEndCards[i].cl-1,260,25+i*33,scr);
                if (pEndCards[i].cl==2)
                {
                    if (Slot!=i)
                        DrawAImage(wht_crd_img,260,25+i*33,j,scr);
                    else if (Who==0)
                        DrawAImage(wht_crd_img,260,25+i*33,j,scr);
                }
            }
        }
        SDL_Flip(scr);
#ifndef DINGOO
        SDL_Delay(10);
#endif
    }



    for (int16_t j=255;j>0;j-=30)
    {
        DrawBkg(BKG_MENU,scr);
        for (uint8_t i=0; i<5;i++)
        {
            if (eEndCards[i].crd)
            {
                if (Slot!=i)
                    DrawCard2(eEndCards[i].crd,1,16,25+i*33,scr);
                else if (Who==0)
                    DrawCard2(eEndCards[i].crd,0,16,25+i*33,scr);
                else if (Who==1)
                    DrawCard2(eEndCards[i].crd,1,16,25+i*33,scr);



                if (eEndCards[i].cl==1)
                {
                    if (Slot!=i)
                        DrawAImage(wht_crd_img,16,25+i*33,j,scr);
                    else if (Who==1)
                        DrawAImage(wht_crd_img,16,25+i*33,j,scr);
                }
            }

            if (pEndCards[i].crd)
            {
                if (Slot!=i)
                    DrawCard2(pEndCards[i].crd,0,260,25+i*33,scr);
                else if (Who==1)
                    DrawCard2(pEndCards[i].crd,1,260,25+i*33,scr);
                else if (Who==0)
                    DrawCard2(pEndCards[i].crd,0,260,25+i*33,scr);

                if (pEndCards[i].cl==2)
                {
                    if (Slot!=i)
                        DrawAImage(wht_crd_img,260,25+i*33,j,scr);
                    else if (Who==0)
                        DrawAImage(wht_crd_img,260,25+i*33,j,scr);
                }
            }
        }
        SDL_Flip(scr);
#ifndef DINGOO
        SDL_Delay(10);
#endif
    }

    for (uint8_t i=0; i<5;i++)
    {
        if (Slot!=i)
        {
            eEndCards[i].cl=2;
            pEndCards[i].cl=1;
        }
        else if (Who==0)
            pEndCards[i].cl=1;
        else if (Who==1)
            eEndCards[i].cl=2;
    }

}



void FromEnemy(uint8_t slot,bool vse,SDL_Surface *scr)
{
    DrawBkg(BKG_MENU,scr);
    DrawEndCards(scr);
    SDL_Flip(scr);

    if (vse)
        SDL_Delay(500);
    else
        SDL_Delay(100);


    card *temp;
    float koef,y,xx;

    if (!vse)
        DrawPereRash(slot,0,scr);


    temp=eEndCards[slot].crd;
    eEndCards[slot].crd=NULL;
    koef=(95.0-(25.0+slot*33.0))/10.0;
    y=25.0+slot*33.0;

    xx=16.0;


    for (uint8_t x=1;x<12;x++)
    {
        DrawBkg(BKG_MENU,scr);
        DrawEndCards(scr);
        DrawCard2(temp,0,xx,y,scr);
        y+=koef;
        xx+=12.3;
        SDL_Flip(scr);
        SDL_Delay(10);
    }


    uint8_t Dx,Dy;
    bool lllexit=false;
    SPU(sChif);
    while (!lllexit)
    {
        DrawBkg(BKG_MENU,scr);
        DrawEndCards(scr);
        DrawCard2(temp,0,139,95,scr);



        if (input_GetState(Ki_X) || input_GetState(Ki_O) || input_GetState(Ki_D))
            lllexit=true;

        sprintf(s_buf,GetLangString(23),cardName[temp->Number]);  //Получено %s

        CreateWindowText(160-(GetFFWidth(s_buf)+10)/2,200,s_buf,scr);

        Dx=temp->Number % 10;
        Dy=temp->Number / 10;


        uint8_t ff=nCardGrid[Dx][Dy];

        if (ff==0)
            DrawImage(NewCard,166,77,scr);


        SDL_Flip(scr);
    }


    xx=139;
    for (uint8_t x=1;x<12;x++)
    {
        DrawBkg(BKG_MENU,scr);
        DrawCard2(temp,0,xx,95,scr);
        xx+=12.1;
        DrawEndCards(scr);
        SDL_Flip(scr);
        SDL_Delay(10);
    }

    AddCardToPlayer2(temp);
//Delete temp


    DrawBkg(BKG_MENU,scr);
    DrawEndCards(scr);
    SDL_Flip(scr);

    if (vse)
        SDL_Delay(500);
    else
        SDL_Delay(100);

}



void AddCardToPlayer2(card *crd)
{
    uint8_t Dx,Dy;
    Dx=crd->Number % 10;
    Dy=crd->Number / 10;

    if (nCardGrid[Dx][Dy]<50)
    {
        nCardGrid[Dx][Dy]++;
        playercards.push_back(crd);


    }
    else
    {
        vPlayer.Pl_v_Gil+=Price2(crd);
        delete  crd;
    }
}




void FromPlayer(uint8_t slot,bool vse,SDL_Surface *scr)
{
    DrawBkg(BKG_MENU,scr);
    DrawEndCards(scr);
    SDL_Flip(scr);

    if (vse)
        SDL_Delay(500);
    else
        SDL_Delay(100);

    card *temp;
    float koef,y,xx;

    if (!vse)
        DrawPereRash(slot,1,scr);

    temp=pEndCards[slot].crd;
    pEndCards[slot].crd=NULL;
    koef=(95.0-(25.0+slot*33.0))/10.0;
    y=25+slot*33;
    xx=260;




    for (uint8_t x=1;x<12;x++)
    {
        DrawBkg(BKG_MENU,scr);
        DrawEndCards(scr);
        DrawCard2(temp,1,xx,y,scr);
        y+=koef;
        xx-=12.1;
        SDL_Flip(scr);
        SDL_Delay(10);
    }


    DrawBkg(BKG_MENU,scr);
    DrawEndCards(scr);
    DrawCard2(temp,1,139,95,scr);

    uint8_t Dx,Dy;
    Dx=temp->Number % 10;
    Dy=temp->Number / 10;


    uint8_t ff=nCardGrid[Dx][Dy];

    if (ff==1)
        DrawImage(LastCard,166,77,scr);

    SDL_Flip(scr);

    nCardGrid[Dx][Dy]--;

    if (vse)
        SDL_Delay(500);
    else
        SDL_Delay(1500);


    SPU(sChif);
    xx=139;
    for (uint8_t x=1;x<12;x++)
    {
        DrawBkg(BKG_MENU,scr);
        DrawCard2(temp,1,xx,95,scr);
        DrawEndCards(scr);
        xx-=12.3;
        SDL_Flip(scr);
        SDL_Delay(10);
    }

    AddCardToEnemy(WhoNow,temp);
    DeletePlayerCard(temp);

    DrawBkg(BKG_MENU,scr);
    DrawEndCards(scr);
    SDL_Flip(scr);

    if (vse)
        SDL_Delay(100);
    else
        SDL_Delay(500);


}

