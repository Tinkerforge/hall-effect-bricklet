function matlab_example_simple()
    import com.tinkerforge.IPConnection;
    import com.tinkerforge.BrickletHallEffect;

    HOST = 'localhost';
    PORT = 4223;
    UID = 'XYZ'; % Change to your UID

    ipcon = IPConnection(); % Create IP connection
    he = BrickletHallEffect(UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Get current edge count without reset
    edgeCount = he.getEdgeCount(false);
    fprintf('Edge Count: %i\n', edgeCount);

    input('Press key to exit\n', 's');
    ipcon.disconnect();
end
