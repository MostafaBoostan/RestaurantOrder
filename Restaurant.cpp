#include <iostream>
#include <math.h>
#include <cstring>
#include <unistd.h>


using namespace std;

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define RESET   "\x1b[0m"


struct foods{
    int number_type_food;
    int number_food;
    struct foods *pfnext = NULL;
};

struct order{
    int number_order = 0;
    int number_std = 0;
    char name[200];
    char family[200];
    int situation = 0;
    struct foods *pfhead = NULL;
    struct order *ponext = NULL;
};

struct order* loading();
void first_menu();
void food_menu();
struct order* new_order(struct order*);
void foods_new_order(struct foods**);
void order_deliver(struct order*);
void cancle(struct order*);
void change_order(struct order*);
void review(struct order*);

int main(){
    struct order *pohead;
    int choise;
    pohead = loading();
    first_menu();
}

//load kardan tamam data ha az file dar linklist.
struct order* loading(){
    FILE *file_order;
    struct order* pohead = NULL;
    struct order* potemp = NULL;
    struct order* ponew = NULL;
    file_order = fopen("order_data.bin", "rb");
    //agar file nabashad mipare biroon va adres null barmigardad.
    if(file_order == NULL){
        return pohead;
    }
    else{
        //avalin khone vared mishavad.
        pohead = new struct order;
        fread(pohead, sizeof(struct order), 1, file_order);
        potemp = pohead;
        //bad az avalin khone betartib data ha vared mishavad va load mishavad dar ram.
        while(1){
            ponew = new struct order;
            if(fread(ponew, sizeof(struct order), 1, file_order) > 0){
                potemp->ponext = ponew;
                potemp = ponew;
            }
            else{
                free(ponew);
                return pohead;
            }
        }
    }
}

//sakht va namayehs avalin safhe namayesh.
void first_menu(){
    static struct order *pohead = loading();
    
    int choise;
    system("cls || clear");
    printf(YELLOW"* * * * * * * * * * * * * * * *"RESET"\n");
    printf(YELLOW"*"RESET"     "MAGENTA"Welcome to resturant"RESET"    "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"                             "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"                 "GREEN"Menu (1"RESET"     "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"            "GREEN"New order (2"RESET"     "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"      "GREEN"Order delivered (3"RESET"     "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"         "GREEN"Cancle order (4"RESET"     "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"         "GREEN"Change order (5"RESET"     "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"               "GREEN"Review (6"RESET"     "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"                             "YELLOW"*"RESET"\n");
    printf(YELLOW"* * * * * * * * * * * * * * * *"RESET"\n");
    printf(BLUE"Please enter your choise: "RESET);
    scanf("%d",& choise);
    switch(choise){
        case 1:
            food_menu();        
            break;
        case 2 :
            pohead = new_order(pohead);
            first_menu();
            break;
        default:
            system("cls || clear");
            printf("\n"RED"The entered number is not valid. Please enter one of the options correctly."RESET);
            usleep(3000000);
            first_menu();
    }
}

//neshoon dadan ghaza ha dar safhe aval faghat baraye moshahede
void food_menu(){
    int choise;
    system("cls || clear");
    printf(YELLOW"* * * * * * * * * * * * * * * *"RESET"\n");
    printf(YELLOW"*"RESET"          "MAGENTA"Food menu"RESET"          "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"                             "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"          "GREEN"lasagna (1"RESET"         "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"         "GREEN"Sandwich (2"RESET"         "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"           "GREEN"Burger (3"RESET"         "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"          "GREEN"Hot dog (4"RESET"         "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"            "GREEN"Pizza (5"RESET"         "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"                             "YELLOW"*"RESET"\n");
    printf(YELLOW"* * * * * * * * * * * * * * * *"RESET"\n");
    printf(BLUE"Would you like to return to the home page?(yes: 1),(no: 0): "RESET);
    scanf("%d",& choise);
    switch(choise){
        case 1:
            first_menu();
            break;
        case 0:
            exit(0);
            break;
        default:
            system("cls || clear");
            printf("\n"RED"The entered number is not valid. Please enter one of the options correctly."RESET);
            usleep(3000000);
            food_menu();
    }

}

