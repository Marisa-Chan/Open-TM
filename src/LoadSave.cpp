#include "res.h"

int8_t SLState=0;
int8_t OnScrSt=0;
char   SL_State[3][6][30];
uint8_t SL_Face[3];


void DeleteAllPlayerCards()
{
    for (uint32_t ii=0;ii<playercards.size();ii++)
        delete playercards[ii];

    playercards.clear();
}

void DeleteAllEnemysCards()
{
    for (uint8_t i=0;i<21;i++)
        for ( uint8_t j=0;j<30;j++)
            if (EnemiesCards[i][j])
            {
                delete EnemiesCards[i][j];
                EnemiesCards[i][j]=NULL;
            }
}


void GetStatesInfo()
{
    memset(SL_State,0,3*6*30);

    FILE *fil;

    Player tmpl;

    for (uint8_t i=0; i<3; i++)
    {
        sprintf(s_buf,"./save/state%d.sav",i+OnScrSt);
        fil=fopen(s_buf,"rb");

        if (fil)
        {
            uint32_t magic[3];
            fread(magic,12,1,fil);

            //MAGIC CHECK
            //


            float ver;
            fread(&ver,4,1,fil);

            // VERSION CHECK
            //


            char data[11];
            data[10]=0;
            fread(data,10,1,fil);

            char timee[6];
            timee[5]=0;
            fread(timee,5,1,fil);

            fread(&tmpl,sizeof(Player),1,fil);


            memcpy(SL_State[i][0],tmpl.Pl_v_Name,29); // Имя
            SL_Face[i]=tmpl.Pl_v_Face;

            sprintf(s_buf,GetLangString(14),tmpl.Pl_Level); //Уровень
            memcpy(SL_State[i][1],s_buf,strlen(s_buf));

            sprintf(s_buf,GetLangString(13),tmpl.Pl_v_Gil); //Гили
            memcpy(SL_State[i][2],s_buf,strlen(s_buf));

            sprintf(s_buf,GetLangString(15),data);
            memcpy(SL_State[i][3],s_buf,strlen(s_buf));//Дата

            sprintf(s_buf,GetLangString(16),timee);
            memcpy(SL_State[i][4],s_buf,strlen(s_buf));//Время


            fclose(fil);
        }
    }
}



bool LoadState(uint8_t num)
{
    sprintf(s_buf,"./save/state%d.sav",num);
    FILE *fil=fopen(s_buf,"rb");

    uint32_t magic[3];
    fread(magic,12,1,fil);

    //MAGIC CHECK
    //

    float ver;
    fread(&ver,4,1,fil);

    // VERSION CHECK
    //

    fseek(fil,15,SEEK_CUR);

    //readdate 10 bytes
    //readtime 5 bytes



    DeleteAllEnemysCards();
    DeleteAllPlayerCards();



    fread(&vPlayer,sizeof(Player),1,fil);



    uint32_t cards;

    fread(&cards,sizeof(cards),1,fil);
    for (uint32_t i=0;i<cards;i++)
    {
        card *crd;
        crd=new(card);
        fread(crd,sizeof(card),1,fil);
        playercards.push_back(crd);
    }

    for (uint8_t j=0; j<21; j++)
    {
        fread(&cards,sizeof(cards),1,fil);
        for (uint32_t i=0;i<cards;i++)
        {
            card *crd;
            crd=new(card);
            fread(crd,sizeof(card),1,fil);
            EnemiesCards[j][i]=crd;
        }
        EnemiesNumCards[j]=cards;
    }


    fclose(fil);
    return true;
}







