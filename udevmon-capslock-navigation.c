#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <linux/input.h>

// clang-format off
const struct input_event
    esc_up          = {.type = EV_KEY, .code = KEY_ESC,      .value = 0},
    esc_down        = {.type = EV_KEY, .code = KEY_ESC,      .value = 1},
    esc_repeat      = {.type = EV_KEY, .code = KEY_ESC,      .value = 2},
    capslock_up     = {.type = EV_KEY, .code = KEY_CAPSLOCK, .value = 0},
    capslock_down   = {.type = EV_KEY, .code = KEY_CAPSLOCK, .value = 1},
    capslock_repeat = {.type = EV_KEY, .code = KEY_CAPSLOCK, .value = 2},

    h_up     = {.type = EV_KEY, .code = KEY_H, .value = 0},
    h_down   = {.type = EV_KEY, .code = KEY_H, .value = 1},
    h_repeat = {.type = EV_KEY, .code = KEY_H, .value = 2},
    i_up     = {.type = EV_KEY, .code = KEY_I, .value = 0},
    i_down   = {.type = EV_KEY, .code = KEY_I, .value = 1},
    i_repeat = {.type = EV_KEY, .code = KEY_I, .value = 2},
    j_up     = {.type = EV_KEY, .code = KEY_J, .value = 0},
    j_down   = {.type = EV_KEY, .code = KEY_J, .value = 1},
    j_repeat = {.type = EV_KEY, .code = KEY_J, .value = 2},
    k_up     = {.type = EV_KEY, .code = KEY_K, .value = 0},
    k_down   = {.type = EV_KEY, .code = KEY_K, .value = 1},
    k_repeat = {.type = EV_KEY, .code = KEY_K, .value = 2},
    l_up     = {.type = EV_KEY, .code = KEY_L, .value = 0},
    l_down   = {.type = EV_KEY, .code = KEY_L, .value = 1},
    l_repeat = {.type = EV_KEY, .code = KEY_L, .value = 2},

    backspace_up     = {.type = EV_KEY, .code = KEY_BACKSPACE, .value = 0},
    backspace_down   = {.type = EV_KEY, .code = KEY_BACKSPACE, .value = 1},
    backspace_repeat = {.type = EV_KEY, .code = KEY_BACKSPACE, .value = 2},
    delete_up        = {.type = EV_KEY, .code = KEY_DELETE, .value = 0},
    delete_down      = {.type = EV_KEY, .code = KEY_DELETE, .value = 1},
    delete_repeat    = {.type = EV_KEY, .code = KEY_DELETE, .value = 2},
    semicolon_up     = {.type = EV_KEY, .code = KEY_SEMICOLON, .value = 0},
    semicolon_down   = {.type = EV_KEY, .code = KEY_SEMICOLON, .value = 1},
    semicolon_repeat = {.type = EV_KEY, .code = KEY_SEMICOLON, .value = 2},

    left_up      = {.type = EV_KEY, .code = KEY_LEFT,  .value = 0},
    left_down    = {.type = EV_KEY, .code = KEY_LEFT,  .value = 1},
    left_repeat  = {.type = EV_KEY, .code = KEY_LEFT,  .value = 2},
    down_up      = {.type = EV_KEY, .code = KEY_DOWN,  .value = 0},
    down_down    = {.type = EV_KEY, .code = KEY_DOWN,  .value = 1},
    down_repeat  = {.type = EV_KEY, .code = KEY_DOWN,  .value = 2},
    up_up        = {.type = EV_KEY, .code = KEY_UP,    .value = 0},
    up_down      = {.type = EV_KEY, .code = KEY_UP,    .value = 1},
    up_repeat    = {.type = EV_KEY, .code = KEY_UP,    .value = 2},
    right_up     = {.type = EV_KEY, .code = KEY_RIGHT, .value = 0},
    right_down   = {.type = EV_KEY, .code = KEY_RIGHT, .value = 1},
    right_repeat = {.type = EV_KEY, .code = KEY_RIGHT, .value = 2},

    home_up         = {.type = EV_KEY, .code = KEY_HOME,     .value = 0},
    home_down       = {.type = EV_KEY, .code = KEY_HOME,     .value = 1},
    home_repeat     = {.type = EV_KEY, .code = KEY_HOME,     .value = 2},
    pagedown_up     = {.type = EV_KEY, .code = KEY_PAGEDOWN, .value = 0},
    pagedown_down   = {.type = EV_KEY, .code = KEY_PAGEDOWN, .value = 1},
    pagedown_repeat = {.type = EV_KEY, .code = KEY_PAGEDOWN, .value = 2},
    pageup_up       = {.type = EV_KEY, .code = KEY_PAGEUP,   .value = 0},
    pageup_down     = {.type = EV_KEY, .code = KEY_PAGEUP,   .value = 1},
    pageup_repeat   = {.type = EV_KEY, .code = KEY_PAGEUP,   .value = 2},
    end_up          = {.type = EV_KEY, .code = KEY_END,      .value = 0},
    end_down        = {.type = EV_KEY, .code = KEY_END,      .value = 1},
    end_repeat      = {.type = EV_KEY, .code = KEY_END,      .value = 2},

    syn = {.type = EV_SYN, .code = SYN_REPORT, .value = 0};
