#pragma once

#include <string>

#define PLURAL 0
#define SINGULAR 1

class Text {
public:
    Text() = default;
    Text(std::string NAenglish_, std::string NAfrench_, std::string NAspanish_)
      : NAenglish(NAenglish_),
        NAfrench(NAfrench_),
        NAspanish(NAspanish_),
        EURenglish(NAenglish_),
        EURfrench(std::move(NAfrench_)),
        EURspanish(std::move(NAspanish_)),
        EURitalian(NAenglish_),
        EURgerman(std::move(NAenglish_)) {}

    Text(std::string NAenglish_, std::string NAfrench_, std::string NAspanish_,
         std::string EURenglish_, std::string EURfrench_, std::string EURspanish_,
         std::string EURitalian_, std::string EURgerman_)
      : NAenglish(std::move(NAenglish_)),
        NAfrench(std::move(NAfrench_)),
        NAspanish(std::move(NAspanish_)),
        EURenglish(std::move(EURenglish_)),
        EURfrench(std::move(EURfrench_)),
        EURspanish(std::move(EURspanish_)),
        EURitalian(std::move(EURitalian_)),
        EURgerman(std::move(EURgerman_)) {}

    const std::string& GetNAEnglish() const {
        return NAenglish;
    }

    const std::string& GetNAFrench() const {
        if (NAfrench.length() > 0) {
            return NAfrench;
        }
        return NAenglish;
    }

    const std::string& GetNASpanish() const {
        if (NAspanish.length() > 0) {
            return NAspanish;
        }
        return NAenglish;
    }

    const std::string& GetEUREnglish() const {
        if (EURenglish.length() > 0) {
            return EURenglish;
        }
        return NAenglish;
    }

    const std::string& GetEURFrench() const {
        if (EURfrench.length() > 0) {
            return EURfrench;
        }
        return NAenglish;
    }

    const std::string& GetEURSpanish() const {
        if (EURspanish.length() > 0) {
            return EURspanish;
        }
        return NAenglish;
    }

    const std::string& GetEURItalian() const {
        if (EURitalian.length() > 0) {
            return EURitalian;
        }
        return NAenglish;
    }

    const std::string& GetEURGerman() const {
        if (EURgerman.length() > 0) {
            return EURgerman;
        }
        return NAenglish;
    }

    Text operator+ (const Text& right) const {
        return Text{NAenglish + right.GetNAEnglish(), NAfrench + right.GetNAFrench(), NAspanish + right.GetNASpanish(),
                    EURenglish + right.GetEUREnglish(), EURfrench + right.GetEURFrench(), EURspanish + right.GetEURSpanish(),
                    EURitalian + right.GetEURItalian(), EURgerman + right.GetEURGerman()};
    }

    Text operator+ (const std::string& right) const {
        return Text{NAenglish + right, NAfrench + right, NAspanish + right,
                    EURenglish + right, EURfrench + right, EURspanish + right,
                    EURitalian + right, EURgerman + right};
    }

    bool operator==(const Text& right) const {
        return NAenglish == right.NAenglish;
    }

    bool operator!=(const Text& right) const {
        return !operator==(right);
    }

    void Replace(std::string oldStr, std::string newStr) {

        for (std::string* str : {&NAenglish, &NAfrench, &NAspanish, &EURenglish, &EURfrench, &EURspanish, &EURitalian, &EURgerman}) {
            size_t position = str->find(oldStr);
            while (position != std::string::npos) {
              str->replace(position, oldStr.length(), newStr);
              position = str->find(oldStr);
            }
        }
    }

    //find the appropriate bars that separate singular from plural
    void SetForm(int form) {
        for (std::string* str : {&NAenglish, &NAfrench, &NAspanish, &EURenglish, &EURfrench, &EURspanish, &EURitalian, &EURgerman}) {

            size_t firstBar = str->find('|');
            if (firstBar != std::string::npos) {

                size_t secondBar = str->find('|', firstBar + 1);
                if (secondBar != std::string::npos) {

                    size_t thirdBar = str->find('|', secondBar + 1);
                    if (thirdBar != std::string::npos) {

                        if (form == SINGULAR) {
                            str->erase(secondBar, thirdBar - secondBar);
                        } else {
                            str->erase(firstBar, secondBar - firstBar);
                        }
                    }
                }
            }
        }
        //remove the remaining bar
        this->Replace("|", "");
    }

    std::string NAenglish = "";
    std::string NAfrench = "";
    std::string NAspanish = "";
    std::string EURenglish = "";
    std::string EURfrench = "";
    std::string EURspanish = "";
    std::string EURitalian = "";
    std::string EURgerman = "";
};