void Load_Menu(SDL_Surface *scr)
{

    memset(SL_State,0,3*6*30*sizeof(char));
    memset(SL_Face,0,3*sizeof(uint8_t));
    GetStatesInfo();

    bool LLoop=false;
    uint32_t ttimer=0;
    bool WhatTT=true;


    SDL_Delay(400);


    while (!LLoop)
    {
        DrawBkg(BKG_LOAD,scr);

        if (millisec()>ttimer+500)
        {
            ttimer=millisec();
            WhatTT=!WhatTT;
        }

        if (WhatTT)
        {
            DrawAnimImage(S_L_Arrays,302,44,0,scr);
            DrawAnimImage(S_L_Arrays,302,207,2,scr);
        }
        else
        {
            DrawAnimImage(S_L_Arrays,302,44,1,scr);
            DrawAnimImage(S_L_Arrays,302,207,3,scr);
        }


        for (uint8_t i=0; i<3; i++)
        {
            if (strlen(SL_State[i][0]))
            {
                DrawImage(Faces[SL_Face[i]],13,47+i*60,scr);
                TextFF(64,50+i*60,SL_State[i][0],scr); // Имя
                TextFF(64,65+i*60,SL_State[i][2],scr); // Гили
                TextFF(64,80+i*60,SL_State[i][1],scr); // Уровень
                TextFF(170,77+i*60,SL_State[i][3],scr);// Дата
                TextFF(170,87+i*60,SL_State[i][4],scr);//Время
            }
            else
            {
                TextFF(30,66+i*60,GetLangString(17),scr);  //Пустой блок.
                sprintf(s_buf,GetLangString(18),OnScrSt+i); //ФАЙЛ %.2d
                TextFF(10,46+i*60,s_buf,scr);
            }
        }




        if (input_GetState(Ki_X))
            if (strlen(SL_State[SLState][0]))
            {
                LLoop=true;
                LoadState(OnScrSt+SLState);
                NextScreen(scrMain);
                spuMusic(1);

                SPU(sChif);
            }

        if (input_GetState(Ki_O))
        {
            SPU(sOtmen);
            LLoop=true;
            if (getPrevScreen()==1)
                NextScreen(scrMain);
            else
                NextScreen(scrIntro2);
        }

        if (input_GetState(Ki_UP))
        {
            SPU(sKlik2);
            SLState--;
            if (SLState<0)
            {
                SLState=0;
                if (OnScrSt>0)
                {
                    OnScrSt--;
                    GetStatesInfo();
                }
                if (OnScrSt<0)
                    OnScrSt=0;
            }
        }

        if (input_GetState(Ki_DOWN))
        {
            SPU(sKlik2);
            SLState++;
            if (SLState>2)
            {
                SLState=2;
                if (OnScrSt<12)
                {
                    OnScrSt++;
                    GetStatesInfo();
                }
                if (OnScrSt>12)
                    OnScrSt=12;
            }
        }


        sprintf(s_buf,GetLangString(18),OnScrSt+SLState);  //ФАЙЛ %.2d
        TextFF(166,16,s_buf,scr);

        DrawHand(0,65+SLState*60,scr);

        SDL_Flip(scr);
    }

}





bool SaveState(uint8_t num)
{
    time_t tim;
    tm * timeinfo;

    Pereshet();

    mkdir("./save",ALLPERMS);
    sprintf(s_buf,"./save/state%d.sav",num);
    FILE *fil=fopen(s_buf,"wb");

    uint32_t magic[3];
    magic[0]=0x72746554;
    magic[1]=0x614D2061;
    magic[2]=0x72657473;
    fwrite(magic,12,1,fil);


    float ver=1.0;
    fwrite(&ver,4,1,fil);

    tim=time(NULL);
    timeinfo=localtime ( &tim );
    strftime(s_buf,20,"%d-%m-%Y",timeinfo);
    fwrite(s_buf,10,1,fil);

    strftime(s_buf,20,"%H:%M",timeinfo);
    fwrite(s_buf,5,1,fil);



    fwrite(&vPlayer,sizeof(Player),1,fil);


    HowManyCards();
    uint32_t cards=v_HMCards;

    fwrite(&cards,sizeof(cards),1,fil);
    for (uint32_t i=0;i<cards;i++)
    {
        fwrite(playercards[i],sizeof(card),1,fil);
    }

    enemy_sortirovka();
    enemy_podshet();

    for (uint8_t j=0; j<21; j++)
    {
        cards=EnemiesNumCards[j];
        fwrite(&cards,sizeof(cards),1,fil);
        for (uint32_t i=0;i<cards;i++)
        {
            fwrite(EnemiesCards[j][i],sizeof(card),1,fil);
        }

    }


    fclose(fil);
    return true;
}




void Save_Menu(SDL_Surface *scr)
{


    memset(SL_State,0,3*6*30*sizeof(char));
    memset(SL_Face,0,3*sizeof(uint8_t));

    Pereshet();
    GetStatesInfo();

    bool LLoop=false;
    uint32_t ttimer=0;
    bool WhatTT=true;



    SDL_Delay(400);//Delay 400


    while (!LLoop)
    {
        DrawBkg(BKG_SAVE,scr);

        if (millisec()>ttimer+500)
        {
            ttimer=millisec();
            WhatTT=!WhatTT;
        }

        if (WhatTT)
        {
            DrawAnimImage(S_L_Arrays,302,44,0,scr);
            DrawAnimImage(S_L_Arrays,302,207,2,scr);
        }
        else
        {
            DrawAnimImage(S_L_Arrays,302,44,1,scr);
            DrawAnimImage(S_L_Arrays,302,207,3,scr);
        }



        for (uint8_t i=0; i<3; i++)
        {
            if (strlen(SL_State[i][0]))
            {
                DrawImage(Faces[SL_Face[i]],13,47+i*60,scr);
                TextFF(64,50+i*60,SL_State[i][0],scr); // Имя
                TextFF(64,65+i*60,SL_State[i][2],scr); // Гили
                TextFF(64,80+i*60,SL_State[i][1],scr); // Уровень
                TextFF(170,77+i*60,SL_State[i][3],scr);// Дата
                TextFF(170,87+i*60,SL_State[i][4],scr);//Время
            }
            else
            {
                TextFF(30,66+i*60,GetLangString(17),scr); //Пустой блок.
                sprintf(s_buf,GetLangString(18),OnScrSt+i); //ФАЙЛ %.2d
                TextFF(10,46+i*60,s_buf,scr);
            }
        }

        sprintf(s_buf,GetLangString(18),OnScrSt+SLState); //ФАЙЛ %.2d
        TextFF(166,16,s_buf,scr);

        DrawHand(0,65+SLState*60,scr);

        if (input_GetState(Ki_X))
        {
            if (strlen(SL_State[SLState][0]))
            {
                if (DrawTrueOrNo2(GetLangString(21),scr)) //Записать поверх?
                {
                    SPU(sChif);
                    SaveState(OnScrSt+SLState);
                    SDL_Delay(500);
                    GetStatesInfo();
                }
                else
                {
                    SPU(sOtmen);
                }

            }
            else
            {

                SPU(sChif);
                SaveState(OnScrSt+SLState);
                SDL_Delay(500);
                GetStatesInfo();
            }
        }

        if (input_GetState(Ki_O))
        {
            SPU(sOtmen);
            LLoop=true;
            NextScreen(scrMain);
        }

        if (input_GetState(Ki_UP))
        {
            SPU(sKlik2);
            SLState--;
            if (SLState<0)
            {
                SLState=0;
                if (OnScrSt>0)
                {
                    OnScrSt--;
                    GetStatesInfo();
                }
                if (OnScrSt<0)
                    OnScrSt=0;
            }
        }

        if (input_GetState(Ki_DOWN))
        {
            SPU(sKlik2);
            SLState++;
            if (SLState>2)
            {
                SLState=2;
                if (OnScrSt<12)
                {
                    OnScrSt++;
                    GetStatesInfo();
                }
                if (OnScrSt>12)
                    OnScrSt=12;
            }
        }



        SDL_Flip(scr);
    }
}


