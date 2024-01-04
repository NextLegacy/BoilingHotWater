#pragma once

#include <string>

namespace BHW
{
    namespace ANSI
    {
        extern std::string ESCAPE       ;
        extern std::string CSI          ;
        extern std::string END          ;

        extern std::string RESET        ;

        extern std::string BOLD         ;
        extern std::string DIM          ;
        extern std::string ITALIC       ;
        extern std::string UNDERLINE    ;
        extern std::string BLINK        ;
        extern std::string REVERSE      ;
        extern std::string HIDDEN       ;
        extern std::string STRIKETHROUGH;
    
        extern std::string FOREGROUND   ;
        extern std::string BACKGROUND   ;

        std::string ANSI_CODE(std::string code);

        std::string COLOR(std::string type, uint32_t color);
    }

    class ANSICode
    {
    public:
        ANSICode(
            bool     bold         , 
            bool     dim          ,
            bool     italic       ,
            bool     underline    , 
            bool     blink        , 
            bool     reverse      , 
            bool     hidden       , 
            bool     strikethrough, 
            uint32_t forground    , 
            uint32_t background   
        );

        std::string operator()(std::string code);

    private:
        std::string m_code;
    };

    class ANSICodeBuilder
    {
    public:
        ANSICodeBuilder();

        ANSICodeBuilder& Bold         (bool    value = true);
        ANSICodeBuilder& Dim          (bool    value = true);
        ANSICodeBuilder& Italic       (bool    value = true);
        ANSICodeBuilder& Underline    (bool    value = true);
        ANSICodeBuilder& Blink        (bool    value = true);
        ANSICodeBuilder& Reverse      (bool    value = true);
        ANSICodeBuilder& Hidden       (bool    value = true);
        ANSICodeBuilder& Strikethrough(bool    value = true);

        ANSICodeBuilder& Foreground   (uint32_t value = 0xFFFFFF);
        ANSICodeBuilder& Background   (uint32_t value = 0x000000);

        ANSICode Build();

    private:
        bool m_bold         ;
        bool m_dim          ;
        bool m_italic       ;
        bool m_underline    ;
        bool m_blink        ;
        bool m_reverse      ;
        bool m_hidden       ;
        bool m_strikethrough;

        uint32_t m_forground ;
        uint32_t m_background;
    };
}