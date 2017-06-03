/**
* Reid Stuberg and Kevin Couture
* TCES 202
* Winter 2015   Project
* This global.h contains the header file for the structures
* that are used in the project.
*
*
**/
#ifndef Global_LIST_H_INCLUDED
#define Global_LIST_H_INCLUDED

struct Product{
char*  ID;
char* name;
int num_unit;
float price;
struct Product* next;
};

struct Transaction{
char* f_name;
char* l_name;
char* address;
float pay;
int dd, mm, yy;
struct Product* p;
struct Transaction* next;
};

typedef struct Product* Prod;
typedef struct Transaction* Trans;

#endif
