#include <stdio.h>
#include <stdlib.h>

#include "funcs.h"
#include "password.h"

// Use extern to define it in external files (such as in main.c)
extern PasswordEntry g_entries[MAX_PASSWORDS];
extern int g_password_count;

// Defining function menu_item_1 to show current passwords
void menu_item_1(void) {
    int choice = -1;
    char line[64];

    printf("\n>> Menu 1: Current Passwords\n");

    // Loading file to show latest data
    load_passwords(g_entries, &g_password_count);

    do{
        // Print current passwords
        show_current_passwords(g_entries, g_password_count);

        printf("\nOptions:\n");
        printf("1. Add a new password\n");
        printf("2. Delete an existing password\n");
        printf("0. Return to main menu\n");
        printf("Select an option: ");

        // Handle error, for string & other types of value
        if (!fgets(line, sizeof(line), stdin)) {
            printf("\nINPUT ERROR\n");
            return;
        }

        // If number is not inserted
        if (sscanf(line, "%d", &choice) != 1) {
            printf("Please enter a number!\n");
            continue;
        }    

        switch(choice){
            case 1:
                add_password(g_entries, &g_password_count);
                save_passwords(g_entries, g_password_count);
                break;
            case 2:
                remove_password(g_entries, &g_password_count);
                save_passwords(g_entries, g_password_count);
                break;
            case 0:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid option! Please choose 0, 1 or 2!\n\n");
        }
    } while (choice!=0);
}

// Defining function menu_item_2 to export passwords to CSV file
void menu_item_2(void) {
    printf("\n>> Menu 2: Export Passwords to CSV File\n");
    
    load_passwords(g_entries, &g_password_count);
    export_passwords_csv(g_entries, g_password_count);
}

// Defining function menu_item_3 to exit the program
void menu_item_3(void) {
    printf("Exiting program...\n"); 
    exit(0);
}
