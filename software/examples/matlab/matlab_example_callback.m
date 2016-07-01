function matlab_example_callback()
    import com.tinkerforge.IPConnection;
    import com.tinkerforge.BrickletHallEffect;

    HOST = 'localhost';
    PORT = 4223;
    UID = 'XYZ'; % Change XYZ to the UID of your Hall Effect Bricklet

    ipcon = IPConnection(); % Create IP connection
    he = handle(BrickletHallEffect(UID, ipcon), 'CallbackProperties'); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Register edge count callback to function cb_edge_count
    set(he, 'EdgeCountCallback', @(h, e) cb_edge_count(e));

    % Set period for edge count callback to 0.05s (50ms)
    % Note: The edge count callback is only called every 0.05 seconds
    %       if the edge count has changed since the last call!
    he.setEdgeCountCallbackPeriod(50);

    input('Press key to exit\n', 's');
    ipcon.disconnect();
end

% Callback function for edge count callback
function cb_edge_count(e)
    fprintf('Edge Count: %i\n', e.edgeCount);
end
