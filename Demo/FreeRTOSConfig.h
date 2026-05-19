#ifndef FREERTOS_CONFIG_H
	#define FREERTOS_CONFIG_H

	#define configUSE_TRACE_FACILITY        1
	#define configGENERATE_RUN_TIME_STATS   0

	/* Timeline Scheduler Configuration */
	#define configUSE_TIMELINE_SCHEDULER    1
	#define configTIMELINE_TASK_COUNT 4
	#define configTIMELINE_MAJOR_FRAME_TICKS 30
	#define configTIMELINE_MINOR_FRAME_TICKS 6


	/* Enable Hooks for Deadline/Kill Monitoring */
	#define configUSE_TIMELINE_DEADLINE_HOOK 0
	#define configTIMELINE_SUBFRAMES_PER_CYCLE (configTIMELINE_MAJOR_FRAME_TICKS / configTIMELINE_MINOR_FRAME_TICKS)


	#define configUSE_TIME_SLICING					0
	#define configUSE_PREEMPTION            		1
	#define configUSE_IDLE_HOOK             		0
	#define configUSE_TICK_HOOK             		0
	#define configCPU_CLOCK_HZ              		( ( unsigned long ) 25000000 )
	#define configTICK_RATE_HZ              		( ( TickType_t ) 1000 )
	#define configMINIMAL_STACK_SIZE        		( ( unsigned short ) 80 )
	#define configMAX_TASK_STACK_SIZE       		( ( unsigned short ) 256 )
	#define configTOTAL_HEAP_SIZE           		( ( size_t ) ( 60 * 1024 ) )
	#define configMAX_TASK_NAME_LEN         		( 16 )
	#define configUSE_16_BIT_TICKS                   0
	#define configIDLE_SHOULD_YIELD                  0
	#define configUSE_CO_ROUTINES                    0
	#define configUSE_MUTEXES                        1
	#define configUSE_RECURSIVE_MUTEXES              1
	#define configCHECK_FOR_STACK_OVERFLOW           0
	#define configUSE_MALLOC_FAILED_HOOK             0
	#define configUSE_QUEUE_SETS                     1
	#define configUSE_COUNTING_SEMAPHORES            1

	#define configMAX_PRIORITIES                     ( 3UL )
	#define configMAX_CO_ROUTINE_PRIORITIES          ( 2 )
	#define configQUEUE_REGISTRY_SIZE                10
	#define configSUPPORT_STATIC_ALLOCATION          1
	#define configKERNEL_PROVIDED_STATIC_MEMORY      1

	/* Timer related defines (unused but required by some ports) */
	#define configUSE_TIMERS                         0
	#define configTIMER_TASK_PRIORITY                ( configMAX_PRIORITIES - 1 )
	#define configTIMER_QUEUE_LENGTH                 20
	#define configTIMER_TASK_STACK_DEPTH             ( configMINIMAL_STACK_SIZE * 2 )

	#define configUSE_TASK_NOTIFICATIONS             1
	#define configTASK_NOTIFICATION_ARRAY_ENTRIES    3

	/* API Includes */
	#define INCLUDE_vTaskPrioritySet                  1
	#define INCLUDE_uxTaskPriorityGet                 1
	#define INCLUDE_vTaskDelete                       1
	#define INCLUDE_vTaskCleanUpResources             0
	#define INCLUDE_vTaskSuspend                      1
	#define INCLUDE_vTaskDelayUntil                   1
	#define INCLUDE_vTaskDelay                        1
	#define INCLUDE_uxTaskGetStackHighWaterMark       1
	#define INCLUDE_xTaskGetSchedulerState            1
	#define INCLUDE_xTimerGetTimerDaemonTaskHandle    1
	#define INCLUDE_xTaskGetIdleTaskHandle            1
	#define INCLUDE_xSemaphoreGetMutexHolder          1
	#define INCLUDE_eTaskGetState                     1
	#define INCLUDE_xTimerPendFunctionCall            1
	#define INCLUDE_xTaskAbortDelay                   1
	#define INCLUDE_xTaskGetHandle                    1

	#define configUSE_STATS_FORMATTING_FUNCTIONS      0

	#define configKERNEL_INTERRUPT_PRIORITY           ( 255 )
	#ifndef _IASMARM_
		#define configASSERT( x ) if( ( x ) == 0 ) while(1);
	#endif

	#define configMAX_SYSCALL_INTERRUPT_PRIORITY             ( 4 )
	#define configUSE_PORT_OPTIMISED_TASK_SELECTION          1
	#define configRUN_ADDITIONAL_TESTS                       1
	#define configSTREAM_BUFFER_TRIGGER_LEVEL_TEST_MARGIN    4

	#define intqHIGHER_PRIORITY      ( configMAX_PRIORITIES - 5 )
	#define bktPRIMARY_PRIORITY      ( configMAX_PRIORITIES - 3 )
	#define bktSECONDARY_PRIORITY    ( configMAX_PRIORITIES - 4 )

	#define configENABLE_BACKWARD_COMPATIBILITY 0

#endif /* FREERTOS_CONFIG_H */
