#include "rayclay.h"

#include "theme.h"
#include "sidebar.h"
#include "content.h"
#include "titlebar.h"

typedef struct App {
    bool sidebar_open;
    RC_Color logo;
} App;

static void layout(RC_App *app, void *user_data)
{
    App *state = (App *)user_data;

    rcColumn(.id = "Root", .w = "grow", .h = "grow", .bg = BG_APP) {
        titlebar("RayClay Tutorial App");

        rcRow(.w = "grow", .h = "grow") {
            sidebar(&state->sidebar_open);
            content(app, &state->logo);
        }
    }
}

int main(void)
{
    App app = {
        .sidebar_open = true,
        .logo = ACCENT,
    };
    RC_AppOptions options = {
        .width = 960,
        .height = 620,
        .title = "RayClay Tutorial App",
        .iconPath = ICONS "app-icon.png",

        .nativeFrame = true,
        .titlebarHeight = BAR_H,
        .titlebar = { .custom = true },

        .zoom = { .pan = true },

        .layoutCallback = layout,
        .userData = &app,
    };

    return rcRunApp(&options);
}
