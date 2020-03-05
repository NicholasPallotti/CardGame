//Nicholas Pallotti
//Card Game Part 1
//date submitted 2/12
//date revised 2/14
//this program will evetualy run a card game that uses a 52 card deck
//the deck will have 5 colors and numbers 1-10 as well as wild cards
//the objective of the game is to group cards with matching colors or 
//numbers, the player with the least unmatched cards wins
#include <iostream>
#include<string>
#include <iomanip>
#include <stdlib.h>
#include <ctime>
#include <vector>
#include <string>
using namespace std;



///testing changes


/************************************************
        Card
A Card object contains two variables, a character 
representing the cards' color, and the number of the card.
the class has a defualt constructor and a constructor for 
being passed data for both variables.
************************************************/
class Card {

    private:
        char color; //the color of the card
        int number; //the number of the card

    public:
        //default contructor
        Card() {
            color = 'o';
            number = 0;
        }
        //constructor that is passed both the data types
        Card(char newColor, int newNumber) {
            color = newColor;
            number = newNumber;
        }

        //setters
        void setColor(char newColor) {
            color = newColor;
        }
        void setNumber(int newNumber) {
            number = newNumber;
        }

        //getters
        char getColor() {
            return color;
        }
        int getNumber() {
            return number;
        }



};

/************************************************
        Player
Players contain one variable, an array of Cards called
hand. only has a default constructor
************************************************/
class Player {
    private:
        vector<Card> hand; //create an vector for holding the players cards
        int score;    //player's score
    public:
        Player() {
            score = 10;
            hand = {};
        }

        //getter for the player's score
        int getScore() {
            return score;
        }

        //setter for the player's score
        void setScore(int modifier) {
            score -= modifier;
            if (score < 0) {
                score = 0;
            }
        }
    
        /************************************************
            displayHand
        parameter: none
        return value: none
        description: for each Card in the players hand prints the Card's number 
        and color.
        ************************************************/
        void displayHand() {

            cout << "players hand: " << endl;
            for (int i = 0; i < hand.size(); i++) { //loops over each card in the players hand and prints the number and color
                cout << hand.at(i).getColor() << ", " << hand.at(i).getNumber() << endl;
            }

            //creates a space after the hand is printed to look nice
            cout << endl << endl;
        }

        /************************************************
            chooseDiscard
        parameter: discard: vector of Cards
        return value: none
        description: prints the player's hand then prompts them to choose a card 
        to discard.
        ************************************************/
        void chooseDiscard() {
            
            displayHand();
            int number;     //holds the color of the card to be discarded
            char color;     //holds the number of the card to be discarded

            //pormpts the player to input the number and color of the card to be discarded and stores the values 
            cout << "what is the cards number? ";
            cin >> number;
            cout << "what is the cards color? ";
            cin >> color;

            for (int i = 0; i < hand.size(); i++) { //loop over the players hand
        
                //if the current card in the players hand matches the one chosen to be discarded by the player, move it to the discard vector
                if ((hand.at(i).getColor() == color) && (hand.at(i).getNumber() == number)) {
                    hand.erase(hand.begin() + i);
                    hand.shrink_to_fit();
                }
            }
        }

        /************************************************
            draw
        parameter: deck: vector of Cards
        return value: player, deck: player, array of Cards
        description: removes a card from the back of the deck, and adds it to the 
        player's hand.
        ************************************************/
        void draw(vector<Card>& deck) {
            
            //add a card to the players hand, remove it from the deck, then shrink the size of the deck
            hand.push_back(deck.back());
            deck.pop_back();
            deck.shrink_to_fit();
        }

