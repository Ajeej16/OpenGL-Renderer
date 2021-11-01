
#include <windows.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include <glad\glad.h>
#include <glad.c>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define internal static
#define global_variable static
#define persist static

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float f32;
typedef double f64;

typedef i8 b8;
typedef i16 b16;
typedef i32 b32;
typedef i64 b64;

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define IDENTITY glm::mat4(1.0f)
#define DEFAULT_YAW -90.0f
#undef DEFAULT_PITCH
#define DEFAULT_PITCH 0.0f
#define DEFAULT_ROLL 0.0f
#define DEFAULT_SPEED 4.0f
#define DEFAULT_SENSITIVITY 0.1f
#define DEFAULT_FOV 45.0f

global_variable b32 first_mouse = 1;
global_variable f32 lastx = SCREEN_WIDTH/2.0f;
global_variable f32 lasty = SCREEN_HEIGHT/2.0f;

global_variable f32 dt = 0.0f;
global_variable f32 last_frame = 0.0f;

global_variable glm::vec3 light_pos(1.2f, 1.0f, 1.0f);

#define array_count(x) ((sizeof(x))/(sizeof((x)[0])))
#define to_string(x) #x

// TODO(ajeej): Not good
internal char *
win32_load_file_as_string(const char *path);

#include "shader.h"

typedef struct camera_t
{
    glm::vec3 pos;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 world_up;
    
    f32 yaw;
    f32 pitch;
    f32 roll;
    
    f32 movement_speed;
    f32 mouse_sensitivity;
    f32 fov;
} camera_t;

typedef struct vertex_t
{
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec2 tex_coords;
} vertex_t;

typedef enum texture_type_t
{
    texture_type_diffuse,
    texture_type_specular,
} texture_type_t;

inline const char *
tex_type_to_string(texture_type_t tt)
{
    switch(tt)
    {
        case texture_type_diffuse:
        {
            return "diffuse";
        };
        case texture_type_specular:
        {
            return "specular";
        };
        default:
        {
            // TODO(ajeej): Error
            return 0;
        };
    }
}

typedef struct texture_t
{
    u32 id;
    texture_type_t type;
    const char *path;
} texture_t;

typedef struct mesh_t
{
    vertex_t *vertices;
    u32 v_count;
    u32 * indices;
    u32 i_count;
    texture_t *textures;
    u32 t_count;
    
    u32 VAO, VBO, IBO;
} mesh_t;

inline void
delete_mesh(mesh_t *m)
{
    free((void *)m->vertices);
    free((void *)m->indices);
    free((void *)m->textures);
    
    glDeleteVertexArrays(1, &m->VAO);
    glDeleteBuffers(1, &m->VBO);
    glDeleteBuffers(1, &m->IBO);
}

internal mesh_t
create_mesh(vertex_t *v, u32 vc,
            u32 *i, u32 ic,
            texture_t *t, u32 tc);
// TODO(ajeej): should only be accessed after creation
internal void
setup_mesh(mesh_t *m);

internal void
render_mesh(mesh_t m);

typedef struct model_t
{
    mesh_t *meshes;
    u32 iter;
    u32 m_count;
    const char *dir;
} model_t;

inline void
render_model(model_t m)
{
    for(u32 i = 0;
        i < m.m_count;
        i++)
        render_mesh(*(m.meshes+i));
}

inline void
delete_model(model_t *m)
{
    free((void *)m->dir);
    
    for(u32 i = 0;
        i < m->m_count;
        
        i++)
        delete_mesh((m->meshes+i));
}

internal model_t
load_model(const char *path);

internal void
process_node(aiNode *node, const aiScene *scene,
             mesh_t *meshes, const char *dir, u32 *iter);

internal mesh_t
process_mesh(aiMesh *mesh, const char *dir, const aiScene *scene);

internal texture_t *
process_material(aiMaterial *mat, aiTextureType type, 
                 texture_type_t etype, const char *dir, u32 *tex_count);

internal void 
framebuffer_size_callback(GLFWwindow *window,
                          i32 width,i32 height);

internal void
mouse_callback(GLFWwindow *window, f64 posx, f64 posy);

internal void
scroll_callback(GLFWwindow *window, f64 offsetx, f64 offsety);

internal void 
process_input(GLFWwindow *window);

internal u32
load_texture(const char *path, const char *dir);

internal camera_t
create_camera();

internal camera_t
create_camera(glm::vec3 pos);

internal camera_t
create_camera(glm::vec3 pos, glm::vec3 world_up, f32 pitch, f32 yaw, f32 roll);

