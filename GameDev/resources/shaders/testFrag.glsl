#version 150 core

in Vertex	{
	vec2 texCoord;
	vec4 colour;
} IN;

out vec4 gl_FragColor;

void main(void)	{	
	gl_FragColor= IN.colour;
	
        
	//gl_FragColor = vec4(0,255,1,1);
}