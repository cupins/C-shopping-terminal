/**
* Reid Stuberg and Kevin Couture
* TCES 202
* Winter 2015   Project
*
* This file contains the Shopping System. It contains main() and
* implements a Owner and Customer menu which have certain
* behaviors defined by the instruction what the user needs to do.
*
**/

/// HEADERS
#include <stdio.h>
#include <stdlib.h>
#include "global.h"
#include <string.h>

/// CONSTANTS
#define NAME_LEN 50

/// PROTOTYPES
void displayOwnerMenu(Trans*, Trans*, Prod*);

/**|||||||||||||||||||||||||||||| FUNCTIONS||||||||||||||||||||||||||||**/

/*************************************************************************
* Arguments/Parameters: Initialized 2 transaction list pointers and one
* for a product list pointer.
*
* Displays the Owner's menu and implements the functions described
* inside the main menu.
*************************************************************************/
void displayOwnerMenu(Trans *t, Trans *recentT, Prod *p){

    printf("\n\n\n            Welcome Owner");
    int ownerExit = 0; // used to exit this menu
    char ownerChoice = '?'; // used to imply functions chosen by owner

    while(ownerExit != 1){
        printf("\n            Owner Menu");
        printf("\n+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+");
        printf("\n| 1.| Display products                  |");
        printf("\n| 2.| Add a product                     |");
        printf("\n| 3.| Delete a product by ID            |");
        printf("\n| 4.| Edit a product by ID              |");
        printf("\n| 5.| View recent transactions          |");
        printf("\n| 6.| Delete recent transactions        |");
        printf("\n| 7.| View all transactions             |");
        printf("\n| 8.| Delete all transactions           |");
        printf("\n| 9.| Exit back to the main menu        |");
        printf("\n+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+");

        printf("\n\nEnter in an integer corresponding to the menu: ");
        scanf("%c", &ownerChoice);
        fflush(stdin);

        switch (ownerChoice){
        case '1' :
            printf("\n       DISPLAY PRODUCTS: \n");
            printProducts(&*p); /* call displayProducts() */
            break;
        case '2' :
            printf("\n         ADD A PRODUCT: \n");
            creatProduct2(&*p); /* call addProducts()  */
            break;
        case '3' :
            printf("\n       DELETE A PRODUCT: \n");
            deleteProductID(&*p); /* call deleteProduct()  */
            break;
        case '4' :
            printf("\n         EDIT A PRODUCT: \n"); /* call editProduct()  */
            editProduct(&*p);
            break;
        case '5' :
            printf("\n       VIEW RECENT TRANSACTIONS: \n");
            viewAllTransactions(&*recentT); /* call viewRecentTrans()  */
            break;
        case '6' :
            printf("\n      DELETE RECENT TRANSACTIONS: \n");
            deleteAllTransactions(&*recentT); /* call deleteRecentTrans()  */
            break;
        case '7' :
            printf("\n         VIEW ALL TRANSACTIONS: \n");
            printf("\n  Recent Transactions: \n");
            viewAllTransactions(&*recentT); /* call viewRecentTrans()  */
            printf("\n  Transactions: \n");
            viewAllTransactions(&*t); /* call viewAllTrans()  */
            break;
        case '8' :
            printf("\n        DELETE ALL TRANSACTIONS: \n");
            printf("\n  Delete Recent Transactions... \n");
            deleteAllTransactions(&*recentT);
            printf("\n  Delete Transactions... \n");
            deleteAllTransactions(&*t); /* call deleteAllTrans()  */
            break;
        case '9' :
            printf("Exiting owner menu"); /* call exit()  */
            ownerExit = 1;
            break;
        default :
            printf("\nInvalid input try again");
            break;
        }
    }
}

/**|||||||||||||||||||||||||| END FUNCTIONS |||||||||||||||||||||||||||**/
