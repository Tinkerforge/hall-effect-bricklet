import com.tinkerforge.IPConnection;
import com.tinkerforge.BrickletHallEffect;

public class ExampleCallback {
	private static final String HOST = "localhost";
	private static final int PORT = 4223;

	// Change XYZ to the UID of your Hall Effect Bricklet
	private static final String UID = "XYZ";

	// Note: To make the example code cleaner we do not handle exceptions. Exceptions
	//       you might normally want to catch are described in the documentation
	public static void main(String args[]) throws Exception {
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletHallEffect he = new BrickletHallEffect(UID, ipcon); // Create device object

		ipcon.connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Add edge count listener
		he.addEdgeCountListener(new BrickletHallEffect.EdgeCountListener() {
			public void edgeCount(long edgeCount, boolean value) {
				System.out.println("Edge Count: " + edgeCount);
			}
		});

		// Set period for edge count callback to 0.05s (50ms)
		// Note: The edge count callback is only called every 0.05 seconds
		//       if the edge count has changed since the last call!
		he.setEdgeCountCallbackPeriod(50);

		System.out.println("Press key to exit"); System.in.read();
		ipcon.disconnect();
	}
}
