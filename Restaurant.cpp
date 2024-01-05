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
#define Lasagna 1
#define Sandwich 2
#define Burger 3
#define Chicken 4
#define Pizza 5

struct foods{
    int id_order = 0;
    int number_type_food = 0;
    int number_food = 0;
    int id_food = 0;
    char food_name[10];
    struct foods *pfnext = NULL;
};

enum situation{
    DOING,
    DELIVERED,
    CANCLE
};

struct order{
    int number_order = 0;
    int number_std = 0;
    char name[200];
    char family[200];
    int situation = DOING;
    struct foods *pfhead = NULL;
    struct order *ponext = NULL;
};



struct order* loading();
void first_menu();
void food_menu();
struct order* new_order(struct order*);
void foods_new_order(struct foods**, int, int);
void order_deliver(struct order*);
void cancle_order(struct order*);
void change_order(struct order*);
void delete_food(struct order*, struct order*);
void change_food(struct order*, struct order*);
void add_food(struct order*, struct order*);
void write_food(struct order*);
void review(struct order*);

int main(){
    first_menu();
}

//load kardan tamam data ha az file dar linklist.
struct order* loading(){
    //motagheyer i baraye id order va j baraye id food dar har order ast.
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
    printf(YELLOW"*"RESET"                 "GREEN"Exit (7"RESET"     "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"                             "YELLOW"*"RESET"\n");
    printf(YELLOW"* * * * * * * * * * * * * * * *"RESET"\n");
    printf(BLUE"Please enter your choise: "RESET);
    scanf("%d",& choise);
    switch(choise){
        case 1:
            food_menu();        
            break;
        case 2:
            pohead = new_order(pohead);
            first_menu();
            break;
        case 3:
            order_deliver(pohead);
            break;    
        case 4:
            cancle_order(pohead);
            break;
        case 5:
            change_order(pohead);
            break;
        case 6:
            review(pohead);
            break;
        case 7:
            exit(0);
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
    printf(YELLOW"*"RESET"          "GREEN"Lasagna (1"RESET"         "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"         "GREEN"Sandwich (2"RESET"         "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"           "GREEN"Burger (3"RESET"         "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"          "GREEN"Chicken (4"RESET"         "YELLOW"*"RESET"\n");
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
    struct order *potemp, *ponew;
    int choise = 3, j = 1;
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
                        i++;
                        potemp = potemp->ponext;
                    }
                    i++;
                    potemp->ponext = ponew; 
                    ponew->number_order = i;
                }

                foods_new_order(&ponew->pfhead, i, j);

                if(ponew->pfhead == NULL){
                    free(ponew);
                    system("cls || clear");
                    printf("\n"RED"Your order was not registered. To register, you must order at least 1 dish."RESET);
                    usleep(3000000);
                }
                else{
                    //neveshtan order ha dar file.
                    order_file = fopen("order.bin", "wb");
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
void foods_new_order(struct foods** pfhead, int i, int j){
    int temp_type_food = 0;
    FILE *food_file;
    food_file = fopen("food.bin", "ab");
    struct foods *pftemp;
    system("cls || clear");
    printf(YELLOW"* * * * * * * * * * * * * * * *"RESET"\n");
    printf(YELLOW"*"RESET"          "MAGENTA"Food menu"RESET"          "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"                             "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"          "GREEN"Lasagna (1"RESET"         "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"         "GREEN"Sandwich (2"RESET"         "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"           "GREEN"Burger (3"RESET"         "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"          "GREEN"Chicken (4"RESET"         "YELLOW"*"RESET"\n");
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
            printf(YELLOW"*"RESET"          "GREEN"Lasagna (1"RESET"         "YELLOW"*"RESET"\n");
            printf(YELLOW"*"RESET"         "GREEN"Sandwich (2"RESET"         "YELLOW"*"RESET"\n");
            printf(YELLOW"*"RESET"           "GREEN"Burger (3"RESET"         "YELLOW"*"RESET"\n");
            printf(YELLOW"*"RESET"          "GREEN"Chicken (4"RESET"         "YELLOW"*"RESET"\n");
            printf(YELLOW"*"RESET"            "GREEN"Pizza (5"RESET"         "YELLOW"*"RESET"\n");
            printf(YELLOW"*"RESET"                             "YELLOW"*"RESET"\n");
            printf(YELLOW"* * * * * * * * * * * * * * * *"RESET"\n");
            printf(BLUE"Food number %d is selected\n"RESET, pfnew->number_type_food);
            printf(BLUE"Please enter the number of meals you want of this type: "RESET);
            scanf("%d",& pfnew->number_food);
            pfnew->id_order = i;
            pfnew->id_food = j;

            //set kardan esm ghaza ha
            switch(pfnew->number_type_food){
                case Lasagna:
                    strcpy(pfnew->food_name, "Lasanga");
                    break;
                case Sandwich:
                    strcpy(pfnew->food_name, "Sandwich");
                    break;
                case Burger:
                    strcpy(pfnew->food_name, "Burger");
                    break;
                case Chicken:
                    strcpy(pfnew->food_name, "Chicken");
                    break;
                case Pizza:
                    strcpy(pfnew->food_name, "Pizza");
                    break;
            }
            j++;
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
            foods_new_order(pfhead, i, j);
            break;
        default:
            system("cls || clear");
            printf("\n"RED"The entered number is not valid. Please enter one of the options correctly."RESET);
            usleep(3000000);
            foods_new_order(pfhead, i, j);
    }
}    

