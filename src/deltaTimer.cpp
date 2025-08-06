#include "include/DeltaTimer.h"

void DeltaTimer_Init(DeltaTimer* timer) {
    timer->lastCounter = SDL_GetPerformanceCounter();
    timer->deltaTime = 0.0;
    timer->totalTime = 0.0;
    timer->frequency = (double)SDL_GetPerformanceFrequency();
}

void DeltaTimer_Update(DeltaTimer* timer) {
    Uint64 now = SDL_GetPerformanceCounter();
    Uint64 elapsed = now - timer->lastCounter;
    timer->lastCounter = now;

    timer->deltaTime = (double)elapsed / timer->frequency;
    timer->totalTime += timer->deltaTime;
}

double DeltaTimer_GetDeltaTime(DeltaTimer* timer) {
    return timer->deltaTime;
}

double DeltaTimer_GetTotalTime(DeltaTimer* timer) {
    return timer->totalTime;
}
