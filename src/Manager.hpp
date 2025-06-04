#pragma once

#include "Utils.hpp"

// Manager.hpp structure by acaruso
// reused with explicit permission and strong encouragement

using namespace geode::prelude;

class Manager {

protected:
	static Manager* instance;
public:

	bool enabled = false;

	bool textureP1JumpWhenPressed = false;
	bool textureP2JumpWhenPressed = false;
	bool textureP1LeftWhenPressed = false;
	bool textureP2LeftWhenPressed = false;
	bool textureP1RightWhenPressed = false;
	bool textureP2RightWhenPressed = false;

	bool disableTintingP1Jump = false;
    bool disableTintingP2Jump = false;
    bool disableTintingP1Left = false;
    bool disableTintingP2Left = false;
    bool disableTintingP1Right = false;
    bool disableTintingP2Right = false;

	bool logging = false;

	std::string jumpMainTextureP1;
	std::string jumpMainTextureP2;
	std::string leftMainTextureP1;
	std::string leftMainTextureP2;
	std::string rightMainTextureP1;
	std::string rightMainTextureP2;

	std::string jumpPressedTextureP1;
	std::string jumpPressedTextureP2;
	std::string leftPressedTextureP1;
	std::string leftPressedTextureP2;
	std::string rightPressedTextureP1;
	std::string rightPressedTextureP2;

	static Manager* getSharedInstance() {
		if (!instance) instance = new Manager();
		return instance;
	}

	static void loadStuff() {
		if (!instance) instance = new Manager();
		instance->enabled = Utils::getBool("enabled");

		instance->textureP1JumpWhenPressed = Utils::getBool("textureP1JumpWhenPressed");
		instance->textureP2JumpWhenPressed = Utils::getBool("textureP2JumpWhenPressed");
		instance->textureP1LeftWhenPressed = Utils::getBool("textureP1LeftWhenPressed");
		instance->textureP2LeftWhenPressed = Utils::getBool("textureP2LeftWhenPressed");
		instance->textureP1RightWhenPressed = Utils::getBool("textureP1RightWhenPressed");
		instance->textureP2RightWhenPressed = Utils::getBool("textureP2RightWhenPressed");

		instance->disableTintingP1Jump = Utils::getBool("disableTintingP1Jump");
		instance->disableTintingP2Jump = Utils::getBool("disableTintingP2Jump");
		instance->disableTintingP1Left = Utils::getBool("disableTintingP1Left");
		instance->disableTintingP2Left = Utils::getBool("disableTintingP2Left");
		instance->disableTintingP1Right = Utils::getBool("disableTintingP1Right");
		instance->disableTintingP2Right = Utils::getBool("disableTintingP2Right");

		instance->logging = Utils::getBool("logging");
		Mod::get()->setLoggingEnabled(instance->logging);

		instance->jumpMainTextureP1 = Mod::get()->getSettingValue<std::filesystem::path>("jumpMainTextureP1").string();
		if (!geode::utils::string::endsWith(instance->jumpMainTextureP1, ".png") || !std::filesystem::exists(instance->jumpMainTextureP1)) instance->jumpMainTextureP1 = "";
		instance->jumpMainTextureP2 = Mod::get()->getSettingValue<std::filesystem::path>("jumpMainTextureP2").string();
		if (!geode::utils::string::endsWith(instance->jumpMainTextureP2, ".png") || !std::filesystem::exists(instance->jumpMainTextureP2)) instance->jumpMainTextureP2 = "";
		instance->leftMainTextureP1 = Mod::get()->getSettingValue<std::filesystem::path>("leftMainTextureP1").string();
		if (!geode::utils::string::endsWith(instance->leftMainTextureP1, ".png") || !std::filesystem::exists(instance->leftMainTextureP1)) instance->leftMainTextureP1 = "";
		instance->leftMainTextureP2 = Mod::get()->getSettingValue<std::filesystem::path>("leftMainTextureP2").string();
		if (!geode::utils::string::endsWith(instance->leftMainTextureP2, ".png") || !std::filesystem::exists(instance->leftMainTextureP2)) instance->leftMainTextureP2 = "";
		instance->rightMainTextureP1 = Mod::get()->getSettingValue<std::filesystem::path>("rightMainTextureP1").string();
		if (!geode::utils::string::endsWith(instance->rightMainTextureP1, ".png") || !std::filesystem::exists(instance->rightMainTextureP1)) instance->rightMainTextureP1 = "";
		instance->rightMainTextureP2 = Mod::get()->getSettingValue<std::filesystem::path>("rightMainTextureP2").string();
		if (!geode::utils::string::endsWith(instance->rightMainTextureP2, ".png") || !std::filesystem::exists(instance->rightMainTextureP2)) instance->rightMainTextureP2 = "";

		instance->jumpPressedTextureP1 = Mod::get()->getSettingValue<std::filesystem::path>("jumpPressedTextureP1").string();
		if (!geode::utils::string::endsWith(instance->jumpPressedTextureP1, ".png") || !std::filesystem::exists(instance->jumpPressedTextureP1)) instance->jumpPressedTextureP1 = "";
		instance->jumpPressedTextureP2 = Mod::get()->getSettingValue<std::filesystem::path>("jumpPressedTextureP2").string();
		if (!geode::utils::string::endsWith(instance->jumpPressedTextureP2, ".png") || !std::filesystem::exists(instance->jumpPressedTextureP2)) instance->jumpPressedTextureP2 = "";
		instance->leftPressedTextureP1 = Mod::get()->getSettingValue<std::filesystem::path>("leftPressedTextureP1").string();
		if (!geode::utils::string::endsWith(instance->leftPressedTextureP1, ".png") || !std::filesystem::exists(instance->leftPressedTextureP1)) instance->leftPressedTextureP1 = "";
		instance->leftPressedTextureP2 = Mod::get()->getSettingValue<std::filesystem::path>("leftPressedTextureP2").string();
		if (!geode::utils::string::endsWith(instance->leftPressedTextureP2, ".png") || !std::filesystem::exists(instance->leftPressedTextureP2)) instance->leftPressedTextureP2 = "";
		instance->rightPressedTextureP1 = Mod::get()->getSettingValue<std::filesystem::path>("rightPressedTextureP1").string();
		if (!geode::utils::string::endsWith(instance->rightPressedTextureP1, ".png") || !std::filesystem::exists(instance->rightPressedTextureP1)) instance->rightPressedTextureP1 = "";
		instance->rightPressedTextureP2 = Mod::get()->getSettingValue<std::filesystem::path>("rightPressedTextureP2").string();
		if (!geode::utils::string::endsWith(instance->rightPressedTextureP2, ".png") || !std::filesystem::exists(instance->rightPressedTextureP2)) instance->rightPressedTextureP2 = "";
	}

};