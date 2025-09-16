#version 330

in vec3 a_Position;
in vec4 a_Color;
out vec4 v_Color;

uniform float u_radius;
uniform float u_Time;

const float pi = 3.141592f;

void main()
{
	vec4 newPosition =  vec4(a_Position,1);

	//newPosition.x += u_radius * cos(u_Time*pi);
	//newPosition.y += u_radius * sin(u_Time*pi);

	float value = 2*fract(u_Time*0.5f)-1.0f; //-1 ~1 
	float rad = (value+1)*pi; // 0~ÆÄÀÌ
	newPosition.x += cos(rad);
	newPosition.y += sin(rad);

	v_Color = a_Color;
	gl_Position = newPosition;
}
