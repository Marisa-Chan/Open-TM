struct anim_surf
{
    SDL_Surface *img;
    uint32_t    frames;
    uint32_t    fr_w;
//uint32_t    fr_h;
}__attribute__((packed));


SDL_Surface * IMG_Load2(SDL_Surface *scr,char *ss);

anim_surf * LoadAnimImage(SDL_Surface *scr,char *file,uint32_t fr_cnt);
void DrawAnimImage(anim_surf *srf, uint32_t x, uint32_t y,uint32_t frame, SDL_Surface * scr);
void DrawAAnimImage(anim_surf *srf, uint32_t x, uint32_t y,uint32_t frame,uint8_t a, SDL_Surface * scr);


void DeleteAnimImage(anim_surf *srf);
void DrawImage(SDL_Surface *srf, uint32_t x, uint32_t y, SDL_Surface * scr);
void DrawAImage(SDL_Surface *srf, uint32_t x, uint32_t y,uint8_t a, SDL_Surface * scr);


void DrawStrelka(uint32_t x,uint32_t y,SDL_Surface * scr);
void DrawiStrelka(uint32_t x,uint32_t y,SDL_Surface * scr);


void DrawCard(uint8_t index,uint8_t color,uint32_t x,uint32_t y,uint8_t a,uint8_t at,uint8_t pd,uint8_t md,uint8_t Arr, SDL_Surface * scr);
void DrawCard2(card *crd, uint8_t color,uint32_t x,uint32_t y, SDL_Surface * scr);
void DrawArrows(uint8_t Arr,uint32_t x,uint32_t y, SDL_Surface * scr);
void DrawImageRect(SDL_Surface *img,int32_t x,int32_t y,uint32_t w,uint32_t h, SDL_Surface * scr);
void DrawImageARect(SDL_Surface *img,int32_t x,int32_t y,uint32_t w,uint32_t h,uint8_t a, SDL_Surface * scr);

void DrawCoin(SDL_Surface *scr);
void DrawCoinF(uint8_t Col,SDL_Surface *scr);

void xCreateWindow(int32_t x,int32_t y,uint32_t w,uint32_t h, SDL_Surface * scr);
void DrawHand(uint16_t x,uint16_t y,SDL_Surface * scr);



enum BKGs
{
    BKG_MENU,
    BKG_GAME,
    BKG_SEL,
    BKG_SAVE,
    BKG_LOAD,
    BKG_DEL,
    BKG_SHOP,
    BKG_CARDS
};


void DrawBkg(BKGs Index,SDL_Surface *scr);

void CreateWindowText(int32_t x,int32_t y,char *txt,SDL_Surface * scr);
bool DrawTrueOrNo(char *Txt,SDL_Surface * scr);
bool DrawTrueOrNo2(char *Txt,SDL_Surface * scr);
