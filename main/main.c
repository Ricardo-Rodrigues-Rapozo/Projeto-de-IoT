#include <stdio.h> //for basic printf commands
#include <string.h> //for handling strings
#include "freertos/FreeRTOS.h" //for delay,mutexs,semphrs rtos operations
#include "esp_system.h" //esp_init funtions esp_err_t 
#include "esp_wifi.h" //esp_wifi_init functions and wifi operations
#include "esp_log.h" //for showing logs
#include "esp_event.h" //for wifi event
#include "nvs_flash.h" //non volatile storage
#include "lwip/err.h" //light weight ip packets error handling
#include "lwip/sys.h" //system applications for light weight ip apps
#include "mqtt_client.h" //provides important functions to connect with MQTT
#include "protocol_examples_common.h" //important for running different protocols in code
#include "freertos/task.h" //MQTT communication often involves asynchronous operations, and FreeRTOS helps handle those tasks effectively


//=========================== Definições ================================================================================================================



const char *ssid = "Rapozo";
const char *pass = "74856191";
int retry_num=0;
static const char *TAG = "MQTT_EXAMPLE";

//=========================== WIFI =======================================================================================================================


static void wifi_event_handler(void *event_handler_arg, esp_event_base_t event_base, int32_t event_id,void *event_data){
if(event_id == WIFI_EVENT_STA_START)
{
  printf("WIFI CONNECTING....\n");
}
else if (event_id == WIFI_EVENT_STA_CONNECTED)
{
  printf("WiFi CONNECTED\n");
}
else if (event_id == WIFI_EVENT_STA_DISCONNECTED)
{
  printf("WiFi lost connection\n");
  if(retry_num<5){esp_wifi_connect();retry_num++;printf("Retrying to Connect...\n");}
}
else if (event_id == IP_EVENT_STA_GOT_IP)
{
  printf("Wifi got IP...\n\n");
}
}

void wifi_connection()
{
     //                          s1.4
    // 2 - Wi-Fi Configuration Phase
    esp_netif_init();
    esp_event_loop_create_default();     // event loop                    s1.2
    esp_netif_create_default_wifi_sta(); // WiFi station                      s1.3
    wifi_init_config_t wifi_initiation = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&wifi_initiation); //     
    esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, wifi_event_handler, NULL);
    esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, wifi_event_handler, NULL);
    wifi_config_t wifi_configuration = {
        .sta = {
            .ssid = "",
            .password = "",
            
           }
    
        };
    strcpy((char*)wifi_configuration.sta.ssid, ssid);
    strcpy((char*)wifi_configuration.sta.password, pass);    
    //esp_log_write(ESP_LOG_INFO, "Kconfig", "SSID=%s, PASS=%s", ssid, pass);
    esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_configuration);
    // 3 - Wi-Fi Start Phase
    esp_wifi_start();
    esp_wifi_set_mode(WIFI_MODE_STA);
    // 4- Wi-Fi Connect Phase
    esp_wifi_connect();
    printf( "wifi_init_softap finished. SSID:%s  password:%s",ssid,pass);
    
}



//======================================== MQTT ==============================================================================================================

static void mqtt_event_handler(esp_mqtt_event_handle_t event){ //here esp_mqtt_event_handle_t is a struct which receieves struct event from mqtt app start funtion
esp_mqtt_client_handle_t client = event->client; //making obj client of struct esp_mqtt_client_handle_t and assigning it the receieved event client
  if(event->event_id == MQTT_EVENT_CONNECTED){
  ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
  esp_mqtt_client_subscribe(client,"your topic",0); //in mqtt we require a topic to subscribe and client is from event client and 0 is quality of service it can be 1 or 2
  ESP_LOGI(TAG, "sent subscribe successful" );
  }
  else if(event->event_id == MQTT_EVENT_DISCONNECTED)
  {
    ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED"); //if disconnected
  }
  else if(event->event_id == MQTT_EVENT_SUBSCRIBED)
  {
    ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED");
  }
  else if(event->event_id == MQTT_EVENT_UNSUBSCRIBED) //when subscribed
  {
    ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED");
  }
  else if(event->event_id == MQTT_EVENT_DATA)//when unsubscribed
  {
    ESP_LOGI(TAG, "MQTT_EVENT_DATA");
  }
  else if(event->event_id == MQTT_EVENT_ERROR)//when any error
  {
    ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
  }
}

static void mqtt_initialize(void)
{/*Depending on your website or cloud there could be more parameters in mqtt_cfg.*/
  const esp_mqtt_client_config_t mqtt_cfg = {
    .uri="mqtt://io.adafruit.com", //Uniform Resource Identifier includes path,protocol
    .event_handle = mqtt_event_handler, //described above event handler
    .username="",/*your username*/ //your username
    .password="",/*your adafruit password*/ //your adafruit io password
  };
  esp_mqtt_client_handle_t client=esp_mqtt_client_init(&mqtt_cfg); //sending struct as a parameter in init client function
  esp_mqtt_client_start(client); //starting the process
}



//======================================== Task geral ==============================================================================================================




void vTaskCode(void *pvParameters) {
    int i = 1;

    while (1) {
        for (i = 1; i <= 5; i++) {
            printf("deu bom\n");
            vTaskDelay(pdMS_TO_TICKS(1000)); // Espera 1 segundo
        }
    }
}




//======================================== Main ===================================================================================================================


void app_main(void) {
  nvs_flash_init(); //keeps stored important wifi configs like ssid and password also mqtt configs code will not work without it
  wifi_connection(); // connects to wifi 
  vTaskDelay(10000 /portTICK_PERIOD_MS); //delay is important cause we need to let it connect to wifi 
  mqtt_app_start(); // MQTT start app as shown above most important code for MQTT   
}
