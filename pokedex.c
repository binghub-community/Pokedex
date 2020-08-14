// Assignment 2 19T1 COMP1511: Pokedex
// pokedex.c
//
// This program was written by YOUR-NAME-HERE (z5555555)
// on INSERT-DATE-HERE
//
// Version 1.0.0: Assignment released.
// Version 1.0.1: Minor clarifications about `struct pokenode`.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Add any extra #includes your code needs here.

//
// But note you are not permitted to use functions from string.h
// so do not #include <string.h>

#include "pokedex.h"

// Add your own #defines here.

#define T 1
#define F 0

// Note you are not permitted to use arrays in struct pokedex,
// you must use a linked list.
//
// You are also not permitted to use arrays in any of the functions
// below.
//
// The only exception is that char arrays are permitted for
// search_pokemon and functions it may call.
//
// You will need to add fields to struct pokedex.
// You may change or delete the head field.

struct pokedex {
    struct pokenode *head;
    struct pokenode *curr;
};


// You don't have to use the provided struct pokenode, you are free to
// make your own struct instead.
// If you use the provided struct pokenode, you will need to add fields
// to it to store other information.

struct pokenode {
    struct pokenode *next;
    struct pokenode *prev;
    int             found;
    Pokemon         pokemon;
    struct pokenode *evolution;
};

// Add any other structs you define here.

struct pokenode *new_pokenode(Pokemon pokemon){
    struct pokenode *nPokenode = malloc(sizeof(*nPokenode));
    nPokenode->pokemon = pokemon;
    nPokenode->next = NULL;
    nPokenode->found = F;
    nPokenode->evolution = NULL;
    return nPokenode;
}

// Add prototypes for any extra functions you create here.


// You need to implement the following 20 functions.
// In other words, replace the lines calling fprintf & exit with your code.
// You can find descriptions of what each function should do in pokedex.h


Pokedex new_pokedex(void){
    Pokedex nPokedex = malloc(sizeof (*nPokedex));
    assert(new_pokedex != NULL);
    // add your own code here
    nPokedex->head = NULL;
    nPokedex->curr = NULL;
    return nPokedex;
}

////////////////////////////////////////////////////////////////////////
//                         Stage 1 Functions                          //
////////////////////////////////////////////////////////////////////////

void add_pokemon(Pokedex pokedex, Pokemon pokemon){
    struct pokenode *temp = pokedex->head;
    if (pokedex->head == NULL){
        pokedex->head = new_pokenode(pokemon);
        pokedex->curr = new_pokenode(pokemon);
        pokedex->curr->prev = NULL;
        pokedex->curr->next = NULL;
        pokedex->head->next = NULL;
    } else {
        while (temp != NULL){
            if (temp->pokemon == pokemon){
                break;
            } else if (temp->next == NULL){
                temp->next = new_pokenode(pokemon);
                break;
            }
            temp = temp->next;
        }
    }
    return;
}

void detail_pokemon(Pokedex pokedex){
    struct pokenode *temp = pokedex->curr;
    int i = 0;
    
    if (temp->found == T){
        if (pokemon_id(temp->pokemon) < 10){
            printf("Id: 00%d\n", pokemon_id(temp->pokemon));
        } else if (pokemon_id(temp->pokemon) > 10 && pokemon_id(temp->pokemon) < 100){
            printf("Id: 0%d\n", pokemon_id(temp->pokemon));
        } else {
            printf("Id: %d\n", pokemon_id(temp->pokemon));
        }
        printf("Name: %s\n", pokemon_name(temp->pokemon));
        printf("Height: %1fm\n", pokemon_height(temp->pokemon));
        printf("Weight: %1fkg\n", pokemon_weight(temp->pokemon));
        if (pokemon_second_type(temp->pokemon) == NONE_TYPE){
            printf("Type: %s\n", pokemon_type_to_string(pokemon_first_type(temp->pokemon)));
        } else {
            printf("Type: %s %s\n", pokemon_type_to_string(pokemon_first_type(temp->pokemon)), pokemon_type_to_string(pokemon_second_type(temp->pokemon)));
        }
    } else if (temp->found == F){
        if (pokemon_id(temp->pokemon) < 10){
            printf("Id: 00%d\n", pokemon_id(temp->pokemon));
        } else if (pokemon_id(temp->pokemon) > 10 && pokemon_id(temp->pokemon) < 100){
            printf("Id: 0%d\n", pokemon_id(temp->pokemon));
        } else {
            printf("Id: %d\n", pokemon_id(temp->pokemon));
        }
        printf("Name: ");
        while (pokemon_name(temp->pokemon)[i] != '\0'){
            printf("*");
            i++;
        }
        printf("\n");
        printf("Height: --\n");
        printf("Weight: --\n");
        printf("Type: --\n");
    }
    
    return;
}

