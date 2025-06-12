#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/UILayer.hpp>
#include "Settings.hpp"
#include "Manager.hpp"

using namespace geode::prelude;

$on_mod(Loaded) {
	(void) Mod::get()->registerCustomSettingType("configdir", &MyButtonSettingV3::parse);
	Manager::loadStuff();
	listenForAllSettingChanges([](std::shared_ptr<SettingV3> _) { Manager::loadStuff(); });
	auto readme = Mod::get()->getConfigDir() / R"(README.txt)";
	if (std::filesystem::exists(readme)) return;
	const std::string& content = R"(Hi there! TexturePlatformerButtons doesn't come with any preset files for platformer button textures.
I have zero faith in you to name your image files while following a specific format, and covering every imaginable combination and permutation of the words "player", "1"/"one"/"2"/"two", "left"/"jump"/"right", and "main"/"pressed" is beyond what this mod was designed to do.
However, setting the textures of six different buttons (twelve if you want custom textures when the button is pressed) gets real tedious real fast.
Feel free to use this mod's config directory to make your own sets of custom platformer button texture presets.
Go ahead, I won't mind.
--RayDeeUx)";
	if (const auto result = utils::file::writeString(readme, content); result.isErr()) log::error("Error writing to README.txt");
}

static std::string unpressedPlayerOneJumpSpriteID = "plat-p1-jump"_spr;
static std::string unpressedPlayerOneLeftSpriteID = "plat-p1-left"_spr;
static std::string unpressedPlayerOneRightSpriteID = "plat-p1-right"_spr;

static std::string pressedPlayerOneJumpSpriteID = "plat-p1-jump-pressed"_spr;
static std::string pressedPlayerOneLeftSpriteID = "plat-p1-left-pressed"_spr;
static std::string pressedPlayerOneRightSpriteID = "plat-p1-right-pressed"_spr;

static std::string unpressedPlayerTwoJumpSpriteID = "plat-p2-jump"_spr;
static std::string unpressedPlayerTwoLeftSpriteID = "plat-p2-left"_spr;
static std::string unpressedPlayerTwoRightSpriteID = "plat-p2-right"_spr;

static std::string pressedPlayerTwoJumpSpriteID = "plat-p2-jump-pressed"_spr;
static std::string pressedPlayerTwoLeftSpriteID = "plat-p2-left-pressed"_spr;
static std::string pressedPlayerTwoRightSpriteID = "plat-p2-right-pressed"_spr;

GLubyte platP1LeftOpacity = 0;
GLubyte platP1RightOpacity = 0;
GLubyte platP1JumpOpacity = 0;
GLubyte platP2LeftOpacity = 0;
GLubyte platP2RightOpacity = 0;
GLubyte platP2JumpOpacity = 0;

static void addTexturesToButton(CCSprite* originalSprite, CCSprite* replacementSprite, const std::string& nodeID, const bool disableTinting) {
	if (!originalSprite || !replacementSprite) return log::info("[NULLPTR]: !originalSprite: {} | !replacementSprite: {}", !originalSprite, !replacementSprite);

	const bool isPressedSprite = utils::string::contains(nodeID, "-pressed");
	std::string userObjectID = isPressedSprite ? "pressed-added"_spr : "unpressed-added"_spr;
	if (originalSprite->getUserObject(userObjectID)) return log::info("[EARLY RETURN]: {} was already added for potential sprite {}", userObjectID, nodeID);

	const GLubyte originalOpacity = originalSprite->getOpacity();
	const CCSize originalSize = originalSprite->getContentSize();
	const CCSize replacementSize = replacementSprite->getContentSize();
	const float yRatio = originalSize.height / replacementSize.height;
	const float xRatio = originalSize.width / replacementSize.width;

	originalSprite->setCascadeColorEnabled(!disableTinting);
	originalSprite->setCascadeOpacityEnabled(false);
	originalSprite->setOpacity(0);
	originalSprite->addChild(replacementSprite);
	originalSprite->setUserObject(userObjectID, CCBool::create(true));

	replacementSprite->setTag(isPressedSprite ? 6022025 : 6012025);
	replacementSprite->setScale(std::min(xRatio, yRatio));
	replacementSprite->setPosition(originalSize / 2.f);
	replacementSprite->setID(nodeID);

	if (!isPressedSprite) return;

	replacementSprite->setVisible(false);
	if (!originalSprite->getChildByTag(6012025)) originalSprite->setOpacity(originalOpacity);
}

