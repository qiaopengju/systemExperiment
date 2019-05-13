//
//  systemShell.hpp
//  systemShell
//
//  Created by kkyou on 2019/5/11.
//  Copyright © 2019 kkyou. All rights reserved.
//

#ifndef systemExperiment_h
#define systemExperiment_h

#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum prState{Running, Ready, Block, Del};
enum prPriority{Init, User, System};

class Process{
    public:
        Process* father;
        vector<Process*> children;
        string pid;
        prState state;
        prPriority priority;
        int resUse[4];
        int resNeed[4];

        Process(string pid, prPriority priority);
        Process(string pid, Process* father, prPriority priority);
        void delProcess();
        void blockThis(int);
        void rmFromRL();
};
class Resource{
    public:
        string rid;
        int resKind;
        int status;

        Resource(string rid, int resKind, int status){
            this->rid = rid;
            this->resKind = resKind;
            this->status = status;
        }
        void requestRes(int);
        void releaseRes(int);
};

extern Process* runningPro;
#endif /* systemExperiment_h */
