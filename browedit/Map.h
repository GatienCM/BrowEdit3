#pragma once

#include <string>
#include <vector>
#include <browedit/gl/Shader.h>
class Node;
class Action;
class Rsw;
class BrowEdit;
namespace gl { class FBO; }

class Map
{
public:
	std::string name;
	Node* rootNode = nullptr;
	std::vector<Action*> undoStack;
	std::vector<Action*> redoStack;
	std::vector<Node*> selectedNodes;


	Map(const std::string& name);
	void doAction(Action* action, BrowEdit* browEdit);
	void undo(BrowEdit* browEdit);
	void redo(BrowEdit* browEdit);

	glm::vec3 getSelectionCenter();

	void selectSameModels(BrowEdit* browEdit);
	void selectAll(BrowEdit* browEdit);
	void selectInvert(BrowEdit* browEdit);
	void selectNear(float nearDistance, BrowEdit* browEdit);

	void copySelection();
	void pasteSelection(BrowEdit* browEdit);
	void deleteSelection(BrowEdit* browEdit);
	void flipSelection(int axis, BrowEdit* browEdit);
};