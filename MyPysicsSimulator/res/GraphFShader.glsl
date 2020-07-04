#version 120
varying vec4 v_position;
varying vec4 v_normal;
uniform vec3 viewPos;
uniform vec3 objectColor;

vec3 CalLight(vec3 lightPos,vec3 lightColor,float ambient,float specular)
{
    vec3 norm = normalize(v_normal.xyz);

    vec3 ambientLight = ambient*lightColor;

    vec3 lightDir = normalize(lightPos - v_position.xyz);

    float diffuse = max(dot(norm, lightDir),0.0);

    vec3 diffuseLight = diffuse*lightColor;

    vec3 viewDir = normalize(viewPos - v_position.xyz);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

    vec3 specularLight = specular * spec * lightColor;

    return ambientLight+diffuseLight+specularLight;
}


void main()
{
    vec3 lColor1 = vec3(1.0,1.0,1.0);
    //vec3 lPos1 = vec3(0,10000.0,10000.0);
    vec3 lPos1 = viewPos*100;          // 光源的位置
    vec3 light = CalLight(lPos1,lColor1,0.3,0.0);

    vec4 color = vec4(light*objectColor,0.9);

    gl_FragColor = color;
}



