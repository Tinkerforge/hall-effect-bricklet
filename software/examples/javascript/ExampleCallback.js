var Tinkerforge = require('tinkerforge');

var HOST = 'localhost';
var PORT = 4223;
var UID = 'XYZ'; // Change XYZ to the UID of your Hall Effect Bricklet

var ipcon = new Tinkerforge.IPConnection(); // Create IP connection
var he = new Tinkerforge.BrickletHallEffect(UID, ipcon); // Create device object

ipcon.connect(HOST, PORT,
    function (error) {
        console.log('Error: ' + error);
    }
); // Connect to brickd
// Don't use device before ipcon is connected

ipcon.on(Tinkerforge.IPConnection.CALLBACK_CONNECTED,
    function (connectReason) {
        // Set period for edge count callback to 0.05s (50ms)
        // Note: The edge count callback is only called every 0.05 seconds
        //       if the edge count has changed since the last call!
        he.setEdgeCountCallbackPeriod(50);
    }
);

// Register edge count callback
he.on(Tinkerforge.BrickletHallEffect.CALLBACK_EDGE_COUNT,
    // Callback function for edge count callback
    function (count, value) {
        console.log('Count: ' + count);
    }
);

console.log('Press key to exit');
process.stdin.on('data',
    function (data) {
        ipcon.disconnect();
        process.exit(0);
    }
);
