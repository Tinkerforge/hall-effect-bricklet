<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickletHallEffect.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickletHallEffect;

const HOST = 'localhost';
const PORT = 4223;
const UID = 'XYZ'; // Change XYZ to the UID of your Hall Effect Bricklet

// Callback function for edge count callback
function cb_edgeCount($count, $value)
{
    echo "Count: $count\n";
}

$ipcon = new IPConnection(); // Create IP connection
$he = new BrickletHallEffect(UID, $ipcon); // Create device object

$ipcon->connect(HOST, PORT); // Connect to brickd
// Don't use device before ipcon is connected

// Register edge count callback to function cb_edgeCount
$he->registerCallback(BrickletHallEffect::CALLBACK_EDGE_COUNT, 'cb_edgeCount');

// Set period for edge count callback to 0.05s (50ms)
// Note: The edge count callback is only called every 0.05 seconds
//       if the edge count has changed since the last call!
$he->setEdgeCountCallbackPeriod(50);

echo "Press ctrl+c to exit\n";
$ipcon->dispatchCallbacks(-1); // Dispatch callbacks forever

?>
