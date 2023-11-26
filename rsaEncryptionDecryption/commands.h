#include <iostream>
#include <unordered_map>
class commands
{
    public:
        //ctor
        commands(long long p, long long q);
        //encryp command
        void encryption(std::string filename, long long n, std::string message);
        //decryp command
        void decryption(std::string inputFile, std::string outputFile);
        //find decryption key
        long long findDecrypKey();
        long long euclideanAlgorithm(long long p, long long q);
        long long extendedEuclideanAlgorithm(long long E, long long L);
        //decryp message
        void actualDecrypProcess(std::string inputFile, std::string outputFile);
        //convert message
        void convMessage();
        long long mod_exp(long long base, long long exponent, long long mod);
        
    private:
        long long e;
        long long x;
        long long C;
        long long M;
        long long P;
        long long Q;
        long long encrypN;
        std::string word;
        std::string outputFileName;
        std::unordered_map<char,std::string> letterValuePairings;
        std::unordered_map<std::string,char> valueLetterPairings;
};