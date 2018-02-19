# Active RFID based telemetry system

This project is meant to be a easy to implement solution for a telemetry system.
The whole system uses technologies available for quickly developing a MVP solution.
In short words, the system can be described by: sensor nodes that connect through low-level radio 
to a gateway that has access to the internet. The gateway operates as a MQTT client and publishes the 
data to a remote MQTT server. A MQTT client in subscribes to the incoming data and directs it
to a database for later visualization. The database client that provides good visualization of the
data uses a customizable dashboard approach.

## Key technologies

To develop the hardware, it was used the technologies available. For the **Gateway** it was necessary to use a  **Arduino Nano** to receive data through the radio because the **RadioHead** lib was not compatible with the **NodeMCU**.

**Sensor Node**

-  **LM35:** Temperature sensor
- **Arduino Nano:** microcontrolling unit
- **FS1000A:** 433MHz radio transmitter
- **Firmware:** RadioHead ASK lib


**Gateway**

- **XY-MK-5V:** 433MHz radio receiver
- **Arduino Nano:** radio bridge
	- **Firmware:**  RadioHead ASK lib + bridge
- **NodeMCU:** microcontrolling unit with WiFi capability (ESP8266)
- **Firmware:** PubSubClient (MQTT Client)


For the service part of the project it was used a **Heroku** dyno as the MQTT Server, so that we could have the sensors and the rest of the system running in different LANs (for easy demonstration). The rest of the services it was used a selection of **Docker** containers with proper configuration that are organized by a *docker-compose* file.

**MQTT Server**

- **Heroku:** CloudMQTT

**Database**

- **InfluxDB:** time series database (container: influxdb)

**Data Visualization**

- **Grafana:** open platform for analytics and monitoring (container: grafana/grafana)

**Application** (container: telegraf)

- **Telegraf:** a plugin-driven server agent for collecting and reporting metrics