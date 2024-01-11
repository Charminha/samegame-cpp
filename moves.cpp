//Programmteil für Zugeingabe, Zugbehandlung und Punkteberechnung
#include <vector>
#include <string>
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;


void inputMove (int &row, int &col)
{
    string stringRow;
    string stringCol;
    bool inputValid = true;
    
    cout << "Which square do you want to delete? Enter your move." << endl;
    cout << "Row: ";
    cin >> stringRow;
    cout << "Column: ";
    cin >> stringCol;
      
    if (stringRow.size()!=1 || stringCol.size()!=1) {
        cout<<"Invalid input."<<endl;
        inputValid = false;
        inputMove(row, col);
    }
    
    if (inputValid) {
        row = stringRow[0] - 48;
        col = stringCol[0] - 48;
    }

    if(!(row <= 8 && row >= 0)||!(col <= 8 && col >= 0)){
        cout<<"Invalid input."<<endl;
        inputMove(row, col);

    }
    //row = stringRow[0] - 48;
    //col = stringCol[0] - 48;
}
    
//Funktion überprüft, ob um das angegebene Feld herum ein Feld 
//in der gleichen Farbe und damit eine Gruppe existiert
bool groupExists(vector<vector<char> > &gameboard, int row, int col){
    char currentColor= gameboard[row][col];
    if (currentColor=='s'){
        cout << "You've chosen an empty square."<<endl;
        return false;
    }
    if ((row>0 && currentColor==gameboard[row - 1][col] ) || //darüber
        (row<8 && currentColor==gameboard[row + 1][col]) ||  //darunter
        (col>0 && currentColor==gameboard[row][col-1]) ||  //links daneben
        (col<8 && currentColor==gameboard[row][col+1]) //rechts daneben
        )
        {
            return true;
        }
    else
        return false;

}

//Funktion löscht eine existierenden Farbgruppe rund um das angegebene Feld in der angegebenen Farbe (char color)
//Gibt Anzahl der gelöschten Felder zurück
int removeGroup(vector<vector<char> > &gameboard, int row, int col, char color){
    int count=0;
    gameboard[row][col]='s';
    count++;
    int tmpRow;
    int tmpCol;
    if (row>0 && color==gameboard[row - 1][col]){
        tmpRow=row-1;
        tmpCol=col;
        count+=removeGroup(gameboard, tmpRow, tmpCol, color);
    } 
    if (row<8 && color==gameboard[row + 1][col] ){
        tmpRow=row+1;
        tmpCol=col;
        
        count+=removeGroup(gameboard, tmpRow, tmpCol, color);
    }  
    if (col>0 && color==gameboard[row][col -1] ){
        tmpRow=row;
        tmpCol=col-1;
        count+=removeGroup(gameboard, tmpRow, tmpCol, color);
    } 
    if (col<8 && color==gameboard[row ][col+1] ){
        tmpRow=row;
        tmpCol=col+1;
        count+=removeGroup(gameboard, tmpRow, tmpCol, color);
    }   
    return count;
}

//Funktion füllt leere Felder nach Schwerkraftprinzip
void closeGapHorizontal(vector<vector<char>> &gameboard){
    int tmp;
    for (int col=0; col<9; col++){
        for(int row=8; row>=0; row--){
            tmp=row;
            while (gameboard[row][col]=='s' && tmp>0){
                tmp--;
                gameboard[row][col]=gameboard[tmp][col];
                gameboard[tmp][col]='s';

            }
        } 
    }

}

//Funktion überprüft, ob das Spielfeld noch löschbare Gruppen enthält. Gibt das überprüfte Ergebnis als bool zurück.
bool movesPossible(vector<vector<char>> gameboard){
    for (int rowindex=0; rowindex<9; rowindex++){
        for (int columnindex=0; columnindex<9; columnindex++){
            if ((gameboard[rowindex][columnindex]!='s')&&(
                (rowindex>0 && gameboard[rowindex][columnindex]==gameboard[rowindex - 1][columnindex] ) || 
                (rowindex<8 && gameboard[rowindex][columnindex]==gameboard[rowindex + 1][columnindex]) ||
                (columnindex>0 && gameboard[rowindex][columnindex]==gameboard[rowindex][columnindex-1]) ||
                (columnindex<8 && gameboard[rowindex][columnindex]==gameboard[rowindex ][columnindex+1])
            )){
                return true;
            }
            
        }
    }
    return false;
}

//Funktion ermittelt aufgrund der gelöschten Blöcke (int deletedSquares) die in diesem Zug gewonnenen Punkte
int computeScore(int deletedSquares){
    return deletedSquares*(deletedSquares-1);
}


//Funktion verschiebt das Spielfeld bei einer leeren Spalte nach links
void closeGapVertical(vector<vector<char>> &gameboard){
    for (int i=0; i<9; i++){
        if (gameboard[8][i]=='s'){
            int tmpcol=i;
            
            int neighbor=i+1;
            while(gameboard[8][neighbor]=='s'&&neighbor<9){
                neighbor+=1;
            }
            for (tmpcol;tmpcol<9;tmpcol++){
                for (int rowi=0;rowi<9;rowi++){
                    if (neighbor<9){
                        gameboard[rowi][tmpcol]=gameboard[rowi][neighbor];
                        }else{
                            gameboard[rowi][tmpcol]='s';
                    }
                
                }
                neighbor++;
            
            }
        }
    }
}
