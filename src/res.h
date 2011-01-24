#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_rotozoom.h>
#include <SDL/SDL_audio.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <stdlib.h>
#include <strings.h>
#include <inttypes.h>
#include <time.h>
#include <math.h>
#include <vector>
#include <string>
#include <sys/file.h>

const uint32_t screen_w=320;
const uint32_t screen_h=240;




void NextScreen(uint8_t Screen);
uint8_t getPrevScreen();
uint8_t getDrawScreen();

void MainCycle(SDL_Surface *scr);

void EndGame();

int Load_Game_Resources(SDL_Surface *scr);




enum ScreenDS
{
    scrIntro=0,
    scrMain=1,
    scrInit=2,
    scrSelect=3,
    scrNew=4,
    scrLoad=5,
    scrIntro2=6,
    scrSave=7,
    scrDel=8,
    scrShop=9,
    scrSelect2=10
};


enum aType
{
    aT_P=0,
    aT_M=1,
    aT_X=2,
    aT_A=3
};

struct card
{
    uint8_t Number;
    uint8_t Attack;
    uint8_t PDefence;
    uint8_t MDefence;
    uint32_t Expirience;
    uint8_t Arr;
    uint8_t Atype;
} __attribute__((packed));


#include "Player.h"
#include "system.h"
#include "Graph_FX.h"
#include "FontSystem.h"
#include "Lang.h"
#include "Enemies.h"
#include "Game.h"
#include "SoundSystem.h"
#include "Card_select.h"
#include "Intro.h"
#include "new_player.h"
#include "LoadSave.h"
#include "Magazine.h"



//using namespace std;

extern char s_buf[256];


///////Global Vars///////
#ifdef RES_H_INCLUDED





Player vPlayer;



SDL_Surface * Card_imgs[100];

SDL_Surface * blRobe;
SDL_Surface * rdRobe;
SDL_Surface * blk_crd_img;
SDL_Surface * wht_crd_img;
anim_surf * Arrows;
anim_surf * whArrows;
anim_surf * cardLetters;
SDL_Surface * enm_Card;
SDL_Surface * Blockedcrd_1;
SDL_Surface * Blockedcrd_1_hlp[8];
SDL_Surface * Blockedcrd_2;
SDL_Surface * Blockedcrd_2_hlp[8];

SDL_Surface *Slash_img;
anim_surf *Slash_Red_Numbers;
anim_surf *Slash_Blue_Numbers;

SDL_Surface *Coin[8];

SDL_Surface *Faces[72];


SDL_Surface * GuiBkg;
anim_surf * GuiCorner;
SDL_Surface * GuiGor;
SDL_Surface *GuiGor2;
SDL_Surface *GuiVert;
SDL_Surface *GuiVert2;

SDL_Surface *Select_img;

SDL_Surface *Imia;


///////BKG////////
SDL_Surface *BackGround;
SDL_Surface *BackGround2;
SDL_Surface *SquareBkg;
SDL_Surface *FFIXBkg;
SDL_Surface *FFIXBkgTM;
SDL_Surface *Blk_Bkg;
SDL_Surface *Wht_Bkg;
SDL_Surface *Select_Bkg;
SDL_Surface *Save_Bkg;
SDL_Surface *Load_Bkg;
SDL_Surface *Delete_Bkg;
SDL_Surface *Shop_Bkg;
SDL_Surface *Cards_BKG;
SDL_Surface *Intro_BKG;
SDL_Surface *ZidaneBkg;
SDL_Surface *Name_BKG;

SDL_Surface *Combo;
anim_surf *Combo_Numb;

anim_surf *Buttons_img;

SDL_Surface *Hand;

SDL_Surface *Gil_img;

/////--BKG--//////

anim_surf *Glyphx;//
anim_surf *GlyphNumbers;


/////////////////SFX///////////////
Mix_Chunk *Win_snd;
Mix_Chunk *Lose_snd;
Mix_Chunk *Both_snd;
Mix_Chunk *Chif_snd;
Mix_Chunk *Boom_snd;
Mix_Chunk *Block_snd;
Mix_Chunk *Combo_snd;
Mix_Chunk *Drink_snd;
Mix_Chunk *Klik_snd;
Mix_Chunk *Monetka_snd;
Mix_Chunk *Dzin_snd;
Mix_Chunk *klik2_snd;
Mix_Chunk *Otmen_snd;
Mix_Chunk *Super_snd;
Mix_Chunk *Blocker_snd;
////---------------------------////

