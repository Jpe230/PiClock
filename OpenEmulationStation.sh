#!/bin/sh

sudo pkill ./PiClock
sleep(1)
sudo systemctl start fbcp-ili9341
sleep(3)
emulationstation 
