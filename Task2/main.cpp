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
    const int PAGE_SIZE_IN_ROWS = 45;
    const int STOP_WORDS_NUMBER = sizeof(stopWords) / sizeof(string);
    int allWordsCapacity = 10;
    int allWordsLength = 0;
    WordProcessor* allWords = new WordProcessor[allWordsCapacity];

    string currentLine;
    int currentPage = 0;
onPagesCycle:{
        if( in.peek() == EOF ){
            goto toSorting;
        }
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
                       || currentWord[currentWordSize-1] == ':' || currentWord[currentWordSize-1] == ';'
                       || currentWord[currentWordSize-1] == '"' || currentWord[currentWordSize-1] == '\''){
                        //so that is why we`re deleting last character
                        string tmp = "";
                        for(int i = 0; i < currentWordSize-1; i++){
                            tmp += currentWord[i];
                        }
                        currentWord = tmp;
                        currentWordSize--;
                    }
                    //cout << currentWord << "|";
                    /*now we have got a new word*/
                    /*comparing to already existing words in the array*/

                    bool isANormalWord = true;
                    for(int it = 0; it < currentWord.size(); it++){
                        if( !( (currentWord[it]>='A' && currentWord[it]<='Z') || (currentWord[it]>='a' && currentWord[it]<='z') ) ){
                            isANormalWord = false;
                        }
                    }

                    for(int i = 0; i < currentWord.size(); i++){
                        if( currentWord[i] >= 'A' && currentWord[i] <= 'Z' )
                            currentWord[i] += 'a' - 'A';
                    }

                    for(int i = 0; i < STOP_WORDS_NUMBER; i++){
                        if( stopWords[i] == currentWord )
                            isANormalWord = false;
                    }





                    if(isANormalWord){
                        bool wasFound = false;//was added a new word into collection?
                        for(int i = 0; i < allWordsLength; i++){

                            int compareWordLength = 0;
                            while( allWords[i].word[compareWordLength] != '\0' ){
                                compareWordLength++;
                            }
                            bool equal = true;
                            for(int k = 0; k < currentWordSize; k++){
                                if( currentWord[k] != allWords[i].word[k] )
                                    equal = false;
                            }


                            if( equal && compareWordLength == currentWordSize ){
                                int p = allWords[i].currentNumberOfPages;
                                if( p <= 100 ){
                                    allWords[i].pages[p] = currentPage;
                                    allWords[i].currentNumberOfPages++;
                                }
                                wasFound = true;
                                break;
                            }

                        }

                        if( !wasFound ){
                            /*here I am enlarging my allWords-array*/
                            if( allWordsLength == allWordsCapacity ){
                                WordProcessor* copyOfAllWordsArray = new WordProcessor[allWordsLength];
                                for(int l = 0; l < allWordsLength; l++){
                                    copyOfAllWordsArray[l] = allWords[l];
                                }
                                allWordsCapacity *= 2;
                                allWords = new WordProcessor[allWordsCapacity];
                                for(int l = 0; l < allWordsLength; l++){
                                    allWords[l] = copyOfAllWordsArray[l];
                                }
                            }
                            //now add a new word
                            allWords[allWordsLength].word = currentWord;
                            allWords[allWordsLength].pages[0] = currentPage;
                            allWords[allWordsLength].currentNumberOfPages = 1;
                            allWordsLength++;
                        }
                    }




                }else{
                    left++;
                }
            }




        }//cycle on lines in the page
        goto onPagesCycle;
    }//cycle on pages
toSorting:
    ofstream out("output.txt");

    for(int i = 0; i < allWordsLength-1; i++){
        for(int j = i + 1; j < allWordsLength; j++){
            if( allWords[i].word > allWords[j].word )swap(allWords[i], allWords[j]);
        }
    }


    for(int i = 0; i < allWordsLength; i++){
        if( allWords[i].currentNumberOfPages < 101 ){
            out << allWords[i].word << " ---> ";
            for(int j = 0; j < allWords[i].currentNumberOfPages; j++){
                out << allWords[i].pages[j] << " ";
            }
            out << endl;
        }
    }


    out.close();
    in.close();
    return 0;
}
