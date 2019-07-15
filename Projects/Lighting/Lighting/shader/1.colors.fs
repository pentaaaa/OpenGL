#version 330 core
out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

in vec3 Normal;
in vec3 FragPos;
void main(){
     //diffuse 漫反射
	 vec3 norm=normalize(Normal);
	 vec3 lightDir=normalize(lightPos-FragPos);
	 float diff=max(dot(norm,lightDir),0.0);
	 vec3 diffuse=diff*lightColor;

	 //specular 镜面
	 float specularStrength=0.5f;
	 vec3 viewDir=normalize(viewPos-FragPos);  //view direction
	 vec3 reflectDir=reflect(-lightDir,norm);  // reflect direction
	 float spec=pow(max(dot(viewDir,reflectDir),0.0),32);
	 vec3 specular=specularStrength*spec*lightColor;


     //ambient 环境
	 float ambientStrength=0.1;
	 vec3 ambient=ambientStrength*lightColor;

	 vec3 result=(ambient+diffuse+specular)*objectColor;
	 FragColor=vec4(result,1.0);
}