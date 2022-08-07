#pragma once

typedef struct DeltaTime {
    double start;
    double elapsed;
    double delta;
}deltat_t;

void initTime(deltat_t*);
void getTime(deltat_t*);
double normDelta(deltat_t, double);
