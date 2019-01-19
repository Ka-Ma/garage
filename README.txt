This project uses a headless Raspberry Pi and C++ code to monitor the garage door (via a magnetic switch plugged into one of the GPIO) and send an email to the home owners to alert them to their forgetfulness should they leave it open longer than half an hour.
Updating to include an LCD screen to show up time & IP Address this requires WiringPi therefore updating to use that instead of GPIOClass

To compile, type into CLI:
OLD: g++ GPIOClass.cpp email.cpp garage.cpp -o garage
NEW: g++ -std=c++0x email.cpp garage.cpp -o garage -lwiringPi -lwiringPiDev

For email, using Postfix and aliases: as per this guide - https://blog.dantup.com/2016/04/setting-up-raspberry-pi-raspbian-jessie-to-send-email/
altered to use actual gmail account as per this guide (did not have to make any changes to code) - https://www.linode.com/docs/email/postfix/configure-postfix-to-send-mail-using-gmail-and-google-apps-on-debian-or-ubuntu/

To have program run on boot: 
add program to rc.local
also added postfix start to rc.local after 5 sec sleep restart to see if that will solve email problem


Things to do:
add count for number of mins:secs it has been open
remove "Up time:" label or maybe change that to just days and hours
add a button to temporarily increase time before email sent (for when you want the garage open longer) and indicate that on screen