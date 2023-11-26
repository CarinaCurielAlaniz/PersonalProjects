#include "commands.h"

commands::commands(long long p, long long q)
{
    //set up variables
    P = p;
    Q = q;
    std::pair<char, std::string> newPair(' ', "00");
    letterValuePairings[newPair.first] = newPair.second;
    valueLetterPairings[newPair.second] = newPair.first;
    //set up maps (01, a) and (a, 00)
    for(int i = 1; i < 27; i++)
    {
        //ascii a = 97
        int asciiCode = i + 96;
        char alphabet = static_cast<char>(asciiCode);
        std::string newInt = std::to_string(i);
        if(i < 10)
        {
            newInt = "0" + newInt;
        }
        std::pair<char, std::string> newPair(alphabet, newInt);
        letterValuePairings[newPair.first] = newPair.second;
        valueLetterPairings[newPair.second] = newPair.first;
    }
}