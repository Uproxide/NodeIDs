#include <Geode/Bindings.hpp>
#include <Geode/modify/GauntletSelectLayer.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/ui/BasedButtonSprite.hpp>
#include <Geode/utils/NodeIDs.hpp>


using namespace geode::prelude;
using namespace geode::node_ids;


$register_ids(GauntletSelectLayer) {

    auto gauntletLayer = static_cast<cocos2d::CCLayer*>(this->getChildren()->objectAtIndex(0));
    auto winSize = CCDirector::get()->getWinSize();


};

struct GauntletSelectLayerIDs : Modify<GauntletSelectLayerIDs, GauntletSelectLayer> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("GauntletSelectLayer::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set GauntletSelectLayer::init hook priority, node IDs may not work properly");
        }
    }

    bool init(int p0) {
        if(!GauntletSelectLayer::init(p0)) return false;

        NodeIDs::get()->provide(this);

        return true;
    }
};