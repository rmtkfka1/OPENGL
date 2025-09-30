#version 330

in vec3 a_Position;
in vec4 a_Color;
in float a_Value; //0~1 randomSeed
in float a_STime;
in float a_LifeTime;
in float a_Mass;
in float a_Period;
in vec3 a_Vel;
out vec4 v_Color;

uniform float u_radius;
uniform float u_Time;
uniform vec3 u_Force;

const float pi = 3.141592f;
const float c_G = -9.8f;

void raining()
{
	vec4 newPosition =  vec4(a_Position,1);

	float lifeTime =a_LifeTime;
	float newTime = u_Time - a_STime;
	float newAlpha = 1.0f;
	vec3 finalColor = a_Color.rgb;

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

		newPosition.xy += vec2(x,y);
		newAlpha = 1-t/lifeTime;
	}
	else
	{
		newPosition.x += 300;
		newPosition.y += 300;
	}

	
	
	v_Color = vec4(finalColor,newAlpha);
	gl_Position = newPosition;
}


void SinGraph0930()
{
	vec4 newPosition =  vec4(a_Position,1);
	vec4 centerColor = vec4(1,0,0,1);
	vec4 borderColor = vec4(1,1,1,1);
	vec4 newColor = a_Color;
	float lifeTime = a_LifeTime;
	float newTime =  u_Time - a_STime;
	float newAlpha=1.0f;
	
	if(newTime>0)
	{
		float period =a_Period*5;
		float t = fract(newTime/lifeTime)*lifeTime;
		float x = 2*t-1;
		float y = t* sin(2*pi*t*period)* (a_Value-0.5)*2;
		y *= sin(fract(newTime/lifeTime)*pi);
		newPosition.xy += vec2(x,y);
		newAlpha = 1-t/lifeTime;
		newColor = mix(centerColor,borderColor,abs(y*4));
	} 
	else
	{
		newPosition.x =999;
		newPosition.y =999;
	}

	v_Color = vec4(newColor.rgb,newAlpha);
	gl_Position = newPosition;
}


void CircleParticle()
{
	vec4 newPosition =  vec4(a_Position,1);
	float lifeTime = a_LifeTime;
	float newTime =  u_Time - a_STime;
	float newAlpha=1.0f;
	
	if(newTime>0)
	{
		float t = fract(newTime/lifeTime)*lifeTime;
		float tt= t*t;
		float x = sin(a_Value*2*pi);
		float y = cos(a_Value*2*pi);


		//s=s0​+v0​t+21​at2

		float newX = x + 0.5 * 0 * tt;
		float newY = y + 0.5 *c_G  * tt;
		newPosition.xy += vec2(newX,newY); // 파티클의 원 계산

		newAlpha = 1-t/lifeTime;


	
	} 
	else
	{
		newPosition.x =999;
		newPosition.y =999;
	}

	v_Color = vec4(a_Color.rgb,1);
	gl_Position = newPosition;
}


void main()
{
	CircleParticle();

};
