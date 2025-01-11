#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#define NUM_PRODUCTS 20
#define NUM_CLIENTS 5
#define REQUESTS_PER_CLIENT 10

// Δομή για τα προϊόντα
typedef struct {
    char description[50];
    float price;
    int item_count;
} Product;

// Δηλώσεις συναρτήσεων
void initialize_catalog(Product catalog[]);
void generate_report(Product catalog[], int total_requests, int successful_requests, int failed_requests, float total_revenue);

#endif
