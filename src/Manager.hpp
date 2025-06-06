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

	bool textureP1JumpWhenPressedTwoPlayer = false;
	bool textureP2JumpWhenPressedTwoPlayer = false;
	bool textureP1LeftWhenPressedTwoPlayer = false;
	bool textureP2LeftWhenPressedTwoPlayer = false;
	bool textureP1RightWhenPressedTwoPlayer = false;
	bool textureP2RightWhenPressedTwoPlayer = false;

	bool disableTintingP1JumpTwoPlayer = false;
	bool disableTintingP2JumpTwoPlayer = false;
	bool disableTintingP1LeftTwoPlayer = false;
	bool disableTintingP2LeftTwoPlayer = false;
	bool disableTintingP1RightTwoPlayer = false;
	bool disableTintingP2RightTwoPlayer = false;

	std::string jumpMainTextureP1TwoPlayer;
	std::string jumpMainTextureP2TwoPlayer;
	std::string leftMainTextureP1TwoPlayer;
	std::string leftMainTextureP2TwoPlayer;
	std::string rightMainTextureP1TwoPlayer;
	std::string rightMainTextureP2TwoPlayer;

	std::string jumpPressedTextureP1TwoPlayer;
	std::string jumpPressedTextureP2TwoPlayer;
	std::string leftPressedTextureP1TwoPlayer;
	std::string leftPressedTextureP2TwoPlayer;
	std::string rightPressedTextureP1TwoPlayer;
	std::string rightPressedTextureP2TwoPlayer;

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

		instance->textureP1JumpWhenPressedTwoPlayer = Utils::getBool("textureP1JumpWhenPressedTwoPlayer");
		instance->textureP2JumpWhenPressedTwoPlayer = Utils::getBool("textureP2JumpWhenPressedTwoPlayer");
		instance->textureP1LeftWhenPressedTwoPlayer = Utils::getBool("textureP1LeftWhenPressedTwoPlayer");
		instance->textureP2LeftWhenPressedTwoPlayer = Utils::getBool("textureP2LeftWhenPressedTwoPlayer");
		instance->textureP1RightWhenPressedTwoPlayer = Utils::getBool("textureP1RightWhenPressedTwoPlayer");
		instance->textureP2RightWhenPressedTwoPlayer = Utils::getBool("textureP2RightWhenPressedTwoPlayer");

		instance->disableTintingP1JumpTwoPlayer = Utils::getBool("disableTintingP1JumpTwoPlayer");
		instance->disableTintingP2JumpTwoPlayer = Utils::getBool("disableTintingP2JumpTwoPlayer");
		instance->disableTintingP1LeftTwoPlayer = Utils::getBool("disableTintingP1LeftTwoPlayer");
		instance->disableTintingP2LeftTwoPlayer = Utils::getBool("disableTintingP2LeftTwoPlayer");
		instance->disableTintingP1RightTwoPlayer = Utils::getBool("disableTintingP1RightTwoPlayer");
		instance->disableTintingP2RightTwoPlayer = Utils::getBool("disableTintingP2RightTwoPlayer");

		instance->jumpMainTextureP1TwoPlayer = Mod::get()->getSettingValue<std::filesystem::path>("jumpMainTextureP1TwoPlayer").string();
		if (!geode::utils::string::endsWith(instance->jumpMainTextureP1TwoPlayer, ".png") || !std::filesystem::exists(instance->jumpMainTextureP1TwoPlayer)) instance->jumpMainTextureP1TwoPlayer = "";
		instance->jumpMainTextureP2TwoPlayer = Mod::get()->getSettingValue<std::filesystem::path>("jumpMainTextureP2TwoPlayer").string();
		if (!geode::utils::string::endsWith(instance->jumpMainTextureP2TwoPlayer, ".png") || !std::filesystem::exists(instance->jumpMainTextureP2TwoPlayer)) instance->jumpMainTextureP2TwoPlayer = "";
		instance->leftMainTextureP1TwoPlayer = Mod::get()->getSettingValue<std::filesystem::path>("leftMainTextureP1TwoPlayer").string();
		if (!geode::utils::string::endsWith(instance->leftMainTextureP1TwoPlayer, ".png") || !std::filesystem::exists(instance->leftMainTextureP1TwoPlayer)) instance->leftMainTextureP1TwoPlayer = "";
		instance->leftMainTextureP2TwoPlayer = Mod::get()->getSettingValue<std::filesystem::path>("leftMainTextureP2TwoPlayer").string();
		if (!geode::utils::string::endsWith(instance->leftMainTextureP2TwoPlayer, ".png") || !std::filesystem::exists(instance->leftMainTextureP2TwoPlayer)) instance->leftMainTextureP2TwoPlayer = "";
		instance->rightMainTextureP1TwoPlayer = Mod::get()->getSettingValue<std::filesystem::path>("rightMainTextureP1TwoPlayer").string();
		if (!geode::utils::string::endsWith(instance->rightMainTextureP1TwoPlayer, ".png") || !std::filesystem::exists(instance->rightMainTextureP1TwoPlayer)) instance->rightMainTextureP1TwoPlayer = "";
		instance->rightMainTextureP2TwoPlayer = Mod::get()->getSettingValue<std::filesystem::path>("rightMainTextureP2TwoPlayer").string();
		if (!geode::utils::string::endsWith(instance->rightMainTextureP2TwoPlayer, ".png") || !std::filesystem::exists(instance->rightMainTextureP2TwoPlayer)) instance->rightMainTextureP2TwoPlayer = "";

		instance->jumpPressedTextureP1TwoPlayer = Mod::get()->getSettingValue<std::filesystem::path>("jumpPressedTextureP1TwoPlayer").string();
		if (!geode::utils::string::endsWith(instance->jumpPressedTextureP1TwoPlayer, ".png") || !std::filesystem::exists(instance->jumpPressedTextureP1TwoPlayer)) instance->jumpPressedTextureP1TwoPlayer = "";
		instance->jumpPressedTextureP2TwoPlayer = Mod::get()->getSettingValue<std::filesystem::path>("jumpPressedTextureP2TwoPlayer").string();
		if (!geode::utils::string::endsWith(instance->jumpPressedTextureP2TwoPlayer, ".png") || !std::filesystem::exists(instance->jumpPressedTextureP2TwoPlayer)) instance->jumpPressedTextureP2TwoPlayer = "";
		instance->leftPressedTextureP1TwoPlayer = Mod::get()->getSettingValue<std::filesystem::path>("leftPressedTextureP1TwoPlayer").string();
		if (!geode::utils::string::endsWith(instance->leftPressedTextureP1TwoPlayer, ".png") || !std::filesystem::exists(instance->leftPressedTextureP1TwoPlayer)) instance->leftPressedTextureP1TwoPlayer = "";
		instance->leftPressedTextureP2TwoPlayer = Mod::get()->getSettingValue<std::filesystem::path>("leftPressedTextureP2TwoPlayer").string();
		if (!geode::utils::string::endsWith(instance->leftPressedTextureP2TwoPlayer, ".png") || !std::filesystem::exists(instance->leftPressedTextureP2TwoPlayer)) instance->leftPressedTextureP2TwoPlayer = "";
		instance->rightPressedTextureP1TwoPlayer = Mod::get()->getSettingValue<std::filesystem::path>("rightPressedTextureP1TwoPlayer").string();
		if (!geode::utils::string::endsWith(instance->rightPressedTextureP1TwoPlayer, ".png") || !std::filesystem::exists(instance->rightPressedTextureP1TwoPlayer)) instance->rightPressedTextureP1TwoPlayer = "";
		instance->rightPressedTextureP2TwoPlayer = Mod::get()->getSettingValue<std::filesystem::path>("rightPressedTextureP2TwoPlayer").string();
		if (!geode::utils::string::endsWith(instance->rightPressedTextureP2TwoPlayer, ".png") || !std::filesystem::exists(instance->rightPressedTextureP2TwoPlayer)) instance->rightPressedTextureP2TwoPlayer = "";
	}

};