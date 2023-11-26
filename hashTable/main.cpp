#include "Hashtable.h"
#include <iostream>
#include <sstream >
#include <vector>
#include <cstdlib>
#include <ctime>

int main() 
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    bool debug = true;
    int size = 3203;
    int probe = 0;
    int n = 0;
    int maxProbe = 0;
    std::vector<std::pair<int,int>> maxProbeStore;
    std::vector<int> halfFullAverages;
    std::vector<int> fourthFullAverages;
    int pairNumberOfItems = 0;

    for(int i = 0; i < 1000; i++)
    {
        Hashtable<int> hashtable(debug, size);
        for(int j = 0; j < size; j++)
        {
            n++;
            std::string result;
            for(int i = 0; i < 28; ++i) 
            {
                int random_number = std::rand() % 26 + 1;
                char addToString = 'a' + random_number - 1;
                // Append the character to the result string
                result += addToString;
            }
            probe = hashtable.add(result,n);
            if(n/3203.0 <= 0.5 && n/3203.0 > 0.45)
            {
                halfFullAverages.push_back(probe);
            }
            if(n/3203.0 <= 0.25 && n/3203.0 > 0.2)
            {
                fourthFullAverages.push_back(probe);
            }
            if(probe > maxProbe)
            {
                maxProbe = probe;
                pairNumberOfItems = j;
            }
        }
        std::pair<int,int> maxProbePairN;
        maxProbePairN.first = maxProbe;
        maxProbePairN.second = pairNumberOfItems;
        maxProbeStore.push_back(maxProbePairN);
        maxProbe = 0;
        pairNumberOfItems = 0;
    }
    for(size_t i = 0; i < maxProbeStore.size();  i++)
    {
        std::cout << "MaxProbe: " << maxProbeStore[i].first << "  n:" << maxProbeStore[i].second << std::endl;
    }
    int totalHalf =  0;
    for(size_t  i = 0; i < halfFullAverages.size();  i++)
    {
        totalHalf += halfFullAverages[i];
    }
    double sizeHalf = halfFullAverages.size();
    std::cout << totalHalf/sizeHalf << " probes on average when 1/2 full" << std::endl;

    int totalFourth =  0;
    for(size_t  i = 0; i < fourthFullAverages.size();  i++)
    {
        totalFourth += fourthFullAverages[i];
    }
    double sizeFourth = fourthFullAverages.size();
    std::cout << totalFourth/sizeFourth << " probes on average when 1/4 full" << std::endl;
    
    std::cout << "------------------------------------------" << std::endl;
}