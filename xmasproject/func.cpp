#include "header.h"
#include <iostream>
#include <ncurses.h>
// #include <fstream>

// Collect input into a float value
float input_price(int row){
    int printrow;

    switch(row){
        case GIFTPRICE:
            printrow = GIFTPRICE;
            mvprintw(printrow, 0, "The price of the gift: ");
            break;
        default:
            return -1;
    }

    char buffer[256] = {0};
    int ch;
    int counter = 0;
    bool dot_exists = false;
    curs_set(1);

    while (true) {
        ch = getch();

        if (ch == 27) { curs_set(0); return -1; }

        if (ch == '\n'){
            if (!std::strtof(buffer, nullptr)){
                for(int i = 0; i < counter; i++){
                    mvdelch(printrow, 28);
                }
                buffer[256] = {0}; // clear buffer
                dot_exists = false;
                counter = 0;
                attron(A_REVERSE);
                mvprintw(ERROR_MESSAGE_ROW , 0 , " - There is no free lunch! Price cannot be zero. (ESC to abort)");
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

        if (counter < 8) {
            if ((ch >= '0' && ch <= '9') || ch == 'e' || (ch == '.' && !dot_exists)) {
                if (ch == '.') dot_exists = true;
                buffer[counter++] = ch;
                addch(ch);
            }
        }
    }

    counter = 0;

    float price = std::strtof(buffer, nullptr);

    mvhline(printrow, 0, ' ', MAX_CHARACTERS);
    mvprintw(printrow, 0, "Rounded price was: %.2fe", price);

    return price;
}

// Collect input into a text string
std::string text_input_loop(int row){

        int printrow;

        std::string type;

        switch(row){
            case GIFTTYPE:
                printrow = GIFTTYPE;
                mvprintw(printrow, 0, "What is the gift? enter: ");
                type = "as gift type.";
                break;
            case GIFTMANU:
                printrow = GIFTMANU;
                mvprintw(printrow, 0, "Give the manufacturer: ");
                type = "as manufacturer.";
                break;
            case GIFTRECEIVER:
                printrow = GIFTRECEIVER;
                mvprintw(printrow, 0, "Who is going to receive the gift: ");
                type = "as receiver";
                break;
            default:
                break;
        }

        char buffer[256] = {0}; // buffer for names etc

        int ch;
        int counter = 0;
        curs_set(1); // show cursor
            
        //- Loop for input text
        while (true) {
            
            ch = getch();
            if (ch == 27) {
                curs_set(0);
                return "\\";
            }

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

            if ((counter < STRING_LENGTH) && (row != GIFTRECEIVER)) {
                if ((ch >= 'A') && (ch <= 'Z') || (ch >= 'a') && (ch <= 'z') || (ch == ' ') ||
                    ((ch >= '!') && (ch <= '@'))) { // Special characters + numbers
                    
                    buffer[counter++] = ch;
                    addch(ch);
                }
            }
            else if (counter < STRING_LENGTH){
                if ((ch >= 'A') && (ch <= 'Z') || (ch >= 'a') && (ch <= 'z') || (ch == ' ')){
                    // For receiver name only letters are available
                    buffer[counter++] = ch;
                    addch(ch);
                }
            }
        }

        counter = 0; // reset counter
    
    mvhline(printrow, 0, ' ', MAX_CHARACTERS);
    if (buffer[0] == '\0') mvprintw(printrow, 0, "You entered: <empty> %s", type.c_str());
    else mvprintw(printrow, 0, "You entered: %s %s", buffer,type.c_str());
    return buffer;
}