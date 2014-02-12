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
        // Get current edge count of encoder without reset 
        he.getEdgeCount(false,
            function(edgeCount) {
                console.log('Edge Count: '+edgeCount);
            },
            function(error) {
                console.log('Error: '+error);
            }
        );
    }
);

console.log("Press any key to exit ...");
process.stdin.on('data',
    function(data) {
        ipcon.disconnect();
        process.exit(0);
    }
);

