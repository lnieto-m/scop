#version 400

in vec3 fragmentColor;
in vec2 UV;
in float transition_value;

uniform sampler2D myTextureSampler;

out vec4 frag_colour;

void main() {
  vec4 text = vec4(texture(myTextureSampler, UV).rgb, 1.0);
  vec4 colour = vec4(fragmentColor, 1.0);
  frag_colour = mix(text, colour, transition_value);
}
