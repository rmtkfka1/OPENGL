#version 330
in vec4 v_Color;

layout(location=0) out vec4 FragColor;
uniform float u_Time;
uniform sampler2D u_TexID;

in vec2 v_Tex;

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


void main()
{
Pixelization();
}