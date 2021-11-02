#pragma once

#include "../lib/ui.hpp"
#include "menu_screen.hpp"

class GenerateMenu : public MenuScreen {
public:
    GenerateMenu(int x, int y);

    void update(const touchPosition& touchPos, u32 kDown, u32 kHeld) override;
    void draw() const override;

    UI::Element* getTopScreenElement() {
        return &topScreenElement;
    }

    class TopScreenElement : public UI::Element {
    public:
        friend GenerateMenu;
        TopScreenElement();

        void draw() const override;
    private:
        UI::Textbox mainText;
        UI::Textbox seedText;
    };

private:
    static void onClick3DSButton(UI::Button*);
    static void onClickCitraButton(UI::Button*);
    static void onClickCustomSeedButton(UI::Button*);
    static void onClickRandomSeedButton(UI::Button*);
    void setSeed(const std::string& seed);

    TopScreenElement topScreenElement;

    UI::Button backButton;

    UI::Button dsButton;
    UI::Button citraButton;
    UI::Button customSeedButton;
    UI::Button randomSeedButton;
};
