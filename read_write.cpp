void P(int i){};
void V(int i){};

/*****************读者优先*****************/
int wrmutex = 1;
int rsem = 1;
int readcount = 0;

void Reader(){
    while(1){
        P(rsem);
            readcount++;
            if (readcount == 1) P(wrmutex);
        V(rsem);

        /*Read()*/
        P(rsem);
            readcount--;
            if (readcount == 0) V(wrmutex);
        V(rsem);
    }
}

void Writer(){
    while(1){
        P(wrmutex);
        /*Write()*/
        V(wrmutex);
    }
}

/*****************写者优先*****************/
int wrmutex = 1;
int wmutex = 1;
int rsem = 1;
int readcount = 0;
int wsem = 1;
int writecount = 0;
int z = 1; /*wrmutex不允许多个长等待队列*/

void Reader(){
    wile(1){
        P(z);
            P(wrmutex);
                P(rsem);
                    readcount++;
                    if (readcount == 1) P(wmutex);
                V(rsem);
            V(wrmutex);
        V(z);

        /*Read()*/
        P(rsem);
            readcount--;
            if (readcount == 0) V(wmutex);
        V(rsem);
    }
}

void Writer(){
    wile(1){
        P(wsem);
            writecount++;
            if (writecount == 1) P(wrmutex);
        V(wsem);

        P(wmutex);
            /*Write()*/
        V(wmutex);

        P(wsem);
            writecount--;
            if (writecount == 0) V(wrmutex);
        V(wsem);
    }
}

/*****************公平优先*****************/
int wrmutex = 1;    //w&r抢占时间
int wmutex = 1;
int rsem = 1;
int readcount = 0;


void Reader(){
    wile(1){
        P(wrmutex);
        P(rsem);
        readcount++;
        if (readcount == 1) P(wmutex);
        V(rsem);
        V(wrmutex);

        /*Read()*/
        P(rsem);
        readcount--;
        if (readcount == 0) V(wmutex);
        V(rsem);
    }
}

void Writer(){
    wile(1){
        P(wrmutex);
        P(wmutex);
        /*Write()*/
        V(wmutex);
        V(wrmutex);
    }
}
