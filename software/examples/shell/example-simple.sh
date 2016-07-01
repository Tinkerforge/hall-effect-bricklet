#!/bin/sh
# Connects to localhost:4223 by default, use --host and --port to change this

uid=XYZ # Change XYZ to the UID of your Hall Effect Bricklet

# Get current edge count without reset
tinkerforge call hall-effect-bricklet $uid get-edge-count false
