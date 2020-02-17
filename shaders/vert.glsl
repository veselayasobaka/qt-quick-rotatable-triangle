attribute highp vec4 VertexPosition;

varying lowp vec3 position;

uniform highp mat4 matrixMvp;
uniform highp mat4 matrixModel;
uniform highp mat4 matrixView;

void main()
{
    // multiplication of modelview matrix and vertex position
    position = vec3( (matrixView * matrixModel) * VertexPosition);
    gl_Position = matrixMvp * VertexPosition;
}
