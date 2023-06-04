// ########################## Project 1 ########################## //
//______________________ Stone-Paper-Scissor ______________________//

#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
using namespace std;

enum enGameChoice
{
    Stone = 1,
    Paper = 2,
    Scissors = 3,
};

enum enWinner
{
    Player = 1,
    Computer = 2,
    Draw = 3
};

struct stRoundInfo
{
    short RoundNumber = 0;
    enGameChoice PlayerChoice;
    enGameChoice ComputerChoice;
    enWinner Winner;
    string WinnerName;
};

struct stGameResults
{
    short GameRounds = 0;
    short PlayerWinTimes = 0;
    short ComputerWinTimes = 0;
    short DrawTimes = 0;
    enWinner GameWinner;
    string WinnerName = "";
};

int RandomNumber(int From, int To)
{
    // Function to generate a random number
    int randNum = rand() % (To - From + 1) + From;
    return randNum;
}

enWinner WhoWonTheGame(short PlayerWinTimes, short ComputerWinTimes)
{
    if (PlayerWinTimes > ComputerWinTimes)
        return enWinner::Player;
    else if (ComputerWinTimes > PlayerWinTimes)
        return enWinner::Computer;
    else
        return enWinner::Draw;
}

string WinnerName(enWinner Winner)
{
    string arrWinnerName[3] = {"Player", "Computer", "No Winner"};
    return arrWinnerName[Winner - 1];
}

string ChoiceName(enGameChoice Choice)
{
    string arrChoiceName[3] = {"Stone", "Paper", "Scissors"};
    return arrChoiceName[Choice - 1];
}

void SetWinnerScreenColor(enWinner Winner)
{
    switch (Winner)
    {
    case enWinner::Player:
        system("color 2F"); // Turn Screen to Green
        break;
    case enWinner::Computer:
        system("color 4F"); // Turn Screen to Rad
        cout << "\a";
        break;
    default:
        system("color 6F"); // Turn Screen to Yellow
        break;
    }
}

stGameResults FillGameResults(int GameRounds, short PlayerWinTimes, short ComputerWinTimes, short DrawTimes)
{
    stGameResults GameResults;

    GameResults.GameRounds = GameRounds;
    GameResults.PlayerWinTimes = PlayerWinTimes;
    GameResults.ComputerWinTimes = ComputerWinTimes;
    GameResults.DrawTimes = DrawTimes;
    GameResults.GameWinner = WhoWonTheGame(PlayerWinTimes, ComputerWinTimes);
    GameResults.WinnerName = WinnerName(GameResults.GameWinner);

    return GameResults;
}

void PrintRoundResults(stRoundInfo RoundInfo)
{
    cout << "\n___________Round [" << RoundInfo.RoundNumber << "]___________\n";
    cout << "Plauer Choice   : " << ChoiceName(RoundInfo.PlayerChoice) << endl;
    cout << "Computer Choice : " << ChoiceName(RoundInfo.ComputerChoice) << endl;
    cout << "Round Winner    : [" << RoundInfo.WinnerName << "]\n";
    cout << "_______________________________\n";

    SetWinnerScreenColor(RoundInfo.Winner);
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
    if (RoundInfo.PlayerChoice == RoundInfo.ComputerChoice)
    {
        return enWinner::Draw;
    }

    switch (RoundInfo.PlayerChoice)
    {
    case enGameChoice::Stone:
        if (RoundInfo.ComputerChoice == enGameChoice::Paper)
        {
            return enWinner::Computer;
        }
        break;

    case enGameChoice::Paper:
        if (RoundInfo.ComputerChoice == enGameChoice::Scissors)
        {
            return enWinner::Computer;
        }
        break;

    case enGameChoice::Scissors:
        if (RoundInfo.ComputerChoice == enGameChoice::Stone)
        {
            return enWinner::Computer;
        }
        break;
    }

    // if you reach here then player is the winner.
    return enWinner::Player;
}

enGameChoice ReadPalyerChoice()
{
    short Choice = 1;
    do
    {
        cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissors ? ";
        cin >> Choice;
    } while (Choice < 1 || Choice > 3);

    return (enGameChoice)Choice;
}

enGameChoice GetComputerChoice()
{
    return (enGameChoice)RandomNumber(1, 3);
}

string Tabs(short NumberOfTabs)
{
    string t = "";
    for (int i = 1; i < NumberOfTabs; i++)
    {
        t = t + "\t";
        cout << t;
    }
    return t;
}

void ShowFinalGameResults(stGameResults GameResults)
{
    cout << Tabs(2) << "_________________[Game Results]_________________\n";
    cout << Tabs(2) << "Game Rounds         : " << GameResults.GameRounds << endl;
    cout << Tabs(2) << "Palyer won times    : " << GameResults.PlayerWinTimes << endl;
    cout << Tabs(2) << "Computer won times  : " << GameResults.ComputerWinTimes << endl;
    cout << Tabs(2) << "Draw times          : " << GameResults.DrawTimes << endl;
    cout << Tabs(2) << "Final Winner        : " << GameResults.WinnerName << endl;
    cout << Tabs(2) << "________________________________________________\n";

    SetWinnerScreenColor(GameResults.GameWinner);
}

void ShowGameOverScreen()
{
    cout << Tabs(2) << "________________________________________________\n\n";
    cout << Tabs(2) << "         +++ G a m e  O v e r +++\n";
    cout << Tabs(2) << "________________________________________________\n\n";
}

short ReadHowManyRounds()
{
    short Rounds;
    cout << "How Many Rounds 1 to 10 ? ";
    cin >> Rounds;
    return Rounds;
}

stGameResults PalyGame(short HowManyRounds)
{
    stRoundInfo RoundInfo;
    short PlayerWinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

    for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
    {
        cout << "\nRound [" << GameRound << "] begins:\n";
        RoundInfo.RoundNumber = GameRound;
        RoundInfo.PlayerChoice = ReadPalyerChoice();
        RoundInfo.ComputerChoice = GetComputerChoice();
        RoundInfo.Winner = WhoWonTheRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

        // Increase win/Draw counters
        if (RoundInfo.Winner == enWinner::Player)
            PlayerWinTimes++;
        else if (RoundInfo.Winner == enWinner::Computer)
            ComputerWinTimes++;
        else
            DrawTimes++;

        PrintRoundResults(RoundInfo);
    }
    return FillGameResults(HowManyRounds, PlayerWinTimes, ComputerWinTimes, DrawTimes);
}

void ResetScreen()
{
    system("cls");
    system("color 0F");
}

void StartGame()
{
    char PlayAgain = 'Y';

    do
    {
        ResetScreen();
        stGameResults GameResults = PalyGame(ReadHowManyRounds());
        ShowGameOverScreen();
        ShowFinalGameResults(GameResults);

        cout << endl << Tabs(2) << "Do you want to play again Y/N ? ";
        cin >> PlayAgain;

    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
    srand((unsigned)time(NULL)); // Seeds the random number generator in C++, called only once

    StartGame();

    return 0;
}