//taghir vaziat sefareshat be tahvil dade shode
void order_deliver(struct order *pohead){
    FILE *order_file;
    int number_std_search, choise = 3;
    struct order *potemp;
    system("cls || clear");
    printf(YELLOW"* * * * * * * * * * * * * * * *"RESET"\n");
    printf(YELLOW"*"RESET"                             "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"  "MAGENTA"Search the student number"RESET"  "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"                             "YELLOW"*"RESET"\n");
    printf(YELLOW"* * * * * * * * * * * * * * * *"RESET"\n");
    printf(BLUE"Please enter your student number: "RESET);
    scanf("%d",& number_std_search);

    for(potemp = pohead; potemp != NULL && potemp->number_std != number_std_search; potemp = potemp->ponext);
    if(potemp == NULL){
        while(choise != 1 || choise != 2){
            system("cls || clear");
            printf(YELLOW"* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"RESET"\n");
            printf(YELLOW"*"RESET"   "RED"No order has been registered with this student number."RESET"  "YELLOW"*"RESET"\n");
            printf(YELLOW"*"RESET"                                                           "YELLOW"*"RESET"\n");
            printf(YELLOW"*"RESET"                      "GREEN"Add new order (1"RESET"                     "YELLOW"*"RESET"\n");
            printf(YELLOW"*"RESET"                          "GREEN"Back (2"RESET"                          "YELLOW"*"RESET"\n");
            printf(YELLOW"*"RESET"                        "GREEN"Home page (3"RESET"                       "YELLOW"*"RESET"\n");
            printf(YELLOW"*"RESET"                                                           "YELLOW"*"RESET"\n");
            printf(YELLOW"* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"RESET"\n");
            printf(BLUE"Please enter your choise: "RESET);
            scanf("%d",& choise);

            switch(choise){
                case 1:
                    new_order(pohead);
                    break;
                case 2:
                    order_deliver(pohead); 
                    break;
                case 3:
                    first_menu(); 
                    break;  
                default:
                    system("cls || clear");
                    printf("\n"RED"The entered number is not valid. Please enter one of the options correctly."RESET);
                    usleep(3000000);
                    choise = 3;
            }

        }
    }
    else{
        if(potemp->situation == CANCLE){
            while(choise != 1 || choise != 2){
                system("cls || clear");
                printf(YELLOW"* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"RESET"\n");
                printf(YELLOW"*"RESET"           "RED"Your order has already been cancelled."RESET"          "YELLOW"*"RESET"\n");
                printf(YELLOW"*"RESET"                                                           "YELLOW"*"RESET"\n");
                printf(YELLOW"*"RESET"                      "GREEN"Add new order (1"RESET"                     "YELLOW"*"RESET"\n");
                printf(YELLOW"*"RESET"                          "GREEN"Back (2"RESET"                          "YELLOW"*"RESET"\n");
                printf(YELLOW"*"RESET"                        "GREEN"Home page (3"RESET"                       "YELLOW"*"RESET"\n");
                printf(YELLOW"*"RESET"                                                           "YELLOW"*"RESET"\n");
                printf(YELLOW"* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"RESET"\n");
                printf(BLUE"Please enter your choise: "RESET);
                scanf("%d",& choise);

                switch(choise){
                    case 1:
                        new_order(pohead);
                        break;
                    case 2:
                        order_deliver(pohead); 
                        break;
                    case 3:
                        first_menu(); 
                        break;  
                    default:
                        system("cls || clear");
                        printf("\n"RED"The entered number is not valid. Please enter one of the options correctly."RESET);
                        usleep(3000000);
                        choise = 3;
                } 
            }
        }
        else{
            while(choise != 1 || choise != 2){
              system("cls || clear");
                printf(GREEN"The order was successfully delivered"RESET"\n\n");
                printf(YELLOW"*"RESET"  "MAGENTA"studetn number > %d \n"RESET, potemp->number_std);
                printf(YELLOW"*"RESET"        "MAGENTA"order id > %d \n"RESET, potemp->number_order);
                printf(YELLOW"*"RESET"            "MAGENTA"name > %s \n"RESET, potemp->name);
                printf(YELLOW"*"RESET"          "MAGENTA"family > %s \n"RESET, potemp->family);
                printf(YELLOW"*"RESET"       "MAGENTA"situation > Delivered "RESET"\n");
                printf(YELLOW"*"RESET"               "RED"1 > Back "RESET"\n");
                printf(YELLOW"*"RESET"               "RED"2 > Home page "RESET"\n");
                printf("\n");
                printf(BLUE"Please enter your choise: "RESET);
                potemp->situation = DELIVERED;
                //write kardan dar file
                order_file = fopen("order.bin", "wb");
                potemp = pohead;
                while(potemp != NULL){
                    fwrite(potemp, sizeof(struct order), 1, order_file);
                    potemp = potemp->ponext;
                }
                fclose(order_file);
                scanf("%d",& choise);
                switch (choise){
                    case 1:
                        order_deliver(pohead);
                        break;
                    case 2:
                        first_menu();
                        break;
                    default:
                        system("cls || clear");
                        printf("\n"RED"The entered number is not valid. Please enter one of the options correctly."RESET);
                        usleep(3000000);
                        choise = 3;
                }  
            } 
        }
    }
}

