#!/bin/bash

# Start the Drogon application
cd ./build  
cmake ..
make
./prebid_api_dynamic

