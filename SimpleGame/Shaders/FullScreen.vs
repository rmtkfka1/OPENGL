#version 330

in vec3 a_Position;

uniform vec4 u_Color;

void main()
{
	gl_Position = vec4(a_Position,1);
}
