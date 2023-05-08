#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <map>
#include <vector>
#include <list>
#include "stb_image.h"
using namespace std;

class createwindow
{
protected:
    unsigned int SCR_WIDTH  ;
    unsigned int SCR_HEIGHT ;
    GLFWwindow* window;
    static int xx, yy;
    static float xpos;
    static float ypos;
    

    bool mouseable;
    string na;
public:
    static float yset;
    createwindow()
    {

    }
    createwindow(unsigned int width,unsigned int height,string name)
    {
        mouseable = true;
        SCR_WIDTH = width;
        SCR_HEIGHT = height;
        na = name;
       
        xx = width;
        yy = height;
        
        initialize();
    }
    void initialize()
    {
        // glfw: initialize and configure
    // ------------------------------
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        // glfw window creation
        // --------------------
        window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT,na.c_str(), NULL, NULL);
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            exit(-1);
        }
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetScrollCallback(window, scroll_callback);
        

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            exit(-1);
        }
    }
    static void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
    {
        xpos = static_cast<float>(xposIn);
        ypos = static_cast<float>(yposIn);
    }
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
    {
        yset += static_cast<float>(yoffset)*0.1*yset;
        
    }

    float mousex()
    {
        return xpos;
    }
    void setmydata(float* ff)
    {
       
    }
    float mousey()
    {
        return ypos;
    }
    float mousescroll()
    {
        return yset;
    }

    void processInput()
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

    }
    void disableMouse()
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        mouseable = false;
    }
    void normalMouse()
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        mouseable = true;
    }
    
   
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
        xx = width; yy = height;
    }
    GLFWwindow* value()
    {
        return window;
    }
    float x()
    {
        return xx;
    }
    float y()
    {
        return yy;
    }
};
class Shader
{
private:
    unsigned int shaderProgram;
    string vertexCode;
    string fragmentCode;
    string geometryCode;
    fstream f1;
    fstream f2;
    fstream f3;
    string name;
    const char* vertexShaderSource;
    const char* fragmentShaderSource;
    const char* geometryShaderSource;
    void buildshader()
    {
        // build and compile our shader program
    // ------------------------------------
    // vertex shader
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);
        // check for shader compile errors
        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
            std::cout << name << endl;
        }
        // fragment shader
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);
        // check for shader compile errors
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
            std::cout << name << endl;
        }
        // link shaders
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        // check for linking errors
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
            std::cout << name << endl;
        }
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }
    void buildshader2()
    {
        // build and compile our shader program
   // ------------------------------------
   // vertex shader
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);
        // check for shader compile errors
        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
            std::cout << name << endl;
        }
        // fragment shader
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);
        // check for shader compile errors
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
            std::cout << name << endl;
        }
        // geometry shader
        unsigned int geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometryShader, 1, &geometryShaderSource, NULL);
        glCompileShader(geometryShader);
        glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(geometryShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
            std::cout << name << endl;
        }
        // link shaders
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glAttachShader(shaderProgram, geometryShader);
        glLinkProgram(shaderProgram);
        // check for linking errors
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
            std::cout << name << endl;
        }
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }
public:
    Shader(string vf, string ff)
    {
        name = vf;
        f1.open(vf, ios::in | ios::out | ios::binary);
        if (!f1)
        {
            cout << "Failed vertexCode Open!" << vf << endl;
            exit(0);
        }




        f1.seekg(0, ios::end);
        unsigned int lenv = f1.tellg();
        string temp;
        temp.resize(lenv);
        f1.seekg(0, ios::beg);
        f1.read((char*)temp.c_str(), lenv);

        unsigned int pos1, pos2;
        pos1 = temp.find("#version");
        pos2 = temp.rfind("}");

        vertexCode = temp.substr(pos1, pos2 - pos1 + 1);



        f2.open(ff, ios::in | ios::out | ios::binary);
        if (!f2)
        {
            cout << "Failed fragmentCode Open!" << ff << endl;
            exit(0);
        }


        f2.seekg(0, ios::end);
        unsigned int lenf = f2.tellg();

        temp.resize(lenf);
        f2.seekg(0, ios::beg);
        f2.read((char*)temp.c_str(), lenf);

        pos1 = temp.find("#version");
        pos2 = temp.rfind("}");

        fragmentCode = temp.substr(pos1, pos2 - pos1 + 1);



        vertexShaderSource = vertexCode.c_str();

        fragmentShaderSource = fragmentCode.c_str();
        buildshader();
    }
    Shader(string vf, string ff, string gf)
    {
        name = vf;
        f1.open(vf, ios::in | ios::out | ios::binary);
        if (!f1)
        {
            cout << "Failed vertexCode Open!" << vf << endl;
            exit(0);
        }

        f1.seekg(0, ios::end);
        unsigned int lenv = f1.tellg();
        string temp;
        temp.resize(lenv);
        f1.seekg(0, ios::beg);
        f1.read((char*)temp.c_str(), lenv);

        unsigned int pos1, pos2;
        pos1 = temp.find("#version");
        pos2 = temp.rfind("}");

        vertexCode = temp.substr(pos1, pos2 - pos1 + 1);



        f2.open(ff, ios::in | ios::out | ios::binary);
        if (!f2)
        {
            cout << "Failed fragmentCode Open!" << ff << endl;
            exit(0);
        }
        f2.seekg(0, ios::end);
        unsigned int lenf = f2.tellg();
        temp.resize(lenf);
        f2.seekg(0, ios::beg);
        f2.read((char*)temp.c_str(), lenf);
        pos1 = temp.find("#version");
        pos2 = temp.rfind("}");
        fragmentCode = temp.substr(pos1, pos2 - pos1 + 1);

        f3.open(gf, ios::in | ios::out | ios::binary);
        if (!f3)
        {
            cout << "Failed fragmentCode Open!" << gf << endl;
            exit(0);
        }
        f3.seekg(0, ios::end);
        unsigned int leng = f3.tellg();
        temp.resize(leng);
        f3.seekg(0, ios::beg);
        f3.read((char*)temp.c_str(), leng);
        pos1 = temp.find("#version");
        pos2 = temp.rfind("}");
        geometryCode = temp.substr(pos1, pos2 - pos1 + 1);


        vertexShaderSource = vertexCode.c_str();
        fragmentShaderSource = fragmentCode.c_str();
        geometryShaderSource = geometryCode.c_str();
        buildshader2();
    }
    void use()
    {
        glUseProgram(shaderProgram);
    }
    void setBool(const std::string& name, bool value) const
    {
        glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), (int)value);
    }
    void setInt(const std::string& name, int value) const
    {
        glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
    }
    void setFloat(const std::string& name, float value) const
    {
        glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value);
    }
    void setVec4(const std::string& name, glm::vec4 value)
    {
        glUniform4f(glGetUniformLocation(shaderProgram, name.c_str()), value.x, value.y, value.z, value.w);
    }
    void setVec3(const std::string& name, glm::vec3 value)
    {
        glUniform3f(glGetUniformLocation(shaderProgram, name.c_str()), value.x, value.y, value.z);
    }
    void setVec2(const std::string& name, glm::vec2 value)
    {
        glUniform2f(glGetUniformLocation(shaderProgram, name.c_str()), value.x, value.y);
    }
    void setMat3(const std::string& name, const glm::mat3& mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    void setMat4(const std::string& name, const glm::mat4& mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    unsigned int id()
    {
        return shaderProgram;
    }
    ~Shader()
    {
        glDeleteProgram(shaderProgram);
        f1.close();
        f2.close();
    }

};
class basicdraw
{
private:
    float* vertices;
    int verticesize;
public:
    unsigned int VBO, VAO;
    basicdraw(float* inputvertices, int inputsize)
    {
        vertices = inputvertices;
        verticesize = inputsize;
        setbuffer();
    }
    
    void setbuffer()
    {

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, verticesize, vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }

   
    void draw(unsigned int s)
    {
        glUseProgram(s);
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0, verticesize / 12);
    }

    ~basicdraw()
    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }
};
class indexedDrawing
{
private:
    unsigned int VBO, VAO, EBO;
    float* vertices; int verticessize;
    unsigned int* indices; int indicessize;
public:
    indexedDrawing(float* vertice,int verticesize,unsigned int* indice,int indicesize)
    {
        vertices = vertice;
        indices = indice;
        verticessize = verticesize;
        indicessize = indicesize;
        setbuffer();
    }
    void setbuffer()
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, verticessize, vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicessize, indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

    }

    void draw(unsigned int shaderProgram)
    {
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO); 
        glDrawElements(GL_TRIANGLES, indicessize/4, GL_UNSIGNED_INT, 0);
    }

    ~indexedDrawing()
    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }
};
class textRender
{
private:
    struct Character {
        GLuint TextureID;   // ID handle of the glyph texture
        glm::ivec2 Size;    // Size of glyph
        glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
        GLuint Advance;    // Horizontal offset to advance to next glyph
    };
    std::map<GLchar, Character> Characters;
    GLuint VAO, VBO;
public:
    textRender()
    {
        // FreeType
        FT_Library ft;
        // All functions return a value different than 0 whenever an error occurred
        if (FT_Init_FreeType(&ft))
            std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

        // Load font as face
        FT_Face face;
        if (FT_New_Face(ft, "arial.ttf", 0, &face))
            std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

        // Set size to load glyphs as
        FT_Set_Pixel_Sizes(face, 0, 48*2);

        // Disable byte-alignment restriction
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        // Load first 128 characters of ASCII set
        for (GLubyte c = 0; c < 128; c++)
        {
            // Load character glyph 
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
                continue;
            }
            // Generate texture
            GLuint texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
            );
            // Set texture options
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // Now store character for later use
            Character character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                face->glyph->advance.x
            };
            Characters.insert(std::pair<GLchar, Character>(c, character));
        }
        glBindTexture(GL_TEXTURE_2D, 0);
        // Destroy FreeType once we're finished
        FT_Done_Face(face);
        FT_Done_FreeType(ft);


        // Configure VAO/VBO for texture quads
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    void RenderText(Shader& shader, string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        // Activate corresponding render state	
        shader.use();
        glUniform3f(glGetUniformLocation(shader.id(), "textColor"), color.x, color.y, color.z);
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(VAO);

        // Iterate through all characters
        std::string::const_iterator c;
        for (c = text.begin(); c != text.end(); c++)
        {
            Character ch = Characters[*c];

            GLfloat xpos = x + ch.Bearing.x * scale;
            GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

            GLfloat w = ch.Size.x * scale;
            GLfloat h = ch.Size.y * scale;
            // Update VBO for each character
            GLfloat vertices[6][4] = {
                { xpos,     ypos + h,   0.0, 0.0 },
                { xpos,     ypos,       0.0, 1.0 },
                { xpos + w, ypos,       1.0, 1.0 },

                { xpos,     ypos + h,   0.0, 0.0 },
                { xpos + w, ypos,       1.0, 1.0 },
                { xpos + w, ypos + h,   1.0, 0.0 }
            };
            // Render glyph texture over quad
            glBindTexture(GL_TEXTURE_2D, ch.TextureID);
            // Update content of VBO memory
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            // Render quad
            glDrawArrays(GL_TRIANGLES, 0, 6);
            // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
        }
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_BLEND);
    }
};
class button
{
protected:
    textRender a;
    string b;
    float x1,y1,x2,y2;
    float tx1, ty1,tx2,ty2;
    
