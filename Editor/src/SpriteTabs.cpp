#include <SpriteFileManager.h>
#include "SpriteTabs.h"
#include "EditorScreen.h"
#include <map>

SpriteTabs::SpriteTabs(QWidget *parent, EditorScreen *editorScreen)
    : editorScreen(editorScreen) {
    SpriteFileManager spriteFileManager;

    std::map<int, std::string> texturesMap =
            spriteFileManager.createMapFromTextureFileWithoutValues("textures");
    this->itemsList = new TextureList(0, this);
    this->itemsList->setSpriteList(texturesMap);
    this->addTab(this->itemsList, "Textures");

    std::map<int, std::string> itemsMap =
            spriteFileManager.createMapFromTextureFileWithValues("items");
    this->textureList = new TextureList(0, this);
    this->textureList->setSpriteList(itemsMap);
    this->addTab(this->textureList, "Items");

    std::map<int, std::string> decorationsMap =
            spriteFileManager.createMapFromTextureFileWithoutValues("decorations");
    this->decorationsList = new TextureList(0, this);
    this->decorationsList->setSpriteList(decorationsMap);
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