//ezafe kardan sefaresh jadid
struct order* new_order(struct order* pohead){
    struct order *potemp, *ponew;
    int choise = 3, i = 1;

    ponew = new struct order;
    //kamel kardan shomare daneshjoyi
    system("cls || clear");
    printf(YELLOW"* * * * * * * * * * * * * * * *"RESET"\n");
    printf(YELLOW"*"RESET"        "MAGENTA"Add new order"RESET"        "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"                             "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"        "RED"Number of std(<"RESET"      "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"                 "GREEN"Name(<"RESET"      "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"               "GREEN"Family(<"RESET"      "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"          "GREEN"Go to menu (1"RESET"      "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"     "GREEN"Go to home page (2"RESET"      "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"                             "YELLOW"*"RESET"\n");
    printf(YELLOW"* * * * * * * * * * * * * * * *"RESET"\n");
    printf(BLUE"Please enter you student number: "RESET);
    scanf("%d",& ponew->number_std);
    //kamel kardan name
    system("cls || clear");
    printf(YELLOW"* * * * * * * * * * * * * * * *"RESET"\n");
    printf(YELLOW"*"RESET"        "MAGENTA"Add new order"RESET"        "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"                             "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"        "GREEN"Number of std(<"RESET"      "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"                 "RED"Name(<"RESET"      "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"               "GREEN"Family(<"RESET"      "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"          "GREEN"Go to menu (1"RESET"      "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"     "GREEN"Go to home page (2"RESET"      "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"                             "YELLOW"*"RESET"\n");
    printf(YELLOW"* * * * * * * * * * * * * * * *"RESET"\n");
    printf(BLUE"Your student nuber is: %d\n"RESET, ponew->number_std);
    printf(BLUE"Please enter you name: "RESET);
    getchar();
    scanf("%[^\n]", ponew->name);
    //kamel kardan family
    system("cls || clear");
    printf(YELLOW"* * * * * * * * * * * * * * * *"RESET"\n");
    printf(YELLOW"*"RESET"        "MAGENTA"Add new order"RESET"        "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"                             "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"        "GREEN"Number of std(<"RESET"      "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"                 "GREEN"Name(<"RESET"      "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"               "RED"Family(<"RESET"      "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"          "GREEN"Go to menu (1"RESET"      "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"     "GREEN"Go to home page (2"RESET"      "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"                             "YELLOW"*"RESET"\n");
    printf(YELLOW"* * * * * * * * * * * * * * * *"RESET"\n");
    printf(BLUE"Your student nuber is: %d\n"RESET, ponew->number_std);
    printf(BLUE"Your name is: %s\n"RESET, ponew->name);
    printf(BLUE"Please enter you family: "RESET);
    getchar();
    scanf("%[^\n]", ponew->family);
    //neveshtan tamam etelat order va entekhab gozine
    while(choise != 1 || choise != 2){
        system("cls || clear");
        printf(YELLOW"* * * * * * * * * * * * * * * *"RESET"\n");
        printf(YELLOW"*"RESET"        "MAGENTA"Add new order"RESET"        "YELLOW"*"RESET"\n");
        printf(YELLOW"*"RESET"                             "YELLOW"*"RESET"\n");
        printf(YELLOW"*"RESET"        "GREEN"Number of std(<"RESET"      "YELLOW"*"RESET"\n");
        printf(YELLOW"*"RESET"                 "GREEN"Name(<"RESET"      "YELLOW"*"RESET"\n");
        printf(YELLOW"*"RESET"               "GREEN"Family(<"RESET"      "YELLOW"*"RESET"\n");
        printf(YELLOW"*"RESET"          "RED"Go to menu (1"RESET"      "YELLOW"*"RESET"\n");
        printf(YELLOW"*"RESET"     "RED"Go to home page (2"RESET"      "YELLOW"*"RESET"\n");
        printf(YELLOW"*"RESET"                             "YELLOW"*"RESET"\n");
        printf(YELLOW"* * * * * * * * * * * * * * * *"RESET"\n");
        printf(BLUE"Your student nuber is: %d\n"RESET, ponew->number_std);
        printf(BLUE"Your name is: %s\n"RESET, ponew->name);
        printf(BLUE"Your family is: %s\n"RESET, ponew->family);
        printf(BLUE"Please enter your choise: "RESET);
        scanf("%d",& choise);
        //sakht order jadid
        potemp = pohead;
        if(potemp == NULL){
            ponew->number_order = 1;
            pohead = ponew;
        }
        else{
            while(potemp->ponext != NULL){
            potemp->number_order = i;
            potemp = potemp->ponext;
            i++;
            }
            ponew->number_order = i;
            potemp->ponext = ponew;
        }
        
        switch(choise){
            case 1:
                foods_new_order(& pohead->pfhead);
                system("cls || clear");
                printf("\n"GREEN"Your order has been successfully placed."RESET);
                usleep(3000000);
                return pohead;
                break;
            case 2:
                system("cls || clear");
                printf("\n"GREEN"Your order has been successfully placed. but you dant have any food."RESET);
                usleep(3000000);
                return pohead;
                break;
            default:
                system("cls || clear");
                printf("\n"RED"The entered number is not valid. Please enter one of the options correctly."RESET);
                usleep(3000000);
        }
    }    
}

