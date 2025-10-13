#version 330

in vec3 a_Position;
in vec4 a_Color;

out vec4 v_Color;

uniform float u_Time;
const float pi = 3.141592;

void main()
{
	vec4 newPosition =  vec4(a_Position,1);
	float Value = newPosition.x +0.5f; // 0 ~ 1f;
	float dX = 0;
	float height = mix(1.0f,0,Value);
	float dY = Value * 0.7f * sin(2*pi*Value-7.0f *u_Time);
	float newColor =  (sin(2*pi*Value-7.0f *u_Time)+1)*0.5f;
	newPosition += vec4(dX,dY,0,0);
	newPosition.y *= height;

	gl_Position = newPosition;

	v_Color = vec4(newColor);
}
