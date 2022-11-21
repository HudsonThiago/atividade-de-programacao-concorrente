#ifndef SEMAFORO_H
#define SEMAFORO_H

#include <semaphore.h>

class Semaforo
{
public:
    static sem_t semaforo;
    Semaforo();
};

#endif // SEMAFORO_H
