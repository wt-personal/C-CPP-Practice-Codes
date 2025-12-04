#ifndef HEADER
#define HEADER

#include <string>

#define MAX_GIFTS 100

#define MAX_CHARACTERS 80

#define ERROR_MESSAGE_ROW 25

#define TITLE \
"    /$$   /$$ /$$$$$$/$$$$   /$$$$$$   /$$$$$$$  \n" \
"   |  $$ /$$/| $$_  $$_  $$ |____  $$ /$$_____/  \n" \
"    \\  $$$$/ | $$ \\ $$ \\ $$  /$$$$$$$|  $$$$$$   \n" \
"     >$$  $$ | $$ | $$ | $$ /$$__  $$ \\____  $$  \n" \
"    /$$/\\  $$| $$ | $$ | $$|  $$$$$$$ /$$$$$$$/  \n" \
"   |__/  \\__/|__/ |__/ |__/ \\_______/|_______/   \n"

enum Mode{
    ADD,
    SHOW,
    LIST
};

enum inputRows{
    GIFTTYPE = 2,
    GIFTMANU = 5,
    GIFTRECEIVER = 8,
    GIFTPRICE = 11
};

float input_price(int row);

std::string text_input_loop(int row);

#endif