#version 330
in vec3 a_Position;
in vec2 v_UV;

const float c_PI=3.14f;
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

void test()
{
    vec2 newUV = v_UV;
    float dx =0.1f * sin (v_UV.y * 6 * c_PI + u_Time);
    float dy =0.1f * sin (v_UV.x * 6 * c_PI + u_Time);
    newUV += vec2(dx,dy);
    vec4 sampleColor = texture(u_RGBTexture,newUV);
    FragColor =sampleColor;
}



void circle()
{
    vec2 newUV = v_UV; // 0~1  왼쪽위 0,0 
    vec2 center = vec2(0.5, 0.5);
    
    float d = distance(newUV, center);
    
    vec4 newColor = vec4(0);
    
    float value = sin(4*c_PI*d*4 - 3*u_Time);
    
    newColor = vec4(value);

    FragColor = newColor;
}

void Flag()
{
    vec2 newUV = vec2(v_UV.x, 1 - v_UV.y-0.5); // left bottom =(0,0) 
    
    vec4 newColor = vec4(0);
    
    float width = 0.2 * (1 - v_UV.x);
    float sinValue = v_UV.x * 0.2f * sin(newUV.x * 2 * c_PI - u_Time);


    if (newUV.y < sinValue + width && newUV.y > sinValue - width)
    {
        newColor = vec4(1);
    }
    
    FragColor = newColor;
    
    
}



void Q1()
{
    //그림그려보기
    
    vec2 newUV = vec2(v_UV.x, v_UV.y); // left bottom =(0,0) right Top = (1,1);
    float x = newUV.x; //0~1
    float y = 1-abs(2 * (v_UV.y - 0.5)); // 0 ~ 1 ~ 0
    vec4 newColor = texture(u_RGBTexture, vec2(x, y));
 
    FragColor = newColor;
   
}

void Q2()
{
    //그림그려보기
    vec2 newUV = vec2(v_UV.x, v_UV.y); // left bottom =(0,0) right Top = (1,1);
    float x = fract(newUV.x * 3); //0~1
    float y = (2 - floor(newUV.x * 3)) / 3 + v_UV.y / 3;
    vec4 newColor = texture(u_RGBTexture, vec2(x, y));
    FragColor = newColor;
   
}

void Q3()
{
    //그림그려보기
    vec2 newUV = vec2(v_UV.x, v_UV.y); // left bottom =(0,0) right Top = (1,1);
    float x = fract(newUV.x * 3); //0~1
    float y = (floor(newUV.x * 3)) / 3 + v_UV.y / 3;
    vec4 newColor = texture(u_RGBTexture, vec2(x, y));
    FragColor = newColor;
   
}

void testing()
{
    //그림그려보기
    vec2 newUV = vec2(v_UV.x, v_UV.y); // left bottom =(0,0) right Top = (1,1);

    
    newUV.y = 1-abs(2 * (v_UV.y - 0.5)); // 0 ~ 1 ~ 0

    vec4 newColor = texture(u_RGBTexture,newUV);
    FragColor = newColor;
   
}

void testing2()
{
    //그림그려보기
    vec2 newUV = vec2(v_UV.x, v_UV.y); // left bottom =(0,0) right Top = (1,1);

    newUV.x = fract(3.0f * v_UV.x);
    newUV.y = (2-floor(3.0f * v_UV.x))/3.0f + v_UV.y/3.f;

    vec4 newColor = texture(u_RGBTexture,newUV);
    FragColor = newColor;
   
}

void testing3()
{
    //그림그려보기
    vec2 newUV = vec2(v_UV.x, v_UV.y); // left bottom =(0,0) right Top = (1,1);

    newUV.x =fract(2.0f*v_UV.x) + (floor(2.0f * v_UV.y)+1)*0.5f;
    newUV.y =fract(2.0f*v_UV.y);

    vec4 newColor = texture(u_RGBTexture,newUV);
    FragColor = newColor;
   
}


void testing4()
{
    //그림그려보기
    vec2 newUV = vec2(v_UV.x, v_UV.y); // left bottom =(0,0) right Top = (1,1);

    newUV.x =newUV.x;
    newUV.y = (2-floor(v_UV.y*3.0f))/3.0f + fract(v_UV.y*3.0f)/3.0f;

    vec4 newColor = texture(u_RGBTexture,newUV);
    FragColor = newColor;
   
}

void testing5()
{
    //그림그려보기
    vec2 newUV = vec2(v_UV.x, v_UV.y); // left bottom =(0,0) right Top = (1,1);

    newUV.x =fract(2.0f*newUV.x);
    newUV.y =fract(2.0f*newUV.y)+fract((floor(2*v_UV.x))*0.5f);

    vec4 newColor = texture(u_RGBTexture,newUV);
    FragColor = newColor;
   
}

//void my()
//{
//    //그림그려보기
//    vec2 newUV = vec2(v_UV.x, v_UV.y); // left bottom =(0,0) right Top = (1,1);
//    float x = fract(5 *newUV.x);
//    float y = (newUV.y/3.0f )+ 1/3.0f; 
//    vec4 newColor = texture(u_RGBTexture, vec2(x, y));
//    FragColor = newColor;
   
//}


void main()
{
    //circle();
    //Flag();
    //Q1();
    testing3();

}