internal void
update_camera(camera_t *camera);

inline glm::mat4
get_view_matrix(camera_t camera)
{
    return glm::lookAt(camera.pos,
                       camera.pos+camera.front,
                       camera.up);
}

global_variable camera_t camera = create_camera(glm::vec3(0.0f, 0.0f, 3.0f));

internal shader_t
load_shader(const char *vertex_path,
            const char *fragment_path);


inline u32
get_string_size(const char *str)
{
    u32 size = 0;
    
    for(u32 i = 0;
        str[i] != 0;
        i++)
    {
        size++;
    }
    
    return size;
}

inline u32
get_index_of_last_char(const char *str, char c)
{
    u32 index = 0;
    
    u32 size = get_string_size(str);
    
    for(u32 i = size;
        i >= 0;
        i--)
    {
        if(str[i] == c)
        {
            index = i;
            break;
        }
    }
    
    return index;
}

inline u32
get_index_of_char(const char *str, char c)
{
    u32 index = 0;
    
    for(u32 i = 0;
        str[i] != 0;
        i++)
    {
        if(str[i] == c)
        {
            index = i;
            break;
        }
    }
    
    return index;
}

inline const char*
get_substr(const char *str, u32 start, u32 end)
{
    u32 substr_size = ((end-start)+2)*sizeof(*str);
    char *substr = (char *)malloc(substr_size);
    memcpy((void *)substr, (void *)(str+start), substr_size);
    substr[(end-start)+1] = 0;
    return substr;
}


INT WINAPI 
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
        PSTR lpCmdLine, INT nCmdShow)
{
    // NOTE(ajeej): initalize and configure glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    
    // NOTE(ajeej): create glfw window
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT,
                                          "OpenGL Starter", NULL, NULL);
    
    if(window == NULL)
    {
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // NOTE(ajeej): load glad OpenGL function pointers
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        return -1;
    }
    
    stbi_set_flip_vertically_on_load(true);
    
    // NOTE(ajeej): enable depth testing
    glEnable(GL_DEPTH_TEST);
    
    // NOTE(ajeej): build and compile shaders
    shader_t model_shader = load_shader("shaders\\model.vs", "shaders\\model.fs");
    shader_t light_shader = load_shader("shaders\\light.vs", "shaders\\light.fs");
    
    model_t light = load_model("models\\cube\\cube.obj");
    model_t backpack = load_model("models\\backpack\\backpack.obj");
    
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    while(!glfwWindowShouldClose(window))
    {
        
        f32 current_frame = glfwGetTime();
        dt = current_frame - last_frame;
        last_frame = current_frame;
        
        // NOTE(ajeej): input
        process_input(window);
        
        // NOTE(ajeej): render
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        
        start_using_shader(model_shader);
        
        set_float(material.shininess, 32.0f);
        set_vec3(view_pos, camera.pos);
        
        set_vec3(plight.pos, light_pos);
        set_vec3(plight.ambient, glm::vec3(0.05f, 0.05f, 0.05f));
        set_vec3(plight.diffuse, glm::vec3(0.8f, 0.8f, 0.8f));
        set_vec3(plight.specular, glm::vec3(1.0f, 1.0f, 1.0f));
        set_float(plight.constant, 1.0f);
        set_float(plight.linear, 0.09f);
        set_float(plight.quadratic, 0.032);
        
        glm::mat4 projection = glm::perspective(glm::radians(camera.fov), SCREEN_WIDTH/(f32)SCREEN_HEIGHT,
                                                0.1f, 100.f);
        set_mat4(projection, projection);
        
        glm::mat4 view = get_view_matrix(camera);
        set_mat4(view, view);
        
        glm::mat4 model = IDENTITY;
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
        set_mat4(model, model);
        render_model(backpack);
        
        end_using_shader();
        
        start_using_shader(light_shader);
        
        set_mat4(projection, projection);
        
        set_mat4(view, view);
        
        model = IDENTITY;
        model = glm::translate(model, light_pos);
        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
        set_mat4(model, model);
        render_model(light);
        
        end_using_shader();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }
    
    // NOTE(ajeej): deallocate all resources
    delete_shader(model_shader);
    //delete_model(&backpack);
    
    glfwTerminate();
    
    return 0;
}

