#include <Rayer.h>

#include <EditorLayer.h>

class RayerEditor : public Rayer::Application {

public:

	RayerEditor() {

		PushLayer(new Rayer::EditorLayer());

	}

};


Rayer::Application* Rayer::CreateApplication() {

	return new RayerEditor();

}

int main() {

	auto app = Rayer::CreateApplication();

	app->ApplicationLoop();


	delete app;

}