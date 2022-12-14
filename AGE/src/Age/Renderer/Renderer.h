//
// Created by alex on 04.10.22.
//

#ifndef AGE_RENDERER_H
#define AGE_RENDERER_H

#include "RenderAPI.h"

#include <glm/vec4.hpp>

#include "OrthographicCamera.h"
#include "VertexArray.h"
#include "Shader.h"

namespace AGE {
  class Renderer {
  public:
    static void Init();
    static void BeginScene(OrthographicCamera& camera);
    static void EndScene();
    static void Submit(
        const Ref <VertexArray>& va, const Ref <Shader>& shader,
        const glm::mat4& transform = glm::mat4(1.0f)
    );

    static RenderAPI::API GetAPI() { return RenderAPI::GetAPI(); }

  private:
    struct SceneData {
      glm::mat4 ViewProjectionMatrix;
    };

    static SceneData* s_SceneData;
  };

} // AGE

#endif //AGE_RENDERER_H
