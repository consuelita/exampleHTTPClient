//
//  HTTPClient.c
//  exampleHTTPClient
//
//  Created by Adelita Schule on 5/31/18.
//  Copyright © 2018 Operator Foundation. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <unistd.h>

/// To test this in Xcode, add the IP address of the server you want to connect to in Edit Scheme > Arguments > Arguments Passed on Launch

int main(/*the number of command line arguments that we pass in*/int argc, /*The list of arguments*/char *argv[])
{
    // Get the address of the server from the command line arguments and store it in a pointer
    char *address;
    address = argv[1]; // argv[0] is actually the name of the program
    
    // Create the socket
    int client_socket;
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    
    // Connect the socket to an address
    struct sockaddr_in remote_address;
    remote_address.sin_family = AF_INET;
    remote_address.sin_port = htons(80);
    
    // Convert the address string from the command line arguments to a format that can be understood
    inet_aton(address/*the string address*/, &remote_address.sin_addr.s_addr/*Pointer to where we want the address stored*/);
    
    // Connect
    connect(client_socket, (struct sockaddr *) &remote_address, sizeof(remote_address));
    
    char request[] = "GET / HTTP/1.1\r\n\r\n";
    char response[4096];
    
    // Send the request
    send(client_socket, request, sizeof(request), 0);
    
    // Receive the response
    recv(client_socket, &response, sizeof(response), 0);
    
    //Print what we got back from the server
    printf("💌  Response from the server  💌\n%s\n", response);
    
    // Close the socket
    close(client_socket);
    
    return 0;
}


