#version 330
in vec3 a_Position;
in vec2 v_UV;

const float c_PI=3.14f;
uniform sampler2D u_RGBTexture;
uniform sampler2D u_texture2;
uniform sampler2D u_DigitTexture;
uniform sampler2D u_NumTexture;
uniform float u_Time;

layout(location=0) out vec4 FragColor;
layout(location=1) out vec4 FragColor1;

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

vec4 test()
{
    vec2 newUV = v_UV;
    float dx =0.1f * sin (v_UV.y * 6 * c_PI + u_Time);
    float dy =0.1f * sin (v_UV.x * 6 * c_PI + u_Time);
    newUV += vec2(dx,dy);
    vec4 sampleColor = texture(u_RGBTexture,newUV);
    FragColor =sampleColor;
    return FragColor;
}



vec4 circle()
{
    vec2 newUV = v_UV; // 0~1  왼쪽위 0,0 
    vec2 center = vec2(0.5, 0.5);
    
    float d = distance(newUV, center);
    
    vec4 newColor = vec4(0);
    
    float value = sin(4*c_PI*d*4 - 3*u_Time);
    
    newColor = vec4(value);

    FragColor = newColor;
    return FragColor;
}

vec4 Flag()
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
    return FragColor;
    
    
}



vec4 Q1()
{
    //그림그려보기
    
    vec2 newUV = vec2(v_UV.x, v_UV.y); // left bottom =(0,0) right Top = (1,1);
    float x = newUV.x; //0~1
    float y = 1-abs(2 * (v_UV.y - 0.5)); // 0 ~ 1 ~ 0
    vec4 newColor = texture(u_RGBTexture, vec2(x, y));
 
    FragColor = newColor;
    return FragColor;
   
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

vec4 Q3()
{
    //그림그려보기
    vec2 newUV = vec2(v_UV.x, v_UV.y); // left bottom =(0,0) right Top = (1,1);
    float x = fract(newUV.x * 3); //0~1
    float y = (floor(newUV.x * 3)) / 3 + v_UV.y / 3;
    vec4 newColor = texture(u_RGBTexture, vec2(x, y));
    FragColor = newColor;
    return FragColor;
   
}


vec4 Brick_Horizental()
{
    //그림그려보기
     vec2 newUV = vec2(v_UV.x, v_UV.y); // left bottom =(0,0) right Top = (1,1);
     float rCount=6.0f;
     float sAmount =0.5f;

    float x = fract(newUV.x * rCount)+floor(newUV.y* rCount+1)*sAmount; //0~1
    float y = fract(newUV.y * rCount); // 0~1 , 0~1 
    vec4 newColor = texture(u_RGBTexture, vec2(x, y));
    FragColor = newColor;
    return FragColor;
}

vec4 Brick_Vertical()
{
    //그림그려보기
    vec2 newUV = vec2(v_UV.x, v_UV.y); // left bottom =(0,0) right Top = (1,1);
    float x = fract(newUV.x * 2); //0~1
    float y = fract(newUV.y * 2)+floor(newUV.x* 2)*0.5f; // 0~1 , 0~1 
    vec4 newColor = texture(u_texture2, vec2(x, y));
    FragColor = newColor;
    return FragColor;
   
}

vec4 TestUV()
{
   //그림그려보기
    vec2 newUV = vec2(v_UV.x, v_UV.y); // left bottom =(0,0) right Top = (1,1);
    vec4 newColor = texture(u_DigitTexture, newUV);
    FragColor = newColor;
    return FragColor;
}

vec4 Digit_Num()
{
   
    float tx = v_UV.x;
    float ty = v_UV.y;

   // int digit = 0;
   // float offX = digit-1;
   // float offY = (digit/6); 

    int digit = int(u_Time)%10;
    int tileindex = (digit+9)%10;

    float offX = float(tileindex%5)/5;
    float offY = floor(tileindex/5.0f)/2; 

    tx = tx * 0.2f + offX;
    ty = ty * 0.5f + offY;

    vec4 newColor = texture(u_NumTexture, vec2(tx,ty));
    FragColor = newColor;
    return FragColor;
}


void main()
{
    //circle();
    //Flag();
    //Q1();
    //Brick_Horizental();
    //TestUV();

    FragColor =  Digit_Num();
    FragColor1=  vec4(1,0,0,0);

}
