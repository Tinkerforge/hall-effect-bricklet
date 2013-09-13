<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickletHallEffect.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickletHallEffect;

$host = 'localhost';
$port = 4223;
$uid = 'XYZ'; // Change to your UID

# Callback function for edge_count callback 
function cb_edge_count($edge_count, $value)
{
    echo "Edge Count: $edge_count\n";
}

$ipcon = new IPConnection(); // Create IP connection
$he = new BrickletHallEffect($uid, $ipcon); // Create device object

$ipcon->connect($host, $port); // Connect to brickd
// Don't use device before ipcon is connected

// Set Period for edge_count callback to 0.05s (50ms)
// Note: The edge_count callback is only called every 50ms if the 
//       edge_count has changed since the last call!
$he->setEdgeCountCallbackPeriod(50);

# Register edge count callback to function cb_edge_count
$he->registerCallback(BrickletHallEffect::CALLBACK_EDGE_COUNT, 'cb_edge_count');

echo "Press ctrl+c to exit\n";
$ipcon->dispatchCallbacks(-1); // Dispatch callbacks forever

?>
