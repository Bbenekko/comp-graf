#version 410

in data {
  vec3 n;
  vec3 l;
  vec3 v;
  vec2 tc;
} v;

out vec4 color;

uniform mat4 Mv; 
uniform mat4 Mn; 
uniform mat4 Mvp;

uniform vec4 lpos;  // light pos in eye space
uniform vec4 lamb;
uniform vec4 ldif;
uniform vec4 lspe;

uniform vec4 mamb;
uniform vec4 mdif;
uniform vec4 mspe;
uniform float mshi;

uniform sampler2D decal;
uniform sampler2D gloss; // brilho

void main (void)
{
  vec3 n = normalize(v.n);
  vec3 l = normalize(v.l);
  vec3 v = normalize(v.v);

  float ndotl = max(dot(n, l), 0.0);

  vec4 base = mamb * lamb + mdif * ldif * ndotl;
  vec4 texc = texture(decal, v.st);

  vec4 c = base * texc;

  if (ndotl > 0.0) {
    vec3 r = reflect(-l, n);
    float spec = pow(max(dot(r, v), 0.0), mshi);
    vec3 g = texture(gloss, v.st).rgb;
    c += vec4(mspe.rgb * lspe.rgb * spec * g, 0.0);
  }

  color = c;
}