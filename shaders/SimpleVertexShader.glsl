
#version 330 core

// Input vertex data and color data
layout(location = 0) in vec3 vertexPosition;

void main()
{
	// position of each vertex in homogeneous coordinates
	gl_Position = vec4(vertexPosition, 1.0);
}
