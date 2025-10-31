#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <cmath>
#include <time.h> // used for randomization https://stackoverflow.com/questions/4196153/find-how-many-seconds-past-since-1-1-1970


using namespace std;

// the json thing was to make our compiler work but we realized they were useless

int getIndexFromChar(char ch) { // i learned functions in ap computer science a
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

// everything below is for midterm part 1

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

string vigenereShift(string s, string key) { // void function because i just want it to print
    vector<int> stringToIndex(key.length()); // this array is the same length as the number of letters in the key
    for (int i = 0; i < key.length(); i++) {
        stringToIndex.at(i) = getIndexFromChar(key.at(i)); // turns the words into there number counterpart and into an array
    }
    string newMessage = "";
     for (int i = 0, j = 0; i < s.length(); i++) { // 2 variables i and j. i iterates and j counts the key looping
        if (isalpha(s.at(i))) { // checks if the character is a letter or a space
            if (j == key.length()) { // a words length is always (excluding length 0) last index + 1. we reset j to 0 to avoid out of range error
                j = 0;
            }
            newMessage += getCharFromIndex((getIndexFromChar(s.at(i)) - stringToIndex.at(j) + 26) % 26);
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
            newMessage += " "; // account for the spaces
        }
    }
    return newMessage;
}

string suggestKey(string s) {
    vector<string> keys({
        "UTTER","DESCRIPTIVE","CARING","PIES","DRAWER","STATION","SOOTHE","YEAR",
        "AGREEABLE","SEEMLY","BUTTON","ENCOURAGE","REDUCE","BED","WAVE","NOSY",
        "ZOO","HATEFUL","FLAKY","WORK","EAR","UNEVEN","CUMBERSOME","LANGUID","BOX",
        "DEVILISH","YAWN","ABLAZE","LAKE","HARBOR","LEGS","GLOW","GLOSSY","CRUEL",
        "WARN","HARD","UNIQUE","CARD","HUG","TANGIBLE","HOOK","LABEL","EXOTIC",
        "ACCOUNT","IMAGINE","GRAIN","TRANQUIL","BOOK","PICKLE","WHISTLE","SACK",
        "SCISSORS","TRASHY","PUZZLED","BOTTLE","SMILE","NEIGHBORLY","EATABLE",
        "ADMIT","PICAYUNE","TYPE","FAST","SHY","ANGER","OPEN","ADD","CURLY",
        "FREE","AFTERMATH","CHERRY","DAILY","HEAL","ROSE","ABHORRENT","SHORT",
        "FINE","GUARDED","VASE","FASCINATED","FRESH","CHICKENS","MINE","STARE"
    });
    /*
        AI used to populate this list due to the sheer amount of keys
        prompt "...turn the keys into a string vector with all upper case"
        Accessed Oct. 2025
    */
    string spaceslessMessage = "";
    for (int i = 0; i < s.length(); i++) {
        if (s.at(i) != ' ') {
            spaceslessMessage += s.at(i);
        }
    }
    /*
        gets rid of the spaces to get the number of characters in the message. otherwise 
        the actual letter frequencies in the message would be lower than it actually is
    */

    vector<double> deviation; 
    // vector of letter deviation (explained a bit blow)
    for (string key : keys) {
        vector<int> frequencyAfterShift = populateFreqArray(vigenereShift(spaceslessMessage,key));
        // calls the frequency functions after the vigenere reverse shift
        vector<double> englishLanguageFrequencies = {8.2, 1.5, 2.8, 4.3, 12.7, 2.2, 2.0, 6.1, 7.0, 0.15, 0.77, 4.0, 2.4, 6.7, 7.5, 1.9, 0.095, 6.0, 6.3, 9.1, 2.8, 0.98, 2.4, 0.15, 2.0, 0.074};
        /*
            this is a bit hard to follow but. I used AI
            to get the frequency of all the letters in the alphabet
            so index 0 would be the frequency out of 100
            for the letter A and index 25 is the letter Z
            this info is easily accesbile on the internet but using AI allowed
            me to order them a lot easier without leaving any human error

            i feel this is a responsible use of AI and if not
            im open to pleading my case
            prompt "can you output the frequency of all letters as spoken in the english language"
            ... "put it in a double vector in c++"
            accessed: Oct. 2025
        */ 
        double totalDeviation = 0;
        // deviation starts at zero
        for (int i = 0; i < 26; i++) {
            double freq = (0.0 + frequencyAfterShift.at(i)) / spaceslessMessage.length() * 100;
            /*
                freq takes the number of times the letter at index i pops up in the message
                divides it by the number of characters to and multiply it by 100 to get the percentage
            */ 

            totalDeviation += abs(englishLanguageFrequencies.at(i) - freq); 
            /*
                I calculated the "deviation" as the absolute value of the letter frequency
                in the english language minus the letter frequency in the inputted string
                i add all of them together for all 26 letters in the alphabet
                logically speaking, the key that produces the least deviation is the one that
                decrypts the message because it simulates an actual english paragraph
            */
        }
        deviation.push_back(totalDeviation); // adda it to the array
    }

    double smallestDev = deviation.at(0);
    int indexOfSmallestDev = 0;
    for (int i = 1; i < (int)deviation.size(); i++) {
        if (deviation.at(i) < smallestDev) {
            smallestDev = deviation.at(i);
            indexOfSmallestDev = i;
        }
    } 
    // this for loop finds the lowest deviation and returns the index

    return keys.at(indexOfSmallestDev); 
    // returns the key at the given index to circle back to the key given because we are techincally still brute forcing
}

void decryptFunction() {
    string encrypted = "EHOE YAVC EIME WEXK TNOL LSXS AROX PNCM ZNCA SADI GEBX ZOBM RIXE EEKR JTRM YGSX NAXH ZWRE EEFI CWOO YOGL ZWDS ZRNI CIDX ZPOV QOBQ TTME YFYP WOGE YAVC DICF FTSX SACR ZPYA PRYJ LNDM NIZE EIXK LNIE YAVC EIME WROP LTSS YSYV EREX SSSX DPBS GIXG PICX ZACW TSDY DIXQ LKSR RAFE TLKF WEGL LTGI LROE WROE OYKG BUKM YTOH HIDL EHOE YAVC EIME WEXK TNOA PAFI DAVK PBBE TCZE ETOV YSTY DTKW EHON LCAY LRNP ZOWA PAFI DFVS HEBW LNNP PAFI D";
    // team 7's key
    string suggestedKey = suggestKey(encrypted);
    // gets the suggested key
    int choice = 0;
    while (choice != 1 && choice != 2) {
        cout << endl;
        cout << "Would you like to see the suggested key (1) \nor see the correct key, frequency table, and message (2)" << endl;
        cin >> choice;
        if (choice != 1 && choice != 2) {
            cout << "Choose a valid option" << endl;
        }
    } cout << endl;
    if (choice == 1) {
        cout << "Suggested Key: " << suggestedKey << endl;
    } else if (choice == 2) {
        vector<int> freqArray = populateFreqArray(encrypted);
        cout << "Frequency Table of Encrypted Message" << endl;
        for (int i = 0; i < 26; i++) {
            cout << getCharFromIndex(i) << ": " << freqArray.at(i) << " ";
            if ((i + 1) % 5 == 0 || i == 25) {
                cout << endl;
            }
        }

        string decryptedMessage = vigenereShift(encrypted, suggestedKey);
        cout << endl << "Decrypted Message without proper spacing" << endl;
        cout << decryptedMessage;
        cout << endl << endl;
        cout << "Correct Key: " << suggestedKey;
    }
}

// Midterm Part two below 

// void encryptFunction() {
//     string message;
//     cin >> message;
//     vector<int> keyCode;
//     string encryptedMessage;
//     for (int i = 0; message.length(); i++) {

//     }
// }

int main() {
    decryptFunction();
    return 0;
}

/*
    decrypted message with proper spacing
    THE ANALYTICAL ENGINE HAS NO PRETENSIONS WHATSOEVER TO ORIGINATE ANYTHING 
    IT CAN DO WHATEVER WE KNOW HOW TO ORDER IT TO PERFORM IT CAN FOLLOW ANALYSIS BUT 
    IT HAS NO POWER OF ANTICIPATING ANY ANALYTICAL RELATIONS OR TRUTHS ITS PROVINCE IS 
    TO ASSIST US IN MAKING AVAILABLE WHAT WE ARE ALREADY ACQUAINTED WITH THE ANALYTICAL
    ENGINE WEAVES ALGEBRAIC PATTERNS JUST AS THE JACQUARD LOOM WEAVES FLOWERS AND LEAVES
*/

