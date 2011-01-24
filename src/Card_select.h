

uint8_t selGetX(uint8_t Number);
uint8_t selGetY(uint8_t Number);


void ScreenSelectCard(SDL_Surface * scr);

void DrawCrdPlot(SDL_Surface *scr);
void DrawCrdPlot2(SDL_Surface *scr);

void SelScrn_PrintLet(uint16_t x,uint16_t y,uint8_t Str,SDL_Surface * scr);
uint8_t SelScrn_GetWidth(uint8_t Str);


void DrawGlyph(uint8_t x,uint8_t y,uint8_t Numb,uint8_t Col,SDL_Surface * scr);
void DrawGlyph2(uint8_t x,uint8_t y,uint8_t Numb,uint8_t Col,SDL_Surface * scr);

void ScreenSelectCard2(SDL_Surface *scr);



void ExSelect();

char *GetRang(uint32_t Level);
void Pereshet();

void HowManyCards();
void HowManyCardType();

extern uint32_t v_HMCardsType;
extern uint32_t v_HMCards;


extern card * CardGrid[10][10][50];
extern uint32_t nCardGrid[10][10];
