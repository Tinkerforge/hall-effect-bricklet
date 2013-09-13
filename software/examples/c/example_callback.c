
#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_hall_effect.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change to your UID

// Callback function for edge_count callback
void cb_edge_count(int32_t edge_count, bool value, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Edge Count: %d\n", edge_count);
}

int main() {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	HallEffect ehe;
	hall_effect_create(&he, UID, &ipcon); 

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		exit(1);
	}
	// Don't use device before ipcon is connected

	// Set Period for edge_count callback to 0.05s (50ms)
	// Note: The edge_count callback is only called every 50ms if the 
	//       edge_count has changed since the last call!
	hall_effect_set_edge_count_callback_period(&he, 50);

	// Register edge_count callback to function cb_edge_count
	hall_effect_register_callback(&he,
	                              HALL_EFFECT_CALLBACK_EDGE_COUNT,
	                              (void *)cb_edge_count,
	                              NULL);

	printf("Press key to exit\n");
	getchar();
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
}
