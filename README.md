# ZeroMQMCU
Implementation of sub/pub socket of ZeroMQ for Arduino and WIZnet W5500.
The maximum read speed of the subscriber is 5000 messages per second for a payload of 10 bytes. 
The maximum speed of sending by the publisher is 2300 messages per second for 1 subscriber and 400 for 8 subscribers 
simultaneously, also for 10 bytes of payload. Results are shown for Arduino Uno.
For building and uploading used platformio (https://platformio.org/), but you can use any other tools.

Papper of implementation https://cloudofscience.ru/sites/default/files/pdf/CoS_6_666.pdf
