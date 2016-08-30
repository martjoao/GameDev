#pragma once

#include <vector>

#include <glm\mat4x4.hpp>
#include "mesh.h"
#include "shader.h"

/*
    RenderObject Class, taken from the framework provided with some modifications
*/
 
class RenderObject	{
public:
    RenderObject(void);
    RenderObject(Mesh*m, Shader*s, GLuint t = 0);
    ~RenderObject(void);

    Mesh*	GetMesh()	const			{ return mesh; }
    void	SetMesh(Mesh*m)				{ mesh = m; }

    Shader* GetShader()		const		{ return shader; }
    void	SetShader(Shader*s)			{ shader = s; }

    GLuint	GetTexture()		const	{ return texture; }
    void	SetTexture(GLuint tex)		{ texture = tex; }

    void	SetModelMatrix(glm::mat4x4 mat) { modelMatrix = mat; }
    glm::mat4x4 GetModelMatrix()	const	{ return modelMatrix; }

    virtual void Update(float msec);

    virtual void Draw() const;

    //virtual void Update(float msec);

    void	AddChild(RenderObject &child) {
        children.push_back(&child);
        child.parent = this;
    }

    glm::mat4x4 GetWorldTransform() const {
        return worldTransform;
    }

    const vector<RenderObject*>& GetChildren() const  {
        return children;
    }

protected:
    Mesh*	mesh;
    Shader*	shader;

    GLuint	texture;

    glm::mat4x4 modelMatrix;
    glm::mat4x4 worldTransform;

    RenderObject*			parent;
    vector<RenderObject*>	children;
};

