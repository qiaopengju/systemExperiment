#ifndef proManager_h 
#define proManager_h

#ifndef systemExperiment_h
#include "systemExperiment.hpp"
#endif

extern vector<Process*> RL[3];
extern vector<Process*> BL[4];
//extern vector<Process> TL;
extern Process lastCreatePro;

extern Process TL[50];
extern int tlIdx;

void listPro();
void scheduler();
void timeOut();
void createPro(string, prPriority);
void destroyPro(string);
void requestRes(string, int);
void releaseRes(string, int);
void refreshList(string);
#endif
