function octave_example_simple
    more off;
    
    HOST = "localhost";
    PORT = 4223;
    UID = "uit"; % Change to your UID

    ipcon = java_new("com.tinkerforge.IPConnection"); % Create IP connection
    he = java_new("com.tinkerforge.BrickletHallEffect", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Get current edge count of encoder without reset 
    edge_count = he.getEdgeCount(false);

    fprintf("EdgeCount: %s\n", edge_count.toString());

    input("\nPress any key to exit...\n", "s");
    ipcon.disconnect();
end
