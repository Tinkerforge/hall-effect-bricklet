package main

import (
	"fmt"
	"tinkerforge/hall_effect_bricklet"
	"tinkerforge/ipconnection"
)

const ADDR string = "localhost:4223"
const UID string = "XYZ" // Change XYZ to the UID of your Hall Effect Bricklet.

func main() {
	ipcon := ipconnection.New()
	defer ipcon.Close()
	he, _ := hall_effect_bricklet.New(UID, &ipcon) // Create device object.

	ipcon.Connect(ADDR) // Connect to brickd.
	defer ipcon.Disconnect()
	// Don't use device before ipcon is connected.

	// Get current edge count without reset.
	count, _ := he.GetEdgeCount(false)
	fmt.Printf("Count: \n", count)

	fmt.Print("Press enter to exit.")
	fmt.Scanln()

}
