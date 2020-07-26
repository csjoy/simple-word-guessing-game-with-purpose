#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;


void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool PlayAgain();
void PrintGameSummary();

FBullCowGame BCGame;

int main()
{
    bool reply = false;

    do {
        PrintIntro();
        PlayGame();
        reply = PlayAgain();

        if (reply) {
            system("CLS");
        }
    } while (reply);

    return 0;
}

void PrintIntro()
{
    std::cout << "                                                  " << std::endl;
    std::cout << "               }   {         ___                  " << std::endl;
    std::cout << "               (o o)        (o o)                 " << std::endl;
    std::cout << "    /-------^-- \\ /          \\ /----^-------\\  " << std::endl;
    std::cout << "   / |  BULL   | o            o |   COW    | \\   " << std::endl;
    std::cout << "  *  |-,-------|                |----------|  *   " << std::endl;
    std::cout << "     ^         ^                ^          ^      " << std::endl;
    std::cout << "                                                  " << std::endl;
    std::cout << "WELCOME TO BULLS AND COWS, A FUN WORD GAME.\n";
    std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n";
    std::cout << std::endl;
}

FText GetValidGuess()
{
    EGuessStatus status = EGuessStatus::Invalid_status;
    FText result = "";

    do
    {
        int32 currentTries = BCGame.GetCurrentTry();
        FText guess = "";

        std::cout << "Try " << currentTries << " of " << BCGame.GetMaxTries() << " Enter your guess: ";
        std::getline(std::cin, guess);

        status = BCGame.CheckGuessValidity(guess);

        switch (status)
        {
        case EGuessStatus::OK:
            return guess;
            break;
        case EGuessStatus::Not_Isogram:
            std::cout << "Please enter a word without repeating letters\n\n";
            break;
        case EGuessStatus::Wrong_Length:
            std::cout << "Please enter a " << BCGame.GetHiddenWordLength();
            std::cout << " letter word.\n" << std::endl;
            break;
        case EGuessStatus::Not_Lowercase:
            std::cout << "Please enter all lowercase letters.\n\n";
            break;
        }

        result = guess;
    } while (status != EGuessStatus::OK);
    
    return result;
}

void PrintGameSummary()
{
    if (BCGame.IsGameWon())
    {
        std::cout << "WELL DONE! - YOU WIN!\n";
    }
    else
    {
        std::cout << "Better luck next time!\n";
    }
}

void PlayGame()
{
    BCGame.Reset();
    int32 maxTries = BCGame.GetMaxTries();

    while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= maxTries)
    {
        FText guess = GetValidGuess();

        FBullCowCount BullCowCount = BCGame.SubmitValidGuess(guess);
        std::cout << "Bulls = " << BullCowCount.bulls;
        std::cout << ". Cows = " << BullCowCount.cows << "\n\n";
    }

    PrintGameSummary();
}

bool PlayAgain()
{
    std::cout << "Do you want to play again with the same hidden word (y/n)? ";
    FText response;
    std::getline(std::cin, response);

    bool answer = response[0] == 'y' || response[0] == 'Y';

    return answer;
}