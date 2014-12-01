#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <iterator>
#include <numeric>
using namespace std;

#define SIZE 3


typedef vector< tuple<int, int> > moveList;
typedef vector< vector<int> > field;

class Board
{
    public:
        field* boardArr;
        Board(vector< vector<int> >*);
        moveList getMoves() const;
        bool won(int);
        void prettyPrint() const;
};

Board::Board(field* arr)
{
    boardArr = arr;
}

moveList Board::getMoves() const
{
    moveList moves;
    int x=0, y=0;
    //vector<int> moves;
    for(int y = 0; y < SIZE; y++)
    {
        for(int x = 0; x < SIZE; x++)
        {
            if((*boardArr)[y][x] == 0)
            {
                moves.push_back(tuple<int, int>(x, y));
                //moves.push_back(x);
            }
        }
    }

    return moves;
}

bool isvalueinarray(int val, int *arr, int size){
    int i;
    for (i=0; i < size; i++) {
        if (arr[i] == val)
            return true;
    }
    return false;
}

bool Board::won(int letter)
{
    //vector<int> rows(SIZE, 0);
    int rows[SIZE] = {0};
    //vector<int> cols(SIZE, 0);
    int cols[SIZE] = {0};
    //vector<int> diags(2, 0);
    int diags[2] = {0};

    for(int y = 0; y < SIZE; y++)
    {
        for(int x = 0; x < SIZE; x++)
        {
            if((*boardArr)[y][x] == letter)
            {
                rows[y] += 1;
                cols[x] += 1;

                if(x == y)
                {
                    diags[0] += 1;
                }

                if(x+y == SIZE-1)
                {
                    diags[1] += 1;
                }
            }
        }
    }
    //bool rows_good = find(rows.begin(), rows.end(), SIZE) != rows.end();
    bool rows_good = isvalueinarray(SIZE, rows, SIZE);
    //bool cols_good = find(cols.begin(), cols.end(), SIZE) != cols.end();
    bool cols_good = isvalueinarray(SIZE, cols, SIZE);
    //bool diags_good = find(diags.begin(), diags.end(), SIZE) != diags.end();
    bool diags_good = isvalueinarray(SIZE, diags, 2);

    return (rows_good || cols_good || diags_good);
}

void Board::prettyPrint() const
{
    char trans[] = {' ', 'X', 'O'};
    bool first = true;
    for(int i = 0; i < boardArr->size(); i++)
    {
        if(!first)
        {
            for(int j = 0; j < SIZE * 2 - 1; j++)
            {
                cout << "-";
            }
            cout << endl;
        }

        first = false;

        bool innerFirst = true;
        for(int j = 0; j < (*boardArr)[i].size(); j++)
        {
            if(!innerFirst)
            {
                cout << "|";
            }
            innerFirst = false;
            cout << trans[(*boardArr)[i][j]];
        }

        cout << endl;
    }
}

vector<int> minimax(const Board& board, int letter)
{
    moveList moves = board.getMoves();
    field arr = *board.boardArr;
    vector<int> scores = vector<int>(moves.size(), 0);
    //cout << moves.size() << endl;
    /*for(int i = 0; i < moves.size(); i++)
    {
        cout << get<0>(moves[i]) << " " << get<1>(moves[i]) << endl;
    }*/

    for(int i = 0; i < moves.size(); i++)
    {
        //arr2 = arr;
        field arr2 = arr;

        int y = get<1>(moves[i]);
        int x = get<0>(moves[i]);
        arr2[y][x] = letter;

        Board board2(&arr2);
        if(board2.won(letter))
        {
            scores[i] = 10;
        }
        else
        {
            int letter2;
            if(letter == 1)
            {
                letter2 = 2;
            }
            else
            {
                letter2 = 1;
            }

            vector<int> scores2 = vector<int>(moves.size(), 0);
            moveList moves2 = board2.getMoves();
            //cout << moves2.size() << endl;
            for(int j = 0; j < moves2.size(); j++)
            {
                field arr3 = arr2;
                int y2 = get<1>(moves2[j]);
                int x2 = get<0>(moves2[j]);
                arr3[y2][x2] = letter2;

                Board board3(&arr3);
                if(board3.won(letter2))
                {
                    scores2[j] = -10;
                }
                else
                {
                    vector<int> run = minimax(board3, letter);
                    scores2[j] = accumulate(run.begin(), run.end(), 0);
                }
            }

            scores[i] = accumulate(scores2.begin(), scores2.end(), 0);
        }
    }

    return scores;
}

field playerTurn(const Board& board)
{
    vector<int> scores = minimax(board, 1);

    moveList moves = board.getMoves();

    int ind = distance(scores.begin(), max_element(scores.begin(), scores.end()));
    //cout << ind << endl;

    tuple<int, int> move = moves[ind];
    //cout << get<0>(move) << endl;

    int x = get<0>(move);
    int y = get<1>(move);

    field arr = *board.boardArr;
    field arr2 = arr;
    arr2[y][x] = 1;

    //Board board2(&arr2);
    //Board board2 (&arr2);


    return arr2;
}

field userTurn(const Board& board)
{
    bool accept = false;
    int x_coord, y_coord;

    while(!accept)
    {

        cout << "Enter your desired x-coord: ";
        cin >> x_coord;

        cout << "Enter your desired y-coord: ";
        cin >> y_coord;

        if(x_coord >= 1 && x_coord <= SIZE && y_coord >= 1
           && y_coord <= SIZE && (*board.boardArr)[y_coord-1][x_coord-1] == 0)
            accept = true;
    }

    field arr = *board.boardArr;
    field arr2 = arr;
    arr2[y_coord-1][x_coord-1] = 2;

    return arr2;
}

bool zerosExist(field arr)
{
    for (field::iterator it = arr.begin(); it != arr.end(); it++)
    {
        if (find(it->begin(), it->end(), 0) != it->end())
        {
            return true;
        }
    }

    return false;
}


int main(void)
{
    //int arr[] = {0, 0, 0};
    //field arr {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    vector<std::vector<int>> arr(SIZE, vector<int>(SIZE));
    //int arr[SIZE][SIZE] = {{0}};
    Board board (&arr);
    //board.prettyPrint();
    /*field arr2 = playerTurn(board);
    Board board2(&arr2);
    board2.prettyPrint();*/
    //cout << board.getMoves() << endl;
    field arr2, arr3;
    while(!board.won(1) && !board.won(2) && zerosExist(*board.boardArr))
    {
        //field arr2, arr3;
        arr2 = playerTurn(board);
        //board.boardArr = &arr2;
        board = Board(&arr2);
        board.prettyPrint();

        if(board.won(1) || board.won(2) || !zerosExist(*board.boardArr))
        {
            break;
        }

        arr3 = userTurn(board);
        //board.boardArr = &arr3;
        board = Board(&arr3);
        //board.prettyPrint();
    }

    if(board.won(1))
    {
        cout << "Ooh, you lost! That blows!" << endl;
    }
    else if (board.won(2))
    {
        cout << "Hey, you won! Awesome!" << endl;
    }
    else
    {
        cout << "It was a tie? I have... strongly mixed feelings." << endl;
    }
    //board.prettyPrint();
    return 0;
}