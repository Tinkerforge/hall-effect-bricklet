use std::{error::Error, io, thread};
use tinkerforge::{hall_effect_bricklet::*, ipconnection::IpConnection};

const HOST: &str = "127.0.0.1";
const PORT: u16 = 4223;
const UID: &str = "XYZ"; // Change XYZ to the UID of your Hall Effect Bricklet

fn main() -> Result<(), Box<dyn Error>> {
    let ipcon = IpConnection::new(); // Create IP connection
    let hall_effect_bricklet = HallEffectBricklet::new(UID, &ipcon); // Create device object

    ipcon.connect(HOST, PORT).recv()??; // Connect to brickd
                                        // Don't use device before ipcon is connected

    //Create listener for edge count events.
    let edge_count_listener = hall_effect_bricklet.get_edge_count_receiver();
    // Spawn thread to handle received events. This thread ends when the hall_effect_bricklet
    // is dropped, so there is no need for manual cleanup.
    thread::spawn(move || {
        for event in edge_count_listener {
            println!("Count: {}", event.count);
        }
    });

    // Set period for edge count listener to 0.05s (50ms)
    // Note: The edge count callback is only called every 0.05 seconds
    //       if the edge count has changed since the last call!
    hall_effect_bricklet.set_edge_count_callback_period(50);

    println!("Press enter to exit.");
    let mut _input = String::new();
    io::stdin().read_line(&mut _input)?;
    ipcon.disconnect();
    Ok(())
}
