APP_NAME=client
VERSION=0.0.1

PACKAGE_NAME="${APP_NAME}_${VERSION}"
BUILT_APP=../build/client/$APP_NAME

#Chequeo si existe la app
if [ ! -f "$BUILT_APP" ]; then
    echo "$BUILT_APP not found"
else 
    # Creo carpetas como si estuviera en la raiz de mis sistema
    mkdir -p $PACKAGE_NAME/usr/bin/
    mkdir -p $PACKAGE_NAME/usr/share/applications/
    mkdir -p $PACKAGE_NAME/usr/share/pixmaps/
    # Copio información del paquete
    cp -r DEBIAN $PACKAGE_NAME/
    # Copio entrada al menú de instalación
    cp assets/$APP_NAME.desktop $PACKAGE_NAME/usr/share/applications/
    # Copio logo
    cp assets/logo.png $PACKAGE_NAME/usr/share/pixmaps/$APP_NAME.png
    # Copio ejecutable, si símbolos de debug
    objcopy --strip-debug --strip-unneeded $BUILT_APP $PACKAGE_NAME/usr/bin/$APP_NAME
    # Actualizo los permisos
    chmod -R 755 $PACKAGE_NAME
    chmod -x $PACKAGE_NAME/usr/share/pixmaps/$APP_NAME.png
    # Armo el paquete simulando ser root
    fakeroot dpkg-deb --build $PACKAGE_NAME
fi
