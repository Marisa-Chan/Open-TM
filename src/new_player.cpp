#include "res.h"



void New_player(SDL_Surface *scr)
{

    bool endscr=false;

    uint8_t part=0;


    char namaiwa[31];
    memset(namaiwa,0,31);
    uint8_t bukva=0;

    uint8_t sel_Face=0;

    uint8_t sel_menu=0;

    uint8_t prev=1;





    uint8_t DSX=0,DSY=0;

    uint16_t tabs[21][8];

    memset(tabs,0,21*8*sizeof(uint16_t));
    for (uint8_t i=0;i<95;i++)
        {
            *(uint8_t *)(&(tabs[i % 21][i/21]))=i+32;
        }
    for (uint8_t i=95;i<(95+64);i++)
        {
            *(uint8_t *)(&(tabs[i % 21][i/21]))=i+97;
        }


    while(!endscr)
    {
        DrawImage(Name_BKG,0,0,scr);


        for (uint8_t j=0;j<8;j++)
            for (uint8_t i=0;i<21;i++)
                if (tabs[i][j]!=0)
                    TextFF(90+i*10,95+j*15,(char *)&tabs[i][j],scr);


        sprintf(s_buf,"%s_",namaiwa);
        TextFF(88,72,s_buf,scr);

        DrawImage(Faces[sel_Face],8,26,scr);


        TextFF(20,95,GetLangString(63),scr); //Create
        TextFF(20,115,GetLangString(8),scr); //Cancel





        switch(part)
        {
        case 0: ////Change Face

        DrawHand(0,30,scr);

        if (input_GetState(Ki_RIGHT))
            {
                sel_Face= sel_Face == 71 ? 0 :++sel_Face;
                SPU(sKlik2);
            }

        if (input_GetState(Ki_LEFT))
            {
                sel_Face= sel_Face == 0 ? 71 :--sel_Face;
                SPU(sKlik2);
            }

        if (input_GetState(Ki_DOWN))
            {
                part=prev;
                SPU(sKlik2);
            }

        if (input_GetState(Ki_X))
            {
                part=1;
                SPU(sKlik2);
            }

        if (input_GetState(Ki_O))
                    {
                        SPU(sOtmen);
                        part=2;
                        sel_menu=1;
                    }



        break;

        case 1:   ////Change Name
        prev=1;
        DrawHand(90-22+DSX*10,95+DSY*15,scr);

        if (input_GetState(Ki_RIGHT))
                if (DSX<20)
                    if (tabs[DSX+1][DSY]!=0)
                    {
                        DSX++;
                        SPU(sKlik2);
                    }

        if (input_GetState(Ki_LEFT))
                if (DSX>0)
                    {
                        if (tabs[DSX-1][DSY]!=0)
                        {
                            DSX--;
                            SPU(sKlik2);
                        }
                    }
                else
                    {
                    part=2;
                    SPU(sKlik2);
                    }


        if (input_GetState(Ki_DOWN))
                if (DSY<7)
                    if (tabs[DSX][DSY+1]!=0)
                    {
                        DSY++;
                        SPU(sKlik2);
                    }

        if (input_GetState(Ki_UP))
                if (DSY>0)
                    {
                        if (tabs[DSX][DSY-1]!=0)
                        {
                            DSY--;
                            SPU(sKlik2);
                        }
                    }
                else
                    {
                    part=0;
                    SPU(sKlik2);
                    }

        if (input_GetState(Ki_X))
                if (bukva<30)
                    {
                        namaiwa[bukva]=(tabs[DSX][DSY] & 0xFF);
                        bukva++;
                        SPU(sChif);
                    }

        if (input_GetState(Ki_O))
                if (bukva>0)
                    {
                        bukva--;
                        namaiwa[bukva]=0;
                        SPU(sOtmen);
                    }
                else
                    {
                        SPU(sOtmen);
                        part=2;
                        sel_menu=1;
                    }



        break;

        case 2: ////Menu
        prev=2;

        DrawHand(0,95+sel_menu*20,scr);


        if (input_GetState(Ki_DOWN))
                    {
                        sel_menu=1-sel_menu;
                        SPU(sKlik2);
                    }

        if (input_GetState(Ki_UP))
                if (sel_menu)
                    {
                        sel_menu--;
                        SPU(sKlik2);
                    }
                else
                    {
                    part=0;
                    SPU(sKlik2);
                    }

        if (input_GetState(Ki_RIGHT))
                    {
                        part=1;
                        SPU(sKlik2);
                    }

        if (input_GetState(Ki_O))
                    {
                        SPU(sOtmen);
                        sel_menu=1;
                    }

        if (input_GetState(Ki_X))
            switch(sel_menu)
                {
                    case 0:
                        if (strlen(namaiwa)>0)
                            {
                                memset(&vPlayer,0,sizeof(Player));
                                memcpy(vPlayer.Pl_v_Name,namaiwa,31);
                                vPlayer.Pl_v_Face=sel_Face;
                                SPU(sChif);
                                NextScreen(scrMain);
                                spuMusic(1);
                                endscr=true;
                            }
                        else
                            {
                                SPU(sBlocker);

                            }
                    break;
                    case 1:
                        NextScreen(scrIntro2);
                        SPU(sOtmen);
                        endscr=true;


                }






        }



        if (input_GetState(Ki_SELECT))
                endscr=true;



        SDL_Flip(scr);


    }
}
