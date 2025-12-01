#version 330
in vec4 v_Color;
layout(location=0) out vec4 FragColor;
layout(location=1) out vec4 FragColor1;

void main()
{
	FragColor= v_Color;
	FragColor1= vec4(1,0,0,0);
};
