#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "FreeRTOS.h"
#include "task.h"

typedef struct {
    int id; //görev numarası
    int arrival_time; //görevin sisteme gelme zamanı
    int priority;      // 0: RT, 1, 2, 3: User
    int burst_time;    //görevin toplam çalışma süresi
    int remaining_time; //görevin kalan çalışma süresi
    int wait_time;     // Bekleme süresi
    TaskHandle_t handle;
    char* color;       
} TaskInfo;

extern char *colors[]; //renk dizisine erişim sağlar
void vDispatcherTask(void *pvParameters);
void vUserTask(void *pvParameters);

#endif