varying lowp vec3 position;

uniform lowp vec3 normal;

uniform lowp vec3 Light1Position;
uniform lowp vec3 Light1Intensity;

uniform lowp vec3 Light2Position;
uniform lowp vec3 Light2Intensity;

uniform lowp vec3 MaterialReflection;
uniform lowp vec3 MirrorReflection;
uniform lowp float Shininess;


void main()
{
    lowp vec3 v = normalize(-position);

    //temporary variables for light power defining
    lowp vec3 s = normalize(Light1Position - position);
    lowp vec3 r = reflect( -s, normal );
    lowp vec3 s2 = normalize(Light2Position - position);
    lowp vec3 r2 = reflect( -s2, normal );

    //left source of light
    lowp vec4 leftLight = vec4( Light1Intensity * (
                                    MaterialReflection * max( dot(s, normal), 0.0 ) +
                                    MirrorReflection * pow( max( dot(r, v), 0.0 ), Shininess )), 1.0 );
    //right source of light
    lowp vec4 rightLight = vec4( Light2Intensity * (
                                    MaterialReflection * max( dot(s2, normal), 0.0 ) +
                                    MirrorReflection * pow( max( dot(r2, v), 0.0 ), Shininess )), 1.0 );

    // adding also material reflection as diffused light source
    gl_FragColor = vec4(MaterialReflection, 1.0) + rightLight + leftLight;
}
