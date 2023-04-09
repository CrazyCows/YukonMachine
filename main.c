#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


void create_node(){

}
// Each card represent a Node in the linked list
typedef struct Card{
    // Clubs, diamonds, Hearts, Spades
    char cardType;
    // Ace, numbers, jacks, queens, kings
    char cardValue;
    // Loads the next and previous memory location for sorrounding cards
    struct Card *next;
    struct Card *previous;
} Card;

/*
 * To be implemented
 */
// Creates a card from a given deck.
Card* createCard(int cardValue, int cardType, Card *next){
    // *** Following is just an explanation for allocating memory ***
    /* *card represents the memory location we want to allocate
     * (Card*) is a type cast. This will convert the pointer from 'void*' to 'Card*'
     * malloc() allocates a specified amount of bytes.
     * In our case the amount of bytes we wish to reserve is equal to or a little more than the struct Card()
     * An estimate of the actual size of Card would be 6 bytes on a 32 bit system and 10 bytes on a 64 bit system.
     * The two chars each takes up one byte. The pointers size depends on the system. Addresses for 32 bit is 4 bytes and 64 bit is 8 bytes.
     * Card might be expanded later to also include
     */

    Card *card = (Card*)malloc(sizeof(Card));

    // Assign the type, C/D/H/S
    /*
    if ( == 1){
        card->cardType = 'C';
    } else if (i == 2){
        card->cardType = 'D';
    } else if (i == 3){
        card->cardType = 'H';
    } else if (i == 4){
        card->cardType = 'S';
    }
    if (j == 1){
        card -> cardValue = 'A';
    } else if(j < 10){
        // Converts ASCII int value to char
        card -> cardValue = j + '0';
    } else if(j == 10){
        card -> cardValue = 'S';
    } else if(j == 11){
        card -> cardValue = 'Q';
    } else if(j == 12){
        card -> cardValue = 'K';
    }
    card->next = *head;
    *head = card;
     */


}




// Creates 52 nodes in a double linked list containing the values given in the assignment if no file is given...
// Was created to avoid writing 52 cards by hand... 10/10 time sink!
// Double pointer as we want to change the content outside the function
void createDeck(Card** firstCard, Card** lastCard){
    // Will create a deck with 52 cards, startng
    for (int i = 1; i <= 4; i++){
        for(int j = 1; j <= 13; j++){
            // *** The following is just an explanation for allocating memory ***
            /* *card represents the memory location we want to allocate
             * (Card*) is a type cast. This will convert the pointer from 'void*' to 'Card*'
             * malloc() allocates a specified amount of bytes.
             * In our case the amount of bytes we wish to reserve is equal to or a little more than the struct Card()
             * An estimate of the actual size of Card would be 6 bytes on a 32 bit system and 10 bytes on a 64 bit system.
             * The two chars each takes up one byte. The pointers size depends on the system. Addresses for 32 bit is 4 bytes and 64 bit is 8 bytes.
             * Card might be expanded to a double linked list at which point its size increase to 10 or 16 bytes.
             */
            Card* newCard = (Card*)malloc(sizeof(Card));
            // Assign the type, C/D/H/S
            if (i == 1){
                newCard->cardType = 'C';
            } else if (i == 2){
                newCard->cardType = 'D';
            } else if (i == 3){
                newCard->cardType = 'H';
            } else if (i == 4){
                newCard->cardType = 'S';
            }
            // Assigns the value from ACE to K
            if (j == 1){
                newCard -> cardValue = 'A';
            } else if(j < 10){
                // Converts ASCII int value to char
                newCard -> cardValue = j + '0';
            } else if(j == 10){
                newCard -> cardValue = 'T';
            }else if(j == 11){
                newCard -> cardValue = 'J';
            } else if(j == 12){
                newCard -> cardValue = 'Q';
            } else if(j == 13){
                newCard -> cardValue = 'K';
            }
            // Saves the pointer to the previous card
            newCard->previous = *lastCard;
            // As this is now the last card in the deck, the next card is NULL
            newCard->next = NULL;
            // The first card of an empty deck is always NULL.
            if (*firstCard == NULL){
                // sets the pointer of the first card to point at the new card
                *firstCard = newCard;
            }
            // If not the first entry in the deck
            else {
                // Links the new node to the end of the list by modifying the previous cards next pointer to the current card
                (*lastCard)->next = newCard;
            }
            // Updates the lastCard pointer to the card which has been added last
            *lastCard = newCard;
        }
    }
}
/** The function loadDeck got quite long as it both loads the data and check for corrections simultaneously
 * The function was not split up for overall readability reasons.
 *
 * @param firstCard
 * @param lastCard
 * @param fileName
 * @param textbuf
 * @return
 */
