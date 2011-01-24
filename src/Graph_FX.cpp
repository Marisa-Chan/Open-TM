#include "res.h"


SDL_Surface * IMG_Load2(SDL_Surface *scr,char *ss)
{
    SDL_Surface *tmp=IMG_Load(ss);
    SDL_Surface *tmp2=SDL_ConvertSurface(tmp,scr->format,0);
    SDL_FreeSurface(tmp);
    return tmp2;
}

anim_surf * LoadAnimImage(SDL_Surface *scr,char *file,uint32_t fr_cnt)
{
    anim_surf * im;
    im=new (anim_surf);
    im->img=IMG_Load2(scr,file);
    im->fr_w=im->img->w / fr_cnt;
    im->frames=fr_cnt;

//img->frames=fr_cnt;
    return im;
}

void DrawAnimImage(anim_surf *srf, uint32_t x, uint32_t y,uint32_t frame, SDL_Surface * scr)
{
    SDL_Rect rect,rect2;
    rect.x=x;
    rect.y=y;

    rect2.y=0;
    rect2.h=srf->img->h;
    rect2.x=frame * srf->fr_w;
    rect2.w=srf->fr_w;

    SDL_BlitSurface(srf->img,&rect2,scr,&rect);
}

void DrawAAnimImage(anim_surf *srf, uint32_t x, uint32_t y,uint32_t frame,uint8_t a, SDL_Surface * scr)
{
    SDL_Rect rect,rect2;
    rect.x=x;
    rect.y=y;

    rect2.y=0;
    rect2.h=srf->img->h;
    rect2.x=frame * srf->fr_w;
    rect2.w=srf->fr_w;

    SDL_SetAlpha(srf->img,SDL_SRCALPHA | SDL_RLEACCEL ,a);
    SDL_BlitSurface(srf->img,&rect2,scr,&rect);
    SDL_SetAlpha(srf->img,0 ,255);
}

void DeleteAnimImage(anim_surf *srf)
{
    SDL_FreeSurface(srf->img);
    delete srf;
}


void DrawImage(SDL_Surface *srf, uint32_t x, uint32_t y, SDL_Surface * scr)
{
    SDL_Rect rect;
    rect.x=x;
    rect.y=y;

    SDL_BlitSurface(srf,0,scr,&rect);
}

void DrawAImage(SDL_Surface *srf, uint32_t x, uint32_t y,uint8_t a, SDL_Surface * scr)
{
    SDL_Rect rect;
    rect.x=x;
    rect.y=y;

    SDL_SetAlpha(srf,SDL_SRCALPHA| SDL_RLEACCEL,a);
    SDL_BlitSurface(srf,0,scr,&rect);
    SDL_SetAlpha(srf,0 ,255);
}


void DrawCard(uint8_t index,uint8_t color,uint32_t x,uint32_t y,uint8_t a,uint8_t at,uint8_t pd,uint8_t md,uint8_t Arr, SDL_Surface * scr)
{
    switch (color)
    {
    case 0:
        DrawImage(blRobe,x,y,scr);
        break;
    case 1:
        DrawImage(rdRobe,x,y,scr);
    }

    DrawImage(Card_imgs[index],x,y,scr);

    DrawAnimImage(cardLetters,x+10,y+39,a,scr);
    if (at!=3)
        DrawAnimImage(cardLetters,x+16,y+39,at+16,scr);
    else
        DrawAnimImage(cardLetters,x+16,y+39,10,scr);

    DrawAnimImage(cardLetters,x+22,y+39,pd,scr);
    DrawAnimImage(cardLetters,x+28,y+39,md,scr);
    DrawArrows(Arr,x,y,scr);
}


void DrawCard2(card *crd, uint8_t color,uint32_t x,uint32_t y, SDL_Surface * scr)
{
    switch (color)
    {
    case 0:
        DrawImage(blRobe,x,y,scr);
        break;
    case 1:
        DrawImage(rdRobe,x,y,scr);
    }

    DrawImage(Card_imgs[crd->Number],x,y,scr);

    DrawAnimImage(cardLetters,x+10,y+39,crd->Attack,scr);
    if (crd->Atype!=3)
        DrawAnimImage(cardLetters,x+16,y+39,crd->Atype+16,scr);
    else
        DrawAnimImage(cardLetters,x+16,y+39,10,scr);

    DrawAnimImage(cardLetters,x+22,y+39,crd->PDefence,scr);
    DrawAnimImage(cardLetters,x+28,y+39,crd->MDefence,scr);
    DrawArrows(crd->Arr,x,y,scr);
}

