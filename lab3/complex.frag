#version 120

in vec4 col;
void main()
{
	//if(!gl_FrontFacing)
    gl_FragColor = gl_Color;
    gl_FragDepth = gl_FragCoord.z;
}
