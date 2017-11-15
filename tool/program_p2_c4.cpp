#include "program_p2_c4.h"

PROGRAM_P2_C4::PROGRAM_P2_C4()
{
    _position   =   -1;
    _color      =   -1;
    _MVP        =   -1;
    _pointSize  =   -1;
    _texture    =   -1;
}

bool PROGRAM_P2_C4::initialize()
{
    const char* vs  =
    {
        "precision  lowp    float; "
        "uniform    mat4    _MVP;"
        "uniform    float   _pointSize;"
        "attribute  vec2    _position;"
        "attribute  vec4    _color;"
        "varying    vec4    _outColor;"
        "void main()"
        "{"
        "   vec4    pos =   vec4(_position,0,1);"
        "   _outColor   =   _color;"
        "   gl_Position =   _MVP * pos;"
        "   gl_PointSize=   _pointSize;"
        "}"
    };
    const char* ps  =
    {
        "precision  lowp        float; "
        "uniform    sampler2D   _texture;"
        "varying    vec4        _outColor;"
        "void main()"
        "{"
        "   vec4 tColor     =   texture2D(_texture,gl_PointCoord);"
        "   gl_FragColor    =   tColor * _outColor;"
        "}"
    };
    //!使用点精灵，那么uv坐标是shader中自带的
    bool    res =   createProgram(vs,ps);
    if(res)
    {
        _position   =   glGetAttribLocation(_programId,"_position");
        _color      =   glGetAttribLocation(_programId,"_color");
        _MVP        =   glGetUniformLocation(_programId,"_MVP");
        _pointSize  =   glGetUniformLocation(_programId,"_pointSize");
        _texture    =   glGetUniformLocation(_programId,"_texture");
    }
    return  res;
}

void PROGRAM_P2_C4::begin()
{
    glUseProgram(_programId);
    glEnableVertexAttribArray(_position);
    glEnableVertexAttribArray(_color);
}

void PROGRAM_P2_C4::end()
{
    glDisableVertexAttribArray(_position);
    glDisableVertexAttribArray(_color);
    glUseProgram(0);
}
