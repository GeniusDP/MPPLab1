#include <iostream>
#include <fstream>
#include <string>
using namespace std;



/*
    Task 1
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

struct Pair{
    string first;
    int second;
};

int main()
{
    ifstream in("input.txt");
    const int MAX_WORDS_TO_SHOW = 25;
    int wordsLength = 0, wordsCapacity = 5;
    Pair* words = new Pair[wordsCapacity];

    string currentWord;
    string stopWords[] =
        {"the", "for", "in", "on", "a",
         "an", "of", "to", "at", "by",
         "onto", "into", "are", "but", "is",
         "and", "not", "or"
        };
        int j = 0;
        bool foundInStopWords = false;
    whileTrue:
            if( !(in >> currentWord) ){
                goto afterWhileTrue;
            }

            j = 0;
            whileToLowerCase:
                if( currentWord[j] == '\0' ){
                    if(j > 0 && !(currentWord[j-1] >= 'A' && currentWord[j-1] <= 'Z')
                       &&  !(currentWord[j-1] >= 'a' && currentWord[j-1] <= 'z') ){
                        currentWord[j-1] = '\0';
                    }
                    goto afterWhileToLowerCase;
                }
                if( currentWord[j] <= 'Z' && currentWord[j] >= 'A' ){
                    currentWord[j] += 'a' - 'A';
                }
                j++;
            goto whileToLowerCase;
        afterWhileToLowerCase:


            //sizeof - is an operator, not a function
            //(according to C++ standard)
            j = 0;
            foundInStopWords = false;
            filterStopWords:
                if( j >= sizeof(stopWords) / sizeof(string) ){
                    goto afterFilterStopWords;
                }
                if(currentWord == stopWords[j]){
                    foundInStopWords = true;
                }
                j++;
            goto filterStopWords;
        afterFilterStopWords:


            if( !foundInStopWords ){
                bool found = false;
                j = 0;
                countingSimilars:
                    if(j >= wordsLength){
                        goto afterCountingSimilars;
                    }
                    if(words[j].first == currentWord){
                        words[j].second++;
                        found = true;
                    }
                    j++;
                goto countingSimilars;
            afterCountingSimilars:
                if( !found ){
                    if(wordsLength + 1 > wordsCapacity){
                            wordsCapacity *= 2;
                            Pair* tmpWords = new Pair[wordsCapacity];
                            int i = 0;
                            copyingWords:
                                if( i >= wordsLength ){
                                    goto afterCopyingWords;
                                }
                                tmpWords[i] = words[i];
                                i++;
                            goto copyingWords;
                        afterCopyingWords:
                            delete[] words;
                            words = tmpWords;
                    }
                    words[ wordsLength++ ] = {currentWord, 1};
                }
            }
        goto whileTrue;
    afterWhileTrue:


    /*sorting*/
    int i;
    i = 0;
        upperFor:
            if(i >= wordsLength-1){
                goto afterUpperFor;
            }
            j = i + 1;
                innerFor:
                    if( j >= wordsLength ){
                        goto afterInnerFor;
                    }
                        /*body*/
                        if( words[i].second < words[j].second ){
                            Pair tmp;
                            tmp = words[i];
                            words[i] = words[j];
                            words[j] = tmp;
                        }
                    j++;
                goto innerFor;
            afterInnerFor:
            i++;
        goto upperFor;
    afterUpperFor:


    /*printing*/
    i = 0;
    outputCycle:
        if( !(i < wordsLength && i < MAX_WORDS_TO_SHOW) ){
            goto finish;
        }
        cout << words[i].first << " " << words[i].second << endl;
        i++;
    goto outputCycle;
finish:
    return 0;
}