//neshoon daden menu va entekhab ghaza ha baraye avalin bar
void foods_new_order(struct foods** pfhead){
    int temp_type_food = 0;
    struct foods *pftemp;
    system("cls || clear");
    printf(YELLOW"* * * * * * * * * * * * * * * *"RESET"\n");
    printf(YELLOW"*"RESET"          "MAGENTA"Food menu"RESET"          "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"                             "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"          "GREEN"lasagna (1"RESET"         "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"         "GREEN"Sandwich (2"RESET"         "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"           "GREEN"Burger (3"RESET"         "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"          "GREEN"Hot dog (4"RESET"         "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"            "GREEN"Pizza (5"RESET"         "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"              "MAGENTA"end (6"RESET"         "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"                             "YELLOW"*"RESET"\n");
    printf(YELLOW"* * * * * * * * * * * * * * * *"RESET"\n");
    printf(BLUE"Please choose the food you want: "RESET);
    scanf("%d",&temp_type_food);
    switch(temp_type_food){
        case 6:
            break;
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            struct foods *pfnew;
            pfnew = new struct foods;
            pfnew->number_type_food = temp_type_food;
            system("cls || clear");
            printf(YELLOW"* * * * * * * * * * * * * * * *"RESET"\n");
            printf(YELLOW"*"RESET"          "MAGENTA"Food menu"RESET"          "YELLOW"*"RESET"\n");
            printf(YELLOW"*"RESET"                             "YELLOW"*"RESET"\n");
            printf(YELLOW"*"RESET"          "GREEN"lasagna (1"RESET"         "YELLOW"*"RESET"\n");
            printf(YELLOW"*"RESET"         "GREEN"Sandwich (2"RESET"         "YELLOW"*"RESET"\n");
            printf(YELLOW"*"RESET"           "GREEN"Burger (3"RESET"         "YELLOW"*"RESET"\n");
            printf(YELLOW"*"RESET"          "GREEN"Hot dog (4"RESET"         "YELLOW"*"RESET"\n");
            printf(YELLOW"*"RESET"            "GREEN"Pizza (5"RESET"         "YELLOW"*"RESET"\n");
            printf(YELLOW"*"RESET"                             "YELLOW"*"RESET"\n");
            printf(YELLOW"* * * * * * * * * * * * * * * *"RESET"\n");
            printf(BLUE"Food number %d is selected\n"RESET, pfnew->number_type_food);
            printf(BLUE"Please enter the number of meals you want of this type: "RESET);
            scanf("%d",& pfnew->number_food);
            pftemp = *pfhead;
            if(pftemp == NULL){
                *pfhead = pfnew;
            }
            else{
                while(pftemp->pfnext != NULL){
                pftemp = pftemp->pfnext;
                }
                pftemp->pfnext = pfnew;
            }
            system("cls || clear");
            printf("\n"GREEN"Your order has been successfully placed."RESET);
            usleep(3000000);
            foods_new_order(pfhead);
            break;
        default:
            system("cls || clear");
            printf("\n"RED"The entered number is not valid. Please enter one of the options correctly."RESET);
            usleep(3000000);
            foods_new_order(pfhead);
    }
}    
