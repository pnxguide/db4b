#include <cctype>
#include <iostream>
#include <map>
#include <string>

std::string eng_to_braille(std::string before) {
    // Create dictionary
    std::map<char, std::string> dict = {
        {' ', "\u2800"},  {'A', "\u2801"}, {'1', "\u2802"}, {'B', "\u2803"},
        {'\'', "\u2804"}, {'K', "\u2805"}, {'2', "\u2806"}, {'L', "\u2807"},
        {'@', "\u2808"},  {'C', "\u2809"}, {'I', "\u2810"}, {'F', "\u2811"},
        {'/', "\u2812"},  {'M', "\u2813"}, {'S', "\u2814"}, {'P', "\u2815"},
        {'"', "\u2816"},  {'E', "\u2817"}, {'3', "\u2818"}, {'H', "\u2819"},
        {'9', "\u2820"},  {'O', "\u2821"}, {'6', "\u2822"}, {'R', "\u2823"},
        {'^', "\u2824"},  {'D', "\u2825"}, {'J', "\u2826"}, {'G', "\u2827"},
        {'>', "\u2828"},  {'N', "\u2829"}, {'T', "\u2830"}, {'Q', "\u2831"},
        {',', "\u2832"},  {'*', "\u2833"}, {'5', "\u2834"}, {'<', "\u2835"},
        {'-', "\u2836"},  {'U', "\u2837"}, {'8', "\u2838"}, {'V', "\u2839"},
        {'.', "\u2840"},  {'%', "\u2841"}, {'[', "\u2842"}, {'$', "\u2843"},
        {'+', "\u2844"},  {'X', "\u2845"}, {'!', "\u2846"}, {'&', "\u2847"},
        {';', "\u2848"},  {':', "\u2849"}, {'4', "\u2850"}, {'\\', "\u2851"},
        {'0', "\u2852"},  {'Z', "\u2853"}, {'7', "\u2854"}, {'(', "\u2855"},
        {'_', "\u2856"},  {'?', "\u2857"}, {'W', "\u2858"}, {']', "\u2859"},
        {'#', "\u2860"},  {'Y', "\u2861"}, {')', "\u2862"}, {'=', "\u2863"},
    };
    // Convert to Braille
    std::string after = "";
    for (int i = 0; i < before.size(); i++) {
        char cur_char = std::toupper(before[i]);
        if (dict.contains(cur_char)) {
            after += dict[cur_char];
        } else {
            after += before[i];
        }
    }
    // Return
    return after;
}

int main() {
    while (true) {
        std::string cmd;
        std::cout << "😎 ";
        std::getline(std::cin, cmd);
        std::cout << eng_to_braille(cmd).c_str() << std::endl;
    }
    return 0;
}
