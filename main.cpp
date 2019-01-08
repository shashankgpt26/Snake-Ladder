#include<iostream>
#include<vector>
#include<utility>
#include<algorithm>
using namespace std;

// Class for Board.

class Board 
{
    int boardSize; // Square Board Dimension.

    int *ludo; // List for maintaining the board postion with snakes/ladders.

public:

    Board(int boardSize); // Board Constructor.

    void addSnake(int head,int tail); // Function to add snakes on the board.

    void addLadder(int head, int Tail); // Function to add ladders on the board.

    int checkSnakeLadder(int val); // Function to check for (snake head) / (ladder tail) on the board.
};

Board::Board(int boardSize) 
{
    this->boardSize = boardSize;
    ludo = new int[boardSize*boardSize + 1];
    for(int i=0; i <= (boardSize*boardSize); i++)
        ludo[i] = 0; // initializing the default board condition (with 0).
}


void Board::addSnake(int head,int tail)
{
    ludo[head] = -tail; // maintaining negative value for snake(where it takes).
}

void Board::addLadder(int head,int tail)
{
    ludo[tail] = head; // maintaining positive value for ladder(where it takes).
}

int Board::checkSnakeLadder(int val)
{
    return ludo[val]; // checking the current position (snake head) / (ladder tail).
}

// Class for Players.

class Player
{
    int numOfPlayers; // number of Players playing the game.
    int *playerList; // list for maintaing the current position of the players.

public:
    Player(int numOfPlayers); //  Player Constructor.

    void updateList(int playerNumber, int position); // update the list with players cuurent position.

    int currentPosition(int playerNumber); // check current position of the players.
};

Player::Player(int numOfPlayers)
{
    this->numOfPlayers = numOfPlayers;
    playerList = new int[numOfPlayers+1];
    for(int i=0; i<=numOfPlayers; i++)
        playerList[i] = 0; // initializing the default player position.
}

void Player::updateList(int playerNumber, int position)
{
    playerList[playerNumber] = position; // updating the position for the player.
}

int Player::currentPosition(int playerNumber)
{
    return playerList[playerNumber]; // fetching the current position of the player.
}

int main()
{
    Board snakeLadder(10); //10x10 board with 100 numbers
    cout << "Please enter num of Players : ";
    int N;
    cin >> N;
    Player member(N);
    snakeLadder.addLadder(25,5);
    snakeLadder.addLadder(29,10);
    snakeLadder.addLadder(41,22);
    snakeLadder.addLadder(55,28);
    snakeLadder.addLadder(95,44);
    snakeLadder.addLadder(89,70);
    snakeLadder.addLadder(79,81);

    snakeLadder.addSnake(31,14);
    snakeLadder.addSnake(37,17);
    snakeLadder.addSnake(73,53);
    snakeLadder.addSnake(78,39);
    snakeLadder.addSnake(92,35);
    snakeLadder.addSnake(99,7);

    cout << "Start the initial Move ..\n";
    vector< pair<int,int> > intialMove;
    int value,ret1,ret2;
    for(int i=0;i<N;i++)
    {
        cin >> value;
        intialMove.push_back(make_pair(value,i+1));
    }
    sort(intialMove.rbegin(),intialMove.rend());
    char ch = 'A';
    while(1)
    {
        cout << "Next turn starts ...\n";
        for(int i=0; i < N; i++)
        {
            cin >> value;
            ret1 = member.currentPosition(intialMove[i].second);
            if(ret1 == 100) //reached 100 then stop.
                continue;
            ret2 = snakeLadder.checkSnakeLadder(value+ret1);
            if(ret2 == 0)
                member.updateList(intialMove[i].second,value+ret1);
            else
                member.updateList(intialMove[i].second,abs(ret2));
        }
        cout << "Press(Y/y) to stop playing or any key to continue : ";
        cin >> ch;
        if(ch == 'Y' || ch == 'y')
            break;
    }

    cout << "The positions after the sequence of rolls above :\n";
    for(int i = 0; i < N; i++)
    {
        cout << "Player " << i+1 << " - " << member.currentPosition(i+1) << "\n";
    }

    return 0;
}
