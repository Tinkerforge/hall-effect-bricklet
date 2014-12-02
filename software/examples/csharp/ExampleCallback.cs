using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "XYZ"; // Change to your UID

	// Callback function for edge count callback 
	static void EdgeCountCB(BrickletHallEffect sender, long edge_count, bool value)
	{
		System.Console.WriteLine("Edge Count: " + edge_count);
	}

	static void Main() 
	{
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletHallEffect he = new BrickletHallEffect(UID, ipcon); // Create device object

		ipcon.Connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Set Period for edge count callback to 0.05s (50ms)
		// Note: The edge count callback is only called every 50ms if the
		//       edge count has changed since the last call!
		he.SetEdgeCountCallbackPeriod(50);

		// Register edge count callback to function EdgeCountCB
		he.EdgeCount += EdgeCountCB;

		System.Console.WriteLine("Press enter to exit");
		System.Console.ReadLine();
		ipcon.Disconnect();
	}
}
