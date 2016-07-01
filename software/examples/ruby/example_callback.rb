#!/usr/bin/env ruby
# -*- ruby encoding: utf-8 -*-

require 'tinkerforge/ip_connection'
require 'tinkerforge/bricklet_hall_effect'

include Tinkerforge

HOST = 'localhost'
PORT = 4223
UID = 'XYZ' # Change XYZ to the UID of your Hall Effect Bricklet

ipcon = IPConnection.new # Create IP connection
he = BrickletHallEffect.new UID, ipcon # Create device object

ipcon.connect HOST, PORT # Connect to brickd
# Don't use device before ipcon is connected

# Register edge count callback
he.register_callback(BrickletHallEffect::CALLBACK_EDGE_COUNT) do |edge_count, value|
  puts "Edge Count: #{edge_count}"
end

# Set period for edge count callback to 0.05s (50ms)
# Note: The edge count callback is only called every 0.05 seconds
#       if the edge count has changed since the last call!
he.set_edge_count_callback_period 50

puts 'Press key to exit'
$stdin.gets
ipcon.disconnect
