#ifndef ENGINE_HPP
#define ENGINE_HPP

#if __has_include("SDL2/SDL.h")
#   include "SDL2/SDL.h"
#else
#   include "SDL2.h"
#endif

#include <cstdint>

constexpr int ScreenResolution = 128;

class Gorbitsa;
class Engine {
public:
	void start(Gorbitsa* gb);

	inline void put(uint8_t x, uint8_t y, uint8_t color) {

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