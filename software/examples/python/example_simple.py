#!/usr/bin/env python
# -*- coding: utf-8 -*-  

HOST = "localhost"
PORT = 4223
UID = "XYZ" # Change to your UID

from tinkerforge.ip_connection import IPConnection
from tinkerforge.bricklet_hall_effect import HallEffect

if __name__ == "__main__":
    ipcon = IPConnection() # Create IP connection
    he = HallEffect(UID, ipcon) # Create device object

    ipcon.connect(HOST, PORT) # Connect to brickd
    # Don't use device before ipcon is connected

    # Get current edge count of encoder without reset 
    edge_count = he.get_edge_count(False)

    print('EdgeCount: ' + str(edge_count))

    raw_input('Press key to exit\n') # Use input() in Python 3
    ipcon.disconnect()
