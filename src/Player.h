
struct Player
{
uint32_t    Pl_v_Face; ////Player avatar image number
char        Pl_v_Name[31]; ////Player name
uint32_t    Pl_v_Gil;
uint32_t    How_Many_Cards;
uint32_t    Pl_Level;
uint32_t    Pl_winBoth;
uint32_t    Pl_winWIn;
uint32_t    Pl_winLose;
//char
} __attribute__((packed));