char *loadDeck(Card** firstCard, Card** lastCard, const char *fileName, char **textbuf){
    if (fileName == NULL || fileName == ""){
        createDeck(firstCard, lastCard);
        return "OK, deck created";
    }
    FILE* file = fopen(fileName, "r");
    if (file == NULL){
        return "Invalid file path";
    }

    Card* firstCardTemp = NULL;
    Card* lastCardTemp = NULL;
    createDeck(&firstCardTemp, &lastCardTemp);

    char temp[2];
    for (int i = 1; i <= 53; i++){
        bool charFound = false;
        fgets(temp, 4, file);
        Card* currentCardTemp = firstCardTemp;
        while (currentCardTemp != NULL){
            if (temp[0] == currentCardTemp->cardValue && temp[1] == currentCardTemp->cardType){
                charFound = true;
                if (currentCardTemp->previous == NULL && currentCardTemp->next == NULL){
                    break;
                }
                // If it is the first card in the linked list ("AC"), the firstCard pointer must move to the 2. node
                else if (currentCardTemp->previous == NULL){
                    firstCardTemp = firstCardTemp->next;
                    firstCardTemp->previous = NULL;
                    // Frees the allocated memory from the unlinked card
                    free(currentCardTemp);
                    break;
                }
                    // If the card is the last card, the second last card must become the last card. Pointer moves
                else if (currentCardTemp->next == NULL){
                    lastCardTemp = lastCardTemp->previous;
                    lastCardTemp->next = NULL;
                    free(currentCardTemp);
                    break;
                }
                    // If it is not the first card in the list, the pointers in the
                else {
                    (currentCardTemp->next)->previous = currentCardTemp->previous;
                    (currentCardTemp->previous)->next = currentCardTemp->next;
                    free(currentCardTemp);
                    break;
                }
            }
            currentCardTemp = currentCardTemp->next;
        }

        if (charFound == false){
            snprintf((char *) textbuf, 100, "Error at line: %d", i);
            return textbuf;
        }

        Card* newCard = (Card*)malloc(sizeof(Card));
        // Stores the loaded data in a newly created Card;
        newCard->cardValue = temp[0];
        newCard->cardType = temp[1];
        // Saves the pointer to the previous card
        newCard->previous = *lastCard;
        // As this is now the last card in the deck, the next card is NULL
        newCard->next = NULL;
        // The first card of an empty deck is always NULL.
        if (*firstCard == NULL){
            // sets the pointer of the first card to point at the new card
            *firstCard = newCard;
        }
            // If not the first entry in the deck
        else {
            // Links the new node to the end of the list by modifying the previous cards next pointer to the current card
            (*lastCard)->next = newCard;
        }
        // Updates the lastCard pointer to the card which has been added last
        *lastCard = newCard;
    }


    fclose(file);
    return "OK, file loaded";
}

bool controlDeck(Card* currentCardTemp, Card** firstCardTemp, Card** lastCardTemp, const char *temp){
    while (currentCardTemp != NULL){
        if (temp[0] == currentCardTemp->cardValue && temp[1] == currentCardTemp->cardType){
            if (currentCardTemp->previous == NULL && currentCardTemp->next == NULL){
                return true;
            }
                // If it is the first card in the linked list ("AC"), the firstCard pointer must move to the 2. node
            else if (currentCardTemp->previous == NULL){
                firstCardTemp = (*firstCardTemp)->next;
                (*firstCardTemp)->previous = NULL;
                // Frees the allocated memory from the unlinked card
                free(currentCardTemp);
                return true;
            }
                // If the card is the last card, the second last card must become the last card. Pointer moves
            else if (currentCardTemp->next == NULL){
                lastCardTemp = (*lastCardTemp)->previous;
                (*lastCardTemp)->next = NULL;
                free(currentCardTemp);
                return true;
            }
                // If it is not the first card in the list, the pointers in the
            else {
                (currentCardTemp->next)->previous = currentCardTemp->previous;
                (currentCardTemp->previous)->next = currentCardTemp->next;
                free(currentCardTemp);
                return true;
            }
        }
        currentCardTemp = currentCardTemp->next;
    }return false;

}


// Reads the current deck and saves it
// As we only want to read the content from the linked list we point to the content of Card
// savedDeck returns messages to make it easier to incoporate in a gui...
char *saveDeck(Card* firstCard, const char *savedDeckName){
    // If the users has not given an input default name cards.txt will be given in accordance with the specification
    if (savedDeckName == NULL || savedDeckName == ""){
        savedDeckName = "cards.txt";
    }
    // Creates a new file with the given filename. "w" indicate the file will be created if none exists. If file with same name exists, it will be formatted.
    FILE* file = fopen(savedDeckName, "w");
    // If file could not be created, print an error message
    if (file == NULL) {
        // 48 chars used
        return "Error: Unable to create the file. check filepath";
    }
    // temporary pointer currentCard made to not traverse the actual deck
    Card* currentCard = firstCard;
    // If the current card is null, the linked list must be at the very end
    while (currentCard != NULL){
        // Prints the card values to the file
        fprintf(file, "%c%c\n", currentCard->cardValue, currentCard->cardType);
        // sets current card to the next card
        currentCard = currentCard->next;
    }
    // Closes the file
    fclose(file);
    return "Success! File saved.";
}

int main(){
    /*
     * Essentially we are creating an object of type Card and do stuff with it
     */

    char *errorMessages[100];



    // Declares starting address of firstCard
    // -------- Explain why firscard must be an object of card, and why we initialize at NULL. Also explain why we want to pass the address of operate (&) to optain the pointers address.
    // -------- Could also explain why & must be used when passing to a double-pointer fun...
    Card* firstCard = NULL;
    Card* lastCard = NULL;
    // Gives the address to createDeck. firstCard will change accordingly and will no longer be empty
    //createDeck(&firstCard, &lastCard);

    printf("%s", loadDeck(&firstCard, &lastCard, "savedDeck.txt", errorMessages));
    Card* current = firstCard;
    // Prints, for testing
    //char *str = saveDeck(firstCard, "");
    //printf("%s\n", str);

    // just for testing.. Prints the current deck

    printf("\n");
    if (firstCard != NULL){
        while (current != NULL){
            printf("%c%c\n", current->cardValue, current->cardType);
            current = current->next;
        }
    }


    printf("\nCode finished succesfully");
    return 1;
}

