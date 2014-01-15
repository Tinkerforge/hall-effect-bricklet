<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickletHallEffect.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickletHallEffect;

const HOST = 'localhost';
const PORT = 4223;
const UID = 'XYZ'; // Change to your UID

$ipcon = new IPConnection(); // Create IP connection
$he = new BrickletHallEffect(UID, $ipcon); // Create device object

$ipcon->connect(HOST, PORT); // Connect to brickd
// Don't use device before ipcon is connected

// Get current edge count of Hall Effect Bricklet without reset 
$edge_count = $he->getEdgeCount(false);

echo "EdgeCount: $edge_count\n";

echo "Press key to exit\n";
fgetc(fopen('php://stdin', 'r'));
$ipcon->disconnect();

?>
