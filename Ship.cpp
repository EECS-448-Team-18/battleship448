#include "ship.cpp"

using namespace std;

Ship::Ship(int size, char orientation, int startRow, int endRow, char startCol, char endCol, int *row, char *col) {
    size = this->size;
    orientation = this->orientation;
    startRow = this->startRow;
    endRow = this->endRow;
    startCol = this->startCol;
    endCol = this->endCol;

    row = new int[size];
    col = new char[size];
    if(orientation == 'horizontal') {
        for(int i=0; i<size; i++){
            row[i]=startRow;
            for(char j='startCol'; j<'endCol'; j++){
                col[i]=j;
            }
        }
        
    }
    else if (orientation == 'vertical'){
        for(int i=0; i<size; i++){
            row[i]=startRow+i;
           for(char j='startCol'; j<'endCol'; j++){
                col[i]=startCol;
            } 
        }
    }
    else {
        return ;
    }
}

Ship::~Ship() {
    delete[] row;
    delete[] col;
}

int Ship::getSize() {
    return size;
}

char Ship::getOrientation() {
    return orientation;
}

void Ship::fireSpace(int rowPosition, char colPosition) {  
    for(int i=0; i<size; i++) {
        if(rowPosition==row[i] && colPosition==col[i]) {
            row[i]=0;
            col[i]='O';
            size--;
        }
    }
}

bool isSunk(int size) {
    return size==0;
}
