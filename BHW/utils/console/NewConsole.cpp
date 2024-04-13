#include "BHW/utils/console/NewConsole.hpp"

namespace BHW
{
    NewConsole<OutputStreamEvents<StdOut>, InputStreamEvents<StdIn>> StdConsole;
}