| Supported Targets | ESP32 | ESP32-C2 | ESP32-C3 | ESP32-C6 | ESP32-H2 | ESP32-S2 | ESP32-S3 |
| ----------------- | ----- | -------- | -------- | -------- | -------- | -------- | -------- |

# _Sample project_

(See the README.md file in the upper level 'examples' directory for more information about examples.)

This is the simplest buildable example. The example is used by command `idf.py create-project`
that copies the project to user specified path and set it's name. For more information follow the [docs page](https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/build-system.html#start-a-new-project)



## How to use example
We encourage the users to use the example as a template for the new projects.
A recommended way is to follow the instructions on a [docs page](https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/build-system.html#start-a-new-project).

## Example folder contents

The project **sample_project** contains one source file in C language [main.c](main/main.c). The file is located in folder [main](main).

ESP-IDF projects are built using CMake. The project build configuration is contained in `CMakeLists.txt`
files that provide set of directives and instructions describing the project's source files and targets
(executable, library, or both). 

Below is short explanation of remaining files in the project folder.

```
├── CMakeLists.txt
├── main
│   ├── CMakeLists.txt
│   └── main.c
└── README.md                  This is the file you are currently reading
```
Additionally, the sample project contains Makefile and component.mk files, used for the legacy Make based build system. 
They are not used or needed when building with CMake and idf.py.

## Wifi 
documentação do wifi: https://medium.com/@fatehsali517/how-to-connect-esp32-to-wifi-using-esp-idf-iot-development-framework-d798dc89f0d6

## MQTT

MQTT (Message Queuing Telemetry Transport) é um protocolo leve para comunicação entre dispositivos na Internet das Coisas (IoT). Ele usa um modelo de publicação e assinatura, onde os dispositivos podem enviar mensagens (publicadores) e receber mensagens (assinantes) em tópicos específicos. O MQTT é eficiente, confiável e suporta diferentes níveis de qualidade de serviço (QoS) para garantir a entrega das mensagens. É amplamente adotado devido à sua simplicidade e eficiência em ambientes de IoT.
#### 1- Os tópicos
 - No MQTT são canais de comunicação aos quais os dispositivos podem se inscrever (assinantes) para receber mensagens ou publicar (publicadores) para enviar mensagens.
- Os tópicos são strings que servem como identificadores para os diferentes tipos de informações que os dispositivos desejam trocar.
- Eles são organizados em uma hierarquia de nível único, o que significa que podem ser estruturados em uma árvore de tópicos, facilitando a organização e filtragem das mensagens.
#### 2- Broker:

- Um broker MQTT é um servidor que recebe e encaminha mensagens entre dispositivos.
Ele atua como um intermediário na comunicação entre os clientes MQTT (dispositivos) que publicam mensagens e os clientes que as recebem.
- O broker mantém o controle dos tópicos aos quais os clientes estão inscritos e garante que as mensagens sejam entregues aos destinatários corretos.
- Existem brokers MQTT disponíveis em código aberto e também serviços de nuvem que fornecem brokers gerenciados.
#### 3- Clientes:

- Os clientes MQTT são os dispositivos que se conectam ao broker para enviar ou receber mensagens.
- Eles podem ser dispositivos IoT, aplicativos móveis, servidores ou qualquer outra entidade capaz de se comunicar via MQTT.
- Os clientes podem publicar mensagens em tópicos específicos ou se inscrever em tópicos para receber mensagens relevantes.
- Os clientes mantêm uma conexão persistente com o broker, o que permite uma comunicação eficiente e confiável, mesmo em redes com conectividade intermitente.
  

Em resumo, no ecossistema MQTT, os tópicos fornecem uma estrutura organizacional para as mensagens, os brokers facilitam a troca de mensagens entre os clientes e os clientes são os dispositivos ou aplicativos que enviam ou recebem as mensagens. Esses componentes trabalham em conjunto para criar uma rede de comunicação flexível e escalável, adequada para uma variedade de aplicativos de Internet das Coisas (IoT) e outras soluções de comunicação em tempo real.
![Exemplo](imagens/WhatsApp%20Image%202024-02-26%20at%2014.52.35.jpeg)

