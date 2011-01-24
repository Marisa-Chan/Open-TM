#include "res.h"

card * CardGrid[10][10][50];
uint32_t nCardGrid[10][10];

bool Select_Exit=false;

uint32_t v_HMCardsType;
uint32_t v_HMCards;


void ExSelect()
{
    memset(CardGrid,0,10*10*50*(sizeof(card *)));
    memset(nCardGrid,0,10*10*(sizeof(uint32_t)));

    uint8_t Dx;
    uint8_t Dy;

    for (uint32_t i=0;i<playercards.size();i++)
    {
        Dx=selGetX(playercards[i]->Number);
        Dy=selGetY(playercards[i]->Number);
        CardGrid [Dx] [Dy] [ nCardGrid[Dx][Dy] ]=playercards[i];
        nCardGrid[Dx] [Dy] ++;
    }
}



void HowManyCards()
{
    v_HMCards=playercards.size();
}

void HowManyCardType()
{
    HowManyCards();
    ExSelect();
    uint32_t temp=0;
    for (uint8_t i=0;i<=9;i++)
        for (uint8_t ii=0;ii<=9;ii++)
            if (nCardGrid[ii][i])  temp++;
    v_HMCardsType=temp;
}

uint8_t selGetX(uint8_t Number)
{
    return Number % 10;
}

uint8_t selGetY(uint8_t Number)
{

    return Number>9 ? Number/10 : 0;
}

void SelScr_Add(card * crd)
{
    uint8_t Dx=selGetX(crd->Number);
    uint8_t Dy=selGetY(crd->Number);
    CardGrid[Dx] [Dy] [nCardGrid[Dx][Dy]]=crd;
    nCardGrid[Dx][Dy]++;
}

void SelScr_Delete(uint8_t X,uint8_t Y,uint8_t Sel)
{
    if (nCardGrid[X][Y]==1)
    {
        nCardGrid[X][Y]=0;
        CardGrid[X][Y][0]=NULL;
    }
    else if (nCardGrid[X][Y]>1)
    {
        if (Sel==nCardGrid[X][Y])
        {
            CardGrid[X][Y][Sel]=NULL;
            nCardGrid[X][Y]--;
        }
        else
        {
            for (uint8_t i=Sel;i<nCardGrid[X][Y]-1;i++)
                CardGrid[X][Y][i]=CardGrid[X][Y][i+1];

            CardGrid[X][Y][nCardGrid[X][Y]-1]=NULL;
            nCardGrid[X][Y]--;
        }
    }
}



uint32_t YToSelY2(uint32_t y)
{
    return (48+y*15);
}


uint32_t XToSelX2(uint32_t x)
{
    return (12+x*15);
}

uint32_t YToSelY(uint32_t y)
{
    return (45+y*15);
}

uint32_t XToSelX(uint32_t x)
{
    return (18+x*15);
}

void SelScr_PlayerDelSpisk()
{
    memset(MyCards,0,5*sizeof(crd_pl));
}

