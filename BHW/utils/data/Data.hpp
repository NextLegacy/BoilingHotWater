#pragma once

namespace BHW
{
    template <typename TData, typename ...TArgs>
    struct DataStorage : public TData
    {
        inline DataStorage(TArgs... args) : TData(args...) { }
    };

    template <typename ...TDataStorages>
    struct DataStorages : public DataStorage<std::tuple<TDataStorages...>> 
    { 
        template <typename TDataStorage>
        inline TDataStorage& Get() 
        {
            return std::get<TDataStorage>(*this);
        }
    };
}