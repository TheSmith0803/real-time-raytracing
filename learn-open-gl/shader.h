#ifndef SHADER_H
#define SHADER_H

class shader {
public:

	unsigned int ID;

	shader(const char* vertexShaderCode, const char* fragmentShadeCode)
	{
		//get the shader files as strings and convert them to c style strings
		const char* vertexShaderSource = get_file_contents(vertexShaderCode).c_str();
		const char* fragmentShaderSource = get_file_contents(fragmentShadeCode).c_str();

		//compile shaders and check for errors
		unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
		unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(vertex, 1, &vertexShaderSource, NULL);
		glShaderSource(fragment, 1, &fragmentShaderSource, NULL);
		glCompileShader(vertex);
		glCompileShader(fragment);

		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);

		//delete shaders once they are linked to the program 
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	void activate() const
	{
		glUseProgram(ID);
	}

	void unbind() const
	{
		glUseProgram(0);
	}

	void del() const
	{
		glDeleteProgram(ID);
	}


private:

	std::string get_file_contents(const char* filename)
	{
		std::ifstream in(filename, std::ios::binary);
		if (in)
		{
			std::string contents;
			in.seekg(0, std::ios::end);
			contents.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&contents[0], contents.size());
			in.close();
			return(contents);
		}
		std::cout << "ERROR? Make sure you typed the shader file namer correctly..." << std::endl;
		throw(errno);
	}
};

#endif
