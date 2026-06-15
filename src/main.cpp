#include <Geode/Geode.hpp>
#include <Geode/utils/web.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

void sendHandshakeVerification(std::string enteredCode) {
    std::string gdUsername = GJAccountManager::sharedState()->m_username;
    int accountID = GJAccountManager::sharedState()->m_accountID;

    matjson::Value payload;
    payload["code"] = enteredCode;
    payload["username"] = gdUsername;
    payload["accountId"] = std::to_string(accountID);

    web::WebRequest()
        .bodyJSON(payload)
        .post("http://127.0.0.1:5000/verify")
        .listen([](web::WebResponse* res) {
            if (res->isSuccess()) {
                FLAlertLayer::create("Success", "Handshake authorized! Token burned.", "OK")->show();
            } else {
                FLAlertLayer::create("Failed", "Incorrect or expired code.", "Try Again")->show();
            }
        });
}

class $modify(MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        auto menu = this->getChildByID("main-menu");
        
        auto btnSprite = ButtonSprite::create("Auth", "goldFont.fnt", "GJ_button_01.png", 0.8f);
        auto btn = CCMenuItemSpriteExtra::create(
            btnSprite, this, menu_selector(MenuLayer::onAuthTest)
        );
        btn->setID("nobo-auth-btn");
        menu->addChild(btn);
        menu->updateLayout();

        return true;
    }

    void onAuthTest(CCObject*) {
        geode::createQuickPopup(
            "Bridge Auth",
            "Enter the 6-character code from your Python terminal:",
            "Cancel", "Submit",
            [this](FLAlertLayer*, bool btn2) {
                if (btn2) {
                    sendHandshakeVerification("REPLACE_WITH_INPUT");
                }
            }
        );
    }
};
