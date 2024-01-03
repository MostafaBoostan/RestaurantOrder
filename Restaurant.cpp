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
    int id_order = 0;
    int number_type_food = 0;
    int number_food = 0;
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
void foods_new_order(struct foods**, int);
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
    int i = 1;
    FILE *order_file, *food_file;
    struct order *pohead = NULL, *potemp, *ponext;
    struct foods *pfhead = NULL, *pftemp, *pfnext;
    order_file = fopen("order.bin", "rb");
    if(order_file == NULL){
        return NULL;
    }

    ponext = new struct order;
    while(fread(ponext, sizeof(struct order), 1, order_file) > 0){
        ponext->pfhead = NULL;
        if(pohead == NULL){
            potemp = pohead = ponext;
        }
        potemp = ponext;
        ponext = new struct order; 
        potemp->ponext = ponext;
    }
    potemp->ponext = NULL;
    free(ponext);
    fclose(order_file);

    food_file = fopen("food.bin", "rb");
    pfnext = new struct foods;
    potemp = pohead;
    while(1){
        
        if(fread(pfnext, sizeof(struct foods), 1, order_file) <= 0){
            pftemp->pfnext = NULL;
            free(pfnext);
            break;
        }

        if(pfnext->id_order != i){
            pftemp->pfnext = NULL;
            i++;
            //order yedoone mire jelo
            potemp = potemp->ponext;
        }

        if(potemp->pfhead == NULL){
            potemp->pfhead = pfnext;
            pftemp = pfhead = pfnext;
        }
        
        pftemp = pfnext;
        pfnext = new struct foods;
        pftemp->pfnext = pfnext;
    }





    return pohead;

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
    FILE *order_file;
    order_file = fopen("order.bin", "wb");
    struct order *potemp, *ponew;
    int choise = 3;
    static int i =1;

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

        switch(choise){
            case 1:
                //sakht order jadid
                potemp = pohead;
                if(potemp == NULL){
                    ponew->number_order = 1;
                    pohead = ponew;
                }
                else{
                    while(potemp->ponext != NULL){
                        potemp = potemp->ponext;
                    }
                    potemp->ponext = ponew;
                    i++;
                    ponew->number_order = i;
                }

                foods_new_order(&ponew->pfhead, i);

                if(ponew->pfhead == NULL){
                    free(ponew);
                    system("cls || clear");
                    printf("\n"RED"Your order was not registered. To register, you must order at least 1 dish."RESET);
                    usleep(3000000);
                }
                else{
                    //neveshtan order ha dar file.
                    potemp = pohead;
                    while(potemp != NULL){
                        fwrite(potemp, sizeof(struct order), 1, order_file);
                        potemp = potemp->ponext;
                    }
                    fclose(order_file);
                    system("cls || clear");
                    printf("\n"GREEN"Your order has been successfully placed."RESET);
                    usleep(3000000);
                }
                return pohead;
                break;
            case 2:
                system("cls || clear");
                printf("\n"RED"Your order was not registered. To register, you must order at least 1 dish."RESET);
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
void foods_new_order(struct foods** pfhead, int i){
    int temp_type_food = 0;
    FILE *food_file;
    food_file = fopen("food.bin", "ab");
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
            pfnew->id_order = i;
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
            //write kardan ghazaha dar file
            fwrite(pfnew, sizeof(struct foods), 1, food_file);
            fclose(food_file);
            system("cls || clear");
            printf("\n"GREEN"Your order has been successfully placed."RESET);
            usleep(3000000);
            foods_new_order(pfhead, i);
            break;
        default:
            system("cls || clear");
            printf("\n"RED"The entered number is not valid. Please enter one of the options correctly."RESET);
            usleep(3000000);
            foods_new_order(pfhead, i);
    }
}    