internal void process_input(GLFWwindow *window)
{
    f32 camera_speed = camera.movement_speed*dt;
    glm::vec3 front = camera.front;
    glm::vec3 up = camera.up;
    glm::vec3 right = camera.right;
    
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) != GLFW_PRESS)
    {
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, 1);
        if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera.pos += camera_speed*front;
        if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera.pos -= camera_speed*front;
        if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera.pos -= right*camera_speed;
        if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera.pos += right*camera_speed;
        if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            camera.pos += camera_speed*up;
        if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            camera.pos -= camera_speed*up;
    }
    else
    {
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, 1);
        if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            light_pos += camera_speed*glm::vec3(0.0f, 0.0f, -1.0f);
        if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            light_pos -= camera_speed*glm::vec3(0.0f, 0.0f, -1.0f);;
        if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            light_pos -= glm::vec3(1.0f, 0.0f, 0.0f)*camera_speed;
        if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            light_pos += glm::vec3(1.0f, 0.0f, 0.0f)*camera_speed;
        if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            light_pos += camera_speed*glm::vec3(0.0f, 1.0f, 0.0f);;
        if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            light_pos -= camera_speed*glm::vec3(0.0f, 1.0f, 0.0f);;
    }
}

internal void framebuffer_size_callback(GLFWwindow *window,
                                        i32 width, i32 height)
{
    glViewport(0, 0, width, height);
}

internal void
mouse_callback(GLFWwindow *window, f64 posx, f64 posy)
{
    if(first_mouse)
    {
        lastx = posx;
        lasty = posy;
        first_mouse = 0;
    }
    
    f32 *yaw = &camera.yaw;
    f32 *pitch = &camera.pitch;
    
    f32 offsetx = posx - lastx;
    f32 offsety = lasty - posy;
    lastx = posx;
    lasty = posy;
    
    f32 sensitivity = 0.1f;
    offsetx *= sensitivity;
    offsety *= sensitivity;
    
    *yaw += offsetx;
    *pitch += offsety;
    
    if(*pitch > 89.0f)
        *pitch = 89.0f;
    if(*pitch < -89.0f)
        *pitch = -89.0f;
    
    glm::vec3 forward;
    forward.x = cos(glm::radians(*yaw))*cos(glm::radians(*pitch));
    forward.y = sin(glm::radians(*pitch));
    forward.z = sin(glm::radians(*yaw))*cos(glm::radians(*pitch));
    camera.front = glm::normalize(forward);
    
    update_camera(&camera);
}

internal void
scroll_callback(GLFWwindow *window, f64 offsetx, f64 offsety)
{
    f32 *fov = &camera.fov;
    *fov -= (f32)offsety;
    if(*fov < 1.0f)
        *fov = 1.0f;
    if(*fov > 45.0f)
        *fov = 45.0f;
}

internal char *
win32_load_file_as_string(const char *path)
{
    char *result = 0;
    
    HANDLE file = {};
    
    DWORD desired_access = GENERIC_READ | GENERIC_WRITE;
    DWORD share_mode = 0;
    SECURITY_ATTRIBUTES security_attribs = {
        (DWORD)sizeof(SECURITY_ATTRIBUTES),
        0,
        0,
    };
    DWORD creation_disposition = OPEN_EXISTING;
    DWORD flags_and_attributes = 0;
    HANDLE template_file = 0;
    
    if((file = CreateFile(path, desired_access, share_mode, 
                          &security_attribs, creation_disposition,
                          flags_and_attributes, template_file)) != INVALID_HANDLE_VALUE)
    {
        DWORD read_bytes = GetFileSize(file, 0);
        if(read_bytes)
        {
            result = (char *)malloc(read_bytes+1);
            DWORD bytes_read = 0;
            OVERLAPPED overlapped = {};
            
            ReadFile(file, result, read_bytes, &bytes_read, &overlapped);
            
            result[read_bytes] = 0;
        }
        CloseHandle(file);
    }
    else
    {
        // TODO(ajeej): Error
    }
    
    return result;
}

internal u32
load_texture(const char *path, const char *dir)
{
    char filename[MAX_PATH] = "";
    strcat(filename, dir);
    strcat(filename, path);
    
    u32 texture;
    glGenTextures(1, &texture);
    
    i32 width, height, channels;
    u8 *data = stbi_load(filename, &width, &height, &channels, 0);
    if(data)
    {
        GLenum format;
        if(channels == 1)
            format = GL_RED;
        else if (channels == 3)
            format = GL_RGB;
        else if (channels == 4)
            format = GL_RGBA;
        else;// TODO(ajeej): Error
        
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        stbi_image_free(data);
    }
    else
    {
        stbi_image_free(data);
        // TODO(ajeej): Error
    }
    
    return texture;
}