//cancle kardan order
void cancle_order(struct order *pohead){
    FILE *order_file;
    int number_std_search, choise = 3;
    struct order *potemp;
    system("cls || clear");
    printf(YELLOW"* * * * * * * * * * * * * * * *"RESET"\n");
    printf(YELLOW"*"RESET"                             "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"  "MAGENTA"Search the student number"RESET"  "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"                             "YELLOW"*"RESET"\n");
    printf(YELLOW"* * * * * * * * * * * * * * * *"RESET"\n");
    printf(BLUE"Please enter your student number: "RESET);
    scanf("%d",& number_std_search);

    for(potemp = pohead; potemp != NULL && potemp->number_std != number_std_search; potemp = potemp->ponext);
    if(potemp == NULL){
        while(choise != 1 || choise != 2){
            system("cls || clear");
            printf(YELLOW"* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"RESET"\n");
            printf(YELLOW"*"RESET"   "RED"No order has been registered with this student number."RESET"  "YELLOW"*"RESET"\n");
            printf(YELLOW"*"RESET"                                                           "YELLOW"*"RESET"\n");
            printf(YELLOW"*"RESET"                      "GREEN"Add new order (1"RESET"                     "YELLOW"*"RESET"\n");
            printf(YELLOW"*"RESET"                          "GREEN"Back (2"RESET"                          "YELLOW"*"RESET"\n");
            printf(YELLOW"*"RESET"                        "GREEN"Home page (3"RESET"                       "YELLOW"*"RESET"\n");
            printf(YELLOW"*"RESET"                                                           "YELLOW"*"RESET"\n");
            printf(YELLOW"* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"RESET"\n");
            printf(BLUE"Please enter your choise: "RESET);
            scanf("%d",& choise);

            switch(choise){
                case 1:
                    new_order(pohead);
                    break;
                case 2:
                    cancle_order(pohead); 
                    break;
                case 3:
                    first_menu(); 
                    break;  
                default:
                    system("cls || clear");
                    printf("\n"RED"The entered number is not valid. Please enter one of the options correctly."RESET);
                    usleep(3000000);
                    choise = 3;
            }

        }
    }
    else{
        if(potemp->situation == DELIVERED){
            while(choise != 1 || choise != 2){
                system("cls || clear");
                printf(YELLOW"* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"RESET"\n");
                printf(YELLOW"*"RESET"           "RED"Your order has already been deliverded."RESET"         "YELLOW"*"RESET"\n");
                printf(YELLOW"*"RESET"                                                           "YELLOW"*"RESET"\n");
                printf(YELLOW"*"RESET"                      "GREEN"Add new order (1"RESET"                     "YELLOW"*"RESET"\n");
                printf(YELLOW"*"RESET"                          "GREEN"Back (2"RESET"                          "YELLOW"*"RESET"\n");
                printf(YELLOW"*"RESET"                        "GREEN"Home page (3"RESET"                       "YELLOW"*"RESET"\n");
                printf(YELLOW"*"RESET"                                                           "YELLOW"*"RESET"\n");
                printf(YELLOW"* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"RESET"\n");
                printf(BLUE"Please enter your choise: "RESET);
                scanf("%d",& choise);

                switch(choise){
                    case 1:
                        new_order(pohead);
                        break;
                    case 2:
                        cancle_order(pohead); 
                        break;
                    case 3:
                        first_menu(); 
                        break;  
                    default:
                        system("cls || clear");
                        printf("\n"RED"The entered number is not valid. Please enter one of the options correctly."RESET);
                        usleep(3000000);
                        choise = 3;
                } 
            }
        }
        else{
            while(choise != 1 || choise != 2){
                system("cls || clear");
                printf(GREEN"The order was successfully cancled"RESET"\n\n");
                printf(YELLOW"*"RESET"  "MAGENTA"studetn number > %d \n"RESET, potemp->number_std);
                printf(YELLOW"*"RESET"        "MAGENTA"order id > %d \n"RESET, potemp->number_order);
                printf(YELLOW"*"RESET"            "MAGENTA"name > %s \n"RESET, potemp->name);
                printf(YELLOW"*"RESET"          "MAGENTA"family > %s \n"RESET, potemp->family);
                printf(YELLOW"*"RESET"       "MAGENTA"situation > cancle "RESET"\n");
                printf(YELLOW"*"RESET"               "RED"1 > Back "RESET"\n");
                printf(YELLOW"*"RESET"               "RED"2 > Home page "RESET"\n");
                printf("\n");
                printf(BLUE"Please enter your choise: "RESET);
                potemp->situation = CANCLE;
                //write kardan dar file
                order_file = fopen("order.bin", "wb");
                potemp = pohead;
                while(potemp != NULL){
                    fwrite(potemp, sizeof(struct order), 1, order_file);
                    potemp = potemp->ponext;
                }
                fclose(order_file);
                scanf("%d",& choise);
                switch (choise){
                    case 1:
                        cancle_order(pohead);
                        break;
                    case 2:
                        first_menu();
                        break;
                    default:
                        system("cls || clear");
                        printf("\n"RED"The entered number is not valid. Please enter one of the options correctly."RESET);
                        usleep(3000000);
                        choise = 3;
                }  
            } 
        }
    }
}

