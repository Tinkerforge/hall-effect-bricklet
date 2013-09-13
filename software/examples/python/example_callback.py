#!/usr/bin/env python
# -*- coding: utf-8 -*-  

HOST = "localhost"
PORT = 4223
UID = "XYZ" # Change to your UID

from tinkerforge.ip_connection import IPConnection
from tinkerforge.bricklet_hall_effect import HallEffect

# Callback function for edge count callback
def cb_edge_count(edge_count, value):
    print('EdgeCount: ' + str(edge_count))

if __name__ == "__main__":
    ipcon = IPConnection() # Create IP connection
    he = HallEffect(UID, ipcon) # Create device object

    ipcon.connect(HOST, PORT) # Connect to brickd
    # Don't use device before ipcon is connected

    # Set Period for edge_count callback to 0.05s (50ms)
    # Note: The edge_count callback is only called every 50ms if the 
    #       edge_count has changed since the last call!
    he.set_edge_count_callback_period(50)

    # Register edge count callback to function cb_edge_count
    he.register_callback(he.CALLBACK_EDGE_COUNT, cb_edge_count)

    raw_input('Press key to exit\n') # Use input() in Python 3
    ipcon.disconnect()