#version 330

in vec3 a_Position;
in vec4 a_Color;
in float a_Radius;
out vec4 v_Color;

uniform float u_radius;
uniform float u_Time;

const float pi = 3.141592f;

void main()
{
	vec4 newPosition =  vec4(a_Position,1);

	newPosition.x += a_Radius * cos(u_Time*pi);
	newPosition.y += a_Radius * sin(u_Time*pi);

	v_Color = a_Color;
	gl_Position = newPosition;
}
