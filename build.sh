#!/bin/bash

# Set default value for argument
build_type=${1:-"debug"}

 
# Get the current date and time
timestamp=$(date +"%Y-%m-%d--%H:%M:%S")
mkdir -p LOG/${build_type}

# Run the make command with the specified argument
make config="$build_type" 2>&1 | tee "LOG/${build_type}/${timestamp}build.LOG"
