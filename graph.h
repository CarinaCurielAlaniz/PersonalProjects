#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <unordered_map>

//node and all of its edges and information (f,g,h)
struct Node 
{
    std::string word;
    int dist = 0;
    int h = 0;
    int f = 0;
    int idx;
    Node* parent;
    std::vector<Node*> neighbors;
};

class graph
{
    public:
        //graph ctor, reads input from txt file and adds all the words to allWords and makes a node for each word
        graph(std::string textFile, std::string start, std::string goal);  

    private:
        //stores words for fast access
        std::unordered_map<std::string,int> wordMap;
        //stores bools for each node
        std::vector<bool> explored;
        //size of wordMap
        int size;
        //vector storing all of the nodes
        std::vector<Node> adjList;
        //alphabet array for permutations
        char alphabet[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M','N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
        //makes all permutations for each word and if any are valid adds them to the edges vector
        void findPossibleWords(Node* current);
        //calculates h value of Node
        int heurisitc(std::string node, std::string goal);
        //A* Search function
        void AStarSearch(Node start, Node goal);
};