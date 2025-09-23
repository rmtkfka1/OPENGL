#version 330

in vec3 a_Position;
in vec4 a_Color;
in float a_Radius;
in float a_STime;
in vec3 a_Vel;
out vec4 v_Color;

uniform float u_radius;
uniform float u_Time;

const float pi = 3.141592f;
const float c_G = -9.8f;

void main()
{
	vec4 newPosition =  vec4(a_Position,1);
	float newTime = u_Time - a_STime;

	if(newTime >0)
	{
		float t = fract(newTime/2.0f)*2.0f;
		float tt = t*t;

		newPosition.x += 0;
		newPosition.y += 0.5f * c_G * tt;
	}
	else
	{
		newPosition.x += 300;
		newPosition.y += 300;
	}

	
	v_Color = a_Color;
	gl_Position = newPosition;

};
