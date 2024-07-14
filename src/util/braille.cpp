#include "braille.hpp"

#include <map>

std::string braille_to_eng(std::string input) {
    // Create dictionary
    std::map<std::string, char> dict = {
        {"\u2800", ' '},  {"\u2801", 'A'}, {"\u2802", '1'}, {"\u2803", 'B'},
        {"\u2804", '\''}, {"\u2805", 'K'}, {"\u2806", '2'}, {"\u2807", 'L'},
        {"\u2808", '@'},  {"\u2809", 'C'}, {"\u2810", 'I'}, {"\u2811", 'F'},
        {"\u2812", '/'},  {"\u2813", 'M'}, {"\u2814", 'S'}, {"\u2815", 'P'},
        {"\u2816", '"'},  {"\u2817", 'E'}, {"\u2818", '3'}, {"\u2819", 'H'},
        {"\u2820", '9'},  {"\u2821", 'O'}, {"\u2822", '6'}, {"\u2823", 'R'},
        {"\u2824", '^'},  {"\u2825", 'D'}, {"\u2826", 'J'}, {"\u2827", 'G'},
        {"\u2828", '>'},  {"\u2829", 'N'}, {"\u2830", 'T'}, {"\u2831", 'Q'},
        {"\u2832", ','},  {"\u2833", '*'}, {"\u2834", '5'}, {"\u2835", '<'},
        {"\u2836", '-'},  {"\u2837", 'U'}, {"\u2838", '8'}, {"\u2839", 'V'},
        {"\u2840", '.'},  {"\u2841", '%'}, {"\u2842", '['}, {"\u2843", '$'},
        {"\u2844", '+'},  {"\u2845", 'X'}, {"\u2846", '!'}, {"\u2847", '&'},
        {"\u2848", ';'},  {"\u2849", ':'}, {"\u2850", '4'}, {"\u2851", '\\'},
        {"\u2852", '0'},  {"\u2853", 'Z'}, {"\u2854", '7'}, {"\u2855", '('},
        {"\u2856", '_'},  {"\u2857", '?'}, {"\u2858", 'W'}, {"\u2859", ']'},
        {"\u2860", '#'},  {"\u2861", 'Y'}, {"\u2862", ')'}, {"\u2863", '='}
    };

    // Convert to English
    std::string eng = "";
    for (int i = 0; i < input.length(); ) {
        if (i + 2 < input.length() && dict.find(input.substr(i, 3)) != dict.end()) {
            // If it's a valid Braille character
            eng += dict[input.substr(i, 3)];
            i += 3;
        } else {
            // If it's not a Braille character, keep it as is
            eng += input[i];
            i++;
        }
    }

    // Return
    return eng;
}

std::string eng_to_braille(std::string eng) {
#ifdef BLIND
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
    std::string braille = "";
    for (int i = 0; i < eng.length(); i++) {
        char cur_char = std::toupper(eng[i]);
        if (dict.contains(cur_char)) {
            braille += dict[cur_char];
        } else {
            braille += eng[i];
        }
    }
    // Return
    return braille;
#else
    return eng;
#endif
}
