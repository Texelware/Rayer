#include <Rayer/Filesystem/FileSystem.h>
#include <Rayer/RenderEngine/MeshBench/MeshBench.h>

namespace Rayer {

    MeshBench::MeshBench() {
        s_RendererApi = RenderEngine::GetActiveApi();

        // Creating shader for MeshBench
        m_Shader = Shader::Create("shader/meshbench/glsl/vertex.glsl", "shader/meshbench/glsl/fragment.glsl");
    }

    void MeshBench::SetClearColor(const glm::vec4& color) {
        s_RendererApi->SetClearColor(color);
    }

    void MeshBench::Clear() {
        s_RendererApi->Clear();
    }

    void MeshBench::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count) {
        m_Shader->Bind();
        s_RendererApi->DrawIndexed(vertexArray, count);
        m_Shader->Unbind();
    }

    // Uniform setting functions implementation
    void MeshBench::SetShaderMat4(const std::string& name, const glm::mat4& matrix) {
        m_Shader->Bind();
        m_Shader->SetUniformMat4(name, matrix);
        m_Shader->Unbind();
    }

    void MeshBench::SetShaderFloat(const std::string& name, float value) {
        m_Shader->Bind();
        m_Shader->SetUniformFloat(name, value);
        m_Shader->Unbind();
    }

    void MeshBench::SetShaderInt(const std::string& name, int value) {
        m_Shader->Bind();
        m_Shader->SetUniformInt(name, value);
        m_Shader->Unbind();
    }

}
