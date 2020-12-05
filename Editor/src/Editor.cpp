#include <MenuWindow.h>
#include "../include/Editor.h"


Editor::Editor() {
    MenuWindow menu(this);
    menu.show();
}

Editor::~Editor() {

}