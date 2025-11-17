#version 330
in vec3 a_Position;
in vec2 v_UV;

uniform sampler2D u_RGBTexture;
uniform float u_Time;
layout(location=0) out vec4 FragColor;

//void main()
//{
//    vec4 newColor = vec4(0);
    
    
//    //시험에 나왔던것
//    //float color1 = sin(8 * v_UV.x * 3.14f);
//    //float color2 = sin(8 * v_UV.y * 3.14f);
//    //newColor.xyz = vec3(color1 + color2);
    
//    //float Xvalue = pow(abs(sin(8 * v_UV.x * 3.14f)), 0.5f);
//    //float Yvalue = pow(abs(sin(8 * v_UV.y * 3.14f)), 0.5f);
//    //newColor.xyz = vec3(Xvalue*Yvalue);
    
    
    
//    FragColor = newColor;

//}

void main()
{
    vec2 newUV = v_UV;
    float dx =0;
    float dy =u_Time;
    newUV += vec2(dx,dy);
    vec4 sampleColor = texture(u_RGBTexture,newUV);
    FragColor =sampleColor;


}