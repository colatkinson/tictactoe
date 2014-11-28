#include <iostream>
#include <vector>
using namespace std;

class Board
{
    public:
        vector< vector<int> >* boardArr;
        Board(vector< vector<int> >*);
        //int* getMoves();
        //bool won(int letter);
        void prettyPrint();
};

Board::Board(vector< vector<int> >* arr)
{
    boardArr = arr;
}

void Board::prettyPrint()
{
    char trans[] = {' ', 'X', 'O'};
    bool first = true;
    for(int i = 0; i < boardArr->size(); i++)
    {
        if(!first)
        {
            cout << "-----" << endl;
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



int main(void)
{
    //int arr[] = {0, 0, 0};
    vector< vector<int> > arr {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    Board board (&arr);
    board.prettyPrint();
    return 0;
}