// clang-format on

int equal(const struct input_event *first, const struct input_event *second)
{
    return first->type == second->type && first->code == second->code &&
           first->value == second->value;
}

int read_event(struct input_event *event)
{
    return fread(event, sizeof(struct input_event), 1, stdin) == 1;
}

void write_event(const struct input_event *event)
{
    if (fwrite(event, sizeof(struct input_event), 1, stdout) != 1)
        exit(EXIT_FAILURE);
}

int main(void)
{
    int capslock_is_down = 0, capslock_give_up = 0;
    struct input_event input;
    setbuf(stdin, NULL), setbuf(stdout, NULL);

    while (read_event(&input))
    {
        // Fluff
        if (input.type == EV_MSC && input.code == MSC_SCAN)
        {
            continue;
        }
        if (input.type != EV_KEY)
        {
            write_event(&input);
            continue;
        }

        if (equal(&input, &capslock_down))
        {
            // capslock was pressed, mark and supress
            capslock_is_down = 1;
            continue;
        }

        if (capslock_is_down)
        {
            // Something else happened while capslock was down
            if (equal(&input, &capslock_down) || equal(&input, &capslock_repeat))
            {
                // More capslock, suppress
                continue;
            }

            if (equal(&input, &capslock_up))
            {
                // capslock was released
                if (!capslock_give_up)
                {
                    // Nothing else happened in the meantime, handle as esc down+up
                    write_event(&esc_down);
                    write_event(&syn);
                    usleep(20000);
                    write_event(&esc_up);
                }
                capslock_is_down = 0;
                capslock_give_up = 0;
                continue;
            }

            // Something other than capslock happened
            capslock_give_up = 1;

            const struct input_event *mappings[21][2] = {
                {&h_up, &home_up},
                {&h_down, &home_down},
                {&h_repeat, &home_repeat},
                {&i_up, &up_up},
                {&i_down, &up_down},
                {&i_repeat, &up_repeat},
                {&j_up, &left_up},
                {&j_down, &left_down},
                {&j_repeat, &left_repeat},
                {&k_up, &down_up},
                {&k_down, &down_down},
                {&k_repeat, &down_repeat},
                {&l_up, &right_up},
                {&l_down, &right_down},
                {&l_repeat, &right_repeat},
                {&semicolon_up, &end_up},
                {&semicolon_down, &end_down},
                {&semicolon_repeat, &end_repeat},
                {&backspace_up, &delete_up},
                {&backspace_down, &delete_down},
                {&backspace_repeat, &delete_repeat},
            };

            int broke = 0;
            for (int i = 0; i < 21; i++)
            {
                const struct input_event *from = mappings[i][0],
                                         *to = mappings[i][1];
                if (equal(&input, from))
                {
                    write_event(to);
                    write_event(&syn);
                    usleep(20000);
                    broke = 1;
                    break;
                }
            }
            if (broke)
            {
                continue;
            }
        }

        write_event(&input);
    }
}
