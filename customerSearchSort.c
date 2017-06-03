/**
* Reid Stuberg and Kevin Couture
* TCES 202
* Winter 2015   Project
*
* This contains the search and sort functions implemented in the customer
* menu and the display menu.
*
**/

/// INCLUDES
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"global.h"

///PROTOTYPES
void bubbleSortStock(Prod *);
void bubbleSortPrice(Prod *);
void searchProdName(Prod *);

/**|||||||||||||||||||||||||||||| FUNCTIONS||||||||||||||||||||||||||||**/

/*************************************************************************
* Arguments/Parameters: A pointer head node for product list.
*
* This function searches for a product based on a customers input for a
* unique ID. It displays the product if found or a message if not found.
*************************************************************************/
void searchProdName(Prod *p){
    printf("\nPlease enter in the product name to search for: ");
    char buff[50];
    scanf("%s", buff);
    fflush(stdin);
    // parsing done
    Prod temp = *p;
    int x = 0;
    while(temp != NULL){ // traverse the list and compare to the other products

        if (strcmp(temp->name, buff) == 0){
            printf("\n\nProduct found.");
            printf("\nID: %s", temp->ID);
            printf("\nName: %s", temp->name);
            printf("\nStock: %d", temp->num_unit);
            printf("\nPrice: %f", temp->price);
            x++;
        }
        temp = temp->next; // continue
    }
    if (x == 0)
        printf("\n\nNo products not found. \n");


}

/*************************************************************************
* Arguments/Parameters: A pointer head node for product list.
*
* This function sorts a product list by doing a bubble sort. The list is
* sorted by the stock in ascending order and is returned by parameter.
*************************************************************************/
void bubbleSortStock(Prod *p)
{

    int done = 0;
    while(!done) ////////// If a swap happens this will be 0;
    {
        Prod current = *p;
        Prod next = current->next;
        Prod previous = NULL;
        done = 1; /////////////// Resets the flag.

        while(next != NULL)
        {
            int compare = (current->num_unit-next->num_unit); //////// Compares the stock
            if (compare > 0)                             //////// If it is a larger string value, swap.
            {
                done = 0;                                //////// Set Flag.
                if (current == *p)                     //////// No previous if its the first element.
                {
                    *p = next;
                } else                                   //////// Links the list so previous will point to the new next after swap.
                {
                    previous->next = next;
                }

                current->next = next->next;              //////// Links the list for swap.
                next->next = current;                    //////// Swaps the nodes.

                previous = next;                         //////// Advances Node.
                next = current->next;                    //////// Advances Node.
            }
            else {                                       //////// Advances Node. No swap happened.
                previous = current;
                current = current->next;
                next = current->next;
            }
        }
    }
}


/*************************************************************************
* Arguments/Parameters: A pointer head node for product list.
*
* This function sorts a product list by doing a bubble sort. The list is
* sorted by the price in ascending order and is returned by parameter.
*************************************************************************/
void bubbleSortPrice(Prod *p)
{
    int done = 0;
    while(!done) ////////// If a swap happens this will be 0;
    {
        Prod current = *p;
        Prod next = current->next;
        Prod previous = NULL;
        done = 1; /////////////// Resets the flag.

        while(next != NULL)
        {
            if (current->price > next->price)             //////// If it is a larger value, swap.
            {
                done = 0;                                //////// Set Flag.
                if (current == *p)                     //////// No previous if its the first element.
                {
                    *p = next;
                } else                                   //////// Links the list so previous will point to the new next after swap.
                {
                    previous->next = next;
                }

                current->next = next->next;              //////// Links the list for swap.
                next->next = current;                    //////// Swaps the nodes.

                previous = next;                         //////// Advances Node.
                next = current->next;                    //////// Advances Node.
            }
            else {                                       //////// Advances Node. No swap happened.
                previous = current;
                current = current->next;
                next = current->next;
            }
        }
    }
}

/**|||||||||||||||||||||||||| END FUNCTIONS |||||||||||||||||||||||||||**/
