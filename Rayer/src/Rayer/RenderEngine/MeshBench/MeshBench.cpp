#include <Rayer/Filesystem/FileSystem.h>
#include <Rayer/RenderEngine/MeshBench/MeshBench.h>

namespace Rayer {

    MeshBench::MeshBench() {
        s_RendererApi = RenderEngine::GetActiveApi();

        // Creating shader for MeshBench
        m_Shader = Shader::Create("shader/meshbench/glsl/vertex.glsl", "shader/meshbench/glsl/fragment.glsl");
    }

    void MeshBench::Init() {

        s_RendererApi->Init();

    }

    void MeshBench::SetClearColor(const glm::vec4& color) {
        s_RendererApi->SetClearColor(color);
    }

    void MeshBench::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {

		s_RendererApi->SetViewport(x, y, width, height);

    }

    void MeshBench::Clear() {
        s_RendererApi->Clear();
    }

    void MeshBench::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count) {
        m_Shader->Bind();
        s_RendererApi->DrawIndexed(vertexArray, count);
        m_Shader->Unbind();
    }


    void MeshBench::DrawWireframe(const Ref<VertexArray>& vertexArray, uint32_t count) {
        m_Shader->Bind();
        s_RendererApi->DrawWireframe(vertexArray, count);
        m_Shader->Unbind();
    }

    void MeshBench::DrawLine(const Ref<VertexArray>& vertexArray, uint32_t count) {
        m_Shader->Bind();
        s_RendererApi->DrawLine(vertexArray, count);
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

    void MeshBench::SetShaderFloat3(const std::string& name, const glm::vec3& value) {

		m_Shader->Bind();
		m_Shader->SetUniformFloat3(name, value);
		m_Shader->Unbind();
    }

    void MeshBench::SetShaderInt(const std::string& name, int value) {
        m_Shader->Bind();
        m_Shader->SetUniformInt(name, value);
        m_Shader->Unbind();
    }

    void MeshBench::SetShaderBool(const std::string& name, bool value) {
        m_Shader->Bind();
		m_Shader->SetUniformBool(name, value);
        m_Shader->Unbind();
    }

}
