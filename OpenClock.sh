#!/bin/sh

#exit emulation gracefully
sudo pkill emulationstation
sleep 1s
sudo systemctl start fbcp
sleep 1s
cd && PiClock/PiClock
