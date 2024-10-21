#include "TransformComponent.h"

#include <imgui.h>

#include <glm/gtc/type_ptr.hpp>

namespace Rayer {

	TransformComponent::TransformComponent(glm::mat4& _modelMatrix) : modelMatrix(_modelMatrix) , Component(ComponentType::TransformComponent) {
		
		//Extracting position from entity
        translate = glm::vec3(_modelMatrix[3]);

		//Extracting scale from entity
        scale.x = glm::length(glm::vec3(_modelMatrix[0]));
        scale.y = glm::length(glm::vec3(_modelMatrix[1]));
        scale.z = glm::length(glm::vec3(_modelMatrix[2]));
           
        
	}

    void TransformComponent::OnUpdate() {


        transformationMatrix = glm::mat4(1);

        //// Applying the rotations
        //glm::vec3 rotationRadians = glm::radians(rotation);
        //transformationMatrix = glm::rotate(transformationMatrix, rotationRadians.x, glm::vec3(1.0f, 0.0f, 0.0f)); // X-axis rotation
        //transformationMatrix = glm::rotate(transformationMatrix, rotationRadians.y, glm::vec3(0.0f, 1.0f, 0.0f)); // Y-axis rotation
        //transformationMatrix = glm::rotate(transformationMatrix, rotationRadians.z, glm::vec3(0.0f, 0.0f, 1.0f)); // Z-axis rotation

        // Applying scaling
        transformationMatrix = glm::scale(transformationMatrix, scale);

        // Applying rotation using the quaternion
        transformationMatrix *= glm::mat4_cast(rotationInQuat); // Rotate before translation

        // Applying translation
        transformationMatrix = glm::translate(transformationMatrix, translate);

       

        modelMatrix = transformationMatrix;
    }



	void TransformComponent::OnRender() {

        

    
        const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;
        

        if (ImGui::TreeNodeEx("Transform" , treeNodeFlags)) {


            modelMatrix = transformationMatrix;
          
            //Modify the translation
            if (ImGui::DragFloat3("Position", glm::value_ptr(translate), 0.05f)) {

                OnUpdate();

            }
            
			//Modifying the rotation
            if (ImGui::DragFloat3("Rotation", glm::value_ptr(rotation), 0.05f, -360.0f, 360.0f)) {

                OnUpdate();

            }

            //Modifying scale
            if (ImGui::DragFloat3("Scale", glm::value_ptr(scale), 0.05f)) {

              

                OnUpdate();
            }

          
           
            ImGui::TreePop();

        }


        modelMatrix = transformationMatrix;

        translate = glm::vec3(transformationMatrix[3]);

        scale.x = glm::length(transformationMatrix[0]);
        scale.y = glm::length(transformationMatrix[1]);
        scale.z = glm::length(transformationMatrix[2]);


        ImGui::Separator();

 

	}

}