SDL_Surface *NewGame_img;
SDL_Surface *Continue_img;
SDL_Surface *Sq_img;


anim_surf * Font;
anim_surf * CyrFont;


anim_surf * aStrelka;
anim_surf * iStrelka;
anim_surf * Card_ANumb;

anim_surf * Boom_img;
anim_surf * S_L_Arrays;

SDL_Surface *ico_Card;

SDL_Surface *Win_Scrn_Game;
SDL_Surface *Lose_Scrn_Game;
SDL_Surface *Super_Scrn_Game;
SDL_Surface *NoWho_Scrn_Game;

SDL_Surface *NewCard;
SDL_Surface *LastCard;



#ifdef DINGOO
float fpsmul=0.1;
#else
float fpsmul=1.0;
#endif

uint32_t Kii=0;


uint8_t WhoNow=0;


std::vector <card *> playercards;



crd_pl MyCards[5]; // Массивы под карты не выложенные
crd_pl EnemyCards[5]; //
//св-во 0 :   0-неиспользована 1-использована
//св-во 1 -адрес



#else


extern Player vPlayer;



extern SDL_Surface * Card_imgs[100];

extern SDL_Surface * blRobe;
extern SDL_Surface * rdRobe;
extern anim_surf * Arrows;
extern anim_surf * whArrows;
extern anim_surf * cardLetters;
extern SDL_Surface * enm_Card;
extern SDL_Surface * Blockedcrd_1;
extern SDL_Surface * Blockedcrd_1_hlp[8];
extern SDL_Surface * Blockedcrd_2;
extern SDL_Surface * Blockedcrd_2_hlp[8];

extern SDL_Surface *Slash_img;
extern anim_surf *Slash_Red_Numbers;
extern anim_surf *Slash_Blue_Numbers;

extern SDL_Surface *Coin[8];

extern SDL_Surface * wht_crd_img;





extern SDL_Surface * GuiBkg;
extern anim_surf * GuiCorner;
extern SDL_Surface * GuiGor;
extern SDL_Surface *GuiGor2;
extern SDL_Surface *GuiVert;
extern SDL_Surface *GuiVert2;

extern SDL_Surface *Select_img;


///////BKG////////
extern SDL_Surface *BackGround;
extern SDL_Surface *BackGround2;
extern SDL_Surface *SquareBkg;
extern SDL_Surface *FFIXBkg;
extern SDL_Surface *FFIXBkgTM;
extern SDL_Surface *Blk_Bkg;
extern SDL_Surface *Wht_Bkg;
extern SDL_Surface *Select_Bkg;
extern SDL_Surface *Save_Bkg;
extern SDL_Surface *Load_Bkg;
extern SDL_Surface *Delete_Bkg;
extern SDL_Surface *Shop_Bkg;
extern SDL_Surface *Cards_BKG;
extern SDL_Surface *Intro_BKG;
extern SDL_Surface *ZidaneBkg;
extern SDL_Surface *Name_BKG;

extern SDL_Surface * blk_crd_img;


extern SDL_Surface *Combo;
extern anim_surf   *Combo_Numb;

extern anim_surf *Buttons_img;

/////--BKG--//////

extern SDL_Surface *Gil_img;

extern anim_surf *Glyphx;



/////////////////SFX///////////////
extern Mix_Chunk *Win_snd;
extern Mix_Chunk *Lose_snd;
extern Mix_Chunk *Both_snd;
extern Mix_Chunk *Chif_snd;
extern Mix_Chunk *Boom_snd;
extern Mix_Chunk *Block_snd;
extern Mix_Chunk *Combo_snd;
extern Mix_Chunk *Drink_snd;
extern Mix_Chunk *Klik_snd;
extern Mix_Chunk *Monetka_snd;
extern Mix_Chunk *Dzin_snd;
extern Mix_Chunk *klik2_snd;
extern Mix_Chunk *Otmen_snd;
extern Mix_Chunk *Super_snd;
extern Mix_Chunk *Blocker_snd;
////---------------------------////



