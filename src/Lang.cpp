#include "res.h"

char *LangString[100];

char *cardName[100];


void LoadCardNames()
{



}

void enemy_LoadNameList()
{
    memset(EnemiesCards,0,sizeof(card *)*21*30);
    memset(EnemiesNumCards,0,sizeof(uint8_t)*21);


    FILE * fl;

    fl=fopen("./Enemies","rb");

    for (uint8_t i=0; i<21;i++)
    {
        char tmps[255];
        fgets(tmps,100,fl);
        EnemiesNames[i]=GetCP1251(tmps);
        //memset(EnemiesNames[i],0,31);
        //sprintf(EnemiesNames[i],"Enemy %d",i);
    }
    fclose(fl);
}


void InitLangStrings()
{
    FILE * fl;

    fl=fopen("./Lang","rb");

    uint8_t jj=0;
    while (!feof(fl))
    {
        char tmps[255];
        fgets(tmps,100,fl);
        LangString[jj]=GetCP1251(tmps);
        jj++;
        //memset(EnemiesNames[i],0,31);
        //sprintf(EnemiesNames[i],"Enemy %d",i);
    }
    fclose(fl);



    fl=fopen("./Cards","rb");

    for (uint8_t i=0; i<100;i++)
    {
        char tmps[255];
        fgets(tmps,100,fl);
        cardName[i]=GetCP1251(tmps);
        //memset(EnemiesNames[i],0,31);
        //sprintf(EnemiesNames[i],"Enemy %d",i);
    }
    fclose(fl);
}

char * GetLangString(uint8_t Numb)
{
    return LangString[Numb];

}


