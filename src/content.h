#pragma once

#include <stdlib.h>

#include "rayclay.h"

#include "theme.h"

static void shortcut(const char *keys, const char *description)
{
    rcRow(.w = "grow", .gap = 16) {
        rcBox(.w = "190px") {
            rcTextC(keys, .color = ACCENT);
        }
        rcTextC(description, .color = FG_MUTED);
    }
}

static void content(RC_App *app, RC_Color *logo)
{
    rcColumn(.w = "grow", .h = "grow", .bg = BG_APP, .p = 32,
             .gap = 24, .align = "tc") {
        rcBox(.id = "Logo", .w = "fit", .h = "fit") {
            rcSvg(ICONS "rayclay-logo-mono.svg", 140.0f, *logo);
        }
        if (rcClicked("Logo"))
            *logo = rcRgb(rand() % 256, rand() % 256, rand() % 256);

        rcColumn(.w = "grow", .gap = 8) {
            shortcut("Ctrl / Cmd  +  =", "zoom in");
            shortcut("Ctrl / Cmd  +  -", "zoom out");
            shortcut("Ctrl / Cmd  +  0", "reset to 100%");
            shortcut("Ctrl / Cmd  +  wheel", "continuous zoom");
            shortcut("Space  +  drag", "pan  (optical mode, opt-in)");
        }

        RC_Window *window = rcAppMainWindow(app);
        bool optical = rcWindowZoomMode(window) == RC_ZOOM_OPTICAL;
        rcBox(.id = "Mode", .w = "fit", .px = 14, .py = 8,
              .borderRadius = "all-sm",
              .bg = rcIsHovered("Mode") ? BG_HOVER : CLEAR,
              .border = { .color = ACCENT, .width = "1px" }) {
            rcTextC(optical ? "optical zoom  (canvas-like)"
                            : "layout zoom  (browser-like)",
                    .color = FG_TEXT);
        }
        if (rcClicked("Mode"))
            rcWindowSetZoomMode(window,
                                optical ? RC_ZOOM_LAYOUT : RC_ZOOM_OPTICAL);
    }
}
