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
    int n = size/2;
    int maxProbe = 0;
    int totalProbes = 0;
    std::vector<int> maxProbeStore;
    std::vector<int> halfFullAverages;
    std::vector<int> fourthFullAverages;

    for(int i = 0; i < 1000; i++)
    {
        Hashtable<int> hashtable(debug, size);
        for(int j = 0; j < n; j++)
        {
            probe = hashtable.add("",n);
            if(n/3203.0 <= 0.5 && n/3203.0 > 0.25)
            {
                halfFullAverages.push_back(probe);
            }
            if(n/3203.0 <= 0.25)
            {
                fourthFullAverages.push_back(probe);
            }
            if(probe > maxProbe)
            {
                maxProbe = probe;
            }
            totalProbes++;
        }
        maxProbeStore.push_back(maxProbe);
        maxProbe = 0;
        totalProbes = 0;
    }
    for(int i = 0; i < maxProbeStore.size();  i++)
    {
        std::cout << maxProbeStore[i] << " ";
    }
    std::cout << std::endl;
    int totalHalf =  0;
    for(int i = 0; i < halfFullAverages.size();  i++)
    {
        totalHalf += halfFullAverages[i];
    }
    double size = halfFullAverages.size();
    std::cout << totalHalf/size << " probes on average when 1/2 full" << std::endl;

    int totalFourth =  0;
    for(int i = 0; i < fourthFullAverages.size();  i++)
    {
        totalFourth += fourthFullAverages[i];
    }
    double sizeFourth = fourthFullAverages.size();
    std::cout << totalFourth/sizeFourth << " probes on average when 1/4 full" << std::endl;
}