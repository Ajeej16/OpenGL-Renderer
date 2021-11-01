/* date = July 22nd 2021 7:05 pm */

#ifndef SHADER_H
#define SHADER_H

typedef struct shader_t
{
    u32 id;
} shader_t;

#define CURRENT_SHADER __current_shader_in_use
global_variable shader_t CURRENT_SHADER = {};

inline void
start_using_shader(shader_t shader)
{
    glUseProgram(shader.id);
    CURRENT_SHADER = shader;
}

inline void
end_using_shader()
{
    CURRENT_SHADER.id = 0;
}

inline void
delete_shader(shader_t shader)
{
    glDeleteProgram(shader.id);
}

#define set_bool(NAME, VAL)\
set_int(to_string(NAME), VAL)
#define set_int(NAME, VAL)\
_set_int(#NAME, VAL)
inline void
_set_int(const char *name, i32 val)
{
    if(!CURRENT_SHADER.id)
    {
        glUniform1i(glGetUniformLocation(CURRENT_SHADER.id, name), val);
    }
    else
    {
        // TODO(ajeej): Error
    }
}

#define set_float(NAME, VAL)\
_set_float(to_string(NAME), VAL)
inline void
_set_float(const char *name, f32 val)
{
    if(CURRENT_SHADER.id)
    {
        glUniform1f(glGetUniformLocation(CURRENT_SHADER.id, name), val);
    }
    else
    {
        // TODO(ajeej): Error
    }
}

#define set_vec2(NAME, VAL)\
_set_vec2(to_string(NAME), VAL)
inline void
_set_vec2(const char *name, glm::vec2 val)
{
    if(CURRENT_SHADER.id)
    {
        glUniform2f(glGetUniformLocation(CURRENT_SHADER.id, name), val.x, val.y);
    }
    else
    {
        // TODO(ajeej): Error
    }
}

#define set_vec3(NAME, VAL)\
_set_vec3(to_string(NAME), VAL)
inline void
_set_vec3(const char *name, glm::vec3 val)
{
    if(CURRENT_SHADER.id)
    {
        glUniform3f(glGetUniformLocation(CURRENT_SHADER.id, name), val.x, val.y, val.z);
    }
    else
    {
        // TODO(ajeej): Error
    }
}

#define set_vec4(NAME, VAL)\
_set_vec4(to_string(NAME), VAL)
inline void
_set_vec4(const char *name, glm::vec4 val)
{
    if(CURRENT_SHADER.id)
    {
        glUniform4f(glGetUniformLocation(CURRENT_SHADER.id, name), val.x, val.y, val.z, val.w);
    }
    else
    {
        // TODO(ajeej): Error
    }
}

#define set_mat4(NAME, VAL)\
_set_mat4(to_string(NAME), VAL)
inline void
_set_mat4(const char *name, glm::mat4 val)
{
    if(CURRENT_SHADER.id)
    {
        glUniformMatrix4fv(glGetUniformLocation(CURRENT_SHADER.id, name), 1, GL_FALSE, glm::value_ptr(val));
    }
    else
    {
        // TODO(ajeej): Error
    }
}

inline b32
shader_success(u32 shader_id)
{
    b32 success;
    
    glGetShaderiv(shader_id,
                  GL_COMPILE_STATUS,
                  &success);
    
    return success;
}

internal shader_t
load_shader(const char *vertex_path,
            const char *fragment_path)
{
    shader_t result = {0};
    
    const char *vert_source = win32_load_file_as_string(vertex_path);
    const char *frag_source = win32_load_file_as_string(fragment_path);
    
    u32 vert_shader, frag_shader;
    
    vert_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert_shader, 1,
                   &vert_source, NULL);
    glCompileShader(vert_shader);
    
    if(!shader_success(vert_shader))
    {
        GLint bufflen = 0;
        glGetShaderiv(vert_shader, GL_INFO_LOG_LENGTH, &bufflen);
        GLchar *log_string = (GLchar *)malloc(sizeof(*log_string)*(bufflen+1));
        glGetShaderInfoLog(vert_shader,bufflen, 0, log_string);
        
        OutputDebugString((char *)log_string);
        
        free(log_string);
    }
    
    frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag_shader, 1,
                   &frag_source, NULL);
    glCompileShader(frag_shader);
    
    if(!shader_success(frag_shader))
    {
        GLint bufflen = 0;
        glGetShaderiv(frag_shader, GL_INFO_LOG_LENGTH, &bufflen);
        GLchar *log_string = (GLchar *)malloc(sizeof(*log_string)*(bufflen+1));
        glGetShaderInfoLog(frag_shader,bufflen, 0, log_string);
        
        OutputDebugString((char *)log_string);
        
        free(log_string);
    }
    
    result.id = glCreateProgram();
    glAttachShader(result.id, vert_shader);
    glAttachShader(result.id, frag_shader);
    glLinkProgram(result.id);
    
    b32 success;
    glGetProgramiv(result.id, GL_LINK_STATUS, &success);
    if(!success)
    {
        // TODO(ajeej): Error
    }
    
    glDeleteShader(vert_shader);
    glDeleteShader(frag_shader);
    
    free((void *)vert_source);
    free((void *)frag_source);
    
    return result;
}

#endif //SHADER_H
