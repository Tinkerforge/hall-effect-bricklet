#!/bin/sh
# Connects to localhost:4223 by default, use --host and --port to change this

uid=XYZ # Change to your UID

# Handle incoming edge count callbacks
tinkerforge dispatch hall-effect-bricklet $uid edge-count &

# Set period for edge count callback to 0.05s (50ms)
# Note: The edge count callback is only called every 0.05 seconds
#       if the edge count has changed since the last call!
tinkerforge call hall-effect-bricklet $uid set-edge-count-callback-period 50

echo "Press key to exit"; read dummy

kill -- -$$ # Stop callback dispatch in background
