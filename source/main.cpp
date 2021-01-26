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

		//launch oot3d directly by holding L and R (cartridge only)
		u32 kHeld = hidKeysHeld();
		if (kHeld & KEY_L && kHeld & KEY_R) {
			aptSetChainloader(0x0004000000033500, 2);
			break;
		}

		// Flush and swap framebuffers
		gfxFlushBuffers();
		gfxSwapBuffers();

		//Wait for VBlank
		gspWaitForVBlank();
	}

	gfxExit();
	return 0;
}
