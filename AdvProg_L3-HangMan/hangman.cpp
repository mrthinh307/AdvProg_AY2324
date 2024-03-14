#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "hangman.h"

using namespace std;

int generateRandomNumber(const int min, const int max) {
    return rand() % (max - min + 1) + min;
}

vector<string> readWordListFromFile(const string& filePath) {
    vector<string> wordList;
    ifstream wordFile(filePath);
    if (!wordFile.is_open()) {
        throw domain_error("Unable to open file");
    }
    string word;
    while (wordFile >> word) {
        wordList.push_back(word);
    }
    wordFile.close();
    return wordList;
}

bool isCharInWord(const char ch, const string& word) {
    return word.find(ch) != string::npos;
}

string chooseWordFromList(const vector<string>& wordList, int index) {
    return wordList[index];
}

string generateHiddenCharacters(const string& answerWord) {
    return string(answerWord.size(), '-');
}

char getInputCharacter() {
    char ch;
    cin >> ch;
    return tolower(ch);
}

void updateSecretWord(string& secretWord, const char ch, const string& word) {
    for (size_t i = 0; i < word.size(); ++i) {
        if (word[i] == ch) {
            secretWord[i] = ch;
        }
    }
}

void updateEnteredChars(const char ch, string& chars) {
    chars += ch;
}

void updateIncorrectGuess(int& incorrectGuess) {
    ++incorrectGuess;
}

void processData(const char ch, const string& word, 
                 string& secretWord, string& correctChars, 
                 int& incorrectGuess, string& incorrectChars) {
    if (isCharInWord(ch, word)) {
        updateSecretWord(secretWord, ch, word);
        updateEnteredChars(ch, correctChars);
    } else {
        updateIncorrectGuess(incorrectGuess);
        updateEnteredChars(ch, incorrectChars);
    }
}