//change kardan sefareshat
void change_order(struct order *pohead){
    FILE *order_file;
    int number_std_search, choise = 3;
    struct order *potemp;
    system("cls || clear");
    printf(YELLOW"* * * * * * * * * * * * * * * *"RESET"\n");
    printf(YELLOW"*"RESET"                             "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"  "MAGENTA"Search the student number"RESET"  "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"                             "YELLOW"*"RESET"\n");
    printf(YELLOW"* * * * * * * * * * * * * * * *"RESET"\n");
    printf(BLUE"Please enter your student number: "RESET);
    scanf("%d",& number_std_search);

    for(potemp = pohead; potemp != NULL && potemp->number_std != number_std_search; potemp = potemp->ponext);
    if(potemp == NULL){
        while(choise != 1 || choise != 2){
            system("cls || clear");
            printf(YELLOW"* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"RESET"\n");
            printf(YELLOW"*"RESET"   "RED"No order has been registered with this student number."RESET"  "YELLOW"*"RESET"\n");
            printf(YELLOW"*"RESET"                                                           "YELLOW"*"RESET"\n");
            printf(YELLOW"*"RESET"                      "GREEN"Add new order (1"RESET"                     "YELLOW"*"RESET"\n");
            printf(YELLOW"*"RESET"                          "GREEN"Back (2"RESET"                          "YELLOW"*"RESET"\n");
            printf(YELLOW"*"RESET"                        "GREEN"Home page (3"RESET"                       "YELLOW"*"RESET"\n");
            printf(YELLOW"*"RESET"                                                           "YELLOW"*"RESET"\n");
            printf(YELLOW"* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"RESET"\n");
            printf(BLUE"Please enter your choise: "RESET);
            scanf("%d",& choise);

            switch(choise){
                case 1:
                    new_order(pohead);
                    break;
                case 2:
                    change_order(pohead); 
                    break;
                case 3:
                    first_menu(); 
                    break;  
                default:
                    system("cls || clear");
                    printf("\n"RED"The entered number is not valid. Please enter one of the options correctly."RESET);
                    usleep(3000000);
                    choise = 3;
            }

        }
    }
    else{
        if(potemp->situation == DELIVERED || potemp->situation == CANCLE){
            while(choise != 1 || choise != 2){
                system("cls || clear");
                printf(YELLOW"* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"RESET"\n");
                printf(YELLOW"*"RESET"     "RED"Your order has already been deliverded or cancled."RESET"    "YELLOW"*"RESET"\n");
                printf(YELLOW"*"RESET"                                                           "YELLOW"*"RESET"\n");
                printf(YELLOW"*"RESET"                      "GREEN"Add new order (1"RESET"                     "YELLOW"*"RESET"\n");
                printf(YELLOW"*"RESET"                          "GREEN"Back (2"RESET"                          "YELLOW"*"RESET"\n");
                printf(YELLOW"*"RESET"                        "GREEN"Home page (3"RESET"                       "YELLOW"*"RESET"\n");
                printf(YELLOW"*"RESET"                                                           "YELLOW"*"RESET"\n");
                printf(YELLOW"* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"RESET"\n");
                printf(BLUE"Please enter your choise: "RESET);
                scanf("%d",& choise);

                switch(choise){
                    case 1:
                        new_order(pohead);
                        break;
                    case 2:
                        change_order(pohead); 
                        break;
                    case 3:
                        first_menu(); 
                        break;  
                    default:
                        system("cls || clear");
                        printf("\n"RED"The entered number is not valid. Please enter one of the options correctly."RESET);
                        usleep(3000000);
                        choise = 3;
                } 
            }
        }
        else{
            choise = 6;
            while(choise != 1 || choise != 2 || choise != 3 || choise != 4 || choise != 5){
                system("cls || clear");
                printf(YELLOW"* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"RESET"\n");
                printf(YELLOW"*"RESET"                  "RED"What do you want to do?"RESET"                  "YELLOW"*"RESET"\n");
                printf(YELLOW"*"RESET"                                                           "YELLOW"*"RESET"\n");
                printf(YELLOW"*"RESET"                      "GREEN"Delete foods (1"RESET"                      "YELLOW"*"RESET"\n");
                printf(YELLOW"*"RESET"                      "GREEN"Change foods (2"RESET"                      "YELLOW"*"RESET"\n");
                printf(YELLOW"*"RESET"                         "GREEN"Add foods (3"RESET"                      "YELLOW"*"RESET"\n");
                printf(YELLOW"*"RESET"                              "GREEN"Back (4"RESET"                      "YELLOW"*"RESET"\n");
                printf(YELLOW"*"RESET"                         "GREEN"Home page (5"RESET"                      "YELLOW"*"RESET"\n");
                printf(YELLOW"*"RESET"                                                           "YELLOW"*"RESET"\n");
                printf(YELLOW"* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"RESET"\n");
                printf(BLUE"Please enter your choise: "RESET);
                scanf("%d",& choise);
                switch(choise){
                    case 1:
                        delete_food(potemp, pohead);
                        break;
                    case 2:
                        change_food(potemp, pohead);
                        break;
                    case 3:
                        add_food(potemp, pohead);
                        break;
                    case 4:
                        change_order(pohead);
                        break;
                    case 5:
                        first_menu();
                        break;
                    default:
                        system("cls || clear");
                        printf("\n"RED"The entered number is not valid. Please enter one of the options correctly."RESET);
                        usleep(3000000);
                        choise = 6;
                }
            }
        }
    }
}

