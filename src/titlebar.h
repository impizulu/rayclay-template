#pragma once

#include "rayclay.h"

#include "theme.h"

#define BAR_H 46

/* macOS puts the window controls on the left; every other platform on the right. */
#if defined(__APPLE__)
#define CONTROLS_LEFT 1
#else
#define CONTROLS_LEFT 0
#endif

static void chip(const char *id, const char *svg, RC_Color hover)
{
    rcBox(.id = id, .w = "46px", .h = "grow", .align = "cc",
          .bg = rcIsHovered(id) ? hover : CLEAR) {
        rcSvg(svg, 16.0f, FG_TEXT);
    }
}

static void controls(void)
{
    rcRow(.h = "grow", .align = "cc") {
        if (CONTROLS_LEFT) {
            chip(RC_ID_WINDOW_CLOSE, ICONS "x.svg", DANGER);
            chip(RC_ID_WINDOW_MINIMIZE, ICONS "minus.svg", BG_HOVER);
            chip(RC_ID_WINDOW_MAXIMIZE,
                 rcIsWindowMaximized() ? ICONS "minimize.svg"
                                       : ICONS "maximize.svg",
                 BG_HOVER);
        } else {
            chip(RC_ID_WINDOW_MINIMIZE, ICONS "minus.svg", BG_HOVER);
            chip(RC_ID_WINDOW_MAXIMIZE,
                 rcIsWindowMaximized() ? ICONS "minimize.svg"
                                       : ICONS "maximize.svg",
                 BG_HOVER);
            chip(RC_ID_WINDOW_CLOSE, ICONS "x.svg", DANGER);
        }
    }
}

static void titlebar(const char *title)
{
    rcUnzoomed() {
        rcRow(.id = RC_ID_WINDOW_DRAG, .w = "grow", .hType = RC_PX(BAR_H),
              .bg = BG_PANEL, .align = "cl",
              /* The control cluster runs to the window edge, so the inset
                 goes on the side it is not on. */
              .pl = CONTROLS_LEFT ? 0 : 12,
              .pr = CONTROLS_LEFT ? 12 : 0) {
            if (CONTROLS_LEFT)
                controls();

            rcRow(.w = "grow", .h = "grow", .overflow = "hidden",
                  .gap = 10, .align = "cl") {
                rcSvg(ICONS "rayclay-logo-mono.svg", 22.0f, FG_TEXT);
                rcTextC(title, .color = FG_TEXT);
            }

            if (!CONTROLS_LEFT)
                controls();
        }
    }
}
