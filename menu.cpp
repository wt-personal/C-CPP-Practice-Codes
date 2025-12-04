/*
    Xmas present calculator program

    - Author: e2403299
    - Date: 3rd of dec
    
    This is a small project for VAMK's C++ OOP course
*/
#include <iostream>
#include <ncurses.h>
#include <fstream>

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
    GIFTMANU = 4,
    GIFTRECEIVER = 6,
    GIFTPRICE = 7
};

void text_input_loop(int row){

}

class listingGift {
    public:
        void addGift() {

            move(2, 0);
            for(int j = 0; j < 30; j++){    // Clear the row for pressing any buttons
                addch(' ');
            }
            mvprintw(2, 0, "Give the type of gift: ");

            char buffer[256] = {0}; // buffer for names etc

            int ch;
            int counter = 0;

            // Loop for input text
            while (true) {
                // Sleep function is about 1/60 ~ 16,7...ms 

                curs_set(1); // show cursor
                
                ch = getch();

                if (ch == '\n'){
                    curs_set(0); // show cursor
                    break;
                }


                if (ch == KEY_BACKSPACE || ch == 127 || ch == 8) {
                    if (counter > 0) {
                        counter--;

                        // remove from buffer
                        buffer[counter] = '\0';

                        // move cursor one left and delete char on screen
                        int y, x;
                        getyx(stdscr, y, x);
                        if (x > 0) {
                            mvdelch(y, x - 1);
                        }
                    }
                    continue;   // IMPORTANT
                }

                // Add character
                if (counter < 40) {
                    if ((ch >= 'A') && (ch <= 'Z') || (ch >= 'a') && (ch <= 'z') || (ch == ' ')){
                        buffer[counter++] = ch;
                        // printw("%d",ch);
                        addch(ch);
                    }
                }
            }

            counter = 0; // reset counter
            
            getstr(buffer);
            giftType = buffer;

            mvprintw(3, 0, "You entered: %s", giftType.c_str());

            mvprintw(5, 0, "Give the manufacturer: ");
            getstr(buffer);
            manufacturer = buffer;

            mvprintw(6, 0, "You entered: %s", giftType.c_str());

            getch();
        }

    private:
        std::string giftType = "";
        std::string manufacturer = "";
        std::string receiver = "";
        float price = 0;
};

int main(void) {


    // std::string list_of_gifts[100] = {0};

    listingGift Gifts;

    std::string lista[100];

    // menu valikon tekstit
    const char *options[] = {
    "Add new gift",
    "Show list",
    "Delete gift from list",
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
        
        for (i = 0; i < N_OPTIONS; ++i) {
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
        } else if (ch == KEY_DOWN) {
            highlight = (highlight + 1) % N_OPTIONS;
        } else if (ch == '\n' || ch == KEY_ENTER) {
            // which option was chosen
            clear();
            mvprintw(0, 0, "Mode: %s", options[highlight]);
            mvprintw(2, 0, "Press any key to continue...");
            refresh();
            getch();
            if (highlight == N_OPTIONS - 1) break; // "Lopeta" lopettaa
            else if (highlight == ADD) {
                Gifts.addGift();
            }

        } else if (ch == 'Q') { 
            quit = 0; // quit the program with shift Q
        }
    }

    endwin();
    return 0;
}