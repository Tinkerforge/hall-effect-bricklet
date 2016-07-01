<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickletHallEffect.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickletHallEffect;

const HOST = 'localhost';
const PORT = 4223;
const UID = 'XYZ'; // Change XYZ to the UID of your Hall Effect Bricklet

$ipcon = new IPConnection(); // Create IP connection
$he = new BrickletHallEffect(UID, $ipcon); // Create device object

$ipcon->connect(HOST, PORT); // Connect to brickd
// Don't use device before ipcon is connected

// Get current edge count without reset
$edge_count = $he->getEdgeCount(FALSE);
echo "Edge Count: $edge_count\n";

echo "Press key to exit\n";
fgetc(fopen('php://stdin', 'r'));
$ipcon->disconnect();

?>
