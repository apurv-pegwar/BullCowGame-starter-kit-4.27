// Fill out your copyright notice in the Description page of Project Settings.
#include <BullCowCartridge.h>
#include "HiddenWordList.h"
void UBullCowCartridge::BeginPlay() // When the game starts
//
{
    Super::BeginPlay();

    SetupGame(); // bgameover variable= false
    PrintLine(TEXT(" the total number of words are %i."),Words.Num()); // debug line 
    PrintLine(TEXT("the total number of valid words are %i."),GetValidWords(Words).Num()); 
}   

void UBullCowCartridge::OnInput(const FString& Input)
 {
        if (bGameOver==true)
    { 
            ClearScreen();
            SetupGame();
    }
        else //checking player guess]
        {
            ProcessGuess(Input);   
        }       
 }      
        //remove life 
        // check life >0    
        // if yes then playAgain  

void UBullCowCartridge::SetupGame()
    {
        HiddenWord = TEXT("CAKE"); //WE Have TO SET HiddenWord
        Lives=HiddenWord.Len();
        bGameOver= false;
        PrintLine(TEXT(" Welcome to Cow Game"));
        PrintLine(TEXT("Guess the %i word.."), HiddenWord.Len()) ;  
        PrintLine(TEXT("press tab to write then press return"));
        PrintLine(TEXT("LIVES Have = %i") , Lives);
        
        
        
        // enter lives 
        // enter hint after wrong answer 
        //promte for guess
    }
void UBullCowCartridge:: EndGame()
    {
        bGameOver =true;
        PrintLine(TEXT("YOU LOST"));
        PrintLine(TEXT("\nPress enter to play again."));

    }
void UBullCowCartridge:: ProcessGuess(const FString& Guess)
{

    //check for right no. of characters 
    
    // remove life 
      if (Guess.Len()!=HiddenWord.Len())
            {
            --Lives;
             PrintLine(TEXT("Sorry, Try guessing Again,\n"));//MAGIC NUMBER
             PrintLine(TEXT("Now you have %i Lives"), Lives);
             if (Lives<=0)
        {
            EndGame();
        }
             return;
            }
        if(Guess==HiddenWord)
    {
        PrintLine("you win!!");
        PrintLine("Press return to continue");
        EndGame();
        return;
    }
          // check for isogram 
      if(!IsIsogram(Guess))
      { --Lives;
        PrintLine(TEXT("Now you have %i Lives"), Lives);
        PrintLine(TEXT("No repeating Words,try again"));
        if (Lives<=0)
        {
            EndGame();
        }
        return;
      }
 
    
         if (Lives<=0)
        {
        ClearScreen();
        PrintLine(TEXT("You Have no lives left\n"));
        PrintLine(TEXT("Hidden word was %s"), *HiddenWord);
         return;
        }
    
}
 
bool UBullCowCartridge::IsIsogram(FString Word) const
 {

        for (int32 Index =0; Index< Word.Len(); Index++) // no lives removed now , we have to change this 
     {
         
         for (int32 Comparison= Index +1 ; Comparison <Word.Len(); Comparison++)
         {
               if (Word[Index]==Word[Comparison])
               {
                return false;
               }
         }
     }
         return true;
 } 
TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{   
    TArray<FString> ValidWords;
    for (FString Cword : WordList)
    { 
        if (Cword.Len()>=4 && Cword.Len()<=8 && IsIsogram(Cword))
        {
        ValidWords.Emplace(Cword);
        }  
    }
    return ValidWords;
}
