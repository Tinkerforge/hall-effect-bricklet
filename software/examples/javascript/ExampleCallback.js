var IPConnection = require('Tinkerforge/IPConnection');
var BrickletHallEffect = require('Tinkerforge/BrickletHallEffect');

var HOST = 'localhost';
var PORT = 4223;
var UID = 'irP';// Change to your UID

var ipcon = new IPConnection();// Create IP connection
var he = new BrickletHallEffect(UID, ipcon);// Create device object

ipcon.connect(HOST, PORT,
    function(error) {
        console.log('Error: '+error);        
    }
);// Connect to brickd

// Don't use device before ipcon is connected
ipcon.on(IPConnection.CALLBACK_CONNECTED,
    function(connectReason) {
        // Set Period for edge_count callback to 0.05s (50ms)
        // Note: The edge_count callback is only called every 50ms if the 
        // edge_count has changed since the last call!
        he.setEdgeCountCallbackPeriod(50);       
    }
);

// Register edge count callback
he.on(BrickletHallEffect.CALLBACK_EDGE_COUNT,
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

