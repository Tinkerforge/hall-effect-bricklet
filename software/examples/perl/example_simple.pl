#!/usr/bin/perl  

use Tinkerforge::IPConnection;
use Tinkerforge::BrickletHallEffect;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => '7xwQ9g'; # Change to your UID

my $ipcon = Tinkerforge::IPConnection->new(); # Create IP connection
my $he = Tinkerforge::BrickletHallEffect->new(&UID, $ipcon); # Create device object

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Get current edge count of encoder without reset 
my $edge_count = $he->get_edge_count(0);

print "\nEdgeCount: $edge_count\n";

print "\nPress any key to exit...\n";
<STDIN>;
$ipcon->disconnect();

