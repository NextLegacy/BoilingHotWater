#include "BHW/utils/console/ANSI.hpp"

namespace BHW
{
    std::string ANSI::ESCAPE        = "\033";
    std::string ANSI::CSI           = "["   ;
    std::string ANSI::END           = "m"   ;
    std::string ANSI::RESET         = "0"   ;
    std::string ANSI::BOLD          = "1"   ;
    std::string ANSI::DIM           = "2"   ;
    std::string ANSI::ITALIC        = "3"   ;
    std::string ANSI::UNDERLINE     = "4"   ;
    std::string ANSI::BLINK         = "5"   ;
    std::string ANSI::REVERSE       = "7"   ;
    std::string ANSI::HIDDEN        = "8"   ;
    std::string ANSI::STRIKETHROUGH = "9"   ;
    std::string ANSI::FOREGROUND    = "38"  ;
    std::string ANSI::BACKGROUND    = "48"  ;
    
    std::string ANSI::ANSI_CODE(std::string code)
    {
        return ANSI::ESCAPE + ANSI::CSI + code + ANSI::END;
    }

    std::string ANSI::COLOR(std::string type, uint32_t color)
    {
        return type + ";2;" +
                std::to_string((color >> 16) & 0xFF) + ";" +
                std::to_string((color >>  8) & 0xFF) + ";" +
                std::to_string( color        & 0xFF); 
    }

    ANSICode::ANSICode
    (
        bool     bold         , 
        bool     dim          ,
        bool     italic       ,
        bool     underline    , 
        bool     blink        , 
        bool     reverse      , 
        bool     hidden       , 
        bool     strikethrough, 
        uint32_t foreground   , 
        uint32_t background   
    ) : m_code(ANSI::ANSI_CODE(
            ( bold           ? ANSI::BOLD                                + ";" : "" ) +
            ( dim            ? ANSI::DIM                                 + ";" : "" ) +
            ( italic         ? ANSI::ITALIC                              + ";" : "" ) +
            ( underline      ? ANSI::UNDERLINE                           + ";" : "" ) +
            ( blink          ? ANSI::BLINK                               + ";" : "" ) +
            ( reverse        ? ANSI::REVERSE                             + ";" : "" ) +
            ( hidden         ? ANSI::HIDDEN                              + ";" : "" ) +
            ( strikethrough  ? ANSI::STRIKETHROUGH                       + ";" : "" ) +
            ( foreground > 0 ? ANSI::COLOR(ANSI::FOREGROUND, foreground) + ";" : "" ) +
            ( background > 0 ? ANSI::COLOR(ANSI::BACKGROUND, background)       : "" )   )) { }

    std::string ANSICode::operator()(const std::string string)
    {
        return m_code + string + ANSI::ANSI_CODE(ANSI::RESET);
    }

    ANSICodeBuilder::ANSICodeBuilder() 
        : m_bold         (false   ),
          m_dim          (false   ),
          m_italic       (false   ),
          m_underline    (false   ),
          m_blink        (false   ),
          m_reverse      (false   ),
          m_hidden       (false   ),
          m_strikethrough(false   ),
          m_forground    (0xFFFFFF),
          m_background   (0x000000) { }

    ANSICodeBuilder& ANSICodeBuilder::Bold         (bool     bold         ) { m_bold          = bold         ; return *this; }
    ANSICodeBuilder& ANSICodeBuilder::Dim          (bool     dim          ) { m_dim           = dim          ; return *this; }
    ANSICodeBuilder& ANSICodeBuilder::Italic       (bool     italic       ) { m_italic        = italic       ; return *this; }
    ANSICodeBuilder& ANSICodeBuilder::Underline    (bool     underline    ) { m_underline     = underline    ; return *this; }
    ANSICodeBuilder& ANSICodeBuilder::Blink        (bool     blink        ) { m_blink         = blink        ; return *this; }
    ANSICodeBuilder& ANSICodeBuilder::Reverse      (bool     reverse      ) { m_reverse       = reverse      ; return *this; }
    ANSICodeBuilder& ANSICodeBuilder::Hidden       (bool     hidden       ) { m_hidden        = hidden       ; return *this; }
    ANSICodeBuilder& ANSICodeBuilder::Strikethrough(bool     strikethrough) { m_strikethrough = strikethrough; return *this; }
    ANSICodeBuilder& ANSICodeBuilder::Foreground   (uint32_t forground    ) { m_forground     = forground    ; return *this; }
    ANSICodeBuilder& ANSICodeBuilder::Background   (uint32_t background   ) { m_background    = background   ; return *this; }

    ANSICode ANSICodeBuilder::Build()
    {
        return ANSICode(
            m_bold         , 
            m_dim          ,
            m_italic       ,
            m_underline    , 
            m_blink        , 
            m_reverse      , 
            m_hidden       , 
            m_strikethrough, 
            m_forground    , 
            m_background   
        );
    }
}
    