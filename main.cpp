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
    return (char)(x + 65);
}

int main() {
    string encrypted = "EHOE YAVC EIME WEXK TNOL LSXS AROX PNCM ZNCA SADI GEBX ZOBM RIXE EEKR JTRM YGSX NAXH ZWRE EEFI CWOO YOGL ZWDS ZRNI CIDX ZPOV QOBQ TTME YFYP WOGE YAVC DICF FTSX SACR ZPYA PRYJ LNDM NIZE EIXK LNIE YAVC EIME WROP LTSS YSYV EREX SSSX DPBS GIXG PICX ZACW TSDY DIXQ LKSR RAFE TLKF WEGL LTGI LROE WROE OYKG BUKM YTOH HIDL EHOE YAVC EIME WEXK TNOA PAFI DAVK PBBE TCZE ETOV YSTY DTKW EHON LCAY LRNP ZOWA PAFI DFVS HEBW LNNP PAFI D";
    int frequencyTable[26] = { 0 };
    for (char c : encrypted) { 
        if (isalpha(c)) {
            frequencyTable[getIndexFromChar(c)] += 1;
        }
    }
    /* 
        for each loop
        https://www.codecademy.com/resources/docs/cpp/loops/foreach
    */

    for (int i = 0; i < 26; i++) {
        cout << getCharFromIndex(i) << ": " << frequencyTable[i] << endl;
    }

    return 0;
}

