// // // // #include <microhttpd.h>
// // // // #include <stdio.h>
// // // // #include <string.h>

// // // // #define PORT 3000
// // // // #define POSTBUFFERSIZE 512

// // // // enum MHD_Result request_handler(void *cls, struct MHD_Connection *connection,
// // // //                                 const char *url, const char *method,
// // // //                                 const char *version, const char *upload_data,
// // // //                                 size_t *upload_data_size, void **con_cls)
// // // // {
// // // //     if (strcmp(method, "POST") == 0 && strcmp(url, "/upload") == 0)
// // // //     {
// // // //         // Handle file upload
// // // //         printf("Received file data: %.*s\n", (int)(*upload_data_size), upload_data);

// // // //         const char *page = "<html><body>File uploaded successfully!</body></html>";
// // // //         struct MHD_Response *response = MHD_create_response_from_buffer(strlen(page), (void *)page, MHD_RESPMEM_PERSISTENT);
// // // //         MHD_queue_response(connection, MHD_HTTP_OK, response);
// // // //         MHD_destroy_response(response);

// // // //         return MHD_YES;
// // // //     }

// // // //     // Handle other types of requests or routes
// // // //     const char *page = "<html><body>Hello, this is a simple REST API!</body></html>";
// // // //     struct MHD_Response *response = MHD_create_response_from_buffer(strlen(page), (void *)page, MHD_RESPMEM_PERSISTENT);
// // // //     MHD_queue_response(connection, MHD_HTTP_OK, response);
// // // //     MHD_destroy_response(response);

// // // //     return MHD_YES;
// // // // }

// // // // int main()
// // // // {
// // // //     struct MHD_Daemon *daemon;

// // // //     daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
// // // //                               &request_handler, NULL, MHD_OPTION_END);

// // // //     if (daemon == NULL)
// // // //     {
// // // //         fprintf(stderr, "Failed to start the server.\n");
// // // //         return 1;
// // // //     }

// // // //     printf("Server is running on port %d...\n", PORT);
// // // //     getchar(); // Press Enter to stop the server

// // // //     MHD_stop_daemon(daemon);

// // // //     return 0;
// // // // }

// // // #include <stdio.h>
// // // #include <stdlib.h>
// // // #include <string.h>
// // // #include <unistd.h>
// // // #include <sys/socket.h>
// // // #include <arpa/inet.h>

// // // #define PORT 3000
// // // #define MAX_REQUEST_SIZE 8192

// // // void handle_request(int client_socket)
// // // {
// // //     char request[MAX_REQUEST_SIZE];
// // //     ssize_t bytes_received = recv(client_socket, request, sizeof(request) - 1, 0);
// // //     if (bytes_received == -1)
// // //     {
// // //         perror("recv");
// // //         close(client_socket);
// // //         return;
// // //     }

// // //     // Null-terminate the received data to treat it as a string
// // //     request[bytes_received] = '\0';

// // //     // Parse the request to check for the method and URL
// // //     const char *method = strtok(request, " ");
// // //     const char *url = strtok(NULL, " ");

// // //     if (method != NULL && url != NULL && strcmp(method, "POST") == 0 && strcmp(url, "/upload") == 0)
// // //     {
// // //         // Handle file upload
// // //         // Extract the file data from the request (this is a simplified example)
// // //         // You would need to implement proper handling for multipart/form-data
// // //         const char *page = "HTTP/1.1 200 OK\r\nContent-Length: 31\r\n\r\n<html><body>File uploaded successfully!</body></html>";
// // //         send(client_socket, page, strlen(page), 0);
// // //     }
// // //     else
// // //     {
// // //         // Handle other types of requests or routes
// // //         const char *page = "HTTP/1.1 200 OK\r\nContent-Length: 44\r\n\r\n<html><body>Hello, this is a simple REST API!</body></html>";
// // //         send(client_socket, page, strlen(page), 0);
// // //     }

// // //     close(client_socket);
// // // }

// // // int main()
// // // {
// // //     int server_socket = socket(AF_INET, SOCK_STREAM, 0);
// // //     if (server_socket == -1)
// // //     {
// // //         perror("socket");
// // //         return 1;
// // //     }

// // //     struct sockaddr_in server_addr = {
// // //         .sin_family = AF_INET,
// // //         .sin_port = htons(PORT),
// // //         .sin_addr.s_addr = INADDR_ANY,
// // //     };

// // //     if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
// // //     {
// // //         perror("bind");
// // //         close(server_socket);
// // //         return 1;
// // //     }

// // //     if (listen(server_socket, 10) == -1)
// // //     {
// // //         perror("listen");
// // //         close(server_socket);
// // //         return 1;
// // //     }

// // //     printf("Server is running on port %d...\n", PORT);

