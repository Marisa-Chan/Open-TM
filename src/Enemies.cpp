#define ENEMY
#include "res.h"




void enemy_sortirovka()
{
for (uint8_t i=0; i<21;i++)
        for (uint8_t z=0;z<30;z++)
            if (!EnemiesCards[i][z])
                {
                    for (uint8_t q=z; q<29; q++)
                        EnemiesCards[i][q]=EnemiesCards[i][q+1];

                    EnemiesCards[i][29]=NULL;
                }

}

void enemy_ssortirovka(uint8_t Who)
{
    for (uint8_t z=0;z<30;z++)
        if (!EnemiesCards[Who][z])
            {
                for (uint8_t q=z; q<29; q++)
                    EnemiesCards[Who][q]=EnemiesCards[Who][q+1];

                EnemiesCards[Who][29]=NULL;
            }

}


void enemy_podshet()
{
    for (uint8_t i=0; i<21; i++)
        {
            EnemiesNumCards[i]=0;
            for (uint8_t z=0;z<30;z++)
                if (EnemiesCards[i][z])
                    EnemiesNumCards[i]++;

        }
}

void enemy_spodshet(uint8_t Who)
{
            EnemiesNumCards[Who]=0;
            for (uint8_t z=0;z<30;z++)
                if (EnemiesCards[Who][z])
                    EnemiesNumCards[Who]++;
}


bool AddCardToEnemy(uint8_t ENumber,card *crd)
{
enemy_ssortirovka(ENumber);
enemy_spodshet(ENumber);
if (EnemiesNumCards[ENumber]<30)
    {
        EnemiesCards[ENumber][EnemiesNumCards[ENumber]]=crd;
        EnemiesNumCards[ENumber]++;
        return true;
	}
else
    {
        delete crd;
        return false;
    }
}

card * CreateCard(uint8_t num, uint8_t attack, uint8_t atyp,uint8_t pd, uint8_t md, uint8_t arr)
{
    card *crd = new (card);
    crd->Number=num;
    crd->Expirience=0;
    crd->Arr=arr;
    crd->Attack=attack;
    crd->PDefence=pd;
    crd->MDefence=md;
    crd->Atype=atyp;
    return  crd;
}

