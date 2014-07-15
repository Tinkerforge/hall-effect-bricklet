import com.tinkerforge.BrickletHallEffect;
import com.tinkerforge.IPConnection;

public class ExampleCallback {
	private static final String HOST = "localhost";
	private static final int PORT = 4223;
	private static final String UID = "XYZ"; // Change to your UID

	// Note: To make the example code cleaner we do not handle exceptions. Exceptions you
	//       might normally want to catch are described in the documentation
	public static void main(String args[]) throws Exception {
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletHallEffect he = new BrickletHallEffect(UID, ipcon); // Create device object

		ipcon.connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Set Period for edge_count callback to 0.05s (50ms)
		// Note: The edge_count callback is only called every 50ms if the
		//       edge_count has changed since the last call!
		he.setEdgeCountCallbackPeriod(50);

		// Add and implement edge count listener
		he.addEdgeCountListener(new BrickletHallEffect.EdgeCountListener() {
			public void edgeCount(long edge_count, boolean value) {
				System.out.println("Edge Count: " + edge_count);
			}
		});

		System.out.println("Press key to exit"); System.in.read();
		ipcon.disconnect();
	}
}
