#include "res.h"


uint32_t kUpCode=SDLK_UP;
uint32_t kDownCode=SDLK_DOWN;
uint32_t kLeftCode=SDLK_LEFT;
uint32_t kRightCode=SDLK_RIGHT;

uint32_t kStartCode=SDLK_RETURN;
uint32_t kSelectCode=SDLK_ESCAPE;

#ifdef DINGOO
uint32_t kXCode=SDLK_LALT;
uint32_t kOCode=SDLK_LCTRL;
uint32_t kSquareCode=SDLK_LSHIFT;
uint32_t kTriangleCode=SDLK_SPACE;

uint32_t kR1Code=SDLK_BACKSPACE;
uint32_t kL1Code=SDLK_TAB;
#else

uint32_t kXCode=SDLK_z;
uint32_t kOCode=SDLK_x;
uint32_t kSquareCode=SDLK_a;
uint32_t kTriangleCode=SDLK_s;

uint32_t kR1Code=SDLK_LALT;
uint32_t kL1Code=SDLK_LCTRL;
#endif






uint32_t time_to_update_input=0;
bool Inp_True=false;
uint32_t Inp_Delay=100;


bool input_GetState(Ki_ENM State)
{

    if (millisec()>time_to_update_input+Inp_Delay)
    {
        switch (State)
        {
        case Ki_UP:
            if (Kii==kUpCode) Inp_True=true;
            break;

        case Ki_DOWN:
            if (Kii==kDownCode) Inp_True=true;
            break;

        case Ki_LEFT:
            if (Kii==kLeftCode) Inp_True=true;
            break;

        case Ki_RIGHT:
            if (Kii==kRightCode) Inp_True=true;
            break;

        case Ki_X:
            if (Kii==kXCode) Inp_True=true;
            break;

        case Ki_O:
            if (Kii==kOCode) Inp_True=true;
            break;

        case Ki_R:
            if (Kii==kR1Code) Inp_True=true;
            break;

        case Ki_L:
            if (Kii==kL1Code) Inp_True=true;
            break;

        case Ki_D:
            if (Kii==kSquareCode) Inp_True=true;
            break;

        case Ki_4:
            if (Kii==kTriangleCode) Inp_True=true;
            break;

        case Ki_START:
            if (Kii==kStartCode) Inp_True=true;
            break;

        case Ki_SELECT:
            if (Kii==kSelectCode) Inp_True=true;
            break;

        }

        if (Inp_True==true)
        {
            time_to_update_input=millisec();
            //FlushKeys()
            //FlushJoy()
            Kii=0;
            Inp_True=false;
            return true;
        }

    }
    return false;
}



uint64_t millisec()
{
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return (uint64_t)t.tv_sec * 1000 + t.tv_nsec / 1000000;
}




char s_buf[256];
