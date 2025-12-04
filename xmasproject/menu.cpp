/*
    Xmas present calculator program

    - Author: e2403299
    - Date: 3rd of dec
    
    This is a small project for VAMK's C++ OOP course
*/
#include "header.h"
#include <iostream>
#include <ncurses.h>
#include <fstream>

class listingGift {
    public:
        void addGift() {

            char placehold[100];

            move(2, 0);
            for(int j = 0; j < 30; j++){    // Clear the row for pressing any buttons
                addch(' ');
            }

            giftType = text_input_loop(GIFTTYPE); // assign gift type
            manufacturer = text_input_loop(GIFTMANU); // assign gift manu
            receiver = text_input_loop(GIFTRECEIVER); // assign gift receiver

            // different function for the price
            for(int i = 0; i < MAX_GIFTS; i++){ 
                if (price[i] == 0) {
                    price[i] = input_price(GIFTPRICE); // Try to find price 0;
                    break;
                }
            }
            mvhline(ERROR_MESSAGE_ROW, 0, ' ', MAX_CHARACTERS); // Clear error messages
        
            mvprintw(GIFTPRICE + 3, 0, "Press any key to continue...");

            getch();
        }

    private:
        std::string giftType = "";
        std::string manufacturer = "";
        std::string receiver = "";
        float price[MAX_GIFTS] = {0};
};

int main(void) {

    listingGift Gifts;

    std::string lista[100];

    // menu valikon tekstit
    const char *options[] = {
    "Add new gift",
    "Show list               (not done yet)",
    "Delete gift from list - (not done yet)",
    "Quit"
    };
    #define N_OPTIONS (sizeof(options)/sizeof(options[0]))

    int ch, i;
    int highlight = 0;

    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    init_pair(2, COLOR_WHITE, COLOR_RED);
    // bkgd(COLOR_PAIR(1));

    char quit = 1; // use char type to determine quitting

    while (quit) {
        clear();
        attron(COLOR_PAIR(2));
        mvprintw(1, 0, TITLE);
        
        attroff(COLOR_PAIR(2));
        mvprintw(7, 0, "      --- Gift Calculator - by e2403299 ---      \n");
        
        for (i = 0; i < N_OPTIONS; i++) {
            if (i == highlight) {
                attron(COLOR_PAIR(1));
                mvprintw(10 + i, 4, "%s", options[i]);
                attroff(COLOR_PAIR(1));
            } else {
                mvprintw(10 + i, 4, "%s", options[i]);
            }
        }
        refresh();

        ch = getch();
        if (ch == KEY_UP) {
            highlight = (highlight - 1 + N_OPTIONS) % N_OPTIONS;
            } 
        else if (ch == KEY_DOWN) {
            highlight = (highlight + 1) % N_OPTIONS;
            } 
        else if (ch == '\n' || ch == KEY_ENTER) {
            // which option was chosen
            clear();
            if (highlight == N_OPTIONS - 1) {
            mvprintw(4,4," - Merry xmas!");
            getch();
            break; // quit the program
            }

            mvprintw(0, 0, "Mode: %s", options[highlight]);
            mvprintw(2, 0, "Press any key to continue...");
            refresh();
            getch();
           
            if (highlight == ADD) {
                Gifts.addGift();
            }

        } else if (ch == 'Q') { 
            quit = 0; // quit the program with shift Q
        }
    }

    endwin();
    return 0;
}

void add_to_list(std::string lista[]){

}