//delete kardan ghazayi az sefareshat
void delete_food(struct order *potemp, struct order *pohead){
    struct foods *pftemp, *pfchoise;
    int food_id_choise, count = 0;
    system("cls || clear");
    printf("   "MAGENTA"studetn number > %d \n"RESET, potemp->number_std);
    printf("         "MAGENTA"order id > %d \n"RESET, potemp->number_order);
    printf("             "MAGENTA"name > %s \n"RESET, potemp->name);
    printf("           "MAGENTA"family > %s \n"RESET, potemp->family);
    printf("        "MAGENTA"situation > Doing "RESET"\n");
    printf("\n");
    printf(YELLOW"***************(foods)***************"RESET"\n");

    //neveshtan tamam ghaza ha be tartib sefaresh vared kardan
    for(pftemp = potemp->pfhead; pftemp != NULL; pftemp = pftemp->pfnext){
        printf(YELLOW"*"RESET"         "RED"food id > %d \n"RESET, pftemp->id_food);
        printf(YELLOW"*"RESET"       "GREEN"food name > %s \n"RESET, pftemp->food_name);
        printf(YELLOW"*"RESET"  "GREEN"number of food > %d \n"RESET, pftemp->number_food);
        printf(YELLOW"*************************************"RESET"\n");
    }
    printf("\n");
    printf(BLUE"Please enter your food id (first page: 0): "RESET);
    scanf("%d",& food_id_choise);
    for(pftemp = potemp->pfhead; pftemp != NULL; pftemp = pftemp->pfnext){
        count ++;
    }
    if(food_id_choise == 0){
        first_menu();
    }
    //shart bishtar az 1 ghaza dar order
    if(count <= 1){
        system("cls || clear");
        printf("\n"RED"The number of your food orders is 1. You cannot delete all your food.You can cancel your entire order."RESET);
        usleep(3000000);
        delete_food(potemp, pohead);
    }
    for(pftemp = potemp->pfhead; pftemp != NULL && pftemp->id_food != food_id_choise; pftemp = pftemp->pfnext);
    if(pftemp == NULL){
        system("cls || clear");
        printf("\n"RED"The entered number is not valid. Please enter one of the options correctly."RESET);
        usleep(3000000);
        delete_food(potemp, pohead);
    }
    else if(pftemp == potemp->pfhead){
        potemp->pfhead = pftemp->pfnext;
        free(pftemp);
        system("cls || clear");
        printf("\n"GREEN"Your food has been successfully removed."RESET);
        usleep(3000000);
    }
    else{
        for(pfchoise = potemp->pfhead; pfchoise->pfnext != pftemp; pfchoise = pfchoise->pfnext);
        pfchoise->pfnext = pftemp->pfnext;
        free(pftemp);
        system("cls || clear");
        printf("\n"GREEN"Your food has been successfully removed."RESET);
        usleep(3000000);
    }
    write_food(pohead);
    delete_food(potemp, pohead);
}

