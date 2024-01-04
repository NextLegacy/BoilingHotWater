#pragma once

#include "BHW/utils/reflection/Member.hpp"
#include "BHW/utils/reflection/Value.hpp"
#include "BHW/utils/reflection/Type.hpp"
#include "BHW/utils/reflection/TypeInfo.hpp"
#include "BHW/utils/reflection/ReflectionDefinitions.hpp"

BHW_REFLECT(bool              );
BHW_REFLECT(char              );
BHW_REFLECT(unsigned char     );
BHW_REFLECT(short             );
BHW_REFLECT(unsigned short    );
BHW_REFLECT(int               );
BHW_REFLECT(unsigned int      );
BHW_REFLECT(long              );
BHW_REFLECT(unsigned long     );
BHW_REFLECT(long long         );
BHW_REFLECT(unsigned long long);
BHW_REFLECT(float             );
BHW_REFLECT(double            );
BHW_REFLECT(long double       );
BHW_REFLECT(std::string       );
BHW_REFLECT(std::string_view  );

/*
BHW_REFLECT(std::vector<bool              >);
BHW_REFLECT(std::vector<char              >);
BHW_REFLECT(std::vector<unsigned char     >);
BHW_REFLECT(std::vector<short             >);
BHW_REFLECT(std::vector<unsigned short    >);
BHW_REFLECT(std::vector<int               >);
BHW_REFLECT(std::vector<unsigned int      >);
BHW_REFLECT(std::vector<long              >);
BHW_REFLECT(std::vector<unsigned long     >);
BHW_REFLECT(std::vector<long long         >);
BHW_REFLECT(std::vector<unsigned long long>);
BHW_REFLECT(std::vector<float             >);
BHW_REFLECT(std::vector<double            >);
BHW_REFLECT(std::vector<long double       >);
BHW_REFLECT(std::vector<std::string       >);
BHW_REFLECT(std::vector<std::string_view  >);

BHW_REFLECT(std::vector<std::vector<bool              >>);
BHW_REFLECT(std::vector<std::vector<char              >>);
BHW_REFLECT(std::vector<std::vector<unsigned char     >>);
BHW_REFLECT(std::vector<std::vector<short             >>);
BHW_REFLECT(std::vector<std::vector<unsigned short    >>);
BHW_REFLECT(std::vector<std::vector<int               >>);
BHW_REFLECT(std::vector<std::vector<unsigned int      >>);
BHW_REFLECT(std::vector<std::vector<long              >>);
BHW_REFLECT(std::vector<std::vector<unsigned long     >>);
BHW_REFLECT(std::vector<std::vector<long long         >>);
BHW_REFLECT(std::vector<std::vector<unsigned long long>>);
BHW_REFLECT(std::vector<std::vector<float             >>);
BHW_REFLECT(std::vector<std::vector<double            >>);
BHW_REFLECT(std::vector<std::vector<long double       >>);
BHW_REFLECT(std::vector<std::vector<std::string       >>);
BHW_REFLECT(std::vector<std::vector<std::string_view  >>);
*/