internal camera_t
create_camera()
{
    camera_t result = {};
    result.pos = glm::vec3(0.0f, 0.0f, 0.0f);
    result.world_up = glm::vec3(0.0f, 1.0f, 0.0f);
    result.yaw = DEFAULT_YAW;
    result.pitch = DEFAULT_PITCH;
    result.roll = DEFAULT_ROLL;
    result.movement_speed = DEFAULT_SPEED;
    result.mouse_sensitivity = DEFAULT_SENSITIVITY;
    result.fov = DEFAULT_FOV;
    
    update_camera(&result);
    
    return result;
}

internal camera_t
create_camera(glm::vec3 pos)
{
    camera_t result = {};
    result.pos = pos;
    result.world_up = glm::vec3(0.0f, 1.0f, 0.0f);
    result.yaw = DEFAULT_YAW;
    result.pitch = DEFAULT_PITCH;
    result.roll = DEFAULT_ROLL;
    result.movement_speed = DEFAULT_SPEED;
    result.mouse_sensitivity = DEFAULT_SENSITIVITY;
    result.fov = DEFAULT_FOV;
    
    update_camera(&result);
    
    return result;
}

internal camera_t
create_camera(glm::vec3 pos, glm::vec3 world_up, f32 pitch, f32 yaw, f32 roll)
{
    camera_t result = {};
    result.pos = pos;
    result.world_up = world_up;
    result.yaw = yaw;
    result.pitch = pitch;
    result.roll = roll;
    result.movement_speed = DEFAULT_SPEED;
    result.mouse_sensitivity = DEFAULT_SENSITIVITY;
    result.fov = DEFAULT_FOV;
    
    update_camera(&result);
    
    return result;
}

internal void
update_camera(camera_t *camera)
{
    f32 yaw = camera->yaw;
    f32 pitch = camera->pitch;
    
    glm::vec3 front;
    front.x = cos(glm::radians(yaw))*cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw))*cos(glm::radians(pitch));
    
    camera->front = glm::normalize(front);
    camera->right = glm::normalize(glm::cross(camera->front, camera->world_up));
    camera->up = glm::normalize(glm::cross(camera->right, camera->front));
}

internal mesh_t
create_mesh(vertex_t *v, u32 vc,
            u32 *i, u32 ic,
            texture_t *t, u32 tc)
{
    mesh_t result = {};
    
    u32 v_size = vc*sizeof(*result.vertices);
    result.vertices = (vertex_t *)malloc(v_size);
    memcpy(result.vertices, v, v_size);
    result.v_count = vc;
    
    u32 i_size = ic*sizeof(*result.indices);
    result.indices = (u32 *)malloc(i_size);
    memcpy(result.indices, i, i_size);
    result.i_count = ic;
    
    u32 t_size = tc*sizeof(*result.textures);
    result.textures = (texture_t *)malloc(t_size);
    memcpy(result.textures, t, t_size);
    result.t_count = tc;
    
    free(v);
    free(i);
    free(t);
    
    setup_mesh(&result);
    
    return result;
}

internal void
setup_mesh(mesh_t *m)
{
    glGenVertexArrays(1, &m->VAO);
    glGenBuffers(1, &m->VBO);
    glGenBuffers(1, &m->IBO);
    
    glBindVertexArray(m->VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, m->VBO);
    glBufferData(GL_ARRAY_BUFFER, m->v_count*sizeof(*m->vertices),
                 m->vertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m->i_count*sizeof(*m->indices),
                 m->indices, GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                          sizeof(*m->vertices), (void *)0);
    
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
                          sizeof(*m->vertices), (void *)offsetof(vertex_t, normal));
    
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
                          sizeof(*m->vertices), (void *)offsetof(vertex_t, tex_coords));
    
    glBindVertexArray(0);
}

internal void
render_mesh(mesh_t m)
{
    u32 diffuse_count = 1;
    u32 specular_count = 1;
    for(u32 i = 0;
        i < m.t_count;
        i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        
        u32 num;
        const char *type = tex_type_to_string(m.textures[i].type);
        if(strcmp(type, "diffuse") == 0)
            num = diffuse_count++;
        else if(strcmp(type, "specular") == 0)
            num = specular_count++;
        
        char buffer[50];
        sprintf(buffer, "material.%s%u", type, num);
        _set_float(buffer, i);
        glBindTexture(GL_TEXTURE_2D, m.textures[i].id);
    }
    
    glBindVertexArray(m.VAO);
    glDrawElements(GL_TRIANGLES, m.i_count, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    
    glActiveTexture(GL_TEXTURE0);
}

internal void
get_mesh_count(aiNode *node, u32 *count)
{
    *count += node->mNumMeshes;
    
    for(u32 i = 0;
        i < node->mNumChildren;
        i++)
        get_mesh_count(node->mChildren[i], count);
}

internal model_t
load_model(const char *path)
{
    model_t result = {};
    
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate|aiProcess_FlipUVs);
    
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        // TODO(ajeej): Error
    }
    
    result.dir = get_substr(path, 0, get_index_of_last_char(path, '\\'));
    
    u32 mesh_count = 0;
    get_mesh_count(scene->mRootNode, &mesh_count);
    result.meshes = (mesh_t *)malloc(mesh_count * sizeof(*result.meshes));
    result.m_count = mesh_count;
    
    process_node(scene->mRootNode, scene, result.meshes, result.dir, &result.iter);
    
    return result;
}

