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
    onLinesCycle:{
            if( !( ++cntRows <= PAGE_SIZE_IN_ROWS && in.peek() != EOF ) ){
                goto afterLinesInThePage;
            }
            getline(in, currentLine);

            /*
                split
            */

            int left, right;
            left = right = 0;
            goThroughLine:{
                if( currentLine[left] == '\0' ){
                    goto afterLineRead;
                }
                if( currentLine[left] != ' ' ){
                    right = left;
                    /*
                        here i am increasing right,
                        until it stands after current word
                    */
                    rightIncreaser:{
                        if( !( currentLine[right] != ' ' && currentLine[right] != '\0' ) ){
                            goto afterRightIncreaser;
                        }
                        right++;
                        goto rightIncreaser;
                    }
                    /*here i am processing current word*/
                afterRightIncreaser:
                    string currentWord = "";
                    int currentWordSize = right-left;
                currentWordReading:{
                        if( left >= right ){
                            goto afterCurrentWordReading;
                        }

                        currentWord += currentLine[left];
                        left++;
                        goto currentWordReading;
                    }
                afterCurrentWordReading:
                    if( currentWord[currentWordSize-1] == '.' || currentWord[currentWordSize-1] == ','
                       || currentWord[currentWordSize-1] == '!' || currentWord[currentWordSize-1] == '?'
                       || currentWord[currentWordSize-1] == ':' || currentWord[currentWordSize-1] == ';'
                       || currentWord[currentWordSize-1] == '"' || currentWord[currentWordSize-1] == '\''){
                        //so that is why we`re deleting last character
                        string tmp = "";
                            int i1 = 0;
                            for1:{
                                if( i1 >= currentWordSize-1 ){
                                    goto afterFor1;
                                }
                                tmp += currentWord[i1];
                                i1++;
                                goto for1;
                            }
                        afterFor1:
                        currentWord = tmp;
                        currentWordSize--;
                    }
                    //cout << currentWord << "|";
                    /*now we have got a new word*/
                    /*comparing to already existing words in the array*/

                    bool isANormalWord = true;//if this word is really a word(not a char sequence at all);
                        int it = 0;
                        /*here i am parsing word */
                        for2:{
                            if( it >= currentWord.size() ){
                                goto afterFor2;
                            }

                                if( !( (currentWord[it]>='A' && currentWord[it]<='Z')
                                    || (currentWord[it]>='a' && currentWord[it]<='z') ) ){
                                    isANormalWord = false;
                                }

                            it++;
                            goto for2;
                        }
                    afterFor2:


                    /*here i am processing current word into lower case*/
                        it = 0;
                        for3:{
                            if( it >= currentWord.size() )
                                goto afterFor3;

                            if( currentWord[it] >= 'A' && currentWord[it] <= 'Z' )
                                currentWord[it] += 'a' - 'A';

                            it++;
                            goto for3;
                        }
                    afterFor3:

                        it = 0;
                        for4:{
                            if( it >= STOP_WORDS_NUMBER )
                                goto afterFor4;

                            if( stopWords[it] == currentWord )
                                isANormalWord = false;

                            it++;
                            goto for4;
                        }
                    afterFor4:


                    if(isANormalWord){
                        bool wasFound = false;//was added a new word into collection?
                        int i = 0;
                        for5:{
                            if( i >= allWordsLength ){
                                goto afterFor5;
                            }

                                int compareWordLength = 0;
                                    while1:{
                                        if( allWords[i].word[compareWordLength] == '\0' )
                                            goto afterWhile1;

                                        compareWordLength++;
                                        goto while1;
                                    }
                                afterWhile1:

                                bool equal = true;
                                int k = 0;
                                for6:{
                                    if( k >= currentWordSize )
                                        goto afterFor6;

                                    if( currentWord[k] != allWords[i].word[k] )
                                        equal = false;

                                    k++;
                                    goto for6;
                                }
                            afterFor6:

                                if( equal && compareWordLength == currentWordSize ){
                                    int p = allWords[i].currentNumberOfPages;
                                    if( p <= 100 ){
                                        allWords[i].pages[p] = currentPage;
                                        allWords[i].currentNumberOfPages++;
                                    }
                                    wasFound = true;
                                    goto afterFor5;
                                }

                            i++;
                            goto for5;
                        }
                    afterFor5:

                        if( !wasFound ){
                            /*here I am enlarging my allWords-array*/
                            if( allWordsLength == allWordsCapacity ){
                                WordProcessor* copyOfAllWordsArray = new WordProcessor[allWordsLength];
                                int l;
                                l = 0;
                                    for7:{
                                        if( l >= allWordsLength )
                                            goto afterFor7;

                                        copyOfAllWordsArray[l] = allWords[l];

                                        l++;
                                        goto for7;
                                    }
                                afterFor7:
                                allWordsCapacity *= 2;
                                allWords = new WordProcessor[allWordsCapacity];

                                l = 0;
                                for8:{
                                    if( l >= allWordsLength )
                                        goto afterFor8;

                                    allWords[l] = copyOfAllWordsArray[l];

                                    l++;
                                    goto for8;
                                }
                                afterFor8:
                                //needed, because it is impossible to set
                                //label just before "}" token
                                if(true);
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
                goto goThroughLine;
            }
        afterLineRead:


            goto onLinesCycle;
        }//cycle on lines in the page
    afterLinesInThePage:
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
