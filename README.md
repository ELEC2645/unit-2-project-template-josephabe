[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-2972f46106e565e64193e422d61a12cf1da4916b45550586e14ef0a7c637dd04.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=21824063)
# ELEC2645 Unit 2 Project: Password Manager with Random Password Generator

Welcome to the Password Manager Application! :D

This application is a simple menu-driven password manager that can both generate and store passwords for multiple services. Users can view all current passwords (each with a service name, username, and password), add a new password, or remove an existing password. 

The program generates random password according to the desired length and how many capital letters, digits, and special characters it is requested by the users. The program uses C’s pseudorandom number generator to build passwords and then shuffles them to avoid predictable patterns. All passwords are saved to a .txt file so they are loaded again the next time the program runs. Users can also export the stored passwords to a CSV file for backup.

### 1 Run code

First, compile the code by typing `gcc main.c funcs.c password.c -o main.out` in the terminal

Then run the code with `./main.out`

OR

compile with `gcc main.c funcs.c password.c -o password_manager` and run with `./password_manager`




### 3 Test command

The `test.sh` script is provided to check that your code compiles correctly. This is what the autograder will use to check your submission. You can run it with `bash test.sh` or `./test.sh` or just `make test`. 

You do not need to modify this script, but you can look at it to see what it does.


### 4 Submit Solution

Use the same method as previous labs to commit and push your code to your GitHub repository for the autograder to check. 

In your final journal post, please include a link to your GitHub repository containing your code  *and* a zip file of your code as an attachment.
