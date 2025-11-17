#version 330
in vec3 a_Position;
in vec2 v_UV;

const float c_PI=3.14f;
uniform sampler2D u_RGBTexture;
uniform float u_Time;
layout(location=0) out vec4 FragColor;

const vec2 texelSize = vec2(1.0/431.0, 1.0/432.0);

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
    float dx =0.1f * sin (v_UV.y * 6 * c_PI + u_Time);
    float dy =0.1f * sin (v_UV.x * 6 * c_PI + u_Time);
    newUV += vec2(dx,dy);
    vec4 sampleColor = texture(u_RGBTexture,newUV);
    FragColor =sampleColor;
}


//GPT
/*void main()
{
    float kernel[9] = float[](
        1.0/16, 2.0/16, 1.0/16,
        2.0/16, 4.0/16, 2.0/16,
        1.0/16, 2.0/16, 1.0/16
    );

    vec4 colorSum = vec4(0.0);
    int index = 0;

    for (int y = -1; y <= 1; ++y)
    {
        for (int x = -1; x <= 1; ++x)
        {
            vec2 offset = vec2(float(x), float(y)) * texelSize;
            vec4 sampleColor = texture(u_RGBTexture, v_UV + offset);
            colorSum += sampleColor * kernel[index];
            index++;
        }
    }

    FragColor = colorSum;
}*/

