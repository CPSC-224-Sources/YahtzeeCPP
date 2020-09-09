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


/**
 * Main function - point of program's start
 * 
 * @return Success or error of execution, 0 means success
 */
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

/**
 * Calculate and output scores for a given hand
 * 
 * @param hand[] Hand of dice values
 * @param diceInPlay Quantity of dice being played with, length of hand[]
 */
void calcAndOutputScores(int hand[], int diceInPlay)
{
    // Hand needs to be sorted to easily check for straights
    sortArray(hand, diceInPlay);
    std::cout << "Here is your sorted hand : ";
    for (int dieNumber = 0; dieNumber < diceInPlay; dieNumber++)
    {
        std::cout << hand[dieNumber] << " ";
    }
    std::cout << std::endl;

    // Upper scorecard
    for (int dieValue = 1; dieValue <= 6; dieValue++)
    {
        int currentCount = 0;
        for (int diePosition = 0; diePosition < 5; diePosition++)
        {
            if (hand[diePosition] == dieValue)
            {
                currentCount++;
            }
        }
        std::cout << " Score " << dieValue * currentCount << " on the ";
        std::cout << dieValue << " line" << std::endl;
    }

    // Lower scorecard
    if (maxOfAKindFound(hand) >= 3)
    {
        std::cout << " Score " << totalAllDice(hand) << " on the ";
        std::cout << "3 of a kind line" << std::endl;
    }
    else std::cout << " Score 0 on the 3 of a kind line" << std::endl;

    if (maxOfAKindFound(hand) >= 4)
    {
        std::cout << " Score " << totalAllDice(hand) << " on the ";
        std::cout << "4 of a kind line" << std::endl;
    }
    else std::cout << " Score 0 on the 4 of a kind line" << std::endl;

    if (fullHouseFound(hand))
        std::cout << " Score 25 on the full house line" << std::endl;
    else
        std::cout << " Score 0 on the full house line" << std::endl;

    if (maxStraightFound(hand) >= 4)
        std::cout << " Score 30 on the small straight line" << std::endl;
    else
        std::cout << " Score 0 on the small straight line" << std::endl;

    if (maxStraightFound(hand) >= 5)
        std::cout << " Score 40 on the large straight line" << std::endl;
    else
        std::cout << " Score 0 on the large straight line" << std::endl;

    if (maxOfAKindFound(hand) >= 5)
        std::cout << " Score 50 on the yahtzee line" << std::endl;
    else
        std::cout << " Score 0 on the yahtzee line" << std::endl;

    std::cout << " Score " << totalAllDice(hand) << " on the ";
    std::cout << "chance line" << std::endl;
}

/**
 * Work with player to calculate their hand of dice
 *  Side effects: changes hand[] values for caller
 * 
 * @param hand[] Array of dice values
 * @param diceInPlay Quantity of dice being played with, length of hand[]
 */
void generateHand(int hand[], int diceInPlay)
{
    std::string keep = "nnnnn"; // Setup to roll all dice in the first roll
    int turn = 1;

    while (turn < 4 && keep != "yyyyy")
    {
        // Roll dice not kept
        for (int dieNumber = 0; dieNumber < diceInPlay; dieNumber++)
        {
            if (keep[dieNumber] != 'y')         // Index string as array
            {
                hand[dieNumber] = rollDie();    // Re-roll that die
            }
        }

        // Output roll
        std::cout << "Your roll was: ";
        for (int dieNumber = 0; dieNumber < diceInPlay; dieNumber++)
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


/**
 * This function simulates the rolling of a single die
 * 
 * @return A single 'random' value in 1..6
 */
int rollDie()
{
    int roll = rand() % 6 + 1;
    return roll;      // 'roll' is superfluous, but compiler will handle that
}


/**
 * This function returns the count of the die value occurring most in the hand
 *  but not the value itself
 * 
 * @param hand[] Array of dice values to check
 * @return Die value occuring most in the hand
 */
int maxOfAKindFound(int hand[])
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


/**
 * This function returns the total value of all dice in a hand
 * 
 * @param hand[] Array of dice values to check
 * @return Total value of the dice
 */
int totalAllDice(int hand[])
{
    int total = 0;
    for (int diePosition = 0; diePosition < 5; diePosition++)
    {
        total += hand[diePosition];
    }
    return total;
}


/**
 * Bubble sort algorithm from Gaddis chapter 8
 *  Includes short circuit pre-sort detection
 *  Side effect: array[] is modified in place
 * 
 * @param array[] Array of integers to sort
 * @param array_size How many elements in array to sort
 */
void sortArray(int array[], int array_size)
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


/**
 * This function returns the length of the longest straight found in a hand
 * 
 * @param hand[] Array of dice values to check
 * @return true of large straight found
 * 
 */
int maxStraightFound(int hand[])
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


/**
 * Determines if the hand of dice contains a full house:
 *  Two of one kind and three of another kind
 * 
 * @param hand[] Array of dice values to check
 * @return true if full house in hand, false otherwise
 */
bool fullHouseFound(int hand[])
{
    bool foundFH = false;
    bool found3K = false;
    bool found2K = false;
    int currentCount;

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
