// ImGui helpers

bool ImGui_tryLoadFont(const std::string & filename, float size = 14.0f, ImFontConfig * config = NULL, const ImWchar * ranges = NULL) {
#ifndef __EMSCRIPTEN__
    printf("Trying to load font from '%s' ..\n", filename.c_str());
#endif
    std::ifstream f(filename);
    if (f.good() == false) {
#ifndef __EMSCRIPTEN__
        printf(" - failed\n");
#endif
        return false;
    }

    if (ImGui::GetIO().Fonts->AddFontFromFileTTF(filename.c_str(), size, config, ranges) == NULL) {
        return false;
    }

#ifndef __EMSCRIPTEN__
    printf(" - success\n");
#endif

    return true;
}

bool ImGui_BeginFrame(SDL_Window * window) {
    ImGui_NewFrame(window);

    return true;
}

bool ImGui_EndFrame(SDL_Window * window) {
    // Rendering
    int display_w, display_h;
    SDL_GetWindowSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui::Render();
    ImGui_RenderDrawData(ImGui::GetDrawData());

    SDL_GL_SwapWindow(window);

    return true;
}

bool ImGui_SetStyle() {
    ImGuiStyle & style = ImGui::GetStyle();

    style.AntiAliasedFill = true;
    style.AntiAliasedLines = true;
    style.WindowRounding = 0.0f;

    style.WindowPadding = ImVec2(8, 8);
    style.WindowRounding = 0.0f;
    style.FramePadding = ImVec2(4, 3);
    style.FrameRounding = 0.0f;
    style.ItemSpacing = ImVec2(8, 4);
    style.ItemInnerSpacing = ImVec2(4, 4);
    style.IndentSpacing = 21.0f;
    style.ScrollbarSize = 16.0f;
    style.ScrollbarRounding = 9.0f;
    style.GrabMinSize = 10.0f;
    style.GrabRounding = 3.0f;

    //style.Colors[ImGuiCol_Text]                  = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);

    style.ScaleAllSizes(1.0f);

    return true;
}

