#include "resManager.hpp"

void Resource::requestRes(int requestNum){
    if (requestNum <= status){ //剩余资源足够
        status -= requestNum;
        runningPro->resUse[this->resKind-1] += requestNum; //压入占用资源
    } else{ //剩余资源不足
        runningPro->blockThis(resKind);//阻塞当前进程
        runningPro->resNeed[this->resKind-1] += requestNum; //压入所需资源数
    }
    scheduler();
}

void Resource::releaseRes(int releaseNum){
    status += releaseNum;
    runningPro->resUse[this->resKind] -= releaseNum;
    int len = BL[resKind-1].size();
    for (int i = 0; i < len; i++){
        if (BL[resKind-1][0]->resNeed[resKind-1] <= status){ //阻塞队列队首可获取资源
            status -= BL[resKind-1][0]->resNeed[resKind-1]; //资源数量减少
            BL[resKind-1][0]->state = Ready; //进入就绪状态
            BL[resKind-1][0]->resUse[resKind-1] = BL[resKind-1][0]->resNeed[resKind-1]; //记录占用资源
            BL[resKind-1][0]->resNeed[resKind-1] = 0; //不需等待该资源
            RL[BL[resKind-1][0]->priority].push_back(BL[resKind-1][0]); //压入就绪队列
            BL[resKind-1].erase(BL[resKind-1].begin()); //从资源阻塞队列中移除
        } else break;
    }
    scheduler(); 
}

void requestRes(string rid, int num){
    for (int i = 0; i < 4; i++){
        if (Res[i].rid == rid){
            Res[i].requestRes(num);
            return;
        }
    }
}

void releaseRes(string rid, int num){
    for (int i = 0; i < 4; i++){
        if (Res[i].rid == rid){
            Res[i].releaseRes(num);
            return;
        }
    }
}
