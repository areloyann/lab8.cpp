#include <iostream>
#include <vector>
#include <string>
using namespace std;
struct LZ77Token {
    int offset;
    int length;
    char next_char;
};
vector<LZ77Token> compressLZ77(const string& input, int window_size, int look_ahead_buffer_size) {
    vector<LZ77Token> tokens;
    int i = 0;
    while (i < input.size()) {
        int best_length = 0;
        int best_offset = 0;
        char next_char = input[i];
        int window_start = max(0, i - window_size);
        for (int j = window_start; j < i; ++j) {
            int length = 0;
            while (i + length < input.size() && input[j + length] == input[i + length]) {
                length++;
                if (length >= look_ahead_buffer_size) break;
            }
            if (length > best_length) {
                best_length = length;
                best_offset = i - j;
                if (i + length < input.size()) next_char = input[i + length];
            }
        }

        tokens.push_back({best_offset, best_length, next_char});
        i += (best_length > 0) ? best_length + 1 : 1;
    }
    return tokens;
}

int main() {
    string input = "aacaacabcabaaac";
    cout<<input<<endl;
    int window_size = 6;
    int look_ahead_buffer_size = 4;
    vector<LZ77Token> compressed = compressLZ77(input, window_size, look_ahead_buffer_size);

    for (const auto& token : compressed) {
        cout << "(" << token.offset << ", " << token.length << ", " << token.next_char << ") ";
    }
    cout << endl;
    return 0;
}