        /************************************************
            groupByNumbers
        parameter: none
        return value: groupSize: int
        description: prompts the player to input cards to be grouped by number, checks to make
        sure the group is valid, and removes the chosen cards from the player's hand,
        then reutrns the number of cards that were discarded
        ************************************************/
        int groupByNumbers() {
            
            Card card;  //card to be discarded
            vector<Card> cardsToDiscard;  //vector holding the cards to be discarded
            char col;  //variable for holding the user input of the color of a card to be discarded
            int num;   //variable for holding the user input of the number of the card to be discarded

            cout << "type each card's color, then number individualy (for example type 'r' for red, then 6).";
            cout << "type f for the color if you are finished ";

            //do while the user still wants to discard cards
            do {

                cin >> col;

                //make sure that the user wants to continue before prompting them to input the cards number
                //if the user is not exiting add the specified card to the cardsToDiscard vector
                if (col != 'f') {
                    cin >> num;
                    card.setColor(col);
                    card.setNumber(num);
                    cardsToDiscard.push_back(card);
                }

            } while (col != 'f');


            int numCompare = card.getNumber(); //numCompare will be compared to make sure a valid group has been made
            int groupSize = cardsToDiscard.size(); //number of cards that need to be discarded

            //check to make sure player chose a valid goruping of cards
            for (int i = 0; i < groupSize; i++) {
                cout << cardsToDiscard.at(i).getColor() << endl;
                if (cardsToDiscard.at(i).getColor() != numCompare) {
                    cout << "That is an invalid grouping of cards";
                    return 0; //leave this method if the group is invalid so no cards are discarded
                }
            }

            //for each card that needs to be discarded search the players hand for a matching card and discard it
            for (int i = 0; i < groupSize; i++) {
                for (int j = 0; j < hand.size(); j++) {
                    if ((hand.at(j).getColor() == cardsToDiscard.at(i).getColor()) && (hand.at(j).getNumber() == cardsToDiscard.at(i).getNumber())) {
                        hand.erase(hand.begin() + j);
                        hand.shrink_to_fit();
                    }

                }
            }

            //return the number of cards discarded
            return groupSize;
            
        }

        /************************************************
            groupByColors
        parameter: none
        return value: groupSize: int
        description: prompts the player to input cards to be grouped by color, checks to make
        sure the group is valid, and removes the chosen cards from the player's hand,
        then reutrns the number of cards that were discarded
        ************************************************/
        int groupByColors() {

            Card card;  //card to be discarded
            vector<Card> cardsToDiscard;  //vector holding the cards to be discarded
            char col;  //variable for holding the user input of the color of a card to be discarded
            int num;   //variable for holding the user input of the number of the card to be discarded

            cout << "type each card's color, then number individualy (for example type 'r' for red, then 6).";
            cout << "type f for the color if you are finished ";
            
            //do while the user still wants to discard cards
            do {

                cin >> col;

                //make sure that the user wants to continue before prompting them to input the cards number
                //if the user is not exiting add the specified card to the cardsToDiscard vector
                if (col != 'f') {
                    cin >> num;
                    card.setColor(col);
                    card.setNumber(num);
                    cardsToDiscard.push_back(card);
                }

            } while (col != 'f');

            
            char color = card.getColor(); //color will be compared to make sure a valid group has been made
            int groupSize = cardsToDiscard.size(); //number of cards that need to be discarded

            //check to make sure player chose a valid goruping of cards
            for (int i = 0; i < groupSize; i++) {
                cout << cardsToDiscard.at(i).getColor() << endl;
                if (cardsToDiscard.at(i).getColor() != color) {
                    cout << "That is an invalid grouping of cards";
                    return 0; //leave this method if the group is invalid so no cards are discarded
                }
            }

            //for each card that needs to be discarded search the players hand for a matching card and discard it
            for (int i = 0; i < groupSize; i++) {
                for (int j = 0; j < hand.size(); j++) {
                    if ((hand.at(j).getColor() == cardsToDiscard.at(i).getColor()) && (hand.at(j).getNumber() == cardsToDiscard.at(i).getNumber())) {
                        hand.erase(hand.begin() + j);
                        hand.shrink_to_fit();
                    }

                }
            }

            //return the number of cards discarded
            return groupSize;
        }

};


//prototypes
void createCards(vector<Card>& deck);              //creates the cards for the game and fills the deck with them
void shuffle(vector<Card>& deck);                  //randomizes the order of the card objects in the deck
void deal(Player players[], vector<Card>& deck);   //puts 10 cards in each players hand, taking the cards form the deck
void score(Player players[]);                      //calculates the score of the players

