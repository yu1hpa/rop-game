#include <sys/time.h>
#include "deltatime.h"

void initTime(deltat_t *deltaT){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    deltaT->start = tv.tv_sec + tv.tv_usec * 1.0e-6;
    deltaT->elapsed = 0;
    deltaT->delta = 0;
}

/*
 * ゲームがスタートしてからの時間
 * また、デルタ時間の取得
 * */
void getTime(deltat_t *deltaT){
    static double old = 0;
    struct timeval tv;
    gettimeofday(&tv, NULL);
    double now = tv.tv_sec + tv.tv_usec * 1.0e-6;

    deltaT->elapsed = now - deltaT->start;
    deltaT->delta = now - old;
    old = now;
}

/*
 * sec[秒]の範囲に正規化
 * */
double normDelta(deltat_t deltaT, double sec){
    return deltaT.delta / sec;
}
