#!/bin/sh
# Connects to localhost:4223 by default, use --host and --port to change this

uid=XYZ # Change to your UID

# Get current edge count without reset
tinkerforge call hall-effect-bricklet $uid get-edge-count false
