#include <SpriteFileManager.h>
#include "SpriteTabs.h"
#include "EditorScreen.h"
#include <map>

SpriteTabs::SpriteTabs(QWidget *parent, EditorScreen *editorScreen)
    : editorScreen(editorScreen) {
    SpriteFileManager spriteFileManager;
    std::map<std::string, std::map<int, std::string>> spriteMap =
            spriteFileManager.createMapFromTextureFile();
    this->textureList = new TextureList(0, this);
    this->textureList->setSpriteList(spriteMap["textures"]);
    this->addTab(this->textureList, "Textures");

    this->itemsList = new TextureList(0, this);
    this->itemsList->setSpriteList(spriteMap["items"]);
    this->addTab(this->itemsList, "Items");

    this->decorationsList = new TextureList(0, this);
    this->decorationsList->setSpriteList(spriteMap["decorations"]);
    this->addTab(this->decorationsList, "Decorations");
}

SpriteTabs::~SpriteTabs() {
    delete this->textureList;
    delete this->itemsList;
    delete this->decorationsList;
}

void SpriteTabs::changeCurrentTexture(Texture texture) {
    this->editorScreen->changeCurrentTexture(texture);
}