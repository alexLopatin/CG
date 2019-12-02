#version 120
attribute vec3 pos;
attribute vec3 normal;

uniform float angleX = 0.0;
uniform float angleY = 0.0;
uniform float GlowPow = 1.0f;
uniform float t = 0.0f;
uniform mat4 ProjectionMatrix;
uniform mat4 ModelViewMatrix;

uniform vec3 lightColor = vec3(1.0, 1.0, 1.0);
uniform vec3 lightPos = vec3(0.0, 0.0, -1.7);

void main()
{
	mat4 rotX;
	rotX[0] = vec4(1, 0, 0, 0);
	rotX[1] = vec4(0, cos(angleX), sin(angleX), 0);
	rotX[2] = vec4(0, -sin(angleX), cos(angleX), 0);
	rotX[3] = vec4(0, 0, 0, 1);
	mat4 rotY;
	rotY[0] = vec4(cos(angleY), 0, -sin(angleY), 0);
	rotY[1] = vec4(0, 1, 0, 0);
	rotY[2] = vec4(-sin(angleY), 0, cos(angleY), 0);
	rotY[3] = vec4(0, 0, 0, 1);
	gl_Position = ModelViewMatrix* ProjectionMatrix* vec4(pos.x,
        pos.y,
        pos.z,
        1.0);
    gl_Position =  gl_Position * rotX * rotY;
    vec4 Normal4 = vec4(normal.xyz, 1.0f);
    Normal4 = ModelViewMatrix* ProjectionMatrix * Normal4 * rotX * rotY;
    Normal4 = normalize(Normal4);
    gl_Position.x = gl_Position.x * cos(t);
    float d = distance(gl_Position.xyz, lightPos);
    vec3 L = -pos +lightPos;
    L = normalize(L);
    float dotPr = dot(normal, L);
    if(dotPr < 0.2f)
    	dotPr = 0.2f;
    gl_FrontColor = dotPr *vec4(lightColor, 1.0)*GlowPow;
}
