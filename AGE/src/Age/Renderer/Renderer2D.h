//
// Created by alex on 18.10.22.
//

#ifndef AGE_RENDERER2D_H
#define AGE_RENDERER2D_H

#include <glm/glm.hpp>

#include "OrthographicCamera.h"
#include "Texture.h"

namespace AGE {

  class Renderer2D {
  public:
    static void Init();
    static void ShutDown();

    static void BeginScene(const OrthographicCamera& camera);
    static void EndScene();

    // Primitives
    static void DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color);
    static void DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color);

    static void
    DrawQuad(const glm::vec2& pos, const glm::vec2& size, const Ref<Texture2D>& texture);
    static void
    DrawQuad(const glm::vec3& pos, const glm::vec2& size, const Ref<Texture2D>& texture);

    static void DrawQuad(
        const glm::vec2& pos, const glm::vec2& size, const Ref<Texture2D>& texture,
        const glm::vec4& color
    );

    static void DrawQuad(
        const glm::vec3& pos, const glm::vec2& size, const Ref<Texture2D>& texture,
        const glm::vec4& color
    );
  };

} // AGE

#endif //AGE_RENDERER2D_H
