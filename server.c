#include "server.h"

// Αρχικοποίηση του καταλόγου προϊόντων
void initialize_catalog(Product catalog[]) {
    for (int i = 0; i < NUM_PRODUCTS; i++) {
        sprintf(catalog[i].description, "Product %d", i);
        catalog[i].price = (float)(rand() % 1000) / 10.0; // Τυχαία τιμή από 0.0 έως 100.0
        catalog[i].item_count = 2; // Αρχικοποίηση με 2 μονάδες ανά προϊόν
    }
}

// Δημιουργία αναφοράς
void generate_report(Product catalog[], int total_requests, int successful_requests, int failed_requests, float total_revenue) {
       printf("\nSummary:\n");
    printf("Total requests: %d\n", total_requests);
    printf("Successful requests: %d\n", successful_requests);
    printf("Failed requests: %d\n", failed_requests);
    printf("Total revenue: %.2f euros\n", total_revenue);
}
