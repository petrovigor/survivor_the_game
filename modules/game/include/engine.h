#pragma once

#include <memory>
#include "window.h"
#include "timer.h"
#include "physicsManager.h"

class Engine {
private:
  std::unique_ptr<Window>         window;
  std::unique_ptr<WindowCallback> callback;

	TIMER timer;

public:
	Engine();
  ~Engine();

	void initWindow(int width, int height);
	void mainLoop();
  void processController();
  void closeApp();

private:
	void drawFrame();

};
