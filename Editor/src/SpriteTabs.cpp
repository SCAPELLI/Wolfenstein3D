#include <SpriteFileManager.h>
#include "SpriteTabs.h"
#include "EditorScreen.h"
#include "../../common/Style.h"
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

    std::map<int, std::string> weaponsMap =
            spriteFileManager.createMapFromTextureFileWithValues("weapons");
    this->textureList = new TextureList(0, this);
    this->textureList->setSpriteList(weaponsMap);
    this->addTab(this->textureList, "Wapons");

    std::map<int, std::string> decorationsMap =
            spriteFileManager.createMapFromTextureFileWithoutValues("decorations");
    this->decorationsList = new TextureList(0, this);
    this->decorationsList->setSpriteList(decorationsMap);
    this->addTab(this->decorationsList, "Decorations");

    std::map<int, std::string> walkableMap =
            spriteFileManager.createMapFromTextureFileWithoutValues("walkable");
    this->decorationsList = new TextureList(0, this);
    this->decorationsList->setSpriteList(walkableMap);
    this->addTab(this->decorationsList, "Walkable");

    Style style;
    style.setTabWidgetStyle(this);
}

SpriteTabs::~SpriteTabs() {
    delete this->textureList;
    delete this->itemsList;
    delete this->decorationsList;
}

void SpriteTabs::changeCurrentTexture(Texture &texture) {
    this->editorScreen->changeCurrentTexture(texture);
}