//
// Created by a on 24.08.22.
//

#ifndef AGE_APPLICATION_H
#define AGE_APPLICATION_H

#include "Core.h"

#include "Age/Events/Event.h"
#include "Age/Events/WindowEvent.h"
#include "LayerStack.h"
#include "Window.h"

namespace AGE {
  class DLL_PUBLIC Application {
  public:
    Application();
    virtual ~Application();

    virtual void Run();

    void OnEvent(Event& e);

    void PushLayer(Layer* layer);
    void PushOverlay(Layer* layer);

    Window* Window();

    static Application* Instance();

  private:
    bool OnWindowClose(WindowCloseEvent& e);

    class Window* m_Window;
    bool m_Running{true};
    LayerStack m_LayerStack;

    static Application* s_Instance;
  };

  // To be defined in CLIENT
  Application* CreateApplication();
}// namespace AGE

#endif//AGE_APPLICATION_H
