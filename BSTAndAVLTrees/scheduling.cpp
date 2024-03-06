#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <unordered_map>
#include <algorithm>
#include "bst.h"
#include "avlbst.h"
//print schedule fuctnion
void printSchedule(AVLTree<int, int>& examTree) 
{
    for(BinarySearchTree<int, int>::iterator it = examTree.begin(); it != examTree.end(); ++it) 
    {
        std::cout << it->first << ": " << it->second << std::endl;
    }
}
//scheduling function that assigns timeslots...lots of args....
bool scheduling(int currExam, int totalExams, std::vector<int>& exams, AVLTree<int, int>& examTree, int domain, const std::unordered_map<std::string, std::vector<int>>& classes)
{
    //BC: if currExam (counter) = total exams were done
    if(currExam == totalExams)
    {
        std::cout << "Schedule complete:" << std::endl;
        printSchedule(examTree);
        return true;
    }
    //is exam already shceduled?
    if(examTree.find(exams[currExam]) != examTree.end()) 
    {
        //if it is move on!
        return scheduling(currExam + 1, totalExams, exams, examTree, domain, classes);
    }
    //else go thru domain (1-# of timeslots)
    for(int currentTimeSlot = 1; currentTimeSlot <= domain; currentTimeSlot++)
    {
        bool conflict = false;
        //look for conflicts
        for(BinarySearchTree<int, int>::iterator it = examTree.begin(); it != examTree.end(); ++it) 
        {
            if(it->second == currentTimeSlot)
            {
                int conflictingClass = it->first;
                //check for students with same timeslot exams (BAD)
                for(const auto& student : classes)
                {
                    const std::vector<int>& studentClasses = student.second;
                    if(std::find(studentClasses.begin(), studentClasses.end(), conflictingClass) != studentClasses.end() &&
                        std::find(studentClasses.begin(), studentClasses.end(), exams[currExam]) != studentClasses.end()) 
                    {
                        //CONFLICTING CLASSES!
                        conflict = true;
                        break;
                    }
                }
                if(conflict)
                {
                    //move on to diff timeslot
                    break;
                }
            }
        }
        //insert + move on 
        if(!conflict) 
        {
            examTree.insert(std::make_pair(exams[currExam], currentTimeSlot));
            if(scheduling(currExam + 1, totalExams, exams, examTree, domain, classes)) 
            {
                return true;
            }
            examTree.remove(exams[currExam]);
        }
    }
    //NO SOLTION!
    return false;
}

int main(int argc, char* argv[]) 
{
    std::ifstream input(argv[1]);
    //so we can check if students have same classes at same timeslot
    std::unordered_map<std::string, std::vector<int>> studentClasses;
    //hold exams (no dupes)
    std::vector<int> exams;
    //first line
    int numExams;
    int numStudents;
    int numSlots;
    std::string firstLine;
    //fill in first line variables
    if(std::getline(input, firstLine)) 
    {
        std::stringstream ss(firstLine);
        ss >> numExams;
        ss >> numStudents;
        ss >> numSlots;
    }
    //keep reading + filling vector/map
    std::string line;
    while(std::getline(input, line))
    {
        std::stringstream ss(line);
        std::string name;
        if(!(ss >> name))
        {
            continue;
        }
        int num;
        while(ss >> num) 
        {
            //fill vector/map of exams
            studentClasses[name].push_back(num);
            exams.push_back(num);
        }
    }
    input.close();
    //sort exams
    std::sort(exams.begin(), exams.end());
    //get unqiue exams
    std::vector<int>::iterator last = std::unique(exams.begin(), exams.end());
    //delete dupes
    exams.erase(last, exams.end());
    AVLTree<int, int> avl;
    //call rec
    if(!scheduling(0, numExams, exams, avl, numSlots, studentClasses)) 
	{
        std::cout << "No valid solution :(" << std::endl;
    }
    //DONE!
    return 0;
}