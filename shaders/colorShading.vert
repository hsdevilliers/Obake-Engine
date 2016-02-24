#version 130

in vec2 vertexPosition; //2 dimensional vector as input

void main()
{
	gl_Position.xy = vertexPosition; //Set the xy-position of the vertex shader
	gl_Position.z = 0.0; //Set the z-position of the vertex shader
	gl_Position.w - 1.0;
}