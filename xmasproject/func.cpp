#include "header.h"
#include <iostream>
#include <ncurses.h>
#include <fstream>

float input_price(int row){
    int printrow;

    switch(row){
        case GIFTPRICE:
            printrow = GIFTPRICE;
            mvprintw(printrow, 0, "The price of the gift: ");
            break;
        default:
            return 0;
    }

    char buffer[256] = {0};
    int ch;
    int counter = 0;
    bool dot_exists = false;

    while (true) {
        curs_set(1);
        ch = getch();

        if (ch == '\n'){
            if (!std::strtof(buffer, nullptr)){
                for(int i = 0; i < counter; i++){
                    mvdelch(printrow, 28);
                }
                buffer[256] = {0}; // clear buffer
                dot_exists = false;
                counter = 0;
                attron(A_REVERSE);
                mvprintw(ERROR_MESSAGE_ROW , 0 , " - There is no free lunch! Price cannot be zero.");
                attroff(A_REVERSE);
                mvprintw(printrow, 0, "Give the price of the gift: ");
                
                
            }
            else {
                curs_set(0);
                break;
            }
        }

        if (ch == KEY_BACKSPACE || ch == 127 || ch == 8) {
            if (counter > 0) {
                counter--;
                if (buffer[counter] == '.') dot_exists = false;
                buffer[counter] = '\0';
                int y, x;
                getyx(stdscr, y, x);
                if (x > 0) mvdelch(y, x - 1);
            }
            continue;
        }

        if (counter < 40) {
            if ((ch >= '0' && ch <= '9') || ch == 'e' || (ch == '.' && !dot_exists)) {
                if (ch == '.') dot_exists = true;
                buffer[counter++] = ch;
                addch(ch);
            }
        }
    }

    float price = std::strtof(buffer, nullptr);

    // for(int i = 0; i < MAX_CHARACTERS; i++) {
    //     if (i == MAX_CHARACTERS-1) mvprintw(printrow, 0, "Rounded price was: %.2fe", price);
    //     else mvprintw(printrow, i, " ");
    // }

    mvhline(printrow, 0, ' ', MAX_CHARACTERS);
    mvprintw(printrow, 0, "Rounded price was: %.2fe", price);

    
    return price;
}


std::string text_input_loop(int row){

        int printrow;

        switch(row){
            case GIFTTYPE:
                printrow = GIFTTYPE;
                mvprintw(printrow, 0, "Give the type of gift: ");
                break;
            case GIFTMANU:
                printrow = GIFTMANU;
                mvprintw(printrow, 0, "Give the manufacturer: ");
                break;
            case GIFTRECEIVER:
                printrow = GIFTRECEIVER;
                mvprintw(printrow, 0, "Give who is going to receive the gift: ");
                break;
            default:
                break;
        }

        char buffer[256] = {0}; // buffer for names etc

        int ch;
        int counter = 0;

    //- Loop for input text
        while (true) {

            curs_set(1); // show cursor
            
            ch = getch();

            if (ch == '\n'){
                curs_set(0); // disable cursor
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
                    addch(ch);
                }
            }
        }

        counter = 0; // reset counter
        
    // getstr(buffer);
    mvprintw(printrow + 1, 0, "You entered: %s", buffer);
    return buffer;
}