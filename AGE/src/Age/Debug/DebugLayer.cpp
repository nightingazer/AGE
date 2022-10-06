//
// Created by alex on 08.09.22.
//

#include "agepch.h"

#include "DebugLayer.h"

#include "Age/Core/Window.h"
#include "Age/Core/Application.h"
#include "Age/Core/Input.h"

namespace AGE {
  DebugLayer::DebugLayer() : ImGuiLayer("Debug Layer") {}

  void DebugLayer::OnUpdate(Timestep ts) {
    float fps = 1000.0f / ts.Milliseconds();

    m_FpsPlot.LastUpdate += ts.Seconds();

    if (m_FpsPlot.LastUpdate >= m_FpsPlot.RefreshTime) {
      m_FpsPlot.LastUpdate = 0;
      m_FpsPlot.InsertNewFps(fps);
    }

    ImGui::Begin("Debug");
    Window* window = Application::Instance()->Window();
    ImGui::Text("MainWindow: %s (%i, %i)", window->Title().c_str(), (int)window->Width(), (int)window->Height());
    ImGui::Text("FPS: %f", fps);

    m_FpsPlot.Render();

    auto [mX, mY] = Input::MousePos();
    ImGui::Text("Mouse Position: %i, %i", (int)mX, (int)mY);
    ImGui::End();
  }

  // FPS Plot

  FpsPlot::FpsPlot() {
    m_Data.fill(0.0f);
  }

  void FpsPlot::InsertNewFps(float fps) {
    if (fps > m_MaxValue) {
      m_MaxValue = fps;
    }
    if (fps < m_MinValue) {
      m_MinValue = fps;
    }

    if (m_LastInsertIndex >= m_Data.max_size()) {
      for (std::size_t i = 0; i < m_Data.max_size() - 1; i++) {
        m_Data[i] = m_Data[i + 1];
      }

      m_Data[m_Data.max_size() - 1] = fps;
    } else {
      m_Data[m_LastInsertIndex] = fps;
      m_LastInsertIndex++;
    }
  }

  void FpsPlot::Render() {
    float scaleMax = *std::max_element(m_Data.begin(), m_Data.end());
    ImGui::Text("Max FPS: %f", m_MaxValue);
    ImGui::Text("Min FPS: %f", m_MinValue);


    ImGui::SliderFloat("Refresh time in seconds", &RefreshTime, 0.0f, 5.0f);
    ImGui::PlotLines(
        "FPS",
        m_Data.data(),
        (int)m_Data.max_size(),
        0,
        nullptr,
        -0.1f,
        scaleMax,
        ImVec2(0, 50)
    );
  }
}// namespace AGE