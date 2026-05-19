#include "FreeRTOS.h"
#include "task.h"

#include "FreeRTOSConfig.h"
#include "timelinescheduler.h"


#include "uart.h"

#define TASK_STACK_SIZE 128

void hrt1func(void *param);
void hrt2func(void *param);
void hrt3func(void *param);
void srt1func(void *param);

/* Hooks need to be declared if they are used */
void vApplicationTimelineDeadlineMissedHook( TaskHandle_t xTask );
void vApplicationTimelineTaskKilledHook( TaskHandle_t xTask );

int main(int argc, char **argv){

	(void) argc;
	(void) argv;

    UART_init();

    // const char       *pcTaskName;
    // TaskFunction_t    pxTaskCode;
    // TaskType_t        xType;
    // TickType_t        xStartTime;
    // TickType_t        xEndTime;
    // uint32_t          ulSubframeId;
    // uint16_t          usStackDepth;


    TimelineTaskConfig_t tasks[configTIMELINE_TASK_COUNT] = 
    {
        {"hrt1", hrt3func, TASK_HARD_RT, 0, 3, 0, TASK_STACK_SIZE},
        {"srt1", hrt1func, TASK_HARD_RT, 8, 11, 1, TASK_STACK_SIZE},
        {"srt2", hrt2func, TASK_SOFT_RT, -1, -1, -1, TASK_STACK_SIZE},
        {"srt3", hrt1func, TASK_SOFT_RT, 20, 25, 4, TASK_STACK_SIZE}
    };

    vConfigureScheduler(tasks);

	// Give control to the scheduler
	vTaskStartScheduler();

	// If everything ok should never reach here
    for( ; ; );
}

void hrt1func(void *param){
    (void) param;
    for(int i = 0; i < 10000000000; i++){
        // UART_puts("hrt1");
        for(int j = 0; j < 1000000000; j++){
        // UART_puts("hrt1");
        float a = 95537, b=8476.9;
        volatile float c = 0;
        c = a / b;

        }
    }
    // UART_puts("\n");
    vTaskSuspend(NULL);
}

void hrt2func(void *param){
    (void) param;
        for(int i = 0; i < 10000000000; i++){
        // UART_puts("hrt1");
        for(int j = 0; j < 1000000000; j++){
        // UART_puts("hrt1");
        float a = 95537, b=8476.9;
        volatile float c = 0;
        c = a / b;

        }
    }    
    // UART_puts("\n");
    vTaskSuspend(NULL);
}

void hrt3func(void *param){
    (void) param;
    for(int i = 0; i < 1000; i++){
        // UART_puts("hrt3");
    }
    // UART_puts("\n");
    vTaskSuspend(NULL);
}

void srt1func(void *param){
    (void) param;
    /* Use volatile to prevent the compiler from optimizing the loop away */
    volatile int dummy = 0;
    for(int i = 0; i < 1000; i++){
        for(int j = 0; j < 100; j++){
            float a = 95537, b = 8476.9;
            volatile float c = 0;
            c = a / b;
            dummy += (int)c;
        }
    }
    (void) dummy;
    vTaskSuspend(NULL);
}
