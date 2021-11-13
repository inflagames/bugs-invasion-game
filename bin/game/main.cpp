// This file is part of the OGRE project.
// It is subject to the license terms in the LICENSE file found in the top-level directory
// of this distribution and at https://www.ogre3d.org/licensing.
// SPDX-License-Identifier: MIT

#include "inc/Game.h"

int main(int argc, char *argv[]) {
    Game app;
    app.initApp();
    app.getRoot()->startRendering();
    app.closeApp();
    return 0;
}
