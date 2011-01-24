

struct Pole{
    uint8_t tip;
    card * crd;
    uint8_t wse;
    uint8_t slot;
} __attribute__ ((packed));

struct crd_pl{
    bool used;
    card * crd;
}   __attribute__((packed));


struct crd_end_pl{
    uint8_t cl;
    card * crd;
}   __attribute__((packed));



void DrawEndCards(SDL_Surface *scr);
void FinPereMesh(SDL_Surface *scr);
void Finalize_Game(SDL_Surface *scr);
void DrawEPERem(SDL_Surface *scr);

void FromEnemy(uint8_t slot,bool vse,SDL_Surface *scr);
void FromPlayer(uint8_t slot,bool vse,SDL_Surface *scr);


void Make_Select(uint8_t indx,SDL_Surface *scr);


void DrawPlayerCards(SDL_Surface *scr);
void DrawPlayercardsGrayed(uint8_t Crome,SDL_Surface *scr);
void DrawEnemyCards(SDL_Surface *scr);

void DrawPolyCards(SDL_Surface *scr);//Рисуем Поле со всеми картами.

void AddCardToPlayer2(card *crd);

void Global_Draw_Game_scrn(SDL_Surface *scr); //Рисуем задник и все все все. Чтобы не писать много раз.

void RandomBlocked(SDL_Surface *scr); //Заполняем поле блокираторами от 0 до 6 штук


void Draw_Skolko_Kakogo(SDL_Surface *scr);
void DrawSlash(SDL_Surface *scr);
void Skolko_Kakogo();//Подсчитываем сколько чьих карт.




void DrawGame_LocalScreen(SDL_Surface *scr);
void Draw_Vibor_Grayed(SDL_Surface *scr);

void DrawCARDasd(uint8_t x,uint8_t y,uint8_t i,uint8_t frame,SDL_Surface *scr);

void Draw_COMBOL(SDL_Surface * scr);

void DeleteSpisk(uint8_t i);
void DrawOnCardsNumb(uint8_t x,uint8_t y,uint8_t Numb,SDL_Surface *scr); //;Рисуем числа на картах(атака или защита)

void DrawBoom(uint32_t x,uint32_t y,SDL_Surface *scr);

uint8_t Fight(uint32_t  x,uint32_t  y,uint8_t x2,uint8_t y2,SDL_Surface * scr);
void skolko(uint8_t x,uint8_t y);
void GoFight(uint8_t x,uint8_t y,uint8_t Who,SDL_Surface * scr); //;Пошел на сражение.

void Bot_FindAndAttack();
void Func1();
void Func2();
bool Bot_Finking(SDL_Surface *scr);
void Bot_FindAndAttack(SDL_Surface *scr);
void Skolko(uint8_t x,uint8_t y);
void ClearObaSpiska();
//////
void Bot_PutItDefendedIfFirst(uint8_t slot,SDL_Surface * scr);
uint8_t Bot_FindDefencedCard();
uint8_t GetTypeElement(uint8_t x,uint8_t y,uint8_t z);
uint8_t GetXFromIndex(uint8_t x,uint8_t y,uint8_t z);
uint8_t GetYFromIndex(uint8_t x,uint8_t y,uint8_t z);
uint8_t InvertIndex(uint8_t z);
uint8_t FindMinDef(card * s);
uint8_t FindMinDef2(card * s);
/////

void ToWhite(uint32_t x,uint32_t y,SDL_Surface *scr); //Карту в белый
void ToWhite2(uint32_t x,uint32_t y,SDL_Surface *scr);// ; Карту в белый
void FromWhite(uint32_t x,uint32_t y,SDL_Surface *scr);// ;Карту из белого
void FromWhite2(uint32_t x,uint32_t y,SDL_Surface *scr);//;Карту из белого



void DrawCoinMove(uint8_t Who,SDL_Surface *scr); //;Рисуем перемещение монетки.
void RandomFirstTurn(SDL_Surface *scr); //; Первый ход чей?


void InBOOMCARDS(uint8_t x,uint8_t y,uint8_t x2,uint8_t y2,uint8_t Cadr,uint32_t ldx1,uint32_t ldx2,SDL_Surface *scr);

void delKilList();
void clearStrelList();

void Init_Game(SDL_Surface *scr); //;Инициализируем переменные игры, которые обязательны.
void ToFight(SDL_Surface *scr);


void FlushCards();
void ClearPole();


uint32_t LXtoSX(uint8_t x); //Из координат сетки в координаты экрана X
uint32_t LYtoSY(uint8_t y); //Из координат сетки в координаты экрана Y


void DeletePlayerCard(card * crd);

