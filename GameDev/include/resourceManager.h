#ifndef _RESOURCE_MANAGER_H
#define _RESOURCE_MANAGER_H

#include <map>
#include <string>
#include <sstream>

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "renderableEntity.h"
#include "renderManager.h"


/*
    Handles resources, such as meshes and audio, 
    in order for them not to be loaded twice into 
    memory
*/
class ResourceManager
{
public:
    ResourceManager();
    ~ResourceManager();

    bool init();
    void update();
    void shutdown();
    
    //loads a mesh to creates a renderObject (a single mesh is not loaded twice)
    static RenderObject* createRenderObject(string meshfile, string texfile, 
        string vertex, string fragment, string geometry = "", string tcs = "", string tes = "");
    
    //shader creation
    static Shader * createShader(string vertex, string fragment, string geometry = "", string tcs = "", string tes = "");
    
    //audio loading (SFX and Music)
    static Mix_Chunk* loadAudioChunk(std::string audiofile);
    static Mix_Music* loadAudioMusic(std::string audiofile);
    
    //texture loading (from image or text)
    static GLuint loadBmpTex(std::string bmpfile);
    static TTF_Font* loadFont(std::string text, int size);
    static GLuint loadTTFTex(std::string text);


private:
    //maps the meshes to their filename
    static map<std::string, Mesh*> meshes;
    static map<std::string, Mix_Chunk*> soundEffects;
    static map<std::string, Mix_Music*> musics;
    static map<std::string, GLuint> textures;
    static map<std::string, Shader*> programs;
    static map<std::string, TTF_Font*> fonts;

    void deleteMeshList();
    void deleteSoundEffectsList();
    void deleteMusicList();
    void deleteTextureList();
    void deleteProgramList();
    void deleteFontList();

    static GLuint loadBMP_custom(const char * imagepath);
 
    static GLuint loadTTFtex_custom(std::string text);

};

#endif