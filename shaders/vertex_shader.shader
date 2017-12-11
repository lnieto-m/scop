#version 400

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_color;
layout(location = 2) in vec2 vertexUV;

uniform mat4 rotationy;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 scale;
uniform mat4 translation;
uniform float transition;

out vec3 fragmentColor;
out vec2 UV;
out float transition_value;

void main() {
  fragmentColor = vertex_color;
  mat4 model = translation * rotationy * scale;
  mat4 MVP = projection * model;
  gl_Position = MVP * vec4(vertex_position, 1.0);
  UV = vertexUV;
  transition_value = transition;
}
