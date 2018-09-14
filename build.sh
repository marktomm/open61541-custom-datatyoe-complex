#!/bin/bash

gcc --std=c99 server_types_custom.c open62541.c -o server
gcc --std=c99 client_types_custom.c open62541.c -o client
