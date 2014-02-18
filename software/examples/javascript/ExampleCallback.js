var Tinkerforge = require('tinkerforge');

var HOST = 'localhost';
var PORT = 4223;
var UID = 'irP';// Change to your UID

var ipcon = new Tinkerforge.IPConnection();// Create IP connection
var he = new Tinkerforge.BrickletHallEffect(UID, ipcon);// Create device object

ipcon.connect(HOST, PORT,
    function(error) {
        console.log('Error: '+error);        
    }
);// Connect to brickd

// Don't use device before ipcon is connected
ipcon.on(Tinkerforge.IPConnection.CALLBACK_CONNECTED,
    function(connectReason) {
        // Set Period for edge_count callback to 0.05s (50ms)
        // Note: The edge_count callback is only called every 50ms if the 
        // edge_count has changed since the last call!
        he.setEdgeCountCallbackPeriod(50);       
    }
);

// Register edge count callback
he.on(Tinkerforge.BrickletHallEffect.CALLBACK_EDGE_COUNT,
    // Callback function for edge count callback
    function(edgeCount, value) {
        console.log('Edge Count: '+edgeCount);
    }
);

console.log("Press any key to exit ...");
process.stdin.on('data',
    function(data) {
        ipcon.disconnect();
        process.exit(0);
    }
);

