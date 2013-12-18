//
// Created by NiTe Luo on 10/31/13.
//



#ifndef __CC_RENDERER_H_
#define __CC_RENDERER_H_

#include "CCPlatformMacros.h"
#include "RenderCommand.h"
#include "CCGLProgram.h"
#include "CCGL.h"
#include <vector>
#include <stack>

NS_CC_BEGIN

typedef std::vector<RenderCommand*> RenderQueue;

struct RenderStackElement
{
    int renderQueueID;
    size_t currentIndex;
};

class Renderer
{
public:
    static const int vbo_size = 65536 / 6;

    Renderer();
    ~Renderer();

    //TODO manage GLView inside Render itself
    void initGLView();
    
    //TODO support multiple viewport
    void addCommand(RenderCommand* command);
    void addCommand(RenderCommand* command, int renderQueue);
    void pushGroup(int renderQueueID);
    void popGroup();
    
    int createRenderQueue();
    void render();

protected:

    void setupIndices();
    //Setup VBO or VAO based on OpenGL extensions
    void setupBuffer();
    void setupVBOAndVAO();
    void setupVBO();
    void mapBuffers();

    void drawBatchedQuads();
    //Draw the previews queued quads and flush previous context
    void flush();

    void onBackToForeground(Object* obj);

    std::stack<int> _commandGroupStack;
    
    std::stack<RenderStackElement> _renderStack;
    std::vector<RenderQueue> _renderGroups;

    int _lastMaterialID;

    size_t _firstCommand;
    size_t _lastCommand;

    V3F_C4B_T2F_Quad _quads[vbo_size];
    GLushort _indices[6 * vbo_size];
    GLuint _quadVAO;
    GLuint _buffersVBO[2]; //0: vertex  1: indices

    int _numQuads;
    
    bool _glViewAssigned;
};

NS_CC_END

#endif //__CC_RENDERER_H_
