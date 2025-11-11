#version 330
in vec3 a_Position;
in vec2 v_UV;
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
    // UV -> 중심 기준
    vec2 uv = v_UV * 2.0 - 1.0;
    float r = length(uv);

    // 반복 주기
    float period = 2.0;
    float t = mod(u_Time, period); // 반복되는 시간 (0 ~ period)

    // 파동 파라미터
    float speed = 1.5;
    float frequency = 15.0;
    float damping = 6.0;

    // 중심에서 퍼지는 물방울
    float wave = sin(frequency * (r - speed * t));

    // 파동 감쇠 (r과 t 합쳐서 항상 반복 가능)
    wave *= exp(-damping * pow(r - speed * t, 2.0));

    // 중심 밝기 강조
    float glow = 1.0 / (0.02 + r * r);

    vec3 color = vec3(0.0, 0.7, 1.0) * (0.5 + 0.5 * wave) * glow;

    FragColor = vec4(color, 1.0);
}