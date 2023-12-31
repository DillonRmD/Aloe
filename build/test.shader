#version 330 core

#VERTEX_SHADER
layout(location = 0) in vec3 vertexPosition_modelspace;

uniform mat4 MVP;

void main(){  
  gl_Position = MVP * vec4(vertexPosition_modelspace, 1);
}

#FRAGMENT_SHADER
out vec3 color;
void main(){
  color = vec3(1,0,0);
}