void ScreenSelectCard(SDL_Surface * scr)
{
    Select_Exit=false;
    FlushCards();
    SelScr_PlayerDelSpisk();


    uint8_t SDX=0;
    uint8_t SDY=0;
    uint8_t SDS=0;
    card * temp;
    ExSelect();
    int8_t SDSEL=0;
    HowManyCards();
    HowManyCardType();



    while (!Select_Exit)
    {
        DrawBkg(BKG_SEL,scr);

        if (input_GetState(Ki_O))
        {
            SDSEL--;
            SPU(sOtmen);
            if (SDSEL>=0)
            {
                temp=MyCards[SDSEL].crd;
                SelScr_Add(MyCards[SDSEL].crd);
                MyCards[SDSEL].crd=NULL;
            }
        }

        if (input_GetState(Ki_X))
            if (nCardGrid[SDX][SDY]!=0)
            {
                {
                    MyCards[SDSEL].crd=CardGrid[SDX][SDY][SDS];
                    SelScr_Delete(SDX,SDY,SDS);
                    SDSEL++;
                    SPU(sChif);
                    if (SDS>0)
                        SDS--;
                }
            }

        if (input_GetState(Ki_UP))
        {
            if (SDX==0) SDX=10;
            SDX--;
            SPU(sKlik2);
            SDS=0;
        }

        if (input_GetState(Ki_DOWN))
        {
            SDX++;
            SPU(sKlik2);
            if (SDX>9) SDX=0;
            SDS=0;
        }

        if (input_GetState(Ki_LEFT))
        {
            if (SDY==0) SDY=10;
            SDY--;
            SPU(sKlik2);
            SDS=0;
        }

        if (input_GetState(Ki_RIGHT))
        {
            SDY++;
            SPU(sKlik2);
            if (SDY>9) SDY=0;
            SDS=0;
        }


        if (SDSEL<0)
        {
            Select_Exit=true;
            NextScreen(scrMain);
        }


        sprintf(s_buf,"%d",v_HMCards);
        TextFF(70,202,s_buf,scr);
        sprintf(s_buf,"%d",v_HMCardsType);
        TextFF(138,202,s_buf,scr);
        sprintf(s_buf,"%d",vPlayer.Pl_winWIn);
        TextFF(245-GetFFWidth(s_buf),66,s_buf,scr);
        sprintf(s_buf,"%d",vPlayer.Pl_winLose);
        TextFF(245-GetFFWidth(s_buf),76,s_buf,scr);
        sprintf(s_buf,"%d",vPlayer.Pl_winBoth);
        TextFF(245-GetFFWidth(s_buf),86,s_buf,scr);

        DrawCrdPlot(scr);

        DrawHand(XToSelX(SDY)-14,YToSelY(SDX)+2,scr);



        if (nCardGrid[SDX][SDY]>0)
        {
            temp=CardGrid[SDX][SDY][SDS];
            if (nCardGrid[SDX][SDY]>1)
            {
                uint8_t jkl=nCardGrid[SDX][SDY];
                if (jkl>5)
                    jkl=5;
                jkl--;
                for (uint8_t lkj=jkl;lkj>0;lkj--)
                {
                    DrawImage(blRobe,194+lkj*4,129+lkj,scr);
                    DrawImage(Card_imgs[temp->Number],194+lkj*4,129+lkj,scr);
                    DrawAImage(blk_crd_img,194+lkj*4,129+lkj,50+lkj*40,scr);
                }
            }
            DrawCard2(temp,0,194,129,scr);
            sprintf(s_buf,"No%d",temp->Number+1);
            TextFF(216-GetFFWidth(s_buf)/2,118,s_buf,scr);

            TextFF(216-GetFFWidth(cardName[temp->Number])/2,202,cardName[temp->Number],scr);

            if (nCardGrid[SDX][SDY]>1)
            {
                if (input_GetState(Ki_R) && (SDS<nCardGrid[SDX][SDY]-1))
                {
                    SDS++;
                    SPU(sChif);
                }
                if (input_GetState(Ki_L) && SDS>0)
                {
                    SDS--;
                    SPU(sChif);
                }

                sprintf(s_buf,"%d/%d",SDS+1,nCardGrid[SDX][SDY]);
                TextFF(216-GetFFWidth(s_buf)/2,184,s_buf,scr);

                DrawAnimImage(Buttons_img,181,184,4,scr);
                DrawAnimImage(Buttons_img,241,184,5,scr);
            }
        }

        DrawPlayerCards(scr);




        if (SDSEL==5)//  ;яДЕКЮКХ БШАНП?
        {
        SDL_Flip(scr);
        DrawBkg(BKG_SEL,scr);
        sprintf(s_buf,"%d",v_HMCards);
        TextFF(70,202,s_buf,scr);
        sprintf(s_buf,"%d",v_HMCardsType);
        TextFF(138,202,s_buf,scr);
        sprintf(s_buf,"%d",vPlayer.Pl_winWIn);
        TextFF(245-GetFFWidth(s_buf),66,s_buf,scr);
        sprintf(s_buf,"%d",vPlayer.Pl_winLose);
        TextFF(245-GetFFWidth(s_buf),76,s_buf,scr);
        sprintf(s_buf,"%d",vPlayer.Pl_winBoth);
        TextFF(245-GetFFWidth(s_buf),86,s_buf,scr);

        DrawCrdPlot(scr);
        DrawPlayerCards(scr);
        SDL_Flip(scr);

        if (DrawTrueOrNo2(GetLangString(25),scr))//Подтверждаете выбор?
            {
                Select_Exit=true;
                NextScreen(scrInit);
            }
        else
            {
            		SDSEL=SDSEL-1;
            		SPU(sOtmen);

            		if (SDSEL>=0)
                        {
                            SelScr_Add(MyCards[SDSEL].crd);
                            MyCards[SDSEL].crd=NULL;
                        }
            }
        }

        // If KeyDown(70) Then
        //	If CardGrid(SDX,SDY,0)<>0 Then CreateWindowText(10,10,(GetLangString(26)+Str(Temp\Expirience)+"/"+Str (  (LetterToNumber(Temp\Attack) - LetterToNumber(cardAtack[Temp\Number]))*750+1500)))
        //EndIf


        SDL_Flip(scr);
    }

}



