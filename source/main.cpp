#include <3ds.h>
#include "menu.hpp"

int main() {
	gfxInitDefault();
	MenuInit();
	while (aptMainLoop()) {

		hidScanInput();
		u32 kDown = hidKeysDown();
		if (kDown & KEY_SELECT) break; //stop the app

		MenuUpdate(kDown);

		// Flush and swap framebuffers
		gfxFlushBuffers();
		gfxSwapBuffers();

		//Wait for VBlank
		gspWaitForVBlank();
	}

	gfxExit();
	return 0;
}
