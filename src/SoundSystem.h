



typedef enum
{
sBoom,
sBlock,
sBoth,
sCombo,
sChif,
sDrink,
sDzin,
sKlik,
sLose,
sMonetka,
sWin,
sKlik2,
sOtmen,
sSuper,
sBlocker
} sounds;


extern int8_t CurrentMusic;
extern bool ExtendMusic;


void SPU(sounds Index);
void LoadSounds();
void InitMusic();
void spuMusic(uint8_t ind);
