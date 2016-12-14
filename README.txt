This project uses a headless Raspberry Pi and C++ code to monitor the garage door (via a magnetic switch plugged into one of the GPIO) and send an email to the home owners to alert them to their forgetfulness should they leave it open longer than half an hour.

To compile, type into CLI:
g++ GPIOClass.cpp email.cpp garage.cpp -o garage

For email, using Postfix and aliases: as per this guide - https://blog.dantup.com/2016/04/setting-up-raspberry-pi-raspbian-jessie-to-send-email/

To have program run on boot: 
