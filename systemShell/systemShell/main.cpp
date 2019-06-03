//
//  main.cpp
//  systemShell
//
//  Created by kkyou on 2019/5/11.
//  Copyright © 2019 kkyou. All rights reserved.
//
#include "systemExperiment.hpp"
#include "proManager.hpp"
#include "resManager.hpp"

#define PRINT_PS1()\
    printf("%s", PS1);

using namespace std;

/*就绪队列/阻塞队列/时间线/正在运行进程*/
vector<Process*> RL[3]; //就绪进程指针队列，每种优先级对应一个就绪队列
vector<Process*> BL[4]; //阻塞进程指针队列，每种资源对应一个阻塞队列
Process* runningPro;    //正在运行的进程
Process TL[50];         //用来保存所有创建的进程
int tlIdx(0);           //TL指针，指向最新创建的进程

/*初始化资源*/
Resource Res[4] = {
    Resource("res1", 1, 1),
    Resource("res2", 2, 2),
    Resource("res3", 3, 3),
    Resource("res4", 4, 4)
};
const char PS1[] = "shell>";

void initProgram();
void runFrontEnd(int, const char*[]);
void quit();

int main(int argc, const char * argv[]) {
    runFrontEnd(argc, argv); //运行前端解释程序

    return 0;
}

void initProgram(){
    system("clear");
    printf("==========================Welcome==========================\n");
    system("./init.sh");
    printf("===========================================================\n");

    /*
    TL.push_back(Process("init", Init)); //创建0号系统进程
    runningPro = &TL[TL.size()-1];
    */
    TL[0].set("init", Init); tlIdx++;
    runningPro = TL;
    RL[0].push_back(&TL[0]);
    
    scheduler();
}

void runFrontEnd(int argc, const char * argv[]){
    enum Mode{explain, readFile} mode = argc == 1 ? explain : readFile;
    string cmd, id;
    char cCmd[10], cId[10];
    int iCmd;

    initProgram();
    /*if (mode == readFile){
        string readFile = "./myshell < ";
        readFile += argv[2];
        system(readFile.c_str());
        return;
    }*/

    while(1){
        PRINT_PS1();
        scanf("%s", cCmd); cmd = cCmd;
        if (cmd == "quit") {
            quit();
            return; //退出
        }
        else if (cmd == "to"){ //时间片用完
            timeOut();
        } else if (cmd == "ls"){ //列出所有进程
            listPro();
        } else{
            scanf("%s", cId);
            if (cmd == "cr"){ //创建进程
                scanf("%d", &iCmd);
                createPro(cId, (prPriority)iCmd);
            } else if (cmd == "de"){ //删除进程
                destroyPro(cId);
            } else if (cmd == "req"){ //请求资源
                scanf("%d", &iCmd);
                requestRes(cId, iCmd);
            } else if (cmd == "rel"){ //释放资源
                scanf("%d", &iCmd);
                releaseRes(cId, iCmd);
            }
        }
    }
}

void quit(){
    for (int i = 0; i < 3; i++) RL[i].clear();
    for (int i = 0; i < 4; i++) BL[i].clear();
}
