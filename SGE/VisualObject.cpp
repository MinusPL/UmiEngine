#include "VisualObject.h"
#include "ResourceManager.h"
#include "Game.h"

void VisualObject::Draw()
{
	this->shader.Use();

	glm::mat4 model = transform.ApplyTransform();
	glm::mat4 MVP = Game::instance->camera["main"]->GetProjectionMatrix() * Game::instance->camera["main"]->GetViewMat() * model;
	glm::mat3 normalModel = (glm::mat3) glm::transpose(glm::inverse(model));
	


	/*TODO Update to use textures next!!!*/
	this->shader.SetInteger("hasDiffuseMap", false);
	this->shader.SetInteger("hasSpecularMap", false);
	this->shader.SetInteger("hasNormalMap", false);
	


	this->shader.SetMatrix4("MVP", MVP);
	this->shader.SetMatrix4("model", model);
	this->shader.SetVector3f("viewPos", Game::instance->camera["main"]->transform.Position());

	//Pass material to shader
	this->shader.SetVector3f("material.ambient", this->material.ambient);
	this->shader.SetVector3f("material.diffuse", this->material.diffuse);
	this->shader.SetVector3f("material.specular", this->material.specular);
	this->shader.SetFloat("material.shiness", this->material.shiness);

	this->shader.SetVector3f("dirLight.direction", -0.2f, -1.0f, -0.3f);
	
	float ambientval = 0.4f;
	this->shader.SetVector3f("dirLight.ambient", ambientval, ambientval, ambientval);
	this->shader.SetVector3f("dirLight.diffuse", 0.5f, 0.5f, 0.5f);
	this->shader.SetVector3f("dirLight.specular", 1.0f,1.0f,1.0f);

	this->shader.SetMatrix4("normalModel", normalModel);

	mesh.Draw();
}

VisualObject::VisualObject(ShaderType shaderType)
{
	switch (shaderType)
	{
		case STANDARD:
		{
			this->shader = ResourceManager::GetShader("standard");
			break;
		}
	}
}

VisualObject::~VisualObject()
{

}