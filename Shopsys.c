/**
* Reid Stuberg and Kevin Couture
* TCES 202
* Winter 2015   Project
*
* This file contains the Shopping System. It contains main() and
* implements and the main_menu functions. It also contains the creation
* and use of the main product/transaction I/O. The file I/O is
* implemented in main so it can be used throughout the program.
*
**/

/// HEADERS
#include <stdio.h>
#include <stdlib.h>
#include "global.h"
#include <stdbool.h>
#include <string.h>

/// CONSTANTS
#define NAME_LEN 50

/// PROTOTYPES
bool credentialsExists(char[], char[]);
void main_menu(Trans*, Prod*);
void exitProgram( Prod*, Trans*);

/**|||||||||||||||||||||||||||||| FUNCTIONS||||||||||||||||||||||||||||**/

int main() {
    /// Get Products kept on file from last terminal use
    Prod p = NULL;
    getProducts(&p);

    /// Get Transactions kept on file from last terminal use
    Trans t= NULL;
    getTransactions(&t);

    /// Implement the program
    main_menu(&t, &p);
    /// Program falls through after exiting main menu
 ///   exitProgram(); /// Writes the updated product file and appends new transactions
    return 0;
}

/*************************************************************************
* Arguments/Parameters: Initialized transaction list t and product list p
*
* This function displays the main menu, it hard codes the owners
* information and goes to a sub_menu if it is chosen. It also parses user
* input to see if the right owner is selected.
*************************************************************************/
void main_menu(Trans *t, Prod *p){
    /// Initialize  Transaction use in the terminal
    Trans customerTransactions = NULL;
    // Customer buffer
    char f_name[NAME_LEN];
    char l_name[NAME_LEN];
    char address[NAME_LEN];
    // Owner buffer
    char login[NAME_LEN];
    char password[NAME_LEN];
    // menu parsing booleans
    bool isOwner = false;
    bool isCustomer = false;

    char niceTry = '?';
    char split = '?'; // init to not = 0
    while(split != '0'){


        printf("\n                     Main Menu");
        printf("\n===================================================");
        printf("\nPress 0 to exit, 1 if you are a owner\nOR \nAny other key if you are a customer: ");
        split = getchar();
        int trys = 0;
        if ( split == '1'){
            do {
                if (trys >= 1){
                    printf("\nPress E to exit or anything else to continue: ");
                    scanf("%c", &niceTry);
                    fflush(stdin);
                        if (niceTry == 'e' || niceTry == 'E'){
                            isOwner = false;
                            break;
                        }
                }
                trys++;
                printf("\nLogin: (admin) ");
                scanf("%s", login);
                printf("\nPassword: (password) ");
                scanf("%s", password);
                getchar(); // closes scanner
                    // owner == admin, password for default
                isOwner = true;

            } while(credentialsExists(login, password) == false) ; // checks if comparison is same == true

        } else if(split == '0'){
            Trans bufferT = *t; // merge customer and old transactions
            if (bufferT == NULL){
                bufferT = customerTransactions;
            } else {
                while (bufferT->next != NULL){
                    bufferT = bufferT->next;
                }
                bufferT->next = customerTransactions;
            }
            exitProgram(&*p, &*t);
        } else {
            if (split != '1'){ /* Owner attempt already tried */
                isCustomer = true;
                // Customer name and addr needed
                printf("\nEnter your first name: ");
                scanf("%s", f_name);
                getchar();
                printf("\nEnter your last name: ");
                scanf("%s", l_name);
                getchar();
                printf("\nEnter your address: ");
                scanf("%s", address);
                getchar(); // closes scanner

            }else {
                // do nothing
            }
        }

        if (isOwner == true){ // rights are true when owner
            displayOwnerMenu(&*t, &customerTransactions, &*p);
        } else if (isCustomer == true) { // the person is a customer
            displayCustomerMenu(&*p, &customerTransactions, f_name, l_name, address);
        }
        isCustomer = false; // reinit the people after sub menu displayed
        isOwner = false;
    }
    // if exited drops out of function

}

/*************************************************************************
* Arguments/Parameters: login string and password string (credentials)
*
* Used for the Main Menu for the owner
* Does the password exist?
* Returns true if it is the same as the owners credentials false otherwise.
*************************************************************************/
bool credentialsExists(char login[], char password[]){
    if ((strcmp(login, "admin") == 0) && (strcmp(password, "password") == 0 )){
        return true;
    } else {
        printf("\nIncorrect owner credentials, try again.");
        return false;
    }
}

/*************************************************************************
* Arguments/Parameters: A product list and a transaction list
*
* Used when the person on the terminal quits the main menu. It deletes all
* of the memory being used and writes to the product.txt and tran.. texts
* with the appropriate lists and format.
*************************************************************************/
void exitProgram(Prod *p, Trans *t){
    setProducts(&*p);
    setTransactions(&*t);

    Prod p1 = *p;
    Prod p2 = p1;
    while (p1 != NULL){
        p2 = p2->next;
        free(p1->name);
        free(p1->ID);
        free(p1);
        p1 = p2;
    }
    *p = NULL;

    Trans t1 = *t;
    Trans t2 = t1;
    while (t1 != NULL){
        t2 = t2->next;
        free(t1->f_name);
        free(t1->l_name);
        free(t1->address);
        free(t1);
        t1 = t2;

    }
    *t = NULL;
}

/**|||||||||||||||||||||||||| END FUNCTIONS |||||||||||||||||||||||||||**/

