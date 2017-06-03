/**
* Reid Stuberg and Kevin Couture
* TCES 202
* Winter 2015   Project
*
* This file contains the customer functions which alter the shopping cart
* created in customerMenu. These functions deal with buying a product,
* adding a product and deleting all the products in the shopping cart.
*
**/


/// INCLUDES
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "global.h"

/// PROTOTYPES
void buyProducts(Prod *, Prod *, Trans *, char [], char [], char []);
void exitCustomer(Prod *);
void updateProdList(Prod *, Prod *);
void customerAddProd(Prod *, Prod *);
void delProd(Prod *, char []);

/**|||||||||||||||||||||||||||||| FUNCTIONS||||||||||||||||||||||||||||**/

/*************************************************************************
* Arguments/Parameters: 2 product lists as pointers (shopping cart and
* the product text) transaction list pointer to create recent transactions
* the address, first and last name for the transaction list.
*
* This function buys products from a text and creates a recent transaction
* with what was in the shopping cart. The user is prompted if they want to
* buy the product list. If they buy it the product list *prodList is updated
* so that there other owners/customers know what happen. The shopping cart
* is unloaded into a transaction then deleted. The transaction will have
* the information from the customer login and shopping cart.
*************************************************************************/
void buyProducts(Prod *p, Prod *prodList, Trans *tz, char f_name[], char l_name[], char address[]){
    if (*p == NULL)
        return printf("\nThere are no products in your shopping cart. Returning to last menu.");

    printf("\n\n        Are you sure you want to buy the following products?\n");
    printProducts(&*p);
    printf("\n\nEnter '1' if you want to buy these products \nOR\nAnything else to return to the Customer Menu: ");
    char input[2];
    scanf("%s", input);
    fflush(stdin);

    if (input[0] == '1' && input[1] == '\0'){

    } else {
        return;
    }

    updateProdList(&*p, &*prodList); // updates the stock in the product list

    /// Customer wants to buy something then
    float totalCost = 0.0;
    Trans tr;
    // prepends transaction to transaction list
    tr = malloc(sizeof(struct Transaction)); // memory for transaction and allocates appropriate values
    tr->f_name = malloc(50);
    strcpy(tr->f_name, f_name);
    tr->l_name = malloc(50);
    strcpy(tr->l_name, l_name);
    tr->address = malloc(50);
    strcpy(tr->address, address);

    /// Get local time
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    tr->dd = t->tm_mon+1;
    tr->mm = t->tm_mday;
    tr->yy = t->tm_year+1900;

    tr->p = NULL; // list not defined yet will load/unload shopping cart to transaction
    /// pay wasn't declared because we have to cycle through the products

    Prod productList = tr->p; // loading transaction with shopping cart
    Prod head = NULL;
    Prod transProd  = *p; // deleting shopping cart
    Prod temp = transProd; // keeps track since stuff is deleted

    while (transProd != NULL){ // creates a copy of a list and deletes the cart

        productList = malloc(sizeof( struct Product)); // memory for copy

        productList->ID = malloc(30);
        strcpy(productList->ID, transProd->ID);
        productList->name = malloc(30);
        strcpy(productList->name,transProd->name);
        productList->num_unit = transProd->num_unit;
        productList->price = transProd->price;

        productList->next = tr->p; // tr->p defined already as null
        tr->p = productList;

        totalCost = totalCost + (transProd->num_unit*transProd->price); // update for transaction

        temp = temp->next;
        free(transProd->ID); // delete cart
        free(transProd->name);
        free(transProd);
        transProd = temp;
    }
    tr->pay = totalCost;
    *p = NULL; // update shopping cart so it's null (nothing in it)

    // prepended list
    tr->next = *tz;
    *tz = tr;

    printf("\nThank you for shopping here %s. You bought: \n", f_name);
    Prod printProds = tr->p;
    printProducts(&printProds);
    printf("\n\n            Your total was %f", totalCost);

}

/*************************************************************************
* Arguments/Parameters: Two product list pointers. (The shopping cart and
* product list)
*
* Helper function for buyProducts()
*
* The product list updates the number of units it has. This is done by
* checking the shopping cart and updating the stock.
*************************************************************************/
void updateProdList(Prod *i, Prod *j){
    Prod decrementStock = *i; // shopping cart
    Prod currentStock;
    Prod temp;

    while (decrementStock != NULL){

        currentStock = *j; // product list
        while(currentStock != NULL){

            if (strcmp(currentStock->ID,decrementStock->ID) == 0){ // found match
              currentStock->num_unit = currentStock->num_unit  - decrementStock->num_unit; // update stock
            }
            temp = currentStock; // traverse list
            currentStock = currentStock->next;
        }
        decrementStock = decrementStock->next;  // traverse cart
    }
}

