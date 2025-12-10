#ifndef PASSWORD_H
#define PASSWORD_H

#define MAX_PASSWORDS 20
#define MAX_FIELD_LEN 128
#define DATA_FILE "passwords.txt"
#define CSV_FILE  "passwords.csv"

typedef struct {
    char service[MAX_FIELD_LEN];
    char username[MAX_FIELD_LEN];
    char password[MAX_FIELD_LEN];
} PasswordEntry;

void load_passwords(PasswordEntry entries[], int *count);
void save_passwords(PasswordEntry entries[], int count);
void export_passwords_csv(PasswordEntry entries[], int count);

void show_current_passwords(PasswordEntry entries[], int count);
void add_password(PasswordEntry entries[], int *count);
void remove_password(PasswordEntry entries[], int *count);

#endif
