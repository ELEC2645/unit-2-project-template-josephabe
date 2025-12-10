#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "password.h"

// Reading line from stdin into buffer safely
void read_line(char *buffer, int size){
    if(fgets(buffer, size, stdin) != NULL){
        int len = strlen(buffer);
        
        if(len>0 && buffer[len-1] == '\n'){
            buffer[len-1] = '\0';
        }
    }
    else {
        if(size>0) {buffer[0] = '\0';}
    }
}

// Checking whether it is digits or not
// Return 1 if s is not empty and contains only digits 0-9, otherwise 1
int is_all_digits(const char *s){
    if(*s == '\0'){     // EMPTY STRING
        return 0;
    }
    while(*s){
        if(*s < '0' || *s>'9'){
            return 0;
        }
        s++;
    }
    return 1;           // ALL CHARACTERS ARE DIGIT
}

// Shuffle randomly character order to make the password random
void shuffle_string(char *str) {
    int len = strlen(str);
    if(len <= 1) {return;}

    for (size_t i = len - 1; i > 0; i--) {
        size_t j = (size_t)(rand() % (int)(i + 1));
        char tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
    }
}

// Generate random password with the asked requirements
void generate_password( char *out,
                        int length,
                        int num_upper,
                        int num_digits,
                        int num_special){
    const char *lower_chars = "abcdefghijklmnopqrstuvwxyz"; // Defining the characters as constant
    const char *upper_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char *digit_chars = "0123456789";
    const char *special_chars = "!@#$^&*()-_=+";
    char temp[MAX_FIELD_LEN]; // Temporary local storage for password
    int pos = 0;

    // Add required uppercase letters
    for(int i=0; i < num_upper && pos < length; i++){
        temp[pos++] = upper_chars[rand() % (int)strlen(upper_chars)];
    }

    // Add required digits
    for(int i=0; i < num_digits && pos < length; i++){
        temp[pos++] = digit_chars[rand() % (int)strlen(digit_chars)];
    }
    
    // Add required unique characters
    for(int i=0; i < num_special && pos < length; i++){
        temp[pos++] = special_chars[rand() % (int)strlen(special_chars)];
    }

    // Fill remaining characters with random lowercase
    while(pos<length){
        temp[pos++] = lower_chars[rand() % (int)strlen(lower_chars)];
    }

    temp[length] = '\0';

    // Shuffle order randomly
    shuffle_string(temp);

    strncpy(out, temp, MAX_FIELD_LEN-1); // Copy the password from temp to output (safer)
    out[MAX_FIELD_LEN-1] = '\0'; // Ends string with '\0' so it is a safe string
}

// Load passwords from the txt file
void load_passwords(PasswordEntry entries[], int *count){
    FILE *fp = fopen(DATA_FILE, "r");
    char line[256];
    *count = 0;

    // Start empty
    if(!fp){
        return;
    }
    
    while(fgets(line, sizeof(line), fp) != NULL && *count < MAX_PASSWORDS){
        char *service = strtok(line, "|"); // Splits the line 
        char *username = strtok(NULL, "|");
        char *password = strtok(NULL, "|\n");

        if(service && username && password){

        strncpy(entries[*count].service, service, MAX_FIELD_LEN - 1); // Copy service into struct
        entries[*count].service[MAX_FIELD_LEN - 1] = '\0';

        strncpy(entries[*count].username, username, MAX_FIELD_LEN - 1); // Copy username into struct
        entries[*count].username[MAX_FIELD_LEN - 1] = '\0';

        strncpy(entries[*count].password, password, MAX_FIELD_LEN - 1); // Copy password into struct
        entries[*count].password[MAX_FIELD_LEN - 1] = '\0';

        (*count)++;
        }
    }
    fclose(fp);
}

// Save all current password to the txt file
void save_passwords(PasswordEntry entries[], int count){
    FILE *fp = fopen(DATA_FILE, "w"); // uses .txt file for password 'bank'

    if(!fp){
        printf("ERROR! Could not open %s for writing\n", DATA_FILE);
        return;
    }

    // Writes each password entry to the file (service|username|password)
    for(int i=0; i<count; i++){
        fprintf(fp, "%s|%s|%s\n",
                entries[i].service,
                entries[i].username,
                entries[i].password);
    }
    fclose(fp);
}

// Export all current passwords to a CSV file
void export_passwords_csv(PasswordEntry entries[], int count){
    FILE *fp = fopen(CSV_FILE, "w"); // Produces CSV File
    if(!fp){
        printf("ERROR! Could not open %s for writing\n", CSV_FILE);
        return;
    }

    // Writes each password entry to the CSV file (service|username|password)
    fprintf(fp, "Service, Username, Password\n");
    for(int i=0;i < count; i++){
        fprintf(fp, "%s,%s,%s\n",
                entries[i].service,
                entries[i].username,
                entries[i].password);
    }

    fclose(fp);
    printf("Exported %d password(s) to %s\n", count, CSV_FILE);
}

// Show current passwords
void show_current_passwords(PasswordEntry entries[], int count){
    if(count==0){
        printf("No password saved\n"); // NO PASSWORDS IN TXT FILE
        return;
    }
    
    printf("\n#  %-20s %-20s %-20s\n", "Service", "Username", "Password");
    printf("---------------------------------------------------------\n");
    for(int i = 0; i < count; i++){
        printf("%-2d %-20s %-20s %-20s\n",
               i + 1,
               entries[i].service,
               entries[i].username,
               entries[i].password);
    }
}

