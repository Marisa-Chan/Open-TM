//#define FONTSYSTEM_H
#include "res.h"
#include <iconv.h>

uint8_t FontWidths[159];
iconv_t d;


void InitFonts()
{
    FILE * fl;

    fl=fopen("./Fontdb.dat","rb");
    fread(FontWidths,1,159,fl);
    fclose(fl);
    d=iconv_open("windows-1251","UTF-8");

}

char *GetCP1251(char *st)
{
    uint32_t tmp,tmp2;
    char *buf;
    char    *mu1,*mu2;


    tmp=strlen(st);
    tmp2=256;

    buf=(char *)malloc(tmp+1);
    memset(buf,0,tmp+1);

    mu2=buf;
    mu1=st;
#ifndef FREE_BSD
    iconv(d,&mu1,&tmp,&mu2,&tmp2);
#else
    iconv(d,(const char **)&mu1,&tmp,&mu2,&tmp2);
#endif

    return buf;
}

uint32_t GetFFWidth_UTF(char *st)
{
    size_t tmp,tmp2;
    unsigned char buf[256];
    char    *mu1,*mu2;

    memset(buf,0,256);
    tmp=strlen(st);
    tmp2=256;
    mu2=(char *)buf;
    mu1=st;
#ifndef FREE_BSD
    iconv(d,&mu1,&tmp,&mu2,&tmp2);
#else
    iconv(d,(const char **)&mu1,&tmp,&mu2,&tmp2);
#endif


    tmp=0;

    for (uint32_t i=0;i<strlen((char *)buf);i++)
    {
        if ((buf[i]>191) && (buf[i]<=255))
            tmp+=FontWidths[buf[i]-97];

        if ((buf[i]>31) && (buf[i]<127))
            tmp+=FontWidths[buf[i]-32];

    }

    return tmp;
}

uint32_t GetFFWidth(char *st)
{
    uint32_t tmp=0;
    unsigned char *buf;
    buf=(unsigned char *)st;

    for (uint32_t i=0;i<strlen((char *)buf);i++)
    {
        if ((buf[i]>191) && (buf[i]<=255))
            tmp+=FontWidths[buf[i]-97];

        if ((buf[i]>31) && (buf[i]<127))
            tmp+=FontWidths[buf[i]-32];

    }

    return tmp;
}




void TextFF_UTF(uint32_t x, uint32_t y, char *st, SDL_Surface * scr)
{
    size_t tmp,tmp2;
    unsigned char buf[256];
    char    *mu1,*mu2;

    memset(buf,0,256);
    tmp=strlen(st);
    tmp2=256;
    mu2=(char *)buf;
    mu1=st;
#ifndef FREE_BSD
    iconv(d,&mu1,&tmp,&mu2,&tmp2);
#else
    iconv(d,(const char **)&mu1,&tmp,&mu2,&tmp2);
#endif

    tmp=0;

    //printf ("%d",strlen(buf));

    for (uint32_t i=0;i<strlen((char *)buf);i++)
    {
        if ((buf[i]>191) && (buf[i]<=255))
        {
            // printf ("nyo");
            DrawAnimImage(CyrFont,x+tmp,y,buf[i]-192,scr);
            tmp+=FontWidths[buf[i]-97];
        }

        if ((buf[i]>31) && (buf[i]<127))
        {
            DrawAnimImage(Font,x+tmp,y,buf[i]-32,scr);
            tmp+=FontWidths[buf[i]-32];
        }

    }
}

void TextFF(uint32_t x, uint32_t y, char *st, SDL_Surface * scr)
{
    uint32_t tmp=0;
    unsigned char *buf;
    buf=(unsigned char *)st;
    //printf ("%d",strlen(buf));

    for (uint32_t i=0;i<strlen((char *)buf);i++)
    {
        if ((buf[i]>191) && (buf[i]<=255))
        {
            // printf ("nyo");
            DrawAnimImage(CyrFont,x+tmp,y,buf[i]-192,scr);
            tmp+=FontWidths[buf[i]-97];
        }

        if ((buf[i]>31) && (buf[i]<127))
        {
            DrawAnimImage(Font,x+tmp,y,buf[i]-32,scr);
            tmp+=FontWidths[buf[i]-32];
        }

    }
}

