#include "res.h"


uint8_t FxBlkBkgAlpha=255;
uint8_t Vibor=0;
bool intro_MayExit=false;





int8_t what=0;

void Intro_Screen(SDL_Surface * scr, bool gg)
{
    intro_MayExit=false;
    FxBlkBkgAlpha=255;

#ifdef DINGOO
    const uint8_t koe=6;
#else
    const uint8_t koe=2;
#endif


    if (gg) goto go_g;

//ClsColor(0,0,0)
    while (FxBlkBkgAlpha>0)
    {
        DrawImage(Intro_BKG,0,0,scr);
        DrawAImage(Blk_Bkg,0,0,FxBlkBkgAlpha,scr);
        FxBlkBkgAlpha-=koe;
        if (FxBlkBkgAlpha<koe)
            FxBlkBkgAlpha=0;

        SDL_Flip(scr);//Flip2D()
        #ifndef DINGOO
        SDL_Delay(10);
        #endif

    }// ;SquareSoft ++
    SDL_Delay(3000);
    FxBlkBkgAlpha=0;
    while (FxBlkBkgAlpha<255)
    {
        DrawImage(Intro_BKG,0,0,scr);
        DrawAImage(Blk_Bkg,0,0,FxBlkBkgAlpha,scr);
        FxBlkBkgAlpha+=koe;
        if (FxBlkBkgAlpha>255-koe)
            FxBlkBkgAlpha=255;

        SDL_Flip(scr);//Flip2D()
        #ifndef DINGOO
        SDL_Delay(10);
        #endif

    }
    FxBlkBkgAlpha=255;
//ClsColor(0,0,0)
    while (FxBlkBkgAlpha>0)
    {
        DrawImage(SquareBkg,0,0,scr);
        DrawAImage(Blk_Bkg,0,0,FxBlkBkgAlpha,scr);
        FxBlkBkgAlpha-=koe;
        if (FxBlkBkgAlpha<koe)
            FxBlkBkgAlpha=0;

        SDL_Flip(scr);//Flip2D()
        #ifndef DINGOO
        SDL_Delay(10);
        #endif

    }// ;SquareSoft ++
    SDL_Delay(1000);
    FxBlkBkgAlpha=0;
    while (FxBlkBkgAlpha<255)
    {
        DrawImage(SquareBkg,0,0,scr);
        DrawAImage(Blk_Bkg,0,0,FxBlkBkgAlpha,scr);
        FxBlkBkgAlpha+=koe;
        if (FxBlkBkgAlpha>255-koe)
            FxBlkBkgAlpha=255;

        SDL_Flip(scr);//Flip2D()
        #ifndef DINGOO
        SDL_Delay(10);
        #endif

    }
    FxBlkBkgAlpha=255;
//ClsColor(0,0,0)
    while (FxBlkBkgAlpha>0)
    {
        DrawImage(ZidaneBkg,0,0,scr);
        DrawAImage(Blk_Bkg,0,0,FxBlkBkgAlpha,scr);
        FxBlkBkgAlpha-=koe;
        if (FxBlkBkgAlpha<koe)
            FxBlkBkgAlpha=0;

        SDL_Flip(scr);//Flip2D()
        #ifndef DINGOO
        SDL_Delay(10);
        #endif

    }// ;SquareSoft ++
    SDL_Delay(1000);
    FxBlkBkgAlpha=0;
    while (FxBlkBkgAlpha<255)
    {
        DrawImage(ZidaneBkg,0,0,scr);
        DrawAImage(Blk_Bkg,0,0,FxBlkBkgAlpha,scr);
        FxBlkBkgAlpha+=koe;
        if (FxBlkBkgAlpha>255-koe)
            FxBlkBkgAlpha=255;

        SDL_Flip(scr);//Flip2D()
        #ifndef DINGOO
        SDL_Delay(10);
        #endif

    }

    FxBlkBkgAlpha=255;
//ClsColor(0,0,0)
    while (FxBlkBkgAlpha>0)
    {
        DrawImage(FFIXBkg,0,0,scr);
        DrawAImage(Blk_Bkg,0,0,FxBlkBkgAlpha,scr);
        FxBlkBkgAlpha-=koe;
        if (FxBlkBkgAlpha<koe)
            FxBlkBkgAlpha=0;

        SDL_Flip(scr);//Flip2D()
        #ifndef DINGOO
        SDL_Delay(10);
        #endif

    }// ;SquareSoft ++

go_g:

    while (!intro_MayExit)
    {
        DrawImage(FFIXBkg,0,0,scr);
        DrawImage(NewGame_img,124,141,scr);
        DrawImage(Continue_img,123,158,scr);
        DrawImage(Sq_img,119,210,scr);
        DrawImage(Hand,95,143+what*18,scr);

        if (input_GetState(Ki_DOWN))
        {
            what++;
            SPU(sKlik);
            if (what>1)
                what=0;
        }

        if (input_GetState(Ki_UP))
        {
            what--;
            SPU(sKlik);
            if (what<0)
                what=1;
        }

        if (input_GetState(Ki_X))
        {
            intro_MayExit=true;
            SPU(sKlik);
        }

        if (input_GetState(Ki_SELECT))
        {
            intro_MayExit=true;
            SPU(sKlik);
            EndGame();
        }


//If KeyHit(1) Then Global_Exit=True : intro_MayExit=True
//TextFF(315-GetFFWidth("Ver: "+GVer),227,"Ver: "+GVer)
        SDL_Flip(scr);

    }

    FxBlkBkgAlpha=0;
    while (FxBlkBkgAlpha<255)
    {
        DrawImage(FFIXBkg,0,0,scr);
        DrawAImage(Blk_Bkg,0,0,FxBlkBkgAlpha,scr);
        FxBlkBkgAlpha+=koe;
        if (FxBlkBkgAlpha>255-koe)
            FxBlkBkgAlpha=255;
        SDL_Flip(scr);
        #ifndef DINGOO
        SDL_Delay(10);
        #endif
    }


    if (what==0)
        NextScreen(scrNew);
    else
        NextScreen(scrLoad);

}
