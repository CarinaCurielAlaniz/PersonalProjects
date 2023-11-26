#include "commands.h"
#include <fstream>
#include <cmath>

void commands::encryption(std::string filename, long long n, std::string message)
{
    outputFileName = filename;
    encrypN = n;
    //if n is less than 27 ERROR and ask for new n
    if(n < 27)
    {
        std::cout << "ERROR: n too small, input n value greater than 27" << std::endl << "n: ";
        std::cin >> encrypN;
    }
    long long result = log(encrypN/27)/log(100.0);
    e = 65537;
    x = 1 + result;
    word = message;
    //convert word
    convMessage();
}
void commands::convMessage()
{
    std::ofstream outputFile(outputFileName);
    std::string mHold = "";
    std::string associatedNumber;
    //conv first x characters in message to int m
    long long curCount = 0;
    int it = 0;
    long long size = word.size();
    //repeat till entire thing is converted
    while(curCount < size)
    {
        mHold = "";
        if(static_cast<long long int>(word.size()) < x)
        {
            int append = x - word.size();
            for(int i = 0; i < append; i++) 
            {
                word += ' '; 
            }
        }  
        for(int i = 0; i < x; i++)
        {
            char wordLetter = word[i];
            if(letterValuePairings.find(wordLetter) != letterValuePairings.end()) 
            {
                associatedNumber = letterValuePairings[wordLetter];
            }
            mHold += associatedNumber; 
        }
        word.erase(0, x); 
        curCount += x;
        it++;
        M = std::stoll(mHold);
        outputFile << mod_exp(M,e,encrypN) << " ";
    }
}
long long commands::mod_exp(long long base, long long exponent, long long mod) 
{
    long long result = 1;
    base = base % mod;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exponent /= 2;
    }
    return result;
}