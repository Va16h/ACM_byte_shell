#define ANSI_RESET_ALL          "\x1b[0m"

#define ANSI_COLOR_BLACK        "\x1b[30m"
#define ANSI_COLOR_RED          "\x1b[31m"
#define ANSI_COLOR_GREEN        "\x1b[32m"
#define ANSI_COLOR_YELLOW       "\x1b[33m"
#define ANSI_COLOR_BLUE         "\x1b[34m"
#define ANSI_COLOR_MAGENTA      "\x1b[35m"
#define ANSI_COLOR_CYAN         "\x1b[36m"
#define ANSI_COLOR_WHITE        "\x1b[37m"

#define ANSI_BACKGROUND_BLACK   "\x1b[40m"
#define ANSI_BACKGROUND_RED     "\x1b[41m"
#define ANSI_BACKGROUND_GREEN   "\x1b[42m"
#define ANSI_BACKGROUND_YELLOW  "\x1b[43m"
#define ANSI_BACKGROUND_BLUE    "\x1b[44m"
#define ANSI_BACKGROUND_MAGENTA "\x1b[45m"
#define ANSI_BACKGROUND_CYAN    "\x1b[46m"
#define ANSI_BACKGROUND_WHITE   "\x1b[47m"

#define ANSI_STYLE_BOLD         "\x1b[1m"
#define ANSI_STYLE_ITALIC       "\x1b[3m"
#define ANSI_STYLE_UNDERLINE    "\x1b[4m"

#define PRINT_STRING_1_ARGS(STYLE) printf("%s \x1b[0m\n", STYLE)
#define PRINT_STRING_2_ARGS(STYLE,STR) printf("%s %s \x1b[0m\n", STYLE, STR)
#define PRINT_STRING_3_ARGS(STYLE,STR,ARGS) printf("%s %s \x1b[0m\n", STYLE, STR, ARGS)

#define GET_4TH_ARG(arg1, arg2, arg3, arg4, ...) arg4
#define PRINT_STRING_MACRO_CHOOSER(...) \
    GET_4TH_ARG(__VA_ARGS__, PRINT_STRING_3_ARGS, \
                PRINT_STRING_2_ARGS, PRINT_STRING_1_ARGS, )

#define PRINT(...) PRINT_STRING_MACRO_CHOOSER(__VA_ARGS__)(__VA_ARGS__)

