#pragma once

#include <Geode/loader/SettingV3.hpp>

#define SHOW_HEADS_UP_WARNING\
	return FLAlertLayer::create(nullptr, "Config Directory Opened!", R"(Hi there! TexturePlatformerButtons doesn't come with any preset files for platformer button textures.
	I have zero faith in you to name your image files while following a specific format, and covering every imaginable combination and permutation of the words "player", "1"/"one"/"2"/"two", "left"/"jump"/"right", and "main"/"pressed" is beyond what this mod was designed to do.
	However, setting the textures of six different buttons (twelve if you want custom textures when the button is pressed) gets real tedious real fast.
	Feel free to use this mod's config directory to make your own sets of custom platformer button texture presets.
	Go ahead, I won't stop you.
	--RayDeeUx)", "OK", nullptr, 420.f, true, 320.f, 1.f)->show()

using namespace geode::prelude;

class MyButtonSettingV3 : public SettingV3 {
public:
	static Result<std::shared_ptr<SettingV3>> parse(std::string const& key, std::string const& modID, matjson::Value const& json) {
		auto res = std::make_shared<MyButtonSettingV3>();
		auto root = checkJson(json, "MyButtonSettingV3");
		res->init(key, modID, root);
		res->parseNameAndDescription(root);
		res->parseEnableIf(root);
		return root.ok(std::static_pointer_cast<SettingV3>(res));
	}
	bool load(matjson::Value const& json) override {
		return true;
	}
	bool save(matjson::Value& json) const override {
		return true;
	}
	bool isDefaultValue() const override {
		return true;
	}
	void reset() override {}
	// SettingNodeV3* createNode(float width) override; // this line is [absolutely] certified cringe
	SettingNodeV3 *createNode(float width) override; // this line is NOT certified cringe
};

class MyButtonSettingNodeV3 : public SettingNodeV3 {
private:
	std::string m_desc = "";
public:
	void onCommit() {}
	void onResetToDefault() {}
	bool hasUncommittedChanges() const {
		return false;
	}
	bool hasNonDefaultValue() const {
		return false;
	}
	void onConfigDirButton(CCObject*) {
		file::openFolder(Mod::get()->getConfigDir());
		#ifndef GEODE_IS_MOBILE
		if (!CCKeyboardDispatcher::get()->getShiftKeyPressed()) SHOW_HEADS_UP_WARNING;
		FLAlertLayer::create(
			"Config Directory Opened!",
			m_desc,
			"Aight"
		)->show();
		#else
		SHOW_HEADS_UP_WARNING
		#endif
	}
	bool init(std::shared_ptr<MyButtonSettingV3> setting, float width) {
		if (!SettingNodeV3::init(setting, width)) return false;
		this->setContentSize({ width, 40.f });
		std::string name = setting->getName().value();
		m_desc = setting->getDescription().value();
		CCMenu* theMenu = CCMenu::create();
		CCLabelBMFont* theLabel = CCLabelBMFont::create(name.c_str(), "bigFont.fnt");

		// copied a bit from louis ck jr
		theLabel->setScale(.35f);
		theLabel->limitLabelWidth(300.f, .35f, .25f); // added by Ery. max width is 346.f

		CCMenuItemSpriteExtra* theLabelAsAButton = CCMenuItemSpriteExtra::create(theLabel, this, menu_selector(MyButtonSettingNodeV3::onConfigDirButton));

		theLabelAsAButton->setPositionX(0);
		theLabelAsAButton->m_scaleMultiplier = 1.1f;
		theLabelAsAButton->setID("config-dir-shortcut-button"_spr);

		theMenu->addChild(theLabelAsAButton);
		theMenu->setPosition(width / 2, 20.f);
		theMenu->setID("config-dir-shortcut-menu"_spr);

		this->addChild(theMenu);

		for (const auto &node : CCArrayExt<CCNode*>(this->getChildren())) node->setVisible(!node->getID().empty() && utils::string::startsWith(node->getID(), Mod::get()->getID()));

		return true;
	}
	static MyButtonSettingNodeV3* create(std::shared_ptr<MyButtonSettingV3> setting, float width) {
		auto ret = new MyButtonSettingNodeV3();
		if (ret && ret->init(setting, width)) {
			ret->autorelease();
			return ret;
		}
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
};