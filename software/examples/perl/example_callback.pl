#!/usr/bin/perl

use strict;
use Tinkerforge::IPConnection;
use Tinkerforge::BrickletHallEffect;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'XYZ'; # Change XYZ to the UID of your Hall Effect Bricklet

# Callback subroutine for edge count callback
sub cb_edge_count
{
    my ($edge_count, $value) = @_;

    print "Edge Count: $edge_count\n";
}

my $ipcon = Tinkerforge::IPConnection->new(); # Create IP connection
my $he = Tinkerforge::BrickletHallEffect->new(&UID, $ipcon); # Create device object

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Register edge count callback to subroutine cb_edge_count
$he->register_callback($he->CALLBACK_EDGE_COUNT, 'cb_edge_count');

# Set period for edge count callback to 0.05s (50ms)
# Note: The edge count callback is only called every 0.05 seconds
#       if the edge count has changed since the last call!
$he->set_edge_count_callback_period(50);

print "Press key to exit\n";
<STDIN>;
$ipcon->disconnect();