/*************************************************************************
* Arguments/Parameters: A product list pointer or shopping cart pointer
*
* This deletes the linked list that was created. Used to delete the
* delete the shopping cart.
*************************************************************************/
void exitCustomer(Prod *p){
    if (*p == NULL)
        return;

    Prod temp = *p;
    Prod curr = temp;
    while (temp != NULL){
        temp = temp->next;

        free(curr->ID);
        free(curr->name);
        free(curr);

        curr = temp;
    }
    //*p = NULL;
}

/*************************************************************************
* Arguments/Parameters: Two product list pointers. (The shopping cart and
* product list)
*
* Adds a product to the product list shopping cart by matching the ID's
* from a product list. Merges a product (makes sure the stock doesn't exceed
* the total amount) if it already exists. Then creates a merged or new
* product for the shopping cart.
*************************************************************************/
void customerAddProd(Prod *p, Prod *shoppingCart){
    int exit = 0, stock, add_num_unit = 0, inShoppingCart = 0, mergeProd = 0;
    Prod pAdd;
    while (exit == 0){ // parsing loop
        printf("\nPlease enter in the product ID to add to the cart: ");
        char buff1[50];
        scanf("%s", buff1);
        fflush(stdin);
        printf("\nPlease enter in the amount to add to the cart: ");
        char buff2[50];
        scanf("%s", buff2);
        fflush(stdin);

        stock = atoi(buff2);
        Prod temp = *p;
        while(temp != NULL){

            if (strcmp(temp->ID, buff1) == 0){ // product exists
                if (temp->num_unit-stock >= 0){ /// can merge products?
                    if (*shoppingCart == NULL){ // first thing added?
                        add_num_unit = stock;
                        exit = 1;
                        pAdd = temp;
                    } else { /// Is there a item in the cart of same product already? if so merge or give error
                        exit = 1;

                        Prod cartBuffer = *shoppingCart;
                        while (cartBuffer != NULL){

                            if (strcmp(cartBuffer->ID, buff1) == 0){ // merge stock
                                add_num_unit = stock + cartBuffer->num_unit;
                                if (temp->num_unit-add_num_unit >= 0){ // correct amount of stock entered / no overflow
                                    inShoppingCart = 1;
                                    pAdd = temp;
                                    mergeProd = 1;
                                } else {
                                    printf("\nShopping cart cannot contain more product than stock. Please try again.\n");
                                    return;
                                } // end else
                            } // end if
                            cartBuffer = cartBuffer->next; // traverse list
                        }// end sc while
                        if (inShoppingCart == 0){ // not already in shopping cart? check
                            add_num_unit = stock;
                            pAdd = temp;
                        }
                    } // end else
                }
            }
            temp = temp->next; // traverse list
        } // end while
            if (exit == 0){
                printf("\nNo such product ID exists\nOR\nAmount of product chosen is greater than current stock.\n\n Press 1 to exit or any other key to continue: ");
                scanf("%s", buff1);
                fflush(stdin);
                if (buff1[0] == '1' && buff1[1] == '\0'){
                    return;
                }
            }
    } // exited parsing
    if (mergeProd == 1){ /// DELETES the product from the shopping cart because the add_num has the adjusted amount
        delProd(&*shoppingCart, pAdd->ID);
    }
    /// Allocate memory for the shopping list
    Prod curr;
    curr = malloc(sizeof(struct Product));

    curr->ID = malloc(50);
    strcpy(curr->ID,pAdd->ID);

    curr->name = malloc(50);
    strcpy(curr->name,pAdd->name);

    curr->num_unit = add_num_unit;
    curr->price = pAdd->price;

    // Was there a stock already in the shopping cart needing to be edited?

    /// Prepend the shopping list
    curr->next = *shoppingCart;
    *shoppingCart = curr;


}

/*************************************************************************
* Arguments/Parameters: Pointer of a product list(specifically shopping cart)
* and a target ID (product ID)
*
* Helper function for addProduct()
*
* Traverses a list to see if a product exists if it does it deletes it.
*************************************************************************/
void delProd(Prod *s, char ID[]){
    Prod c = *s;
    Prod temp2 = c;
    while(c != NULL){
        if(strcmp(ID,c->ID) == 0){
            if(c == *s){
                temp2 = temp2->next;
                free(c->ID);
                free(c->name);
                free(c);
                *s = temp2;
                return;
            }

            temp2->next = c->next;
            free(c->ID);
            free(c->name);
            free(c);

            return;
        }
        temp2 = c;
        c = c->next;
    }
}
/**|||||||||||||||||||||||||| END FUNCTIONS |||||||||||||||||||||||||||**/

