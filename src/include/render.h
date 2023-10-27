#ifndef nevec_renderer_h
#define nevec_renderer_h

#define RED "\e[1;31m"
#define GREEN "\e[1;32m"
#define YELLOW "\e[1;33m"
#define BLUE "\e[1;34m"
#define MAGENTA "\e[1;35m"
#define WHITE "\e[1;37m"
#define RESET "\e[0m"

void setLine(int line);
void renderErrMsg(const char *fmt, va_list args);
void renderLocus(const char *fname, Loc loc);
void renderLine(char *src, Loc loc);
void highlightErr(Loc loc, const char *fmt, va_list args);
void highlightNote(Loc loc, const char *fmt, va_list args);
void highlightChange(Loc loc, const char *fmt, va_list args);
void renderHint(Loc loc, const char *fmt, va_list args);
void renderModifiedLine(char *src, Loc loc, const char *fmt, va_list args);
void renderFix(char *src, Loc loc, const char *fmt, va_list args);
#endif
