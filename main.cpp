
#include <Geode/Geode.hpp>

#include <Geode/modify/CCEGLView.hpp>


#define WIN32_LEAN_AND_MEAN
#include <windows.h>

using namespace geode::prelude;

class $modify(CCEGLView) {
	void pollEvents() {
		CCEGLView::pollEvents();

		static bool wasFocused = true;
		
		static float savedMusicVol = 1.0f;
		static float savedSfxVol = 1.1f;

		HWND gdWindow = WindowFromDC(wglGetCurrentDC());
		bool isFocused = (GetActiveWindow() == gdWindow);

		
		auto engine = FMODAudioEngine::sharedEngine();

		if (!isFocused && wasFocused) {
			
			savedMusicVol = engine->m_musicVolume;
			savedSfxVol = engine->m_sfxVolume;

			
			engine->setBackgroundMusicVolume(0.0f);
			engine->setEffectsVolume(0.0f);
			//mutes game when it detects it is unfocused

			
		}
		else if (isFocused && !wasFocused) {
			
			if (savedSfxVol <= 1.0f) { //fixes a bug where the game doesn't have a volume set when opening and sets it to max volume
				engine->setBackgroundMusicVolume(savedMusicVol);
				engine->setEffectsVolume(savedSfxVol);
				//when gd is refocused, it turns the volume back to what it was before
			}

			
		}

		wasFocused = isFocused;
	}
};