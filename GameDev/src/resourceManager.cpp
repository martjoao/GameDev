#include "resourceManager.h"

map<std::string, Mesh*> ResourceManager::meshes;
map<std::string, Shader*> ResourceManager::programs;
map<std::string, Mix_Chunk*> ResourceManager::soundEffects;
map<std::string, Mix_Music*> ResourceManager::musics;
map<std::string, GLuint> ResourceManager::textures;
map<std::string, TTF_Font*> ResourceManager::fonts;


ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{

}

Shader* ResourceManager::createShader(string vertex, string fragment, string geometry , string tcs , string tes)
{
    string id = vertex + "/" + fragment + "/" + geometry + "/" + tcs + "/" + tes;
    map < string, Shader* >::iterator i = programs.find(id);


    Shader* s = NULL;
    if (i != programs.end())
    {
        s = i->second;
    }
    else
    {
        string folder = "resources/shaders/";

        string geo = geometry.empty() ? geometry : folder + geometry;
        string tc = tcs.empty() ? tcs : folder + tcs;
        string ts = tes.empty() ? tes : folder + tes;

        s = new Shader(folder + vertex, folder + fragment, geo, tc, ts);
        programs.insert(std::pair<std::string, Shader*>(id, s));
    }
    return s;

}

RenderObject* ResourceManager::createRenderObject(std::string meshfile, string texfile,
    string vertex, string fragment, string geometry, string tcs , string tes)
{
    //creates mesh
    map < string, Mesh* >::iterator i = meshes.find(meshfile);

    Mesh *m = NULL;

    if (i != meshes.end())
    {
        m = i->second;
    }
    else
    {
        //m = Mesh::LoadMeshFile(meshfile);
        string folder = "resources/meshes/";

        m = Mesh::LoadObj(folder + meshfile);
        meshes.insert(std::pair<std::string, Mesh*>(meshfile, m));
    }

    //loads shaders
    Shader* s1 = createShader(vertex, fragment, geometry, tcs, tes);

    //loads tex
    GLuint tex = loadBmpTex(texfile);

    return new RenderObject(m, s1, tex);

}

Mix_Chunk* ResourceManager::loadAudioChunk(std::string audiofile)
{
    map < string, Mix_Chunk* >::iterator i = soundEffects.find(audiofile);

    Mix_Chunk *m = NULL;

    if (i != soundEffects.end())
    {
        m = i->second;
    }
    else
    {
        string folder = "resources/audio/";

        m = Mix_LoadWAV((folder + audiofile).c_str());
        if (m == NULL)
            std::cout << Mix_GetError() << "\n";
        soundEffects.insert(std::pair<std::string, Mix_Chunk*>(audiofile, m));
    }
    return m;
}

Mix_Music* ResourceManager::loadAudioMusic(std::string audiofile)
{
    map < string, Mix_Music* >::iterator i = musics.find(audiofile);

    Mix_Music *m = NULL;

    if (i != musics.end())
    {
        m = i->second;
    }
    else
    {
        string folder = "resources/audio/";

        m = Mix_LoadMUS((folder + audiofile).c_str());
        if (m == NULL)
            std::cout << Mix_GetError() << "\n";
        musics.insert(std::pair<std::string, Mix_Music*>(audiofile, m));
    }
    return m;
}


GLuint ResourceManager::loadBmpTex(std::string texfile)
{
    map < string, GLuint >::iterator i = textures.find(texfile);

    GLuint t = 0;

    if (i != textures.end())
    {
        t = i->second;
    }
    else
    {
        string folder = "resources/textures/";

        t = loadBMP_custom((folder + texfile).c_str());
        textures.insert(std::pair<std::string, GLuint>(texfile, t));
    }
    return t;
}

GLuint ResourceManager::loadTTFTex(std::string text)
{
    std::string  id = "text/" + text;
    map < string, GLuint >::iterator i = textures.find(id);

    GLuint t = 0;

    if (i != textures.end())
    {
        t = i->second;
    }
    else
    {
        t = loadTTFtex_custom(text);
        textures.insert(std::pair<std::string, GLuint>(id, t));
    }
    return t;
}

