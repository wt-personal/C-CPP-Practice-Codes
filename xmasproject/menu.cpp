/*
    Xmas present calculator program

    - Author: e2403299
    - Date: 3rd of dec
    
    This is a small project for VAMK's C++ OOP course
*/
#include "header.h"
#include <iostream>
#include <ncurses.h>

#include <sstream>
#include <iomanip>

#include <fstream>

class listingGift {
    public:
        int add_to_list(std::string list[]) {
            for (int i = 0; i < LIST_ITEMS; i++) {
                if (list[i].empty()) {
                    std::stringstream ss; // Gather string info in a single string stream
                    ss << std::fixed << std::setprecision(2);
                    ss << "| Gift type: " << giftType                   
                    << " | made by: " << manufacturer
                    << " | receiver: " << receiver
                    << " | price: " << price[giftcounter] << " |";

                    list[i] = ss.str();

                    return i;
                }
            }

            attron(A_REVERSE);
            mvprintw(ERROR_MESSAGE_ROW, 0, " - ERROR: Empty list entry not found! ");
            attroff(A_REVERSE);
            return -1;
        }

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

            giftcounter = add_to_list(list);

            if (giftcounter == -1) mvprintw(GIFTPRICE + 3, 0, "-- Failed to add new gift to the list -- Press any key to continue...");

            else {
                attron(A_REVERSE);
                mvprintw(GIFTPRICE + 2, 2, list[giftcounter].c_str());
                attroff(A_REVERSE);
                giftcounter++; 
                mvprintw(GIFTPRICE + 4, 0, " ~ Added new gift to list: #%d ! Press any key to continue",giftcounter);
                curs_set(1);
            }
            getch();
            curs_set(0);
        }

        float sum_of_prizes(){
            float sum = 0;
            for(int i = 0; i < giftcounter; i++){
                sum += price[i];
            }
            return sum;
        }

        int amount_of_gifts(){
            return giftcounter;
        }

    private:
        std::string giftType = "";
        std::string manufacturer = "";
        std::string receiver = "";
        float price[MAX_GIFTS] = {0};

        int giftcounter = 0;
        std::string list[LIST_ITEMS] = { "" };
};

int main(void) {

    // create object
    listingGift Gifts;
    
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
        mvprintw(0, 0, TITLE); // banner
        
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

        
        attron(COLOR_PAIR(2));
        mvprintw(15, 30, "Amount of gifts: #%d",Gifts.amount_of_gifts());
        mvprintw(16, 30, "Total:%13.2f",Gifts.sum_of_prizes());
        attroff(COLOR_PAIR(2));
        

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
        refresh();
    }

    endwin();
    return 0;
}

