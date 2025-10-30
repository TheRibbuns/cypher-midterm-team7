#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <ctime> 

using namespace std;

int getIndexFromChar(char ch) {
    return (int)ch - 65; 
    /*
        ascii uppercase letters start at 65
        vigenere cypher starts A at 0 and Z at 25
        So subtract 65 to get the index in the alphabet
    */  
}

char getCharFromIndex(int x) {
    return (char)(x + 65);
    /*
        same logic in reverse
        start with number x which is a number 
        from 0-25
        add 65 to get the ascii value
    */  
}

vector<int> populateFreqArray(string s) {
    vector<int> freq(26, 0);
    /*
        create an array of 26 0's representing
        the frequency of the letters
    */
    for (char c : s) { // for each loop
        if (isalpha(c)) { // check if the character is not a space
            freq[getIndexFromChar(c)]++; 
            /*
                the index of the letter is found using
                the get index from char function.
                the number from that is used to 
                get the index of the frequency array.
                ex: if the char is A. 
                The function returns 0 and then 
                freq[0] is incremented by 1.
                B=1,C=2...Z=25
            */
        }
    }
    return freq;
    /*
        for each loop
        https://www.codecademy.com/resources/docs/cpp/loops/foreach
    */
}

void vigenereShiftPartOne(string s, string key) { // void function because i just want it to print
    vector<int> stringToIndex(key.length()); // this array is the same length as the number of letters in the key
    for (int i = 0; i < key.length(); i++) {
        stringToIndex.at(i) = getIndexFromChar(key.at(i)); // turns the words into there number counterpart and into an array
    }

    for (int i = 0, j = 0; i < s.length(); i++) { // 2 variables i and j. i iterates and j counts the key looping
        if (isalpha(s.at(i))) { // checks if the character is a letter or a space
            if (j == key.length()) { // a words length is always (excluding length 0) last index + 1. we reset j to 0 to avoid out of range error
                j = 0;
            }
            cout << getCharFromIndex((getIndexFromChar(s.at(i)) - stringToIndex.at(j) + 26) % 26);
            /*
                starting from the inside
                getIndexFromChar(s.at(i)) gives you the alphabetic index of the letter
                we subtract the number of index j because we are decrypting and not encrypting
                if the key were HELLO and with our first 4 letters EHOE
                this first statement would be
                E - H
                H - E
                O - L
                E - L
                we then add 26 to get a positive number and loop back around to the end of the alphabet
                then we do mod 26 to get a number between 0 and 25 and not get random non-alpha characters
            */
            j++; // increment j to go to the next letter
        } else {
            cout << " "; // account for the spaces
        }
    }
}

int main() {
    string encrypted = "EHOE YAVC EIME WEXK TNOL LSXS AROX PNCM ZNCA SADI GEBX ZOBM RIXE EEKR JTRM YGSX NAXH ZWRE EEFI CWOO YOGL ZWDS ZRNI CIDX ZPOV QOBQ TTME YFYP WOGE YAVC DICF FTSX SACR ZPYA PRYJ LNDM NIZE EIXK LNIE YAVC EIME WROP LTSS YSYV EREX SSSX DPBS GIXG PICX ZACW TSDY DIXQ LKSR RAFE TLKF WEGL LTGI LROE WROE OYKG BUKM YTOH HIDL EHOE YAVC EIME WEXK TNOA PAFI DAVK PBBE TCZE ETOV YSTY DTKW EHON LCAY LRNP ZOWA PAFI DFVS HEBW LNNP PAFI D";
    // vigenereShiftPartOne(encrypted);
    string keys[] = {"UTTER","DESCRIPTIVE","CARING","PIES","DRAWER","STATION","SOOTHE","YEAR","AGREEABLE","SEEMLY","BUTTON","ENCOURAGE","REDUCE","BED","WAVE","NOSY","ZOO","HATEFUL","FLAKY","WORK","EAR","UNEVEN","CUMBERSOME","LANGUID","BOX","DEVILISH","YAWN","ABLAZE","LAKE","HARBOR","LEGS","GLOW","GLOSSY","CRUEL","WARN","HARD","UNIQUE","CARD","HUG","TANGIBLE","HOOK","LABEL","EXOTIC","ACCOUNT","IMAGINE","GRAIN","TRANQUIL","BOOK","PICKLE","WHISTLE","SACK","SCISSORS","TRASHY","PUZZLED","BOTTLE","SMILE","NEIGHBORLY","EATABLE","ADMIT","PICAYUNE","TYPE","FAST","SHY","ANGER","OPEN","ADD","CURLY","FREE","AFTERMATH","CHERRY","DAILY","HEAL","ROSE","ABHORRENT","SHORT","FINE","GUARDED","VASE","FASCINATED","FRESH","CHICKENS","MINE","STARE"};
    // AI used to put the keys into an array and all uppercase
    for (string key : keys) {
        /*
            this is our brute for algorithm to test all the keys
        */
        cout << key << endl;
        vigenereShiftPartOne(encrypted, key); 
        cout << endl << endl << endl;
    }
    // vector<int> vigenereFreq = populateFreqArray(vigenereShiftedString);

    return 0;
}

