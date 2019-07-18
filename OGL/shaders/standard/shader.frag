/**
    Implements a fragment shader for all main calculations of a fragment's color

    @author       D3PSI
    @version      0.0.1 02.12.2019
    
    @file         shader.vert
    @brief        Implementation of a fragment shader for all main calculations of a fragment's color
*/
#version 330 core

in vec2 outTex;

out vec4 FragColor;

uniform sampler2D inTexture;

void main() {

    FragColor = texture(inTexture, outTex);

}