//change kardan foods
void change_food(struct order *potemp, struct order *pohead){
    struct foods *pftemp, *pfchoise;
    int food_id_choise, food_type_choise;
    system("cls || clear");
    printf("   "MAGENTA"studetn number > %d \n"RESET, potemp->number_std);
    printf("         "MAGENTA"order id > %d \n"RESET, potemp->number_order);
    printf("             "MAGENTA"name > %s \n"RESET, potemp->name);
    printf("           "MAGENTA"family > %s \n"RESET, potemp->family);
    printf("        "MAGENTA"situation > Doing "RESET"\n");
    printf("\n");
    printf(YELLOW"***************(foods)***************"RESET"\n");

    //neveshtan tamam ghaza ha be tartib sefaresh vared kardan
    for(pftemp = potemp->pfhead; pftemp != NULL; pftemp = pftemp->pfnext){
        printf(YELLOW"*"RESET"         "RED"food id > %d \n"RESET, pftemp->id_food);
        printf(YELLOW"*"RESET"       "GREEN"food name > %s \n"RESET, pftemp->food_name);
        printf(YELLOW"*"RESET"  "GREEN"number of food > %d \n"RESET, pftemp->number_food);
        printf(YELLOW"*************************************"RESET"\n");
    }
    printf("\n");
    printf(BLUE"Please enter your food id (first page: 0): "RESET);
    scanf("%d",& food_id_choise);
    if(food_id_choise == 0){
        first_menu();
    }    
    for(pftemp = potemp->pfhead; pftemp != NULL && pftemp->id_food != food_id_choise; pftemp = pftemp->pfnext);
    if(pftemp == NULL){
        system("cls || clear");
        printf("\n"RED"The entered number is not valid. Please enter one of the options correctly."RESET);
        usleep(3000000);
        change_food(potemp, pohead);
    }
    else{
        system("cls || clear");
        printf(RESET"         "GREEN"food id > %d \n"RESET, pftemp->id_food);
        printf(RESET"       "RED"food name > %s \n"RESET, pftemp->food_name);
        printf(RESET"  "GREEN"number of food > %d \n\n"RESET, pftemp->number_food);
        printf(YELLOW"* * * * * * * * * * * * * * * *"RESET"\n");
        printf(YELLOW"*"RESET"          "MAGENTA"Food menu"RESET"          "YELLOW"*"RESET"\n");
        printf(YELLOW"*"RESET"                             "YELLOW"*"RESET"\n");
        printf(YELLOW"*"RESET"          "GREEN"Lasagna (1"RESET"         "YELLOW"*"RESET"\n");
        printf(YELLOW"*"RESET"         "GREEN"Sandwich (2"RESET"         "YELLOW"*"RESET"\n");
        printf(YELLOW"*"RESET"           "GREEN"Burger (3"RESET"         "YELLOW"*"RESET"\n");
        printf(YELLOW"*"RESET"          "GREEN"Chicken (4"RESET"         "YELLOW"*"RESET"\n");
        printf(YELLOW"*"RESET"            "GREEN"Pizza (5"RESET"         "YELLOW"*"RESET"\n");
        printf(YELLOW"*"RESET"                             "YELLOW"*"RESET"\n");
        printf(YELLOW"* * * * * * * * * * * * * * * *"RESET"\n");
        printf(BLUE"Please choose the food you want: "RESET);
        scanf("%d",& food_type_choise);
        switch(food_type_choise){
            case Lasagna:
                pftemp->number_type_food = Lasagna;
                strcpy(pftemp->food_name, "Lasanga");
                break;
            case Sandwich:
                pftemp->number_type_food = Sandwich;
                strcpy(pftemp->food_name, "Sandwich");
                break;
            case Burger:
                pftemp->number_type_food = Burger;
                strcpy(pftemp->food_name, "Burger");
                break;
            case Chicken:
                pftemp->number_type_food = Chicken;
                strcpy(pftemp->food_name, "Chicken");
                break;
            case Pizza:
                pftemp->number_type_food = Pizza;
                strcpy(pftemp->food_name, "Pizza");
                break;
            default:
                system("cls || clear");
                printf("\n"RED"The entered number is not valid. Please enter one of the options correctly."RESET);
                usleep(3000000);
                change_food(potemp, pohead);
        }
        write_food(pohead);
        system("cls || clear");
        printf(GREEN"Your food has been successfully changed\n\n"RESET, pftemp->number_food);
        printf(YELLOW"*************************************"RESET"\n");
        printf(YELLOW"*"RESET"         "MAGENTA"food id > %d \n"RESET, pftemp->id_food);
        printf(YELLOW"*"RESET"       "RED"food name > %s \n"RESET, pftemp->food_name);
        printf(YELLOW"*"RESET"  "MAGENTA"number of food > %d \n"RESET, pftemp->number_food);
        usleep(3000000);
        change_food(potemp, pohead);

    }
}

