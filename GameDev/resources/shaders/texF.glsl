#version 150 core

in Vertex	{
	vec2 texCoord;
	vec4 colour;
        vec3 normal;
} IN;

out vec4 gl_FragColor;

uniform sampler2D textureSampler;

void main(void)	{	
	//gl_FragColor= IN.colour;
        vec3 normal = normalize(IN.normal);
	vec3 color = (texture2D( textureSampler, IN.texCoord )).rgb;
        vec3 lightDir = vec3(0,0,1);
        vec3 I = (vec3(1, 1, 1) * 0.2) + vec3(1, 1, 1) *(0.6*(dot(normal, lightDir)));
        
        gl_FragColor = vec4(I * color, 1);
        //gl_FragColor = vec4(normal, 1);
	//gl_FragColor = vec4(0,255,1,1);
}