#include <stdio.h>
#include <string.h>

//the data of each customers
struct Database {
    char name[50];
    char number[50];
    int balance;
};

// We created this function for easy separation when needed for a better visual output
void separator(){
     printf("\t\t========================================\n");
}

// We created this function for easy separation when needed for a better visual output
void NewLine(){
    printf("\n");
}

// This is a Function to display the main user interface
void interface() {
    printf("\n\t\t========================================\n");
    printf("\t\tWelcome to Customer Billing System!");
    printf("\n\t\t========================================\n");
    printf("\t\t1.\tAdd Account\n");
    printf("\t\t2.\tSearch Account by Username\n");
    printf("\t\t3.\tSearch Account by ID\n");
    printf("\t\t4.\tDisplay All Customers\n");
    printf("\t\t5.\tExit");
    printf("\n\t\t========================================\n");
}

// This is a Function that checks if a customer with the given name or number already exists
// It compares the each characters of the input using strcmp
int checkDuplicate(struct Database customers[], int totalCustomers, char name[], char number[]) {
    int i;
    for (i = 0; i < totalCustomers; i++) {
        if (strcmp(customers[i].name, name) == 0 || strcmp(customers[i].number, number) == 0) {
            return 1; //if a duplicate is found
        }
    }
    return 0; // if no duplicate found
}

void displayAllCustomers(struct Database customers[], int totalCustomers) {
    separator();
    printf("\t\tDisplaying All Customers:\n");
    separator();

    int i;
    for (i = 0; i < totalCustomers; i++) {
        printf("\t\tName: %s\n\t\tAccount ID: %s\n\t\tBalance: Php %d\n",
        customers[i].name, customers[i].number, customers[i].balance);
        separator();
    }
    separator();
}

