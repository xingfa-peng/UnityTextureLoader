#pragma once

#include "Typedef.h"
namespace Inking
{
    class RefCounter
    {
        int _refCount = 1;
    public:
        RefCounter() {

        }

        virtual ~RefCounter() {

        }
        void AddRef() {
            _refCount++;
        }

        void Release() {
            --_refCount;
            if (_refCount == 0)
                delete this;
        }

        int GetRecCount() {
            return _refCount;
        }

    };
}
