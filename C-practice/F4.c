#include <stdio.h>

int days_in_month(int month);

int main(){
    int month;

    int days = 0;

    char array[12][10] = {"January","February","March","April","May","June","July","August","September","October","November","December"};

    printf("Give month: ");
    scanf("%d",&month);
    while ((month < 1) || (month > 12)){
        printf("Give month: ");
        scanf("%d",&month);
    }

    days = days_in_month(month);

    printf("There are %d days in %s",days,array[month-1]);

}

int days_in_month(int month){
    int days;
    switch(month){
        case 1:
        days = 31;
        break;
        case 2:
        days = 28;
        break;
        case 3:
        days = 31;
        break;
        case 4:
        days = 30;
        break;
        case 5:
        days = 31;
        break;
        case 6:
        days = 30;
        break;
        case 7:
        days = 31;
        break;
        case 8:
        days = 31;
        break;
        case 9:
        days = 30;
        break;
        case 10:
        days = 31;
        break;
        case 11:
        days = 30;
        break;
        case 12:
        days = 31;
        break;
    }

    return days;
}