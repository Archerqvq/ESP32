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

// My first task
void myTask1(void *pvParam)
{
    // Here are what we are gonna do in our first task
    // Just print a string and with 1s delay
    // And just notice that there is a infinite loop in every task in freeRTOS
    while (1)
    {
        printf("task1-111\n");

        // This delay statement here is necessary for avoiding esp32 reset by watchdog
        // And this a mechanism for freeRTOS, and for more information that just googling this topic
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void myTask2(void *pvParam)
{
    while (1)
    {
        printf("task2-222\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void app_main(void)
{
    // UBaseType_t iPriority = 0;
    // TaskHandle_t pxTask = NULL;

    xTaskCreate(myTask1, "myTask1", 2048, NULL, 1, NULL);
    xTaskCreate(myTask2, "myTask2", 2048, NULL, 1, NULL);
    
    // iPriority = uxTaskPriorityGet(pxTask);
    // printf("iPriority = %d\n", iPriority);
}
