function octave_example_callback()
    more off;
    
    HOST = "localhost";
    PORT = 4223;
    UID = "uit"; % Change to your UID

    ipcon = java_new("com.tinkerforge.IPConnection"); % Create IP connection
    he = java_new("com.tinkerforge.BrickletHallEffect", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Set Period for edge_count callback to 0.05s (50ms)
    % Note: The edge_count callback is only called every 50ms if the 
    %       edge_count has changed since the last call!
    he.setEdgeCountCallbackPeriod(50);

    % Register edge count callback to function cb_edge_count
    he.addEdgeCountCallback(@cb_edge);

    input("Press any key to exit...\n", "s");
    ipcon.disconnect();
end

% Callback function for edge count callback
function cb_edge(e)
    fprintf("EdgeCount: %s\n", e.count.toString());
end
