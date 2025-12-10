#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "funcs.h"
#include "password.h"

// Global accessible from funcs.c
PasswordEntry g_entries[MAX_PASSWORDS];
int g_password_count = 0;

void main_menu(void);               // Runs in the main loop
void print_main_menu(void);         // Output the main menu text
int  get_user_input(void);          // Get a valid integer menu choice
void select_menu_item(int input);   // Run code based on user's choice
void go_back_to_main(void);         // Wait for 'b'/'B' to continue
int  is_integer(const char *s);     // Validate integer string

int main(void)
{
    // Seed random numbers for password generation
    srand((unsigned int)time(NULL));

    // Load existing password
    load_passwords(g_entries, &g_password_count);

    // Run program forever until exit(0) is called
    for(;;) {
        main_menu();
    }
    // Not reached
    return 0;
}

void main_menu(void)
{
    print_main_menu();
    {
        int input = get_user_input();
        select_menu_item(input);
    }
}

// Reading user input
int get_user_input(void)
{
    enum{ MENU_ITEMS = 5 }; 
    char buf[128];
    int valid_input = 0;
    int value = 0;

    do{
        printf("\nSelect item: ");
        if(!fgets(buf, sizeof(buf), stdin)) {
            // Handle error or end of file
            puts("\nInput error! Exiting...");
            exit(1);
        }

        // Strip trailing newline
        buf[strcspn(buf, "\r\n")] = '\0';

        // Validating input
        if(!is_integer(buf)) {
            printf("Enter an integer!\n");
            valid_input = 0;
        } else{
            value = (int)strtol(buf, NULL, 10);
            if(value >= 1 && value <= MENU_ITEMS) {
                valid_input = 1;
            } 
            else{
                printf("Invalid menu item!\n");
                valid_input = 0;
            }
        }
    } 
    while(!valid_input);
    return value;
}

void select_menu_item(int input)
{
    switch(input){
        case 1:
            menu_item_1();
            go_back_to_main();
            break;
        case 2:
            menu_item_2();
            go_back_to_main();
            break;
        case 3:
            menu_item_3();
            go_back_to_main();
            break;
        default:
            printf("Bye!\n");
            exit(0);
    }
}

void print_main_menu(void)
{
    printf("\n----------- Main menu -----------\n");
    printf("\n"
           "\t\t\t\t\t\t\n"
           "\t1. Current passwords\t\t\n"
           "\t2. Export passwords to CSV file\t\t\n"
           "\t3. Exit\t\t\t\t\n"
           "\t\t\t\t\t\t\n");
    printf("-----------------------------------\n");
}

void go_back_to_main(void)
{
    char buf[64];
    do{
        printf("\nEnter 'b' or 'B' to go back to main menu: ");
        if(!fgets(buf, sizeof(buf), stdin)) {
            puts("\nInput error. Exiting.");
            exit(1);
        }
        buf[strcspn(buf, "\r\n")] = '\0';
    } 
    while(!(buf[0] == 'b' || buf[0] == 'B') || buf[1] != '\0');
}

int is_integer(const char *s)
{
    if(!s || !*s) return 0;

    if(*s == '+' || *s == '-') s++;

    if(!isdigit((unsigned char)*s)) return 0;

    while(*s) {
        if(!isdigit((unsigned char)*s)) return 0;
        s++;
    }
    return 1;
}