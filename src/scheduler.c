#include <stdio.h>
#include "scheduler.h"

extern TaskInfo task_list[100];
extern int task_count;

void vDispatcherTask(void *pvParameters) {
    float current_time = 0.0;
    TaskInfo *running_task = NULL;

    while (1) {
        // yeni gelenleri sisteme alıyoruz
        
        for (int i = 0; i < task_count; i++) {
            if (task_list[i].arrival_time == (int)current_time && task_list[i].handle == NULL) { //Görevi oluştur
                xTaskCreate(vUserTask, "Task", configMINIMAL_STACK_SIZE, &task_list[i], tskIDLE_PRIORITY + 1, &task_list[i].handle); //Askiya al
                vTaskSuspend(task_list[i].handle);
            }
        }

        // 2. zaman aşımı kontrolü
        for (int i = 0; i < task_count; i++) {
            if (task_list[i].remaining_time > 0 && task_list[i].handle != NULL) {
                if ((int)current_time - task_list[i].arrival_time >= 20) {
                    printf("%s%.4f sn proses zamanaşımı (id:%04d öncelik:%d kalan süre:%d sn)\x1b[0m\n", 
                           task_list[i].color, current_time, task_list[i].id, task_list[i].priority, task_list[i].remaining_time);
                    vTaskDelete(task_list[i].handle); //görevi sil
                    task_list[i].remaining_time = 0;
                    if (running_task == &task_list[i]) running_task = NULL;
                }
            }
        }

        // 3. en uygun görevi seçer
        TaskInfo *next_task = NULL;
        for (int i = 0; i < task_count; i++) {
            if (task_list[i].remaining_time > 0 && task_list[i].arrival_time <= (int)current_time) {
                if (next_task == NULL || task_list[i].priority < next_task->priority) { //en yüksek öncelikliyi seç
                    next_task = &task_list[i];
                }
            }
        }

        // 4. bağlam değişimi ve mesajlar
        if (next_task != NULL) {
            if (running_task != next_task) {
                if (running_task != NULL && running_task->remaining_time > 0) { //eskiyi durdur
                    vTaskSuspend(running_task->handle);
                    printf("%s%.4f sn proses askıda     (id:%04d öncelik:%d kalan süre:%d sn)\x1b[0m\n", 
                           running_task->color, current_time, running_task->id, running_task->priority, running_task->remaining_time);
                }
                
                vTaskResume(next_task->handle); //yeniyi başlat
                printf("%s%.4f sn proses başladı    (id:%04d öncelik:%d kalan süre:%d sn)\x1b[0m\n", 
                       next_task->color, current_time, next_task->id, next_task->priority, next_task->remaining_time);
            } else {
                printf("%s%.4f sn proses yürütülüyor (id:%04d öncelik:%d kalan süre:%d sn)\x1b[0m\n", 
                       next_task->color, current_time, next_task->id, next_task->priority, next_task->remaining_time);
            }

            //  simülasyonu 1 saniye ilerletir ve çalışan görevin kalan süresini 1 azaltır.
            vTaskDelay(pdMS_TO_TICKS(1000));
            current_time += 1.0;
            next_task->remaining_time--;

            // geri besleme (öncelik 0 değilse ve bitmediyse önceliği düşür)
            if (next_task->priority > 0 && next_task->remaining_time > 0) {
                if (next_task->priority < 3) next_task->priority++;
            }

            if (next_task->remaining_time == 0) {
                printf("%s%.4f sn proses sonlandı    (id:%04d öncelik:%d kalan süre:%d sn)\x1b[0m\n", 
                       next_task->color, current_time, next_task->id, next_task->priority, next_task->remaining_time);
                running_task = NULL;
            } else {
                running_task = next_task;
            }
        } else {
            // yapacak iş yoksa zaman ilerler
            vTaskDelay(pdMS_TO_TICKS(1000));
            current_time += 1.0;
        }
        
        
    }
}