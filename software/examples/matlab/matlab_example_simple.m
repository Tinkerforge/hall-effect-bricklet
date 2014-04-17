function matlab_example_simple
    import com.tinkerforge.IPConnection;
    import com.tinkerforge.BrickletHallEffect;

    HOST = 'localhost';
    PORT = 4223;
    UID = 'uit'; % Change to your UID
    
    ipcon = IPConnection(); % Create IP connection
    he = BrickletHallEffect(UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Get current edge count of encoder without reset 
    edge_count = he.getEdgeCount(false);
    fprintf('EdgeCount: %g\n', edge_count);

    input('Press any key to exit...\n', 's');
    ipcon.disconnect();
end