Pokemon get_current_pokemon(Pokedex pokedex){
    if (pokedex->head == NULL){
        printf("Error: No Pokemon currently in Pokedex. Goodbye Ash Ketchup!");
        exit(0);
    }
    return pokedex->curr->pokemon;
}

void find_current_pokemon(Pokedex pokedex){
    pokedex->curr->found = T;
    return;
}

void print_pokemon(Pokedex pokedex){
    
    struct pokenode *temp = pokedex->head;
    
    while (temp != NULL){
        if (temp->pokemon == pokedex->curr->pokemon){
            printf("--> ");
        } else {
            printf("    ");
        }
        printf("#");
        if (pokemon_id(temp->pokemon) < 10){
            printf("00%d", pokemon_id(temp->pokemon));
        } else if (pokemon_id(temp->pokemon) > 10 && pokemon_id(temp->pokemon) < 100){
            printf("0%d", pokemon_id(temp->pokemon));
        } else {
            printf("%d", pokemon_id(temp->pokemon));
        }
        
        printf(": ");
        
        if (temp->found == T){
            printf("%s", pokemon_name(temp->pokemon));
        } else if (temp->found == F){
            int i = 0;
            while (pokemon_name(temp->pokemon)[i] != '\0'){
                printf("*");
                i++;
            }
        }
        
        printf("\n");
        temp = temp->next;
    }
        

    
}

////////////////////////////////////////////////////////////////////////
//                         Stage 2 Functions                          //
////////////////////////////////////////////////////////////////////////

void next_pokemon(Pokedex pokedex){
    if (pokedex->curr == NULL){
        return;
    } else if (pokedex->curr->next== NULL){
        return;
    } else {
        pokedex->curr = pokedex->curr->next;
    }
    
    return;
}

void prev_pokemon(Pokedex pokedex){
    struct pokenode *temp = pokedex->head;
    if (pokedex->head == NULL){
        return;
    } else if (pokedex->curr == pokedex->head){
        return;
    } else if (pokedex->curr == pokedex->head->next){
        pokedex->curr->prev = pokedex->head;
        return;
    }
    while (temp->next->next != NULL){
        if (temp->next->next == pokedex->curr){
            pokedex->curr = temp->next;
            pokedex->curr->prev = temp;
            pokedex->curr->next = temp->next->next;
            break;
        } else {
            temp = temp->next;
        }
    }
    return;
}

void change_current_pokemon(Pokedex pokedex, int id){
    struct pokenode *temp = pokedex->head;
    while (temp->next != NULL){
        if (pokemon_id(temp->pokemon) == id){
            pokedex->curr = temp;
            break;
        } else {
            temp = temp->next;
        }
    }
    return;
}

void remove_pokemon(Pokedex pokedex){
    struct pokenode *temp = pokedex->head;
    if (pokedex->head == NULL){
        return;
    } else if (pokedex->head->next == NULL){
        pokedex->head = NULL;
    }
    
    while (temp != NULL){
        if (temp->next == pokedex->curr){
            break;
        } else {
            temp = temp->next;
        }
    }
    
    temp->next = temp->next->next;
    pokedex->curr = temp->next;
    return;
}

////////////////////////////////////////////////////////////////////////
//                         Stage 3 Functions                          //
////////////////////////////////////////////////////////////////////////

void go_exploring(Pokedex pokedex, int seed, int factor, int how_many){
    struct pokenode *temp = pokedex->head;
    srand(seed);
    int i = 0;
    int poke_id;
    while (i < how_many){
        poke_id = rand() % factor;
        while (temp != NULL){
            if (pokemon_id(temp->pokemon) == poke_id){
                temp->found = T;
                break;
            } else {
                temp = temp->next;
            }
        }
        i++;
    }
}

int count_found_pokemon(Pokedex pokedex){
    struct pokenode *temp = pokedex->head;
    int counter = 0;
    
    if (pokedex->head == NULL){
        return 0;
    }
    
    while (temp != NULL){
        if (temp->found == T){
            counter++;
            temp = temp->next;
        } else {
            temp = temp->next;
        }
    }
    
    return counter;
}

int count_total_pokemon(Pokedex pokedex){
    struct pokenode *temp = pokedex->head;
    int counter = 0;
    
    if (pokedex->head == NULL){
        return 0;
    }
    
    while (temp != NULL){
        counter++;
        temp = temp->next;
    }
    return counter;
}

////////////////////////////////////////////////////////////////////////
//                         Stage 4 Functions                          //
////////////////////////////////////////////////////////////////////////

