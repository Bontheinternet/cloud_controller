#!/bin/bash
# Knulli Port Launch Script for Cloud Controller

# Set working directory to the port's installation path
PORT_DIR="$(dirname "$0")"
cd "$PORT_DIR"

# Export necessary environment variables for SDL and audio on RG40XXV
export SDL_VIDEODRIVER=x11
export SDL_AUDIODRIVER=alsa

# Make executable if not already
chmod +x cloud_controller

# Launch the synthesizer binary
./cloud_controller