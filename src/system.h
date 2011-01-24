typedef enum
{
    Ki_UP=0,
    Ki_DOWN=1,
    Ki_LEFT=2,
    Ki_RIGHT=3,
    Ki_X=4,
    Ki_O=5,
    Ki_4=6,
    Ki_D=7,
    Ki_R=8,
    Ki_L=9,
    Ki_START=10,
    Ki_SELECT=11
}
Ki_ENM;


bool input_GetState(Ki_ENM State);

uint64_t  millisec();
