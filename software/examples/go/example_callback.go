package main

import (
	"fmt"
	"github.com/Tinkerforge/go-api-bindings/hall_effect_bricklet"
	"github.com/Tinkerforge/go-api-bindings/ipconnection"
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

	he.RegisterEdgeCountCallback(func(count uint32, value bool) {
		fmt.Printf("Count: %d\n", count)
	})

	// Set period for edge count receiver to 0.05s (50ms).
	// Note: The edge count callback is only called every 0.05 seconds
	//       if the edge count has changed since the last call!
	he.SetEdgeCountCallbackPeriod(50)

	fmt.Print("Press enter to exit.")
	fmt.Scanln()

}
