#version 330

#define MAX_POINTS 100

in vec3 a_Position;
in vec4 a_Color;

out vec4 v_Color;
uniform float u_Time;

uniform vec4 u_Points[MAX_POINTS];
const float pi = 3.141592;
//const vec4 c_Points[] = vec4[](vec4(0,0,2,2),vec4(0.5,0,3,3),vec4(-0.3f,-0.3f,4,4));

void Flag()
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

void Wave()
{
	vec4 newPosition =  vec4(a_Position,1);

	float dx =0;
	float dy =0;

	vec2 pos = vec2(a_Position.xy);
	vec2 cen = vec2(0,0);
	float dist = distance(pos,cen);
	float v = 2* clamp(0.5 -dist,0,1);
	float newColor = v * sin(dist*20*pi- 30.0f * u_Time ) ;
	gl_Position = newPosition;
	v_Color = vec4(newColor);

}


void RainDrop()
{
	vec4 newPosition =  vec4(a_Position,1);

	float dx =0;
	float dy =0;


	vec2 pos = vec2(a_Position.xy);
	float newColor= 0;

	for(int i=0; i<MAX_POINTS; ++i)
	{	
		//float newTime = sin(1.5*(u_Time - u_Points[i].z));
		//float newF = clamp(newTime,0,1);
		float STime = u_Points[i].z;
		float LTime = u_Points[i].w;
		float newTime = u_Time - STime;
		if(newTime>0)
		{
			float baseTime	= fract(newTime/LTime);
			float oneMinus  = 1-baseTime;
			float t			= baseTime * LTime;
			float range		= baseTime * LTime/10;
			vec2 cen		= u_Points[i].xy;
			float dist		= distance(pos,cen);
			float v			= 15*clamp(range -dist,0,1);
			newColor		+= oneMinus * v * sin(dist*40*pi- 20.0f * u_Time ) ;
		}
	}

	gl_Position = newPosition;
	v_Color = vec4(newColor);

}

void main()
{
	RainDrop();
}