void add_password(PasswordEntry entries[], int *count){
    char buffer[256];

    // Limit maximum passwords (in this model is 20, can be added more with some modification)
    if(*count >= MAX_PASSWORDS){
        printf("Cannot add more password, maximum of %d reached!\n", MAX_PASSWORDS);
        return;
    }

    printf("\n=== Add New Password ===\n");
    printf("Type 00 at any prompt to cancel\n");

    printf("Enter service name: ");
    read_line(buffer, sizeof(buffer)); // Gets service name from user input
    if(strcmp(buffer, "00") == 0) { // Type '00' to cancel and return to menu
        printf("Add password cancelled\n");
        return;
    }
    strncpy(entries[*count].service, buffer, MAX_FIELD_LEN - 1);
    entries[*count].service[MAX_FIELD_LEN - 1] = '\0';

    printf("Enter username: ");
    read_line(buffer, sizeof(buffer)); // Gets username from user input
    if (strcmp(buffer, "00") == 0) { // Type '00' to cancel and return to menu
        printf("Add password cancelled\n");
        return;
    }
    strncpy(entries[*count].username, buffer, MAX_FIELD_LEN - 1);
    entries[*count].username[MAX_FIELD_LEN - 1] = '\0';

    int length, num_upper, num_digits, num_special;

    while (1) {
        printf("Enter password length (1-%d) or 00 to cancel: ", MAX_FIELD_LEN - 1); // Gets password length from user input
        read_line(buffer, sizeof(buffer));
        if (strcmp(buffer, "00") == 0) {
            printf("Add password cancelled\n");
            return;
        }
        if (!is_all_digits(buffer)) { // Check if input is digits
            printf("Please enter digits only\n");
            continue;
        }
        length = atoi(buffer);
        if (length < 1 || length >= MAX_FIELD_LEN) {
            printf("Please enter a valid length\n");
        } else {
            break;
        }
    }

    while (1) {
        printf("Enter number of capital letters or 00 to cancel: "); // Gets number of capital letters from user input
        read_line(buffer, sizeof(buffer));
        if (strcmp(buffer, "00") == 0) {
            printf("Add password cancelled\n");
            return;
        }
        if (!is_all_digits(buffer)) { // Check if input is digits
            printf("Please enter digits only\n");
            continue;
        }
        num_upper = atoi(buffer);
        if (num_upper < 0 || num_upper > length) {
            printf("Invalid number. Must be between 0 and %d\n", length);
        } else {
            break;
        }
    }

    while (1) {
        printf("Enter number of digits or 00 to cancel: "); // Gets number of digits from user input
        read_line(buffer, sizeof(buffer));
        if (strcmp(buffer, "00") == 0) {
            printf("Add password cancelled\n");
            return;
        }
        if (!is_all_digits(buffer)) { // Check if input is digits
            printf("Please enter digits only\n");
            continue;
        }
        num_digits = atoi(buffer);
        if (num_digits < 0 || num_digits > length) {
            printf("Invalid number! Must be between 0 and %d\n", length);
        } else {
            break;
        }
    }

    while (1) {
        printf("Enter number of special (unique) characters or 00 to cancel: "); // Gets number of unique characters from user input
        read_line(buffer, sizeof(buffer));
        if(strcmp(buffer, "00") == 0) {
            printf("Add password cancelled\n");
            return;
        }
        if(!is_all_digits(buffer)) { // Check if input is digits
            printf("Please enter digits only\n");
            continue;
        }
        num_special = atoi(buffer);
        if(num_special < 0 || num_special > length) {
            printf("Invalid number! Must be between 0 and %d\n", length);
        } else {
            break;
        }
    }

    if(num_upper + num_digits + num_special > length) { // Check if no of special characters is more than password length
        printf("Error: Sum of capitals, digits and unique characters exceeds length\n");
        printf("Add password cancelled\n"); // If it is, add password cancelled, return to menu
        return;
    }

    // Generating random password
    generate_password(entries[*count].password,
                             length,
                             num_upper,
                             num_digits,
                             num_special);

    printf("Generated password: %s\n", entries[*count].password);
    (*count)++;
    printf("Password added successfully\n");
}

// Removing password
void remove_password(PasswordEntry entries[], int *count) {
    char buffer[64];
    int index;

    if (*count == 0) {
        printf("No passwords to remove\n");
        return;
    }

    printf("\n=== Remove Password ===\n");
    show_current_passwords(entries, *count);
    printf("Enter password number to remove (1-%d), 0 to return, or 00 to cancel: ",
           *count);

    read_line(buffer, sizeof(buffer));

    if(strcmp(buffer, "00") == 0) {
        printf("Remove password cancelled\n");
        return;
    }

    if(strcmp(buffer, "0") == 0) {
        printf("Returning without removing\n");
        return;
    }

    if(!is_all_digits(buffer)) {
        printf("Invalid input\n");
        return;
    }

    index = atoi(buffer);
    if(index < 1 || index > *count) {
        printf("Invalid password number\n");
        return;
    }

    printf("Are you sure you want to remove password #%d? (y/n): ", index);
    read_line(buffer, sizeof(buffer));
    if(buffer[0] != 'y' && buffer[0] != 'Y') {
        printf("Removal cancelled\n");
        return;
    }

    for(int i = index - 1; i < *count - 1; i++) {
        entries[i] = entries[i + 1];
    }
    (*count)--;

    printf("Password removed\n");
}