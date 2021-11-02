#include <3ds.h>

#include "menu.hpp"
// #include "hint_list.hpp"
// #include "item_list.hpp"
// #include "item_location.hpp"
// #include "location_access.hpp"

#include "lib/ui.hpp"
#include "gui.hpp"

#include "menus/main_menu.hpp"
#include "menus/menu_screen.hpp"

#include "world.hpp"

#define TICKS_PER_SEC 268123480.0

void backButtonProc(UI::Element* backButton) {
  MenuStack::popMenuStack();
}

int main() {
  GUI gui;

  // HintTable_Init();
  // ItemTable_Init();
  // LocationTable_Init();
  // MenuInit();

  MainMenu mainMenu(0, 0);
  MenuStack menuStack;
  MenuStack::pushToMenuStack(&mainMenu);

  // u64 initialHoldTime = svcGetSystemTick();
  // u64 intervalTime = initialHoldTime;
  while (aptMainLoop()) {

    World::updateAll();

    hidScanInput();
    u32 kDown = hidKeysDown();
    u32 kHeld = hidKeysHeld();
    if (kDown & KEY_SELECT) break; //stop the app
    touchPosition p;
    hidTouchRead(&p);

    gui.addElementToBottom(&menuStack);
    gui.addElementToTop(menuStack.getTopScreenElement());

    gui.doFrame(p, kDown, kHeld);

  }
  return 0;
}
