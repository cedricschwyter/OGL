/**
    Implements a vertex shader for all main calculations of a vertex' color

    @author       D3PSI
    @version      0.0.1 02.12.2019
    
    @file         shader.vert
    @brief        Implementation of a vertex shader for all main calculations of a vertex' color
*/
#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 nor;
layout(location = 2) in vec2 tex;
layout(location = 3) in vec3 tan;
layout(location = 4) in vec3 bit;

out vec2 outTex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {

    gl_Position         = projection * view * model * vec4(pos, 1.0);
    outTex              = tex;

}