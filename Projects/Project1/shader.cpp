#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>;  //����glad����ȡ���е�Ū��openglͷ�ļ�

#include<string>
#include<fstream>
#include<sstream>
#include<iostream>


class Shader {
public:
	//����ID
	unsigned int ID;

	//��������ȡ��������ɫ��
	//Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	//ʹ��/�������
	//void use();
	////uniform���ߺ���
	//void setBool(const std::string &name, bool value) const;
	//void setInt(const std::string &name, int value) const;
	//void setFloat(const std::string &name, float value) const;




	Shader(const char* vertexPath, const char* fragmentPath) {
		//1. ���ļ�·���л�ȡ����/Ƭ����ɫ��
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		//��֤ifstream��������׳��쳣��
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try {
			//open the file
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;
			//��ȡ�ļ��Ļ������ݵ���������
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			//�ر��ļ�������
			vShaderFile.close();
			fShaderFile.close();
			//ת����������string
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
		//����������  ��ӡ
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