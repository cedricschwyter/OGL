/**
    Implements a vertex shader for all main calculations of a vertex' color

    @author       D3PSI
    @version      0.0.1 02.12.2019
    
    @file         shader.vert
    @brief        Implementation of a vertex shader for all main calculations of a vertex' color
*/
#version 330 core

layout(location = 0) in vec3 pos;

void main() {

    gl_Position         = vec4(pos.x, pos.y, pos.z, 1.0);

}