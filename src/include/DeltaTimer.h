#pragma once

#include <SDL.h>

typedef struct {
    Uint64 lastCounter;
    double deltaTime;         // Seconds between frames
    double totalTime;         // Accumulated time since start
    double frequency;         // SDL frequency as double
} DeltaTimer;

void DeltaTimer_Init(DeltaTimer* timer);
void DeltaTimer_Update(DeltaTimer* timer);
double DeltaTimer_GetDeltaTime(DeltaTimer* timer);
double DeltaTimer_GetTotalTime(DeltaTimer* timer);