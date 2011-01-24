

void enemy_LoadNameList();

void enemy_sortirovka();
void enemy_ssortirovka(uint8_t Who);

void enemy_podshet();
void enemy_spodshet(uint8_t Who);
bool AddCardToEnemy(uint8_t ENumber,card *crd);

card * CreateCard(uint8_t num, uint8_t attack, uint8_t atyp,uint8_t pd, uint8_t md, uint8_t arr);

void enemy_addy(uint8_t Who);


#ifdef ENEMY
card    *EnemiesCards[21][30];  // Cards of enemies
char     EnemiesNames[21][31];  // Enemies names
uint8_t  EnemiesNumCards[21];   // Number of cards
uint8_t  enemy_WhoNow;
#else
extern card     *EnemiesCards[21][30];
extern char     *EnemiesNames[21];
extern uint8_t   EnemiesNumCards[21];
extern uint8_t   enemy_WhoNow;
#endif
