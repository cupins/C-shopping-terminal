/**
* Reid Stuberg and Kevin Couture
* TCES 202
* Winter 2015   Project
*
* This file contains the majority of the transaction functions
* it has the 2 owner functions in it which are implemented in the
* Owner menu.
*
**/

/// HEADERS
#include <stdio.h>
#include <stdlib.h>
#include "global.h"

/// CONSTANTS
#define NAME_LEN 50

/// PROTOTYPES
void viewAllTransactions(Trans *transList);
void deleteAllTransactions(Trans *transList);

/**|||||||||||||||||||||||||||||| FUNCTIONS||||||||||||||||||||||||||||**/

/*************************************************************************
* Arguments/Parameters: A pointer head node for transaction list.
*
* This function prints all of the transactions known in the list provided.
*************************************************************************/
void viewAllTransactions(Trans *transList){
    Trans t1 = *transList;
    if (t1 == NULL){
        printf("\n No transaction exists.");
        return; // no transactions to be shown
    } else {
        while (t1 != NULL){
          printf("\nFirst name   Last name     Address     Pay     Date\n");
            printf("\n%s  ",t1->f_name);
            printf("%s  ",t1->l_name);
            printf("%s  ",t1->address);
            printf("%f  ",t1->pay);
            printf("%d, ",t1->dd);
            printf("%d, ",t1->mm);
            printf("%d   \n",t1->yy);

            printf("\n Product(s): "); // display all products
            printf("\nID   Name  Quantity   Price\n");
            Prod tempP = t1->p;

            while (tempP != NULL){ // make sure they didn't buy anything
                printf("\n%s  ", tempP->ID);
                printf("%s  ", tempP->name);
                printf("%d  ", tempP->num_unit);
                printf("%f  ", tempP->price);
                tempP = tempP->next; // next product?
            }
            t1 = t1->next; // go to next transaction
        }
    }
}

/*************************************************************************
* Arguments/Parameters: A pointer head node for transaction list.
*
* This function prints all of the transactions passed down by the list.
*************************************************************************/
void deleteAllTransactions(Trans *transList){
    Trans curr = *transList;

    while (curr != NULL){ // delete the transaction if there is one
        free(curr->f_name);
        free(curr->l_name);
        free(curr->address);
        Prod curr2 = curr->p;;
        Prod temp2 = curr2;

        while (curr2 != NULL){ // deletes products if they are there
            temp2 = temp2->next;
            free(curr2->ID);
            free(curr2->name);
            free(curr2); /** DELTETED num_unit and price **/
            curr2 = temp2;
        }
        curr2 = NULL;
        temp2 = NULL;
        free(curr); /** DELTETED date and pay **/
        curr = curr->next; // next transaction

    }
    *transList = NULL; // just to make sure the list pointer won't pick up anything
}

/**|||||||||||||||||||||||||| END FUNCTIONS |||||||||||||||||||||||||||**/