internal void
process_node(aiNode *node, const aiScene *scene,
             mesh_t *meshes, const char *dir, u32 *iter)
{
    for(u32 i = 0;
        i < node->mNumMeshes;
        i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        *(meshes+(*iter)) = process_mesh(mesh, dir, scene);
        ++(*iter);
    }
    
    for(u32 i = 0;
        i < node->mNumChildren;
        i++)
    {
        process_node(node->mChildren[i], scene, meshes, dir, iter);
    }
}

internal mesh_t
process_mesh(aiMesh *mesh, const char * dir, const aiScene *scene)
{
    mesh_t result = {};
    
    vertex_t *vertices;
    u32 *indices;
    texture_t *textures;
    
    u32 v_count = 0, i_count = 0, t_count = 0;
    
    v_count = mesh->mNumVertices;
    vertices = (vertex_t *)malloc(v_count*sizeof(*vertices));
    
    for(u32 i = 0;
        i < mesh->mNumFaces;
        i++)
    {
        aiFace face = mesh->mFaces[i];
        i_count += face.mNumIndices;
    }
    indices = (u32 *)malloc(i_count*sizeof(*indices));
    
    for(u32 i = 0;
        i < v_count;
        i++)
    {
        vertex_t vertex = {};
        glm::vec3 vector;
        
        if(mesh->mVertices)
        {
            vector.x = mesh->mVertices[i].x;
            vector.y = mesh->mVertices[i].y;
            vector.z = mesh->mVertices[i].z;
            vertex.pos = vector;
        }
        else
        {
            vertex.pos = glm::vec3(0.0f, 0.0f, 0.0f);
        }
        
        if(mesh->mNormals)
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.normal = vector;
        }
        else
        {
            vertex.normal = glm::vec3(0.0f, 0.0f, 0.0f);
        }
        
        if(mesh->mTextureCoords[0])
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.tex_coords = vec;
        }
        else
        {
            vertex.tex_coords = glm::vec2(0.0f, 0.0f);
        }
        
        *(vertices+i) = vertex;
    }
    
    u32 i_iter = 0;
    for(u32 i = 0;
        i < mesh->mNumFaces;
        i++)
    {
        aiFace face = mesh->mFaces[i];
        for(u32 j = 0;
            j < face.mNumIndices;
            j++)
        {
            *(indices+i_iter) = face.mIndices[j];
            i_iter++;
        }
    }
    
    if(mesh->mMaterialIndex >= 0)
    {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        
        u32 diffuse_count = 0;
        texture_t *diffuse_maps = process_material(material, aiTextureType_DIFFUSE, texture_type_diffuse,
                                                   dir, &diffuse_count);
        
        u32 specular_count = 0;
        texture_t *specular_maps = process_material(material, aiTextureType_SPECULAR, texture_type_specular,
                                                    dir, &specular_count);
        
        t_count = diffuse_count+specular_count;
        textures = (texture_t *)malloc(t_count*sizeof(*textures));
        
        memcpy(textures, diffuse_maps, diffuse_count*sizeof(*textures));
        memcpy(textures+diffuse_count, specular_maps, specular_count*sizeof(*textures));
        
        free(diffuse_maps);
        free(specular_maps);
    }
    
    result = create_mesh(vertices, v_count, indices, i_count, textures, t_count);
    
    return result;
}

internal texture_t *
process_material(aiMaterial *mat, aiTextureType type, 
                 texture_type_t etype, const char *dir, u32 *tex_count)
{
    texture_t *result;
    *tex_count = mat->GetTextureCount(type);
    result = (texture_t *)malloc(*tex_count*sizeof(*result));
    
    for(u32 i = 0;
        i < *tex_count;
        i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        texture_t texture;
        texture.id = load_texture(str.C_Str(), dir);
        texture.type = etype;
        texture.path = str.C_Str();
        *(result+i) = texture;
    }
    
    return result;
}