//
//  main.cpp
//  Assignment3
//
//  Created by 郑昊 on 2016-11-15.
//  Copyright © 2016 haozheng. All rights reserved.
//

#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm> // for std::copy

using namespace std;

bool solve(vector<string> goal, vector<string> kb);

int main()
{
    
    
    ifstream myfile("data2.txt");
    const size_t SIZE = 30;
    string line[SIZE]; // creates SIZE empty strings
    size_t i=0;
    while(!myfile.eof() && i < SIZE) {
        getline(myfile,line[i]); // read the next line into the next string
        ++i;
    }
    size_t numLines = i;
    cout << numLines << endl;
    for (i=0; i < numLines; ++i) {
        cout << i << "--" << line[i]<<endl;     }
    
    // get the goal and put it into a vector
    vector<string> goal;
    
    goal.push_back(line[0]);
    // put the rules in a vector of string
    vector<string> kb;
    for (int i = 1; i < numLines; i++) {
        kb.push_back(line[i]);
    }
    
    for (int i=0; i<numLines-1; i++) {
        kb[i].erase(remove(kb[i].begin(), kb[i].end(), ' '), kb[i].end());
    }
    
    for (int i = 0; i < numLines; i++) {
        cout << kb[i] << endl;
    }
    
    bool result = solve(goal, kb);

    cout << result << endl;
    return 0;
    
}
    
bool solve(vector<string> goal, vector<string> kb){
    if (goal[0].size() == 0) {
        return true;
    }
    else{
        //get the first element of the goal, and store the rest
        char front = goal[0][0];
       
        //string rest = goal[0].erase(goal[0].begin());
        
        //for each r in rules where head(r) = a
        for (int i = 0; i < kb.size(); i++) {
            char kb_front = kb[i][0];
            cout << "goal: "<< goal[0] << endl;
            if (kb_front == front) {
                vector<string> next_goal;
                if (goal[0].size() == 1) {// eg.just r, no rest part,just append the body of the rule
                    // if the rule's body is 0 which means example p=p or q=q
                    // then just return true
                    if (kb[i].size() == 1) {
                        return true;
                    }
                    // otherwise push the body of the rule to the next_goal
                    next_goal.push_back(kb[i].substr(1));
                    if (solve(next_goal, kb) == true) {
                        return true;
                    }
                    
                }
                else{// rest of goal is not empty
                    // if kb[i] is of size 1, just append the rest of goal to the next_goal
                    if (kb[i].size() == 1) {
                        next_goal.push_back(goal[0].substr(1));
                        
                    }
                    // else kb[i]'s size is not 1, then append the rest of goal to the body of the rule
                    else{
                        next_goal.push_back(kb[i].substr(1) + goal[0].substr(1));

                    }
                    
                    if (solve(next_goal, kb) == true) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}
    
    
    
    


