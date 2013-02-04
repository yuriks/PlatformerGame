#include "text.hpp"
#include "SpriteBuffer.hpp"

int measureStringWidth(const std::string& text, const FontInfo& font) {
	return text.length() * font.char_w;
}

void drawString(int x, int y, const std::string& text, SpriteBuffer& buffer, const FontInfo& font) {
	Sprite spr;
	spr.setPos(x, y);
	spr.setImg(font.img_x, font.img_y, font.char_w, font.char_h);

	for (char c : text) {
		const int grid_pos = c - font.first_char;
		const int grid_line = grid_pos / font.grid_w;
		const int grid_col = grid_pos % font.grid_w;
		assert(grid_line < font.grid_h);

		spr.img.x = font.img_x + grid_col * font.char_w;
		spr.img.y = font.img_y + grid_line * font.char_h;
		buffer.append(spr);
		spr.x += font.char_w;
	}
}

void drawString(int x, int y, const std::string& text, SpriteBuffer& buffer, const FontInfo& font, TextAlignment alignment) {
	switch (alignment) {
	case TextAlignment::left:
		drawString(x, y, text, buffer, font);
		break;
	case TextAlignment::right:
		drawString(x - measureStringWidth(text, font), y, text, buffer, font);
		break;
	case TextAlignment::center:
		// The weird position dance is so that it rounds down instead of up.
		drawString((2*x - measureStringWidth(text, font)) / 2, y, text, buffer, font);
		break;
	}
}