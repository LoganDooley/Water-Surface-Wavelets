#version 460

out vec4 FragColor;
	
in vec2 TexCoords;
	
uniform sampler2D tex;
	
void main()
{             
    vec2 texCol = texture(tex, TexCoords).rg;      
    FragColor = vec4(texCol, 1.0, 1.0);
}