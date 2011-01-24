#ifdef __cplusplus
#include <cstdlib>
#else
#include <stdlib.h>
#endif

#include "res.h"


bool done = false;
int32_t tt=10;

int gamethread(void *data);
bool gameend=false;
SDL_Thread *sys;

int main ( int argc, char** argv )
{

    if (argc==2)
        if (strcmp(argv[1],"-music")==0)
            ExtendMusic=true;

    srand(time(NULL));
    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }

    SDL_EnableKeyRepeat(50,SDL_DEFAULT_REPEAT_INTERVAL);

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);



    //SDL_Surface* screen = SDL_SetVideoMode(screen_w, screen_h, 32,SDL_HWSURFACE|SDL_DOUBLEBUF);
#ifdef DINGOO
    SDL_ShowCursor(SDL_DISABLE);
    SDL_Surface* screen = SDL_SetVideoMode(screen_w, screen_h, 16,SDL_SWSURFACE);
#else
    SDL_Surface* screen = SDL_SetVideoMode(screen_w, screen_h, 32,SDL_HWSURFACE);
#endif



    if ( !screen )
    {
        printf("Unable to set 320x240 video: %s\n", SDL_GetError());
        return 1;
    }






    memset(EnemiesCards,0,21*30*sizeof(card *));
    memset(EnemiesNumCards,0,21);
    memset(&vPlayer,0,sizeof(Player));


    InitMusic();
    Load_Game_Resources(screen);
    LoadSounds();
    InitFonts();
    enemy_LoadNameList();
    InitLangStrings();



    //ClearPole();
    //FlushCards();




    //music=Mix_LoadMUS("./TetraMaster.ogg");

    //if (music)
    //    Mix_PlayMusic(music,0);

    // program main loop
    Kii=0;
    sys=SDL_CreateThread(gamethread,screen);

    while (!done)
    {
        // message processing loop
        Kii=0;

        if (!Mix_PlayingMusic())
            if (CurrentMusic>4)
                spuMusic(1);


        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // check for messages
            switch (event.type)
            {
                // exit if the window is closed
            case SDL_QUIT:
                done =  true;
                gameend = true;
                break;

                // check for keypresses
            case SDL_KEYDOWN:
            {
                Kii=event.key.keysym.sym;
            }
            // case SDL_KEYUP:
            // {
            //     Kii=event.key.keysym.sym;
            // }
            } // end switch
            //
        } // end of message processing
#ifdef DINGOO
        SDL_Delay(150);
#else
        SDL_Delay(100);
#endif

    } // end main loop
    if (sys) SDL_KillThread(sys);
    Mix_CloseAudio();
    return 0;
}


void EndGame()
{
    gameend=true;
}


int gamethread(void *data)
{
    SDL_Surface *scr;
    scr=(SDL_Surface *)data;

    uint32_t fps,fpsshow,fpstimer=0;
    fpstimer=0;

    /*for (uint8_t s=0;s<10;s++)
        {
            card *pss;
        pss=new card;
        pss->Number=rand()%100;
        pss->Attack=defAtack[pss->Number];
        pss->Atype=defAType[pss->Number];
        pss->Expirience=0;
        pss->MDefence=defMDef[pss->Number];
        pss->PDefence=defPDef[pss->Number];
        pss->Arr=(rand() & 0xFF);


        playercards.push_back(pss);  //  MyCards[i].crd=pss;


        }*/

    //Intro_Screen(scr,false);

    char *bzz=GetCP1251("Select - Выход");
    char *bzz2=GetCP1251(" - Начать");


    time_t tim;
    tm * timeinfo;

    NextScreen(scrIntro);
    spuMusic(0); //intro


    while (!gameend)
    {
        switch (getDrawScreen())
        {
        case 0:
            Intro_Screen(scr,false);
            break;
        case 1:
            MainCycle(scr);
            break;
        case 2:
            Init_Game(scr);
            break;
        case 3:
            ScreenSelectCard(scr);
            break;
        case 4:
            New_player(scr);
            break;
        case 5:
            Load_Menu(scr);
            break;
        case 6:
            Intro_Screen(scr,true);
            break;
        case 7:
            Save_Menu(scr);
            break;
        case 8:
            Delete_Menu(scr);
            break;
        case 9:
            Magazine(scr);
            break;
        case 10:
            ScreenSelectCard2(scr);
        }

        /*fps++;

        SDL_FillRect(scr, 0, SDL_MapRGB(scr->format, 0, 0, 0));

        DrawAnimImage(Buttons_img,10,50,0,scr);

        TextFF(21,50,bzz2,scr);
        TextFF(10,70,bzz,scr);



        if (fpstimer<=millisec())
        {
            fpsshow=fps;
            fps=0;
            fpstimer=millisec()+1000;
        };

        char pss[10];
        memset(pss,0,10);
        sprintf(pss,"%d",fpsshow);

        tim=time(NULL);
        timeinfo=localtime ( &tim );
        strftime(s_buf,50,"%H:%M  %d-%m-%Y",timeinfo);
        CreateWindowText(100,100,s_buf,scr);

        if (input_GetState(Ki_START))
        {
            //Load_Menu(scr);
            //DrawTrueOrNo("nyaa",scr);

            //ScreenSelectCard2(scr);
            vPlayer.Pl_v_Gil=50000;
            Load_Menu(scr);//  Intro_Screen(scr,false);

        }

        if (input_GetState(Ki_X))
        {

            ScreenSelectCard(scr);
            WhoNow=20;
            Init_Game(scr);
            //New_player(scr);
        }


        if (input_GetState(Ki_L))
        {
            New_player(scr);
            SaveState(10);
            //New_player(scr);
        }


        if (input_GetState(Ki_R))
        {
            Save_Menu(scr);
            //SaveState(10);
            //New_player(scr);
        }

        //Global_Draw_Game_scrn(scr);

        for (uint8_t i=0; i<21;i++)
        {
            enemy_spodshet(i);
            sprintf(s_buf,"%s %d",EnemiesNames[i],EnemiesNumCards[i]);
            TextFF(150,10+i*10,s_buf,scr);
        }


        TextFF(10,10,pss,scr);





        if (input_GetState(Ki_SELECT))
        {
            done = true;
            gameend = true;
        };

        SDL_Flip(scr);
        #ifdef DINGOO
        SDL_Delay(2*fpsmul);
        #else
        SDL_Delay(1000/50);
        #endif*/

    }
    sys=NULL;
    done=true;
    return 0;
}