uint8_t NumberToGroup(uint8_t Number)
{
    if (Number>=56 && Number<=69) return 1;
    if (Number>=70 && Number<=79) return 2;
    if (Number>=80 && Number<=87) return 3;
    if (Number>=88 && Number<=92) return 4;
    if (Number>=93 && Number<=94) return 5;
    if (Number>=95 && Number<=100) return 6;
    return 0;
}
/*;Группы
;0-КАРТЫ МОНСТРОВ
;1-КАРТЫ МАГИИ И ЭЙДОЛОНОВ
;2-КАРТЫ ОРУЖИЯ И ЭКИПИРОВКИ
;3-КАРТЫ КОРАБЛЕЙ
;4-КАРТЫ ДРУЖЕЛЮБНЫХ МОНСТРОВ
;5-КАРТЫ ЗАМКОВ
;6-РЕДКИЕ КАРТЫ
*/


void DrawGlyph(uint8_t x,uint8_t y,uint8_t Numb,uint8_t Col,SDL_Surface * scr)
{
    if (Col==1)
        DrawAnimImage(Glyphx,XToSelX(y),YToSelY(x),NumberToGroup(Numb),scr);
    else if (Col > 1)
    {
        DrawAnimImage(Glyphx,XToSelX(y),YToSelY(x),NumberToGroup(Numb)+7,scr);
        SelScrn_PrintLet(XToSelX(y)+12-SelScrn_GetWidth(Col),YToSelY(x)+9,Col,scr);
    }
}

void DrawGlyph2(uint8_t x,uint8_t y,uint8_t Numb,uint8_t Col,SDL_Surface * scr)
{
    if (Col==1)
        DrawAnimImage(Glyphx,XToSelX2(y),YToSelY2(x),NumberToGroup(Numb),scr);
    else if (Col > 1)
    {
        DrawAnimImage(Glyphx,XToSelX2(y),YToSelY2(x),NumberToGroup(Numb)+7,scr);
        SelScrn_PrintLet(XToSelX2(y)+12-SelScrn_GetWidth(Col),YToSelY2(x)+9,Col,scr);
    }
}


void SelScrn_PrintLet(uint16_t x,uint16_t y,uint8_t Str,SDL_Surface * scr)
{
    char bff[4];
    memset(bff,0,4);
    sprintf(bff,"%d",Str);
    for (uint8_t i=0;i<strlen(bff);i++)
        DrawAnimImage(GlyphNumbers,(x+((i-1)*4)),y,(uint8_t)bff[i]-0x30,scr);
}

uint8_t SelScrn_GetWidth(uint8_t Str)
{
    char bff[4];
    memset(bff,0,4);
    sprintf(bff,"%d",Str);

    if (strlen(bff)>0)
        return (3+((strlen(bff)-1)*4));
    else
        return 0;
}


void DrawCrdPlot(SDL_Surface *scr)
{
    for (uint8_t y=0;y<=9;y++)
        for (uint8_t x=0;x<=9;x++)
            DrawGlyph(x,y,(y*10+x+1),nCardGrid[x][y],scr);
}

void DrawCrdPlot2(SDL_Surface *scr)
{
    for (uint8_t y=0;y<=9;y++)
        for (uint8_t x=0;x<=9;x++)
            DrawGlyph2(x,y,(y*10+x+1),nCardGrid[x][y],scr);
}


