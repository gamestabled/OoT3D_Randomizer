#pragma once

#include <variant>
#include <string>
#include <vector>

class Setting {
public:
    enum class Category;
    class Option;

    static Setting Bool(std::string name_, std::string description_, std::vector<Option> options_, Category category_ = Category::NonCosmetic, size_t defaultOption_ = 0, bool defaultHidden_ = false) {
        return Setting{false, std::move(name_), std::move(description_), std::move(options_), category_, defaultOption_, defaultHidden_};
    }

    static Setting Int(std::string name_, std::string description_, std::vector<Option> options_, Category category_  = Category::NonCosmetic, size_t defaultOption_ = 0, bool defaultHidden_ = false) {
        return Setting{size_t{0}, std::move(name_), std::move(description_), std::move(options_), category_, defaultOption_, defaultHidden_};
    }

    static Setting Range(std::string name_, std::string description_, int rangeStart, int rangeEnd, Category category_ = Category::NonCosmetic, size_t defaultOption_ = 0, bool defaultHidden_ = false) {
        return Setting{size_t{0}, std::move(name_), std::move(description_), rangeStart, rangeEnd, category_, defaultOption_, defaultHidden_};
    }

    enum class Category {
        NonCosmetic,
        Cosmetic,
    };

    enum {
        Off,
        On,
    } BooleanSetting;

    class Option {
    public:
        Option(std::string name_, std::string description_) : name(std::move(name_)), description(std::move(description_)) {}
    
        std::string& getName() {
            return name;
        }

        std::string& getDescription() {
            return description;
        }
    private:
        std::string name;
        std::string description;
    };

    void setVariable() {
        if (std::holds_alternative<bool>(var)) {
            var.emplace<bool>(selectedOption != 0);
        } else {
            var.emplace<size_t>(selectedOption);
        }
    }

    void setNextOption() {
        if (std::holds_alternative<bool>(var)) {
            selectedOption = !selectedOption;
        } else {
            selectedOption++;
            if (selectedOption >= options.size()) {
                selectedOption = 0;
            }
        }
        setVariable();
    }

    void setPreviousOption() {
        if (std::holds_alternative<bool>(var)) {
            selectedOption = !selectedOption;
        } else {
            if (selectedOption == 0) {
                selectedOption = options.size() - 1;
            } else {
                selectedOption--;
            }
        }
        setVariable();
    }

    void addOption(const std::string& name, const std::string& description) {
        options.push_back(std::move(Option(name, description)));
    }

    std::string& getName() {
        return name;
    }

    std::string& getDescription() {
        return description;
    }

    std::string& getCurrentOptionDescription() {
        return options[selectedOption].getDescription();
    }

    std::string& getCurrentOptionName() {
        return options[selectedOption].getName();
    }

    void hide() {
        hidden = true;
    }

    void unhide() {
        hidden = false;
    }

    bool isHidden() const {
        return hidden;
    }

    template <typename T>
    T value() const {
        return std::get<T>(var);
    }

    template <typename T>
    bool is(T other) const {
        static_assert(std::is_integral_v<T> || std::is_enum_v<T>,
                      "T must be an integral type or an enum.");

        if constexpr ((std::is_integral_v<T> && !std::is_same_v<bool, T>) || std::is_enum_v<T>) {
            return value<size_t>() == static_cast<size_t>(other);
        } else {
            return value<bool>() == static_cast<bool>(other);
        }
    }

    template <typename T>
    bool isNot(T other) const {
        return !is(other);
    }

    explicit operator bool() const {
        if (std::holds_alternative<bool>(var)) {
            return value<bool>();
        } else {
            return value<size_t>() != 0;
        }
    }

    void setSelectedIndex(size_t index) {
        selectedOption = index;
        if (selectedOption >= options.size()) {
            printf("\x1b[30;0HERROR: Incompatible selection for %s\n", name.c_str());
            selectedOption = 0;
        }
        setVariable();
    }

private:
    Setting(size_t var_, std::string name_, std::string description_, std::vector<Option> options_, Category category_, size_t defaultOption_, bool defaultHidden_)
          : var(var_), name(std::move(name_)), description(std::move(description_)), options(std::move(options_)), category(category_), defaultOption(defaultOption_), defaultHidden(defaultHidden_) {
        selectedOption = defaultOption;
        hidden = defaultHidden;
        setVariable();
    }

    Setting(bool var_, std::string name_, std::string description_, std::vector<Option> options_, Category category_, size_t defaultOption_, bool defaultHidden_)
          : var(var_), name(std::move(name_)), description(std::move(description_)), options(std::move(options_)), category(category_), defaultOption(defaultOption_), defaultHidden(defaultHidden_) {
        selectedOption = defaultOption;
        hidden = defaultHidden;
        setVariable();
    }

    Setting(size_t var_, std::string name_, std::string description_, int rangeStart_, int rangeEnd_, Category category_, size_t defaultOption_, bool defaultHidden_)
          : var(var_), name(std::move(name_)), description(std::move(description_)), category(category_), defaultOption(defaultOption_), defaultHidden(defaultHidden_) {
        options.reserve(rangeEnd_ - rangeStart_);
        for (int i = rangeStart_; i < rangeEnd_; i++) {
            options.push_back(std::move(Option(std::to_string(i), "")));
        }
        selectedOption = defaultOption;
        hidden = defaultHidden;
        setVariable();
    }

    std::variant<bool, size_t> var;
    std::string name;
    std::string description;
    std::vector<Option> options;
    Category category;
    size_t defaultOption = 0;
    bool defaultHidden = false;

    size_t selectedOption;
    bool hidden = false;
};

using SettingsGroup = std::vector<Setting*>;
