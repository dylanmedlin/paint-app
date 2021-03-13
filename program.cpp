#include "splashkit.h"

using namespace std;

#define TOP_BOUNDRY 60.0

// Video link: https://youtu.be/_0N1bdov79E

struct button
{
    double x;
    double y;
    double width;
    double height;
};

void draw_button(button &button, color value, string name)
{
    fill_rectangle(value, button.x, button.y, button.width, button.height);             // background color of button
    draw_rectangle(COLOR_BLACK, button.x, button.y, button.width, button.height);       // black border around the button
    draw_text(name, COLOR_BLACK, button.x + 5, button.y + 7);    // text that appears on the button
}

void color_menu()
{
    const int no_of_colors = 5;
    
    double color_width = 50;
    double color_height = 50;
    double menu_start_x = screen_width() - (color_width * no_of_colors);
    double menu_start_y = 0;
    color colors[no_of_colors] = {COLOR_BLACK, COLOR_GRAY, COLOR_RED, COLOR_GREEN, COLOR_BLUE};

    for (int i = 0; i < no_of_colors; i++)
    {
        double x = menu_start_x + (color_width * i);
        fill_rectangle(colors[i], x, menu_start_y, color_width, color_height);
    }
}

void selected_color_box(color selected_color)
{
    fill_rectangle(selected_color, 750, 550, 40, 40);
    draw_rectangle(COLOR_BLACK, 750, 550, 40, 40);
}

void pen_size_box(int pen_size)
{   
    button size2x;
    size2x.x = 0;
    size2x.y = 0;
    size2x.width = 100;
    size2x.height = 25;

    draw_button(size2x, COLOR_ALICE_BLUE, "Pen size: " + to_string(pen_size));
}

void make_gui(color selected_color, int pen_size)
{
    draw_rectangle(COLOR_GRAY, 0, 0, screen_width(), TOP_BOUNDRY);
    
    button c_hotkey;
    c_hotkey.x = 150;
    c_hotkey.y = 0;
    c_hotkey.width = 150;
    c_hotkey.height = 25;
    draw_button(c_hotkey, COLOR_ALICE_BLUE, "'C' to clear");

    selected_color_box(selected_color);
    color_menu();
    pen_size_box(pen_size);
}

void draw_pixel2x(color selected_color)
{
    fill_rectangle(selected_color, mouse_x(), mouse_y(), 4, 4);
}

int main()
{
    open_window("Paint", 800, 600);
    clear_screen(COLOR_WHITE);

    int pen_size = 1;
    color selected_color = COLOR_BLACK;

    make_gui(selected_color, pen_size);

    while (!quit_requested() == true)
    {
        process_events();   // Check for keyboard presses, mouse movement, etc.

        // Color select / eyedropper
        if (mouse_clicked(RIGHT_BUTTON))
        {
            selected_color = get_pixel(mouse_x(), screen_height() - mouse_y());
            selected_color_box(selected_color);
        }

        // Drawing
        if (mouse_down(LEFT_BUTTON) and mouse_y() > TOP_BOUNDRY)
        {
            if (pen_size == 2)
            {
                draw_pixel2x(selected_color);
            }
            else
            {
                draw_pixel(selected_color, mouse_position());
            }
        }

        // Clear drawing
        if (key_typed(C_KEY))
        {
            clear_screen(COLOR_WHITE);
            make_gui(selected_color, pen_size);
        }

        // Pen size
        if (key_typed(NUM_1_KEY))
        {
            pen_size = 1;
            pen_size_box(pen_size);
        }
        if (key_typed(NUM_2_KEY))
        {
            pen_size = 2;
            pen_size_box(pen_size);
        }

        refresh_screen();
    }

    return 0;
}