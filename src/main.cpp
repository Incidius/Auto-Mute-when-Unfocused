/**
 * Include the Geode headers.
 */
#include <Geode/Geode.hpp>

#include <Geode/modify/CCEGLView.hpp>

// Win32 headers for focus detection
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

using namespace geode::prelude;

class $modify(CCEGLView) {
	void pollEvents() {
		CCEGLView::pollEvents();

		static bool wasFocused = true;
		// Storage for volumes when we alt-tab out
		static float savedMusicVol = 1.0f;
		static float savedSfxVol = 1.1f;

		HWND gdWindow = WindowFromDC(wglGetCurrentDC());
		bool isFocused = (GetActiveWindow() == gdWindow);

		// Get the engine instance using sharedEngine() from your header
		auto engine = FMODAudioEngine::sharedEngine();

		if (!isFocused && wasFocused) {
			// --- LOSS OF FOCUS ---
			// 1. Save current volume levels from the member variables
			savedMusicVol = engine->m_musicVolume;
			savedSfxVol = engine->m_sfxVolume;

			// 2. Mute using the setter functions found in your header
			engine->setBackgroundMusicVolume(0.0f);
			engine->setEffectsVolume(0.0f);

			
		}
		else if (isFocused && !wasFocused) {
			// --- GAIN OF FOCUS ---
			// Restore the volumes we saved earlier
			if (savedSfxVol <= 1.0f) {
				engine->setBackgroundMusicVolume(savedMusicVol);
				engine->setEffectsVolume(savedSfxVol);
			}

			
		}

		wasFocused = isFocused;
	}
};