void enemy_addy(uint8_t Who)
{
uint8_t sstt;
switch (Who)
    {
	case 20:
		sstt=rand() % 100;
		switch (rand() % 20)
            {
            case 0:
                AddCardToEnemy(Who,CreateCard(sstt,defAtack[sstt]+rand() % 6,aT_A,defPDef[sstt]+rand() % 6,defMDef[sstt]+rand() % 6,rand() % 256));
                break;
            case 1:
            case 2:
            case 3:
                AddCardToEnemy(Who,CreateCard(sstt,defAtack[sstt]+rand() % 6,aT_X,defPDef[sstt]+rand() % 6,defMDef[sstt]+rand() % 6,rand() % 256));
                break;
            default:
                AddCardToEnemy(Who,CreateCard(sstt,defAtack[sstt]+rand() % 6,defAType[sstt],defPDef[sstt]+rand() % 6,defMDef[sstt]+rand() % 6,rand() % 256));
            }

        break;


	case 19:
		switch (rand() & 1)
            {
            case 0:
                sstt=55;
                break;
            case 1:
                sstt=75;
            }
        AddCardToEnemy(Who,CreateCard(sstt,defAtack[sstt]+rand() % 5,defAType[sstt],defPDef[sstt]+rand() % 5,defMDef[sstt]+rand() % 5,rand() % 256));
        break;


	case 18:
        switch (rand() % 12)
            {
            case 0:
                sstt=64;
                break;
            case 1:
                sstt=73;
                break;
            case 2:
                sstt=74;
                break;
            case 3:
                sstt=76;
                break;
            case 4:
                sstt=77;
                break;
            case 5:
                sstt=79;
                break;
            case 6:
                sstt=91;
                break;
            case 7:
                sstt=92;
                break;
            case 8:
                sstt=95;
                break;
            case 9:
                sstt=96;
                break;
            case 10:
                sstt=99;
                break;
            case 11:
                sstt=100;
            }
        AddCardToEnemy(Who,CreateCard(sstt,defAtack[sstt]+rand() % 3,defAType[sstt],defPDef[sstt]+rand() % 3,defMDef[sstt]+rand() % 3,rand() % 256));
		break;


	case 17:
		switch (rand() % 7)
            {
            case 0:
                sstt=59;
                break;
            case 1:
                sstt=61;
                break;
            case 2:
            	sstt=63;
            	break;
            case 3:
            	sstt=72;
            	break;
            case 4:
                sstt=74;
                break;
            case 5:
            	sstt=94;
            	break;
            case 6:
            	sstt=96;
            }
        AddCardToEnemy(Who,CreateCard(sstt,defAtack[sstt]+rand() % 7,defAType[sstt],defPDef[sstt]+rand() % 3,defMDef[sstt]+rand() % 3,rand() % 256));
		break;


	case 16:
		sstt=(rand() & 1) + 76;
		AddCardToEnemy(Who,CreateCard(sstt,defAtack[sstt]+rand() & 1,defAType[sstt],defPDef[sstt]+rand() % 6,defMDef[sstt]+rand() % 6,rand() % 256));
		break;


	case 15:
		switch (rand() % 4)
            {
            case 0:
                sstt=54;
                break;
            case 1:
            	sstt=83;
            	break;
            case 2:
            	sstt=56;
            	break;
            case 3:
            	sstt=70;
            }
        AddCardToEnemy(Who,CreateCard(sstt,defAtack[sstt]+rand() % 4,defAType[sstt],defPDef[sstt]+rand() % 4,defMDef[sstt]+rand() % 4,rand() % 256));
		break;


	case 0:
		sstt=(rand() % 3) + 1;
		AddCardToEnemy(Who,CreateCard(sstt,defAtack[sstt]+rand() & 1,defAType[sstt],defPDef[sstt]+rand() & 1,defMDef[sstt]+rand() & 1,rand() % 256));
        break;


	case 14:
		switch (rand() % 6)
            {
            case 0:
                sstt=45;
                break;
            case 1:
                sstt=46;
                break;
            case 2:
            	sstt=47;
            	break;
            case 3:
                sstt=48;
                break;
            case 4:
                sstt=60;
                break;
            case 5:
                sstt=72;
            }
        AddCardToEnemy(Who,CreateCard(sstt,defAtack[sstt]+rand() & 1,defAType[sstt],defPDef[sstt]+rand() & 1,defMDef[sstt]+rand() & 1,rand() % 256));
		break;


	case 13:
		sstt=93;
		AddCardToEnemy(Who,CreateCard(sstt,defAtack[sstt]+rand() % 3,defAType[sstt],defPDef[sstt]+rand() % 3,defMDef[sstt]+rand() % 3,rand() % 256));
		break;


	case 12:
		sstt=8;
		AddCardToEnemy(Who,CreateCard(sstt,defAtack[sstt]+rand() % 3,defAType[sstt],defPDef[sstt]+rand() % 3,defMDef[sstt]+rand() % 3,rand() % 256));
		break;


	case 11:
		sstt=(rand() % 4) + 50;
		AddCardToEnemy(Who,CreateCard(sstt,defAtack[sstt]+rand() & 1,defAType[sstt],defPDef[sstt]+rand() & 1,defMDef[sstt]+rand() & 1,rand() % 256));
		break;


	case 10:
		sstt=(rand() % 3) + 57;
		AddCardToEnemy(Who,CreateCard(sstt,defAtack[sstt]+rand() & 1,defAType[sstt],defPDef[sstt]+rand() & 1,defMDef[sstt]+rand() & 1,rand() % 256));
		break;


	case 9:
		sstt=49;
		AddCardToEnemy(Who,CreateCard(sstt,defAtack[sstt]+rand() % 3,defAType[sstt],defPDef[sstt]+rand() % 3,defMDef[sstt]+rand() % 3,rand() % 256));
		break;


	case 8:
		sstt=80;
		AddCardToEnemy(Who,CreateCard(sstt,defAtack[sstt]+rand() % 3,defAType[sstt],defPDef[sstt]+rand() % 3,defMDef[sstt]+rand() % 3,rand() % 256));
		break;


	case 7:
		sstt=(rand() % 9) + 60;
		AddCardToEnemy(Who,CreateCard(sstt,defAtack[sstt]+rand() % 3,defAType[sstt],defPDef[sstt]+rand() % 3,defMDef[sstt]+rand() % 3,rand() % 256));
		break;


	case 6:
		sstt=53;
		AddCardToEnemy(Who,CreateCard(sstt,defAtack[sstt]+rand() % 3,defAType[sstt],defPDef[sstt]+rand() % 3,defMDef[sstt]+rand() % 3,rand() % 256));
		break;


	case 5:
		sstt=52;
		AddCardToEnemy(Who,CreateCard(sstt,defAtack[sstt]+rand() % 4,defAType[sstt],defPDef[sstt]+rand() % 4,defMDef[sstt]+rand() % 4,rand() % 256));
		break;


	case 4:
		sstt=(rand() & 1) + 33;
		AddCardToEnemy(Who,CreateCard(sstt,defAtack[sstt]+rand() % 3,defAType[sstt],defPDef[sstt]+rand() % 3,defMDef[sstt]+rand() % 3,rand() % 256));
		break;


	case 3:
		sstt=(rand() & 11) + 22;
		AddCardToEnemy(Who,CreateCard(sstt,defAtack[sstt]+rand() % 3,defAType[sstt],defPDef[sstt]+rand() % 3,defMDef[sstt]+rand() % 3,rand() % 256));
		break;


	case 2:
		sstt=(rand() & 10) + 12;
		AddCardToEnemy(Who,CreateCard(sstt,defAtack[sstt]+rand() & 1,defAType[sstt],defPDef[sstt]+rand() & 1,defMDef[sstt]+rand() & 1,rand() % 256));
		break;


	case 1:
		sstt=(rand() & 8) + 4;
		AddCardToEnemy(Who,CreateCard(sstt,defAtack[sstt]+rand() & 1,defAType[sstt],defPDef[sstt]+rand() & 1,defMDef[sstt]+rand() & 1,rand() % 256));
    }

}

/*void enemy_add_to(who%,address)
Local tempp.encards
If EnemiesCards(who,0)<30 Then
	EnemiesCards(who,0)=EnemiesCards(who,0)+1
	EnemiesCards(who,EnemiesCards(who,0))=address
	Return True
Else
tempp=Object.encards(address)
Delete tempp
Return False
EndIf
End Function
*/
