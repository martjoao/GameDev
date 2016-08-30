#version 150 core

in Vertex	{
	vec2 texCoord;
} IN;

out vec4 gl_FragColor;

uniform sampler2D textureSampler;

void main(void)	{	
       
        gl_FragColor = texture2D( textureSampler, IN.texCoord );
}