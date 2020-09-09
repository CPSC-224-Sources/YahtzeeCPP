/**
 * Yahtzee1 - A program that plays and scores one hand of Yahtzee
 * Used in CPSC 224 - Gonzaga University
 * Programming Assignment #1
 * No sources to cite
 *
 * @author: Bruce Worobec <worobec@gonzaga.edu>
 * @copyright: 2020
 *
 * @contributors:
 *   Aaron S. Crandall <crandall@gonzaga.edu>, 2020
 *
 * @version v1.0 2020.09.03
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

// Forward function interface declarations
int rollDie();
int maxOfAKindFound(int []);
int maxStraightFound(int []);
bool fullHouseFound(int []);
int totalAllDice(int []);
void sortArray(int [], int);
void generateHand(int [], int);
void calcAndOutputScores(int [], int);


// Main function - point of program's start
int main()
{
    const int DICE_IN_PLAY = 5;
    int hand[DICE_IN_PLAY];
    char playAgain = 'y';

    srand(time(0));                 // Initialize random number generator

    while (playAgain == 'y')
    {
        generateHand(hand, DICE_IN_PLAY);
        calcAndOutputScores(hand, DICE_IN_PLAY);

        std::cout << std::endl << "Enter 'y' to play again ";
        std::cin >> playAgain;
    }
    return 0;
}


void calcAndOutputScores(int hand[], int dice_in_play)
// Calculate and output scores for a given hand
{
    // Hand need to be sorted to check for straights
    sortArray(hand, dice_in_play);
    std::cout << "here is your sorted hand : ";
    for (int dienumber = 0; dienumber < dice_in_play; dienumber++)
    {
        std::cout << hand[dienumber] << " ";
    }
    std::cout << std::endl;

    // Upper scorecard
    for (int dievalue = 1; dievalue <= 6; dievalue++)
    {
        int currentcount = 0;
        for (int dieposition = 0; dieposition < 5; dieposition++)
        {
            if (hand[dieposition] == dievalue)
            {
                currentcount++;
            }
        }
        std::cout << "score " << dievalue * currentcount << " on the ";
        std::cout << dievalue << " line" << std::endl;
    }

    // Lower scorecard
    if (maxOfAKindFound(hand) >= 3)
    {
        std::cout << "score " << totalAllDice(hand) << " on the ";
        std::cout << "3 of a kind line" << std::endl;
    }
    else std::cout << "score 0 on the 3 of a kind line" << std::endl;

    if (maxOfAKindFound(hand) >= 4)
    {
        std::cout << "score " << totalAllDice(hand) << " on the ";
        std::cout << "4 of a kind line" << std::endl;
    }
    else std::cout << "score 0 on the 4 of a kind line" << std::endl;

    if (fullHouseFound(hand))
        std::cout << "score 25 on the full house line" << std::endl;
    else
        std::cout << "score 0 on the full house line" << std::endl;

    if (maxStraightFound(hand) >= 4)
        std::cout << "score 30 on the small straight line" << std::endl;
    else
        std::cout << "score 0 on the small straight line" << std::endl;

    if (maxStraightFound(hand) >= 5)
        std::cout << "score 40 on the large straight line" << std::endl;
    else
        std::cout << "score 0 on the large straight line" << std::endl;

    if (maxOfAKindFound(hand) >= 5)
        std::cout << "score 50 on the yahtzee line" << std::endl;
    else
        std::cout << "score 0 on the yahtzee line" << std::endl;

    std::cout << "score " << totalAllDice(hand) << " on the ";
    std::cout << "chance line" << std::endl;
}


void generateHand(int hand[], int DICE_IN_PLAY)
// Work with player to calculate their hand of dice
//  Side effects: changes hand[] values for caller
{
    std::string keep = "nnnnn"; // Setup to roll all dice in the first roll
    int turn = 1;

    while (turn < 4 && keep != "yyyyy")
    {
        // Roll dice not kept
        for (int dieNumber = 0; dieNumber < DICE_IN_PLAY; dieNumber++)
        {
            if (keep[dieNumber] != 'y')         // Index string as array
            {
                hand[dieNumber] = rollDie();    // Re-roll that die
            }
        }

        // Output roll
        std::cout << "Your roll was: ";
        for (int dieNumber = 0; dieNumber < DICE_IN_PLAY; dieNumber++)
        {
            std::cout << hand[dieNumber] << " ";
        }
        std::cout << std::endl;

        // If not the last roll of the hand prompt the user for dice to keep
        if (turn < 3)
        {
            std::cout << "enter dice to keep (y or n) ";
            std::cin >> keep;
        }

        turn++;
    }
}


int rollDie()
// This function simulates the rolling of a single die
{
    int roll = rand() % 6 + 1;
    return roll;      // 'roll' is superfluous, but compiler will handle that
}


int maxOfAKindFound(int hand[])
// This function returns the count of the die value occurring most in the hand
//  but not the value itself
{
    int maxCount = 0;
    int currentCount ;
    for (int dieValue = 1; dieValue <= 6; dieValue++)
    {
        currentCount = 0;
        for (int diePosition = 0; diePosition < 5; diePosition++)
        {
            if (hand[diePosition] == dieValue)
            {
                currentCount++;
            }
        }
        if (currentCount > maxCount)
        {
            maxCount = currentCount;
        }
    }
    return maxCount;
}


int totalAllDice(int hand[])
// This function returns the total value of all dice in a hand
{
    int total = 0;
    for (int diePosition = 0; diePosition < 5; diePosition++)
    {
        total += hand[diePosition];
    }
    return total;
}


void sortArray(int array[], int array_size)
// Bubble sort from Gaddis chapter 8
{
   bool swap;
   int temp;

   do
   {
      swap = false;     // Short circuit flag - stops if sorted pass

      for (int count = 0; count < (array_size - 1); count++)
      {
         if (array[count] > array[count + 1])
         {
            temp = array[count];
            array[count] = array[count + 1];
            array[count + 1] = temp;
            swap = true;
         }
      }
   } while (swap);
}


int maxStraightFound(int hand[])
// This function returns the length of the longest
//  straight found in a hand
{
    int maxLength = 1;
    int curLength = 1;
    for(int counter = 0; counter < 4; counter++)
    {
        if (hand[counter] + 1 == hand[counter + 1] ) //jump of 1
        {
            curLength++;
        }
        else if (hand[counter] + 1 < hand[counter + 1]) //jump of >= 2
        {
            curLength = 1;
        }
        if (curLength > maxLength)
        {
            maxLength = curLength;
        }
    }
    return maxLength;
}


bool fullHouseFound(int hand[])
// This function returns true if the hand is a full house
//  or false if it does not
{
    bool foundFH = false;
    bool found3K = false;
    bool found2K = false;
    int currentCount ;

    for (int dieValue = 1; dieValue <= 6; dieValue++)
    {
        currentCount = 0;
        for (int diePosition = 0; diePosition < 5; diePosition++)
        {
            if (hand[diePosition] == dieValue)
            {
                currentCount++;
            }
        }
        if (currentCount == 2)
        {
            found2K = true;
        }
        if (currentCount == 3)
        {
            found3K = true;
        }
    }

    if (found2K && found3K)
    {
        foundFH = true;
    }

    return foundFH;
}
