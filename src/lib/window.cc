#define GL_SILENCE_DEPRECATION 1
#include "window.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <chrono>
#include <iostream>

#include "frame_buffer.h"
#include "key.h"

namespace sren {

namespace {

void GlfwErrorCallback(int error, const char* description) {
  std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

}  // namespace

void Window::Close() { glfwSetWindowShouldClose(glfw_window_, GL_TRUE); }

Window::Window(std::string const& title, int width, int height) {
  glfwSetErrorCallback(GlfwErrorCallback);
  // 初始化 GLFW
  if (!glfwInit()) {
    throw std::runtime_error("failed to initialize GLFW");
  }

  // Decide GL+GLSL versions
#ifdef __APPLE__
  // GL 3.2 + GLSL 150
  const char* glsl_version = "#version 150";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  // Required on Mac
#else
  // GL 3.0 + GLSL 130
  const char* glsl_version = "#version 130";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  // 3.2+ only
  // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // 3.0+ only
  // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  glfw_window_ =
      glfwCreateWindow(width, height, title.data(), nullptr, nullptr);

  if (glfw_window_ == nullptr) {
    throw std::runtime_error("failed to create GLFW window");
  }

  glfwMakeContextCurrent(glfw_window_);
  glfwSwapInterval(1);  // Enable vsync
  glfwSetKeyCallback(glfw_window_, details::HandleKey);

  if (glewInit() != GLEW_OK) {
    throw std::runtime_error("failed to initialize GLEW");
  }

  // Create a OpenGL texture identifier
  glGenTextures(1, &image_texture_);
  glBindTexture(GL_TEXTURE_2D, image_texture_);
  // Setup filtering parameters for display
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // This is required on WebGL for non power-of-two textures
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);  // Same

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  (void)io;
  ImGui::StyleColorsClassic();
  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(glfw_window_, true);
  ImGui_ImplOpenGL3_Init(glsl_version);
}

Window::~Window() { glfwTerminate(); }

std::chrono::time_point<std::chrono::system_clock> Window::now() {
  return std::chrono::system_clock::now();
}

void Window::Run() {
  last_update_time_ = now();
  while (!glfwWindowShouldClose(glfw_window_)) {
    current_time_ = now();
    auto const delta_dura = current_time_ - last_update_time_;
    delta_time_ = std::chrono::duration_cast<FloatSeconds>(delta_dura).count();

    // 检查事件
    glfwPollEvents();

    // 在每个新的渲染迭代开始的时候清屏，否则仍会看见上一迭代的渲染结果。
    // glClear 接受一个 Buffer Bit 来指定要清空的缓冲，
    // 包括：GL_COLOR_BUFFER_BIT，GL_DEPTH_BUFFER_BIT 和 GL_STENCIL_BUFFER_BIT
    // 这个操作还能防止屏幕闪烁，参考
    // https://stackoverflow.com/questions/27678819/crazy-flashing-window-opengl-glfw
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 注意在 retina 屏幕下，由于存在缩放，所以像素和 window 大小并不是一对一的
    // 例如 200% 缩放的情况下，对于一个屏幕上的一个单位点，需要渲染四个像素
    // https://stackoverflow.com/questions/36672935/why-retina-screen-coordinate-value-is-twice-the-value-of-pixel-value
    int bwidth{};
    int bheight{};
    glfwGetFramebufferSize(glfw_window_, &bwidth, &bheight);
    glViewport(0, 0, bwidth, bheight);
    frame_buffer_.Resize(bwidth * 0.9, bheight * 0.9);

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    if (main_loop_) {
      main_loop_(this);
    }

    frame_buffer_.FlipVertically();

    // Upload pixels into texture
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, frame_buffer_.width(),
                 frame_buffer_.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 frame_buffer_.data());

    {
      ImGui::SetNextWindowPos(ImVec2(0, 0));
      ImGui::SetNextWindowSize(ImVec2(bwidth, bheight));
      constexpr auto win_flags =
          ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBringToFrontOnFocus;
      ImGui::Begin("Render Result", nullptr, win_flags);
      ImGui::Image((void*)(intptr_t)image_texture_,
                   ImVec2(frame_buffer_.width(), frame_buffer_.height()));
      ImGui::End();
    }

    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    // 交换缓冲，修改的缓冲和展示的缓冲是两个数据，交换才能正常展示
    glfwSwapBuffers(glfw_window_);
    // 清理按键记录
    details::ClearKeyState();
  }
}

}  // namespace sren
