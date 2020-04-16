#include <stdio.h>
#include <GLFW/glfw3.h>

extern "C" {
#include <ft2build.h>
#include FT_FREETYPE_H
}

bool get_character_bitmap(char ch, float font_size, FT_Bitmap* bitmap) {
    FT_Error error;
    
    FT_Library library;
    error = FT_Init_FreeType(&library);
    if (error) {
        printf("Couldn't init FreeType2\n");
        return false;
    }

    FT_Face face;
    error = FT_New_Face(library, "/Users/bmj/Desktop/gl-freetype/assets/SFBold.ttf", 0, &face);
    if (error == FT_Err_Unknown_File_Format) {
        printf("Couldn't open font file, unknown file format.\n");
        return false;
    } else if (error) {
        printf("Couldn't open font file.\n");
        return false;
    }

    error = FT_Set_Char_Size(face, 0, (int)(font_size * 64), 300, 300);
    if (error) {
        printf("Couldn't set font size.\n");
        return false;
    }

    FT_UInt glyph_index = FT_Get_Char_Index(face, (FT_UInt32)ch);

    error = FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
    if (error) {
        printf("Couldn't load glyph\n");
        return false;
    }

    error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
    if (error) {
        printf("Couldn't render glyph\n");
        return false;
    }

    *bitmap = face->glyph->bitmap;
    return true;
}

int main(int argc, const char** argv) {
    GLFWwindow* window;

    if (!glfwInit()) {
        printf("Couldn't init GLFW\n");
        return 1;
    }

    window = glfwCreateWindow(640, 480, "OpenGL FreeType2 test", NULL, NULL);
    if (!window) {
        printf("Couldn't open window\n");
        return 1;
    }

    FT_Bitmap bitmap;
    if (!get_character_bitmap('A', 100, &bitmap)) {
        printf("Rendering character failed\n");
        return 1;
    }

    glfwMakeContextCurrent(window);

    GLuint tex_handle;
    const int tex_width = bitmap.width;
    const int tex_height = bitmap.rows;
    glGenTextures(1, &tex_handle);
    glBindTexture(GL_TEXTURE_2D, tex_handle);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex_width, tex_height, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, bitmap.buffer);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Set up orphographic projection
        int win_width, win_height;
        glfwGetFramebufferSize(window, &win_width, &win_height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, win_width, 0, win_height, -1, 1);
        glMatrixMode(GL_MODELVIEW);

        // Render whatever you want
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, tex_handle);
        glBegin(GL_QUADS);
            glTexCoord2d(0,1); glVertex2i((win_width - tex_width) / 2, (win_height - tex_height) / 2);
            glTexCoord2d(1,1); glVertex2i((win_width + tex_width) / 2, (win_height - tex_height) / 2);
            glTexCoord2d(1,0); glVertex2i((win_width + tex_width) / 2, (win_height + tex_height) / 2);
            glTexCoord2d(0,0); glVertex2i((win_width - tex_width) / 2, (win_height + tex_height) / 2);
        glEnd();
        glDisable(GL_TEXTURE_2D);

        glfwSwapBuffers(window);
        glfwWaitEvents();
    }

    return 0;
}

