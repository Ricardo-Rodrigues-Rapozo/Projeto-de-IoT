#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void vTaskCode(void *pvParameters) {
    int i = 1;

    while (1) {
        for (i = 1; i <= 5; i++) {
            printf("deu bom\n");
            vTaskDelay(pdMS_TO_TICKS(1000)); // Espera 1 segundo
        }
    }
}

void app_main(void) {
    xTaskCreate(vTaskCode, "task1", 2048, NULL, 1, NULL);
}