void findAndAddTextures(UILayer* uiLayer, const GJBaseGameLayer* gjbgl) {
	const Manager* manager = Manager::getSharedInstance();
	if (!manager->enabled) return;

	log::info("initalizing sprites !!!");
	CCSprite* p1JumpPressedSprite = nullptr;
	CCSprite* p2JumpPressedSprite = nullptr;
	CCSprite* p1LeftPressedSprite = nullptr;
	CCSprite* p2LeftPressedSprite = nullptr;
	CCSprite* p1RightPressedSprite = nullptr;
	CCSprite* p2RightPressedSprite = nullptr;

	const bool is2P = gjbgl->m_level->m_twoPlayerMode;

	CCSprite* p1JumpSprite = CCSprite::create(is2P ? manager->jumpMainTextureP1TwoPlayer.c_str() : manager->jumpMainTextureP1.c_str());
	if (is2P ? manager->textureP1JumpWhenPressedTwoPlayer : manager->textureP1JumpWhenPressed) p1JumpPressedSprite = CCSprite::create(is2P ? manager->jumpPressedTextureP1TwoPlayer.c_str() : manager->jumpPressedTextureP1.c_str());

	CCSprite* p1LeftSprite = CCSprite::create(is2P ? manager->leftMainTextureP1TwoPlayer.c_str() : manager->leftMainTextureP1.c_str());
	if (is2P ? manager->textureP1LeftWhenPressedTwoPlayer : manager->textureP1LeftWhenPressed) p1LeftPressedSprite = CCSprite::create(is2P ? manager->leftPressedTextureP1TwoPlayer.c_str() : manager->leftPressedTextureP1.c_str());

	CCSprite* p1RightSprite = CCSprite::create(is2P ? manager->rightMainTextureP1TwoPlayer.c_str() : manager->rightMainTextureP1.c_str());
	if (is2P ? manager->textureP1RightWhenPressedTwoPlayer : manager->textureP1RightWhenPressed) p1RightPressedSprite = CCSprite::create(is2P ? manager->rightPressedTextureP1TwoPlayer.c_str() : manager->rightPressedTextureP1.c_str());

	const bool jP1Valid = p1JumpSprite && !p1JumpSprite->getUserObject("geode.texture-loader/fallback");
	const bool lP1Valid = p1LeftSprite && !p1LeftSprite->getUserObject("geode.texture-loader/fallback");
	const bool rP1Valid = p1RightSprite && !p1RightSprite->getUserObject("geode.texture-loader/fallback");

	const bool jP1PressedValid = p1JumpPressedSprite && !p1JumpPressedSprite->getUserObject("geode.texture-loader/fallback");
	const bool lP1PressedValid = p1LeftPressedSprite && !p1LeftPressedSprite->getUserObject("geode.texture-loader/fallback");
	const bool rP1PressedValid = p1RightPressedSprite && !p1RightPressedSprite->getUserObject("geode.texture-loader/fallback");

	CCSprite* p2JumpSprite = CCSprite::create(is2P ? manager->jumpMainTextureP2TwoPlayer.c_str() : manager->jumpMainTextureP2.c_str());
	if (is2P ? manager->textureP2JumpWhenPressedTwoPlayer : manager->textureP2JumpWhenPressed) p2JumpPressedSprite = CCSprite::create(is2P ? manager->jumpPressedTextureP2TwoPlayer.c_str() : manager->jumpPressedTextureP2.c_str());

	CCSprite* p2LeftSprite = CCSprite::create(is2P ? manager->leftMainTextureP2TwoPlayer.c_str() : manager->leftMainTextureP2.c_str());
	if (is2P ? manager->textureP2LeftWhenPressedTwoPlayer : manager->textureP2LeftWhenPressed) p2LeftPressedSprite = CCSprite::create(is2P ? manager->leftPressedTextureP2TwoPlayer.c_str() : manager->leftPressedTextureP2.c_str());

	CCSprite* p2RightSprite = CCSprite::create(is2P ? manager->rightMainTextureP2TwoPlayer.c_str() : manager->rightMainTextureP2.c_str());
	if (is2P ? manager->textureP2RightWhenPressedTwoPlayer : manager->textureP2RightWhenPressed) p2RightPressedSprite = CCSprite::create(is2P ? manager->rightPressedTextureP2TwoPlayer.c_str() : manager->rightPressedTextureP2.c_str());

	const bool jP2Valid = p2JumpSprite && !p2JumpSprite->getUserObject("geode.texture-loader/fallback");
	const bool lP2Valid = p2LeftSprite && !p2LeftSprite->getUserObject("geode.texture-loader/fallback");
	const bool rP2Valid = p2RightSprite && !p2RightSprite->getUserObject("geode.texture-loader/fallback");

	const bool jP2PressedValid = p2JumpPressedSprite && !p2JumpPressedSprite->getUserObject("geode.texture-loader/fallback");
	const bool lP2PressedValid = p2LeftPressedSprite && !p2LeftPressedSprite->getUserObject("geode.texture-loader/fallback");
	const bool rP2PressedValid = p2RightPressedSprite && !p2RightPressedSprite->getUserObject("geode.texture-loader/fallback");

	log::info("jP1Valid: {}", jP1Valid);
	log::info("lP1Valid: {}", lP1Valid);
	log::info("rP1Valid: {}", rP1Valid);
	log::info("jP1PressedValid: {}", jP1PressedValid);
	log::info("lP1PressedValid: {}", lP1PressedValid);
	log::info("rP1PressedValid: {}", rP1PressedValid);
	log::info("jP2Valid: {}", jP2Valid);
	log::info("lP2Valid: {}", lP2Valid);
	log::info("rP2Valid: {}", rP2Valid);
	log::info("jP2PressedValid: {}", jP2PressedValid);
	log::info("lP2PressedValid: {}", lP2PressedValid);
	log::info("rP2PressedValid: {}", rP2PressedValid);

	const auto platP1Move = manager->hasNodeIDs ? uiLayer->getChildByID("platformer-p1-move-button") : typeinfo_cast<GJUINode*>(uiLayer->m_uiNodes->objectAtIndex(0));
	const auto platP2Move = manager->hasNodeIDs ? uiLayer->getChildByID("platformer-p2-move-button") : typeinfo_cast<GJUINode*>(uiLayer->m_uiNodes->objectAtIndex(1));
	const auto platP1Jump = manager->hasNodeIDs ? uiLayer->getChildByID("platformer-p1-jump-button") : typeinfo_cast<GJUINode*>(uiLayer->m_uiNodes->objectAtIndex(2));
	const auto platP2Jump = manager->hasNodeIDs ? uiLayer->getChildByID("platformer-p2-jump-button") : typeinfo_cast<GJUINode*>(uiLayer->m_uiNodes->objectAtIndex(3));

	if (platP1Move && platP1Move->getChildrenCount() > 1) {
		const auto leftButton = typeinfo_cast<CCSprite*>(platP1Move->getChildren()->objectAtIndex(0));
		if (!leftButton) return log::info("[NULLPTR] AT leftButton! just before checking lP1Valid");
		platP1LeftOpacity = leftButton->getOpacity();
		if (lP1Valid) addTexturesToButton(leftButton, p1LeftSprite, unpressedPlayerOneLeftSpriteID, is2P ? manager->disableTintingP1LeftTwoPlayer : manager->disableTintingP1Left);
		if (lP1PressedValid) addTexturesToButton(leftButton, p1LeftPressedSprite, pressedPlayerOneLeftSpriteID, is2P ? manager->disableTintingP1LeftTwoPlayer : manager->disableTintingP1Left);

		const auto rightButton = typeinfo_cast<CCSprite*>(platP1Move->getChildren()->objectAtIndex(1));
		if (!rightButton) return log::info("[NULLPTR] AT rightButton! just before checking rP1Valid");
		platP1RightOpacity = rightButton->getOpacity();
		if (rP1Valid) addTexturesToButton(rightButton, p1RightSprite, unpressedPlayerOneRightSpriteID, is2P ? manager->disableTintingP1RightTwoPlayer : manager->disableTintingP1Right);
		if (rP1PressedValid) addTexturesToButton(rightButton, p1RightPressedSprite, pressedPlayerOneRightSpriteID, is2P ? manager->disableTintingP1RightTwoPlayer : manager->disableTintingP1Right);
	}
	if (platP1Jump && platP1Jump->getChildrenCount() != 0) {
		const auto jumpButton = typeinfo_cast<CCSprite*>(platP1Jump->getChildren()->objectAtIndex(0));
		if (!jumpButton) return log::info("[NULLPTR] AT jumpButton! just before checking jP1Valid");
		platP1JumpOpacity = jumpButton->getOpacity();
		if (jP1Valid) addTexturesToButton(jumpButton, p1JumpSprite, unpressedPlayerOneJumpSpriteID, is2P ? manager->disableTintingP1JumpTwoPlayer : manager->disableTintingP1Jump);
		if (jP1PressedValid) addTexturesToButton(jumpButton, p1JumpPressedSprite, pressedPlayerOneJumpSpriteID, is2P ? manager->disableTintingP1JumpTwoPlayer : manager->disableTintingP1Jump);
	}

	if (platP2Move && platP2Move->getChildrenCount() > 1) {
		const auto leftButton = typeinfo_cast<CCSprite*>(platP2Move->getChildren()->objectAtIndex(0));
		if (!leftButton) return log::info("[NULLPTR] AT leftButton! just before checking lP2Valid");
		platP2LeftOpacity = leftButton->getOpacity();
		if (lP2Valid) addTexturesToButton(leftButton, p2LeftSprite, unpressedPlayerTwoLeftSpriteID, is2P ? manager->disableTintingP2LeftTwoPlayer : manager->disableTintingP2Left);
		if (lP2PressedValid) addTexturesToButton(leftButton, p2LeftPressedSprite, pressedPlayerTwoLeftSpriteID, is2P ? manager->disableTintingP2LeftTwoPlayer : manager->disableTintingP2Left);

		const auto rightButton = typeinfo_cast<CCSprite*>(platP2Move->getChildren()->objectAtIndex(1));
		if (!rightButton) return log::info("[NULLPTR] AT rightButton! just before checking rP2Valid");
		platP2RightOpacity = rightButton->getOpacity();
		if (rP2Valid) addTexturesToButton(rightButton, p2RightSprite, unpressedPlayerTwoRightSpriteID, is2P ? manager->disableTintingP2RightTwoPlayer : manager->disableTintingP2Right);
		if (rP2PressedValid) addTexturesToButton(rightButton, p2RightPressedSprite, pressedPlayerTwoRightSpriteID, is2P ? manager->disableTintingP2RightTwoPlayer : manager->disableTintingP2Right);
	}
	if (platP2Jump && platP2Jump->getChildrenCount() != 0) {
		const auto jumpButton = typeinfo_cast<CCSprite*>(platP2Jump->getChildren()->objectAtIndex(0));
		if (!jumpButton) return log::info("[NULLPTR] AT jumpButton! just before checking jP2Valid");
		platP2JumpOpacity = jumpButton->getOpacity();
		if (jP2Valid) addTexturesToButton(jumpButton, p2JumpSprite, unpressedPlayerTwoJumpSpriteID, is2P ? manager->disableTintingP2JumpTwoPlayer : manager->disableTintingP2Jump);
		if (jP2PressedValid) addTexturesToButton(jumpButton, p2JumpPressedSprite, pressedPlayerTwoJumpSpriteID, is2P ? manager->disableTintingP2JumpTwoPlayer : manager->disableTintingP2Jump);
	}
}

