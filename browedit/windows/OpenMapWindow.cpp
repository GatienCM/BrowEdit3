#include <windows.h>
#include <browedit/BrowEdit.h>
#include <misc/cpp/imgui_stdlib.h>
#include <browedit/util/FileIO.h>
#include <iostream>

void BrowEdit::openWindow()
{

	ImVec2 center = ImGui::GetMainViewport()->GetCenter();
	ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

	if (ImGui::BeginPopupModal("Open Map", 0, ImGuiWindowFlags_NoDocking))
	{
		if (ImGui::Button("Browse for file"))
		{
			std::cout << "Sorry, not working yet" << std::endl;
		}

		static bool selectFirst = false;
		ImGui::Text("Filter");
		ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
		if(windowData.openJustVisible)
			ImGui::SetKeyboardFocusHere();
		windowData.openJustVisible = false;
		static std::string lastOpenFilter = windowData.openFilter;
		if (ImGui::InputText("##filter", &windowData.openFilter, ImGuiInputTextFlags_EnterReturnsTrue))
		{
			loadMap(windowData.openFiles[windowData.openFileSelected]);
			ImGui::CloseCurrentPopup();
		}
		if (lastOpenFilter != windowData.openFilter)
		{
			selectFirst = true;
			lastOpenFilter = windowData.openFilter;
		}

		if (ImGui::BeginListBox("##Files", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y-40)))
		{
			for (std::size_t i = 0; i < windowData.openFiles.size(); i++)
			{
				if (windowData.openFilter == "" || windowData.openFiles[i].find(windowData.openFilter) != std::string::npos)
				{
					if (selectFirst)
					{
						selectFirst = false;
						windowData.openFileSelected = i;
					}
					if (ImGui::Selectable(windowData.openFiles[i].c_str(), windowData.openFileSelected == i))
						windowData.openFileSelected = i;
					if (ImGui::IsItemClicked(0) && ImGui::IsMouseDoubleClicked(0))
					{
						loadMap(windowData.openFiles[windowData.openFileSelected]);
						ImGui::CloseCurrentPopup();
					}
				}
			}
			ImGui::EndListBox();
		}

		if (ImGui::Button("Open"))
		{
			loadMap(windowData.openFiles[windowData.openFileSelected]);
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
}



void BrowEdit::showOpenWindow()
{
	windowData.openFiles = util::FileIO::listFiles("data");
	windowData.openFiles.erase(std::remove_if(windowData.openFiles.begin(), windowData.openFiles.end(), [](const std::string& map) { return map.substr(map.size() - 4, 4) != ".rsw"; }), windowData.openFiles.end());
	windowData.openJustVisible = true;
	ImGui::OpenPopup("Open Map");
}