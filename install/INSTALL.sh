#!/bin/bash

echo "Installing dependencies..."

sudo apt update

sudo apt install g++ make gcc cmake xorg-dev libgl1-mesa-dev libglu1-mesa-dev libglfw3-dev libassimp-dev assimp-utils libglm-dev libsdl2-dev libsdl2-2.0-0 libjpeg-dev libwebp-dev libtiff5-dev libsdl2-image-dev libsdl2-image-2.0-0 -y