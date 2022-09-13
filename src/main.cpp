#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"


extern "C"
{
    void vTaskCode( void * pvParameters )
    {
        static const char* TAG = "MAIN";
        int8_t counter = 0;
        TickType_t skipped_ticks = 200;
        for( ;; )
        {
            gpio_set_level(GPIO_NUM_2, (uint32_t)(counter%2));
            ESP_LOGW(TAG, "Hello World from vtask! count: %d", counter += 1);
            vTaskDelay(skipped_ticks);
        }
    }

    void vTaskCodeTwo( void * pvParameters )
    {
        static const char* TAG = "MAIN_TWO";
        int8_t counter = 0;
        TickType_t skipped_ticks = 50;
        for( ;; )
        {
            ESP_LOGW(TAG, "Hello World from vtask two! count: %d", counter += 2);
            vTaskDelay(skipped_ticks);
        }
    }

    void app_main()
    {
        gpio_reset_pin(GPIO_NUM_2);
        gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);
        static const char* TAG = "MAIN";
        ESP_LOGD(TAG,"Hello World!");
        ESP_LOGD(TAG,"Hello World!");
        ESP_LOGI(TAG,"Hello World!");
        ESP_LOGI(TAG,"Hello World!");
        ESP_LOGW(TAG,"Hello World!");

        static uint8_t ucParameterToPass;
        TaskHandle_t xHandle = NULL;
        TaskHandle_t xHandleTwo = NULL;
        UBaseType_t taskPriority = 2;
        // Create the task, storing the handle.  Note that the passed parameter ucParameterToPass
        // must exist for the lifetime of the task, so in this case is declared static.  If it was just an
        // an automatic stack variable it might no longer exist, or at least have been corrupted, by the time
        // the new task attempts to access it.
        xTaskCreate( vTaskCode, "FIRST", 4096, &ucParameterToPass, taskPriority, &xHandle );
        configASSERT( xHandle );
        xTaskCreate( vTaskCodeTwo, "TWO", 4096, &ucParameterToPass, taskPriority, &xHandleTwo );


        // Use the handle to delete the task.
        // if( xHandle != NULL )
        // {
        //     vTaskDelete( xHandle );
        // }

    }
}
