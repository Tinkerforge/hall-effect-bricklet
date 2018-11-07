use std::{error::Error, io, thread};
use tinkerforge::{hall_effect_bricklet::*, ip_connection::IpConnection};

const HOST: &str = "localhost";
const PORT: u16 = 4223;
const UID: &str = "XYZ"; // Change XYZ to the UID of your Hall Effect Bricklet.

fn main() -> Result<(), Box<dyn Error>> {
    let ipcon = IpConnection::new(); // Create IP connection.
    let he = HallEffectBricklet::new(UID, &ipcon); // Create device object.

    ipcon.connect((HOST, PORT)).recv()??; // Connect to brickd.
                                          // Don't use device before ipcon is connected.

    let edge_count_receiver = he.get_edge_count_callback_receiver();

    // Spawn thread to handle received callback messages.
    // This thread ends when the `he` object
    // is dropped, so there is no need for manual cleanup.
    thread::spawn(move || {
        for edge_count in edge_count_receiver {
            println!("Count: {}", edge_count.count);
        }
    });

    // Set period for edge count receiver to 0.05s (50ms).
    // Note: The edge count callback is only called every 0.05 seconds
    //       if the edge count has changed since the last call!
    he.set_edge_count_callback_period(50);

    println!("Press enter to exit.");
    let mut _input = String::new();
    io::stdin().read_line(&mut _input)?;
    ipcon.disconnect();
    Ok(())
}