void ScreenSelectCard2(SDL_Surface *scr)
{

    Select_Exit=false;


    uint8_t SDX=0;
    uint8_t SDY=0;
    uint8_t SDS=0;
    uint8_t SDP=0;
    bool    ToDraw=true;
    int16_t Cvet=0;
    uint32_t ttime=0;
    card * temp;

    ExSelect();
    HowManyCards();
    HowManyCardType();
    Pereshet();


    while (!Select_Exit)
    {
        DrawBkg(BKG_CARDS,scr);

        if (input_GetState(Ki_O))
        {
            SPU(sOtmen);
            Select_Exit=true;
            NextScreen(scrMain);
        }

        if (millisec()>ttime+10)
        {
            ttime=millisec();
            if (ToDraw)
            {
                Cvet+=4;
                if (Cvet>255)
                {
                    Cvet=255;
                    ToDraw=!ToDraw;
                }
            }
            else
            {
                Cvet-=4;
                if (Cvet<0)
                {
                    Cvet=0;
                    ToDraw=!ToDraw;
                }
            }
        }

        if (input_GetState(Ki_UP))
        {
            if (SDX==0) SDX=10;
            SDX--;
            SPU(sKlik2);
            SDS=0;
        }

        if (input_GetState(Ki_DOWN))
        {
            SDX++;
            SPU(sKlik2);
            if (SDX>9) SDX=0;
            SDS=0;
        }

        if (input_GetState(Ki_LEFT))
        {
            if (SDY==0) SDY=10;
            SDY--;
            SPU(sKlik2);
            SDS=0;
        }

        if (input_GetState(Ki_RIGHT))
        {
            SDY++;
            SPU(sKlik2);
            if (SDY>9) SDY=0;
            SDS=0;
        }

        sprintf(s_buf,"%d",v_HMCards);
        TextFF(58,203,s_buf,scr);
        sprintf(s_buf,"%d",v_HMCardsType);
        TextFF(137,203,s_buf,scr);
        sprintf(s_buf,"%d",vPlayer.Pl_winWIn);
        TextFF(295-GetFFWidth(s_buf),79,s_buf,scr);
        sprintf(s_buf,"%d",vPlayer.Pl_winLose);
        TextFF(295-GetFFWidth(s_buf),89,s_buf,scr);
        sprintf(s_buf,"%d",vPlayer.Pl_winBoth);
        TextFF(295-GetFFWidth(s_buf),99,s_buf,scr);

        TextFF(180,59,GetRang(vPlayer.Pl_Level),scr);
        sprintf(s_buf,"%d",vPlayer.Pl_Level);
        TextFF(298-GetFFWidth(s_buf),47,s_buf,scr);


        DrawCrdPlot2(scr);
        rectangleRGBA(scr,XToSelX2(SDY),YToSelY2(SDX),XToSelX2(SDY)+14,YToSelY2(SDX)+14,255,0,0,Cvet);
        DrawHand(XToSelX2(SDY)-14,YToSelY2(SDX)+2,scr);

        if (nCardGrid[SDX][SDY]>0)
        {
            temp=CardGrid[SDX][SDY][SDS];
            if (nCardGrid[SDX][SDY]>1)
            {
                uint8_t jkl=nCardGrid[SDX][SDY];
                if (jkl>5)
                    jkl=5;
                jkl--;
                for (uint8_t lkj=jkl;lkj>0;lkj--)
                {
                    DrawImage(blRobe,217+lkj*4,127+lkj,scr);
                    DrawImage(Card_imgs[temp->Number],217+lkj*4,127+lkj,scr);
                    DrawAImage(blk_crd_img,217+lkj*4,127+lkj,50+lkj*40,scr);
                }
            }
            DrawCard2(temp,0,217,127,scr);
            sprintf(s_buf,"%s",cardName[temp->Number]);
            s_buf[17]=0;
            TextFF(239-GetFFWidth(s_buf)/2,203,s_buf,scr);

            if (nCardGrid[SDX][SDY]>1)
            {
                if (input_GetState(Ki_R) && (SDS<nCardGrid[SDX][SDY]-1))
                {
                    SDS++;
                    SPU(sChif);
                }
                if (input_GetState(Ki_L) && SDS>0)
                {
                    SDS--;
                    SPU(sChif);
                }

                sprintf(s_buf,"%d/%d",SDS+1,nCardGrid[SDX][SDY]);
                TextFF(239-GetFFWidth(s_buf)/2,190,s_buf,scr);
                DrawAnimImage(Buttons_img,200,183,4,scr);
                DrawAnimImage(Buttons_img,264,183,5,scr);
            }
        }


        if (input_GetState(Ki_X))
        {
        	if (nCardGrid[SDX][SDY])
                {
                SPU(sChif);
        		temp=CardGrid[SDX][SDY][SDS];
        		if (temp->Number<5)
                    {
        			if ((temp->Attack==defAtack[temp->Number]) && (temp->Atype==defAType[temp->Number]) && (temp->PDefence==defPDef[temp->Number]) && (temp->MDefence==defMDef[temp->Number]))
                        SDP=0;
        			else
                        SDP=Price2(temp)/3;
                    }
        		else
        			SDP=Price2(temp)/3;

                sprintf(s_buf,GetLangString(27),SDP);  //Вы хотите продать за %d?
        		if (DrawTrueOrNo2(s_buf,scr))
                    {
        			vPlayer.Pl_v_Gil+=SDP;
        			DeletePlayerCard(CardGrid[SDX][SDY][SDS]);
        			delete CardGrid[SDX][SDY][SDS];
        			if (SDS==nCardGrid[SDX][SDY] && SDS>1)
                        SDS--;
        			ExSelect();
        			SPU(sChif);
        			Pereshet();
        			HowManyCards();
                    }
        		else
        			SPU(sOtmen);
                }
        }

        /*If KeyDown(70) Then
        	If CardGrid(SDX,SDY,0)<>0 Then CreateWindowText(10,10,(GetLangString(26)+Str(Temp\Expirience)+"/"+Str (  (LetterToNumber(Temp\Attack) - LetterToNumber(cardAtack[Temp\Number]))*750+1500)))
        EndIf
        */
        SDL_Flip(scr);
    }

}


