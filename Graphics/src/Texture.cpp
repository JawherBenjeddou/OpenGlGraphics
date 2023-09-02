
#include "Texture.h"
#include"stb/stb_image.h"
#include "DebugUtils.h"



// @param[in] PATH path of the texture.
//@param[in] TexType texture type written in form of texture_type where type can be (diffuse or specular).
Texture::Texture(const char* PATH, const std::string& TexType) :
	m_ID(0),
	m_Width(0),
	m_Height(0),
	m_nrChannels(0),
	m_TexType(TexType)
{
	GLCall(glGenTextures(1, &m_ID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_ID));
	// set the texture wrapping/filtering options (on currently bound texture)
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	// load and generate the texture
	unsigned char* image = stbi_load(PATH, &m_Width, &m_Height, &m_nrChannels, 0);
	if (image)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	//stbi_set_flip_vertically_on_load(true); //FLIP IMAGE AFTER LOADED
	stbi_image_free(image);
}



Texture::~Texture()
{
	glDeleteTextures(1, &m_ID);
}

void Texture::Bind(const uint32_t& unit) const {
	glActiveTexture(GL_TEXTURE0+unit);
	glBindTexture(GL_TEXTURE_2D, m_ID);
}

void Texture::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

uint32_t Texture::getID() const
{
	return m_ID;
}

std::string Texture::getType() const
{
	return m_TexType;
}
