/**
* Reid Stuberg and Kevin Couture
* TCES 202
* Winter 2015   Project
*
* This file contains the majority of the file input/output functions
* it has 4 functions in it that read/write a .txt file and 1 helper
* function that helps read from the file.
*
**/

/// HEADERS
#include <stdio.h>
#include <stdlib.h>
#include "global.h"

/// PROTOTYPES
void getTransactions(Trans *);
void getFileProduct(struct Product ** , char *, char *, int , float );
void getProducts(Prod *);
void setTransactions(Trans *);
void setProducts(Prod *);

/// CONSTANTS
#define NAME_LEN 50

/**|||||||||||||||||||||||||||||| FUNCTIONS||||||||||||||||||||||||||||**/

/*************************************************************************
* Arguments/Parameters: NULL or empty list can be passed as pointer or list pointer
*
* Creates a transaction list from reading a file transaction.txt.
*************************************************************************/
void getTransactions(Trans *t){
    char f_n[NAME_LEN]; //buffers
    char l_n[NAME_LEN];
    char addr[100];
    float pay;
    int dd, mm, yy;

    FILE *fp;
    fp = fopen("transactions.txt", "r");
    while (!feof(fp)){
        // Create the new transaction from the file
        Trans newTransaction = malloc(sizeof(struct Transaction));
        fscanf(fp, "%s %s %s %f %d %d %d ", f_n, l_n, addr, &pay, &dd, &mm, &yy);

        newTransaction->f_name = malloc(50); // allocate the memory
        strcpy(newTransaction->f_name,f_n);
        newTransaction->l_name = malloc(50);
        strcpy(newTransaction->l_name,l_n);
        newTransaction->address = malloc(100);
        strcpy(newTransaction->address, addr);

        newTransaction->pay = pay;
        newTransaction->dd = dd;
        newTransaction->mm = mm;
        newTransaction->yy = yy;
        newTransaction->next = NULL;

        // See if there is a next transaction must have at least one product
        char ID[NAME_LEN];
        char nam[NAME_LEN];
        char buff[NAME_LEN];
        int num;
        float price;
        int productCheck = 0;

        newTransaction->p = NULL;
        Prod temp = newTransaction->p;

        while (productCheck == 0){ // unload product list for each transaction

            Prod newProd = malloc(sizeof(struct Product));
            fscanf(fp, "%s %s %d %f ",ID, nam, &num, &price);

            newProd->ID = malloc(NAME_LEN);
            strcpy(newProd->ID, ID);

            newProd->name = malloc(NAME_LEN);
            strcpy(newProd->name, nam);

            newProd->num_unit = num;
            newProd->price = price;
            newProd->next = NULL;

            if (newTransaction->p == NULL){
                newTransaction->p = newProd;
            } else {
                struct Product * curr= newTransaction->p;
                while(curr->next!=NULL){
                    curr=curr->next;
                }
                curr->next = newProd;
            }
            if (feof(fp)){ // just created the last product?
                if(*t == NULL){ // only one transaction
                        *t = newTransaction;
                } else { // multiple transaction
                    struct Transaction * curr = *t;
                    while(curr->next != NULL){
                        curr = curr->next;
                    }
                    curr->next = newTransaction;
                }
            return;
            }
            fscanf(fp, "%s",buff);
            if (isdigit(buff[0])){ // next thing is not a product
                int offsetFP = strlen(buff);
                fseek(fp, (-1)*offsetFP, SEEK_CUR);//put the file pointer back to the product id

            } else {
                int offsetFP = strlen(buff);
                fseek(fp, (-1)*offsetFP, SEEK_CUR);//put the file pointer back to the product id
                productCheck = 1;
            }
        }
        if(*t == NULL){
            *t = newTransaction;
        } else {
            struct Transaction * curr = *t;
            while(curr->next != NULL){
                curr = curr->next;
            }
            curr->next = newTransaction;
        }
    }

}

/*************************************************************************
* Arguments/Parameters: A pointer head node for product list, string ID
* string of name, an int and float for structure product.
*
* Helper function for getProducts()
*
* This function adds a product to a list from FILE format only.
*************************************************************************/
void getFileProduct(struct Product ** p, char *ID, char *name, int num, float cost){
    struct Product* ptr1;
    ptr1 = malloc(sizeof(struct Product));

    ptr1->ID = malloc(50);
    strcpy(ptr1->ID,ID);

    ptr1->name = malloc(50);
    strcpy(ptr1->name,name);

    ptr1->num_unit = num;
    ptr1->price = cost;
    ptr1->next = NULL;

    if(*p==NULL)
    {
        *p=ptr1;
    }
    else
    {

        Prod curr=*p;
        while(curr->next!=NULL)
        {
            curr=curr->next;
        }
        curr->next=ptr1;
    }

}

/*************************************************************************
* Arguments/Parameters: A pointer head node for product list init. to null.
*
* This function reads a file then calls getFileProduct to create a product
* list from a product.txt.
*************************************************************************/
void getProducts(Prod * pl)
{
    FILE * fp;
    char ID[50];
    char c[50];
    char name[50];
    int num;
    float cost;
    Prod curr = *pl;
    fp = fopen("product.txt","r");
    fscanf(fp,"%s %s %s %s",c,c,c,c);

    while(!feof(fp)){
        fscanf(fp,"%s",ID);
        fscanf(fp,"%s",name);
        fscanf(fp,"%d",&num);
        fscanf(fp,"%f\n",&cost);

        getFileProduct(&curr, ID, name, num, cost);
    }
    *pl = curr;
    fclose(fp);
}

/*************************************************************************
* Arguments/Parameters: Transaction list can be passed as pointer or list
* should be initialized to null
*
* Should write a file transaction.txt which contains transaction list t
* in  a specific format.
*************************************************************************/
void setTransactions(Trans *t){
    Trans tx = *t;
    FILE * fp;
    fp = fopen("transactions.txt","w");
    // format of file
    if(*t == NULL) // this shouldn't happen or nothing in file
        return;

    while (tx != NULL){
        fprintf(fp,"%s %s %s %f %d %d %d\n",tx->f_name, tx->l_name, tx->address, tx->pay, tx->dd, tx->mm, tx->yy);
        Prod p = tx->p;
        while (p != NULL){
            fprintf(fp,"%s %s %d %f\n",p->ID,p->name,p->num_unit,p->price);
            p = p->next;
        }
        fprintf(fp,"\n");
        tx =tx->next;
    }
}

/*************************************************************************
* Arguments/Parameters: Product list can be passed as pointer or list pointer
* which is initialized to null
*
* Should write a file products.txt which contains a product list.
*************************************************************************/
void setProducts(Prod *p){
    Prod px = *p;
    FILE * fp;
    fp = fopen("product.txt","w");
    // format of file
    fprintf(fp, "Product_ID	Product_name 			Number_of_units 	Price_of_unit\n");
    if(*p == NULL) // this shouldn't happen or nothing in file
        return;

    while (px != NULL){
        fprintf(fp,"%s 		%s 			%d 			%f\n",px->ID,px->name,px->num_unit,px->price);
        px =px->next;
    }
}

/**|||||||||||||||||||||||||| END FUNCTIONS |||||||||||||||||||||||||||**/
