# Arduino SMS Alarm
SMS based motion alarm. It uses a PIR (Passive Infra Red) sensor to detect motion and when motion is detected, an SMS is sent to a predefined phone number.

The project uses SIM800L module for operating GSM / GPRS quad band 850/900/1800/1900 Mhz.

The motion detection sensor acts as a digital output. Therefore, all is needed is to listen for the pin to flip high (motion detected) from low (not detected). An LED is connected to Arduino to visually observe when the PIR has detected motion.

The pinout diagram for this project is listed below:

Sensor Pin	  -> Arduino UNO pin
-------------------------------
SIM800L       ->    TXD	11

SIM800L       ->    RXD	10

SIM800L       ->    GND	Arduino GND

SIM800L       ->    VCC	Arduino +5V

PIR VCC	      ->    Arduino +5V

PIR OUT	      ->    2

PIR GND	      ->    Arduino GND

LED +	        ->    13

LED -	        ->    Arduino GND

More information on WWW.PICSAG.COM
