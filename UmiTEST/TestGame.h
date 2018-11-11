#pragma once

#include <Game.h>
#include <gl/glew.h>


class TestGame : public Game
{
public:
	TestGame();
	~TestGame();
	void Init(GLuint screen_width, GLuint screen_height);
	// Inherited via SGE_Game
	virtual void Update(GLfloat dt) override;
	virtual void ProcessInput(GLfloat dt) override;
	virtual void Render() override;
	virtual void MainLoop() override;
private:
	GLfloat color;
};