int8_t MSlot=0;
int8_t MSlot2=0;
bool MWhatS=true;


void MainCycle(SDL_Surface *scr)
{
    bool MainExit=false;
    bool vib=false;
    while (!MainExit)
    {
        DrawBkg(BKG_MENU,scr);
        xCreateWindow(10,24,200,200,scr);
        xCreateWindow(240,0,80,240,scr);
        DrawImage(Faces[vPlayer.Pl_v_Face],256,26,scr);
        CreateWindowText(105-GetFFWidth(GetLangString(0))/2,4,GetLangString(0),scr); //Выберите противника.

        for (uint8_t i=0; i<21; i++)
            TextFF(20,29+i*9,EnemiesNames[i],scr);

        CreateWindowText(280-(GetFFWidth(vPlayer.Pl_v_Name)+10)/2,0,vPlayer.Pl_v_Name,scr);
        DrawImage(Gil_img,245,80,scr);

        sprintf(s_buf,"%d",vPlayer.Pl_v_Gil);

        TextFF(255,80,s_buf,scr);
        TextFF(245,100,GetLangString(1),scr);//  ;йЮПРШ
        TextFF(245,110,GetLangString(2),scr);//лЮЦЮГХМ
        TextFF(245,120,GetLangString(3),scr);//"вРЕМХЕ"
        TextFF(245,130,GetLangString(4),scr);//гЮОХЯЭ
        TextFF(245,140,GetLangString(5),scr);//сДЮКЕМХЕ
        TextFF(245,150,GetLangString(6),scr);//бШУНД

        if (MWhatS)
        {
            DrawHand(5,30+MSlot*9,scr);

            if (input_GetState(Ki_UP))
            {
                MSlot--;
                SPU(sKlik2);
            }

            if (MSlot<0)
                MSlot=20;


            if (input_GetState(Ki_DOWN))
            {
                MSlot++;
                SPU(sKlik2);
            }

            if (MSlot>20)
                MSlot=0;


            if (input_GetState(Ki_RIGHT))
            {
                MWhatS=!MWhatS;
                SPU(sKlik2);
            }

            if (input_GetState(Ki_X))
            {
                WhoNow=MSlot;
                MainExit=true;
                NextScreen(scrSelect);
                SPU(sChif);
            }
        }
        else
        {
            DrawHand(230,101+MSlot2*10,scr);

            if (input_GetState(Ki_UP))
            {
                MSlot2--;
                SPU(sKlik2);
            }

            if (MSlot2<0)
                MSlot2=5;


            if (input_GetState(Ki_DOWN))
            {
                MSlot2++;
                SPU(sKlik2);
            }

            if (MSlot2>5)
                MSlot2=0;


            if (input_GetState(Ki_LEFT))
            {
                MWhatS=!MWhatS;
                SPU(sKlik2);
            }

            if (input_GetState(Ki_X))
            {
                SPU(sChif);
                switch (MSlot2)
                {
                case 0:   //CardList
                    NextScreen(scrSelect2);
                    MainExit=true;
                    break;

                case 1:  //Shop
                    NextScreen(scrShop);
                    MainExit=true;
                    break;

                case 2:  //LoadGame
                    NextScreen(scrLoad);
                    MainExit=true;
                    break;

                case 3:  //SaveGame
                    NextScreen(scrSave);
                    MainExit=true;
                    break;

                case 4:  //Delete Save
                    NextScreen(scrDel);
                    MainExit=true;
                    break;

                case 5:  //Exit?
                    if (DrawTrueOrNo2(GetLangString(7),scr)) //Вы действительно хотите выйти?
                    {
                        SPU(sChif);
                        EndGame();
                        MainExit=true;
                    }
                    else
                    {
                        SPU(sOtmen);
                    }
                }
            }
        }


        //;	If input_GetState("X") Then NextScreen(3) : MainExit=True
        //;	If input_GetState("O") Then NextScreen(7) : MainExit=True
        //;	If input_GetState("SQ") Then NextScreen(5) : MainExit=True
        //;	If input_GetState("TRI") Then NextScreen(8) : MainExit=True
        SDL_Flip(scr);//Flip2D()
    }
}



