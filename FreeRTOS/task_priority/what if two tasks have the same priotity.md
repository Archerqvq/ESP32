## Description

When I was trying to do an experiment on `ESP32` to figure out how the thing goes on when two tasks have the same priority with freeRTOS.

The source code is posted below:

```c
#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

void myTask1(void *pvParam)
{
    while (1)
    {
        printf("task1-111\n");
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
    xTaskCreate(myTask1, "myTask1", 2048, NULL, 1, NULL);
    xTaskCreate(myTask2, "myTask2", 2048, NULL, 1, NULL);
}
```

I expected that the log would print like this:

```c
task1-111
task2-222
task1-111
task2-222
task1-111
task2-222
...
```

But the log actually was like this:

```c
task1-111
task2-222
task1-222
task2-111
task1-222
task2-111
...
```

Its kind of weird. After googling, I found that this issue might related to multi-core on `ESP32`. So I try to find out the specific core that the task is running on and I will do it by invoking `xPortGetCoreID()`, an internal fucntion in esp-idf. Lets see what it looks like after doing this:

```c

...
void myTask1(void *pvParam)
{
    while (1)
    {
        printf("task1-111\n");
        printf("Task1 running on core %d\n", xPortGetCoreID()); // Get current core id
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        
    }
}

void myTask2(void *pvParam)
{
    while (1)
    {
        printf("task2-222\n");
        printf("Task2 running on core %d\n", xPortGetCoreID()); // Get current core id
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
...
```

From the log, we can see that both task 1 and task 2 are initially running on Core 1. However, after they both switch to Core 0, the sequence of the tasks changes from task 2 to task 1:

```c
task1-111
task2-222
Task2 running on core 1
Task1 running on core 1
task2-222
Task2 running on core 0
task1-111
Task1 running on core 0
task2-222
Task2 running on core 0
task1-111
Task1 running on core 0
task2-222
Task2 running on core 0
```

So, Let's see what's gonna happend when I make some changes to the cores configurations.

## How to fix

### The method 1

```c
    xTaskCreatePinnedToCore(myTask1, "myTask1", 2048, NULL, 1, NULL, 0); // Pin Task1 to Core 0
    xTaskCreatePinnedToCore(myTask2, "myTask2", 2048, NULL, 1, NULL, 0); // Pin Task2 to Core 0
```

And the log will be like this:

```c
task1-111
Task1 running on core 0
task2-222
Task2 running on core 0
task1-111
Task1 running on core 0
task2-222
Task2 running on core 0
task1-111
Task1 running on core 0
task2-222
Task2 running on core 0
```