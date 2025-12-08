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
    
    private:
        std::string giftType = "";
        std::string manufacturer = "";
        std::string receiver = "";
        
        #ifndef DEBUG
        int giftcounter = 0;
        std::string list[LIST_ITEMS] = { "" };
        float price[MAX_GIFTS] = {0};
        #else        
        int giftcounter = 3;
        float price[MAX_GIFTS] = {1,2,3};
        std::string list[LIST_ITEMS] = { DEBUG_STRING };
        #endif
    
    public:
        int add_to_list(std::string list[]) {
            for (int i = 0; i < LIST_ITEMS; i++) {
                if (list[i].empty()) {
                    std::stringstream ss; // Gather string info in a single string stream
                    ss << std::fixed << std::setprecision(2);
                    ss << "| Gift: " << giftType                   
                    << " | Made by: " << manufacturer
                    << " | Receiver: " << receiver
                    << " | Price: " << price[giftcounter] << " |";

                    list[i] = ss.str();

                    return i;
                }
            }

            attron(A_REVERSE);  // error handling
            mvprintw(ERROR_MESSAGE_ROW, 0, " - ERROR: Empty list entry not found! ");
            attroff(A_REVERSE);
            return -1;
        }

        void addGift() {
            if (giftcounter == MAX_GIFTS){
                mvhline(0,0,' ',MAX_CHARACTERS);
                mvprintw(0,0,"Press any key to continue..");
                mvprintw(giftcounter+2,0,"MAX amount of gifts! %d at max, delete gifts to add new.",giftcounter);
                show_list();
                return; // return if there is too many gifts
            }

            char placehold[100];

            move(2, 0);
            for(int j = 0; j < 30; j++){    // Clear the row for pressing any buttons
                addch(' ');
            }

            giftType = text_input_loop(GIFTTYPE); // assign gift type
            if (giftType == "\\") return; // skip if ESC is pressed
            manufacturer = text_input_loop(GIFTMANU); // assign gift manu
            if (manufacturer == "\\") return; // skip if ESC is pressed
            receiver = text_input_loop(GIFTRECEIVER); // assign gift receiver
            if (receiver == "\\") return; // skip if ESC is pressed

            // different function for the price
            for(int i = 0; i < MAX_GIFTS; i++){ 
                if (price[i] == 0) {
                    price[i] = input_price(GIFTPRICE); // Try to find price 0;
                    if (price[i] < 0) {
                        price[i] = 0; // clear current price
                        return; // skip if ESC is pressed
                    }
                    break;
                }
            }

            mvhline(ERROR_MESSAGE_ROW, 0, ' ', MAX_CHARACTERS); // Clear error messages

            giftcounter = add_to_list(list); // add 

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

        void show_list(){
            if (giftcounter == 0){
                mvprintw(2,4,"No gifts in the list.\n\n    Make new ones in the Add new gift -mode.");
                getch();
                return;
            }

            attron(A_REVERSE);
            for(int i = 0; i < giftcounter; i++){
                
                mvprintw(i + 1, 0,"#%d %s",i+1,list[i].c_str());
                
            }
            attroff(A_REVERSE);
            getch();
        }

        void delete_gift() {
            if (giftcounter == 0){
                mvhline(2,0,' ',90);
                mvprintw(2,2,"No gifts in the list.\n\n    Make new ones in the Add new gift -mode.");
                getch();
                return;
            }

            keypad(stdscr, TRUE);   // arrow keys

            int highlight = 0;
            int ch = 0;

            int giftdel = 0; // press two characters to confirm delete

            while (giftdel < 2) {
                // print list with highlight
                for (int i = 0; i < giftcounter; i++) {
                    if (i == highlight) attron(RED);
                    mvprintw(i + 1, 0, "#%d %s", i + 1, list[i].c_str());
                    if (i == highlight) attroff(RED);
                }

                if (ch == 27) return; // ESC

                if ((ch == '\n') && (giftdel == 0)) giftdel++;

                if  (giftdel == 0){
                    mvhline(0,0,' ',90);
                    mvprintw(0, 0, "Mode: Delete gift - Press enter to choose one to delete (ESC to abort)");
                    ch = getch();
                    if (ch == KEY_DOWN) {
                        highlight++;
                    } 
                    else if (ch == KEY_UP) {
                        highlight--;
                    }
                    // boundaries for moving highlight with 
                    if (highlight < 0) highlight = 0;
                    if (highlight >= giftcounter) highlight = giftcounter - 1;
                }

                if (giftdel == 1){
                    mvhline(0,0,' ',90);
                    attron(A_REVERSE);
                    mvprintw(0, 0, "Delete gift #%d, Confirm y/n ? (ESC to abort)",highlight+1);
                    attroff(A_REVERSE);
                    ch = getch();
                    if (ch == 'y') break;
                    else if (ch == 'n'){
                        giftdel = 0;
                    }
                } 
            }

            delete_and_sort(highlight); //move the list items

            // end message for 
            erase(); 
            if (giftcounter == 0) mvprintw(giftcounter+1, 2, "%d entries left,",giftcounter);
            else mvprintw(giftcounter+2, 4, "Deleted gift successfully, press any key to continue.");
            curs_set(0);
            show_list();
            
        }

        void delete_and_sort(int highlight){
            for(int i = highlight; i < giftcounter; i++){
                list[i] = list[i+1];
                price[i] = price[i+1];
            }
            list[giftcounter] = "";
            price[giftcounter] = 0;
            giftcounter--;
        }

        void save_list() {
            if (giftcounter == 0){
                mvprintw(2,2,"No gifts in the list.\n\n    Make new ones in the Add new gift -mode.");
                getch();
                return;
            }
        
            const char *filename = "Christmas_wishlist.txt";

            std::fstream MyFile(filename, std::ios::out); // write

            if (!MyFile.is_open()) {
                mvprintw(2,4,"Error: Could not open file!");
                getch();
                return;
            }

            // Write to file
            MyFile << "Christmas gift list:\n-----------------------\n";

            for (int i = 0; i < giftcounter; i++) {
                MyFile << '#' << i << " " << list[i] << "\n";
            }
            MyFile << "\n" << "Number of gifts: " << amount_of_gifts();

            MyFile << "\n\n" << "Total price: " << sum_of_prizes() << 'e';

            mvprintw(giftcounter+2,4,"List saved to a file: %s\n\nPress any key to continue.", filename);
            show_list();  
            MyFile.close();
        }

        // Getters: sums, prices and amount of gifts
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

};

