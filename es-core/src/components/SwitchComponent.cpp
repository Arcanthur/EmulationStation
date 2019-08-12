#include "MenuThemeData.h"
#include "SwitchComponent.h"

#include "resources/Font.h"
#include "Renderer.h"

SwitchComponent::SwitchComponent(Window* window, bool state) : GuiComponent(window), mImage(window), mState(state)
{
	auto menuTheme = MenuThemeData::getInstance()->getCurrentTheme();
	mImage.setImage(mState ? menuTheme->iconSet.on : menuTheme->iconSet.off);
	mImage.setResize(0, menuTheme->text.font->getLetterHeight());
	mImage.setColorShift(menuTheme->text.color);
	mSize = mImage.getSize();
}

void SwitchComponent::onSizeChanged()
{
	mImage.setSize(mSize);
}

bool SwitchComponent::input(InputConfig* config, Input input)
{
	if(config->isMappedTo("a", input) && input.value)
	{
		mState = !mState;
		onStateChanged();
		return true;
	}

	return false;
}

void SwitchComponent::render(const Transform4x4f& parentTrans)
{
	Transform4x4f trans = parentTrans * getTransform();
	
	mImage.render(trans);

	renderChildren(trans);
}

bool SwitchComponent::getState() const
{
	return mState;
}

void SwitchComponent::setState(bool state)
{
	mState = state;
	onStateChanged();
}

std::string SwitchComponent::getValue() const
{
	return mState ?  "true" : "false";
}

void SwitchComponent::setValue(const std::string& statestring)
{
	if (statestring == "true")
	{
		mState = true;
	}else
	{
		mState = false;
	}
	onStateChanged();
}

void SwitchComponent::onStateChanged()
{
	mImage.setImage(mState ? ":/on.svg" : ":/off.svg");
}

std::vector<HelpPrompt> SwitchComponent::getHelpPrompts()
{
	std::vector<HelpPrompt> prompts;
	prompts.push_back(HelpPrompt("a", "change"));
	return prompts;
}
