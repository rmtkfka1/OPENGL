#version 330
in vec4 v_Color;

layout(location=0) out vec4 FragColor;
uniform float u_Time;
uniform int u_Method; // 0:normal  1:BlurH  3:BlurV
uniform sampler2D u_TexID;
uniform sampler2D u_TexID1;


in vec2 v_Tex;

const float weight[5] = float[] (0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);

vec4 BlurH()
{             
    vec2 tex_offset = 1.0 / textureSize(u_TexID, 0); // gets size of single texel
    vec3 result = texture(u_TexID, v_Tex).rgb * weight[0]; // current fragment's contribution

    for(int i = 1; i < 5; ++i)
    {
        result += texture(u_TexID, v_Tex + vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
        result += texture(u_TexID, v_Tex - vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
    }

    return vec4(result, 1.0);
}

vec4 BlurV()
{             
   vec2 tex_offset = 1.0 / textureSize(u_TexID, 0); // gets size of single texel
    vec3 result = texture(u_TexID, v_Tex).rgb * weight[0]; // current fragment's contribution

    for(int i = 1; i < 5; ++i)
    {
        result += texture(u_TexID, v_Tex + vec2(0, tex_offset.y * i)).rgb * weight[i];
        result += texture(u_TexID, v_Tex - vec2(0, tex_offset.y * i)).rgb * weight[i];
    }

    return vec4(result, 1.0);
};


void Vignette()
{
    vec4 color = texture(u_TexID, vec2(v_Tex.x,1-v_Tex.y));

    // 화면 중심에서 거리 계산 (0=center, 1=edge)
    vec2 uv = v_Tex;
    vec2 center = vec2(0.5, 0.5);
    float dist = distance(uv, center);

    float vignette = smoothstep(0.8, 0.5, dist); // 조절 가능
    color.rgb *= mix(1.0, vignette, 0.5);

    FragColor = color;
}

void retro()
{
    // Y 좌표 뒤집기
    vec2 uv = vec2(v_Tex.x, 1.0 - v_Tex.y);

    // 텍스처 색상 샘플링
    vec4 color = texture(u_TexID, uv);

    // -------------------------
    // 1. 색상 양자화 (8-bit 느낌)
    // -------------------------
    float levels = 8.0; // 컬러 레벨
    color.rgb = floor(color.rgb * levels) / levels;

    // -------------------------
    // 2. CRT 스캔라인 효과
    // -------------------------
    float scanline = sin(uv.y * 512.0 * 3.1415 * 2.0) * 0.1; // 진폭 조절
    color.rgb -= scanline;

    // -------------------------
    // 3. 약간의 색상 왜곡 (RGB shift)
    // -------------------------
    float shift = 0.002; // 픽셀 단위
    float r = texture(u_TexID, uv + vec2(shift, 0.0)).r;
    float g = texture(u_TexID, uv).g;
    float b = texture(u_TexID, uv - vec2(shift, 0.0)).b;
    color.rgb = vec3(r, g, b);

    FragColor = color;
}

void Pixelization()
{
  
    float resol = abs(sin(u_Time))*100;
    float tx = floor(v_Tex.x*resol)/resol; //0~1-> 0 , 0.2 ,0.4
    float ty = floor((1-v_Tex.y)*resol)/resol;;

    vec2 uv = vec2(tx, ty);
    FragColor = texture(u_TexID, uv);
}


vec4 Merge()
{          
    const float u_Exposure=0.2f;
    const float gamma = 2.2;
    vec3 hdrColor = texture(u_TexID, v_Tex).rgb;      
    vec3 bloomColor = texture(u_TexID1, v_Tex).rgb;
    hdrColor += bloomColor; 

    vec3 result = vec3(1.0) - exp(-hdrColor * u_Exposure);

    result = pow(result, vec3(1.0 / gamma));
    return vec4(result, 1.0);
} 


void main()
{
    FragColor= vec4(0);

    if(u_Method==0)
    {
        FragColor = texture(u_TexID,vec2(v_Tex.x , 1-v_Tex.y));
    }
    else if(u_Method==1)
    {
        FragColor = BlurH();
    }
    else if(u_Method==2)
    {
        FragColor = BlurV();
    }
        else if(u_Method==3)
    {
        FragColor = Merge();
    }
}