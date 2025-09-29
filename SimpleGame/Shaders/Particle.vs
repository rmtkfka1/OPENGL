#version 330

in vec3 a_Position;
in vec4 a_Color;
in float a_Radius;
in float a_STime;
in float a_LifeTime;
in float a_Mass;
in vec3 a_Vel;
out vec4 v_Color;

uniform float u_radius;
uniform float u_Time;
uniform vec3 u_Force;

const float pi = 3.141592f;
const float c_G = -9.8f;

void main()
{
	vec4 newPosition =  vec4(a_Position,1);

	float lifeTime =a_LifeTime;
	float newTime = u_Time - a_STime;
	float newAlpha = 1.0f;

	if(newTime >0)
	{
		float t = fract(newTime/1)*lifeTime; 
		float tt = t*t;

		float forceX = u_Force.x + 0 * a_Mass;
		float forceY = u_Force.y + c_G * a_Mass;

		float ax=  forceX / a_Mass;
		float ay=  forceY / a_Mass;

		float x =  (a_Vel.x * t) + (0.5 * ax * tt);
		float y =  (a_Vel.y * t) + (0.5 * ay * tt);

		newPosition.xy += vec2(0,0);
		newAlpha = 1-t/lifeTime;
	}
	else
	{
		newPosition.x += 300;
		newPosition.y += 300;
	}

	
	
	v_Color = vec4(a_Color.rgb,newAlpha);
	gl_Position = newPosition;

};