void add_pokemon_evolution(Pokedex pokedex, int from_id, int to_id){
    struct pokenode *temp = pokedex->head;
    struct pokenode *preEvo = NULL;
    struct pokenode *postEvo = NULL;
    int count = 0;
    while (temp != NULL) {
        if (pokemon_id(temp->pokemon) == from_id) {
            count ++;
            preEvo = new_pokenode(temp->pokemon);
        } else if (pokemon_id(temp->pokemon) == to_id) {
            count ++;
            postEvo = new_pokenode(temp->pokemon);
        }
        if (count == 2) {
            break;
        }
        temp = temp->next;
    }
    if (count == 2) {
        preEvo->evolution = postEvo;
    } else {
        return;
    }
}

void show_evolutions(Pokedex pokedex){
    struct pokenode *pokeTemp = pokedex->curr;
    if (pokedex->curr == NULL){
        return;
    }
    while (pokeTemp != NULL){
        printf("#");
        if (pokemon_id(pokeTemp->pokemon) < 10){
            printf("Id: 00%d", pokemon_id(pokeTemp->pokemon));
        } else if (pokemon_id(pokeTemp->pokemon) > 10 && pokemon_id(pokeTemp->pokemon) < 100){
            printf("Id: 0%d", pokemon_id(pokeTemp->pokemon));
        } else {
            printf("Id: %d", pokemon_id(pokeTemp->pokemon));
        }
        
        printf(" ");
        
        if (pokeTemp->found == T){
            printf("%s ", pokemon_name(pokeTemp->pokemon));
            if (pokemon_second_type(pokeTemp->pokemon) == NONE_TYPE){
                printf("[%s]", pokemon_type_to_string(pokemon_first_type(pokeTemp->pokemon)));
            } else {
                printf("[%s, %s]", pokemon_type_to_string(pokemon_first_type(pokeTemp->pokemon)), pokemon_type_to_string(pokemon_second_type(pokeTemp->pokemon)));
            }
        } else if (pokeTemp->found == F){
            printf("???? ");
            if (pokemon_second_type(pokeTemp->pokemon) == NONE_TYPE){
                printf("[????]");
            } else {
                printf("[????, ????]");
            }
        }
        
        pokeTemp = pokeTemp->evolution;
        if (pokeTemp->evolution != NULL){
            printf(" --> ");
        }
    }
}

int get_next_evolution(Pokedex pokedex){
    return pokemon_id(pokedex->curr->evolution->pokemon);
}

////////////////////////////////////////////////////////////////////////
//                         Stage 5 Functions                          //
////////////////////////////////////////////////////////////////////////

Pokedex get_pokemon_of_type(Pokedex pokedex, pokemon_type type){
    Pokedex typePokedex = new_pokedex();
    struct pokenode *temp = pokedex->head;
    while (temp != NULL) {
        if (pokemon_second_type(temp->pokemon) == type || pokemon_first_type(temp->pokemon) == type) {
            add_pokemon(typePokedex, temp->pokemon);
        }
        temp = temp->next;
    }
    return typePokedex;
}

Pokedex get_found_pokemon(Pokedex pokedex){
    Pokedex foundPokedex = new_pokedex();
    struct pokenode *temp = pokedex->head;
    while (temp != NULL) {
        if (temp->found == T) {
            add_pokemon(foundPokedex, temp->pokemon);
        }
        temp = temp->next;
    }
    return foundPokedex;
}

Pokedex search_pokemon(Pokedex pokedex, char *text){
    Pokedex charPokedex = new_pokedex();
    struct pokenode *temp = pokedex->head;
    int i = 0;
    int count = 0;
    while (text[i] != '\0') {
        count++;
        i++;
    }
    i = 0;
    int count2 = 0;
    int x = 0;
    while (temp != NULL) {
        i = 0;
        count = 0;
        while (i < count - 1) {
            x = 0;
            while (x < count) {
                if (pokemon_name(temp->pokemon)[i + x] == text[x]) {
                    count2++;
                    x++;
                } else {
                    break;
                }
            }
        }
        if (count2 == count) {
            add_pokemon(charPokedex, temp->pokemon);
        }
        temp = temp->next;
    }
    return charPokedex;
}

void destroy_pokedex(Pokedex pokedex){
    struct pokenode *temp1 = pokedex->curr;
    struct pokenode *prev;
    
    while (temp1 != NULL) {
        prev = temp1;
        temp1 = temp1->next;
        destroy_pokemon(prev->pokemon);
        free(prev);
    }
    free(pokedex);
    return;
}

// Add definitions for your own functions below.
// Make them static to limit their scope to this file.

