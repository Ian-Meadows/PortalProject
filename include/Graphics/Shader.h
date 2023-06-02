//taken from learnopengl.com


#ifndef SHADER_H
#define SHADER_H



#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "glm/glm.hpp"

#include "includes.h"


struct Vector3D;

class Shader
{
public:
	unsigned int ID;
	// constructor generates the shader on the fly
	// ------------------------------------------------------------------------

	Shader(const char* vertexPath, const char* fragmentPath);

	~Shader();

	// activate the shader
	// ------------------------------------------------------------------------
	void use();
	// utility uniform functions
	// ------------------------------------------------------------------------
	void setBool(const std::string &name, bool value);
	// ------------------------------------------------------------------------
	void setInt(const std::string &name, int value);
	// ------------------------------------------------------------------------
	void setFloat(const std::string &name, float value);


	void setVec3(const std::string &name, Vector3D value);
	
	void setMat4(const std::string &name, const glm::mat4 &mat);

private:
	// utility function for checking shader compilation/linking errors.
	// ------------------------------------------------------------------------
	void checkCompileErrors(unsigned int shader, std::string type);
};
#endif