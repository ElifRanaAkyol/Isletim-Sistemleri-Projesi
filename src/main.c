#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "scheduler.h"

TaskInfo task_list[100];
int task_count = 0; //toplam görev sayısı

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Kullanım: ./freertos_sim giris.txt\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Dosya açma hatası");
        return 1;
    }

    // Dosyadan satır okur, görevleri listeye ekler
    while (fscanf(file, "%d, %d, %d", &task_list[task_count].arrival_time, 
                  &task_list[task_count].priority, 
                  &task_list[task_count].burst_time) != EOF) {
        task_list[task_count].id = task_count;
        task_list[task_count].remaining_time = task_list[task_count].burst_time;
        task_list[task_count].color = colors[task_count % 6];
        task_count++;
    }
    fclose(file);

    // dispatcher görevini en öncelikli oluşur
    xTaskCreate(vDispatcherTask, "Dispatcher", configMINIMAL_STACK_SIZE * 2, 
                NULL, configMAX_PRIORITIES - 1, NULL);

    vTaskStartScheduler(); // zamanlayıcı başlar

    for (;;);
    return 0;
}