// // //     while (1)
// // //     {
// // //         struct sockaddr_in client_addr;
// // //         socklen_t client_addr_len = sizeof(client_addr);
// // //         int client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);

// // //         if (client_socket == -1)
// // //         {
// // //             perror("accept");
// // //             continue;
// // //         }

// // //         handle_request(client_socket);
// // //     }

// // //     close(server_socket);

// // //     return 0;
// // // }

// // #include <microhttpd.h>
// // #include <stdio.h>
// // #include <string.h>
// // #include <unistd.h>

// // #define PORT 3000

// // enum MHD_Result request_handler(void *cls, struct MHD_Connection *connection,
// //                                 const char *url, const char *method,
// //                                 const char *version, const char *upload_data,
// //                                 size_t *upload_data_size, void **con_cls)
// // {
// //     // Log received ping
// //     if (strcmp(method, "POST") == 0 && strcmp(url, "/ping") == 0)
// //     {
// //         printf("Received PING from server on port 3001.\n");
// //         return MHD_YES;
// //     }

// //     // Handle other types of requests or routes
// //     const char *page = "<html><body>Hello, this is a simple REST API!</body></html>";
// //     struct MHD_Response *response = MHD_create_response_from_buffer(strlen(page), (void *)page, MHD_RESPMEM_PERSISTENT);
// //     MHD_queue_response(connection, MHD_HTTP_OK, response);
// //     MHD_destroy_response(response);

// //     return MHD_YES;
// // }

// // int main()
// // {
// //     struct MHD_Daemon *daemon;

// //     daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
// //                               &request_handler, NULL, MHD_OPTION_END);

// //     if (daemon == NULL)
// //     {
// //         fprintf(stderr, "Failed to start the server.\n");
// //         return 1;
// //     }

// //     printf("Server is running on port %d...\n", PORT);

// //     // Keep the server running
// //     while (1)
// //     {
// //         sleep(1);
// //     }

// //     MHD_stop_daemon(daemon);

// //     return 0;
// // }

// #include <microhttpd.h>
// #include <stdio.h>
// #include <string.h>
// #include <unistd.h>

// #define PORT 3000

// enum MHD_Result request_handler(void *cls, struct MHD_Connection *connection,
//                                 const char *url, const char *method,
//                                 const char *version, const char *upload_data,
//                                 size_t *upload_data_size, void **con_cls)
// {
//     if (strcmp(method, "POST") == 0 && strcmp(url, "/ping") == 0)
//     {
//         // Log received ping
//         printf("Received PING from server on port 3001.\n");

//         const char *page = "<html><body>PING received successfully!</body></html>";
//         struct MHD_Response *response = MHD_create_response_from_buffer(strlen(page), (void *)page, MHD_RESPMEM_PERSISTENT);
//         MHD_queue_response(connection, MHD_HTTP_OK, response);
//         MHD_destroy_response(response);

//         return MHD_YES;
//     }

//     // Handle other types of requests or routes
//     const char *page = "<html><body>Hello, this is a simple REST API!</body></html>";
//     struct MHD_Response *response = MHD_create_response_from_buffer(strlen(page), (void *)page, MHD_RESPMEM_PERSISTENT);
//     MHD_queue_response(connection, MHD_HTTP_OK, response);
//     MHD_destroy_response(response);

//     return MHD_YES;
// }

// int main()
// {
//     struct MHD_Daemon *daemon;

//     daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
//                               &request_handler, NULL, MHD_OPTION_END);

//     if (daemon == NULL)
//     {
//         fprintf(stderr, "Failed to start the server.\n");
//         return 1;
//     }

//     printf("Server is running on port %d...\n", PORT);

//     // Keep the server running
//     while (1)
//     {
//         sleep(1);
//     }

//     MHD_stop_daemon(daemon);

//     return 0;
// }

#include <microhttpd.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define PORT 3000

enum MHD_Result request_handler(void *cls, struct MHD_Connection *connection,
                                const char *url, const char *method,
                                const char *version, const char *upload_data,
                                size_t *upload_data_size, void **con_cls)
{
    if (strcmp(method, "POST") == 0 && strcmp(url, "/ping") == 0)
    {
        // Log received ping to a file
        FILE *logFile = fopen("ping_log.txt", "a");
        if (logFile != NULL)
        {
            fprintf(logFile, "Received PING from server on port 3001.\n");
            fclose(logFile);
        }

        const char *page = "<html><body>PING received successfully!</body></html>";
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(page), (void *)page, MHD_RESPMEM_PERSISTENT);
        MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);

        return MHD_YES;
    }

    // Handle other types of requests or routes
    const char *page = "<html><body>Hello, this is a simple REST API!</body></html>";
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