void DrawArrows(uint8_t Arr,uint32_t x,uint32_t y, SDL_Surface * scr)
{
    if (Arr & 1) DrawAnimImage(Arrows,x,y+1,0,scr);
    if ((Arr >>1) & 1) DrawAnimImage(Arrows,x+17,y,1,scr);
    if ((Arr >>2) & 1) DrawAnimImage(Arrows,x+34,y+1,2,scr);
    if ((Arr >>3) & 1) DrawAnimImage(Arrows,x+35,y+21,3,scr);
    if ((Arr >>4) & 1) DrawAnimImage(Arrows,x+34,y+44,4,scr);
    if ((Arr >>5) & 1) DrawAnimImage(Arrows,x+17,y+45,5,scr);
    if ((Arr >>6) & 1) DrawAnimImage(Arrows,x,y+44,6,scr);
    if ((Arr >>7) & 1) DrawAnimImage(Arrows,x-1,y+21,7,scr);
}

void DrawImageRect(SDL_Surface *img,int32_t x,int32_t y,uint32_t w,uint32_t h, SDL_Surface * scr)
{
    SDL_Rect rect,rect2;
    rect.y=y;
    rect2.x=0;
    rect2.y=0;
    int32_t wx=(((int32_t)w)+x);
    int32_t hy=(((int32_t)h)+y);
    while (rect.y<hy)
    {
        rect.x=x;
        while (rect.x<wx)
        {

            rect2.w=wx-rect.x;
            rect2.h=hy-rect.y;


            if (rect.x>0 && rect.y>0)
                SDL_BlitSurface(img,&rect2,scr,&rect);
            else if (rect.x>(int32_t)-img->w && rect.y>(int32_t)-img->h)
            {
                int32_t tmpx,tmpy;
                tmpx=rect.x;
                tmpy=rect.y;
                if (rect.x<0)
                {
                    rect.x=0;
                    rect2.x=-tmpx;
                    rect2.w+=tmpx;
                }
                if (rect.y<0)
                {
                    rect.y=0;
                    rect2.y=-tmpy;
                    rect2.h+=tmpy;
                }
                SDL_BlitSurface(img,&rect2,scr,&rect);
                rect.x=tmpx;
                rect.y=tmpy;
                rect2.x=0;
                rect2.y=0;

            }
            //SDL_UpdateRects()
            rect.x+=img->w;

        }
        rect.y+=img->h;
    }
}


void DrawImageARect(SDL_Surface *img,int32_t x,int32_t y,uint32_t w,uint32_t h,uint8_t a, SDL_Surface * scr)
{
    SDL_SetAlpha(img,SDL_SRCALPHA ,a);
    DrawImageRect(img,x,y,w,h,scr);
    SDL_SetAlpha(img,0 ,255);
}


void xCreateWindow(int32_t x,int32_t y,uint32_t w,uint32_t h, SDL_Surface * scr)
{
    DrawImageRect(GuiBkg,x+3,y+3,w-6,h-6,scr);
    DrawImageRect(GuiGor,x+12,y,w-24,4,scr);
    DrawImageRect(GuiGor2,x+12,y+h-4,w-24,4,scr);
    DrawImageRect(GuiVert,x,y+12,4,h-24,scr);
    DrawImageRect(GuiVert2,x+w-4,y+12,4,h-24,scr);
    DrawAnimImage(GuiCorner,x,y,0,scr);
    DrawAnimImage(GuiCorner,x+w-12,y,1,scr);
    DrawAnimImage(GuiCorner,x,y+h-12,2,scr);
    DrawAnimImage(GuiCorner,x+w-12,y+h-12,3,scr);
}


void DrawHand(uint16_t x,uint16_t y,SDL_Surface * scr)
{
    DrawImage(Hand,x,y,scr);
}



void CreateWindowText(int32_t x,int32_t y,char *txt,SDL_Surface * scr)
{
    xCreateWindow(x,y,GetFFWidth(txt)+10,20,scr);
    TextFF(x+5,y+5,txt,scr);
}

