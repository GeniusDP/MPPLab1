#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility>

using namespace std;

int main()
{
    ifstream in("input.txt");
    vector<pair<string, vector<int>>> wordsOnPages;
    int pageCounter = 0;

    while(true){
        pageCounter++;
        int cnt = 0;
        string s;
        while( getline(in, s, '\n') && ++cnt <= 45 ){
            cout << "---" << endl;
            cout << s << endl;
            /*vector<string> words;
            int i;
            int left;
            bool leftIsSet;
            int lineLength = 0;
                i = 0;
                while( s[i] != '\0' ){
                    i++;
                }
                lineLength = i;



            left = 0;
            while( left < lineLength && s[left] == ' ' ){
                left++;
            }

            i = left;
            leftIsSet = true;
            while( i < lineLength ){
                if( (s[i] > 'a' && s[i] < 'z') || (s[i] > 'A' && s[i] < 'Z') ){

                }
            }*/

        }

    }

    return 0;
}
