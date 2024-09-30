/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

typedef struct A_STRUCT
{
    int iMem1;
    int iMem2;
} xStruct;

// My first task
void myTask(void *pvParam)
{
    // What if the input parameter is an integer
    // int *pInt = NULL;
    // pInt = (int *)pvParam;

    // What if the input parameter is an array
    // int *pArrayAddr = NULL;
    // pArrayAddr = (int *)pvParam;

    // What if the input parameter is a structure
    // xStruct *pStrTest = NULL;
    // pStrTest = (xStruct *)pvParam;

    // What if the input parameter is a string
    // char *pcTxtInTask = NULL;
    // pcTxtInTask = (char *)pvParam;

    // Here are what we are gonna do in our first task
    // Just print a string and with 1s delay
    // And just notice that there is a infinite loop in every task in freeRTOS
    while (1)
    {
        // printf("I got testNum = %d\n", *pInt);

        // printf("I got num1 = %d\n", *pArrayAddr);
        // printf("I got num2 = %d\n", *(pArrayAddr + 1));
        // printf("I got num3 = %d\n", *(pArrayAddr + 2));

        // printf("I got struct num1 = %d\n", pStrTest->iMem1);
        // printf("I got struct num2 = %d\n", pStrTest->iMem2);

        // printf("I got a message:%s\n", pcTxtInTask);

        // This delay statement here is necessary for avoiding esp32 reset by watchdog
        // And this a mechanism for freeRTOS, and for more information that just googling this topic
        vTaskDelay(1000 / portTICK_PERIOD_MS);

        // Invoke the task deletion within a task with a NULL parameter can be used to delete current task
        // This usage could be found in FreeRTOS reference manual
        vTaskDelete(NULL);

        // Another print statement to confirm that the task has been deleted
        // The second print statement will never be executed
        printf("Task has been deleted\n");
    }
}

int testNum = 1;
int testArray[] = {1, 2, 3};
xStruct xStrTest = {5, 6};

static const char *pcTxt = "Its Archer here\n";

void app_main(void)
{
    UBaseType_t iPriority = 0;
    TaskHandle_t pxTask = NULL;

    // Go check https://www.freertos.org/Documentation/02-Kernel/02-Kernel-features/01-Tasks-and-co-routines/03-Task-priorities for more information
    // The task priority would be set to configMAX_PRIORITIES - 1, if its priority is greater than configMAX_PRIORITIES - 1
    xTaskCreate(myTask, "myTask", 2048, (void *)pcTxt, 30, &pxTask);
    iPriority = uxTaskPriorityGet(pxTask);
    printf("iPriority = %d\n", iPriority);
}