//The main function, this is where our code starts
int main() {

    struct Database customers[100]; // this is an array to store customer data
    int totalCustomers = 0; // this is a variable to track the total number of customers
    int choice; // this is a variable to store user input for menu choice

    // Infinite loop for the main menu
    while (1) {
    interface();// Our function to Display the main menu, it calls the void interface() function
    
    printf("\t\tEnter Choice: "); //Promts the user for their choice
    int result = scanf("%d", &choice); // Gets user input and store it into the choice variable (int choice)


    if (result != 1) {
            while (getchar() != '\n');
            printf("\t\tInvalid input. Please enter a number.\n");
            continue;
        }

    //if choice is equals to 1, it run this part of the code
    if (choice == 1) {
    // In this part you can add a new accounts
    if (totalCustomers < 100) {

        char tempName[50]; // Declares a temporary array to store the entered account name
        char tempNumber[50]; // Declare a temporary array to store the entered account number

        separator();
        printf("\t\tEnter Account Username: ");
        scanf("%s", tempName); // Reads the entered account Username from the user and store it in tempName

        printf("\t\tEnter Account ID: ");
        scanf("%s", tempNumber); // Reads the entered account ID from the user and store it in tempNumber

        // Checks for a duplicate accounts before adding
        if (checkDuplicate(customers, totalCustomers, tempName, tempNumber)) {
            separator();
            // if a duplicate is found it will print this:
            printf("\t\tAccount with this name or ID already exists!\n");
            printf("\t\tPlease create a different account!\n");
            separator();

        }

        // Adds the new account
        //if there's no duplicate for the newly created account, it proceeds here
        else {
            strcpy(customers[totalCustomers].name, tempName);
            strcpy(customers[totalCustomers].number, tempNumber);
            separator();
            printf("\t\tAccount Name \"%s\" with the\n\t\tAccount ID \"%s\" has been added!",
            customers[totalCustomers].name, customers[totalCustomers].number);

            customers[totalCustomers].balance = 0;
            totalCustomers++;
        }
    }
}
    //if choice is equals to 2 OR 3, it run this part of the code:
    else if (choice == 2 || choice == 3) {
    char searchValue[50];

        // This is an option to search for an account by name or number
        //if your choice is 2, it will ask for Username
        if (choice == 2) {
            printf("\t\tEnter Account Username: ");
        }
        
        //if your choice is 3, it will ask for ID
        else {
            printf("\t\tEnter Account ID: ");
        }

    scanf("%s", searchValue);// Gets user input and store it into the searchValue ARRAY

    int found = 0;
    int i;//for forloop, separated because dev C cant run if its inside the for loop :>

    // Iterate through existing customers to find the matching account
    for (i = 0; i < totalCustomers; i++) { //adjusts the array so that we can add infinite accounts
    if ((choice == 2 && strcmp(customers[i].name, searchValue) == 0) || //finds the inputed name and compares customers[i].name and searchValue
        (choice == 3 && strcmp(customers[i].number, searchValue) == 0)) { //if found the particular name or number, it calls that part of the array or (customer account)
        separator();
        printf("\t\tWelcome %s!\n", customers[i].name);

        int customerChoice;
        // Inner loop for customer-specific operations
        do {
        separator();
        printf("\t\tWhat do you want to do?\n");
        printf("\t\t1.\tCheck Balance\n");
        printf("\t\t2.\tAdd Due Amount\n");
        printf("\t\t3.\tDeposit Money\n");
        printf("\t\t4.\tWithdraw Money\n");
        printf("\t\t5.\tExit\n");
        separator();

        printf("\t\tEnter Your Choice: ");
        scanf("%d", &customerChoice);

        // Switch statement for customer-specific choices
        switch (customerChoice) {

            //if customerChoice is equals to 1, case 1 will run until break;
            case 1:
                separator();
                printf("\t\tYour balance is: Php %d\n", customers[i].balance);
                break;

            //if customerChoice is equals to 2, case 2 will run until break;
            case 2:
                separator();
                int amountToAdd; //variable for due amount, this also accepts negative numbers
                printf("\t\tEnter Due Amount: ");
                scanf("%d", &amountToAdd); //gets the input and stores it to dueAmount variable

                customers[i].balance -= amountToAdd;//formula for dueAmount, gets the customers balance and deduct it to dueAmount variable
                printf("\t\tYou Added Php%d As Due Amount!\n", amountToAdd);
                printf("\t\tYour Balance is: Php %d!\n", customers[i].balance);
                break;

            //if customerChoice is equals to 3, case 3 will run until break;
            case 3:
                separator();
                printf("\t\tEnter Amount to deposit: ");
                
                int depAmount; //variable for deposit amount, this only adds to the customers balance
                scanf("%d", &depAmount); //gets the input and stores it to depAmount variable

                customers[i].balance += depAmount; //formula for depAmount, gets the customers balance and adds the value inside depAmount
                separator();
                printf("\t\tYou Added Php%d To Your Account!\n",depAmount); //shows the amount you've added
                printf("\t\tYour balance is now: Php%d!\n", customers[i].balance);  //shows your new balance
                break;

            //if customerChoice is equals to 4, case 4 will run until break;
            case 4:
                separator();
                printf("\t\tEnter Amount to Withdraw: ");

                int withDraw = 0;//variable for withDraw amount, this doesn't accept overwithdrawal/negative numbers
                scanf("%d", &withDraw);//gets the input and stores it to withDraw variable

                //checks the amount you've withdrawed
                //if withdrawal amount is GREATER than your balance, it will proceed to this part will run until "}"
                if (withDraw > customers[i].balance) {
                    separator();
                    printf("\t\tInsufficient Balance!\n");
                    printf("\t\tYou Only Have Php%d In Your Account!\n",customers[i].balance);
                }
                
                //checks the amount you've withdrawed
                //if withdrawal amount is LESS than your balance, it will proceed to this part will run until "}"
                else {
                    customers[i].balance -= withDraw;//formula for withdrawal, this will take your balance and deduct it to the withDraw amount
                    separator();
                    printf("\t\tYou Withdrawed Php%d From Your Account!\n",withDraw); //shows your withdrawal amount
                    printf("\t\tYour New Balance Is: Php%d!\n", customers[i].balance); //shows you new balance
                }
                break;

            //if customerChoice is equals to 5, case 5 will run until break;
            case 5:
                separator();
                printf("\t\tGoodbye %s!", customers[i].name); //prints this goodbye message with the customers name
                break;

            //if customerChoice is not numbers 1-5, it will run this part until break;
            default:
                separator();
                printf("\t\tInvalid Choice!\n");
                printf("\t\tPlease Select From 1-5\n");
                break;
        }
    }

        while (customerChoice != 5);

        found = 1;// Account found
        break;
    }
}
        //if the account was NOT found
        if (!found) {
            if (choice == 2) {
                printf("\t\tThere's no Customer with name %s\n", searchValue);//prints this part if the choice was 2
            }
            
            else {
                printf("\t\tThere's no Customer with Account ID %s\n", searchValue);//prints this part if the choice was 3
            }
        }
    }

        //if choice is equals to 4, It displays all the accounts in the array
        else if (choice == 4) {
        displayAllCustomers(customers, totalCustomers);
        }
        
        //Exits the program if choice is 5
        else if (choice == 5) {
            break;
        }
        
        //this part displays a message for an invalid menu choice
        else {
            printf("\t\tInvalid Choice!");
        }
    }
    
    separator();
    printf("\t\tGoodBye!, See You Next Time :)\n"); //prints this code if your choice was 5
    separator();
    return 0;
}
