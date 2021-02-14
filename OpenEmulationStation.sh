#!/bin/sh

sudo pkill ./PiClock
sleep 1s
sudo systemctl start fbcp-ili9341
sleep 3s
emulationstation