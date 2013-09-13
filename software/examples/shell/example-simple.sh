#!/bin/sh
# connects to localhost:4223 by default, use --host and --port to change it

# change to your UID
uid=XYZ

# get current edge count without reset 
tinkerforge call hall-effect-bricklet $uid get-edge-count false
