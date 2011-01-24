#define RES_H_INCLUDED

#include "res.h"



//SDL_Surface *Card_imgs[100];



uint8_t DrawScreen=0;
uint8_t PrevScreen=0;
void NextScreen(uint8_t Screen)
{
	PrevScreen=DrawScreen;
	DrawScreen=Screen;
}

uint8_t getPrevScreen()
{
    return PrevScreen;
}

uint8_t getDrawScreen()
{
    return DrawScreen;
}



int Load_Game_Resources(SDL_Surface *scr)
{

    for (int i=0;i<100;i++)
    {
        char ss[255];
        memset(ss,0,255);
        sprintf(ss,"./GraphiX/Cards/Card_%d.bmp",i+1);
        Card_imgs[i]=IMG_Load2(scr,ss);
        SDL_SetColorKey(Card_imgs[i],SDL_SRCCOLORKEY | SDL_RLEACCEL ,SDL_MapRGB(scr->format,0,0,0));
    };

    for (int i=0;i<8;i++)
    {
        char ss[255];
        memset(ss,0,255);
        sprintf(ss,"./GraphiX/Ex/Coin_%d.bmp",i);
        Coin[i]=IMG_Load2(scr,ss);
        SDL_SetColorKey(Coin[i],SDL_SRCCOLORKEY | SDL_RLEACCEL,SDL_MapRGB(scr->format,0,0,0));
    };

    blRobe=IMG_Load2(scr,"./GraphiX/Ex/BlRobe.bmp");
    SDL_SetColorKey(blRobe,SDL_SRCCOLORKEY | SDL_RLEACCEL,SDL_MapRGB(scr->format,0,0,0));
    rdRobe=IMG_Load2(scr,"./GraphiX/Ex/RdRobe.bmp");
    SDL_SetColorKey(rdRobe,SDL_SRCCOLORKEY | SDL_RLEACCEL,SDL_MapRGB(scr->format,0,0,0));
    blk_crd_img=IMG_Load2(scr,"./GraphiX/Ex/Blk_crd.bmp");
    wht_crd_img=IMG_Load2(scr,"./GraphiX/Ex/Wht_crd.bmp");
    enm_Card=IMG_Load2(scr,"./GraphiX/Ex/Robe.bmp");
    SDL_SetColorKey(enm_Card,SDL_SRCCOLORKEY | SDL_RLEACCEL,SDL_MapRGB(scr->format,0,0,0));

    Blockedcrd_1=IMG_Load2(scr,"./GraphiX/Ex/Block_1.bmp");
    SDL_SetColorKey(Blockedcrd_1,SDL_SRCCOLORKEY | SDL_RLEACCEL,SDL_MapRGB(scr->format,0,0,0));
    Blockedcrd_2=IMG_Load2(scr,"./GraphiX/Ex/Block_2.bmp");
    SDL_SetColorKey(Blockedcrd_2,SDL_SRCCOLORKEY | SDL_RLEACCEL,SDL_MapRGB(scr->format,0,0,0));

    for (uint8_t i=0;i<8;i++)
    {
        Blockedcrd_1_hlp[i]=zoomSurface(Blockedcrd_1,(1.5-0.0625*i),(1.5-0.0625*i),1);
        Blockedcrd_2_hlp[i]=zoomSurface(Blockedcrd_2,(1.5-0.0625*i),(1.5-0.0625*i),1);
    }

    for (uint8_t i=0;i<72;i++)
    {
        char ss[255];
        memset(ss,0,255);
        sprintf(ss,"./GraphiX/Player/%d.bmp",i);
        Faces[i]=IMG_Load2(scr,ss);
    }


    Boom_img=LoadAnimImage(scr,"./GraphiX/Ex/Boom.bmp",8);
    SDL_SetColorKey(Boom_img->img,SDL_SRCCOLORKEY | SDL_RLEACCEL,SDL_MapRGB(scr->format,0,0,0));



    Arrows=LoadAnimImage(scr,"./GraphiX/Ex/Arrows.bmp",8);
    SDL_SetColorKey(Arrows->img,SDL_SRCCOLORKEY | SDL_RLEACCEL,SDL_MapRGB(scr->format,0,0,0));
    whArrows=LoadAnimImage(scr,"./GraphiX/Ex/WhArrows.bmp",8);
    SDL_SetColorKey(whArrows->img,SDL_SRCCOLORKEY | SDL_RLEACCEL,SDL_MapRGB(scr->format,0,0,0));

    cardLetters=LoadAnimImage(scr,"./GraphiX/Ex/Card_Numb.bmp",19);
    SDL_SetColorKey(cardLetters->img,SDL_SRCCOLORKEY | SDL_RLEACCEL,SDL_MapRGB(scr->format,0,0,0));



    Slash_img=IMG_Load2(scr,"./GraphiX/Ex/Slash.bmp");
    SDL_SetColorKey(Slash_img,SDL_SRCCOLORKEY | SDL_RLEACCEL,SDL_MapRGB(scr->format,0,0,0));

    Slash_Red_Numbers=LoadAnimImage(scr,"./GraphiX/Ex/Red_0..9.bmp",10);
    SDL_SetColorKey(Slash_Red_Numbers->img,SDL_SRCCOLORKEY | SDL_RLEACCEL,SDL_MapRGB(scr->format,0,0,0));
    Slash_Blue_Numbers=LoadAnimImage(scr,"./GraphiX/Ex/Blue_0..9.bmp",10);
    SDL_SetColorKey(Slash_Blue_Numbers->img,SDL_SRCCOLORKEY | SDL_RLEACCEL,SDL_MapRGB(scr->format,0,0,0));


    Card_ANumb=LoadAnimImage(scr,"./GraphiX/Ex/Card_ANumb.bmp",10);
    SDL_SetColorKey(Card_ANumb->img,SDL_SRCCOLORKEY | SDL_RLEACCEL,SDL_MapRGB(scr->format,0,0,0));


    GuiBkg=IMG_Load2(scr,"./GraphiX/Ex/Gui_Bkg.bmp");
    GuiCorner=LoadAnimImage(scr,"./GraphiX/Ex/Gui_Corner.bmp",4);
    SDL_SetColorKey(GuiCorner->img,SDL_SRCCOLORKEY | SDL_RLEACCEL,SDL_MapRGB(scr->format,0,0,0));
    GuiGor=IMG_Load2(scr,"./GraphiX/Ex/Gui_Gor.bmp");
    GuiGor2=IMG_Load2(scr,"./GraphiX/Ex/Gui_Gor2.bmp");
    GuiVert=IMG_Load2(scr,"./GraphiX/Ex/Gui_Vert.bmp");
    GuiVert2=IMG_Load2(scr,"./GraphiX/Ex/Gui_Vert2.bmp");

    Combo=IMG_Load2(scr,"./GraphiX/Ex/Combo.bmp");
    SDL_SetColorKey(Combo,SDL_SRCCOLORKEY | SDL_RLEACCEL,SDL_MapRGB(scr->format,0,0,0));
    Combo_Numb=LoadAnimImage(scr,"./GraphiX/Ex/Combo_number.bmp",10);
    SDL_SetColorKey(Combo_Numb->img,SDL_SRCCOLORKEY | SDL_RLEACCEL,SDL_MapRGB(scr->format,0,0,0));

    #ifdef DINGOO
    Buttons_img=LoadAnimImage(scr,"./GraphiX/Ex/Buttons_dingoo.bmp",6);
    #else
    Buttons_img=LoadAnimImage(scr,"./GraphiX/Ex/Buttons_ps.bmp",6);
    #endif
    SDL_SetColorKey(Buttons_img->img,SDL_SRCCOLORKEY | SDL_RLEACCEL,SDL_MapRGB(scr->format,0,0,0));







    aStrelka=LoadAnimImage(scr,"./GraphiX/Ex/Strelka.bmp",8);
    SDL_SetColorKey(aStrelka->img,SDL_SRCCOLORKEY | SDL_RLEACCEL,SDL_MapRGB(scr->format,0,0,0));
    iStrelka=LoadAnimImage(scr,"./GraphiX/Ex/iStrelka.bmp",8);
    SDL_SetColorKey(iStrelka->img,SDL_SRCCOLORKEY | SDL_RLEACCEL,SDL_MapRGB(scr->format,0,0,0));


    Select_img=IMG_Load2(scr,"./GraphiX/Ex/PSelect.bmp");
    SDL_SetColorKey(Select_img,SDL_SRCCOLORKEY | SDL_RLEACCEL,SDL_MapRGB(scr->format,0,0,0));


    Hand=IMG_Load2(scr,"./GraphiX/Ex/Hand.bmp");
    SDL_SetColorKey(Hand,SDL_SRCCOLORKEY | SDL_RLEACCEL,SDL_MapRGB(scr->format,0,0,0));


///////////BGK///////////
    BackGround=IMG_Load2(scr,"./GraphiX/BKG/STR0121.bmp");
    BackGround2=IMG_Load2(scr,"./GraphiX/BKG/STR0122.bmp");
    SquareBkg=IMG_Load2(scr,"./GraphiX/BKG/SquareSoft.bmp");
    ZidaneBkg=IMG_Load2(scr,"./GraphiX/BKG/ZidaneGames.bmp");
    FFIXBkg=IMG_Load2(scr,"./GraphiX/BKG/FinalFantasy.bmp");
    FFIXBkgTM=IMG_Load2(scr,"./GraphiX/BKG/FinalFantasy+Tetra_Master.bmp");
    Blk_Bkg=IMG_Load2(scr,"./GraphiX/BKG/Blk_Bkg.bmp");
    Wht_Bkg=IMG_Load2(scr,"./GraphiX/BKG/Wht_Bkg.bmp");
    Select_Bkg=IMG_Load2(scr,"./GraphiX/BKG/Select.bmp");
    Save_Bkg=IMG_Load2(scr,"./GraphiX/BKG/Save.bmp");
    Load_Bkg=IMG_Load2(scr,"./GraphiX/BKG/Load.bmp");
    Delete_Bkg=IMG_Load2(scr,"./GraphiX/BKG/Delete.bmp");
    Shop_Bkg=IMG_Load2(scr,"./GraphiX/BKG/Magazine.bmp");
    Cards_BKG=IMG_Load2(scr,"./GraphiX/BKG/Cards_BKG.bmp");
    Intro_BKG=IMG_Load2(scr,"./GraphiX/BKG/Intro.bmp");
    Name_BKG=IMG_Load2(scr,"./GraphiX/BKG/Name.bmp");



///////----BKG----/////////

    GlyphNumbers=LoadAnimImage(scr,"./GraphiX/Ex/Select_Numbers.bmp",8);
    SDL_SetColorKey(GlyphNumbers->img,SDL_SRCCOLORKEY | SDL_RLEACCEL,SDL_MapRGB(scr->format,0,0,0));


    Glyphx=LoadAnimImage(scr,"./GraphiX/Ex/Glyphx.bmp",14);
    SDL_SetColorKey(Glyphx->img,SDL_SRCCOLORKEY | SDL_RLEACCEL,SDL_MapRGB(scr->format,0,0,0));


    NewGame_img=IMG_Load2(scr,"./GraphiX/Ex/New.bmp");
    SDL_SetColorKey(NewGame_img,SDL_SRCCOLORKEY | SDL_RLEACCEL,SDL_MapRGB(scr->format,0,0,0));

    Continue_img=IMG_Load2(scr,"./GraphiX/Ex/Continue.bmp");
    SDL_SetColorKey(Continue_img,SDL_SRCCOLORKEY | SDL_RLEACCEL,SDL_MapRGB(scr->format,0,0,0));

    Sq_img=IMG_Load2(scr,"./GraphiX/Ex/SQuare2000.bmp");
    SDL_SetColorKey(Sq_img,SDL_SRCCOLORKEY | SDL_RLEACCEL,SDL_MapRGB(scr->format,0,0,0));


    ico_Card=IMG_Load2(scr,"./GraphiX/Ex/mini_cards.bmp");
    SDL_SetColorKey(ico_Card,SDL_SRCCOLORKEY | SDL_RLEACCEL,SDL_MapRGB(scr->format,0,0,0));


    S_L_Arrays = LoadAnimImage(scr,"./GraphiX/Ex/Arrays.bmp",4);
    SDL_SetColorKey(S_L_Arrays->img,SDL_SRCCOLORKEY | SDL_RLEACCEL,SDL_MapRGB(scr->format,0,0,0));

    Imia = IMG_Load2(scr,"./GraphiX/Ex/Imia.bmp");
    SDL_SetColorKey(Imia,SDL_SRCCOLORKEY | SDL_RLEACCEL,SDL_MapRGB(scr->format,0,0,0));



    ///// Init FONT
    Font = LoadAnimImage(scr,"./GraphiX/Ex/Symbols.bmp",95);
    SDL_SetColorKey(Font->img,SDL_SRCCOLORKEY | SDL_RLEACCEL,SDL_MapRGB(scr->format,0,0,0));

    CyrFont = LoadAnimImage(scr,"./GraphiX/Ex/Symbols2.bmp",64);
    SDL_SetColorKey(CyrFont->img,SDL_SRCCOLORKEY | SDL_RLEACCEL,SDL_MapRGB(scr->format,0,0,0));
    /////



    Win_Scrn_Game=IMG_Load2(scr,"./GraphiX/Ex/Win.bmp");
    SDL_SetColorKey(Win_Scrn_Game,SDL_SRCCOLORKEY | SDL_RLEACCEL,SDL_MapRGB(scr->format,0,0,0));

    Lose_Scrn_Game=IMG_Load2(scr,"./GraphiX/Ex/Lose.bmp");
    SDL_SetColorKey(Lose_Scrn_Game,SDL_SRCCOLORKEY | SDL_RLEACCEL,SDL_MapRGB(scr->format,0,0,0));

    Super_Scrn_Game=IMG_Load2(scr,"./GraphiX/Ex/Super.bmp");
    SDL_SetColorKey(Super_Scrn_Game,SDL_SRCCOLORKEY | SDL_RLEACCEL,SDL_MapRGB(scr->format,0,0,0));

    NoWho_Scrn_Game=IMG_Load2(scr,"./GraphiX/Ex/NoWho.bmp");
    SDL_SetColorKey(NoWho_Scrn_Game,SDL_SRCCOLORKEY | SDL_RLEACCEL,SDL_MapRGB(scr->format,0,0,0));


    NewCard=IMG_Load2(scr,"./GraphiX/Ex/New_Card.bmp");
    SDL_SetColorKey(NewCard,SDL_SRCCOLORKEY | SDL_RLEACCEL,SDL_MapRGB(scr->format,0,0,0));

    LastCard=IMG_Load2(scr,"./GraphiX/Ex/Last.bmp");
    SDL_SetColorKey(LastCard,SDL_SRCCOLORKEY | SDL_RLEACCEL,SDL_MapRGB(scr->format,0,0,0));


    Gil_img=IMG_Load2(scr,"./GraphiX/Ex/Gil.bmp");
    SDL_SetColorKey(Gil_img,SDL_SRCCOLORKEY | SDL_RLEACCEL,SDL_MapRGB(scr->format,0,0,0));


    return 0;
}