int main(void) {

    // create object
    listingGift Gifts;
    
    // menu valikon tekstit
    const char *options[] = {
    "Add new gift",
    "Show list",
    "Delete gift from list",
    "Save list",
    "Quit"
    };
    #define N_OPTIONS (sizeof(options)/sizeof(options[0]))

    int ch, i;
    int highlight = 0;

    set_escdelay(25); 

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
        erase();
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
        mvprintw(15, 29, "Number of gifts:  #%d",Gifts.amount_of_gifts());
        mvprintw(16, 29, "Total:%13.2fe",Gifts.sum_of_prizes());
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

            // Display which mode is present
            if (highlight == ADD) {
                mvprintw(0, 0, "Mode: %s (ESC to abort)", options[highlight]);
                Gifts.addGift();
            }
            else if (highlight == SHOW) {

                mvprintw(0, 0, "Mode: %s Gifts: #%d Total: %.2fe - Press any key to continue.", 
                options[highlight],Gifts.amount_of_gifts(),Gifts.sum_of_prizes());
                Gifts.show_list();
            }
            else if (highlight == DELETE) {
                Gifts.delete_gift();
            }
            else if (highlight == SAVE) {
                Gifts.save_list();
            }
            else {
                mvprintw(0, 0, "Mode: %s ", options[highlight]);
                mvprintw(2, 0, "Press any key to continue...");
                getch();
            }
            refresh();
            

        } else if (ch == 'Q') { 
            quit = 0; // quit the program with shift Q
        }
        refresh();
    }

    endwin();
    return 0;
}

