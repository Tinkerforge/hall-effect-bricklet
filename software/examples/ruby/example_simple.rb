#!/usr/bin/env ruby
# -*- ruby encoding: utf-8 -*-

require 'tinkerforge/ip_connection'
require 'tinkerforge/bricklet_hall_effect'

include Tinkerforge

HOST = 'localhost'
PORT = 4223
UID = 'XYZ' # Change to your UID

ipcon = IPConnection.new # Create IP connection
he = BrickletHallEffect.new UID, ipcon # Create device object

ipcon.connect HOST, PORT # Connect to brickd
# Don't use device before ipcon is connected

# Get current edge count without reset
edge_count = he.get_edge_count false
puts "Edge Count: #{edge_count}"

puts 'Press key to exit'
$stdin.gets
ipcon.disconnect
