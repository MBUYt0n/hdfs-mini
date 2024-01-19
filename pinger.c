#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <microhttpd.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define PORT 3001
#define DEST_PORT 3000
#define DEST_IP "127.0.0.1"

enum MHD_Result request_handler(void *cls, struct MHD_Connection *connection,
                                const char *url, const char *method,
                                const char *version, const char *upload_data,
                                size_t *upload_data_size, void **con_cls)
{
    // Connect to the server on port 3000
    int dest_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (dest_socket == -1)
    {
        perror("socket");
        return MHD_NO;
    }

    struct sockaddr_in dest_addr;
    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(DEST_PORT);

    if (inet_pton(AF_INET, DEST_IP, &dest_addr.sin_addr) <= 0)
    {
        perror("inet_pton");
        close(dest_socket);
        return MHD_NO;
    }

    if (connect(dest_socket, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) == -1)
    {
        perror("connect");
        close(dest_socket);
        return MHD_NO;
    }

    // Send a ping to the server on port 3000
    const char *ping_message = "PING";
    send(dest_socket, ping_message, strlen(ping_message), 0);

    close(dest_socket);

    const char *page = "<html><body>PING sent to server on port 3000!</body></html>";
    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(page), (void *)page, MHD_RESPMEM_PERSISTENT);
    MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return MHD_YES;
}

int main()
{
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &request_handler, NULL, MHD_OPTION_END);

    if (daemon == NULL)
    {
        fprintf(stderr, "Failed to start the server.\n");
        return 1;
    }

    printf("Server is running on port %d...\n", PORT);

    // Keep the server running
    while (1)
    {
        sleep(1);
    }

    MHD_stop_daemon(daemon);

    return 0;
}
