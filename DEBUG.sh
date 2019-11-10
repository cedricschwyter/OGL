#!/bin/bash
echo "Copying executable to runtime directory..."
cp "bin/Linux/x64/OGL by D3PSI" "OGL/OGL by D3PSI"
echo "Debugging OGL..."
function code { cd OGL/; }
code
gdb -ex run "OGL by D3PSI"
