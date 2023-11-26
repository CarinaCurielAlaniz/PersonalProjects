#ifndef _HASH_TABLE_H
#define _HASH_TABLE_H
#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>

template<typename T>
class Hashtable
{
public:
	Hashtable(bool debug = false, unsigned int size = 11)
	{
		unbug = debug;
		m = size;
		std::pair<std::string, T> emptyPair;
		for(unsigned int i  = 0; i < m; i++)
		{	
			table.push_back(emptyPair);
		}
		//set up maps (a, 1).....(z, 26)
		for(int i = 1; i < 27; i++)
		{
			//ascii a = 97
			int asciiCode = i + 96;
			char alphabet = static_cast<char>(asciiCode);
			std::pair<char, int> newPair(alphabet, i);
			letterValuePairings[newPair.first] = newPair.second;
		}
	}
	~Hashtable()
	{
	}
	int add(std::string k, const T& val);
	const T& lookup(std::string k) const;
	void reportAll(std::ostream& out) const
	{
		for(size_t i = 0; i < table.size(); i++)
		{
			if(table[i].first != "")
			{
				out << table[i].first << " " << table[i].second << std::endl;
			}
		}
	}
	int hash(std::string k) const
	{
		std::string word = k;
		int values[6] = {0, 0, 0, 0, 0, 0};
		int subVal[5] = {0, 0, 0, 0, 0};
		std::vector<std::string> str;
		std::string newK = "";
		//append spaces if word isnt long enough, allows to make "trojans" into t and rojans
		if(k.size()%6 != 0)
		{
			//append spaces
			int append = 6-(k.size()%6);
            for(int i = 0; i < append; i++) 
            {
                newK += ' '; 
            }
			newK += k;
		}
		else
		{
			newK = k;
		}
		//add the diff substrings to a vector (ex: {t, rojans}) helps with iterations
		for(size_t i = 0; i < newK.size(); i += 6)
		{
			std::string sub = "";
			sub += newK[i];
			sub += newK[i+1];
			sub += newK[i+2];
			sub += newK[i+3];
			sub += newK[i+4];
			sub += newK[i+5];
			str.push_back(sub);
		}

		int its = str.size();
		int val = 0;
		int count = 4-(its-1);
		long long r[5] = {983132572, 1468777056, 552714139, 984953261, 261934300};
		//if NOT debug then generate random numbers
		if(unbug == false)
		{
    		for (int i = 0; i < 5; ++i) {
				long long random_number = std::rand() % 12; // % 12 gives a number between 0 and 11
				r[i] = random_number;
   			}
		}
		int vCount = 0;
		//loop through vector and find the w's
		for(int j = 0; j < its; j++)
		{
			for(int i = 0; i < 6; i++)
			{
				std::string word = str[j];
				char wordLetter = word[i];
				if(letterValuePairings.find(wordLetter) != letterValuePairings.end()) 
				{
					val = letterValuePairings[wordLetter];
				}
				values[vCount] = val;
				vCount++;
			}
			subVal[count] = pow(27,5)*values[0] + pow(27,4)*values[1] + pow(27,3)*values[2] + pow(27,2)*values[3] + 27*values[4] + values[5];;
			count++;
			vCount = 0;
		}
		//actual hash formula:
		long long result = ((r[0]*subVal[0]) + (r[1]*subVal[1]) + (r[2]*subVal[2]) + (r[3]*subVal[3]) + (r[4]*subVal[4])) % m;
		return result;
	}

private:
	void resize()
	{
		unsigned int oldM = m;
		int sizeIdx = -1;
		unsigned int potentialSizes[17] = {11, 23, 47, 97, 197, 397, 797, 1597, 3203, 6421, 12853, 25717, 51437, 102877, 205759, 411527, 823117};
		//check if m is already in array
		for(int i = 0; i < 17; i++)
		{
			if(potentialSizes[i] == m)
			{
				sizeIdx = i+1;
				break;
			}
		}
		// If m is not present, find the index of the nearest larger value
		if(sizeIdx == -1) 
		{
			int nearest = 0;
			for(int i = 0; i < 17; i++)
			{
				if(potentialSizes[i] > m) 
				{
					nearest = i;
					break;  
				}
			}
			sizeIdx = nearest;
		}
		m = potentialSizes[sizeIdx];
		std::vector<std::pair<std::string, T>> newTable;
		std::pair<std::string, T> emptyPair;
		//initalize table
		for(unsigned int i  = 0; i < m; i++)
		{	
			newTable.push_back(emptyPair);
		}
		//rehash in the order of last table
		for(unsigned int i  = 0; i < oldM; i++)
		{
			if(table[i].first != "")
			{	
				int newIdx = hash(table[i].first);
				newTable[newIdx] = table[i];
			}
		}
		table = newTable;
	}
	//private variables
	double loadingFactor = 0;
	bool unbug;
	unsigned int m;
	double n = 0;
	std::vector<std::pair<std::string, T>> table;
    mutable std::unordered_map<char, int> letterValuePairings;
};

template<typename T>
int Hashtable<T>::add(std::string k, const T& val)
{
	n++;
	loadingFactor = n/m;
	//resize if loading factor is above 0.5
	if(loadingFactor > 0.5)
	{
		resize();
	}
	int probes = 0;
	int x = 1;
	int idx = hash(k);
	int finalIdx = idx;
	//keep going till find an open slot
	while(table[finalIdx].first != "")
	{
		finalIdx = (hash(k) + pow(x,2));
		finalIdx = finalIdx%m;
		x++;
		probes++;
	}
	std::pair<std::string, T> insert;
	insert.first = k;
	insert.second = val;
	table[finalIdx] = insert;
	return probes;
}

template<typename T>
const T& Hashtable<T>::lookup(std::string k) const
{
	int idx = hash(k);
	//return first idxs key if k is not present
	if(table[idx].first == "")
	{
		return table[0].second; 
	}
	//if finable return ACTUAL value
	else
	{
		int x = 1;
		int finalIdx = idx;
		while(table[finalIdx].first != k)
		{
			finalIdx = (idx + pow(x,2));
			finalIdx = finalIdx%m;
			x++;
		}	
		return table[finalIdx].second;
	}
}
#endif