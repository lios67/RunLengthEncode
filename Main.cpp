#include <iostream>
#include <fstream>
using namespace std;

class runLength{
    public:
    int numRows, numCols, minVal, maxVal, whichMethod;
    string nameEncodeFile;
    runLength(int x, int y, int z, int s){
        numRows=x;
        numCols=y;
        minVal=z;
        maxVal=s;
    }
    void encodeMethod1(ifstream &inFile, ofstream& encodeFile){
        int row=0;
        while(row<numRows){
            int col=0;
            int length=1;
            int curVal;
            inFile >> curVal;
            encodeFile << row << " " << col << " " << curVal << " ";
            while(col<=(numCols-2)){
                col++;
                int nextVal;
                inFile >> nextVal;
                if(nextVal==curVal){
                    length++;
                }else{
                    encodeFile << length << endl;
                    curVal=nextVal;
                    length=1;
                    encodeFile << row << " " << col << " " << curVal << " ";
                }
            }
            encodeFile << length << endl;
            row++;
        }
    }
    void encodeMethod4(ifstream &inFile, ofstream& encodeFile){
        int row=0;
        int col=-1;
        int length=1;
        int zeroCnt=0;
        int lastVal=skipZeros(inFile, row, col, zeroCnt);
        encodeFile << row << " " << col << " " << lastVal << " ";
        while(!inFile.eof()){
            int nextVal=skipZeros(inFile, row, col, zeroCnt);
            if(zeroCnt>0){
                lastVal=0;
            }
            if(lastVal==nextVal){
                length++;
            }else{
                encodeFile << length << endl;
                lastVal=nextVal;
                length=1;
                if(row==(numRows-1) && col==(numCols-1)){
                  return;
                }
                encodeFile << row << " " << col << " " << lastVal << " ";
            }
        }
    }
    int skipZeros (ifstream &inFile, int &row, int &col, int &zeroCnt){
        int val;
        col++;
        inFile >> val;
        zeroCnt=0;
        while(val==0){
            col++;
            zeroCnt++;
            inFile >> val;
            if(row==(numRows-1) && col==(numCols-1)){
              return 1;
            }
            if(col>=(numCols-1)){
                col=-1;
                row++;
            }
        }
        if(col>=(numCols-1)){
            col=-1;
            row++;
        }
        return val;
    }
};
 
int main(int argc,char* argv[]) {
	ifstream inFile(argv[1]); 
    string name=argv[1], whichMethod=argv[2];
    char *m=argv[2];
    string nameEncodeFile=name.erase(6,4) + "_EncodeMethod" + whichMethod;
	ofstream encodeFile(nameEncodeFile);
    int  numRows, numCols, minVal, maxVal;
    inFile >> numRows >> numCols >> minVal >> maxVal;
    encodeFile << numRows << " " << numCols << " " << minVal << " " << maxVal << endl;
    encodeFile << whichMethod << endl;
    runLength run(numRows, numCols, minVal, maxVal);
    switch (*m){
    case '1':
        run.encodeMethod1 (inFile, encodeFile);
        break;
    case '4':
        run.encodeMethod4 (inFile, encodeFile);
        break;
    default:
        cout << "Error" << endl;
        break;
    }
    inFile.close();
	encodeFile.close();
}