/*char * GetLangString$(uint8_t Numb)
{
    //Local resultSt$
	switch (Numb)
	{
		case 0:
		return "Выберите противника.";
		////If Lang=1 Then resultSt="Select enemy."
		break;
		case 1:
		return "Карты";
		//If Lang=1 Then resultSt="Cards"
		break;
		case 2:
		return "Магазин";
		//If Lang=1 Then resultSt="Shop"
		break;
		case 3:
		return "Чтение";
		//If Lang=1 Then resultSt="Load"
		break;
		case 4:
		return "Запись";
		//If Lang=1 Then resultSt="Save"
		break;
		case 5:
		return "Удаление";
		//If Lang=1 Then resultSt="Delete"
		break;
		case 6:
		return "Выход";
		//If Lang=1 Then resultSt="Exit"
		break;
		case 7:
		return "Вы действительно хотите выйти?";
		//If Lang=1 Then resultSt="Are you sure?"
		break;
		case 8:
		return "Отмена";
		//If Lang=1 Then resultSt="Cancel"
		break;
		case 9:
		return "Да";
		//If Lang=1 Then resultSt="Yes"
		break;
		case 10:
		return "Нет";
		//If Lang=1 Then resultSt="No"
		break;
		case 11:
		return "Сыграть еще?";
		//If Lang=1 Then resultSt="Play again?"
		break;
		case 12:
		return "Имя:";
		//If Lang=1 Then resultSt="Name:"
		break;
		case 13:
		return "Гили:";
		//If Lang=1 Then resultSt="Gil:"
		break;
		case 14:
		return "Уровень:";
		//If Lang=1 Then resultSt="Level:"
		break;
		case 15:
		return "Дата:";
		//If Lang=1 Then resultSt="Date:"
		break;
		case 16:
		return "Время:";
		//If Lang=1 Then resultSt="Time:"
		break;
		case 17:
		return "Пустой блок.";
		//If Lang=1 Then resultSt="Empty Block."
		break;
		case 18:
		return "ФАЙЛ ";
		//If Lang=1 Then resultSt="FILE "
		break;
		case 19:
		return "Введите Пароль";
		//If Lang=1 Then resultSt="Enter Password"
		break;
		case 20:
		return "Неверно";
		//If Lang=1 Then resultSt="Incorrect"
		break;
		case 21:
		return "Записать поверх?";
		//If Lang=1 Then resultSt="Rewrite File?"
		break;
		case 22:
		return "Удалить Файл?";
		//If Lang=1 Then resultSt="Delete File?"
		break;
		case 23:
		return "Получено ";
		//If Lang=1 Then resultSt="Received "
		break;
		case 24:
		return "Всего: ";
		//If Lang=1 Then resultSt="In all: "
		break;
		case 25:
		return "Подтверждаете выбор?";
		//If Lang=1 Then resultSt="Confirm choice?"
		break;
		case 26:
		return "Опыт:";
		//If Lang=1 Then resultSt="Experience:"
		break;
		case 27:
		return "Вы хотите продать за ";
		//If Lang=1 Then resultSt="Do you want to sell for "
		break;
		case 28:
		return "Начинающий";
		//If Lang=1 Then resultSt="Beginner"
		break;
		case 29:
		return "Новичок";
		//If Lang=1 Then resultSt="Novice"
		break;
		case 30:
		return "Игрок";
		//If Lang=1 Then resultSt="Player"
		break;
		case 31:
		return "Старший";
		//If Lang=1 Then resultSt="Senior"
		break;
		case 32:
		return "Фанат";
		//If Lang=1 Then resultSt="Fan"
		break;
		case 33:
		return "Лидер";
		//If Lang=1 Then resultSt="Leader"
		break;
		case 34:
		return "Инструктор";
		//If Lang=1 Then resultSt="Coach"
		break;
		case 35:
		return "Наставник";
		//If Lang=1 Then resultSt="Advisor"
		break;
		case 36:
		return "Директор";
		//If Lang=1 Then resultSt="Director"
		break;
		case 37:
		return "Делец";
		//If Lang=1 Then resultSt="Dealer"
		break;
		case 38:
		return "Торговец";
		//If Lang=1 Then resultSt="Trader"
		break;
		case 39:
		return "Командир";
		//If Lang=1 Then resultSt="Commander"
		break;
		case 40:
		return "Доктор";
		//If Lang=1 Then resultSt="Doctor"
		break;
		case 41:
		return "Профессор";
		//If Lang=1 Then resultSt="Professor"
		break;
		case 42:
		return "Ветеран";
		//If Lang=1 Then resultSt="Veteran"
		break;
		case 43:
		return "Чудак";
		//If Lang=1 Then resultSt="Freak"
		break;
		case 44:
		return "Чемпион";
		//If Lang=1 Then resultSt="Champion"
		break;
		case 45:
		return "Аналитик";
		//If Lang=1 Then resultSt="Analyst"
		break;
		case 46:
		return "Генерал";
		//If Lang=1 Then resultSt="General"
		break;
		case 47:
		return "Эксперт";
		//If Lang=1 Then resultSt="Expert"
		break;
		case 48:
		return "Шулер";
		//If Lang=1 Then resultSt="Shark"
		break;
		case 49:
		return "Специалист";
		//If Lang=1 Then resultSt="Specialist"
		break;
		case 50:
		return "Опытный";
		//If Lang=1 Then resultSt="Elder"
		break;
		case 51:
		return "Доминатор";
		//If Lang=1 Then resultSt="Dominator"
		break;
		case 52:
		return "Маэстро";
		//If Lang=1 Then resultSt="Maestro"
		break;
		case 53:
		return "Король";
		//If Lang=1 Then resultSt="King"
		break;
		case 54:
		return "Волшебник";
		//If Lang=1 Then resultSt="Wizard"
		break;
		case 55:
		return "Авторитет";
		//If Lang=1 Then resultSt="Authority"
		break;
		case 56:
		return "Император";
		//If Lang=1 Then resultSt="Emperor"
		break;
		case 57:
		return "Профессионал";
		//If Lang=1 Then resultSt="Pro"
		break;
		case 58:
		return "Мастер";
		//If Lang=1 Then resultSt="Master"
		break;
		case 59:
		return "Желаете купить: ";
		//If Lang=1 Then resultSt="Do you want to buy: "
		break;
		case 60:
		return "Введите пароль:";
		//If Lang=1 Then resultSt="Enter password:"
		break;
		case 61:
		return "Введите имя:";
		//If Lang=1 Then resultSt="Enter name:"
		break;
		case 62:
		return "Назад";
		//If Lang=1 Then resultSt="Back"
		break;
		case 63:
		return "";
		//If Lang=1 Then resultSt=""
		break;
		case 64:
		return "";
		//If Lang=1 Then resultSt=""
		break;
		case 65:
		return "";
		//If Lang=1 Then resultSt=""
		break;
		case 66:
		return "";
		//If Lang=1 Then resultSt=""
	}
//Return resultSt
}
*/