//runs the game
int main()
{

    srand(time(0));
    vector<Card> deck;    //vector that holds each card
    Player players[4];    //array that contains each player

    //creates four players and adds them to the array players
    for (int i = 0; i < 4; i++) {
        Player player;
        players[i] = player;
    }

    //set up the game by calling createCards and deal
    createCards(deck);  
    deal(players, deck);

    //test the displayHand and chooseDiscard function in player class
    players[0].displayHand();
    players[0].chooseDiscard();

    //test score function
    score(players);

    system("pause");
}

/************************************************
        createCards
parameter: deck : vector of Cards
return value: array: array of cards
description: using for loops create cards with the colors
'r'ed, 'b'lue, 'g'reen, 'p'urple, and 'o'range, each 
color has cards numbered 1-10. then two 'w'ild cards are made 
************************************************/
void createCards(vector<Card>& deck) {

    //create cards numbered 1-10 for each color
    for (int i = 1; i < 11; i++) {
        Card card('r', i);
        deck.push_back(card);
    }
    for (int i = 1; i < 11; i++) {
        Card card('b', i);
        deck.push_back(card);
    }
    for (int i = 1; i < 11; i++) {
        Card card('g', i);
        deck.push_back(card);
    }
    for (int i = 1; i < 11; i++) {
        Card card('p', i);
        deck.push_back(card);
    }
    for (int i = 1; i < 11; i++) {
        Card card('o', i);
        deck.push_back(card);
    }

    //create two wild cards (the color is 'w' for 'wild')
    for (int i = 1; i < 3; i++) {
        Card card('w', i);
        deck.push_back(card);
    }
}

/************************************************
        shuffle
parameter: deck : vector of Cards
return value: none
description: loops through the deck array, and for each Card
randomly decide a new spot in the array to to place the Card,
swaps the locations of Card in that spot and the current Card.

************************************************/
void shuffle(vector<Card>& deck) {

    int newLocation; //variable for shuffling, determines cards' location to be moved to

        //this loops over each position in the deck and swaps the card in it with another 
       //card in a random position in the deck
        for (int i = 0; i < 52; i++) {
            
            //choose a random spot in the deck
            newLocation = rand() % 52;

            //swap the cards in the randomly chosen spot and the current spot
            Card tempCard = deck[newLocation];
            deck[newLocation] = deck[i];
            deck[i] = tempCard;
        }
    

}

/************************************************
        deal
parameter: players, deck: array of Players, vector of Cards
return value: none
description: adds 10 cards to each players hand
************************************************/
void deal(Player players[], vector<Card>& deck) {
    
    for (int i = 0; i < 4; i++) { //for each player
        for (int j = 0; j < 10; j++) { //for loop drawing the player 10 cards
            players[i].draw(deck);
        }  
    }
}


/************************************************
        score
parameter: players: array of Players
return value: none
description: prompts each player to gorup thier cards and 
calculates thier score.
************************************************/
void score(Player players[]) {

    cout << "scoring will now begin...." << endl << endl;

    int choice;     //stores the players choice on how they would like tog roup thier cards
    int score = 0;  //used in the setter for score in the player class

    for (int i = 0; i < 4; i++) {   //loops over each player
        cout << "scoring for player " << i << endl;
        do { //continue scoring scoring untill player is done grouping

            players[i].displayHand();

            //menu prompting player to choose how to group cards or if they are done, then stores thier choice
            cout << "how would you like to group the next group of cards?" << endl;
            cout << "1. by number" << endl;
            cout << "2. by color" << endl;
            cout << "3. I'm finished" << endl << endl;
            cin >> choice;

            //if else staements performing the action the player chose
            if (choice == 1) {
               score = players[i].groupByNumbers();
            }
            else if (choice == 2) {
               score = players[i].groupByColors();
            }
            else if (choice != 3) {
                cout << "invalid choice, please try again.";
            }

            if (score > 4) { //if the player made a group of atleast 5 cards subtract an additional point
                score -= 1;
            }

            players[i].setScore(score); //subtract the number of cards grouped from the players score

        } while (choice != 3); //end of do while loop
        
    }
}









