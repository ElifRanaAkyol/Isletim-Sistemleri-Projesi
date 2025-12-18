CC = gcc

CFLAGS = -I./src \
         -I./FreeRTOS-Kernel/include \
         -I./FreeRTOS-Kernel/portable/ThirdParty/GCC/Posix \
         -I./FreeRTOS-Kernel/portable/ThirdParty/GCC/Posix/utils \
         -D_POSIX_C_SOURCE=200809L \
         -Wall -g

KERNEL_SRC = \
FreeRTOS-Kernel/tasks.c \
FreeRTOS-Kernel/list.c \
FreeRTOS-Kernel/queue.c \
FreeRTOS-Kernel/timers.c \
FreeRTOS-Kernel/event_groups.c \
FreeRTOS-Kernel/portable/ThirdParty/GCC/Posix/port.c \
FreeRTOS-Kernel/portable/ThirdParty/GCC/Posix/utils/wait_for_event.c \
FreeRTOS-Kernel/portable/MemMang/heap_4.c

APP_SRC = \
src/main.c \
src/scheduler.c \
src/tasks.c \
src/utils.c

all: freertos_sim

freertos_sim:
	$(CC) $(CFLAGS) $(KERNEL_SRC) $(APP_SRC) -o freertos_sim -lpthread

clean:
	rm -f freertos_sim
