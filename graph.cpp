#include <iostream>
#include "graph.h"
#include <sstream>
#include <fstream>
#include <vector>
#include "MinHeap.h"
#include <cctype>

graph::graph(std::string textFile, std::string start, std::string goal)
{
    //capitalizes start and goal word (makes program case insensitive)
    for(char& c: start) 
    {
        c = std::toupper(c);
    }
    for(char& c: goal) 
    {
        c = std::toupper(c);
    }
    //read textFile
    std::ifstream infile(textFile);
    std::string line;
    std::getline(infile, line);
    size = std::stoi(line);
    Node target;
    int startIdx = 0;
    //add all words from file
    for(int i = 0; i < size; i++)
    {
        Node n;
        std::getline(infile, line);
        //capitalize ALL words from file
        for(char& c: line) 
        {
            c = std::toupper(c);
        }
        n.word = line;
        n.idx = i;
        //calcualte h
        n.h = heurisitc(n.word, goal);
        //add to node vector
        adjList.push_back(n);
        if(n.word == start)
        {
            startIdx = i;
        }
        if(n.word == goal)
        {
            target = n;
        }
        //add to wordMap with an index for permutations
        std::pair<std::string, int> newPair(line, i);
        wordMap[newPair.first] = newPair.second;
    }
    //call A*
    graph::AStarSearch(adjList[startIdx], target);
}

void graph::findPossibleWords(Node* current)
{
    Node store = *current;
    Node currentWord = *current;
    //loop through every letter of currentWord
    for(size_t j = 0; j < ((currentWord).word).length(); j++)
    {
        //loop through alphabet array and replace every letter in currentWord
        for(int k = 0; k < 26; k++)
        {
            if((currentWord).word[j] != alphabet[k])
            {
                (currentWord).word[j] = alphabet[k];
                //check if new word is in map
                if(wordMap.find(currentWord.word) != wordMap.end()) 
                {
                    //add to neighbors
                    int mapIdx = wordMap[currentWord.word];
                    ((*current).neighbors).push_back(&adjList[mapIdx]);
                }
            }
            //set currentWord back to orginal state 
            (currentWord).word = (store).word;
        }
    }
}

//calaculates the heuristic of the given word
//by comparing every letter with the goal word
int graph::heurisitc(std::string node, std::string goal)
{
    int h = 0;
    if(node == goal)
    {
        return h;
    }
    for(size_t i = 0; i < node.length(); i++)
    {
        if(node[i] != goal[i])
        {
            h++;
        }
    }
    return h;
}


void graph::AStarSearch(Node start, Node goal)
{
    //find neigbors for ALL nodes
    for(size_t i = 0; i < adjList.size(); i++)
    {
        findPossibleWords(&adjList[i]);
    }
    //set up explored vector
    for(size_t i = 0; i < adjList.size(); i++)
    {
        explored.push_back(false);
    }
    MinHeap<std::string> pq(2);
    start.dist = 0;
    pq.add(start.word, start.dist);
    int counter = 0;
    bool reachGoal = false;
    int expansions = 0;
    Node v = start;
    v.word = pq.peek();
    //loop through minheap until we reach goal or it is empty
    while(!pq.isEmpty() || reachGoal)
    {
        v.word = pq.peek();
        pq.remove();
        //find and grab v's information
        for(size_t i = 0; i < adjList.size(); i++)
        {
            if(adjList[i].word == v.word)
            {
                v = adjList[i];
            }
        }
        //set v to explored
        explored[v.idx] = true;
        if(v.word == goal.word)
        {
            break;
        }
        else
        {
            expansions++;
        }
        //go thru v's neighbors
        for(size_t i = 0; i < v.neighbors.size(); i++)
        {
            Node* w = v.neighbors[i];
            if(!explored[(*w).idx] || (v.dist + 1) < (*w).dist)
            {
                if((*w).word == goal.word)
                {
                    reachGoal = true;
                }
                (*w).dist = v.dist + 1;
                (*w).parent = &v;
                int f = (*w).dist + (*w).h;
                counter = (*w).dist;
                //if not explored set w to explored and add to heap
                if(!explored[(*w).idx])
                {
                    explored[(*w).idx] = true;
                    pq.add((*w).word, f*((*w).word.length()+1)+ (*w).h);
                }
                //if explored subtract from expansions and update w's priority
                else
                {
                    expansions--;
                    pq.add((*w).word,f*((*w).word.length()+1)+ (*w).h);
                }
            }
        }
    }
    //cout results
    if(!reachGoal)
    {
        std::cout << "No transformation" << std::endl;
    }
    else
    {  
        //steps  
        std::cout << counter << std::endl;
    }
    //expansions
    std::cout << expansions << std::endl;
}

