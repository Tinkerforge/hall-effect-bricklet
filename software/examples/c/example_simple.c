#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_hall_effect.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change to your UID

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	HallEffect he;
	hall_effect_create(&he, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Get current edge count without reset
	uint32_t edge_count;
	if(hall_effect_get_edge_count(&he, false, &edge_count) < 0) {
		fprintf(stderr, "Could not get edge count without reset, probably timeout\n");
		return 1;
	}

	printf("Edge Count: %d\n", edge_count);

	printf("Press key to exit\n");
	getchar();
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