    float vertice[18];
    createwindow window;
    float sc;
    glm::vec3 tcolor;
    glm::vec3 bcolor;
    bool flag1;
    bool flag11;
    bool flag2;
    bool flag3;
public:
    button(createwindow windowname,string name,float scale,float x1Pos,float y1Pos,float x2Pos,float y2Pos,glm::vec3 textcolor,glm::vec3 buttoncolor)
    {
        window = windowname;
        
        b = name;
        tx1 = x1Pos;
        ty1 = y1Pos;
        tx2 = x2Pos;
        ty2 = y2Pos;
        x1 = (2*x1Pos-10.0) / window.x() - 1.0;
        y1 = (2*y1Pos-10.0) / window.y() - 1.0;
        x2 = 2*(x2Pos) / window.x() - 1.0;
        y2 = 2*(y2Pos) / window.y() - 1.0;
        tcolor = textcolor;
        bcolor = buttoncolor;
        sc = scale;
        
        vertice[0] = x1; vertice[1] = y1; vertice[2] = 0.01f;
        vertice[3] = x1; vertice[4] = y2; vertice[5] = 0.01f;
        vertice[6] = x2; vertice[7] = y2; vertice[8] = 0.01f;
        vertice[9] = x1; vertice[10] = y1; vertice[11] = 0.01f;
        vertice[12] = x2; vertice[13] = y2; vertice[14] = 0.01f;
        vertice[15] = x2; vertice[16] = y1; vertice[17] = 0.01f;
        flag11 = false;
        flag2 = false;
    }
    void render(Shader& textshader,Shader& buttonshader)
    {
        
        if (glfwGetMouseButton(window.value(), GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
        {
            if (flag11)
            {
                flag1 = mouseposition();
            }  
            flag11 = false;
        }
        else
        {
            if (flag1)
            {
                flag2 = true;
                
            }
            flag1 = false;
        }
        if (mouseposition() && glfwGetMouseButton(window.value(), GLFW_MOUSE_BUTTON_1) == GLFW_RELEASE)
        {
            flag11 = true;
        }
        else
        {
            flag11 = false;
            flag2 = false;
        }
            
        glm::vec3 aaa ; glm::vec3 bbb;

        if (flag11)
        {
            aaa = glm::vec3(0.1, 0.1, 0.1);
        }
        else if (flag1)
        {
            aaa = glm::vec3(0.05, 0.05, 0.05);
        }
        else
        {
            aaa = glm::vec3(0, 0, 0);
        }

        basicdraw temp(vertice,sizeof(vertice));
        buttonshader.use();
        buttonshader.setVec3("ourColor", bcolor + aaa);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        temp.draw(buttonshader.id());
        glDisable(GL_BLEND);
        a.RenderText(textshader, b, tx1, ty1, sc, tcolor);
        
        
    }
    bool mouseposition()
    {
        return (fabs(window.mousex() * 1600 /window.x() - (tx1 + tx2) / 2) < fabs(tx1 - tx2) / 2) && (fabs((window.y()-window.mousey() )* 900 / window.y() - (ty1 + ty2) / 2) < fabs(ty1 - ty2) / 2);
    }
    bool click()
    {
        if (flag2)
        {
            flag2 = false;
            return true;
        }
        return false;
    }
};
class textureRGB
{
private:
    string file;
public:
    unsigned int id;
    textureRGB(string fileaddress)
    {
        file = fileaddress;
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        // load image, create texture and generate mipmaps
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
        unsigned char* data = stbi_load(file.c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
    }
};
class textureRGBA
{
private:
    string file;
public:
    unsigned int id;
    textureRGBA(string fileaddress)
    {
        file = fileaddress;
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        // load image, create texture and generate mipmaps
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
        unsigned char* data = stbi_load(file.c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
    }
};
class skybox {
private:
    vector<std::string> faces;
public:
    unsigned int id;
    skybox(string right,string left,string top,string bottom,string front,string back)
    {
        faces.push_back(right);
        faces.push_back(left);
        faces.push_back(top);
        faces.push_back(bottom);
        faces.push_back(front);
        faces.push_back(back);
        stbi_set_flip_vertically_on_load(false);
        unsigned int textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

        int width, height, nrChannels;

        for (unsigned int i = 0; i < faces.size(); i++)
        {
            unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
            if (data)
            {
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                    0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
                );
                stbi_image_free(data);
            }
            else
            {
                std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
                stbi_image_free(data);
            }
        }
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        id = textureID;

    }
  

};
class functiondrawer
{
private:
    float showvertices[30] = {
        0,0,0,0,0,
        0,0.5,0,0,1,
        0.5,0,0,1,0,
        0,0.5,0,0,1,
        0.5,0,0,1,0,
        0.5,0.5,0,1,1
    };
    unsigned int showVAO;
    unsigned int rbo;
    float kuan;
    float gao;
    float vertices[18];
    const char* vertexShaderSource;
    const char* fragmentShaderSource;
    glm::vec2 mypoint;
    unsigned int shaderProgram;
    unsigned int showshaderProgram;
    unsigned int VAO;
    
    float* xx;
    float minx, maxx;
    float miny, maxy;
    float* yy;
    unsigned int yysize;
    
    void useShader()
    {
        glUseProgram(shaderProgram);
    }
public:
    unsigned int texColorBuffer;
    unsigned int framebuffer;
    functiondrawer(float width=1600,float height=900)
    {
        
        kuan = width; gao = height;
        glGenFramebuffers(1, &framebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

        glGenTextures(1, &texColorBuffer);
        glBindTexture(GL_TEXTURE_2D, texColorBuffer);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);
        glGenRenderbuffers(1, &rbo);
        glBindRenderbuffer(GL_RENDERBUFFER, rbo);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);

        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        vertexShaderSource =
            "#version 330 core                                        \n"
            "layout(location = 0) in vec3 aPos;                       \n"
            "out vec2 mypos;                                          \n"
            "void main()                                              \n"
            "{                                                        \n"
            "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);     \n"
            "    mypos = vec2(aPos.x, aPos.y);                        \n"
            "}                                                       \n";
        fragmentShaderSource =
            "#version 330 core                                                                         \n"
            "out vec4 FragColor;                                                                       \n"
            "                                                                                          \n"
            "in vec2 mypos;                                                                            \n"
            "uniform vec2 mypoint;                                                                     \n"
            "uniform vec3 pcolor;                                                                      \n"
            "void main()                                                                               \n"
            "{                                                                                         \n"
            "    if (((mypos.x - mypoint.x)*(mypos.x - mypoint.x)+(mypos.y - mypoint.y)*(mypos.y - mypoint.y)) < 0.0001)       \n"
            "    {                                                                                     \n"
            "        FragColor = vec4(pcolor, 1.0f);                                                  \n"
            "    }                                                                                     \n"
            "    else                                                                                  \n"
            "    {                                                                                     \n"
            "        discard;                                                                          \n"
            "    }                                                                                     \n"
            "}                                                                                         \n";
        // build and compile our shader program
   // ------------------------------------
   // vertex shader
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);
        // check for shader compile errors
        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        // fragment shader
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);
        // check for shader compile errors
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        // link shaders
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        // check for linking errors
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        vertices[0] = -1;
        vertices[1] = -1;
        vertices[2] = 0;
        vertices[3] = -1;
        vertices[4] = 1;
        vertices[5] = 0;
        vertices[6] = 1;
        vertices[7] = -1;
        vertices[8] = 0;
        vertices[9] = -1;
        vertices[10] = 1;
        vertices[11] = 0;
        vertices[12] = 1;
        vertices[13] = -1;
        vertices[14] = 0;
        vertices[15] = 1;
        vertices[16] = 1;
        vertices[17] = 0;

        unsigned int VBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);


