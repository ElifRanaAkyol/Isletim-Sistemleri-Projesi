#include <stdio.h>
#include "scheduler.h"
//Her görev için farklı renk içeren dizi. Terminal çıktısında görevleri renkli göstermek için kullanılır.
char *colors[] = {"\x1b[31m", "\x1b[32m", "\x1b[33m", "\x1b[34m", "\x1b[35m", "\x1b[36m", "\x1b[37m"};

void vUserTask(void *pvParameters) {
    TaskInfo *pxTaskInfo = (TaskInfo *)pvParameters;

    while (pxTaskInfo->remaining_time > 0) {
        // Bu görev sadece dispatcher izin verdiğinde çalışır
        vTaskDelay(pdMS_TO_TICKS(1000)); 
    }
    vTaskDelete(NULL);
}