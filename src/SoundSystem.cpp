#include "res.h"


void SPU(sounds Index)
{
//Local lcp
//If SoundVol#>0 Then
//ChannelVolume lcp,SoundVol#
    switch (Index)
    {
    case sBoom:
        Mix_PlayChannel(1,Boom_snd,0);
        //lcp=PlaySound(Boom_snd)
        break;
    case sBlock:
        Mix_PlayChannel(1,Block_snd,0);
        //lcp=PlaySound(Block_snd)
        break;
    case sBoth:
        Mix_PlayChannel(1,Both_snd,0);
        //lcp=PlaySound(Both_snd)
        break;
    case sCombo:
        Mix_PlayChannel(1,Combo_snd,0);
        //lcp=PlaySound(Combo_snd)
        break;
    case sChif:
        Mix_PlayChannel(1,Chif_snd,0);
        //lcp=PlaySound(Chif_snd)
        break;
    case sDrink:
        Mix_PlayChannel(1,Drink_snd,0);
        //lcp=PlaySound(Drink_snd)
        break;
    case sDzin:
        Mix_PlayChannel(1,Dzin_snd,0);
        //lcp=PlaySound(Dzin_snd)
        break;
    case sKlik:
        Mix_PlayChannel(1,Klik_snd,0);
        //lcp=PlaySound(Klik_snd)
        break;
    case sLose:
        Mix_PlayChannel(1,Lose_snd,0);
        //lcp=PlaySound(Lose_snd)
        break;
    case sMonetka:
        Mix_PlayChannel(1,Monetka_snd,0);
        //lcp=PlaySound(Monetka_snd)
        break;
    case sWin:
        Mix_PlayChannel(1,Win_snd,0);
        //lcp=PlaySound(Win_snd)
        break;
    case sKlik2:
        Mix_PlayChannel(1,klik2_snd,0);
        //lcp=PlaySound(klik2_snd)
        break;
    case sOtmen:
        Mix_PlayChannel(1,Otmen_snd,0);
        //lcp=PlaySound(Otmen_snd)
        break;
    case sSuper:
        Mix_PlayChannel(1,Super_snd,0);
        //lcp=PlaySound(Super_snd)
        break;
    case sBlocker:
        Mix_PlayChannel(1,Blocker_snd,0);
        //lcp=PlaySound(Blocker_snd)
        break;
    }
//End Select
//ChannelVolume lcp,SoundVol#
//End If

}




void LoadSounds()
{
    Win_snd=Mix_LoadWAV("./sfx/Win.wav");
    Lose_snd=Mix_LoadWAV("./sfx/Lose.wav");
    Both_snd=Mix_LoadWAV("./sfx/Both.wav");
    Chif_snd=Mix_LoadWAV("./sfx/Chif.wav");
    Boom_snd=Mix_LoadWAV("./sfx/Boom.wav");
    Block_snd=Mix_LoadWAV("./sfx/Block.wav");
    Combo_snd=Mix_LoadWAV("./sfx/Combo.wav");
    Drink_snd=Mix_LoadWAV("./sfx/Drink.wav");
    Klik_snd=Mix_LoadWAV("./sfx/Klik.wav");
    Monetka_snd=Mix_LoadWAV("./sfx/Monetka.wav");
    Dzin_snd=Mix_LoadWAV("./sfx/Dzin.wav");
    klik2_snd=Mix_LoadWAV("./sfx/Klik2.wav");
    Otmen_snd=Mix_LoadWAV("./sfx/Otmen.wav");
    Super_snd=Mix_LoadWAV("./sfx/Super.wav");
    Blocker_snd=Mix_LoadWAV("./sfx/Blocker.wav");
}


Mix_Music *music = NULL;

int8_t CurrentMusic=-1;

bool ExtendMusic=false;


int audio_rate = MIX_DEFAULT_FREQUENCY;
Uint16 audio_format = MIX_DEFAULT_FORMAT; /* 16-bit stereo */
int audio_channels = MIX_DEFAULT_CHANNELS;
int audio_buffers = 1024;

void InitMusic()
{
    Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers);
}



void spuMusic(uint8_t ind)
{
    if (CurrentMusic!=ind)
    {
        if (music)
            Mix_FreeMusic(music);

        switch (ind)
        {
        case 0:
            music=Mix_LoadMUS("./Music/Intro.ogg");
            break;

        case 1:
            music=Mix_LoadMUS("./Music/Theme.ogg");
            break;

        case 2:
            music=Mix_LoadMUS("./Music/Fairy_Battle.ogg");
            break;

        case 3:
            music=Mix_LoadMUS("./Music/Battle_2.ogg");
            break;

        case 4:
            music=Mix_LoadMUS("./Music/Battle_1.ogg");
            break;

        case 5:
            music=Mix_LoadMUS("./Music/Fanfare.ogg");
            break;

        case 6:
            music=Mix_LoadMUS("./Music/Game_Over.ogg");
            break;

        case 7:
            music=Mix_LoadMUS("./Music/Kuja.ogg");
            break;
        }

        CurrentMusic=ind;

        if (music)
        {
            if (ind>4)
                Mix_PlayMusic(music,0);
            else
                Mix_PlayMusic(music,-1);
        }
    }

}



