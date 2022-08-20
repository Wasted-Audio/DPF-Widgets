/*
 * Quanta-inspired widgets for DPF
 * Copyright (C) 2022 Filipe Coelho <falktx@falktx.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any purpose with
 * or without fee is hereby granted, provided that the above copyright notice and this
 * permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD
 * TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN
 * NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER
 * IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#pragma once

#include "EventHandlers.hpp"
#include "Layout.hpp"
#include "NanoVG.hpp"

START_NAMESPACE_DGL

// --------------------------------------------------------------------------------------------------------------------

struct QuantumTheme {
    // border size for widgets, e.g. button and knob outline border
    uint borderSize = 2;
    // padding for widgets, the space between each other when in a group
    uint padding = 4;
    // main font size, used for all text unless otherwise stated
    uint fontSize = 16;
    // height given to text labels and widgets that use text (without padding)
    uint textHeight = 24;
    // line size for widgets, e.g. slider line
    uint widgetLineSize = 4;
    // how much padding to give from window border to widgets
    uint windowPadding = padding * 3;
    // background color for widgets, e.g. slider line and knob padding, typically dark
    Color widgetBackgroundColor = Color::fromHTML("#141414");
    // default active color for widgets, e.g. pressed button and knob body
    Color widgetDefaultActiveColor = Color::fromHTML("#3f535a");
    // default alternative color for widgets, similar to the active just an alternative color
    Color widgetDefaultAlternativeColor = Color::fromHTML("#585338");
    // foreground color for widgets, e.g. slider handle and knob indicator, typically light
    Color widgetForegroundColor = Color::fromHTML("#8c8c8c");
    // window background, typically lighter than widget background
    Color windowBackgroundColor = Color::fromHTML("#3d3d3d");
    // text color, main / brightest tone
    Color textLightColor = Color::fromHTML("#ffffff");
    // text color, mid brightness tone
    Color textMidColor = Color::fromHTML("#b3b3b3");
    // text color, dark tone
    Color textDarkColor = Color::fromHTML("#8c8c8c");
    // text color, very dark tone
    Color textVeryDarkColor = Color::fromHTML("#383838");
};

struct QuantumMetrics
{
    Size<uint> button;
    Size<uint> label;
    Size<uint> switch_;
    Size<uint> knob;
    Size<uint> valueMeterHorizontal;
    Size<uint> valueMeterVertical;
    Size<uint> valueSlider;

    explicit QuantumMetrics(const QuantumTheme& theme) noexcept
        : button(theme.textHeight + theme.borderSize * 2,
                 theme.textHeight + theme.borderSize * 2),
          label(theme.textHeight,
                theme.textHeight),
          switch_(theme.textHeight * 2 + theme.borderSize * 2,
                 theme.textHeight / 2 + theme.borderSize * 2),
          knob(theme.textHeight * 3 / 2,
                 theme.textHeight * 3 / 2),
          valueMeterHorizontal(theme.textHeight * 4,
                               theme.textHeight),
          valueMeterVertical(theme.textHeight,
                             theme.textHeight * 4),
          valueSlider(theme.textHeight * 4,
                      theme.textHeight)
    {
    }
};

// --------------------------------------------------------------------------------------------------------------------

class QuantumButton : public NanoSubWidget,
                      public ButtonEventHandler
{
    const QuantumTheme& theme;
    Color backgroundColor = theme.widgetDefaultActiveColor;
    char* label = nullptr;

public:
    explicit QuantumButton(TopLevelWidget* parent, const QuantumTheme& theme);
    ~QuantumButton() override;

    inline Color getBackgroundColor() const noexcept
    {
        return backgroundColor;
    }

    inline const char* getLabel() const noexcept
    {
        return label;
    }

    void setBackgroundColor(Color color);
    void setLabel(const char* label, bool adjustWidth = true);

protected:
    void onNanoDisplay() override;
    bool onMouse(const MouseEvent& ev) override;
    bool onMotion(const MotionEvent& ev) override;

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(QuantumButton)
};

// --------------------------------------------------------------------------------------------------------------------

// alignment uses NanoVG::Align
class QuantumLabel : public NanoSubWidget
{
    const QuantumTheme& theme;
    uint alignment = ALIGN_LEFT|ALIGN_MIDDLE;
    char* label = nullptr;

public:
    explicit QuantumLabel(TopLevelWidget* parent, const QuantumTheme& theme);
    ~QuantumLabel() override;

    inline uint getAlignment() const noexcept
    {
        return alignment;
    }

    inline const char* getLabel() const noexcept
    {
        return label;
    }

    void setAlignment(uint alignment);
    void setLabel(const char* label, bool adjustWidth = true);

protected:
    void onNanoDisplay() override;

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(QuantumLabel)
};

// --------------------------------------------------------------------------------------------------------------------

class QuantumSwitch : public NanoSubWidget,
                      public ButtonEventHandler
{
    const QuantumTheme& theme;
    char* label = nullptr;

public:
    explicit QuantumSwitch(TopLevelWidget* parent, const QuantumTheme& theme);
    ~QuantumSwitch() override;

    inline const char* getLabel() const noexcept
    {
        return label;
    }

    // width changes when called
    void setLabel(const char* label);

protected:
    void onNanoDisplay() override;
    bool onMouse(const MouseEvent& ev) override;
    bool onMotion(const MotionEvent& ev) override;

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(QuantumSwitch)
};

// --------------------------------------------------------------------------------------------------------------------

class QuantumDualSidedSwitch : public NanoSubWidget,
                               public ButtonEventHandler
{
    const QuantumTheme& theme;
    char* labelLeft = nullptr;
    char* labelRight = nullptr;

public:
    explicit QuantumDualSidedSwitch(TopLevelWidget* parent, const QuantumTheme& theme);
    ~QuantumDualSidedSwitch() override;

    // width changes when called
    void setLabels(const char* left, const char* right);

protected:
    void onNanoDisplay() override;
    bool onMouse(const MouseEvent& ev) override;
    bool onMotion(const MotionEvent& ev) override;

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(QuantumDualSidedSwitch)
};

// --------------------------------------------------------------------------------------------------------------------

class QuantumKnob : public NanoSubWidget,
                    public KnobEventHandler
{
    const QuantumTheme& theme;
    Color backgroundColor = theme.widgetDefaultActiveColor;

public:
    explicit QuantumKnob(TopLevelWidget* parent, const QuantumTheme& theme);

    inline Color getBackgroundColor() const noexcept
    {
        return backgroundColor;
    }

    void setBackgroundColor(Color color);

protected:
    void onNanoDisplay() override;
    bool onMouse(const MouseEvent& ev) override;
    bool onMotion(const MotionEvent& ev) override;
    bool onScroll(const ScrollEvent& ev) override;

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(QuantumKnob)
};

// --------------------------------------------------------------------------------------------------------------------

class QuantumMixerSlider : public NanoSubWidget,
                           public KnobEventHandler
{
    const QuantumTheme& theme;

public:
    explicit QuantumMixerSlider(TopLevelWidget* parent, const QuantumTheme& theme);

protected:
    void onNanoDisplay() override;
    bool onMouse(const MouseEvent& ev) override;
    bool onMotion(const MotionEvent& ev) override;
    bool onScroll(const ScrollEvent& ev) override;

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(QuantumMixerSlider)
};

// --------------------------------------------------------------------------------------------------------------------

class QuantumValueMeter : public NanoSubWidget
{
public:
    enum Orientation {
        LeftToRight,
        RightToLeft,
        TopToBottom,
        BottomToTop
    };

    explicit QuantumValueMeter(TopLevelWidget* parent, const QuantumTheme& theme);

    inline Color getBackgroundColor() const noexcept
    {
        return backgroundColor;
    }

    inline Orientation getOrientation() const noexcept
    {
        return orientation;
    }

    inline const char* getUnitLabel() const noexcept
    {
        return unitLabel;
    }

    void setBackgroundColor(Color color);
    void setOrientation(Orientation orientation);
    void setRange(float min, float max);
    void setValue(float value);
    void setUnitLabel(const char* label);

protected:
    void onNanoDisplay() override;

    const QuantumTheme& theme;
    Color backgroundColor = theme.widgetDefaultAlternativeColor;
    float maximum = 1.f;
    float minimum = 0.f;
    Orientation orientation = LeftToRight;
    char* unitLabel = nullptr;
    float value = 0.f;

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(QuantumValueMeter)
};

// --------------------------------------------------------------------------------------------------------------------

class QuantumValueSlider : public NanoSubWidget,
                           public KnobEventHandler
{
    const QuantumTheme& theme;
    Color backgroundColor = theme.widgetDefaultActiveColor;
    char* unitLabel = nullptr;

public:
    explicit QuantumValueSlider(TopLevelWidget* parent, const QuantumTheme& theme);

    inline Color getBackgroundColor() const noexcept
    {
        return backgroundColor;
    }

    inline const char* getUnitLabel() const noexcept
    {
        return unitLabel;
    }

    void setBackgroundColor(Color color);
    void setUnitLabel(const char* label);

    bool setValue(float value, bool sendCallback = false) noexcept override;

protected:
    void onNanoDisplay() override;
    bool onMouse(const MouseEvent& ev) override;
    bool onMotion(const MotionEvent& ev) override;
    bool onScroll(const ScrollEvent& ev) override;

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(QuantumValueSlider)
};

// --------------------------------------------------------------------------------------------------------------------

class QuantumLevelMeter : public QuantumValueMeter,
                          public IdleCallback
{
    float falloff = 0.f;

public:
    explicit QuantumLevelMeter(TopLevelWidget* parent, const QuantumTheme& theme);

protected:
    void onNanoDisplay() override;
    void idleCallback() override;

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(QuantumLevelMeter)
};

// --------------------------------------------------------------------------------------------------------------------

class QuantumMixerSliderWithLevelMeter : public NanoSubWidget,
                                         public IdleCallback
{
    const QuantumTheme& theme;

public:
    explicit QuantumMixerSliderWithLevelMeter(TopLevelWidget* parent, const QuantumTheme& theme);

    // publicly exposed for convenience, please do not resize or reposition these
    QuantumLevelMeter meter;
    QuantumMixerSlider slider;

protected:
    void onNanoDisplay() override;
    void onPositionChanged(const PositionChangedEvent& ev) override;
    void onResize(const ResizeEvent& ev) override;
    void idleCallback() override;

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(QuantumMixerSliderWithLevelMeter)
};

// --------------------------------------------------------------------------------------------------------------------

class QuantumValueMeter17 : public NanoSubWidget
{
    const QuantumTheme& theme;
    float values[17] = {};

public:
    explicit QuantumValueMeter17(TopLevelWidget* parent, const QuantumTheme& theme);

    void setValue(uint index, float value);

protected:
    void onNanoDisplay() override;

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(QuantumValueMeter17)
};

// --------------------------------------------------------------------------------------------------------------------

class QuantumFrameGroup : public NanoSubWidget
{
    const QuantumTheme& theme;

public:
    explicit QuantumFrameGroup(TopLevelWidget* parent, const QuantumTheme& theme);

protected:
    void onNanoDisplay() override;
    void onPositionChanged(const PositionChangedEvent& ev) override;

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(QuantumFrameGroup)
};

// --------------------------------------------------------------------------------------------------------------------

// fixed meter, expanding label
struct QuantumValueMeterWithLabel : HorizontalLayout
{
    QuantumValueMeter meter;
    QuantumLabel label;

    explicit QuantumValueMeterWithLabel(TopLevelWidget* parent, const QuantumTheme& theme);
};

// fixed slider, expanding label
struct QuantumValueSliderWithLabel : HorizontalLayout
{
    QuantumValueSlider slider;
    QuantumLabel label;

    explicit QuantumValueSliderWithLabel(TopLevelWidget* parent, const QuantumTheme& theme);
};

// sliders on both sides, center expanding label
struct QuantumDualValueSliderWithCenterLabel : HorizontalLayout
{
    QuantumValueSlider sliderL;
    QuantumLabel label;
    QuantumValueSlider sliderR;

    explicit QuantumDualValueSliderWithCenterLabel(TopLevelWidget* parent, const QuantumTheme& theme);
};

// single expanding switch
struct QuantumSwitchWithLayout : HorizontalLayout
{
    QuantumSwitch switch_;

    explicit QuantumSwitchWithLayout(TopLevelWidget* parent, const QuantumTheme& theme);
};

// --------------------------------------------------------------------------------------------------------------------

template<class tMainWidget>
class QuantumGroupWithVerticallyStackedLayout : public NanoSubWidget
{
    const QuantumTheme& theme;

public:
    explicit QuantumGroupWithVerticallyStackedLayout(TopLevelWidget* parent, const QuantumTheme& theme);

    // place widgets here
    VerticallyStackedHorizontalLayout layout;

    // publicly exposed for convenience, do not resize or reposition
    tMainWidget mainWidget;

    // adjust size to fit full layout contents
    void adjustSize();

    // FIXME remove this once proper child widget setup id added
    void showAll();
    void hideAll();

protected:
    void onNanoDisplay() override;
    void onPositionChanged(const PositionChangedEvent& ev) override;
    void onResize(const ResizeEvent& ev) override;

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(QuantumGroupWithVerticallyStackedLayout)
};

// --------------------------------------------------------------------------------------------------------------------

END_NAMESPACE_DGL