#include "game/Game.h"
#include "utils/Logger.h"

#include <SOIL2/SOIL2.h>

GLuint loadTexture(const char *texImagePath) {
	GLuint textureID;
	textureID = SOIL_load_OGL_texture(texImagePath,
		
	SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (textureID == 0) 
		Utils::Logger::Log("could not find texture file", texImagePath);

	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	return textureID;
}

int main() {

    Game::Game *g = new Game::Game();
    
    GLuint texture_1 = loadTexture("../res/textures/texture1.jpg");
    Utils::Logger::Log("Texture Loaded: ", texture_1);

    g->Run();
    
    Utils::Logger::Log("Application exiting");
}
