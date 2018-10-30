function matlab_example_simple()
    import com.tinkerforge.IPConnection;
    import com.tinkerforge.BrickletHallEffect;

    HOST = 'localhost';
    PORT = 4223;
    UID = 'XYZ'; % Change XYZ to the UID of your Hall Effect Bricklet

    ipcon = IPConnection(); % Create IP connection
    he = handle(BrickletHallEffect(UID, ipcon), 'CallbackProperties'); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Get current edge count without reset
    count = he.getEdgeCount(false);
    fprintf('Count: %i\n', count);

    input('Press key to exit\n', 's');
    ipcon.disconnect();
end