//add kardan ghaza be list baraye har sefaresh
void add_food(struct order *potemp, struct order *pohead){
    struct foods *pftemp, *pfchoise, *pflast, *pfnew;
    int j, food_type_choise;
    system("cls || clear");
    printf("   "MAGENTA"studetn number > %d \n"RESET, potemp->number_std);
    printf("         "MAGENTA"order id > %d \n"RESET, potemp->number_order);
    printf("             "MAGENTA"name > %s \n"RESET, potemp->name);
    printf("           "MAGENTA"family > %s \n"RESET, potemp->family);
    printf("        "MAGENTA"situation > Doing "RESET"\n");
    printf("\n");
    printf(YELLOW"***************(foods)***************"RESET"\n");

    //neveshtan tamam ghaza ha be tartib sefaresh vared kardan
    for(pftemp = potemp->pfhead; pftemp != NULL; pftemp = pftemp->pfnext){
        printf(YELLOW"*"RESET"         "RED"food id > %d \n"RESET, pftemp->id_food);
        printf(YELLOW"*"RESET"       "GREEN"food name > %s \n"RESET, pftemp->food_name);
        printf(YELLOW"*"RESET"  "GREEN"number of food > %d \n"RESET, pftemp->number_food);
        printf(YELLOW"*************************************"RESET"\n");
        if(pftemp->pfnext == NULL){
            pflast = pftemp;
            j = pftemp->id_food;
            j++;
        }
    }
    printf(YELLOW"* * * * * * * * * * * * * * * *"RESET"\n");
    printf(YELLOW"*"RESET"          "MAGENTA"Food menu"RESET"          "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"                             "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"          "GREEN"Lasagna (1"RESET"         "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"         "GREEN"Sandwich (2"RESET"         "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"           "GREEN"Burger (3"RESET"         "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"          "GREEN"Chicken (4"RESET"         "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"            "GREEN"Pizza (5"RESET"         "YELLOW"*"RESET"\n");
    printf(YELLOW"*"RESET"                             "YELLOW"*"RESET"\n");
    printf(YELLOW"* * * * * * * * * * * * * * * *"RESET"\n");
    printf(BLUE"Please choose the food you want (home page: 0): "RESET);
    scanf("%d",& food_type_choise);
    if(food_type_choise == 0){
        first_menu();
    }
    pfnew = new struct foods;
    pfnew->id_food = j;
    pfnew->id_order = potemp->number_order;
    switch(food_type_choise){
        case Lasagna:
            pfnew->number_type_food = Lasagna;
            strcpy(pfnew->food_name, "Lasanga");
            break;
        case Sandwich:
            pfnew->number_type_food = Sandwich;
            strcpy(pfnew->food_name, "Sandwich");
            break;
        case Burger:
            pfnew->number_type_food = Burger;
            strcpy(pfnew->food_name, "Burger");
            break;
        case Chicken:
            pfnew->number_type_food = Chicken;
            strcpy(pfnew->food_name, "Chicken");
            break;
        case Pizza:
            pfnew->number_type_food = Pizza;
            strcpy(pfnew->food_name, "Pizza");
            break;
        default:
            system("cls || clear");
            printf("\n"RED"The entered number is not valid. Please enter one of the options correctly."RESET);
            usleep(3000000);
            add_food(potemp, pohead);
    }
    printf(BLUE"\nPlease enter the quantity of food you need: "RESET);
    scanf("%d",& pfnew->number_food);
    system("cls || clear");
    printf("\n"GREEN"Your food has been successfully added."RESET);
    usleep(3000000);
    pflast->pfnext = pfnew;
    write_food(pohead);
    add_food(potemp, pohead);
}

