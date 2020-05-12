#version 330 core

// Ouput data
out vec4 color;

void main(){

	// Output color = color specified in the vertex shader,
	// interpolated between all 3 surrounding vertices
	color = vec4(1.0f, 0.5f, 0.2f, 1.0f);

}