extern anim_surf * Font;
extern anim_surf * CyrFont;

extern anim_surf * aStrelka;
extern anim_surf * iStrelka;

extern anim_surf * Card_ANumb;

extern anim_surf * Boom_img;
extern anim_surf *GlyphNumbers;

extern SDL_Surface *Hand;

extern SDL_Surface *Faces[72];

extern SDL_Surface *Imia;


extern float fpsmul;
extern uint32_t Kii;

extern SDL_Surface *NewGame_img;
extern SDL_Surface *Continue_img;
extern SDL_Surface *Sq_img;


extern std::vector <card *> playercards;

extern crd_pl MyCards[5]; // Массивы под карты не выложенные
extern crd_pl EnemyCards[5]; //


extern SDL_Surface *ico_Card;

extern anim_surf * S_L_Arrays;

extern uint8_t WhoNow;


extern SDL_Surface *Win_Scrn_Game;
extern SDL_Surface *Lose_Scrn_Game;
extern SDL_Surface *Super_Scrn_Game;
extern SDL_Surface *NoWho_Scrn_Game;

extern SDL_Surface *NewCard;
extern SDL_Surface *LastCard;


#endif // RES_H_INCLUDED


const uint8_t defAtack[100]={0,0,0,0,0,1,1,1,1,1,1,1,1,1,2,2,1,2,2,2,2,2,1,2,2,2,2,3,3,3,3,2,3,\
                              3,3,2,3,4,4,4,4,4,4,5,4,3,3,3,4,3,5,6,8,9,10,12,6,7,8,3,3,3,3,9,8,\
                              9,10,7,8,7,10,10,7,3,9,0,0,1,0,1,5,3,6,2,5,8,1,10,0,1,1,0,1,0,0,5,\
                              2,6,7,7};

const uint8_t defAType[100]={aT_P,aT_P,aT_P,aT_M,aT_P,aT_P,aT_P,aT_M,aT_P,aT_P,aT_M,aT_M,aT_M,aT_M,aT_P,\
                              aT_P,aT_M,aT_P,aT_P,aT_P,aT_M,aT_P,aT_P,aT_P,aT_M,aT_M,aT_M,aT_P,aT_P,aT_P,\
                              aT_P,aT_P,aT_M,aT_P,aT_M,aT_P,aT_M,aT_M,aT_P,aT_M,aT_M,aT_M,aT_M,aT_M,aT_M,\
                              aT_P,aT_M,aT_M,aT_M,aT_M,aT_M,aT_P,aT_P,aT_P,aT_M,aT_M,aT_M,aT_M,aT_M,aT_M,\
                              aT_M,aT_M,aT_M,aT_M,aT_M,aT_M,aT_M,aT_M,aT_M,aT_M,aT_P,aT_P,aT_P,aT_M,aT_M,\
                              aT_M,aT_P,aT_P,aT_P,aT_P,aT_P,aT_P,aT_P,aT_P,aT_P,aT_P,aT_P,aT_P,aT_P,aT_P,\
                              aT_M,aT_P,aT_P,aT_P,aT_P,aT_M,aT_P,aT_M,aT_P,aT_P};

const uint8_t defPDef[100]={0,0,0,0,0,0,1,1,1,0,0,1,0,0,0,2,0,2,0,2,1,2,2,3,1,2,1,2,2,2,4,2,1,3,\
                             2,2,1,0,4,1,2,4,3,3,1,3,1,3,3,12,4,3,5,4,0,12,2,5,1,0,7,1,5,5,6,9,3,\
                             2,1,11,9,1,6,6,2,10,0,3,5,0,7,3,7,3,4,0,4,7,0,1,0,0,1,9,3,4,0,7,7,6};

const uint8_t defMDef[100]={0,0,0,1,0,0,0,1,0,0,1,1,1,2,2,1,2,0,1,1,1,0,1,0,1,1,2,0,1,1,1,2,4,0,\
                             2,3,2,4,1,3,2,0,2,2,2,2,8,2,5,0,1,6,0,9,9,1,3,0,1,4,0,5,6,3,1,4,3,\
                             1,5,3,0,6,3,3,7,9,1,0,5,0,1,0,9,0,0,8,0,1,0,1,0,0,0,4,7,5,3,5,6,7};


