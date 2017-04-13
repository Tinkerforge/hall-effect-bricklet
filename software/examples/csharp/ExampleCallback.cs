using System;
using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "XYZ"; // Change XYZ to the UID of your Hall Effect Bricklet

	// Callback function for edge count callback
	static void EdgeCountCB(BrickletHallEffect sender, long edgeCount, bool value)
	{
		Console.WriteLine("Edge Count: " + edgeCount);
	}

	static void Main()
	{
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletHallEffect he = new BrickletHallEffect(UID, ipcon); // Create device object

		ipcon.Connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Register edge count callback to function EdgeCountCB
		he.EdgeCountCallback += EdgeCountCB;

		// Set period for edge count callback to 0.05s (50ms)
		// Note: The edge count callback is only called every 0.05 seconds
		//       if the edge count has changed since the last call!
		he.SetEdgeCountCallbackPeriod(50);

		Console.WriteLine("Press enter to exit");
		Console.ReadLine();
		ipcon.Disconnect();
	}
}
