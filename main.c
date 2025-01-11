#include "server.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    Product catalog[NUM_PRODUCTS];
    initialize_catalog(catalog);

    int client_to_server[NUM_CLIENTS][2]; // Pipes από πελάτη προς server
    int server_to_client[NUM_CLIENTS][2]; // Pipes από server προς πελάτη

    pid_t pids[NUM_CLIENTS];

    // Δημιουργία pipes και fork για τους πελάτες
    for (int i = 0; i < NUM_CLIENTS; i++) {
        if (pipe(client_to_server[i]) == -1 || pipe(server_to_client[i]) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }

        pids[i] = fork();

        if (pids[i] == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pids[i] == 0) {
            // Διεργασία πελάτη (client)
            close(client_to_server[i][0]); // Κλείνουμε την είσοδο του pipe πελάτη προς server
            close(server_to_client[i][1]); // Κλείνουμε την έξοδο του pipe server προς πελάτη
            handle_client(i, client_to_server[i], server_to_client[i], catalog);
            exit(0);
        } else {
            // Διεργασία server (γονέας)
            close(client_to_server[i][1]); // Κλείνουμε την έξοδο του pipe πελάτη προς server
            close(server_to_client[i][0]); // Κλείνουμε την είσοδο του pipe server προς πελάτη
        }
    }

    // Λογική του server
    int total_requests = 0;
    int successful_requests = 0;
    int failed_requests = 0;
    float total_revenue = 0;

    for (int i = 0; i < NUM_CLIENTS; i++) {
        for (int j = 0; j < REQUESTS_PER_CLIENT; j++) {
            int product_id;
            read(client_to_server[i][0], &product_id, sizeof(int));
            total_requests++;

            if (catalog[product_id].item_count > 0) {
                catalog[product_id].item_count--;
                successful_requests++;
                total_revenue += catalog[product_id].price;
                write(server_to_client[i][1], "success", sizeof("success"));
            } else {
                failed_requests++;
                write(server_to_client[i][1], "failure", sizeof("failure"));
            }

            sleep(1); // Προσομοίωση χρόνου επεξεργασίας
        }
    }

    // Περιμένουμε για να ολοκληρωθούν οι πελάτες
    for (int i = 0; i < NUM_CLIENTS; i++) {
        waitpid(pids[i], NULL, 0);
    }

    // Δημιουργία αναφοράς
    generate_report(catalog, total_requests, successful_requests, failed_requests, total_revenue);

    return 0;
}
