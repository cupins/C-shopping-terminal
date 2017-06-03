/**
* Reid Stuberg and Kevin Couture
* TCES 202
* Winter 2015   Project
*
* This contains the menu and sub menu that are used by the customer.
* It displays the customer menu and the sub menu to display the products.
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
void displayCustomerMenu(Prod*, Trans*, char[], char[], char[]);
void customerProdMenu(Prod *); /* call displayProducts() */

/**|||||||||||||||||||||||||||||| FUNCTIONS||||||||||||||||||||||||||||**/

/*************************************************************************
* Arguments/Parameters: A product list pointer and transaction list pointer
* and the customers credentials -> 3 strings for first and last name
* and the last string is for the address.
*
* This function displays the customer's main menu. The customer can choose
* whatever type of function they want and the program corresponds to that.
*
*************************************************************************/
void displayCustomerMenu(Prod *p, Trans *t, char f_name[], char l_name[], char address[]){
    Prod ShoppingCart = NULL; /// What has the customer added to their cart?

    printf("\n\n\n      Welcome %s", f_name);
    int custExit = 0; // used to exit this menu
    char custChoice = '?'; // used to imply functions chosen by owner

    while(custExit != 1){
        printf("\n            Customer Menu");
        printf("\n+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+");
        printf("\n| 1.| Display products.                 |");
        printf("\n| 2.| Search for product by name.       |");
        printf("\n| 3.| Add a product to shopping cart.   |");
        printf("\n| 4.| Buy products in your cart.        |");
        printf("\n| 5.| Exit back to the main menu.       |");
        printf("\n+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+");

        printf("\n\nEnter in an integer corresponding to the menu: ");
        scanf("%c", &custChoice);
        fflush(stdin);

        switch (custChoice){
        case '1' :
            printf("\n       DISPLAY PRODUCTS: \n");
            customerProdMenu(&*p); /* goes to sub-menu */
            break;
        case '2' :
            printf("\n     SEARCH FOR A PRODUCT: \n");
            searchProdName(&*p); /* search for a product by ID  */
            break;
        case '3' :
            printf("\n      ADD PRODUCT TO CART: \n");
            customerAddProd(&*p, &ShoppingCart); /* add a product to shopping cart  */
            break;
        case '4' :
            printf("\n        PURCHASE PRODUCTS: \n"); /* buy products in shopping cart  */
            buyProducts(&ShoppingCart, &*p, &*t, f_name, l_name, address);
            break;
        case '5' :
            printf("\nExiting customer menu...\n"); /* call exit() for customer */
            custExit = 1;
            exitCustomer(&ShoppingCart);
            break;
        default :
            printf("\nInvalid input try again");
            break;
        }
    }
    printf("    Goodbye, %s", f_name);
}

/*************************************************************************
* Arguments/Parameters: A pointer head node for product list.
*
* This function creates a product in the product list. It asks the user for
* input and the user cannot add an ID that has already been entered (no exit).
*************************************************************************/
void customerProdMenu(Prod *p){

    printf("\n            Display Menu");
    printf("\n================================================");
    printf("\n| 1. Display products.                 ");
    printf("\n| 2. Sort products by amount (ascending order).  ");
    printf("\n| 3. Sort products by price (ascending order).   ");
    printf("\n=================================================");
    printf("\n\n Enter in an integer corresponding to the menu. ");

    char input;
    scanf("%c", &input);
    fflush(stdin);
    // Parse for good input
    while (input != '1' && input != '2' && input != '3'){

        printf("\nYou have entered an invalid input please try again. ");
        scanf("%c", &input);
        fflush(stdin);
    }
    if (input == '1'){ /// display products
        printProducts(&*p);
    } else if (input == '2'){ /// sort products by amount
        bubbleSortStock(&*p);
        printProducts(&*p);
    } else { /// sort products by price
        bubbleSortPrice(&*p);
        printProducts(&*p);
    }
    //back to customer menu
}
/**|||||||||||||||||||||||||| END FUNCTIONS |||||||||||||||||||||||||||**/
