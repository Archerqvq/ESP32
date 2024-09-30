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
void myTask(void *pvParam)
{
    // Here are what we are gonna do in our first task
    // Just print a string and with 1s delay 
    // And just notice that there is a infinite loop in every task in freeRTOS
    while (1)
    {
        printf("Hello world! In the task!\n");   
        // This delay statement here is necessary for avoiding esp32 reset by watchdog
        // And this a mechanism for freeRTOS, and for more information that just googling this topic
        vTaskDelay(1000 / portTICK_PERIOD_MS);  
    }
}

void app_main(void)
{
    TaskHandle_t myHandle = NULL;
    // Go check FreeRTOS reference manual for more information
    xTaskCreate(myTask, "myTask", 2048, NULL, 1, &myHandle);
    
    // Do some delay before deleting the task, so that the string inside the task could be printed
    vTaskDelay(5000 / portTICK_PERIOD_MS); 
    
    // A handle will be assigned to the task after the creation
    if(myHandle != NULL)
    {
        // Delete the task by its handle 
        vTaskDelete(myHandle);
    }
    
    // printf("Hello world!\n");

    // /* Print chip information */
    // esp_chip_info_t chip_info;
    // esp_chip_info(&chip_info);
    // printf("This is %s chip with %d CPU core(s), WiFi%s%s, ",
    //         CONFIG_IDF_TARGET,
    //         chip_info.cores,
    //         (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
    //         (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");

    // printf("silicon revision %d, ", chip_info.revision);

    // printf("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
    //         (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    // printf("Minimum free heap size: %d bytes\n", esp_get_minimum_free_heap_size());

    // for (int i = 10; i >= 0; i--) {
    //     printf("Restarting in %d seconds...\n", i);
    //     vTaskDelay(1000 / portTICK_PERIOD_MS);
    // }
    // printf("Restarting now.\n");
    // fflush(stdout);
    // esp_restart();
}
