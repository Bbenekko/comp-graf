#version 410

in data {
  vec3 n;   // normal no espaço de iluminação
  vec3 l;   // vetor até a luz
  vec3 v;   // vetor até o observador
} v;

uniform vec4 lamb;
uniform vec4 ldif;
uniform vec4 lspe;

uniform vec4 mamb;
uniform vec4 mdif;
uniform vec4 mspe;
uniform float mshi;

//in vec4 color;
out vec4 fcolor;

void main (void)
{
  vec3 n = normalize(v.n);
  vec3 l = normalize(v.l);
  vec3 v = normalize(v.v);

  float ndotl = max(dot(n, l), 0.0);
  vec4 color = mamb * lamb + mdif * ldif * ndotl;

  if (ndotl > 0.0) {
    vec3 r = reflect(-l, n);
    float spec = pow(max(dot(r, v), 0.0), mshi);
    color += mspe * lspe * spec;
  }

  fcolor = color;
}

