#include "ShaderLibrary.h"
#include <iostream>
#include <filesystem>
#include "GLErrorLogger.h"
namespace fs = std::filesystem;

ShaderLibrary* ShaderLibrary::libInstance = 0;

ShaderLibrary::ShaderLibrary() { }

bool ShaderLibrary::LoadShaders()
{
	std::vector<std::string> sdrPath;

	for (const fs::path& entry : fs::directory_iterator(shadersPath))
	{
		std::string currentFilename = entry.stem().string();
		std::string currentPath = entry.parent_path().string();

		if (std::find(sdrPath.begin(), sdrPath.end(), entry.stem().string()) == sdrPath.end())
		{
			// load shader if it is not contained
			sdrPath.push_back(currentFilename);
			Shader* shdToLoad = new Shader(currentFilename);
			std::string vtxPath = currentPath + "/" + currentFilename + ".vert";
			std::string fragPath = currentPath + "/" + currentFilename + ".frag";

			if (fs::exists(fs::path(vtxPath)) && fs::exists(fs::path(fragPath)))
				shdToLoad->Load(vtxPath.c_str(), fragPath.c_str());
			else
			{
				printf("ShaderLibrary: Unable to load shaders for %s !", currentFilename.c_str());
				UnloadShaders();
				return false;
			}

			loadedShaders.push_back(shdToLoad);
		}
	}

	return true;
}

void ShaderLibrary::UnloadShaders()
{
	for (auto it = loadedShaders.begin(); it != loadedShaders.end(); ++it)
	{
		delete* it;
	}
}

Shader* ShaderLibrary::GetShader(const std::string& shaderName)
{
	for (auto it = loadedShaders.begin(); it != loadedShaders.end(); ++it)
	{
		if ((*it)->Name == shaderName)
		{
			return *it;
		}
	}

	return NULL;
}

ShaderLibrary* ShaderLibrary::GetInstance()
{
	if (!libInstance)
		libInstance = new ShaderLibrary;
	return libInstance;
}

void ShaderLibrary::SetShaderPath(const std::string& path)
{
	shadersPath = path;
}

void ShaderLibrary::SetPVGlobal(const glm::mat4& proj, const glm::mat4& view)
{
	for (auto it = loadedShaders.begin(); it != loadedShaders.end(); ++it)
	{
		(*it)->use();
		(*it)->setMat4("proj", proj);

		if ((*it)->Name == "skybox")
		{
			glm::mat4 view2 = glm::mat4(glm::mat3(view));

			(*it)->setMat4("view", view2);
		}
		else
		{
			(*it)->setMat4("view", view);
		}
	}
}

void ShaderLibrary::SetGlobalLight(const glm::vec3& pos, const glm::vec3& diffuse, const glm::vec3& viewPos)
{
	for (auto it = loadedShaders.begin(); it != loadedShaders.end(); ++it)
	{
		(*it)->use();
		(*it)->setVec3("light.diffuse", diffuse);
		(*it)->setVec3("light.position", pos);
		(*it)->setVec3("viewPos", viewPos);
	}
}