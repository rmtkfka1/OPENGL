#version 330

in vec3 a_Pos;
in vec2 a_Tex;

out vec2 v_Tex;

uniform vec2 u_Size;
uniform vec2 u_Tran;

void main()
{
	vec4 newPosition = vec4(a_Pos.xyz,1.0f);

	newPosition.xy *= u_Size.xy;
	newPosition.xy += u_Tran.xy; 

	v_Tex = a_Tex;

	gl_Position = newPosition;

}
