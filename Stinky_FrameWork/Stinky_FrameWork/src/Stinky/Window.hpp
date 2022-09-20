#pragma once
#include <iostream>

#include "Color.hpp"
#include "FrameReferences.hpp"

namespace Stinky
{
	//	create windows
	bool CreateWindow() noexcept;
	bool CreateWindow(const std::string& title) noexcept;
	bool CreateWindow(int width, int height) noexcept;
	bool CreateWindow(const std::string& title, int width, int height) noexcept;

	//	using with while
	bool IsWindowClosed() noexcept;

	//	swap buffer and check inputs
	void UpdateWindow() noexcept;

	//	close window by force
	void CloseWindow() noexcept;

	//	change window's title
	void SetWindowTitle(const std::string& title) noexcept;
	//	change frame references
	void SetFrameReference(FrameReference frameReference);

	//	push settings
	void PushSetting();
	//	pop settings
	void PopSetting();

	//	clear backgrounds
	void ClearBackground();
	//	clear backgrounds with colors
	void ClearBackground(Color color);
	//	clear backgrounds with hexcolors
	void ClearBackground(HexColor color);
}