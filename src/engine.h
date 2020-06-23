#ifndef ENGINE_HPP
#define ENGINE_HPP

#if __has_include("SDL2/SDL.h")
#   include "SDL2/SDL.h"
#else
#   include "SDL2.h"
#endif

#include <cstdint>
#include <cmath>

constexpr int ScreenResolution = 128;
constexpr uint8_t ColorPalette[16][3] = {
	{ 31, 14, 28 }, // BLACK
	{ 62, 33, 55 }, // DARK
	{ 88, 69, 99 }, // GRAY
	{ 140, 143, 174 }, // LIGHT
	{ 154, 99, 72 }, // MAROON
	{ 215, 155, 125 }, // SKIN
	{ 245, 237, 186 }, // WHITE
	{ 192, 199, 65 }, // LGREEN
	{ 100, 125, 52 }, // GREEN
	{ 228, 148, 58 }, // ORANGE
	{ 157, 48, 59 }, // RED
	{ 210, 100, 113 }, // PINK
	{ 112, 55, 127 }, // PURPLE
	{ 126, 196, 193 }, // SKY
	{ 52, 133, 157 }, // WATER
	{ 23, 67, 75 }, // BLUE
};

class Gorbitsa;
class Engine {
public:
	void start(Gorbitsa* gb);

	inline void put(uint8_t x, uint8_t y, uint8_t color) {
		x = x % ScreenResolution;
		y = y % ScreenResolution;
		const uint8_t* col = ColorPalette[color & 0xF];
		const uint32_t i = (x + y * ScreenResolution) * 3;
		m_pixels[i + 0] = col[0];
		m_pixels[i + 1] = col[1];
		m_pixels[i + 2] = col[2];
	}

	inline void clear(uint8_t color) {
		const uint8_t* col = ColorPalette[color & 0xF];
		for (size_t y = 0; y < ScreenResolution; y++) {
			for (size_t x = 0; x < ScreenResolution; x++) {
				const uint32_t i = (x + y * ScreenResolution) * 3;
				m_pixels[i + 0] = col[0];
				m_pixels[i + 1] = col[1];
				m_pixels[i + 2] = col[2];
			}
		}
		
	}

private:
	SDL_Window *m_window;
	SDL_Renderer *m_renderer;

	SDL_Texture *m_buffer;
	uint8_t *m_pixels;

	bool m_running{ false };

	inline void present() {
		SDL_UnlockTexture(m_buffer);

		SDL_Rect sr = { 0, 0, ScreenResolution * 4, ScreenResolution * 4 };
		SDL_RenderCopy(m_renderer, m_buffer, nullptr, &sr);
		SDL_RenderPresent(m_renderer);
		
		int p;
		SDL_LockTexture(m_buffer, nullptr, (void**) &m_pixels, &p);
	}

	inline void exit() {
		SDL_DestroyTexture(m_buffer);
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
	}

};

#endif // ENGINE_HPP