//write kardan foods bar rooye file
void write_food(struct order* pohead){
    struct order *potemp;
    struct foods *pftemp;
    FILE *food_file;
    food_file = fopen("food.bin", "wb");
    for(potemp = pohead; potemp != NULL; potemp = potemp->ponext){
        for(pftemp = potemp->pfhead; pftemp != NULL; pftemp = pftemp->pfnext){
            fwrite(pftemp, sizeof(struct foods), 1, food_file);
        }
    }
    fclose(food_file);
}

//neveshtan tamam etalat tamam sefareshat
void review(struct order* pohead){
    struct order *potemp;
    struct foods *pftemp;
    int choise;
    char situation[15];
    system("cls || clear");
    for(potemp = pohead; potemp != NULL; potemp = potemp->ponext){
        if(potemp->situation == DOING){
            strcpy(situation, "Doing");
        }
        else if(potemp->situation == DELIVERED){
            strcpy(situation, "Delivered");
        }
        else if(potemp->situation == CANCLE){
            strcpy(situation, "Cancle");
        }
        printf("   "MAGENTA"studetn number > %d \n"RESET, potemp->number_std);
        printf("         "MAGENTA"order id > %d \n"RESET, potemp->number_order);
        printf("             "MAGENTA"name > %s \n"RESET, potemp->name);
        printf("           "MAGENTA"family > %s \n"RESET, potemp->family);
        printf("        "MAGENTA"situation > %s "RESET, situation);
        printf("\n\n");
        printf(YELLOW"***************(foods)***************"RESET"\n\n");
        for(pftemp = potemp->pfhead; pftemp != NULL; pftemp = pftemp->pfnext){
            printf("          "GREEN"food id > %d \n"RESET, pftemp->id_food);
            printf("        "GREEN"food name > %s \n"RESET, pftemp->food_name);
            printf("   "GREEN"number of food > %d \n\n"RESET, pftemp->number_food);
            printf(YELLOW"*************************************"RESET"\n\n");        
        }
    }
    printf("           "RED"Home page (1\n"RESET);
    printf("                "RED"Exit (2\n\n"RESET);
    printf(BLUE"Please enter your choise: "RESET);
    scanf("%d",& choise);
    switch(choise){
        case 1:
            first_menu();
            break;
        case 2:
            exit(0);
        default:
            system("cls || clear");
            printf("\n"RED"The entered number is not valid. Please enter one of the options correctly."RESET);
            usleep(3000000);
            review(pohead);
    }
}