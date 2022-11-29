//
// Created by alex on 20.10.22.
//

#include "Sandbox2DLayer.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Age/Age.h"

#include "glm/gtc/type_ptr.hpp"

Sandbox2DLayer::Sandbox2DLayer() : m_CameraController(1280.0f / 720.0f) {
  AGE_PROFILE_FUNCTION();

  m_CreeperFaceTex  = AGE::Texture2D::Create("assets/textures/creeper-face.png");
  m_IncorrectTex    = AGE::Texture2D::Create("wrong/path/to.png");
  m_CheckerboardTex = AGE::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2DLayer::OnUpdate(AGE::Timestep ts) {
  AGE_PROFILE_FUNCTION();

  m_CameraController.OnUpdate(ts);

  AGE::RenderCommand::Clear();
  AGE::Renderer2D::BeginScene(m_CameraController.GetCamera());

  int sq{100};

  static float time{0};

  time += ts;

  for (int x{-sq}; x <= sq; x++) {
    for (int y{-sq}; y <= sq; y++) {
      float clampx{(float)x / (float)sq};
      float clampy{(float)y / (float)sq};

      float distance = glm::length(glm::vec2(clampx, clampy));
      float green = 0.0f;

      glm::vec3 col{distance};

      AGE::Renderer2D::DrawQuad(
          glm::vec3{(float)x * 0.01f, (float)y * 0.01f, 0.0f}, glm::vec2{0.01f},
          {col, 1.0f}
      );
    }
  }

//  AGE::Renderer2D::DrawQuad(glm::vec3{0.0f, 0.0f, 1.0f}, glm::vec2{0.09f}, m_CreeperFaceTex, glm::vec4{1.0f, 1.0f, 1.0f, 1.0f});

  AGE::Renderer2D::EndScene();
}

void Sandbox2DLayer::OnEvent(AGE::Event& e) {
  AGE_PROFILE_FUNCTION();

  m_CameraController.OnEvent(e);
}

void Sandbox2DUI::OnAttach() {
  AGE_PROFILE_FUNCTION();

  ImGuiLayer::OnAttach();

  AGE::RenderCommand::SetClearColor({m_BgColor, 1.0f});
}

void Sandbox2DUI::OnUpdate(AGE::Timestep ts) {
  AGE_PROFILE_FUNCTION();

  ImGui::Begin("Background");
  if (ImGui::ColorEdit3("Color", glm::value_ptr(m_BgColor))) {
    AGE::RenderCommand::SetClearColor(glm::vec4(m_BgColor, 1.0f));
  }
  ImGui::End();
}