char *GetRang(uint32_t Level)
{
	if (Level<300 ) return GetLangString(28);  //Начинающий
	if (Level>=300 && Level<400 ) return GetLangString(29);
	if (Level>=400 && Level<500 ) return GetLangString(30);
	if (Level>=500 && Level<600 ) return GetLangString(31);
	if (Level>=600 && Level<700 ) return GetLangString(32);
	if (Level>=700 && Level<800 ) return GetLangString(33);
	if (Level>=800 && Level<900 ) return GetLangString(34);
	if (Level>=900 && Level<1000 ) return GetLangString(35);
	if (Level>=1000 && Level<1100 ) return GetLangString(36);
	if (Level>=1100 && Level<1200 ) return GetLangString(37);
	if (Level>=1200 && Level<1250 ) return GetLangString(38);
	if (Level>=1250 && Level<1300 ) return GetLangString(39);
	if (Level>=1300 && Level<1320 ) return GetLangString(40);
	if (Level>=1320 && Level<1330 ) return GetLangString(41);
	if (Level>=1330 && Level<1340 ) return GetLangString(42);
	if (Level>=1340 && Level<1350 ) return GetLangString(43);
	if (Level>=1350 && Level<1360 ) return GetLangString(44);
	if (Level>=1360 && Level<1370 ) return GetLangString(45);
	if (Level>=1370 && Level<1380 ) return GetLangString(46);
	if (Level>=1380 && Level<1390 ) return GetLangString(47);
	if (Level>=1390 && Level<1400 ) return GetLangString(48);
	if (Level>=1400 && Level<1450 ) return GetLangString(49);
	if (Level>=1450 && Level<1475 ) return GetLangString(50);
	if (Level>=1475 && Level<1500 ) return GetLangString(51);
	if (Level>=1500 && Level<1550 ) return GetLangString(52);
	if (Level>=1550 && Level<1600 ) return GetLangString(53);
	if (Level>=1600 && Level<1650 ) return GetLangString(54);
	if (Level>=1650 && Level<1680 ) return GetLangString(55);
	if (Level>=1680 && Level<1690 ) return GetLangString(56);
	if (Level>=1690 && Level<1698 ) return GetLangString(57);
	if (Level>=1698 ) return GetLangString(58);  //Мастер

}

void Pereshet()
{
HowManyCardType();
float lLev;
lLev=v_HMCardsType*8;
  for (uint32_t i=0; i<playercards.size();i++)
    lLev+=playercards[i]->Attack*0.65;
vPlayer.Pl_Level=lLev;
}
