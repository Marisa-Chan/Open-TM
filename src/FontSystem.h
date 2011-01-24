

void InitFonts();

uint32_t GetFFWidth(char *st);
uint32_t GetFFWidth_UTF(char *st);
void TextFF(uint32_t x, uint32_t y, char *st, SDL_Surface * scr);
void TextFF_UTF(uint32_t x, uint32_t y, char *st, SDL_Surface * scr);

char *GetCP1251(char *st);

