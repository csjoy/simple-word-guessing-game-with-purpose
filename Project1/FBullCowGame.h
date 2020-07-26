#pragma once
#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 bulls = 0;
	int32 cows = 0;
};

enum class EGuessStatus
{
	Invalid_status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase,
};

class FBullCowGame
{
public:
	FBullCowGame();

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString guess) const;

	void Reset();
	FBullCowCount SubmitValidGuess(FString guess);

private:
	int32 myCurrentTry;
	FString myHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString guess) const;
	bool IsLowerCase(FString guess) const;
};