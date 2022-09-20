#version 330 core
in vec2 texCoord;
in vec4 colors;
out vec4 fFragClr;

uniform sampler2D texture0;
uniform bool noTint;

void main() 
{
    //  fill texture color
    fFragClr = texture(texture0, texCoord);
    
    if(noTint == false)
    {
        fFragClr = (fFragClr * colors);
    }
}
