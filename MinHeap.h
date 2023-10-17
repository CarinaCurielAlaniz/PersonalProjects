#include <vector>
#include <utility>
#include <iostream>

template <class T>
  class MinHeap
  {
    public:
      //initalize numKids to make a dtary tree
      MinHeap (int d)
      {
        numKids = d;
      }
      //clean up minHeap
      ~MinHeap ()
      {
        minHeap.clear();
      }
      
      //adds node to end of heap and sorts it
      void add (T item, int priority);
      
      //returns first elemnt of heap (smallest)
      const T & peek () const;
      
      //swaps head and tail and pops new tail, trickles down
      void remove ()
      {
        //minHeap is empty
        if (minHeap.empty()) 
        {
          throw std::runtime_error("Vector is empty!");
        }
        //minHeap has a size of 1
        if(minHeap.size() == 1)
        {
          minHeap.pop_back();
          nodes--;
          idx = (minHeap.size() - 1);
          return;
        }
        std::swap(minHeap[0], minHeap[minHeap.size() - 1]);
        minHeap.pop_back();
        nodes--;
        trickleDown(0);
      }
      
      //move down heap and organize nodes
      void trickleDown(int pos)
      {
        int smallKid = pos;
        for(int i = 1; i <= numKids; i++)
        {
          size_t kid = (pos*numKids)+i;
          if(kid < minHeap.size())
          {
            if(minHeap[kid].second < minHeap[smallKid].second)
            {
              smallKid = kid;
            }
            //A* string tiebreaker
            else if(minHeap[kid].second == minHeap[smallKid].second)
            {
              if(minHeap[kid].first < minHeap[smallKid].first)
              {
                smallKid = kid;
              }
            }
          }
        }
        if(smallKid != pos)
        {
          std::swap(minHeap[smallKid], minHeap[pos]);
          pos = smallKid;
          trickleDown(pos);
        }
      }
    
      //returns true if heap is empty
      bool isEmpty()
      {
        if(minHeap.empty())
        {
          return true;
        }
        return false;
      }
      
    private:
      //current idx
      int idx = 0;
      //current number of nodes
      int nodes = 0;
      //heap
      std::vector<std::pair<T, int>> minHeap;
      //initalized in ctor, dtary
      int numKids = 0;
  };

  template <class T>
  void MinHeap<T>::add (T item, int priority)
  {
    nodes++;
    idx = (minHeap.size() - 1);
    int tempIdx = idx;
    if(!minHeap.empty())
    {
      idx++;
      tempIdx = idx;
    }
    std::pair<T, int> minHeapPair(item, priority);
    minHeap.push_back(minHeapPair);
  
    //check if new node is smaller than its parent
    while((idx > 0 && minHeap[tempIdx].second < minHeap[(tempIdx-1)/numKids].second))
    {
        std::swap(minHeap[tempIdx], minHeap[(tempIdx-1)/numKids]);
        tempIdx = (tempIdx-1)/numKids;
    }
  }

  template <class T>
  const T & MinHeap<T>::peek () const
  {
    //checks if empty if not returns head else it throws an error
    if(minHeap.empty()) 
    {
      throw std::runtime_error("Vector is empty!");
    }
    return minHeap[0].first;
  }