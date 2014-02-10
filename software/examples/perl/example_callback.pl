#!/usr/bin/perl  

use Tinkerforge::IPConnection;
use Tinkerforge::BrickletHallEffect;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => '7xwQ9g'; # Change to your UID

my $ipcon = Tinkerforge::IPConnection->new(); # Create IP connection
my $he = Tinkerforge::BrickletHallEffect->new(&UID, $ipcon); # Create device object

# Callback function for edge count callback
sub cb_edge_count
{
    my ($edge_count, $value) = @_;
    print "\nEdge Count: $edge_count\n";
}

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Set Period for edge_count callback to 0.05s (50ms)
# Note: The edge_count callback is only called every 50ms if the 
#       edge_count has changed since the last call!
$he->set_edge_count_callback_period(50);

# Register edge count callback to function cb_edge_count
$he->register_callback($he->CALLBACK_EDGE_COUNT, 'cb_edge_count');

print "\nPress any key to exit...\n";
<STDIN>;
$ipcon->disconnect();

