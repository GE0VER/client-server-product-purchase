#include "server.h"

void handle_client(int client_id, int write_pipe[], int read_pipe[], Product catalog[]) {
    srand(time(NULL) + client_id);

    for (int i = 0; i < REQUESTS_PER_CLIENT; i++) {
        int product_id = rand() % NUM_PRODUCTS;
        write(write_pipe[1], &product_id, sizeof(int));

        char response[10];
        read(read_pipe[0], response, sizeof(response));

        if (strcmp(response, "success") == 0) {
            printf("Client %d: Purchase complete, your total is: %.2f euro.\n", client_id, catalog[product_id].price);
        } else {
            printf("Client %d: Product unavailable, request failed.\n", client_id);
        }

        sleep(1); // Περιμένει πριν στείλει το επόμενο αίτημα
    }
}

