#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>;  //包含glad来获取所有的弄虚opengl头文件

#include<string>
#include<fstream>
#include<sstream>
#include<iostream>


class Shader {
public:
	//程序ID
	unsigned int ID;

	//构造器读取并构建着色器
	//Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	//使用/激活程序
	//void use();
	////uniform工具函数
	//void setBool(const std::string &name, bool value) const;
	//void setInt(const std::string &name, int value) const;
	//void setFloat(const std::string &name, float value) const;




	Shader(const char* vertexPath, const char* fragmentPath) {
		//1. 从文件路径中获取顶点/片段着色器
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		//保证ifstream对象可以抛出异常：
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try {
			//open the file
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;
			//读取文件的缓冲内容到数据流中
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			//关闭文件处理器
			vShaderFile.close();
			fShaderFile.close();
			//转换数据流到string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure e) {
			std::cout << "error::shader::file_not_succesfully_read" << std::endl;
		}
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();


		//2. compile shader
		unsigned int vertex, fragment;
		int success;
		char infoLog[512];

		//vertex shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		//如果编译错误  打印
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			std::cout << "error::shader::vertex::compilation_failed\n" << infoLog << std::endl;
		}

		//fragment shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);

		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			std::cout << "error::shader::fragment::compilation_failed\n" << infoLog << std::endl;
		}


		//shader program
		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		//print link error
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			std::cout << "error::shader::program::linking_failed\n" << infoLog << std::endl;
		}

		//delete shader ,because it's linked we program ,  don't need
		glDeleteShader(vertex);
		glDeleteShader(fragment);



		

	}
	    void use() {
			glUseProgram(ID);
		}

		void setBool(const std::string &name, bool value) const
		{
			glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
		}
		void setInt(const std::string &name, int value) const
		{
			glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
		}
		void setFloat(const std::string &name, float value) const
		{
			glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
		}
};

#endif