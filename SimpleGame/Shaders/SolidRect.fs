#version 330
in vec4 v_Color;


layout(location=0) out vec4 FragColor;

void main()
{
	if(v_Color.b>0.5f)
	{
		discard;
	}
	else
	{
		FragColor=v_Color;
	}

}
