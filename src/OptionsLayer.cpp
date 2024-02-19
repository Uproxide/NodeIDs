#include <Geode/Bindings.hpp>
#include <Geode/modify/OptionsLayer.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/ui/BasedButtonSprite.hpp>
#include <Geode/utils/NodeIDs.hpp>


using namespace geode::prelude;
using namespace geode::node_ids;


$register_ids(OptionsLayer) {
    size_t labelOffset = 0;
    size_t menuOffset = 0;
    size_t sliderOffset = 0;
    size_t buttonOffset = 0;

    auto optionsLayer = static_cast<cocos2d::CCLayer*>(this->getChildren()->objectAtIndex(0));
    auto winSize = CCDirector::get()->getWinSize();

    getChildOfType<cocos2d::CCLabelBMFont>(optionsLayer, labelOffset)->setID("music-label");
    labelOffset++;

    getChildOfType<cocos2d::CCLabelBMFont>(optionsLayer, labelOffset)->setID("sfx-label");
    labelOffset++;

    getChildOfType<cocos2d::CCLabelBMFont>(optionsLayer, labelOffset)->setID("menu-music-label");

    getChildOfType<Slider>(optionsLayer, sliderOffset)->setID("music-slider");
    sliderOffset++;

    getChildOfType<Slider>(optionsLayer, sliderOffset)->setID("sfx-slider");

    getChildOfType<cocos2d::CCSprite>(optionsLayer, 0)->setID("left-chain");
    getChildOfType<cocos2d::CCSprite>(optionsLayer, 1)->setID("right-chain");
    getChildOfType<GJListLayer>(optionsLayer, 0)->setID("background"); // sorry i had nothing other than background for this

    auto topLeftMenu = getChildOfType<cocos2d::CCMenu>(optionsLayer, menuOffset);
    topLeftMenu->setID("top-left-menu");

    auto exitButton = getChildOfType<CCMenuItemSpriteExtra>(topLeftMenu, 0);
    exitButton->setID("exit-button");

    topLeftMenu->setPosition(0, winSize.height - exitButton->getContentSize().height / 1);
    topLeftMenu->setContentSize(ccp(32.5, 40));
    exitButton->setPosition(topLeftMenu->getContentSize().width / 2, topLeftMenu->getContentSize().height / 2);
    menuOffset++;



    auto optionsMenu = getChildOfType<cocos2d::CCMenu>(optionsLayer, menuOffset);
    optionsMenu->setID("options-menu");
    optionsMenu->setContentSize(ccp(306, 114));
    optionsMenu->setPosition(ccp(winSize.width / 2, 200));
    optionsMenu->setLayout(
    RowLayout::create()
        ->setGap(12.f)
        ->setGrowCrossAxis(true)
        ->setAxisAlignment(AxisAlignment::Center)
    );
    optionsMenu->updateLayout();
    menuOffset++;

    auto vaultMenu = getChildOfType<cocos2d::CCMenu>(optionsLayer, menuOffset);
    vaultMenu->setID("vault-menu");

    getChildOfType<CCMenuItemSpriteExtra>(vaultMenu, 0)->setID("vault-button");
    getChildOfType<CCMenuItemToggler>(vaultMenu, 0)->setID("menu-music-toggle");

    getChildOfType<CCMenuItemSpriteExtra>(optionsMenu, buttonOffset)->setID("account-button");
    buttonOffset++;

    getChildOfType<CCMenuItemSpriteExtra>(optionsMenu, buttonOffset)->setID("how-to-play-button");
    buttonOffset++;

    #ifdef GEODE_IS_DESKTOP
    getChildOfType<CCMenuItemSpriteExtra>(optionsMenu, buttonOffset)->setID("options-button");
    buttonOffset++;

    getChildOfType<CCMenuItemSpriteExtra>(optionsMenu, buttonOffset)->setID("graphics-button");
    buttonOffset++;

    getChildOfType<CCMenuItemSpriteExtra>(optionsMenu, buttonOffset)->setID("rate-button");
    buttonOffset++;

    getChildOfType<CCMenuItemSpriteExtra>(optionsMenu, buttonOffset)->setID("songs-button");
    buttonOffset++;

    getChildOfType<CCMenuItemSpriteExtra>(optionsMenu, buttonOffset)->setID("help-button");
    buttonOffset++;

    #else
    getChildOfType<CCMenuItemSpriteExtra>(optionsMenu, buttonOffset)->setID("options-button");
    buttonOffset++;

    getChildOfType<CCMenuItemSpriteExtra>(optionsMenu, buttonOffset)->setID("rate-button");
    buttonOffset++;

    getChildOfType<CCMenuItemSpriteExtra>(optionsMenu, buttonOffset)->setID("songs-button");
    buttonOffset++;

    getChildOfType<CCMenuItemSpriteExtra>(optionsMenu, buttonOffset)->setID("help-button");
    #endif
}

struct OptionsLayerIDs : Modify<OptionsLayerIDs, OptionsLayer> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("OptionsLayer::customSetup", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set OptionsLayer::customSetup hook priority, node IDs may not work properly");
        }
    }

    void customSetup() {
        OptionsLayer::customSetup();

        NodeIDs::get()->provide(this);
    }
};
