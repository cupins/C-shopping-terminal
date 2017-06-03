/**
* Reid Stuberg and Kevin Couture
* TCES 202
* Winter 2015   Project
*
* This file contains the majority of the product functions for the owner.
* Print product function is lent to the customer because it has the same
* desired behavior.
*
**/


/// INCLUDES
#include <stdio.h>
#include <stdlib.h>
#include "global.h"

/// PROTOTYPES
void deleteAllProduct(Prod *pl);
void printProducts(Prod *pl);
void creatProduct2(Prod *pl);
void editProduct(Prod *p);


/**|||||||||||||||||||||||||||||| FUNCTIONS||||||||||||||||||||||||||||**/

/*************************************************************************
* Arguments/Parameters: A pointer head node for product list.
*
* This function creates a product in the product list. It asks the user for
* input and the user cannot add an ID that has already been entered (no exit).
*************************************************************************/
void creatProduct2(Prod *pl)
{
    struct Product* p;
    Prod cur = *pl;
    p = malloc(sizeof(struct Product));
    char c[50];
    int checkID = 0;

    while (checkID == 0) {
        printf("Please enter the ID of the product. > ");
        gets(c);
        fflush(stdin);

        Prod cur = *pl;
        checkID = 1; // used to check if ID exists so turn to true
        while(cur != NULL){
            if(strcmp(c,cur->ID) == 0)
            {
                checkID = 0;
            }
            cur = cur->next;
        }
        if (checkID == 0){
            printf("\nID already exists please enter in a different ID\n");
        }
    }
    p->ID = malloc(strlen(c)+1);
    strcpy(p->ID,c);

    printf("Please enter the name of the product. > ");
    fflush(stdin);
    gets(c);
    p->name = malloc(strlen(c)+1);
    strcpy(p->name,c);

    printf("Please enter the Product quantity. > ");
    int y;
    scanf("%d",&y);
    p->num_unit = y;
    getchar();
    float x;

    printf("Please enter the cost of the Product. > ");
    scanf("%f",&x);
    p->price = x;
    getchar();
    p->next = NULL;

    if(*pl == NULL)
    {
        *pl = p;
        return;
    }

    while(cur->next != NULL)
    {
        cur = cur->next;
    }
    cur->next = p;
}

/*************************************************************************
* Arguments/Parameters: A pointer head node for product list.
*
* This function prints all the products within the product list.
* Used multiple times in customerCart.c.
*************************************************************************/
void printProducts(Prod *pl)
{
    if(*pl != NULL){
        Prod px = *pl;

        while(px != NULL){
            printf("________________________________________\n");
            printf("Product ID > %s\n",px->ID);
            printf("Product name > %s\n",px->name);
            printf("Product quantity > %d\n",px->num_unit);
            printf("Product Cost per item > %.2f\n",px->price);

            px = px->next;
        }
    } else{
        printf("\nNo products to display.\n");
    }

}

/*************************************************************************
* Arguments/Parameters: A pointer head node for product list.
*
* This function deletes a product by asking the user for the ID to delete
* the product from a product list.
*************************************************************************/
void deleteProductID(Prod *pl)
{
    char* ID[50];
    printf("Please enter the ID for the product to delete. > \n");
    scanf("%s",ID);
    fflush(stdin);
    Prod cur = *pl;
    Prod temp = cur;

    while(cur != NULL) // traverse list and deletes and returns
    {
        if(strcmp(ID,cur->ID) == 0)
        {
            if(cur == *pl)
            {
                temp = temp->next;
                free(cur->ID);
                free(cur->name);
                free(cur);
                cur = NULL;
                *pl=temp;
                return;
            }
            temp->next = cur->next;
            free(cur->ID);
            free(cur->name);
            free(cur);
            cur=NULL;
            return;
        }
        temp = cur;
        cur = cur->next;
    }

}

/*************************************************************************
* Arguments/Parameters: A pointer head node for product list.
*
* This function edits either the stock or the price of a product. The
* product is chosen by the user by entering in the ID of the product.
*************************************************************************/
void editProduct(Prod *p){
    char* ID[50];
    char ch;
    Prod cur = *p;

    int chID = 0;
    while (chID == 0){

        printf("Please enter the ID for the product to edit. > \n");
        scanf("%s",ID);
        fflush(stdin);
        cur = *p;
        while(cur != NULL)
        {
            if(strcmp(ID,cur->ID) == 0){
                chID = 1;
            }
            cur = cur->next;
        }
        if (chID == 0){
            printf("Invalid ID entered press 0 to exit or any other key to enter an ID again \n");
            scanf("%c", &ch);
            fflush(stdin);
            if (ch == '0'){
                return;
            }
        }
    }

    ch = '?'; // init in case something bad happens
    printf("\n+------------------------------------------------------+");
    printf("\n| Press 1 to edit the amount of stock");
    printf("\n| Press any other key to edit the price of the product");
    printf("\n+------------------------------------------------------+");
    printf("\nInput: ");
    scanf("%c", &ch);
    fflush(stdin);
    cur = *p;
    if (ch == '1') {
        int quantity;
        printf("\nPlease enter the new amount of items of product in the store: ");
        scanf("%d", &quantity);
        fflush(stdin);

        while(cur != NULL)
        {
            if(strcmp(ID,cur->ID) == 0)
            {
                cur->num_unit = quantity;
            }
            cur = cur->next;
        }

    } else {
        float price;
        printf("\nPlease enter the new price of product in the store: ");
        scanf("%f", &price);
        fflush(stdin);

        while(cur != NULL)
        {
            if(strcmp(ID,cur->ID) == 0)
            {
                cur->price = price;
            }
            cur = cur->next;
        }
    }
}

/**|||||||||||||||||||||||||| END FUNCTIONS |||||||||||||||||||||||||||**/

