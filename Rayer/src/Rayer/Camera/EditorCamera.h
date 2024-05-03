#pragma once

#include <rpch.h>

#include <Rayer/Core/Core.h>

#include "Camera.h"

#include <Rayer/Event/Event.h>
#include <Rayer/Event/MouseEvent.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>


namespace Rayer {

	class EditorCamera : public Camera {

	public:
		EditorCamera() {

			UpdateProjection();
			UpdateView();

		};

		EditorCamera(float fov, float aspect_ratio, float near_plane, float far_plane);


		void OnEvent(Event& event);
		void OnUpdate();
		
		/////////////Callback functions for event occurances/////////////////
		bool OnMouseScroll(MouseScrolledEvent& event);

		void SetViewportSize(float width, float height);

		void MouseRotate(const glm::vec2& delta);
		float RotationSpeed() const;
		void MousePan(const glm::vec2& delta);
		std::pair<float , float> PanSpeed() const;
		glm::mat4& GetViewMatrix() { return m_ViewMatrix; }
		glm::mat4& GetProjectionMatrix() { return m_Projection; }

	private:

		void UpdateView();
		void UpdateProjection();

		void MouseZoom(float delta);
		float ZoomSpeed() const;

		glm::vec3 GetUpDirection() const;
		glm::vec3 GetRightDirection() const;
		glm::vec3 GetForwardDirection() const;

		glm::vec3 CalculatePosition() const;
		glm::quat GetOrientation() const;

	private:

		float m_AspectRatio { 1.778f };
		float m_Fov { 45 };
		float m_NearPlane { 0.1f };
		float m_FarPlane { 1000.0f };

		glm::mat4 m_ViewMatrix;
		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_FocalPoint = { 0.0f, 0.0f, 0.0f };

		glm::vec2 m_InitialMousePosition = { 0.0f, 0.0f };

		float m_Distance = 10.0f;
		float m_Pitch = 0.0f, m_Yaw = 0.0f;

		//Viewport size
		float m_ViewportWidth{ 1280 }, m_ViewportHeight { 720 };

	};

}