/*
 * DISTRHO Plugin Framework (DPF)
 * Copyright (C) 2012-2021 Filipe Coelho <falktx@falktx.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any purpose with
 * or without fee is hereby granted, provided that the above copyright notice and this
 * permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD
 * TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN
 * NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER
 * IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

// ImGui is quite large, build it separately
#define IMGUI_SKIP_IMPLEMENTATION

#include "Application.hpp"
#include "../opengl/DearImGui.cpp"
#include "../opengl/DearImGuiColorTextEditor.cpp"

int main(int, char**)
{
    USE_NAMESPACE_DGL;

    Application app;
    ImGuiTextEditorStandaloneWindow win(app);
    win.setGeometryConstraints(640*win.getScaleFactor(), 480*win.getScaleFactor(), false);
    win.setResizable(true);
    win.setTitle("TextEdit");
    win.show();
    app.exec();

    return 0;
}