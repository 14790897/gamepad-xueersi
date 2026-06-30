idf_component_register(
    SRCS
        "main.cpp"
        "game.cpp"
        "input.cpp"
        "buzzer.cpp"
    INCLUDE_DIRS "."
    REQUIRES driver esp_lcd tft_display
)
