#include "res.h"


uint8_t Shop[10][6];
uint32_t Sh_Price[10];


void GenerateShopCard(uint8_t i,uint8_t n)
{
    Shop[i][0]=n;
    Shop[i][1]=defAtack[n]+(rand() & 1);
    Shop[i][2]=defAType[n];
    Shop[i][3]=defPDef[n]+(rand() & 1);
    Shop[i][4]=defMDef[n]+(rand() & 1);
    Shop[i][5]=rand() % 256;
}

uint32_t Price(uint8_t n,uint8_t a,uint8_t at,uint8_t pd,uint8_t md,uint8_t arr)
{
    uint32_t pr;
    pr=n*100;
    uint8_t sk=0;
    for (uint8_t i=0; i<8; i++)
        if (((arr>>i) & 1) == 1)
            sk++;

    pr+=sk*62.5;
    if (at==aT_X)
        pr+=500;
    if (at==aT_A)
        pr+=1000;
    pr+=a*31.25;
    pr+=pd*31.25;
    pr+=md*31.25;
    return pr;
}

uint32_t Price2(card *crd)
{
    uint32_t pr;
    pr=crd->Number*100;
    uint8_t sk=0;
    for (uint8_t i=0; i<8; i++)
        if (((crd->Arr>>i) & 1) == 1)
            sk++;

    pr+=sk*62.5;
    if (crd->Atype==aT_X)
        pr+=500;
    if (crd->Atype==aT_A)
        pr+=1000;
    pr+=crd->Attack*31.25;
    pr+=crd->PDefence*31.25;
    pr+=crd->MDefence*31.25;
    return pr;
}

void Magazine(SDL_Surface *scr)
{
    ExSelect();

    for (uint8_t i=0;i<4;i++)
    {
        Shop[i][0]=i;
        Shop[i][1]=defAtack[i];
        Shop[i][2]=defAType[i];
        Shop[i][3]=defPDef[i];
        Shop[i][4]=defMDef[i];
        Shop[i][5]=rand() % 256;
        Sh_Price[i]=0;
    }

    for (uint8_t i=4; i<10; i++)
    {
        GenerateShopCard(i,rand() % 96+4);
        Sh_Price[i]=Price(Shop[i][0],Shop[i][1],Shop[i][2],Shop[i][3],Shop[i][4],Shop[i][5]);
    }


    bool Shop_exit=false;
    Shop_exit=false;

    int8_t SlotBuy=0;

    while (!Shop_exit)
    {
        DrawBkg(BKG_SHOP,scr);

        if (input_GetState(Ki_UP))
        {
            SPU(sKlik2);
            SlotBuy--;
            if (SlotBuy<0)
                SlotBuy=9;
        }

        if (input_GetState(Ki_DOWN))
        {
            SPU(sKlik2);
            SlotBuy++;
            if (SlotBuy>9)
                SlotBuy=0;
        }

        if (input_GetState(Ki_O))
        {
            SPU(sOtmen);
            Shop_exit=true;
        }

        for (uint8_t i=0; i<10; i++)
        {
            DrawImage(ico_Card,16,45+i*15,scr);
            sprintf(s_buf,"%s",cardName[Shop[i][0]]);
            s_buf[16]=0;
            TextFF(30,48+i*15,s_buf,scr);
            sprintf(s_buf,"%d",Sh_Price[i]);
            TextFF(141,48+i*15,s_buf,scr);
        }
        DrawHand(3,48+SlotBuy*15,scr);
        DrawCard(Shop[SlotBuy][0],0,227,121,Shop[SlotBuy][1],Shop[SlotBuy][2],Shop[SlotBuy][3],Shop[SlotBuy][4],Shop[SlotBuy][5],scr);

        sprintf(s_buf,"%d",vPlayer.Pl_v_Gil);
        TextFF(295-GetFFWidth(s_buf),47,s_buf,scr);

        uint8_t LNumb = Shop[SlotBuy][0];
        uint8_t Dx=LNumb % 10;
        uint8_t Dy=LNumb / 10;

        sprintf(s_buf,"%d",nCardGrid[Dx][Dy]);
        TextFF(295-GetFFWidth(s_buf),61,s_buf,scr);

        if (input_GetState(Ki_X))
        {
            if (vPlayer.Pl_v_Gil>=Sh_Price[SlotBuy])
            {
                if (nCardGrid[Dx][Dy]<50)
                {
                    sprintf(s_buf,GetLangString(59),cardName[Shop[SlotBuy][0]]);  //Желаете купить: %s?
                    if (DrawTrueOrNo2(s_buf,scr))
                    {
                    vPlayer.Pl_v_Gil-=Sh_Price[SlotBuy];
                    AddCardToPlayer2(CreateCard(Shop[SlotBuy][0], Shop[SlotBuy][1],\
                                                Shop[SlotBuy][2], Shop[SlotBuy][3],\
                                                Shop[SlotBuy][4], Shop[SlotBuy][5]));
                    SPU(sChif);
                    //nCardGrid[Dx][Dy]++;
                    if (SlotBuy>3)
                    {
                        GenerateShopCard(SlotBuy,rand() % 96 + 5);
                        Sh_Price[SlotBuy]=Price(Shop[SlotBuy][0],Shop[SlotBuy][1],Shop[SlotBuy][2],Shop[SlotBuy][3],Shop[SlotBuy][4],Shop[SlotBuy][5]);
                    }
                    else
                        Shop[SlotBuy][5]=rand() % 256;

                    }
                }
                else
                    SPU(sBlocker);

            }
            else
                SPU(sBlocker);
        }


        SDL_Flip(scr);
    }
NextScreen(scrMain);
}


