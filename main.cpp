//your code goes here :}

#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <ctime> //gonna need thus for randomizing later?

using namespace std;

int getIndexFromChar(char ch) {
    return (int)ch - 65;
}

char getCharFromIndex(int x) {
    return (char)((x % 26 + 65));
}

vector<int> populateFreqArray(string s) {
    vector<int> freq(26, 0);
    for (char c : s) {
        if (isalpha(c)) {
            freq[getIndexFromChar(c)]++;
        }
    }
    return freq;
    /*
        for each loop
        https://www.codecademy.com/resources/docs/cpp/loops/foreach
    */
}

string vigenereShiftPartOne(string s) {
    string key;
    cin >> key;
    vector<int> stringToIndex(key.length());
    for (int i = 0; i < key.length(); i++) {
        stringToIndex.at(i) = getIndexFromChar(key.at(i)); // turns the words into there number counterpart and into an array
    }

    for (int i = 0, j = 0; i < s.length(); i++) {
        if (isalpha(s.at(i))) {
            int shift = stringToIndex.at(j % key.length()); // gets the index from shifter array with j and mod.
            s.at(i) = getCharFromIndex((getIndexFromChar(s.at(i)) + shift) % 26);  // replaces the character at index i with the key and at index j.
            j++;
        }
    }
    return s;
}

void caesarCipher(string s, int x) {
    for (int i = 0; i < s.length(); i++) {
        if (isalpha(s.at(i))) {
            cout << getCharFromIndex(getIndexFromChar(s.at(i)) + x);
        } else {
            cout << " ";
        }
    }
}

int main() {
    string encrypted = "EHOE YAVC EIME WEXK TNOL LSXS AROX PNCM ZNCA SADI GEBX ZOBM RIXE EEKR JTRM YGSX NAXH ZWRE EEFI CWOO YOGL ZWDS ZRNI CIDX ZPOV QOBQ TTME YFYP WOGE YAVC DICF FTSX SACR ZPYA PRYJ LNDM NIZE EIXK LNIE YAVC EIME WROP LTSS YSYV EREX SSSX DPBS GIXG PICX ZACW TSDY DIXQ LKSR RAFE TLKF WEGL LTGI LROE WROE OYKG BUKM YTOH HIDL EHOE YAVC EIME WEXK TNOA PAFI DAVK PBBE TCZE ETOV YSTY DTKW EHON LCAY LRNP ZOWA PAFI DFVS HEBW LNNP PAFI D";
    string vigenereShiftedString = vigenereShiftPartOne(encrypted);
    vector<int> vigenereFreq = populateFreqArray(vigenereShiftedString);
    caesarCipher(vigenereShiftedString, 1);

    return 0;
}

