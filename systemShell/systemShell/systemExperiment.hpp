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

enum prState{Ready,Running, Block, Del}; //进程状态：就绪/运行/阻塞/删除
enum prPriority{Init, User, System};    //进程优先级: 初始化/用户/系统

class Process{ //定义进程类
    public:
        Process* father;            //父进程
        vector<Process*> children;  //子进程
        string pid;                 //进程名
        prState state;              //进程所处状态
        prPriority priority;        //进程优先级
        int resUse[4];              //进程正在使用的资源
        int resNeed[4];             //进程需要的资源，未获得

        Process();
        Process(string pid, prPriority priority);
        Process(string pid, Process* father, prPriority priority);
        void set(string pid, prPriority priority);
        void set(string pid, Process* father, prPriority priority);
        void delProcess();          //删除进程
        void blockThis(int);        //阻塞进程
        void rmFromRL();            //从就绪队列中移除
};
class Resource{ //定义资源类
    public:
        string rid;                 //资源名
        int resKind;                //资源类型
        int status;                 //资源剩余量

        Resource(string rid, int resKind, int status){
            this->rid = rid;
            this->resKind = resKind;
            this->status = status;
        }
        void requestRes(int);       //当前进程请求资源
        void releaseRes(int);       //当前进程释放资源
        void justRelease(int);      
};

extern Process* runningPro;         //当前运行的进程
extern Resource Res[4];             //四种资源
#endif /* systemExperiment_h */
