/*
 *  1 2 3 4
 *  2 3 4 5
 *  3 4 5 6
 *  4 5 6 7
 */

#define ROW  4
#define COL  4

bool YangMatrix(int array[][COL], int searchKey){
    int i = 0;
    int j = COL - 1;
    int var = array[i][j];
    while(true){
        if(var == searchKey)
            return true;
        else if(var < searchKey && i < ROW-1)
            var = array[++i][j];
        else if(var > searchKey && j > 0)
            var = array[i][--j];
        else
            return false;
    }
}
