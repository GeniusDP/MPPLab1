#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility>

using namespace std;

/*
    Task 2
*/


/*
    This is lab work 1
    on MPP
    Author: B. Zaranik

    stop-words list:
    (prepositions)
    --------------
    the
    for
    in
    on
    a
    an
    of
    to
    at
    by
    onto
    into

    are
    but
    is
    and
    not
    or
    --------------
    (is hardcoded)
*/

struct WordProcessor{
    string word;
    int pages[101];
    int currentNumberOfPages = 0;
};

int main()
{
    string stopWords[] =
        {"the", "for", "in", "on", "a",
         "an", "of", "to", "at", "by",
         "onto", "into", "are", "but", "is",
         "and", "not", "or"
        };
    ifstream in("input.txt");
    const int PAGE_SIZE_IN_ROWS = 5;


    int allWordsCapacity = 100;
    int allWordsLength = 0;
    WordProcessor* allWords = new WordProcessor[allWordsCapacity];

    string currentLine;
    while( in.peek() != EOF ){
        int cnt = 0;
        while( ++cnt <= PAGE_SIZE_IN_ROWS && in.peek() != EOF ){
            getline(in, currentLine);
            //cout << currentLine << endl;

            /*
                split
            */

            int left, right;
            left = right = 0;
            while( currentLine[left] != '\0' ){
                if( currentLine[left] != ' ' ){
                    right = left;
                    while( currentLine[right] != ' ' && currentLine[right] != '\0' ){
                        right++;
                    }
                    string currentWord = "";
                    int currentWordSize = right-left;
                    while( left < right ){
                        currentWord += currentLine[left];
                        left++;
                    }
                    if( currentWord[currentWordSize-1] == '.' || currentWord[currentWordSize-1] == ','
                       || currentWord[currentWordSize-1] == '!' || currentWord[currentWordSize-1] == '?'
                       || currentWord[currentWordSize-1] == ':' || currentWord[currentWordSize-1] == ';'){
                        //so that is why we`re deleting last character
                        string tmp = "";
                        for(int i = 0; i < currentWordSize-1; i++){
                            tmp += currentWord[i];
                        }
                        currentWord = tmp;
                    }
                    cout << currentWord << "|";
                }else{
                    left++;
                }
            }




        }
    }

    /*
        sorting
    */


    in.close();
    return 0;
}
