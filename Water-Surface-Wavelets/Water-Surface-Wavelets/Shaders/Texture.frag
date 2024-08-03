#version 460

out vec4 FragColor;
	
in vec2 TexCoords;
	
uniform sampler2D tex;

void main()
{                
    FragColor = texture(tex, TexCoords);
}