void Delete_Menu(SDL_Surface *scr)
{

    memset(SL_State,0,3*6*30*sizeof(char));
    memset(SL_Face,0,3*sizeof(uint8_t));

    GetStatesInfo();
    bool LLoop=false;
    uint32_t ttimer=0;
    bool WhatTT=true;
    bool ViborSd=false;

    SDL_Delay(400);
//FlushKeys()
//FlushJoy()
    while (!LLoop)
    {
        DrawBkg(BKG_DEL,scr);

        if (millisec()>ttimer+500)
        {
            ttimer=millisec();
            WhatTT=!WhatTT;
        }

        if (WhatTT)
        {
            DrawAnimImage(S_L_Arrays,302,44,0,scr);
            DrawAnimImage(S_L_Arrays,302,207,2,scr);
        }
        else
        {
            DrawAnimImage(S_L_Arrays,302,44,1,scr);
            DrawAnimImage(S_L_Arrays,302,207,3,scr);
        }




        for (uint8_t i=0; i<3; i++)
        {
            if (strlen(SL_State[i][0]))
            {
                DrawImage(Faces[SL_Face[i]],13,47+i*60,scr);
                TextFF(64,50+i*60,SL_State[i][0],scr); // Имя
                TextFF(64,65+i*60,SL_State[i][2],scr); // Гили
                TextFF(64,80+i*60,SL_State[i][1],scr); // Уровень
                TextFF(170,77+i*60,SL_State[i][3],scr);// Дата
                TextFF(170,87+i*60,SL_State[i][4],scr);//Время
            }
            else
            {
                TextFF(30,66+i*60,GetLangString(17),scr); //Пустой блок.
                sprintf(s_buf,GetLangString(18),OnScrSt+i); //ФАЙЛ %.2d
                TextFF(10,46+i*60,s_buf,scr);
            }
        }


        if (input_GetState(Ki_O))
        {
            SPU(sOtmen);
            LLoop=true;
            NextScreen(scrMain);
        }

        if (input_GetState(Ki_UP))
        {
            SPU(sKlik2);
            SLState--;
            if (SLState<0)
            {
                SLState=0;
                if (OnScrSt>0)
                {
                    OnScrSt--;
                    GetStatesInfo();
                }
                if (OnScrSt<0)
                    OnScrSt=0;
            }
        }

        if (input_GetState(Ki_DOWN))
        {
            SPU(sKlik2);
            SLState++;
            if (SLState>2)
            {
                SLState=2;
                if (OnScrSt<12)
                {
                    OnScrSt++;
                    GetStatesInfo();
                }
                if (OnScrSt>12)
                    OnScrSt=12;
            }
        }


        sprintf(s_buf,GetLangString(18),SLState+OnScrSt); //ФАЙЛ %.2d
        TextFF(166,16,s_buf,scr);

        DrawHand(0,65+SLState*60,scr);

        if (input_GetState(Ki_X))
        {
            if (strlen(SL_State[SLState][0]))
            {
                SPU(sChif);
                if (DrawTrueOrNo2(GetLangString(22),scr)) //Delete file?
                {
                    SPU(sChif);
                    sprintf(s_buf,"./save/state%d.sav",SLState+OnScrSt);
                    remove(s_buf);
                    GetStatesInfo();
                }
                else
                {
                    SPU(sOtmen);
                }

            }



        }
    SDL_Flip(scr);
    }
}

