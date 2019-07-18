/**
    Implements a vertex shader for all main calculations of a vertex' color

    @author       D3PSI
    @version      0.0.1 02.12.2019
    
    @file         shader.vert
    @brief        Implementation of a vertex shader for all main calculations of a vertex' color
*/
#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 col;
layout(location = 2) in vec2 tex;

out vec3 outCol;
out vec2 outTex;

void main() {

    gl_Position         = vec4(pos, 1.0);
    outCol              = col;
    outTex              = tex;

}