bool DrawTrueOrNo(char *Txt,SDL_Surface * scr)
{
    bool vib=false;
    while (!input_GetState(Ki_X))
    {
        if (input_GetState(Ki_LEFT) || input_GetState(Ki_RIGHT))
        {
            vib=!vib;
            SPU(sChif);
        }

        CreateWindowText(160-(GetFFWidth(Txt)+10)/2,110,Txt,scr);
        CreateWindowText(120-(GetFFWidth("OK")+10)/2,140,"OK",scr);
        CreateWindowText(180-(GetFFWidth(GetLangString(8))+10)/2,140,GetLangString(8),scr); //Cancel
        if (vib)
        {
            rectangleRGBA(scr,122-(GetFFWidth("OK")+10)/2,142,122-(GetFFWidth("OK")+10)/2+18,142+14,255,0,0,255);
        }
        else
        {
            rectangleRGBA(scr,182-(GetFFWidth(GetLangString(8))+10)/2,142,182-(GetFFWidth(GetLangString(8))+10)/2+47,142+14,255,0,0,255); //Cancel
        }
        SDL_Flip(scr);
    }
    return vib;
}

bool DrawTrueOrNo2(char *Txt,SDL_Surface * scr)
{
    bool vib=false;
    bool localexit=false;
    while (!localexit)
    {
        if (input_GetState(Ki_X))
        {
            localexit=true;
        }
        if (input_GetState(Ki_O))
        {
            localexit=true;
            vib=false;
        }

        if (input_GetState(Ki_UP) || input_GetState(Ki_DOWN))
        {
            vib=!vib;
            SPU(sChif);
        }
        if ((GetFFWidth(Txt)+20)>100)
        {
            xCreateWindow(160-(GetFFWidth(Txt)+20)/2,83,GetFFWidth(Txt)+20,57,scr);
        }
        else
        {
            xCreateWindow(110,83,100,57,scr);
        }
        TextFF(170-(GetFFWidth(Txt)+20)/2,94,Txt,scr);
        TextFF(133,109,GetLangString(9),scr);  //Да
        TextFF(133,124,GetLangString(10),scr);  //нет

        if (vib)
            DrawHand(115,109,scr);
        else
            DrawHand(115,124,scr);

        SDL_Flip(scr);
    }
    return vib;
}


void DrawBkg(BKGs Index,SDL_Surface *scr)
{

    switch (Index)
    {
    case 0:
        DrawImage(BackGround,0,0,scr);
        break;
    case 1:
        SDL_FillRect(scr, 0, SDL_MapRGB(scr->format, 0, 0, 0));
        DrawImage(BackGround2,47,0,scr);
        break;
    case 2:
        DrawImage(Select_Bkg,0,0,scr);
        break;
    case 3:
        DrawImage(Save_Bkg,0,0,scr);
        break;
    case 4:
        DrawImage(Load_Bkg,0,0,scr);
        break;
    case 5:
        DrawImage(Delete_Bkg,0,0,scr);
        break;
    case 6:
        DrawImage(Shop_Bkg,0,0,scr);
        break;
    case 7:
        DrawImage(Cards_BKG,0,0,scr);
    }

}


uint32_t Coint=0;
uint32_t CCoint=0;


void DrawCoin(SDL_Surface *scr)
{
    if (millisec()>CCoint+10)
    {
        Coint++;
        CCoint=millisec();
    }
    if (Coint>7) Coint=0;
    DrawImage(Coin[Coint],137,92,scr);
}

void DrawCoinF(uint8_t Col,SDL_Surface *scr)
{
    switch (Col)
    {
    case 0:
        DrawImage(Coin[0],137,92,scr);
        break;
    case 1:
        DrawImage(Coin[4],137,92,scr);
        break;
    }
}


uint32_t aStrelkat=0;
uint32_t aStrelkaI=0;

void DrawStrelka(uint32_t x,uint32_t y,SDL_Surface * scr)
{
    if (millisec()>aStrelkat+100)
    {
        aStrelkaI++;
        aStrelkaI%=8;
        aStrelkat=millisec();
    }

    DrawAnimImage(aStrelka,x,y,aStrelkaI,scr);
}

void DrawiStrelka(uint32_t x,uint32_t y,SDL_Surface * scr)
{
    if (millisec()>aStrelkat+100)
    {
        aStrelkaI++;
        aStrelkaI%=8;
        aStrelkat=millisec();
    }

    DrawAnimImage(iStrelka,x,y,aStrelkaI,scr);
}
