#include "engine.h"

#include "gorbitsa.hpp"

void Engine::start(Gorbitsa* gb) {
	SDL_Init(SDL_INIT_EVERYTHING);

	m_window = SDL_CreateWindow(
		"Bitsy",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		ScreenResolution * 4, ScreenResolution * 4,
		SDL_WINDOW_SHOWN
	);
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	int p;
	SDL_LockTexture(m_buffer, nullptr, (void**) &m_pixels, &p);

	SDL_Event ev;

	m_running = true;

	while (m_running) {
		while (SDL_PollEvent(&ev)) {
			if (ev.type == SDL_QUIT) {
				m_running = false;
				break;
			}

			switch (ev.type) {
				case SDL_KEYDOWN: {
					if (ev.key.keysym.sym == SDLK_KP_ENTER || ev.key.keysym.sym == SDLK_RETURN) {
						gb->joyaction(II_START);
					} else if (ev.key.keysym.sym == SDLK_SPACE) {
						gb->joyaction(II_JUMP);
					} else if (ev.key.keysym.sym == SDLK_LEFT) {
						gb->joyaction(II_LEFT);
					} else if (ev.key.keysym.sym == SDLK_RIGHT) {
						gb->joyaction(II_RIGHT);
					} else if (ev.key.keysym.sym == SDLK_UP) {
						gb->joyaction(II_UP);
					} else if (ev.key.keysym.sym == SDLK_DOWN) {
						gb->joyaction(II_DOWN);
					}
				} break;
			}
		}

		gb->run(this);

		present();

		SDL_Delay(32);
	}
	exit();
}