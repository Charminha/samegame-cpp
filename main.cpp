// gameboard 9 x 9
// 5 verschiedene Farben
// Das Entfernen einer Gruppe von n Steinen wird mit n · (n − 1) Punkten
// bewertet.
// Wird eine ganze Spalte geleert, so rutschen die Nachbarspalten ebenfalls zusammen. Das Spiel
// endet, wenn kein weiterer Zug möglich ist.

#include <iostream>
#include <string>
#include <vector>
#include "showGame.cpp"
#include "moves.cpp"
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;

//eigentliches Spiel
void sameGame(){
    int currRow;
    int currCol;
    int row = -1;
    int col = -1;
    vector<vector<char> > gameboard(9,vector<char>(9));
    
    int myscore=0;
    fillGameboard(gameboard);
    printGameboardColored(gameboard);
    
    while (movesPossible(gameboard)){

        
        inputMove(row, col);
        currRow = row;
        cout << "currRow " << currRow << endl;
        currCol = col; 
        cout << "currCol " << currCol << endl;
        cout << "col " << col << endl;
        cout << "row " << row << endl;

        if (groupExists(gameboard, row, col))
        {
            int removedSquares=removeGroup(gameboard, row, col, gameboard[currRow][currCol]);
            printGameboardColored(gameboard);
            closeGapHorizontal(gameboard);
            printGameboardColored(gameboard);
            closeGapVertical(gameboard);
            printGameboardColored(gameboard);
            myscore+=computeScore(removedSquares);
            printGameboardColored(gameboard, myscore);
            
        }
        else
            cout << "That's not a valid group."<<endl;
        
        
    }
    cout << "Game finished. Final score: " << myscore << endl;

}


    
int main(){
char tryAgain='y';
while (tryAgain=='y'){
    sameGame();
    cout<<"Would you like to play again? (y/n)"<<endl;
    cin>>tryAgain;
}   
return 0;
}







