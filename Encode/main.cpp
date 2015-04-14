#include <iostream>
#include <string>

using namespace std;

string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

string stripRepeats(string b){
    string retVal = "";
    bool alphaChecked[26];
    for(int iter = 0; iter < 26; iter++){
        alphaChecked[iter] = false;
    }
    bool skip = false;
    for(unsigned int i = 0; i < b.length(); i++){
        for(unsigned int iter = 0; iter < 26; iter++){
            if(b[i] == alphabet[iter]){
                if(alphaChecked[iter] == true){
                    skip = true;
                }
                alphaChecked[iter] = true;
            }
        }
        if(skip){
            skip = false;
            continue;
        }
        retVal += b[i];
    }
    cout << retVal << endl;
    return retVal;
}

int find(char a, string b){
    for(unsigned int iter = 0; iter < b.length(); iter++){
        if(b[iter] == a){
            return iter;
        }
    }
    return -1;
}

string encode(string a, string b){
    b = stripRepeats(b);
    string alphaGamm = b;
    for(unsigned int iter = 0; iter < alphabet.length(); iter++){
        if(find(alphabet[iter], alphaGamm) == -1){
            alphaGamm += alphabet[iter];
        }
    }
    cout << alphaGamm << endl;
    string scrambledSentence = "";
    for(unsigned int iter = 0; iter < a.length(); iter++){
        int letterLoc = find(a[iter], alphabet);
        if(letterLoc != -1){
            scrambledSentence += alphaGamm[letterLoc];
        }
        else{
            scrambledSentence += a[iter];
        }
    }
    return scrambledSentence;
}

int main()
{
    cout << encode("FLEE AT ONCE. WE ARE DISCOVERED!", "ZZEEBBRABS");
    return 0;
}
