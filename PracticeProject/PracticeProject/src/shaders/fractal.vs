#version 330 core

in vec3 aPos;

out vec4 colorGS;

uniform float time;
uniform float threshold;

vec2 uv = vec2(aPos.x, aPos.y);

vec2 random2(vec2 st)
{
    return fract(sin(vec2(dot(st, vec2(127.1, 311.7)), dot(st, vec2(269.5, 183.3)))) * 43758.5453123);
}

vec2 subdivide(vec2 st, float t)
{
    if (t > threshold)
    {
        vec2 r = random2(st);
        vec2 new_st = vec2(st.x + r.x * t, st.y + r.y * t);
        return 0.5 * (subdivide(st, t * 0.5) + subdivide(new_st, t * 0.5));
    }
    else
    {
        return st;
    }
}

void main()
{
    vec2 st = uv * 2.0 - 1.0;
    st *= 2.0;

    vec2 sub_st = subdivide(st, time);

    colorGS = vec4(sub_st, 0.0, 1.0);
}