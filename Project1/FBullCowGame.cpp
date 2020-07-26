#include "FBullCowGame.h"
#include <map>
#define Tmap std::map

using int32 = int;
using FString = std::string;

FBullCowGame::FBullCowGame()
{
    Reset();
}

int32 FBullCowGame::GetCurrentTry() const
{
    return myCurrentTry;
}

int32 FBullCowGame::GetMaxTries() const
{
    return myHiddenWord.length() * 2;

}

int32 FBullCowGame::GetHiddenWordLength() const
{
    return myHiddenWord.length();
}

bool FBullCowGame::IsGameWon() const
{
    return bGameIsWon;
}

void FBullCowGame::Reset()
{
    const FString HIDDEN_WORD = "pla";
    myHiddenWord = HIDDEN_WORD;

    myCurrentTry = 1;
    bGameIsWon = false;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString guess) const
{
    if (!IsIsogram(guess))
    {
        return EGuessStatus::Not_Isogram;
    }
    else if (!IsLowerCase(guess))
    {
        return EGuessStatus::Not_Lowercase;
    }
    else if (guess.length() != GetHiddenWordLength())
    {
        return EGuessStatus::Wrong_Length;
    }
    else
    {
        return EGuessStatus::OK;
    }
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString guess)
{
    myCurrentTry++;

    FBullCowCount BullCowCount;
    int32 WordLength = myHiddenWord.length();

    for (int32 HDi = 0; HDi < WordLength; ++HDi)
    {
        for (int32 GWi = 0; GWi < WordLength; ++GWi)
        {
            if (guess[GWi]==myHiddenWord[HDi])
            {
                if (HDi == GWi)
                {
                    BullCowCount.bulls++;
                }
                else
                {
                    BullCowCount.cows++;
                }
            }
        }
    }

    if (BullCowCount.bulls == WordLength)
    {
        bGameIsWon = true;
    }
    else
    {
        bGameIsWon = false;
    }

    return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString guess) const
{
    if (guess.length() <= 1)
    {
        return true;
    }

    Tmap<char, bool> LetterSeen;

    for (auto letter : guess)
    {
        letter = tolower(letter);

        if (!LetterSeen[letter])
        {
            LetterSeen[letter] = true;
        }
        else
        {
            return false;
        }
    }

    return true;
}

bool FBullCowGame::IsLowerCase(FString guess) const
{
    if (guess.length() < 1)
    {
        return true;
    }

    for (auto letter : guess)
    {
        if (!islower(letter))
        {
            return false;
        }
    }

    return true;
}
