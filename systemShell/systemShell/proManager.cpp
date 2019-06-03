//
//  proManager.cpp
//  systemExperiment
//
//  Created by kkyou on 2019/5/11.
//  Copyright © 2019 kkyou. All rights reserved.
//
#include "proManager.hpp"

using namespace std;

Process::Process(){
}

Process::Process(string pid, Process* father, prPriority priority){
    this->pid = pid;
    this->state = Ready;
    this->father = father;
    this->priority = priority;
    for (int i = 0; i < 4; i++) {
        resUse[i] = 0;
        resNeed[i] = 0;
    }
}

Process::Process(string pid, prPriority priority){
    this->pid = pid;
    this->state = Ready;
    this->priority = priority;
    for (int i = 0; i < 4; i++) {
        resUse[i] = 0;
        resNeed[i] = 0;
    }
}
void Process::set(string pid, prPriority priority){
    this->pid = pid;
    this->state = Ready;
    this->priority = priority;
    for (int i = 0; i < 4; i++) {
        resUse[i] = 0;
        resNeed[i] = 0;
    }
}

void Process::set(string pid, Process* father, prPriority priority){
    this->pid = pid;
    this->state = Ready;
    this->father = father;
    this->priority = priority;
    for (int i = 0; i < 4; i++) {
        resUse[i] = 0;
        resNeed[i] = 0;
    }
}

void Process::delProcess(){
    this->state = Del;          //进程状态为删除
    //scheduler();                //调用，切换进程
    refreshList(this->pid);     //从就绪队列和阻塞队列中删除该进程指针
    for (int i = 0; i < 4; i++){ //释放资源
        if (resUse[i] != 0) Res[i].justRelease(resUse[i]);
    }
    for (int i = 0; i < children.size(); i++){
        children[i]->delProcess();
    }
    children.clear();           //递归删除子进程
}

void Process::blockThis(int resKind){
    state = Block;
    RL[priority].erase(RL[priority].begin());
    BL[resKind - 1].push_back(this);
    //rmFromRL();
}

void Process::rmFromRL(){
    RL[priority].erase(RL[priority].begin());
}

void scheduler(){
    for (int i = 2; i >= 0; i--){ //init进程不会被阻塞
        int idx = 0;

        if (RL[i].size() == 0) continue;
        if (i == runningPro->priority && runningPro->state == Del) idx = 1;

        if (runningPro->priority < RL[i][idx]->priority || runningPro->state != Running){ //抢占进程
            if (runningPro->state == Running) runningPro->state = Ready;
            if (runningPro->state == Ready){
                RL[runningPro->priority].push_back(runningPro); //压入就绪队列队尾
                RL[runningPro->priority].erase(RL[runningPro->priority].begin()); //从队首移除
            }
            RL[i][idx]->state = Running;
            runningPro = RL[i][idx];
            break;
        }
    }
    printf("Running Process: %16s\n", runningPro->pid.c_str()); //打出当前运行进程名
}

void timeOut(){
    runningPro->state = Ready;
    scheduler();
}

void createPro(string pid, prPriority priority){
    /*TL.push_back(Process(pid, runningPro, priority)); 

    RL[TL[TL.size()-1].priority].push_back(&TL[TL.size()-1]); 
    runningPro->children.push_back(&TL[TL.size()-1]);
    for (int i = 0; i < TL.size(); i++){
        if (TL[i].pid == runningPro->pid) TL[i].children.push_back(&TL[TL.size()-1]);
    }*/
    TL[tlIdx].set(pid, runningPro, priority);
    RL[TL[tlIdx].priority].push_back(&TL[tlIdx]);
    runningPro->children.push_back(&TL[tlIdx]);

    tlIdx++;
    scheduler();
}

void destroyPro(string pid){
    for (int i = 0; i < tlIdx/*TL.size()*/; i++){
        if (TL[i].pid == pid){
            TL[i].delProcess();
        }
    }
    scheduler();                //调用，切换进程
}

void listPro(){
    printf("=============================================\n");
    printf("%-16s\t%s %s\n", "Process", "Priority", "State");
    printf("=============================================\n");
    printf("All Process::\n");
    for (int i = 0; i < tlIdx; i++){
        if (TL[i].state != Del) //printf("%-16s\n", TL[i].pid.c_str());
            printf("%-16s\t%d\t%d\n", TL[i].pid.c_str(), TL[i].priority, TL[i].state);
    }
    if (RL[1].size() != 0)  printf("ReadyList User:\n");
    for (int i = 0; i < RL[1].size(); i++){
        //printf("%-16s\n", RL[1][i]->pid.c_str());
        printf("%-16s\t%d\t%d\n", RL[1][i]->pid.c_str(), RL[1][i]->priority, RL[1][i]->state);
    }
    if (RL[2].size() != 0) printf("ReadyList System:\n");
    for (int i = 0; i < RL[2].size(); i++){
        //printf("%-16s\n", RL[2][i]->pid.c_str());
        printf("%-16s\t%d\t%d\n", RL[2][i]->pid.c_str(), RL[2][i]->priority, RL[2][i]->state);
    }
    if (BL[0].size() != 0) printf("BlockList res1:\n");
    for (int i = 0; i < BL[0].size(); i++){
        //printf("%-16s\n", BL[0][i]->pid.c_str());
        printf("%-16s\t%d\t%d\n", BL[0][i]->pid.c_str(), BL[0][i]->priority, BL[0][i]->state);
    }
    if (BL[1].size() != 0) printf("BlockList res2:\n");
    for (int i = 0; i < BL[1].size(); i++){
        printf("%-16s\n", BL[1][i]->pid.c_str());
    }
    if (BL[2].size() != 0) printf("BlockList res3:\n");
    for (int i = 0; i < BL[2].size(); i++){
        printf("%-16s\n", BL[2][i]->pid.c_str());
    }
    if (BL[3].size() != 0) printf("BlockList res4:\n");
    for (int i = 0; i < BL[3].size(); i++){
        printf("%-16s\n", BL[3][i]->pid.c_str());
    }
}

void refreshList(string pid){
    for (int i = 1; i < 3; i++){ //移除已Del的
        for (int j = 0; j < RL[i].size(); j++){
            if (RL[i][j]->pid == pid) {
                RL[i].erase(RL[i].begin() + j);
            }
        }
    }
    for (int i = 0; i < 4; i++){//移除已Del的
        for (int j = 0; j < BL[i].size(); j++){
            if (BL[i][j]->pid == pid) {
                BL[i].erase(BL[i].begin() + j);
            }
        }
    }
}
