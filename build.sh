#!/bin/bash

echo "start make clean && make..."
make clean && make

echo "start execute..."
./si-server