class $modify(MyUILayer, UILayer) {
	#ifndef GEODE_IS_WINDOWS
	void togglePlatformerMode(bool platformer) {
		UILayer::togglePlatformerMode(platformer);
	#else
	void resetUINodeState() {
		UILayer::resetUINodeState();
	#endif
		if (!m_uiNodes || !m_gameLayer || !m_gameLayer->m_level || !m_gameLayer->m_level->isPlatformer()) return;
		findAndAddTextures(this, m_gameLayer);
	}

	bool processUINodeTouch(GJUITouchEvent touchEvent, int p1, cocos2d::CCPoint point, GJUINode* node) {
		const bool result = UILayer::processUINodeTouch(touchEvent, p1, point, node);
		const Manager* manager = Manager::getSharedInstance();
		if (!manager->enabled || !m_uiNodes || !m_gameLayer || !m_gameLayer->m_level || !m_gameLayer->m_level->isPlatformer() || !node->getChildren() || node->getChildrenCount() < 1) return result;

		const bool is2P = m_gameLayer->m_level->m_twoPlayerMode;

		if (!is2P && !manager->textureP1JumpWhenPressed && !manager->textureP2JumpWhenPressed && !manager->textureP1LeftWhenPressed && !manager->textureP2LeftWhenPressed && !manager->textureP1RightWhenPressed && !manager->textureP2RightWhenPressed) return result;
		if (is2P && !manager->textureP1JumpWhenPressedTwoPlayer && !manager->textureP2JumpWhenPressedTwoPlayer && !manager->textureP1LeftWhenPressedTwoPlayer && !manager->textureP2LeftWhenPressedTwoPlayer && !manager->textureP1RightWhenPressedTwoPlayer && !manager->textureP2RightWhenPressedTwoPlayer) return result;

		const auto platP1Move = manager->hasNodeIDs ? this->getChildByID("platformer-p1-move-button") : typeinfo_cast<GJUINode*>(m_uiNodes->objectAtIndex(0));
		const auto platP2Move = manager->hasNodeIDs ? this->getChildByID("platformer-p2-move-button") : typeinfo_cast<GJUINode*>(m_uiNodes->objectAtIndex(1));
		const auto platP1Jump = manager->hasNodeIDs ? this->getChildByID("platformer-p1-jump-button") : typeinfo_cast<GJUINode*>(m_uiNodes->objectAtIndex(2));
		const auto platP2Jump = manager->hasNodeIDs ? this->getChildByID("platformer-p2-jump-button") : typeinfo_cast<GJUINode*>(m_uiNodes->objectAtIndex(3));

		if (!platP1Move || !platP2Move || !platP1Jump || !platP2Jump) {
			log::info("something was a nullptr! !platP1Move: {} | !platP2Move: {} | !platP1Jump: {} | !platP2Jump: {}", !platP1Move, !platP2Move, !platP1Jump, !platP2Jump);
			return result;
		}

		if (touchEvent != GJUITouchEvent::Moved) log::info("————————————————————————————————————————————————————————————");
		if ((node == platP1Jump || node == platP2Jump) && result) MyUILayer::setJumpSpriteVisibility(node, touchEvent);
		else MyUILayer::setMoveSpriteVisibility(node);

		return result;
	}

	static void setJumpSpriteVisibility(GJUINode* node, const GJUITouchEvent touchEvent) {
		const bool isEnded = touchEvent == GJUITouchEvent::Ended;
		if (touchEvent == GJUITouchEvent::Pressed) log::info("user pressed player {} jump", node->m_player2 ? "two" : "one");
		else if (isEnded) log::info("user released player {} jump", node->m_player2 ? "two" : "one");
		MyUILayer::setSpriteVisibility(node, node->m_player2 ? unpressedPlayerTwoJumpSpriteID : unpressedPlayerOneJumpSpriteID, node->m_player2 ? pressedPlayerTwoJumpSpriteID : pressedPlayerOneJumpSpriteID, isEnded, platP2JumpOpacity);
	}

	static void setMoveSpriteVisibility(GJUINode* node) {
		const bool isLeft = node->m_currentButton == PlayerButton::Left;
		const bool isRight = node->m_currentButton == PlayerButton::Right;
		if (isLeft) log::info("user pressed player {} move left.", node->m_player2 ? "two" : "one");
		else if (isRight) log::info("user pressed player {} move right.", node->m_player2 ? "two" : "one");
		else log::info("releasing player {} move buttons", node->m_player2 ? "two" : "one");
		MyUILayer::setSpriteVisibility(node, node->m_player2 ? unpressedPlayerTwoLeftSpriteID : unpressedPlayerOneLeftSpriteID, node->m_player2 ? pressedPlayerTwoLeftSpriteID : pressedPlayerOneLeftSpriteID, !isLeft, platP2LeftOpacity);
		MyUILayer::setSpriteVisibility(node, node->m_player2 ? unpressedPlayerTwoRightSpriteID : unpressedPlayerOneRightSpriteID, node->m_player2 ? pressedPlayerTwoRightSpriteID : pressedPlayerOneRightSpriteID, !isRight, platP2RightOpacity);
	}

	static void setSpriteVisibility(GJUINode* node, const std::string& mainSpriteID, const std::string& pressedSpriteID, const bool showMainSprite, const GLubyte originalOpacity) {
		CCNode* mainSprite = node->getChildByIDRecursive(mainSpriteID);
		CCNode* presSprite = node->getChildByIDRecursive(pressedSpriteID);
		log::info("showMainSprite: {}", showMainSprite);
		log::info("mainSprite && presSprite: {}", mainSprite && presSprite);
		log::info("originalOpacity: {}", originalOpacity);
		if (mainSprite && presSprite) mainSprite->setVisible(showMainSprite);
		if (presSprite) {
			presSprite->setVisible(!showMainSprite);
			if (const auto originalSprite = typeinfo_cast<CCSprite*>(presSprite->getParent()); originalSprite && !mainSprite) originalSprite->setOpacity(showMainSprite ? originalOpacity : 0);
		}
	}
};

/*
honestly it's pretty sad to see that i had to hook
PlayLayer::resume() at all to clean up the mess that
robtop left behind. this shouldn't even be necessary,
but it was what worked for two of my three android
testers to stop the original sprites from revealing
themselves during game pause. pretty stupid but oh well
-- raydeeux
*/
class $modify(MyPlayLayer, PlayLayer) {
	void resume() {
		PlayLayer::resume();
		if (!m_uiLayer || !m_uiLayer->m_uiNodes) return;

		const Manager* manager = Manager::getSharedInstance();
		if (!manager->enabled) return;

		const auto platP1Move = manager->hasNodeIDs ? m_uiLayer->getChildByID("platformer-p1-move-button") : typeinfo_cast<GJUINode*>(m_uiLayer->m_uiNodes->objectAtIndex(0));
		const auto platP2Move = manager->hasNodeIDs ? m_uiLayer->getChildByID("platformer-p2-move-button") : typeinfo_cast<GJUINode*>(m_uiLayer->m_uiNodes->objectAtIndex(1));
		const auto platP1Jump = manager->hasNodeIDs ? m_uiLayer->getChildByID("platformer-p1-jump-button") : typeinfo_cast<GJUINode*>(m_uiLayer->m_uiNodes->objectAtIndex(2));
		const auto platP2Jump = manager->hasNodeIDs ? m_uiLayer->getChildByID("platformer-p2-jump-button") : typeinfo_cast<GJUINode*>(m_uiLayer->m_uiNodes->objectAtIndex(3));

		MyPlayLayer::originalTextureVisibilityMove(platP1Move);
		MyPlayLayer::originalTextureVisibilityMove(platP2Move);
		MyPlayLayer::originalTextureVisibilityJump(platP1Jump);
		MyPlayLayer::originalTextureVisibilityJump(platP2Jump);
	}
	static void originalTextureVisibilityJump(CCNode* jumpNode) {
		if (!jumpNode || jumpNode->getChildrenCount() < 1) return;
		if (const auto jumpButton = typeinfo_cast<CCSprite*>(jumpNode->getChildren()->objectAtIndex(0)); jumpButton && jumpButton->getChildByTag(6012025)) return jumpButton->setOpacity(0);
		log::info("[NULLPTR] AT {}'s jumpButton! on PlayLayer::resume() [originalTextureVisibilityJump]", jumpNode->getID());
	}
	static void originalTextureVisibilityMove(CCNode* moveNode) {
		if (!moveNode || moveNode->getChildrenCount() < 1) return;

		if (const auto leftButton = typeinfo_cast<CCSprite*>(moveNode->getChildren()->objectAtIndex(0)); leftButton && leftButton->getChildByTag(6012025)) leftButton->setOpacity(0);
		else log::info("[NULLPTR] AT {}'s leftButton! on PlayLayer::resume()", moveNode->getID());

		if (const auto rightButton = typeinfo_cast<CCSprite*>(moveNode->getChildren()->objectAtIndex(1)); rightButton && rightButton->getChildByTag(6012025)) rightButton->setOpacity(0);
		else log::info("[NULLPTR] AT {}'s rightButton! on PlayLayer::resume()", moveNode->getID());
	}
};

class $modify(MyMenuLayer, MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) return false;

		Manager* manager = Manager::getSharedInstance();
		if (manager->calledAlready) return true;

		manager->hasNodeIDs = Utils::isModLoaded("geode.node-ids");

		return true;
	}
};