        const char* showverticesouce=
            "     #version 330 core                                   \n"
            "     layout(location = 0) in vec2 aPos;                  \n"
            " layout(location = 1) in vec2 aTexCoords;                \n"
            "                                                         \n"
            " out vec2 TexCoords;                                     \n"
            " uniform mat4 model;                                     \n"
            "                                                         \n"
            " void main()                                             \n"
            " {                                                       \n"
            "     gl_Position = model*vec4(aPos.x, aPos.y, 0.0, 1.0); \n"
            "     TexCoords = aTexCoords;                             \n"
            " }                                                       \n";

        const char* showfragsouce =
            "     #version 330 core                                      \n"
            "     out vec4 FragColor;                                    \n"
            "                                                            \n"
            " in vec2 TexCoords;                                         \n"
            "                                                            \n"
            " uniform sampler2D screenTexture;                           \n"
            "                                                            \n"
            " void main()                                                \n"
            " {                                                          \n"
            "     FragColor = texture(screenTexture, TexCoords);         \n"
            " }                                                          \n";


        unsigned int showvertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(showvertexShader, 1, &showverticesouce, NULL);
        glCompileShader(showvertexShader);
        // check for shader compile errors
        
        
        glGetShaderiv(showvertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(showvertexShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        // fragment shader
        unsigned int showfragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(showfragmentShader, 1, &showfragsouce, NULL);
        glCompileShader(showfragmentShader);
        // check for shader compile errors
        glGetShaderiv(showfragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(showfragmentShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        // link shaders
        showshaderProgram = glCreateProgram();
        glAttachShader(showshaderProgram, showvertexShader);
        glAttachShader(showshaderProgram, showfragmentShader);
        glLinkProgram(showshaderProgram);
        // check for linking errors
        glGetProgramiv(showshaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(showshaderProgram, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
        glDeleteShader(showvertexShader);
        glDeleteShader(showfragmentShader);

        unsigned int showVBO;
        glGenVertexArrays(1, &showVAO);
        glGenBuffers(1, &showVBO);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(showVAO);

        glBindBuffer(GL_ARRAY_BUFFER, showVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(showvertices), showvertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

    } 
    void init(float* x,float* y,unsigned int size,float xmin,float xmax,float ymin,float ymax,glm::vec3 backcolor = glm::vec3(0,0,0))
    {
        xx = x;
        yy = y;
        minx = xmin;
        maxx = xmax;
        miny = ymin;
        maxy = ymax;
        yysize = size;
        mypoint = glm::vec2(-1, -1);
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        glClearColor(backcolor.x, backcolor.y, backcolor.z, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    void showboard(glm::vec2 position = glm::vec2(0.3, 0.2), float scale=1.2f)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

        glUseProgram(shaderProgram);
        glUniform2f(glGetUniformLocation(shaderProgram, "mypoint"), 2 * (*xx - minx) / (maxx - minx) - 1, 2 * (0 - miny) / (maxy - miny) - 1);
        glUniform3f(glGetUniformLocation(shaderProgram, "pcolor"),0.8,0.4,0.2);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glUniform3f(glGetUniformLocation(shaderProgram, "pcolor"),1,1,1);
        for (int i = 0; i < yysize; i++)
        {
            glUseProgram(shaderProgram);
            glUniform2f(glGetUniformLocation(shaderProgram, "mypoint"), 2 * (*xx - minx) / (maxx - minx) - 1, 2 * (*(yy+i) - miny) / (maxy - miny) - 1);
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(position, 0));
        model = glm::scale(model, glm::vec3(scale, scale, scale));
        glDisable(GL_DEPTH_TEST);
        glUseProgram(showshaderProgram);
        glBindTexture(GL_TEXTURE_2D,texColorBuffer);
        glUniformMatrix4fv(glGetUniformLocation(showshaderProgram, "model"), 1, GL_FALSE, &model[0][0]);
        glBindVertexArray(showVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glEnable(GL_DEPTH_TEST);
    }
    void clear(glm::vec3 backcolor = glm::vec3(0,0,0))
    {
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        glClearColor(backcolor.x, backcolor.y, backcolor.z, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    void renderframe(float x,float y)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        glUseProgram(shaderProgram);
        glUniform2f(glGetUniformLocation(shaderProgram, "mypoint"), x,y);
        glUniform3f(glGetUniformLocation(shaderProgram, "pcolor"), 1,0,0);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    void changedata_y(float* target,unsigned int size=1)
    {
        yy = target;
        yysize = size;
    }
    void changedata_x(float* target)
    {
        xx = target;
    }
};