TTF_Font* ResourceManager::loadFont(std::string text, int size)
{
    std::stringstream ss;
    ss << text << "/" << size;

    map < string, TTF_Font* >::iterator i = fonts.find(ss.str());

    TTF_Font* t = 0;

    if (i != fonts.end())
    {
        t = i->second;
    }
    else
    {
        string folder = "resources/fonts/";

        t = TTF_OpenFont((folder + text).c_str(), size);;
        fonts.insert(std::pair<std::string, TTF_Font*>(ss.str(), t));
    }
    return t;
}




bool ResourceManager::init()
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
    {
        return false;
    }
    TTF_Init();

   
    return true;
}

void ResourceManager::update()
{

}


void ResourceManager::deleteMeshList()
{
    for (map < string, Mesh * >::iterator i = meshes.begin(); i != meshes.end(); ++i) {
        delete i->second;
    }
    meshes.clear();
}

void ResourceManager::deleteSoundEffectsList()
{
    for (map < string, Mix_Chunk * >::iterator i = soundEffects.begin(); i != soundEffects.end(); ++i) {
        Mix_FreeChunk(i->second);
    }
    soundEffects.clear();
}

void ResourceManager::deleteMusicList()
{
    for (map < string, Mix_Music * >::iterator i = musics.begin(); i != musics.end(); ++i) {
        Mix_FreeMusic(i->second);
    }
    musics.clear();
}

void ResourceManager::deleteTextureList()

{
    for (map < string, GLuint>::iterator i = textures.begin(); i != textures.end(); ++i) {
        glDeleteTextures(1, &i->second);
    }
    textures.clear();
}

void ResourceManager::deleteProgramList()
{
    for (map < string, Shader*>::iterator i = programs.begin(); i != programs.end(); ++i) {
        delete i->second;
    }
    programs.clear();
}

void ResourceManager::deleteFontList()
{
    for (map < string, TTF_Font * >::iterator i = fonts.begin(); i != fonts.end(); ++i) {
        TTF_CloseFont(i->second);
    }
    fonts.clear();
}


void ResourceManager::shutdown()
{
    deleteMeshList();
    deleteSoundEffectsList();
    deleteMusicList();
    deleteTextureList();
    deleteProgramList();
    deleteFontList();

    Mix_CloseAudio();
}


GLuint ResourceManager::loadBMP_custom(const char * imagepath){

    SDL_Surface* surface = SDL_LoadBMP(imagepath);
    if (!surface)
    {
        std::cout << "\nUnable to load image " << imagepath << "\n";
    }
    GLuint texture;

    //Your format checker
    GLenum format = (surface->format->BytesPerPixel == 3) ? GL_BGR : GL_BGRA;
    GLenum iformat = (surface->format->BytesPerPixel == 3) ? GL_RGB : GL_RGBA;


    //Create OpenGL Texture
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, iformat, surface->w, surface->h, 0,
        format, GL_UNSIGNED_BYTE, surface->pixels);

    //Set Some basic parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

    return texture;
    
}


GLuint ResourceManager::loadTTFtex_custom(std::string text)
{
    //Open Font
    TTF_Font* font = loadFont("brlnsdb.ttf", 72);

    SDL_Color color = { 255, 255, 255, 255 };
    SDL_Surface* surface = NULL;
    GLuint texture;


    //Create Surface
    surface = TTF_RenderUTF8_Blended(font, text.c_str(), color);

    //Your format checker
    GLenum format = (surface->format->BytesPerPixel == 3) ? GL_RGB : GL_RGBA;

    //Create OpenGL Texture
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, format, surface->w, surface->h, 0,
        format, GL_UNSIGNED_BYTE, surface->pixels);

    //Set Some basic parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


    SDL_FreeSurface(surface);
    return texture;
}
