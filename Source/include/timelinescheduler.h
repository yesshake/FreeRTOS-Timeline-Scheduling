/*
 * FreeRTOS Kernel V11.2.0
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

#ifndef INC_TIMELINE_SCHEDULER_H
#define INC_TIMELINE_SCHEDULER_H

    #ifndef INC_FREERTOS_H
        #error "include FreeRTOS.h must appear in source files before include timelinescheduler.h"
    #endif

    /**
     * @brief Defines the classification of tasks within the timeline scheduler.
     *
     * The scheduler distinguishes between tasks that require strict deterministic
     * timing guarantees (Hard Real-Time) and those that run on a best-effort basis
     * during idle periods (Soft Real-Time).
     */
    typedef enum
    {
        /* Tasks that must execute within a specific subframe window and strictly
        * adhere to start and end times. */
        TASK_HARD_RT = 0,

        /* Tasks that execute in the remaining time of a subframe after Hard Real-Time
        * tasks have completed. They are scheduled in a fixed order. */
        TASK_SOFT_RT = 1
    } TaskType_t;

    /**
     * @brief Configuration structure for a single task in the timeline.
     *
     * This structure defines all properties required by the scheduler to manage
     * the task's execution, including its timing constraints, stack requirements,
     * and category.
     */
    typedef struct
    {
        /* A descriptive name for the task. This is used primarily for debugging
        * and identification purposes. */
        const char * pcTaskName;

        /* Pointer to the function that implements the task. The task function must
        * follow the standard FreeRTOS task signature: void vTaskCode( void * pvParameters ); */
        TaskFunction_t pxTaskCode;

        /* The category of the task (Hard Real-Time or Soft Real-Time). */
        TaskType_t xType;

        /* For Hard Real-Time tasks: The offset in ticks from the start of the
        * assigned subframe at which the task must begin execution.
        * For Soft Real-Time tasks: This field is ignored. */
        TickType_t xStartTime;

        /* For Hard Real-Time tasks: The deadline in ticks relative to the start
        * of the assigned subframe. The task must complete execution before this time.
        * For Soft Real-Time tasks: This field is ignored. */
        TickType_t xEndTime;

        /* The index of the subframe (0 to configTIMELINE_SUBFRAMES_PER_CYCLE - 1) in which this task is
        * scheduled to run. */
        uint32_t ulSubframeId;

        /* The number of words (not bytes) to allocate for the task's stack. For example,
        * if the stack is 32-bits wide, a value of 100 allocates 400 bytes. */
        uint16_t usStackDepth;
    } TimelineTaskConfig_t;

    /**
     * @brief Initializes the timeline scheduler with the provided task configuration.
     *
     * This function parses the configuration array, creates the necessary internal
     * structures, and prepares the tasks for execution. It must be called before
     * the FreeRTOS scheduler is started via vTaskStartScheduler().
     *
     * @note The global configuration parameters configTIMELINE_TASK_COUNT, configTIMELINE_MAJOR_FRAME_TICKS, and configTIMELINE_MINOR_FRAME_TICKS
     *       must be defined in FreeRTOSConfig.h.
     *
     * @param[in] cfg Pointer to an array of TimelineTaskConfig_t structures. The array
     *                must contain exactly configTIMELINE_TASK_COUNT entries, defining the complete
     *                schedule for the system.
     */
    void vConfigureScheduler( const TimelineTaskConfig_t * cfg );

    /**
     * @brief Forcefully terminates a task and reschedules it for the next major frame.
     *
     * This function is designed to be called from timeline hooks (which run in 
     * interrupt context) to enforce conditional dependencies or handle faults.
     *
     * @param[in] xTask The handle of the task to terminate.
     */
    #if ( INCLUDE_vTaskTimelineTerminate == 1 )
        void vTaskTimelineTerminateFromISR( TaskHandle_t xTask );
    #endif

#endif /* INC_TIMELINE_SCHEDULER_H */
