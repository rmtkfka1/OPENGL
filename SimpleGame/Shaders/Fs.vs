#version 330

in vec3 a_Position;
out vec2 v_UV;

//a_POSITION -1 ~ 1  u : (x+1)*0.5 ( 0~ 1 ) , v : (1-y)*0.5 


void main()
{
    vec4 newPosition = vec4(a_Position, 1);
    
    v_UV.x = (newPosition.x + 1) /2;
    v_UV.y = (1 - newPosition.y) /2;
    
    gl_Position = vec4(a_Position, 1);

}
