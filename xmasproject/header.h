#ifndef HEADER
#define HEADER

#include <string>

#define DEBUG

#define DEBUG_STRING    "| Gift: test1 | Made by: 67 | Receiver: u | Price: 1.00 |", \
                        "| Gift: test2 | Made by: jk | Receiver: u | Price: 2.00 |", \
                        "| Gift: test3 | Made by: wt | Receiver: u | Price: 3.00 |"

#define RED COLOR_PAIR(2)

#define BLUE COLOR_PAIR(1)

#define MAX_GIFTS 10

#define MAX_CHARACTERS 80

#define ERROR_MESSAGE_ROW 0

#define LIST_ITEMS (MAX_GIFTS+1)

#define STRING_LENGTH 20

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
    DELETE,
    SAVE
};

enum inputRows{
    GIFTTYPE = 2,
    GIFTMANU = 4,
    GIFTRECEIVER = 6,
    GIFTPRICE = 8
};

float input_price(int row);

std::string text_input_loop(int row);

#endif