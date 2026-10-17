#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>

// Function to calculate feedback
pii getFeedback(string guess, string code) {
    int strong = 0, weak = 0;
    int length = guess.size();
    vector<bool> usedCode(length, false), usedGuess(length, false);

    // Count strong matches (correct color & position)
    for (int i = 0; i < length; i++) {
        if (guess[i] == code[i]) {
            strong++;
            usedCode[i] = usedGuess[i] = true;
        }
    }

    // Count weak matches (correct color, wrong position)
    for (int i = 0; i < length; i++) {
        if (usedGuess[i]) continue;
        for (int j = 0; j < length; j++) {
            if (!usedCode[j] && guess[i] == code[j]) {
                weak++;
                usedCode[j] = true;
                break;
            }
        }
    }
    return {strong, weak};
}

// Function to generate all valid secret codes of given length
void generateCodes(string current, int length, vector<string> &codes) {
    if (current.size() == length) {
        codes.push_back(current);
        return;
    }
    for (char c = '1'; c <= '9'; c++) {
        generateCodes(current + c, length, codes);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    while (n--) {
        string guess;
        int strong, weak;
        cin >> guess >> strong >> weak;

        int count = 0;
        vector<string> possibleCodes;
        generateCodes("", guess.size(), possibleCodes);

        for (const string &code : possibleCodes) {
            if (getFeedback(guess, code) == make_pair(strong, weak)) {
                count++;
            }
        }

        cout << count << "\n";
    }
    return 0;
}
