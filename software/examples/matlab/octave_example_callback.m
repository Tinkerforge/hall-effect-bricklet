function octave_example_callback()
    more off;

    HOST = "localhost";
    PORT = 4223;
    UID = "XYZ"; % Change XYZ to the UID of your Hall Effect Bricklet

    ipcon = java_new("com.tinkerforge.IPConnection"); % Create IP connection
    he = java_new("com.tinkerforge.BrickletHallEffect", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Register edge count callback to function cb_edge_count
    he.addEdgeCountCallback(@cb_edge_count);

    % Set period for edge count callback to 0.05s (50ms)
    % Note: The edge count callback is only called every 0.05 seconds
    %       if the edge count has changed since the last call!
    he.setEdgeCountCallbackPeriod(50);

    input("Press key to exit\n", "s");
    ipcon.disconnect();
end

% Callback function for edge count callback
function cb_edge_count(e)
    fprintf("Edge Count: %d\n", java2int(e.edgeCount));
end

function int = java2int(value)
    if compare_versions(version(), "3.8", "<=")
        int = value.intValue();
    else
        int = value;
    end
end
