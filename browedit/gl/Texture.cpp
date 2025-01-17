#include <Windows.h> //for warning
#include <glad/glad.h>
#include "Texture.h"

#include <browedit/util/FileIO.h>
#include <iostream>
#include <stb/stb_image.h>

namespace gl
{
	Texture::Texture(const std::string& fileName, bool flipSelection) : fileName(fileName)
	{
		int comp;
		stbi_set_flip_vertically_on_load(flipSelection);

		std::istream* is = util::FileIO::open(fileName);
		if (!is)
		{
			std::cerr << "Texture: Could not open " << fileName << std::endl;
			id = 0;
			return;
		}
		is->seekg(0, std::ios_base::end);
		std::size_t len = is->tellg();
		char* buffer = new char[len];
		is->seekg(0, std::ios_base::beg);
		is->read(buffer, len);
		delete is;

		unsigned char* data = stbi_load_from_memory((stbi_uc*)buffer, (int)len, &width, &height, &comp, 4);
		if (!data)
		{
			std::cerr<<"Texture: "<<fileName<<" could not load; error: "<<stbi_failure_reason()<<std::endl;
			return;
		}

		for (int x = 0; x < width; x++)
		{
			for (int y = 0; y < height; y++)
			{
				if (data[4 * (x + width * y) + 0] > 250 &&
					data[4 * (x + width * y) + 1] < 5 &&
					data[4 * (x + width * y) + 2] > 250)
				{
					int totalr = 0;
					int totalg = 0;
					int totalb = 0;
					int total = 0;
					for (int xx = -1; xx <= 1; xx++)
					{
						for (int yy = -1; yy <= 1; yy++)
						{
							int xxx = x + xx;
							int yyy = y + yy;
							if (xxx < 0 || xxx >= width || yyy < 0 || yyy >= height)
								continue;
							if (data[4 * (xxx + width * yyy) + 0] > 250 && data[4 * (xxx + width * yyy) + 1] < 5 && data[4 * (xxx + width * yyy) + 2] > 250)
								continue;
							if (data[4 * (xxx + width * yyy) + 3] == 0)
								continue;
							totalr += data[4 * (xxx + width * yyy) + 0];
							totalg += data[4 * (xxx + width * yyy) + 1];
							totalb += data[4 * (xxx + width * yyy) + 2];
							total++;
						}
					}
					if (total > 0)
					{
						data[4 * (x + width * y) + 0] = totalr / total;
						data[4 * (x + width * y) + 1] = totalg / total;
						data[4 * (x + width * y) + 2] = totalb / total;
					}

					data[4 * (x + width * y) + 3] = 0;
				}
			}
		}


		//std::cout << "Texture: loaded " << fileName << std::endl;;
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		stbi_image_free(data);
	}


	Texture::Texture(int width, int height) : width(width), height(height)
	{
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	void Texture::setSubImage(char* data, int x, int y, int width, int height)
	{
		bind();
		glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}

	void Texture::bind()
	{
		glBindTexture(GL_TEXTURE_2D, id);
	}
}