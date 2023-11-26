#include "commands.h"
#include <fstream>
#include <cmath>
#include <numeric>


void commands::decryption(std::string inputFile, std::string outputFile)
{
    actualDecrypProcess(inputFile, outputFile);
}
long long commands::findDecrypKey()
{
    //find gcd
    e = 65537;
    long long gcd = euclideanAlgorithm(P-1, Q-1);
    long long L = (P-1)*(Q-1) /gcd;
    if(L <= e)
    {
        std::cout << "ERROR: small key";
    }
    long long d = extendedEuclideanAlgorithm(e, L);
    return d;
}
void commands::actualDecrypProcess(std::string inputFile, std::string outputFile)
{
    long long funcN = P * Q;
    long long dKey = findDecrypKey();
    long long C;
    std::string associatedLetter;
    std::ifstream in(inputFile); // Open the input file
    std::ofstream out(outputFile);
    long long mSize;
    long long oldSize;
    long long it = 0;
    //repeat until decrypted
    while(in >> C)
    {
        M = mod_exp(C,dKey,funcN);
        //conv M to x letters and spaces
        std::string numM = std::to_string(M);
        if((numM.size())%2 != 0)
        {
            numM = "0" + std::to_string(M);
        }
        mSize = numM.size();
        //check if Ms are all the same size
        if(mSize != oldSize && it != 0)
        {
            long long sizeDif = oldSize - mSize;
            for(int i = 0; i < sizeDif; i++)
            {
                numM = "0" + numM;
            }
        }
        mSize = numM.size();
        for(long long i = 0; i < static_cast<long long int>(numM.size()); i +=2)
        {
            std::string lookUp;
            lookUp = numM[i];
            lookUp = lookUp + numM[i+1];
            if(valueLetterPairings.find(lookUp) != valueLetterPairings.end()) 
            {
                associatedLetter = valueLetterPairings[lookUp];
            }
            out << associatedLetter;
        }
        oldSize = mSize;
        it++;
    }
    out << std::endl;
    in.close();
}
long long commands::euclideanAlgorithm(long long p, long long q)
{
    //find gcd
    long long largest = p;
    long long smallest = q;
    if(largest < q)
    {
        largest = q;
        smallest = p;
    }
    long long quotient = (largest/smallest);
    long long rem = (largest%smallest);
    long long old_rem = rem;
    while(rem != 0)
    {
        largest = smallest;
        smallest = rem;
        quotient = (largest/smallest);
        old_rem = rem;
        rem = (largest%smallest);
    }
    return old_rem;
}
long long commands::extendedEuclideanAlgorithm(long long E, long long L)
{
    //step 1
    long long s = 0;
    long long old_s = 1;
    //step 2
    long long t = 1;
    long long old_t = 0; 
    //step 3
    long long r = E;
    long long old_r = L; //should be = to L;
    //repeat until r == 0
    while(r != 0)
    {
        //step 4
        long long quotient = old_r/r;
        //step 5
        long long temp = r;
        //step 6
        r = old_r - quotient * r;
        //step 7
        old_r = temp;
        //step 8
        temp = s;
        //step 9
        s = old_s - quotient * s;
        //step 10
        old_s = temp;
        //step 11
        temp = t;
        //step 12
        t = old_t - quotient * t;
        //step 13
        old_t = temp;
    }
    long long gcd = old_r;
    if(gcd != 1)
    {
        std::cout << "BAD VALUES";
    }
    long long dKey = old_t;
    while(dKey < 0 && dKey < e*L)
    {
        dKey += e*L;
    }
    return dKey;
}