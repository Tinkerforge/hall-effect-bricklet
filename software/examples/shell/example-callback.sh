#!/bin/sh
# connects to localhost:4223 by default, use --host and --port to change it

# change to your UID
uid=XYZ

# set period for edge_count callback to 0.05s (50ms)
# note: the edge_count callback is only called every second if the
#       edge_count has changed since the last call!
tinkerforge call hall-effect-bricklet $uid set-edge-count-callback-period 50

# handle incoming edge count callbacks
tinkerforge dispatch hall-effect-bricklet $uid edge-count
