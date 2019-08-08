#!/bin/bash
echo "Copying executable to executable directory..."
cp "bin/Linux/x64/OGL by D3PSI" "OGL/OGL by D3PSI"
echo "Running OGL..."
function code { cd OGL/; }
code
./"OGL by D3PSI" &
disown
