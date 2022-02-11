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
    int pages[101] = {};
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
    int currentPage = 0;
    while( in.peek() != EOF ){
        ++currentPage;
        int cntRows = 0;
        while( ++cntRows <= PAGE_SIZE_IN_ROWS && in.peek() != EOF ){
            getline(in, currentLine);

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
                    /*now we have got a new word*/
                    /*comparing to already existing words in the array*/





                    bool wasFound = false;//was added a new word into collection?
                    for(int i = 0; i < allWordsLength; i++){
                        int j = 0;
                        int compareWordLength = 0;
                        while( allWords[i].word[compareWordLength]!='\0' ){
                            compareWordLength++;
                        }

                        if( compareWordLength != currentWordSize ){
                            continue;
                        }
                        bool equal = true;
                        for(j = 0; j < currentWordSize; j++){
                            if( currentWord[j] != allWords[i].word[j] )
                                equal = false;
                        }
                        if( equal ){
                            int p = allWords[i].currentNumberOfPages;
                            if( p < 101 ){
                                allWords[i].pages[p] = currentPage;
                                allWords[i].currentNumberOfPages++;
                            }
                            wasFound = true;
                            break;
                        }

                    }

                    if( !wasFound ){
                        //now add a new word
                        allWords[allWordsLength].word = currentWord;
                        allWords[allWordsLength].pages[0] = currentPage;
                        allWords[allWordsLength].currentNumberOfPages = 1;
                        allWordsLength++;
                    }





                }else{
                    left++;
                }
            }




        }//cycle on lines in the page

        cout << endl << endl << endl;
    }//cycle on pages

    cout << "*******************************************" << endl;
    for(int i = 0; i < allWordsLength; i++){
        cout << allWords[i].word << "|\n";
        for(int j = 0; j < allWords[i].currentNumberOfPages; j++){
            cout << allWords[i].pages[j] << " ";
        }
        cout << endl;
    }
    /*
        sorting
    */


    in.close();
    return 0;
}
