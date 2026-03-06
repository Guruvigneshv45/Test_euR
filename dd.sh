#!/bin/bash

DRIVER_NAME="my_driver"
DRIVER_PATH="./$DRIVER_NAME.ko"

echo "Loading device driver: $DRIVER_NAME"

# Check if module already loaded
if lsmod | grep -q "$DRIVER_NAME"; then
    echo "Driver already loaded."
    exit 0
fi

# Load driver
sudo insmod $DRIVER_PATH

# Check if loading succeeded
if [ $? -eq 0 ]; then
    echo "Driver loaded successfully."
else
    echo "Failed to load driver."
    exit 1
fi

# Show module in lsmod
lsmod | grep $DRIVER_NAME
